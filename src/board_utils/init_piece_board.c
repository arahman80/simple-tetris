#include "makers.h"
#include "board_utils.h"

#define piece_t enum piece_t

void
init_piece_board (u16 piece[NUM_ROT][BOARD_HEIGHT], piece_t piece_type)
{
  for (i16 i = 0; i < NUM_ROT; i++)
    {
      for (i16 j = 0; j < BOARD_HEIGHT; j++)
        {
          piece[i][j] = 0b0000000000000000;
        }
    }

  switch (piece_type)
    {
    case PIECE_O:
      make_o (piece);
      break;
    case PIECE_T:
      make_t (piece);
      break;
    case PIECE_I:
      make_i (piece);
      break;
    case PIECE_S:
      make_s (piece);
      break;
    case PIECE_Z:
      make_z (piece);
      break;
    case PIECE_L:
      make_l (piece);
      break;
    case PIECE_J:
      make_j (piece);
      break;
    default:
      /* Malformed piece: do absolutely nothing */
      break;
    }
}