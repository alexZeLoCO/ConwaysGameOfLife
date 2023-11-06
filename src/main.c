#include <stdio.h>

#include "../libs/board/board.h"
#include "../libs/game/logic/logic.h"
#include "../libs/game/factory/factory.h"
#include "../libs/logging/log/log.h"

struct parameters {
	int n_iters;
	char* template_clue; // Could be a json, rle, plaintext file or template name
	int padding;
};

struct parameters* parse_args (int argc, char** argv)
{
	// printf("%d\n", argc);
	if (argc != 4) error("USE: ./main path/to/template.cells n_iters", 20);
	struct parameters *the_args = (struct parameters*) malloc (sizeof(struct parameters));
	the_args->template_clue = *(argv+1);
	the_args->n_iters = atoi(*(argv+2));
	the_args->padding = atoi(*(argv+3));
	return the_args;
}

board* get_from_file (struct parameters* the_parameters)
{
	char* file_extension = strrchr(the_parameters->template_clue, '.')+1;
	// printf("File has extension %s\n", file_extension);
	if (strcmp(file_extension, "json") == 0) return get_from_json(the_parameters->template_clue, the_parameters->padding);
	if (strcmp(file_extension, "rle") == 0) return get_from_rle(the_parameters->template_clue, the_parameters->padding);
	if (strcmp(file_extension, "cells") == 0) return get_from_plaintext(the_parameters->template_clue, the_parameters->padding);
	return get_from_template(get_template_from_name(the_parameters->template_clue), the_parameters->padding);
}

int main (int argc, char** argv)
{
	set_logging_on(1);
	struct parameters *the_parameters = parse_args(argc, argv);
	board* my_board = get_from_file(the_parameters);
	loop(my_board, the_parameters->n_iters);
	free(my_board);
	return 0;
}

