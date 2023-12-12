#!/bin/bash
wget -O $PWD/winning_numbers.so https://github.com/abdelhafid-mahmoudi-env/alx-low_level_programming/raw/master/0x18-dynamic_libraries/winning_numbers.so
export LD_PRELOAD="$PWD/winning_numbers.so"
