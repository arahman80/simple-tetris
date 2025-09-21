#include "board_utils.h"

void
init_game_board (u16 board[BOARD_HEIGHT])
{
  for (i16 i = 0; i < BOARD_HEIGHT - 1; i++)
    {
      board[i] = BOARD_WITH_WALLS;
    }

  board[BOARD_HEIGHT - 1] = 0b1111111111111111;
}