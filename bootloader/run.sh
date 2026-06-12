#!/bin/bash
set -e

# Build the bootloader
make

# Build the kernel
cd ../kernel
make
cd ../bootloader

# Build disk image
rm -f disk.img
dd if=/dev/zero of=disk.img bs=1M count=64 status=none
mkfs.fat -F 32 disk.img > /dev/null

mmd -i disk.img ::/EFI
mmd -i disk.img ::/EFI/BOOT
mcopy -i disk.img BOOTX64.EFI ::/EFI/BOOT/BOOTX64.EFI
mcopy -i disk.img ../kernel/kernel.elf ::/kernel.elf

if [ ! -f OVMF_VARS.fd ]; then
    cp /usr/share/edk2/x64/OVMF_VARS.4m.fd OVMF_VARS.fd
fi

echo "Starting ARK OS in QEMU..."
qemu-system-x86_64 \
    -machine q35 \
    -enable-kvm \
    -cpu host \
    -drive if=pflash,format=raw,readonly=on,file=/usr/share/edk2/x64/OVMF_CODE.4m.fd \
    -drive if=pflash,format=raw,file=OVMF_VARS.fd \
    -drive format=raw,file=disk.img \
    -m 2048M \
    -smp cores=4,threads=2,sockets=1 \
    -vga std
