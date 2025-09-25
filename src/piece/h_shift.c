#include "game_utils.h"
#include "stdmac.h"

typedef struct game_state game_state_t;

inline static BOOL check_shift (game_state_t* state, I8 dist, BOOL left);
inline static U0 shift_left (game_state_t* state, I8 dist, I8 i);
inline static U0 shift_right (game_state_t* state, I8 dist, I8 i);
inline static U0 perform_shift (game_state_t* state, I8 dist, BOOL left);

BOOL
h_shift (game_state_t* state, I8 dist, BOOL left, BOOL forced)
{
  if (!forced)
  {
    if (!check_shift (state, dist, left))
    {
      return FALSE;
    }
  }

  perform_shift (state, dist, left);

  return TRUE;
}

inline static BOOL
check_shift (game_state_t* state, I8 dist, BOOL left)
{
  for (I8 i = 0; i < BOARD_HEIGHT; i++)
  {
    if (state->board[i] &
        (left ? state->piece[state->selected_rot][i] << (unsigned) dist
              : state->piece[state->selected_rot][i] >> (unsigned) dist))
    {
      return FALSE;
    }
  }

  return TRUE;
}

inline static U0
shift_left (game_state_t* state, I8 dist, I8 i)
{
  for (I8 j = 0; j < NUM_ROT; j++)
  {
    state->piece[j][i] <<= (unsigned) dist;
  }
}

inline static U0
shift_right (game_state_t* state, I8 dist, I8 i)
{
  for (I8 j = 0; j < NUM_ROT; j++)
  {
    state->piece[j][i] >>= (unsigned) dist;
  }
}

inline static U0
perform_shift (game_state_t* state, I8 dist, BOOL left)
{
  U0 (*shift_func) (game_state_t*, I8, I8) = left ? shift_left : shift_right;
  for (I8 i = 0; i < BOARD_HEIGHT; i++)
  {
    shift_func (state, dist, i);
  }
}
