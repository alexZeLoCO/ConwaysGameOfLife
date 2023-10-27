#include <stdio.h>

#include "../libs/board/board.h"
#include "../libs/game/logic/logic.h"
#include "../libs/game/factory/factory.h"

template parse_args (int argc, char** argv)
{
	if (argc == 1) return BEACON;
	else return get_template_from_name(*(argv+1));
}

int main (int argc, char** argv)
{
	board* my_board = get_from_template(parse_args(argc, argv));
	loop(my_board, atoi(*(argv+2)));
	free(my_board);
	return 0;
}

