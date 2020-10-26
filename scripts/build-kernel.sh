#!/bin/bash

. scripts/source-toolchain.sh
rm build/danos.bin
cd kernel
make
cd ..