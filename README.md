# DanOS

## Prerequisites

- Use Ubuntu 19.10 LTS
- Run scripts/install-pkgs.sh

## Building

- Run scripts/build-toolchain.sh
- Source the toolchain you just built

```bash
. scripts/source-toolchain.sh
```

- Build the kernel

```bash
cd kernel
make
```

## Run the kernel in QEMU

```bash
scripts/run-qemu.sh
```

To quit the kernel, use `Ctrl + A, x`

## Build and run the ISO in QEMU

```bash
scripts/build-image.sh
scripts/run-iso.sh
```
