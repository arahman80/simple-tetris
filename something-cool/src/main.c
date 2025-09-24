#include "commac.h"
#include "game.h"
#include "piecesel.h"
#include <stdio.h>

int
main (void)
{
  uint board[21] = {0};
  init_board (board);

  struct tetris_bag bag = {0};
  struct tetris_piece piece = {0};
  uchar seed = 123;
  init_bag (&bag, seed);
  select_piece (next_piece (&bag), &piece);

  print_game (board, &piece);

  uchar c;
  while (1)
  {
    c = getchar ();
    switch (c)
    {
    case 'w':
      rotate_srs (&piece, board, 1);
      break;

    case 's':
      rotate_srs (&piece, board, 0);
      break;

    case 'a':
      if (is_valid (&piece, board, -1, 0, 0, 0))
        piece.x -= 1;
      break;

    case 'd':
      if (is_valid (&piece, board, 1, 0, 0, 0))
        piece.x += 1;
      break;

    case ' ': // impl hard drop
      break;

    case 'q':
      return 0;

    default:
      break;
    }

    if (is_valid (&piece, board, 0, 1, 0, 0))
      piece.y += 1;
    else
    {
      ground_piece (&piece, board);
      clear_rows (board);
      select_piece (next_piece (&bag), &piece);
      if (!is_valid (&piece, board, 0, 0, 0, 0))
      {
        printf ("You Lost!\n");
        return 0;
      }
    }

    print_game (board, &piece);
  }

  return 0;
}
