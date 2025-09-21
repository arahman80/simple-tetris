#ifndef BOARD_UTILS_H
#define BOARD_UTILS_H

#include "stdmac.h"

enum piece_t
{
  PIECE_O,
  PIECE_T,
  PIECE_I,
  PIECE_S,
  PIECE_Z,
  PIECE_L,
  PIECE_J
};

void init_game_board (u16 board[BOARD_HEIGHT]);
void init_piece_board (u16 piece[NUM_ROT][BOARD_HEIGHT],
                       enum piece_t piece_type);
void add_piece_to_board (u16 board[BOARD_HEIGHT],
                         u16 piece[NUM_ROT][BOARD_HEIGHT], i16 selected_rot);
bool fall (u16 board[BOARD_HEIGHT], u16 piece[NUM_ROT][BOARD_HEIGHT],
           i16 selected_rot);
void shift (u16 board[BOARD_HEIGHT], u16 piece[NUM_ROT][BOARD_HEIGHT],
            i16 selected_rot, i16 left);
void clear_rows (u16 board[BOARD_HEIGHT]);

#endif