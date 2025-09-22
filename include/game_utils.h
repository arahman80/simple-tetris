#ifndef GAME_UTILS_H
#define GAME_UTILS_H

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

struct game_state
{
  U16 board[BOARD_HEIGHT];
  U16 piece[NUM_ROT][BOARD_HEIGHT];
  enum piece piece_type;
  U16 selected_rot;
};

U0 init_game_board (struct game_state *state);
U0 init_piece_board (struct game_state *state);
U0 add_piece_to_board (struct game_state *state);
BOOL fall (struct game_state *state);
U0 shift (struct game_state *state, BOOL left);
I8 clear_rows (struct game_state *state);
BOOL test_interference (struct game_state *state);

#endif
