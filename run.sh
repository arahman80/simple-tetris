#!/bin/bash

if [[ " $@ " =~ " -r " ]] || [[ " $@ " =~ " --refresh " ]]; then
    make format
    make clean && make
else
    make format
    make
fi

echo "Press ENTER to continue..."
read dummy

./build/tetris

