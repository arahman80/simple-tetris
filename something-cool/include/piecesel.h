#ifndef PIECESEL_H
#define PIECESEL_H

#include "commac.h"

static const uchar O[4][2] = {{0b01100110, 0b00000000},
                              {0b01100110, 0b00000000},
                              {0b01100110, 0b00000000},
                              {0b01100110, 0b00000000}};

static const uchar i[4][2] = {{0b00001111, 0b00000000},
                              {0b00100010, 0b00100010},
                              {0b00000000, 0b11110000},
                              {0b01000100, 0b01000100}};

static const uchar T[4][2] = {{0b01001110, 0b00000000},
                              {0b01000110, 0b01000000},
                              {0b00001110, 0b01000000},
                              {0b01001100, 0b01000000}};

static const uchar S[4][2] = {{0b01101100, 0b00000000},
                              {0b01000110, 0b00100000},
                              {0b01101100, 0b00000000},
                              {0b10001100, 0b01000000}};

static const uchar Z[4][2] = {{0b11000110, 0b00000000},
                              {0b00100110, 0b01000000},
                              {0b11000110, 0b00000000},
                              {0b01001100, 0b10000000}};

static const uchar L[4][2] = {{0b10001110, 0b00000000},
                              {0b01100100, 0b01000000},
                              {0b11100010, 0b00000000},
                              {0b01000100, 0b11000000}};

static const uchar J[4][2] = {{0b00101110, 0b00000000},
                              {0b01000100, 0b01100000},
                              {0b11101000, 0b00000000},
                              {0b11000100, 0b01000000}};

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
