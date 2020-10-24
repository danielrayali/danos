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

## Guidelines

* Use danos types (UInt32, etc) when you care about the exact storage size of the value
* Prefer compiler types when the storage size is more flexible