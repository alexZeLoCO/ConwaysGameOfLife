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
	if (argc < 3) error("ERR. Usage: ./main template iters", 20);
	struct parameters *the_parameters = malloc (sizeof(struct parameters));
	the_parameters->n_iters = atoi(*(argv+2));
	the_parameters->template_clue = *(argv+1);
	the_parameters->padding = argc == 3 ? atoi(*(argv+3)) : 50;
	return the_parameters;
}

int main (int argc, char** argv)
{
	board* my_board;
	// my_board = get_from_template(get_template_from_name(the_parameters->template_clue));
	struct parameters *the_parameters = parse_args(argc, argv);
	my_board = get_from_rle(the_parameters->template_clue, the_parameters->padding);
	loop(my_board, the_parameters->n_iters);
	free(my_board);
	return 0;
}

