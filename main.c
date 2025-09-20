#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <memory.h>
#include "makers/makers.h"

#define BOARD_WITH_WALLS 0b0010000000000100
#define FILLED_ROW 0b0011111111111100

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
        board[i] = BOARD_WITH_WALLS;
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

void shift_board(uint16_t board[21], uint16_t scratch_buffer[21], bool is_game_board) {
    memcpy(scratch_buffer, board, 21 * sizeof(uint16_t));
    for (int i = 20; i > 0; i--) {
        scratch_buffer[i] = scratch_buffer[i - 1];
    }

    if (is_game_board) {
        scratch_buffer[0] = BOARD_WITH_WALLS;
        scratch_buffer[20] = 0b1111111111111111;
    } else {
        scratch_buffer[0] = 0b0000000000000000;
    }
}

bool test_intersection(uint16_t board[21], uint16_t piece_board[21]) {
    for (int i = 0; i < 21; i++) {
        if (board[i] & piece_board[i]) {
            return true;
        }
    }

    return false;
}

bool fall(uint16_t board[21], uint16_t piece[4][21], int selected_rot) {
    uint16_t scratch_piece[21] = {0};
    shift_board(piece[selected_rot], scratch_piece, false);
    if (test_intersection(board, scratch_piece)) {
        return false;
    }

    memcpy(piece[selected_rot], scratch_piece, 21 * sizeof(uint16_t));
    return true;
}

void clear_rows(uint16_t board[21]) {
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

int main(int argc, char** argv) {
    uint16_t board[21] = {0};
    uint16_t piece[4][21] = {0};
    /* Move legality detection: Just run logical & on potential move and make it if it is 0 :) */
    /* Bottom of board board is made solid for easier detection */

    int selected_rot = 0; /* there will be 4 piece boards: you must select whichever you are using */

    printf("Hello world!\n");
    return 0;
}
