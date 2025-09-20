#include "common_includes.h"

void test_clear_rows() {
    uint16_t board[21];
    init_game_board(board);

    // Fill one row completely
    board[19] = FILLED_ROW | 0b1000000000000001; // include walls

    clear_rows(board);

    int passes = 0, fails = 0;
    ASSERT_TRUE(board[19] == BOARD_WITH_WALLS, "Filled row should clear");
    printf("clear_rows: %d passed, %d failed\n\n", passes, fails);
}