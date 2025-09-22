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

struct score_info
{
  U16 level;
  U32 score;
  U16 lines;
  U16 lines_this_level;
};

struct tetris_bag
{
  U8 bag[7];
  U8 index;
  U8 rng_state;
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
struct score_info update_score (struct score_info info, U8 new_lines);
U8 next_piece (struct tetris_bag *tb);
U0 init_bag (struct tetris_bag *tb, U8 seed);
U8 xorshift8 (U8 *state);
U0 shuffle_bag (U8 bag[7], U8 *rng_state);

#endif
