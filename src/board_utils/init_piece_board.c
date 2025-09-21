#include "board_utils.h"
#include "makers.h"

typedef enum piece piece_t;

void
init_piece_board (U16 piece[NUM_ROT][BOARD_HEIGHT], piece_t piece_type)
{
  for (I16 i = 0; i < NUM_ROT; i++)
    {
      for (I16 j = 0; j < BOARD_HEIGHT; j++)
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