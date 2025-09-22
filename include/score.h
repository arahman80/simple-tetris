#ifndef SCORE_H
#define SCORE_H

#include "stdmac.h"

struct score_info
{
  U8 level;
  U16 score;
  U16 lines;
  U8 lines_this_level;
};

U0 update_score (struct score_info* info, U8 new_lines);

#endif
