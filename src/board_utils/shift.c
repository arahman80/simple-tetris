#include "board_utils.h"

U0
shift (U16 board[BOARD_HEIGHT], U16 piece[NUM_ROT][BOARD_HEIGHT],
       I16 selected_rot, I16 left)
{
  for (I16 i = 0; i < BOARD_HEIGHT; i++)
    {
      if (board[i]
          & (left ? piece[selected_rot][i] << 1 : piece[selected_rot][i] >> 1))
        {
          return;
        }
    }

  for (I16 i = 0; i < BOARD_HEIGHT; i++)
    {
      if (left)
        {
          for (I16 j = 0; j < NUM_ROT; j++)
            {
              piece[j][i] <<= 1;
            }
        }
      else
        {
          for (I16 j = 0; j < NUM_ROT; j++)
            {
              piece[j][i] >>= 1;
            }
        }
    }
}