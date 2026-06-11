CC = clang
CFLAGS = -target x86_64-unknown-windows \
         -ffreestanding \
         -fshort-wchar \
         -mno-red-zone \
         -fno-builtin \
         -Wall \
         -Wextra \
         -I.

LDFLAGS = -target x86_64-unknown-windows \
          -nostdlib \
          -Wl,-entry:efi_main \
          -Wl,-subsystem:efi_application \
          -fuse-ld=lld

SRC = main.c \
      OUTPUT/DISPLAY/display.c \
      INPUT/KEYBOARD/INPUT_ESC/esc.c \
      INPUT/KEYBOARD/INPUT_FUNCTIONKEY/F1/f1.c \
      INPUT/KEYBOARD/INPUT_FUNCTIONKEY/F2/f2.c \
      INPUT/KEYBOARD/INPUT_FUNCTIONKEY/F3/f3.c \
      INPUT/KEYBOARD/INPUT_FUNCTIONKEY/F4/f4.c \
      INPUT/KEYBOARD/INPUT_FUNCTIONKEY/F5/f5.c \
      INPUT/KEYBOARD/INPUT_FUNCTIONKEY/F6/f6.c \
      INPUT/KEYBOARD/INPUT_FUNCTIONKEY/F7/f7.c \
      UI/DRAW/RECOVERYUI/menu.c \
      LOADKERNEL/loadkernel.c

OBJ = $(SRC:.c=.o)
TARGET = BOOTX64.EFI

all: $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET): $(OBJ)
	$(CC) $(LDFLAGS) $(OBJ) -o $@

clean:
	rm -f $(OBJ) $(TARGET)
