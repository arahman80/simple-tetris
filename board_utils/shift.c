#include "board_utils.h"

void
shift (u16 board[BOARD_HEIGHT], u16 piece[NUM_ROT][BOARD_HEIGHT],
       i16 selected_rot, i16 left)
{
  for (i16 i = 0; i < BOARD_HEIGHT; i++)
    {
      if (board[i]
          & (left ? piece[selected_rot][i] << 1 : piece[selected_rot][i] >> 1))
        {
          return;
        }
    }

  for (i16 i = 0; i < BOARD_HEIGHT; i++)
    {
      if (left)
        {
          for (i16 j = 0; j < NUM_ROT; j++)
            {
              piece[j][i] <<= 1;
            }
        }
      else
        {
          for (i16 j = 0; j < NUM_ROT; j++)
            {
              piece[j][i] >>= 1;
            }
        }
    }
}