#!/bin/bash

# TODO(dali) Add checks for the danos.bin
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"
qemu-system-i386 -kernel $DIR/../build/danos.bin
