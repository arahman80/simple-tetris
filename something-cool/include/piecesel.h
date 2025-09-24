#ifndef PIECESEL_H
#define PIECESEL_H

#include "commac.h"

static const uchar O[4][2] = {{0B01100110, 0B00000000},
                              {0B01100110, 0B00000000},
                              {0B01100110, 0B00000000},
                              {0B01100110, 0B00000000}};

static const uchar i[4][2] = {{0B00001111, 0B00000000},
                              {0B00100010, 0B00100010},
                              {0B00000000, 0B11110000},
                              {0B01000100, 0B01000100}};

static const uchar T[4][2] = {{0B01001110, 0B00000000},
                              {0B01000110, 0B01000000},
                              {0B00001110, 0B01000000},
                              {0B01001100, 0B01000000}};

static const uchar S[4][2] = {{0B01101100, 0B00000000},
                              {0B01000110, 0B00100000},
                              {0B01101100, 0B00000000},
                              {0B10001100, 0B01000000}};

static const uchar Z[4][2] = {{0B11000110, 0B00000000},
                              {0B00100110, 0B01000000},
                              {0B11000110, 0B00000000},
                              {0B01001100, 0B10000000}};

static const uchar L[4][2] = {{0B10001110, 0B00000000},
                              {0B01100100, 0B01000000},
                              {0B11100010, 0B00000000},
                              {0B01000100, 0B11000000}};

static const uchar J[4][2] = {{0B00101110, 0B00000000},
                              {0B01000100, 0B01100000},
                              {0B11101000, 0B00000000},
                              {0B11000100, 0B01000000}};

struct tetris_bag
{
  uchar bag[7];
  uchar index;
  uchar rng_state;
};

struct tetris_piece;

void init_bag (struct tetris_bag* bag, uchar seed);
uchar xorshift8 (uchar* state);
void shuffle_bag (uchar bag[7], uchar* random_state);
uchar next_piece (struct tetris_bag* bag);
void select_piece (uchar selector, struct tetris_piece* piece);

#endif
