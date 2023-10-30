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
  // free(file);

  // Parse the JSON data
  json_error_t json_error;
  json_t *root = json_loads(json_data, 0, &json_error);
  free(json_data);

  if (!root) error("Failed to parse the JSON data", 32);

	// Extract values from the JSON object
  const char *name = json_string_value(json_object_get(root, "name"));
  const int padding = json_integer_value(json_object_get(root, "padding"));

  // One row and column on each side is added for padding
	out = new_board(
      padding,
      json_integer_value(json_object_get(root, "rows")),
      json_integer_value(json_object_get(root, "columns"))
  );

  json_t *array = json_object_get(root, "array");
  size_t array_size = json_array_size(array);

  for (size_t i = 0; i < array_size; i++) {
    json_t *item = json_array_get(array, i);
    // One row and column is added to compensate the padding
    set_cell(out,
      json_integer_value(json_object_get(item, "x")),
      json_integer_value(json_object_get(item, "y")),
      POPULATED
    );
  }

  // Cleanup
  json_decref(root);

  return out;
}

board* get_from_template (template name)
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
    case DIEHARD: return get_from_file("templates/diehard.json");
    case DIAMOND: return get_from_file("templates/diamond.json");
  }
}

template get_template_from_name (char* name)
{
  if (strcmp(name, "BLINKER") == 0) return BLINKER;
  if (strcmp(name, "BEACON") == 0) return BEACON;
  if (strcmp(name, "TOAD") == 0) return TOAD;
  if (strcmp(name, "GLIDER") == 0) return GLIDER;
  if (strcmp(name, "LWSS") == 0) return LWSS;
  if (strcmp(name, "MWSS") == 0) return MWSS;
  if (strcmp(name, "HWSS") == 0) return HWSS;
  if (strcmp(name, "GGG") == 0) return GGG;
  if (strcmp(name, "SGG") == 0) return SGG;
  if (strcmp(name, "PENTOMINO") == 0) return PENTOMINO;
  if (strcmp(name, "DIEHARD") == 0) return DIEHARD;
  if (strcmp(name, "DIAMOND") == 0) return DIAMOND;
  return BLINKER;
}

char* min(char* a, char* b){
  return a < b ? a : b; 
}

board* get_from_rle (char* filename)
{
  board* out;
  FILE* fp = fopen(filename, "r");
  char c;
  int bufsize = 100;
  char* buf = (char*) malloc (bufsize * sizeof(char));
  while ((c = getc(fp)) == '#')
    fgets(buf, bufsize, fp); // Discard
  
  fgets(buf, bufsize, fp); // rows, cols and rule line
  char* x = strchr(buf, '=')+2; // rows
  int n_cols = atoi(x);
  char* y = strchr(x, '=')+2; // cols
  int n_rows = atoi(y);

  out = new_board(50, n_rows, n_cols);

  while (fgets(buf, bufsize, fp))
  {
    printf("READ: %s", buf);
    int row = 0;
    int column = 0;
    char  
      *current = buf,
      *last = strchr(buf, '\n');
    while (current < last)
    {
      if (*(current) == '$') row++;
      int repeat = atoi(current) + column;
      char *operation = (min(strchr(current, 'b'), strchr(current, 'o')));
      for (int i = column ; i < repeat ; i++)
        set_cell(out, i, row, *operation == 'b' ? EMPTY : POPULATED);
      column += repeat;
      current = operation+1;
    }
  }
  return out;
}

