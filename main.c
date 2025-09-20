#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "makers/makers.h"

typedef enum {
    O,
    T,
    I,
    S,
    Z,
    L,
    J
} piece_t;

void init_game_board(uint16_t board[21]) {
    for (int i = 0; i < 20; i++) {
        board[i] = 0b0010000000000100;
    }

    board[20] = 0b1111111111111111;
}

void piece_board_init(uint16_t piece[4][21], piece_t piece_type) {
    switch (piece_type) {
    case O:
        make_o(piece);
        break;
    case T:
        make_t(piece);
        break;
    case I:
        make_i(piece);
        break;
    case S:
        make_s(piece);
        break;
    case Z:
        make_z(piece);
        break;
    case L:
        make_l(piece);
        break;
    case J:
        make_j(piece);
        break;
    default:
        printf("Malformed piece type.");
        exit(1);
    }
}

void drop_piece(uint16_t piece[4][21], int selected_rot) {
    int piece_top = 0;
    int piece_bottom = 0;

    for (int board_i = 0; board_i < 21; board_i++) {
        if (piece[selected_rot][board_i]) {
            piece_top = board_i;
            break;
        }
    }

    for (int board_i = piece_top; board_i < 21; board_i++) {
        if (!piece[selected_rot][board_i]) {
            piece_bottom = board_i - 1;
            break;
        }
    }

    /* Future plans for this function: Go through the piece things. Bitwise & them shifted down by 1
       and if that returns true, that means there is a collision and THAT means that the piece cannot be
       moved further. Only check this for the SELECTED PIECE. */
}

int main(int argc, char** argv) {
    uint16_t board[21] = {0};
    uint16_t piece[4][21] = {0};
    /* Move legality detection: Just run logical & on potential move and make it if it is 0 :) */
    /* Bottom of piece board is made solid for easier detection */
    for (int i = 0; i < 4; i++)
        piece[i][20] = 0b1111111111111111;

    int selected_rot = 0; /* there will be 4 piece boards: you must select whichever you are using */

    printf("Hello world!\n");
    return 0;
}
