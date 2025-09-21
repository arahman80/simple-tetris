#include "board_utils.h"

void
add_piece_to_board (U16 board[BOARD_HEIGHT], U16 piece[NUM_ROT][BOARD_HEIGHT],
                    I16 selected_rot)
{
  for (I16 i = 0; i < BOARD_HEIGHT; i++)
    {
      board[i] |= piece[selected_rot][i];
    }
}