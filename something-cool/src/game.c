#include "game.h"
#ifdef debug
#include <stdio.h>
#endif

void
init_board (uint board[21])
{
  for (schar i = 0; i < 20; i++)
    board[i] = 0B0010000000000100;

  board[20] = 0B1111111111111111;
}

#ifdef debug
static void
print_binary_10 (uint x)
{
  for (int i = 9; i >= 0; i--)
  {
    putchar ((x & (1 << i)) ? '#' : '.');
  }
}
#endif

uchar
test_movement (struct tetris_piece* piece, uint board[21], schar x_shift,
               schar y_shift, schar rotate, schar clockwise)
{
  #ifdef debug
  printf ("\n=== test_movement ===\n");
  printf ("piece->x=%d, piece->y=%d, x_shift=%d, y_shift=%d, rotate=%d, "
          "clockwise=%d\n",
          piece->x, piece->y, x_shift, y_shift, rotate, clockwise);
  #endif

  uchar ROT = piece->selected_rotation;
  if (rotate)
  {
    ROT = (ROT + (clockwise ? 1 : 3)) % 4;
  }
  #ifdef debug
  printf ("rotation used=%d\n", ROT);
  #endif

  uchar up_seg = piece->piece_map[ROT][0];
  uchar low_seg = piece->piece_map[ROT][1];

  uchar seg1 = (up_seg & 0xF0) >> 4;
  uchar seg2 = up_seg & 0x0F;
  uchar seg3 = (low_seg & 0xF0) >> 4;
  uchar seg4 = low_seg & 0x0F;

  uint seg1_shifted = (uint) seg1 << (10 - 4 - (piece->x + x_shift));
  uint seg2_shifted = (uint) seg2 << (10 - 4 - (piece->x + x_shift));
  uint seg3_shifted = (uint) seg3 << (10 - 4 - (piece->x + x_shift));
  uint seg4_shifted = (uint) seg4 << (10 - 4 - (piece->x + x_shift));

  #ifdef debug
  printf ("row visualization:\n");
  printf ("row %2d: ", piece->y + 0 + y_shift);
  print_binary_10 (board[piece->y + 0 + y_shift] | seg1_shifted);
  printf ("\n");

  printf ("row %2d: ", piece->y + 1 + y_shift);
  print_binary_10 (board[piece->y + 1 + y_shift] | seg2_shifted);
  printf ("\n");

  printf ("row %2d: ", piece->y + 2 + y_shift);
  print_binary_10 (board[piece->y + 2 + y_shift] | seg3_shifted);
  printf ("\n");

  printf ("row %2d: ", piece->y + 3 + y_shift);
  print_binary_10 (board[piece->y + 3 + y_shift] | seg4_shifted);
  printf ("\n");
  #endif

  if (board[piece->y + 0 + y_shift] & seg1_shifted)
    return 1;
  if (board[piece->y + 1 + y_shift] & seg2_shifted)
    return 1;
  if (board[piece->y + 2 + y_shift] & seg3_shifted)
    return 1;
  if (board[piece->y + 3 + y_shift] & seg4_shifted)
    return 1;

  #ifdef debug
  printf ("no collision detected\n");
  #endif
  return 0;
}

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