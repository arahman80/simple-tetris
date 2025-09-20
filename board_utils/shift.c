#include "board_utils.h"

void shift(uint16_t board[21], uint16_t piece[4][21], int selected_rot, bool left) {
    for (int i = 0; i < 21; i++) {
        if (board[i] & (left ? piece[selected_rot][i] << 1 :
                               piece[selected_rot][i] >> 1)) {
            return;
        }
    }

    for (int i = 0; i < 21; i++) {
        if (left) {
            for (int j = 0; j < 4; j++) {
                piece[j][i] <<= 1;
            }
        } else {
            for (int j = 0; j < 4; j++) {
                piece[j][i] >>= 1;
            }
        }
    }
}