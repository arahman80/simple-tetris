#include "game_utils.h"
#include "stdmac.h"

typedef struct game_state game_state_t;

static BOOL check_shift (game_state_t* state, I8 dist);
static U0 perform_shift (game_state_t* state, I8 dist);
static U0 copy_rows (game_state_t* state, I8 dist);
static U0 clear_vacated_rows (game_state_t* state, I8 dist);

BOOL
v_shift (game_state_t* state, I8 dist, BOOL forced)
{
  if (dist == 0)
  {
    return TRUE;
  }

  if (!forced && !check_shift (state, dist))
  {
    return FALSE;
  }

  perform_shift (state, dist);
  return TRUE;
}

static BOOL
check_shift (game_state_t* state, I8 dist)
{
  I8 start = (dist > 0) ? 0 : -dist;
  I8 end = (dist > 0) ? BOARD_HEIGHT - dist : BOARD_HEIGHT;

  for (I8 i = start; i < end; i++)
  {
    I8 board_row = i + dist;
    if (state->board[board_row] & state->piece[state->selected_rot][i])
    {
      return FALSE;
    }
  }

  return TRUE;
}

static U0
perform_shift (game_state_t* state, I8 dist)
{
  copy_rows (state, dist);
  clear_vacated_rows (state, dist);
}

static U0
determine_loop_bounds (I8* start, I8* end, I8* step, I8 dist)
{
  if (dist > 0)
  {
    *start = BOARD_HEIGHT - 1;
    *end = dist - 1;
    *step = -1;
  }
  else
  {
    *start = 0;
    *end = BOARD_HEIGHT + dist;
    *step = 1;
  }
}

static U0
copy_rows (game_state_t* state, I8 dist)
{
  I8 start, end, step;
  determine_loop_bounds (&start, &end, &step, dist);
  for (I8 r = 0; r < NUM_ROT; r++)
  {
    for (I8 j = start; j != end; j += step)
    {
      state->piece[r][j] = state->piece[r][j - dist];
    }
  }
}

static U0
clear_vacated_rows (game_state_t* state, I8 dist)
{
  I8 low_j_bound = (dist > 0) ? 0 : BOARD_HEIGHT + dist;
  I8 high_j_bound = (dist > 0) ? dist : BOARD_HEIGHT;

  for (I8 r = 0; r < NUM_ROT; r++)
  {
    for (I8 j = low_j_bound; j < high_j_bound; j++)
    {
      state->piece[r][j] = 0x0;
    }
  }
}
