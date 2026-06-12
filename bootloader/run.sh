#!/bin/bash
set -e

# Build the bootloader
make

# Build the kernel
cd ../kernel
make
cd ../bootloader

# Copy to image folder
mkdir -p image/EFI/BOOT
cp BOOTX64.EFI image/EFI/BOOT/BOOTX64.EFI
cp ../kernel/kernel.elf image/kernel.elf

if [ ! -f OVMF_VARS.fd ]; then
    cp /usr/share/edk2/x64/OVMF_VARS.4m.fd OVMF_VARS.fd
fi

echo "Starting ARK OS in QEMU..."
qemu-system-x86_64 \
    -drive if=pflash,format=raw,readonly=on,file=/usr/share/edk2/x64/OVMF_CODE.4m.fd \
    -drive if=pflash,format=raw,file=OVMF_VARS.fd \
    -drive format=raw,file=fat:rw:image \
    -m 2048M \
    -smp cores=4,threads=2,sockets=1 \
    -vga std
