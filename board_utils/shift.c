#include "board_utils.h"

void shift(unsigned short board[21], unsigned short piece[4][21], int selected_rot, int left) {
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