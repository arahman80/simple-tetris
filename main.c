#include <complex.h>
#include <stdint.h>
#include <ncurses.h>
#include <unistd.h>
#include <stdbool.h>
#include <time.h>
#include "board_utils/board_utils.h"

void print_bitboard(uint16_t board_in[21], uint16_t piece_in[21]) {
    for (int j = 0; j < 21; j++) {
        uint16_t board = board_in[j];
        uint16_t piece = piece_in[j];
        for (int i = 15; i >= 0; i--) {
            uint8_t bit1 = (board >> i) & 1;
            uint8_t bit2 = (piece >> i) & 1;
            uint8_t bit = bit1 | bit2;

            mvaddch(j, 15 - i, bit ? ACS_CKBOARD : ' ');
        }
    }

    refresh();
}

bool test_interference(uint16_t board_in[21], uint16_t piece_in[4][21], int selected_rot) {
    for (int i = 0; i < 21; i++) {
        if (board_in[i] & piece_in[selected_rot][i]) {
            return true;
        }
    }

    return false;
}

int main(void) {
    uint16_t board[21] = {0};
    uint16_t piece[4][21] = {0};
    int selected_rot = 0;
    init_game_board(board);
    init_piece_board(piece, PIECE_I);
    clock_t last_fall = time(NULL);
    
    initscr();
    noecho();
    cbreak();
    curs_set(0);
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);

    int ch;
    while ((ch = getch()) != 'q') {
        time_t now = time(NULL);
        double elapsed = difftime(now, last_fall);

        switch (ch) {
        case KEY_UP:
            if (!test_interference(board, piece, (selected_rot + 1) % 4)) {
                selected_rot = (selected_rot + 1) % 4;
            }
            break;
        case KEY_DOWN:
            if (!test_interference(board, piece, (selected_rot - 1) % 4)) {
                selected_rot = (selected_rot - 1) % 4;
            }
            break;
        case KEY_LEFT:
            shift(board, piece, selected_rot, true);
            break;
        case KEY_RIGHT:
            shift(board, piece, selected_rot, false);
            break;
        case ' ':
            fall(board, piece, selected_rot);
            continue;
            break;
        }

        if (elapsed >= 0.25) {
            last_fall = time(NULL);
            if (!fall(board, piece, selected_rot)) {
                add_piece_to_board(board, piece, selected_rot);
                init_piece_board(piece, PIECE_I);
                selected_rot = 0;

                if (test_interference(board, piece, selected_rot)) {
                    endwin();
                    return 0;
                }
            }
        }

        clear_rows(board);
        erase();
        print_bitboard(board, piece[selected_rot]);

        usleep(50000);
    }

    endwin();
    return 0;
}