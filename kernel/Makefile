CC = clang
LD = ld.lld

CFLAGS = -target x86_64-elf -ffreestanding -mno-red-zone -fPIE -Wall -Wextra -O2 -mno-sse
LDFLAGS = -T kernel.ld -nostdlib -z max-page-size=0x1000 -pie

C_SRCS = main.c SHARED/klog.c UEFI/uefi.c STORAGE/RAM/ram.c STORAGE/RAM/paging.c CPU/cores/cores.c CPU/cores/idt.c CLOCKING/TIMERS/timers.c MOTHERBOARD/motherboard.c MOTHERBOARD/acpi.c COOLING/cooling.c STORAGE/storage.c
S_SRCS = CPU/cores/isr.S
OBJS = $(C_SRCS:.c=.o) $(S_SRCS:.S=.o)

all: kernel.elf

kernel.elf: $(OBJS)
	$(LD) $(LDFLAGS) $(OBJS) -o kernel.elf

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.S
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) kernel.elf
