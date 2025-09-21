#include "board_utils.h"

u8
clear_rows (u16 board[BOARD_HEIGHT])
{
  i16 dst = BOARD_HEIGHT - 2;
  u8 cleared_count = 0;
  for (i16 src = BOARD_HEIGHT - 2; src >= 0; src--)
    {
      if ((board[src] & FILLED_ROW) != FILLED_ROW)
        {
          board[dst--] = board[src];
        }
    }

  while (dst >= 0)
    {
      board[dst--] = BOARD_WITH_WALLS;
      cleared_count++;
    }
  return cleared_count;
}
