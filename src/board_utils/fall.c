#include "board_utils.h"

BOOL
fall (U16 board[BOARD_HEIGHT], U16 piece[NUM_ROT][BOARD_HEIGHT],
      I16 selected_rot)
{
  for (I16 i = 0; i < BOARD_HEIGHT - 1; i++)
    {
      if (board[i + 1] & piece[selected_rot][i])
        {
          return FALSE;
        }
    }

  for (I16 i = 0; i < NUM_ROT; i++)
    {
      for (I16 j = BOARD_HEIGHT - 1; j > 0; j--)
        {
          piece[i][j] = piece[i][j - 1];
        }

      piece[i][0] = 0b0000000000000000;
    }

  return TRUE;
}