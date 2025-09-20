#include "board_utils.h"

#define BOARD_WITH_WALLS 0b0010000000000100

void init_game_board(unsigned short board[21]) {
    for (int i = 0; i < 20; i++) {
        board[i] = BOARD_WITH_WALLS;
    }

    board[20] = 0b1111111111111111;
}