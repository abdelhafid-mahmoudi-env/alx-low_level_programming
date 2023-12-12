#!/bin/bash
wget -P /tmp https://github.com/abdelhafid-mahmoudi-env/alx-low_level_programming/raw/master/0x18-dynamic_libraries/winning_numbers.so
export LD_PRELOAD=/tmp/winning_numbers.so
