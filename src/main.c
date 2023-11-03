#include <stdio.h>

#include "../libs/board/board.h"
#include "../libs/game/logic/logic.h"
#include "../libs/game/factory/factory.h"

struct parameters {
	int n_iters;
	char* template_clue; // Could either be one of the JSON templates or an RLE filename
	int padding;
};

struct parameters* parse_args (int argc, char** argv)
{
	if (argc == 2) error("USE: ./main path/to/template.cells n_iters", 20);
	struct parameters *the_args = (struct parameters*) malloc (sizeof(struct parameters));
	the_args->template_clue = *(argv+1);
	the_args->n_iters = atoi(*(argv+2));
	return the_args;
}

board* get_from_file (char* filename)
{
	board* out = NULL;
	// TODO:
	// Check filename extension (strchr('.')).
	// Return board according to extension.
	return out;
}

int main (int argc, char** argv)
{
	struct parameters *the_parameters = parse_args(argc, argv);
	board* my_board = get_from_file(the_parameters->template_clue);
	loop(my_board, the_parameters->n_iters);
	free(my_board);
	return 0;
}

