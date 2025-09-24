#ifndef GAME_H
#define GAME_H

#include "commac.h"

struct tetris_piece
{
  schar x;
  schar y;
  char piece_type;
  uchar selected_rotation;
  const uchar (*piece_map)[2];
};

void init_board (uint board[21]);
uchar is_valid (struct tetris_piece* piece, uint board[21], schar x_shift,
                schar y_shift, schar rotate, schar clockwise);
void ground_piece (struct tetris_piece* piece, uint board[21]);
void print_game (uint board[21], struct tetris_piece* piece);
void clear_rows (uint board[21]);

#endif
