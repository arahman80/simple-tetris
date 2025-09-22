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
  enum piece next_piece_type;
  enum piece held_piece_type;
  U16 selected_rot;
};

U0 init_game_board (struct game_state* state);
U0 init_piece_board (struct game_state* state);
U0 add_piece_to_board (struct game_state* state);
BOOL v_shift (struct game_state* state, I8 dist, BOOL forced);
BOOL h_shift (struct game_state* state, I8 dist, BOOL left, BOOL forced);
I8 clear_rows (struct game_state* state);
BOOL test_interference (struct game_state* state);
U0 do_rotation (struct game_state* state, BOOL clockwise, BOOL is_I);

#endif
