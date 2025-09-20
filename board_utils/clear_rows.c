#include "board_utils.h"

#define BOARD_WITH_WALLS 0b0010000000000100
#define FILLED_ROW 0b0011111111111100

void clear_rows(unsigned short board[21]) {
    int dst = 19;
    for (int src = 19; src >= 0; src--) {
        if ((board[src] & FILLED_ROW) != FILLED_ROW) {
            board[dst--] = board[src];
        }
    }

    while (dst >= 0) {
        board[dst--] = BOARD_WITH_WALLS;
    }
}