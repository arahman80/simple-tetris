#!/bin/bash

if [[ " $@ " =~ " -r " ]] || [[ " $@ " =~ " --refresh " ]]; then
    make format
    make clean && make
else
    make format
    make -j$(nproc)
fi

echo "Press any key to continue"
read dummy

./build/tetris

