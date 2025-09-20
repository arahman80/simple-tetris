#!/bin/bash

if [ ! -d "build" ]; then
    mkdir build
fi

gcc -Wall -Wextra -o build/tetris main.c makers/*.c board_utils/*.c -lncurses