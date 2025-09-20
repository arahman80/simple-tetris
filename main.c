#include <complex.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "tests/test.h"
#include "board_utils/board_utils.h"

void print_bitboard(uint16_t board_in[21], uint16_t piece_in[21]) {
    for (int j = 0; j < 21; j++) {
        uint16_t board = board_in[j];
        uint16_t piece = piece_in[j];
        for (int i = 15; i >= 0; i--) { // MSB first
            uint8_t bit1 = (board >> i) & 1;
            uint8_t bit2 = (piece >> i) & 1;
            uint8_t bit = bit1 | bit2;
            printf("%c", bit ? '#' : ' ');
        }
        printf("\n"); // new row after each uint16_t
    }
}

int main(int argc, char** argv) {
    if (argc > 1) {
        if (!strcmp(argv[1], "--test")) {
            run_tests();
            return 0;
        }
    }

    uint16_t board[21] = {0};
    uint16_t piece[4][21] = {0};
    /* Move legality detection: Just run logical & on potential move and make it if it is 0 :) */
    /* Bottom of board board is made solid for easier detection */
    int selected_rot = 0; /* there will be 4 piece boards: you must select whichever you are using */
    init_game_board(board);
    init_piece_board(piece, PIECE_I);
    print_bitboard(board, piece[selected_rot]);
    fall(board, piece, selected_rot);
    print_bitboard(board, piece[selected_rot]);
    shift(board, piece, selected_rot, true);
    print_bitboard(board, piece[selected_rot]);


    printf("Hello world!\n");
    return 0;
}
