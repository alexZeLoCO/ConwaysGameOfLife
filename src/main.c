#include <stdio.h>

#include "../libs/board/board.h"
#include "../libs/game/logic/logic.h"

int main ()
{
	board* my_board = new_board(3, 3);
	*(my_board->cells+my_board->n_columns-1) = POPULATED;
	*(my_board->cells+my_board->n_columns*2) = POPULATED;
	*(my_board->cells) = POPULATED;
	loop(my_board, 0);
	return 0;
}

