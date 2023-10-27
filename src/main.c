#include <stdio.h>

#include "../libs/board/board.h"
#include "../libs/game/logic/logic.h"
#include "../libs/game/factory/factory.h"

int main ()
{
	board* my_board = get_from_template(BLINKER);
	loop(my_board, 10);
	return 0;
}

