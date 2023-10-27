#ifndef LOGIC_H
#define LOGIC_H

#include <stdlib.h>
#include "../../board/board.h"
#include "../../error/error.h"

board* run_iteration (board* the_board);
int neighbors (board* the_board, int cell_idx);
int is_multiple_of (int a, int b);
int is_different (board* a, board* b);
board* loop (board* the_board, int iterations);

#endif
