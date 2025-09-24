#include "piecesel.h"
#include "game.h"

void
init_bag (struct tetris_bag* bag, uchar seed)
{
  bag->rng_state = seed;
  bag->index = 7;
}

void
ground_piece (struct tetris_piece* piece, uint board[21])
{
  uchar ROT = piece->selected_rotation;

  uchar up_seg = piece->piece_map[ROT][0];
  uchar low_seg = piece->piece_map[ROT][1];

  uchar seg1 = (up_seg & 0xF0) >> 4;
  uchar seg2 = up_seg & 0x0F;
  uchar seg3 = (low_seg & 0xF0) >> 4;
  uchar seg4 = low_seg & 0x0F;

  uint seg1_shifted = (uint) seg1 << (10 - 4 - piece->x);
  uint seg2_shifted = (uint) seg2 << (10 - 4 - piece->x);
  uint seg3_shifted = (uint) seg3 << (10 - 4 - piece->x);
  uint seg4_shifted = (uint) seg4 << (10 - 4 - piece->x);

  board[piece->y + 0] |= seg1_shifted;
  board[piece->y + 1] |= seg2_shifted;
  board[piece->y + 2] |= seg3_shifted;
  board[piece->y + 3] |= seg4_shifted;
}

uchar
xorshift8 (uchar* state)
{
  uchar x = *state;
  x ^= x << 3;
  x ^= x >> 5;
  x ^= x << 2;
  *state = x;
  return x;
}

void
shuffle_bag (uchar bag[7], uchar* random_state)
{
  for (schar i = 0; i < 7; i++)
    bag[i] = i;

  for (schar i = 0; i < 7; i++)
  {
    uchar j = xorshift8 (random_state) % 7;
    uchar tmp = bag[i];
    bag[i] = bag[j];
    bag[j] = tmp;
  }
}

uchar
next_piece (struct tetris_bag* bag)
{
  if (bag->index >= 7)
  {
    shuffle_bag (bag->bag, &bag->rng_state);
    bag->index = 0;
  }

  return bag->bag[bag->index++];
}

void
select_piece (uchar selector, struct tetris_piece* piece)
{
  piece->x = 0;
  piece->y = 0;

  switch (selector)
  {
  case 0:
    piece->piece_map = O;
    piece->piece_type = 'O';
    break;
  case 1:
    piece->piece_map = i;
    piece->piece_type = 'i';
    break;
  case 2:
    piece->piece_map = T;
    piece->piece_type = 'T';
    break;
  case 3:
    piece->piece_map = S;
    piece->piece_type = 'S';
    break;
  case 4:
    piece->piece_map = Z;
    piece->piece_type = 'Z';
    break;
  case 5:
    piece->piece_map = L;
    piece->piece_type = 'L';
    break;
  case 6:
    piece->piece_map = J;
    piece->piece_type = 'J';
    break;
  default:
    break;
  }
}