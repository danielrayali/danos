#!/bin/bash

mkdir -p build/iso/isodir/boot/grub
cp kernel/danos.bin build/iso/isodir/boot/danos.bin
cp kernel/grub.cfg build/iso/isodir/boot/grub/grub.cfg
grub-mkrescue -o build/iso/danos.iso build/iso/isodir