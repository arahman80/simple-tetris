#ifndef BOARD_UTILS_H
#define BOARD_UTILS_H

#include "stdmac.h"

enum piece
{
  PIECE_O,
  PIECE_T,
  PIECE_I,
  PIECE_S,
  PIECE_Z,
  PIECE_L,
  PIECE_J
};

U0 init_game_board (U16 board[BOARD_HEIGHT]);
U0 init_piece_board (U16 piece[NUM_ROT][BOARD_HEIGHT], enum piece piece_type);
U0 add_piece_to_board (U16 board[BOARD_HEIGHT],
                       U16 piece[NUM_ROT][BOARD_HEIGHT], I16 selected_rot);
BOOL fall (U16 board[BOARD_HEIGHT], U16 piece[NUM_ROT][BOARD_HEIGHT],
           I16 selected_rot);
U0 shift (U16 board[BOARD_HEIGHT], U16 piece[NUM_ROT][BOARD_HEIGHT],
          I16 selected_rot, I16 left);
U8 clear_rows (U16 board[BOARD_HEIGHT]);
BOOL test_interference (U16 board_in[BOARD_HEIGHT],
                        U16 piece_in[NUM_ROT][BOARD_HEIGHT], I16 selected_rot);

#endif