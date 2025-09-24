#include "game.h"
#include <stdio.h>

void
print_game (uint board[21], struct tetris_piece* piece)
{
  uint tmp[21];
  for (schar i = 0; i < 21; i++)
    tmp[i] = board[i];

  uchar rot = piece->selected_rotation;
  uchar up_seg = piece->piece_map[rot][0];
  uchar low_seg = piece->piece_map[rot][1];

  uchar seg1 = (up_seg & 0xF0) >> 4;
  uchar seg2 = (up_seg & 0x0F);
  uchar seg3 = (low_seg & 0xF0) >> 4;
  uchar seg4 = (low_seg & 0x0F);

  tmp[piece->y + 0] |= (uint) seg1 << (10 - 4 - piece->x);
  tmp[piece->y + 1] |= (uint) seg2 << (10 - 4 - piece->x);
  tmp[piece->y + 2] |= (uint) seg3 << (10 - 4 - piece->x);
  tmp[piece->y + 3] |= (uint) seg4 << (10 - 4 - piece->x);

  for (schar y = 0; y < 21; y++)
  {
    for (schar x = 15; x >= 0; x--)
      if (tmp[y] & (1 << x))
        printf ("#");
      else
        printf (" ");
    printf ("\n");
  }
}