CC = clang
LD = ld.lld

CFLAGS = -target x86_64-elf -ffreestanding -mno-red-zone -fPIE -Wall -Wextra -O2 -mno-sse
LDFLAGS = -T kernel.ld -nostdlib -z max-page-size=0x1000 -pie

SRCS = main.c SHARED/klog.c UEFI/uefi.c STORAGE/RAM/ram.c CPU/cores/cores.c CLOCKING/TIMERS/timers.c MOTHERBOARD/motherboard.c COOLING/cooling.c STORAGE/storage.c
OBJS = $(SRCS:.c=.o)

all: kernel.elf

kernel.elf: $(OBJS)
	$(LD) $(LDFLAGS) $(OBJS) -o kernel.elf

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) kernel.elf
