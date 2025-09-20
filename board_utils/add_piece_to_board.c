#include "board_utils.h"


void add_piece_to_board(uint16_t board[21], uint16_t piece[4][21], int selected_rot) {
    for (int i = 0; i < 21; i++) {
        board[i] |= piece[selected_rot][i];
    }
}