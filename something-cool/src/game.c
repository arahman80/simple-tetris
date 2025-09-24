#include "game.h"
#ifdef debug
#include <stdio.h>
#endif

void
init_board (uint board[21])
{
  for (schar i = 0; i < 20; i++)
    board[i] = 0b0010000000000100;

  board[20] = 0b1111111111111111;
}

#ifdef debug
static void
print_binary_10 (uint x)
{
  for (int i = 9; i >= 0; i--)
    putchar ((x & (1 << i)) ? '#' : '.');
}
#endif

uchar
is_valid (struct tetris_piece* piece, uint board[21], schar x_shift,
          schar y_shift, schar rotate, schar clockwise)
{
#ifdef debug
  printf ("\n=== is_valid ===\n");
  printf ("piece->x=%d, piece->y=%d, x_shift=%d, y_shift=%d, rotate=%d, "
          "clockwise=%d\n",
          piece->x, piece->y, x_shift, y_shift, rotate, clockwise);
#endif

  uchar ROT = piece->selected_rotation;
  if (rotate)
    ROT = (ROT + (clockwise ? 1 : 3)) % 4;

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
    return 0;
  if (board[piece->y + 1 + y_shift] & seg2_shifted)
    return 0;
  if (board[piece->y + 2 + y_shift] & seg3_shifted)
    return 0;
  if (board[piece->y + 3 + y_shift] & seg4_shifted)
    return 0;

#ifdef debug
  printf ("no collision detected\n");
#endif
  return 1;
}

void
clear_rows (uint board[21])
{
  schar dst = 21 - 2;

  for (schar src = 21 - 2; src >= 0; src--)
    if ((board[src] & (unsigned) 0b1111111111111111) !=
        (unsigned) 0b1111111111111111)
      board[dst--] = board[src];

  while (dst >= 0)
    board[dst--] = 0b0010000000000100;
}