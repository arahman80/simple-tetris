#include "board_utils.h"

bool
fall (u16 board[BOARD_HEIGHT], u16 piece[NUM_ROT][BOARD_HEIGHT],
      i16 selected_rot)
{
  for (i16 i = 0; i < BOARD_HEIGHT - 1; i++)
    {
      if (board[i + 1] & piece[selected_rot][i])
        {
          return false;
        }
    }

  for (i16 i = 0; i < NUM_ROT; i++)
    {
      for (i16 j = BOARD_HEIGHT - 1; j > 0; j--)
        {
          piece[i][j] = piece[i][j - 1];
        }

      piece[i][0] = 0b0000000000000000;
    }

  return true;
}