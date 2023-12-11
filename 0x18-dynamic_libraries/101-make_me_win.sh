#!/bin/bash
wget -q -O /tmp/gm "https://github.com/alx-tools/0x18.c/raw/master/101-md5_gm"
export LD_PRELOAD=/tmp/gm
