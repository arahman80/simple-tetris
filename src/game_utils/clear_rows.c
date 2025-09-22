#include "game_utils.h"

typedef struct game_state game_state_t;

inline static I8 compact_board (game_state_t* state);
inline static I8 fill_top_rows (game_state_t* state, I8 dst);

I8
clear_rows (game_state_t* state)
{
  I8 dst = BOARD_HEIGHT - 2;

  dst = compact_board (state);

  I8 cleared_count = fill_top_rows (state, dst);

  return cleared_count;
}

inline static I8
compact_board (game_state_t* state)
{
  I8 dst = BOARD_HEIGHT - 2;

  for (I8 src = BOARD_HEIGHT - 2; src >= 0; src--)
  {
    if ((state->board[src] & (unsigned) FILLED_ROW) != (unsigned) FILLED_ROW)
    {
      state->board[dst--] = state->board[src];
    }
  }

  return dst;
}

inline static I8
fill_top_rows (game_state_t* state, I8 dst)
{
  I8 cleared_count = 0;

  while (dst >= 0)
  {
    state->board[dst--] = BOARD_WITH_WALLS;
    cleared_count++;
  }

  return cleared_count;
}
