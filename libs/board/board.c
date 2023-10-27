#include <stdlib.h>
#include <stdio.h>

#include "../error/error.h"
#include "board.h"


board* new_board (int n_rows, int n_columns)
{
	board* the_board = (board*) malloc(sizeof(board));
	the_board->n_rows = n_rows;
	the_board->n_columns = n_columns;
	the_board->cells = (int*) malloc(sizeof(int*) * the_board->n_rows * the_board->n_columns);
	int board_size = n_rows * n_columns;
	for (int i = 0 ; i < board_size ; i++)
	{
		*(the_board->cells+i) = EMPTY; // Reset all cells to empty
	}
	return the_board;
}

void show_board (board* the_board)
{
	for (int i = 0 ; i < the_board->n_rows ; i++)
	{
		for (int j = 0 ; j < the_board->n_columns ; j++)
			printf("%d ", *(the_board->cells+i*the_board->n_columns+j));
		printf("\n");
	}
	return;
}

board* set_cell (board* the_board, int target_column, int target_row, int to_be_placed)
{
	if (to_be_placed != EMPTY && to_be_placed != POPULATED) error("An illegal cell is trying to be placed\n", 1);
	*(the_board->cells+target_column+target_row*the_board->n_columns) = to_be_placed;
	return the_board;
}

board* copy_board (board* the_board)
{
	board* out_board = new_board(the_board->n_rows, the_board->n_columns);
	int board_size = the_board->n_rows * the_board->n_columns;
	for (int i = 0 ; i < board_size ; i++) *(out_board->cells+i) = *(the_board->cells+i);
	return out_board;
}

