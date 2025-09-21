#include "board_utils.h"

int fall(unsigned int board[21], unsigned int piece[4][21], int selected_rot) {
    for (int i = 0; i < 20; i++) {
        if (board[i + 1] & piece[selected_rot][i]) {
            return 0;
        }
    }

    for (int i = 0; i < 4; i++) {
        for (int j = 20; j > 0; j--) {
            piece[i][j] = piece[i][j - 1];
        }

        piece[i][0] = 0b0000000000000000;
    }
    
    return 1;
}