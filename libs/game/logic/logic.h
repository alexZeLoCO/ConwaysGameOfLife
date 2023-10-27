#ifndef LOGIC_H
#define LOGIC_H

#include "../../board/board.h"

board* run_iteration (board* the_board);
int neighbors (board* the_board, int cell_idx);
int is_multiple_of (int a, int b);
int is_different (board* a, board* b);
board* loop (board* the_board, int iterations);

#endif
