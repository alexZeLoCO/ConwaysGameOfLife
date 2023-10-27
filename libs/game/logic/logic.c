#include <stdio.h>

#include "logic.h"

board* run_iteration (board* the_board)
{
	board* the_new_board = copy_board(the_board);
	int board_size = the_board->n_rows * the_board->n_columns;
	for (int i = 0 ; i < board_size ; i++)
	{
		int number_of_neighbors = neighbors(the_board, i);

		// Any cell with other than 2 or 3 neighbors dies
		if (number_of_neighbors != 2 && number_of_neighbors != 3) *(the_new_board->cells+i) = EMPTY;

		// Any dead cell with 3 neighbors becomes a live cell
		if (*(the_board->cells+i) == EMPTY && number_of_neighbors == 3) *(the_new_board->cells+i) = POPULATED;
	}
	return the_new_board;
}

int neighbors (board* the_board, int cell_idx)
{
	int neighbor_count = 0;

	// Possible cells (note that not all of these may be counted)
	int 
		above_cell_idx = cell_idx - the_board->n_columns,
		below_cell_idx = cell_idx + the_board->n_columns,
		right_cell_idx = cell_idx + 1,
		left_cell_idx  = cell_idx - 1,
		above_left_cell_idx = above_cell_idx - 1,
		above_right_cell_idx = above_cell_idx + 1,
		below_left_cell_idx = below_cell_idx - 1,
		below_right_cell_idx = below_cell_idx + 1;

	// We check if the previous cells are legal or not
	// SUGGESTION: Do not touch this unless strictly necessary
	int 
		exists_left_cell  =
			left_cell_idx >= 0 &&
			!is_multiple_of(cell_idx, the_board->n_columns),
		exists_right_cell =
			right_cell_idx < the_board->n_columns*the_board->n_rows &&
			!is_multiple_of(cell_idx+1, the_board->n_columns),
		exists_above_cell =
			above_cell_idx >= 0,
		exists_below_cell =
			below_cell_idx < the_board->n_columns * the_board->n_rows;

	// printf("Existing neighbors of %d:\n\tLeft:%d\tRight:%d\n\tAbove:%d\tBelow:%d\n", cell_idx, exists_left_cell, exists_right_cell, exists_above_cell, exists_below_cell);

	if (exists_above_cell) {		// Check if above cell exists
		neighbor_count += *(the_board->cells+above_cell_idx); 
		if (exists_left_cell) neighbor_count += *(the_board->cells+above_left_cell_idx);  // Check if left cell exists (top-left)
		if (exists_right_cell) neighbor_count += *(the_board->cells+above_right_cell_idx); // Check if right cell exists (top-right)
	}
	if (exists_below_cell) { // Check if below cell exists
		neighbor_count += *(the_board->cells+below_cell_idx); 
		if (exists_left_cell) neighbor_count += *(the_board->cells+below_left_cell_idx); // Check if left cell exists (below-left)
		if (exists_right_cell) neighbor_count += *(the_board->cells+below_right_cell_idx); // Check if right cell exists (below-right)
	} 
	if (exists_left_cell) neighbor_count += *(the_board->cells+left_cell_idx); // Check if left cell exists (center-left)
	if (exists_right_cell) neighbor_count += *(the_board->cells+right_cell_idx); // Check if right cell exists (center-right)

	/*
	printf(
		"Neighbors of %d (cellIdx(value)) (%d(%d), %d(%d), %d(%d), %d(%d), (self), %d(%d), %d(%d), %d(%d), %d(%d)): %d\n",
		cell_idx,
		above_left_cell_idx,
		*(the_board->cells+above_left_cell_idx),
		above_cell_idx,
		*(the_board->cells+above_cell_idx),
		above_right_cell_idx,
		*(the_board->cells+above_right_cell_idx),
		left_cell_idx,
		*(the_board->cells+left_cell_idx),
		right_cell_idx,
		*(the_board->cells+right_cell_idx),
		below_left_cell_idx,
		*(the_board->cells+below_left_cell_idx),
		below_cell_idx,
		*(the_board->cells+below_cell_idx),
		below_right_cell_idx,
		*(the_board->cells+below_right_cell_idx),
		neighbor_count
	);
	*/

	return neighbor_count;
}

int is_multiple_of (int a, int b)
{
	if (b == 0) return 1 == 0; // Not multiple
	return a % b == 0;
}

int is_different (board* a, board* b)
{
	if (a->n_columns != b->n_columns || a->n_rows != b->n_rows) error("Boards cannot be compared, sizes do not match", 2);
	int board_size = a->n_columns * a->n_rows;
	for (int i = 0 ; i < board_size ; i++)
		if (*(a->cells+i) != *(b->cells+i)) return 1;
	return 0;
}

board* loop (board* the_board, int iterations)
{
	board* prev_board;
	int current_iteration = 1;
	do {
		show(the_board, current_iteration, iterations);
		prev_board = copy_board_into(the_board, prev_board);
		the_board = run_iteration(prev_board);	
	} while (current_iteration++ != iterations && is_different(the_board, prev_board));
	show(the_board, current_iteration, iterations);
	free(prev_board);
	return the_board;
}

void show (board* the_board, int current_iteration, int iterations)
{
	printf("\n=== ITERATION %d/%d ===\n", current_iteration, iterations);
	show_board(the_board);
	char* buf = (char*) malloc (sizeof(char) * 7+4);
	sprintf(buf, "output/iter_%d.ppm", current_iteration);
	create_bmp(the_board, buf);
}

