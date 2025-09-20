#include "board_utils.h"

void shift(uint16_t board[21], uint16_t piece[4][21], int selected_rot, bool left) {
    int8_t shift_amount = left ? 1 : -1;

    for (int i = 0; i < 21; i++) {
        if (board[i] & piece[selected_rot][i] << shift_amount) {
            return;
        }
    }

    for (int i = 0; i < 21; i++) {
        piece[selected_rot][i] <<= shift_amount;
    }
}