#ifndef PIECE_SELECT_H
#define PIECE_SELECT_H

#include "stdmac.h"

struct tetris_bag
{
  U8 bag[7];
  U8 index;
  U8 rng_state;
};

U8 next_piece (struct tetris_bag* tb);
U0 init_bag (struct tetris_bag* tb, U8 seed);
U8 xorshift8 (U8* state);
U0 shuffle_bag (U8 bag[7], U8* random_state);

#endif
