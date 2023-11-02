#include <stdio.h>

#include "../libs/board/board.h"
#include "../libs/game/logic/logic.h"
#include "../libs/game/factory/factory.h"

struct args 
{
	char* template_hint;
	int n_iters;
};

struct args* parse_args (int argc, char** argv)
{
	if (argc == 2) error("USE: ./main path/to/template.cells n_iters", 20);
	struct args *the_args = (struct args*) malloc (sizeof(struct args));
	the_args->template_hint = *(argv+1);
	the_args->n_iters = atoi(*(argv+2));
	return the_args;
}

int main (int argc, char** argv)
{
	struct args* the_args = parse_args(argc, argv);
	board* my_board = get_from_plaintext(the_args->template_hint);
	loop(my_board, the_args->n_iters);
	free(my_board);
	return 0;
}

