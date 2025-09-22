#!/usr/bin/env bash

# the C replacement I tried making was hot garbage so run.sh is back
set -e  # exit on any error

# Always format first
make format

# Determine which build to run
if [[ " $* " == *" --debug "* ]]; then
    echo "Running debug build..."
    make clean && make debug
elif [[ " $* " == *" --refresh "* ]]; then
    echo "Running refresh build..."
    make clean && make
else
    echo "Running default parallel build..."
    make -j"$(nproc)"
fi
