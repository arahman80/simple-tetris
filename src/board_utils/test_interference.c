#include "board_utils.h"

BOOL
test_interference (U16 board_in[BOARD_HEIGHT],
                   U16 piece_in[NUM_ROT][BOARD_HEIGHT], I16 selected_rot)
{
  for (I16 i = 0; i < BOARD_HEIGHT; i++)
    {
      if (board_in[i] & piece_in[selected_rot][i])
        {
          return TRUE;
        }
    }

  return FALSE;
}