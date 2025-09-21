#!/bin/bash

# Create build directory if it doesn't exist
if [ ! -d "build" ]; then
    mkdir build
fi

# Compile each .c file to assembly (.s) instead of an executable
for src in main.c makers/*.c board_utils/*.c; do
    # Get the base name without extension
    base=$(basename "$src" .c)
    gcc -Wall -Wextra -S -fverbose-asm -O2 "$src" -o "build/${base}.s"
done

echo "Assembly files generated in build/"
