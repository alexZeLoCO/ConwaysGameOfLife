#include <jansson.h>

#include "factory.h"

board* get_from_file (char* filename)
{
	board* out;

	// Open the JSON file
  FILE *file = fopen(filename, "r");
  if (!file) error("Failed to open the JSON file\n", 31);

  // Read the contents of the JSON file
  fseek(file, 0, SEEK_END);
  long file_size = ftell(file);
  fseek(file, 0, SEEK_SET);
  char *json_data = (char *) malloc(file_size + 1);
  fread(json_data, 1, file_size, file);
  json_data[file_size] = '\0';
  fclose(file);

  // Parse the JSON data
  json_error_t json_error;
  json_t *root = json_loads(json_data, 0, &json_error);
  free(json_data);

  if (!root) error("Failed to parse the JSON data", 32);

	// Extract values from the JSON object
  const char *name = json_string_value(json_object_get(root, "name"));

	out = new_board(
      json_integer_value(json_object_get(root, "rows")),
      json_integer_value(json_object_get(root, "columns"))
  );

  json_t *array = json_object_get(root, "array");
  size_t array_size = json_array_size(array);

  for (size_t i = 0; i < array_size; i++) {
    json_t *item = json_array_get(array, i);
    set_cell(out,
      json_integer_value(json_object_get(item, "y")),
      json_integer_value(json_object_get(item, "x")),
      POPULATED
    );
  }

  // Cleanup
  json_decref(root);

  return out;
}

board* get_from_name (template name)
{
  switch(name)
  {
    case BLINKER: return get_from_file("templates/blinker.json");
    case BEACON: return get_from_file("templates/beacon.json");
    case TOAD: return get_from_file("templates/toad.json");
    case GLIDER: return get_from_file("templates/glider.json");
    case LWSS: return get_from_file("templates/lwss.json");
    case MWSS: return get_from_file("templates/mwss.json");
    case HWSS: return get_from_file("templates/hwss.json");
    case GGG: return get_from_file("templates/ggg.json");
    case SGG: return get_from_file("templates/sgg.json");
    case PENTOMINO: return get_from_file("templates/pentomino.json");
    case DIEHARD: return get_from_file("templates/diaehard.json");
    case DIAMOND: return get_from_file("templates/diamond.json");
  }
}

