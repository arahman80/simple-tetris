#include <memory.h>
#include "board_utils.h"

bool fall(uint16_t board[21], uint16_t piece[4][21], int selected_rot) {
    for (int i = 0; i < 20; i++) {
        if (board[i + 1] & piece[selected_rot][i]) {
            return false;
        }
    }

    for (int i = 0; i < 4; i++) {
        for (int j = 20; j > 0; j--) {
            piece[i][j] = piece[i][j - 1];
        }

        piece[i][0] = 0b0000000000000000;
    }
    
    return true;
}