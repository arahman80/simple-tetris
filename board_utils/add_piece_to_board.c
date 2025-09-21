#include "board_utils.h"

void
add_piece_to_board (unsigned int board[21], unsigned int piece[4][21],
                    int selected_rot)
{
  for (int i = 0; i < 21; i++)
    {
      board[i] |= piece[selected_rot][i];
    }
}