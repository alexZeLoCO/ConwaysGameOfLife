#include <jansson.h>
#include <stdio.h>
#include <string.h>

#include "factory.h"

board *get_from_json(char *filename, int padding)
{
  board *out;

  // Open the JSON file
  FILE *file = fopen(filename, "r");
  if (!file)
    error("Failed to open the JSON file\n", 31);

  // Read the contents of the JSON file
  fseek(file, 0, SEEK_END);
  long file_size = ftell(file);
  fseek(file, 0, SEEK_SET);
  char *json_data = (char *)malloc(file_size + 1);
  fread(json_data, 1, file_size, file);
  json_data[file_size] = '\0';
  fclose(file);
  // free(file);

  // Parse the JSON data
  json_error_t json_error;
  json_t *root = json_loads(json_data, 0, &json_error);
  free(json_data);

  if (!root)
    error("Failed to parse the JSON data", 32);

  // Extract values from the JSON object
  const char *name = json_string_value(json_object_get(root, "name"));

  // One row and column on each side is added for padding
  out = new_board(
      padding,
      json_integer_value(json_object_get(root, "rows")),
      json_integer_value(json_object_get(root, "columns")));

  json_t *array = json_object_get(root, "array");
  size_t array_size = json_array_size(array);

  for (size_t i = 0; i < array_size; i++)
  {
    json_t *item = json_array_get(array, i);
    // One row and column is added to compensate the padding
    set_cell(out,
             json_integer_value(json_object_get(item, "x")),
             json_integer_value(json_object_get(item, "y")),
             POPULATED);
  }

  // Cleanup
  json_decref(root);

  return out;
}

board *get_from_template(template name, int padding)
{
  switch (name)
  {
  case BLINKER:
    return get_from_json("templates/blinker.json", padding);
  case BEACON:
    return get_from_json("templates/beacon.json", padding);
  case TOAD:
    return get_from_json("templates/toad.json", padding);
  case GLIDER:
    return get_from_json("templates/glider.json", padding);
  case LWSS:
    return get_from_json("templates/lwss.json", padding);
  case MWSS:
    return get_from_json("templates/mwss.json", padding);
  case HWSS:
    return get_from_json("templates/hwss.json", padding);
  case GGG:
    return get_from_json("templates/ggg.json", padding);
  case SGG:
    return get_from_json("templates/sgg.json", padding);
  case PENTOMINO:
    return get_from_json("templates/pentomino.json", padding);
  case DIEHARD:
    return get_from_json("templates/diehard.json", padding);
  case DIAMOND:
    return get_from_json("templates/diamond.json", padding);
  }
}

template get_template_from_name(char *name)
{
  if (strcmp(name, "BLINKER") == 0)
    return BLINKER;
  if (strcmp(name, "BEACON") == 0)
    return BEACON;
  if (strcmp(name, "TOAD") == 0)
    return TOAD;
  if (strcmp(name, "GLIDER") == 0)
    return GLIDER;
  if (strcmp(name, "LWSS") == 0)
    return LWSS;
  if (strcmp(name, "MWSS") == 0)
    return MWSS;
  if (strcmp(name, "HWSS") == 0)
    return HWSS;
  if (strcmp(name, "GGG") == 0)
    return GGG;
  if (strcmp(name, "SGG") == 0)
    return SGG;
  if (strcmp(name, "PENTOMINO") == 0)
    return PENTOMINO;
  if (strcmp(name, "DIEHARD") == 0)
    return DIEHARD;
  if (strcmp(name, "DIAMOND") == 0)
    return DIAMOND;
  return BLINKER;
}

char *min(char *a, char *b)
{
  if (a == NULL)
    return b;
  if (b == NULL)
    return a;
  return a < b ? a : b;
}

int is_valid(char maybe_valid)
{
  return (maybe_valid >= '0' && maybe_valid <= '9') || maybe_valid == 'b' || maybe_valid == 'o' || maybe_valid == '$';
}

// FIXME: This no worky (still)
board *get_from_rle(char *filename, int padding)
{
  board *out;
  FILE *fp = fopen(filename, "r");
  if (fp == NULL)
    error("File was not found", 40);
  char c;
  int bufsize = 100;
  char *buf = (char *)malloc(bufsize * sizeof(char));
  while ((c = getc(fp)) == '#')
    fgets(buf, bufsize, fp); // Discard

  fgets(buf, bufsize, fp);        // rows, cols and rule line
  char *x = strchr(buf, '=') + 2; // rows
  int n_cols = atoi(x);
  char *y = strchr(x, '=') + 2; // cols
  int n_rows = atoi(y);

  info("rows: %d cols: %d\n", n_rows, n_cols);
  out = new_board(padding, n_rows, n_cols);

  int row = 0;
  int column = 0;
  int repeat = 0;
  char current = fgetc(fp);

  while (!feof(fp))
  {
    if (is_valid(current))
    {
      info("Current: %c\n", current);
      if (current >= '0' && current <= '9')
      {
        if (repeat > 0)
          repeat = repeat * 10 + (current - '0');
        else
          repeat = current - '0';
        info("Operation will be repeated %d times\n", repeat);
      }
      else
      {
        repeat = repeat > 1 ? repeat : 1;
        if (current == '$')
        {
          column = 0;
          row += repeat;
          info("Skipping to row %d\n", row);
        }
        else
        {
          for (int i = 0; i < repeat; i++)
            set_cell(out, column + i, row, current == 'o' ? POPULATED : EMPTY);
          info("Executing %c %d times (at row: %d, col: %d)\n", current, repeat, row, column);
          column += repeat;
        }
        repeat = 0;
      }
    }
    current = fgetc(fp);
  }

  // show_board(out);
  return out;
}

int get_number_of_lines_from_file(FILE *fp)
{
  if (fp == NULL)
    error("File not found", 40);
  int out = 0;
  char c;
  for (c = getc(fp); c != EOF; c = getc(fp))
    if (c == '\n')
      out++;
  return out;
}

board *get_from_plaintext(char *filename, int padding)
{
  FILE *fp = fopen(filename, "r");
  if (fp == NULL)
    error("File not found", 40);
  int sizeofbuf = 100;
  char *buf = (char *)malloc(sizeof(char) * sizeofbuf);
  board *the_board = NULL;
  int n_row = 0;
  int n_col = 0;
  while (fgets(buf, sizeofbuf, fp))
  {
    info("Read: %s", buf);
    if (*(buf) != '!') // Skip lines starting with '!'
    {
      int buf_len = strlen(buf) - 2; // Remove \n
      if (the_board == NULL)
        the_board = new_board(padding, get_number_of_lines_from_file(fopen(filename, "r") // We have to create a new fp to avoid using the lines left in the actual fp we are using
                                                                     ),
                              buf_len);
      for (int n_col = 0; n_col < buf_len; n_col++)
      {
        info("Setting row: %d, col: %d value %c (%d)\n", n_row, n_col, *(buf + n_col), *(buf + n_col) == '.' ? EMPTY : POPULATED);
        set_cell(the_board, n_col, n_row, *(buf + n_col) == '.' ? EMPTY : POPULATED);
      }
      n_row++;
    }
  }
  return the_board;
}
