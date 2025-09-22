#include "board_utils.h"

typedef struct score_info score_info_t;

score_info_t
update_score (score_info_t info, U8 new_lines)
{
  switch (new_lines)
    {
    case 1:
      info.score += 100 * info.level;
    case 2:
      info.score += 300 * info.level;
    case 3:
      info.score += 500 * info.level;
    case 4:
      info.score += 800 * info.level;
    }

  if (info.lines_this_level >= info.level * 10)
    {
      info.level += 1;
      info.lines_this_level -= info.level * 10;
    }

  info.lines += new_lines;

  return info;
}
