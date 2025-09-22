#!/bin/bash

make format

if [[ " $@ " =~ " -d " ]] || [[ " $@ " =~ " --debug " ]]; then
    make clean && make debug
elif [[ " $@ " =~ " -r " ]] || [[ " $@ " =~ " --refresh " ]]; then
    make clean && make
else
    make -j$(nproc)
fi


echo "Press enter to continue"
read dummy

./build/tetris

