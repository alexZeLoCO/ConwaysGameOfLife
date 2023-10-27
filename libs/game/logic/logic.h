#ifndef LOGIC_H
#define LOGIC_H

#include <stdlib.h>
#include "../../board/board.h"
#include "../../error/error.h"
#include "../../media/media.h"

board* run_iteration (board*);
int neighbors (board*, int);
int is_multiple_of (int, int);
int is_different (board*, board*);
board* loop (board*, int);
void show(board*, int, int);

#endif
