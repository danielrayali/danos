#!/bin/bash

mkdir -p build/toolchain
cd build/toolchain

BINUTILS_DIR="binutils-2.34"
GCC_DIR="gcc-9.2.0"

if [ ! -d $BINUTILS_DIR ]; then
    wget https://ftp.gnu.org/gnu/binutils/$BINUTILS_DIR.tar.gz
    tar -xvf ./$BINUTILS_DIR.tar.gz
fi

if [ ! -d $GCC_DIR ]; then
    wget https://ftp.gnu.org/gnu/gcc/$GCC_DIR/$GCC_DIR.tar.gz
    tar -xvf ./$GCC_DIR.tar.gz
fi

export PREFIX="$PWD/opt/local"
export TARGET=x86_64-elf
export PATH="$PREFIX/bin:$PATH"

mkdir -p build-binutils
cd build-binutils
../$BINUTILS_DIR/configure --target=$TARGET --prefix="$PREFIX" --with-sysroot --disable-nls --disable-werror
make -j`nproc`
make install
cd ../

# The $PREFIX/bin dir _must_ be in the PATH. We did that above.
which -- $TARGET-as || echo $TARGET-as is not in the PATH
mkdir -p build-gcc
cd build-gcc
../$GCC_DIR/configure --target=$TARGET --prefix="$PREFIX" --disable-nls --enable-languages=c,c++ --without-headers
make all-gcc -j`nproc`
make all-target-libgcc -j`nproc`
make install-gcc
make install-target-libgcc
cd ../
