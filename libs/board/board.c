#include <stdlib.h>
#include <stdio.h>

#include "../error/error.h"
#include "board.h"


board* new_board (int padding, int n_rows, int n_columns)
{
	board* the_board = (board*) malloc(sizeof(board));
	the_board->padding = padding;
	the_board->n_rows = n_rows+padding*2;
	the_board->n_columns = n_columns+padding*2;
	the_board->cells = (int*) malloc(sizeof(int*) * the_board->n_rows * the_board->n_columns);
	int board_size = the_board->n_rows * the_board->n_columns;
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
	return set_cell_by_idx(
		the_board,
		target_column+(the_board->padding+target_row)*the_board->n_columns+the_board->padding,
		to_be_placed
	);
}

board* set_cell_by_idx (board* the_board, int idx, int to_be_placed)
{
	if (to_be_placed != EMPTY && to_be_placed != POPULATED) error("An illegal cell is trying to be placed\n", 1);
	*(the_board->cells+idx) = to_be_placed;
	return the_board;
}

board* copy_board (board* the_board)
{
	board* out_board = new_board(
		the_board->padding,
		the_board->n_rows-the_board->padding*2,
		the_board->n_columns-the_board->padding*2
	);
	int board_size = the_board->n_rows * the_board->n_columns;
	for (int i = 0 ; i < board_size ; i++) *(out_board->cells+i) = *(the_board->cells+i);
	return out_board;
}

board* copy_board_into (board* the_board, board* dst_board)
{
	dst_board = new_board(
		the_board->padding,
		the_board->n_rows-the_board->padding*2,
		the_board->n_columns-the_board->padding*2
	);
	int board_size = the_board->n_rows * the_board->n_columns;
	for (int i = 0 ; i < board_size ; i++) *(dst_board->cells+i) = *(the_board->cells+i);
	return dst_board;
}

