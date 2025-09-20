#ifndef BOARD_UTILS_H
#define BOARD_UTILS_H

#include <stdint.h>
#include <stdbool.h>

enum piece_t { PIECE_O, PIECE_T, PIECE_I, PIECE_S, PIECE_Z, PIECE_L, PIECE_J };

void init_game_board(uint16_t board[21]);
void init_piece_board(uint16_t piece[4][21], enum piece_t piece_type);
void add_piece_to_board(uint16_t board[21], uint16_t piece[4][21], int selected_rot);
bool fall(uint16_t board[21], uint16_t piece[4][21], int selected_rot);
void shift(uint16_t board[21], uint16_t piece[4][21], int selected_rot, bool left);
void clear_rows(uint16_t board[21]);

#endif