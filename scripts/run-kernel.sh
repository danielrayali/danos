#!/bin/bash

SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"
if [[ ! -f "$SCRIPT_DIR/../build/danos.bin" ]]; then
    echo "Must build kernel image before running it on qemu"
    exit 1
fi
qemu-system-i386 -kernel $SCRIPT_DIR/../build/danos.bin
