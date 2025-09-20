#ifndef BOARD_UTILS_H
#define BOARD_UTILS_H


enum piece_t { PIECE_O, PIECE_T, PIECE_I, PIECE_S, PIECE_Z, PIECE_L, PIECE_J };

void init_game_board(unsigned short board[21]);
void init_piece_board(unsigned short piece[4][21], enum piece_t piece_type);
void add_piece_to_board(unsigned short board[21], unsigned short piece[4][21], int selected_rot);
int fall(unsigned short board[21], unsigned short piece[4][21], int selected_rot);
void shift(unsigned short board[21], unsigned short piece[4][21], int selected_rot, int left);
void clear_rows(unsigned short board[21]);

#endif