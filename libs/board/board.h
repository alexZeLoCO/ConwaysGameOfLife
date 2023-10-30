#ifndef BOARD_H
#define BOARD_H

struct struct_board
{
	int padding;
	int* cells;
	int n_rows;
	int n_columns;
};

#define board struct struct_board

#define EMPTY 0
#define POPULATED 1


board* new_board (int padding, int n_rows, int n_columns);
void show_board (board* the_board);
board* set_cell (board* the_board, int target_column, int target_row, int to_be_placed);
board* set_cell_by_idx (board*, int, int);
board* copy_board(board* the_board);
board* copy_board_into(board* the_board, board* dst_board);

#endif
