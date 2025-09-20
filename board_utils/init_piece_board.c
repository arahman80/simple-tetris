#include <stdio.h>
#include <stdlib.h>
#include "board_utils.h"
#include "../makers/makers.h"

#define piece_t enum piece_t

void init_piece_board(uint16_t piece[4][21], piece_t piece_type) {
    switch (piece_type) {
    case PIECE_O:
        make_o(piece);
        break;
    case PIECE_T:
        make_t(piece);
        break;
    case PIECE_I:
        make_i(piece);
        break;
    case PIECE_S:
        make_s(piece);
        break;
    case PIECE_Z:
        make_z(piece);
        break;
    case PIECE_L:
        make_l(piece);
        break;
    case PIECE_J:
        make_j(piece);
        break;
    default:
        printf("Malformed piece type.");
        exit(1);
    }
}