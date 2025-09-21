#include "board_utils.h"

void
add_piece_to_board (u16 board[BOARD_HEIGHT], u16 piece[NUM_ROT][BOARD_HEIGHT],
                    i16 selected_rot)
{
  for (i16 i = 0; i < BOARD_HEIGHT; i++)
    {
      board[i] |= piece[selected_rot][i];
    }
}