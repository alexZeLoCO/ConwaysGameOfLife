#include <stdio.h>

#include "../libs/board/board.h"
#include "../libs/game/logic/logic.h"
#include "../libs/game/factory/factory.h"

struct parameters {
	int n_iters;
	char* template_clue; // Could either be one of the JSON templates or an RLE filename
} *the_parameters;

void parse_args (int argc, char** argv)
{
	if (argc != 3) error("ERR. Usage: ./main template iters", 20);
	the_parameters->n_iters = atoi(*(argv+2));
	the_parameters->template_clue = *(argv+1);
}

int main (int argc, char** argv)
{
	board* my_board;
	// my_board = get_from_template(get_template_from_name(the_parameters->template_clue));
	my_board = get_from_rle("unsynthesizable_still_life.rle");
	loop(my_board, the_parameters->n_iters);
	free(my_board);
	return 0;
}

