# ARK-OS
A BOOTLOADER+KERNEL+GUI Giving Custom OS. (ONLY SUPPORT 14-gr0000TU [KERNEL])

Clone the repo and run `cd "path/to/ARK-OS/bootloader" && make && cd ../kernel && make && ./run.sh`

## BootLoader

  - Shows ARKOS logo with white background
  - Press `ESC` key to enturrupt boot and get into:
    
  <img width="513" height="315" alt="image" src="https://github.com/user-attachments/assets/c9f56459-5988-410d-b8a1-425e7c8b66bd" />

Issue: Function Keys Do NOT WORK... USE number keys!

## KERNEL

  - It is able to Locate Simple File Systems, Load Kernel Segmennts and build bootinfo.
  - It cant give a display output yet... Boot Into Verbose MODE.

Also it does not know what is anything... it is only made to do that and display a green screen showcasing that I am ready for the next phase but unable to get there yet!

## GUI

  - After the kernel is done booting it will hand it of to the GUI [I am saying GUI since it is a simple word for non techies to understand] WHich is just a bunch of empty folder since i have do nnothing for that yet but here is the tree:

```
OS
├── Applications
│   ├── AI
│   ├── Browsers
│   ├── Cloud
│   ├── Devlopers
│   ├── Entertainment
│   ├── Social
│   ├── Study
│   └── Utilities
├── System
│   ├── <APPNAME>.cache
│   ├── Drivers
│   └── Logs
└── User
    └── USERNAME
        ├── Desktop
        ├── Documents
        ├── Downloads
        ├── Music
        └── Photos
            ├── Camera
            ├── Screen Records
            └── ScreenShots

```

## File Tree OF Project

```tree

.
├── bootloader
│   ├── BOOTX64.EFI
│   ├── efi.h
│   ├── image
│   │   ├── EFI
│   │   │   └── BOOT
│   │   │       └── BOOTX64.EFI
│   │   ├── kernel.elf
│   │   └── NvVars
│   ├── INPUT
│   │   └── KEYBOARD
│   │       ├── INPUT_ESC
│   │       │   ├── ESC
│   │       │   ├── esc.c
│   │       │   ├── esc.h
│   │       │   └── esc.o
│   │       └── INPUT_FUNCTIONKEY
│   │           ├── F1
│   │           │   ├── f1.c
│   │           │   ├── f1.h
│   │           │   └── f1.o
│   │           ├── F2
│   │           │   ├── f2.c
│   │           │   ├── f2.h
│   │           │   └── f2.o
│   │           ├── F3
│   │           │   ├── f3.c
│   │           │   ├── f3.h
│   │           │   └── f3.o
│   │           ├── F4
│   │           │   ├── f4.c
│   │           │   ├── f4.h
│   │           │   └── f4.o
│   │           ├── F5
│   │           │   ├── f5.c
│   │           │   ├── f5.h
│   │           │   └── f5.o
│   │           ├── F6
│   │           │   ├── f6.c
│   │           │   ├── f6.h
│   │           │   └── f6.o
│   │           └── F7
│   │               ├── f7.c
│   │               ├── f7.h
│   │               └── f7.o
│   ├── LOADKERNEL
│   │   ├── loadkernel.c
│   │   ├── loadkernel.h
│   │   └── loadkernel.o
│   ├── main.c
│   ├── main.o
│   ├── Makefile
│   ├── OUTPUT
│   │   └── DISPLAY
│   │       ├── display.c
│   │       ├── display.h
│   │       └── display.o
│   ├── OVMF_VARS.fd
│   ├── RECOVERY
│   │   ├── recovery.c
│   │   ├── recovery.h
│   │   └── recovery.o
│   ├── run.sh
│   ├── UEFI
│   └── UI
│       ├── DRAW
│       │   ├── LOGO
│       │   │   ├── logo.bmp
│       │   │   ├── logo.h
│       │   │   └── logo.png
│       │   └── RECOVERYUI
│       │       ├── menu.c
│       │       ├── menu.h
│       │       └── menu.o
│       └── LOGIC
├── kernel
│   ├── CHARGE
│   │   ├── BATTERY
│   │   │   ├── STATUS
│   │   │   │   └── what.txt
│   │   │   └── what.txt
│   │   └── POWER
│   │       └── what.txt
│   ├── CLOCKING
│   │   ├── INTERRUPTS
│   │   └── TIMERS
│   ├── COOLING
│   ├── CPU
│   │   ├── cores
│   │   ├── hyperthreading
│   │   ├── INTEGRATEDGRAPHICS
│   │   ├── threads
│   │   └── virtulization
│   ├── HARDWARE
│   │   └── EC
│   ├── INPUT
│   │   ├── CAMERA
│   │   ├── KEYBOARD
│   │   │   ├── INPUT_ALPHABET
│   │   │   │   ├── a
│   │   │   │   ├── b
│   │   │   │   ├── c
│   │   │   │   ├── d
│   │   │   │   ├── e
│   │   │   │   ├── f
│   │   │   │   ├── g
│   │   │   │   ├── h
│   │   │   │   ├── i
│   │   │   │   ├── j
│   │   │   │   ├── k
│   │   │   │   ├── l
│   │   │   │   ├── m
│   │   │   │   ├── n
│   │   │   │   ├── o
│   │   │   │   ├── p
│   │   │   │   ├── q
│   │   │   │   ├── r
│   │   │   │   ├── s
│   │   │   │   ├── t
│   │   │   │   ├── u
│   │   │   │   ├── v
│   │   │   │   ├── w
│   │   │   │   ├── x
│   │   │   │   ├── y
│   │   │   │   └── z
│   │   │   ├── INPUT_FUNCTIONKEY
│   │   │   │   ├── F1
│   │   │   │   ├── F10
│   │   │   │   ├── F11
│   │   │   │   ├── F12
│   │   │   │   ├── F2
│   │   │   │   ├── F3
│   │   │   │   ├── F4
│   │   │   │   ├── F5
│   │   │   │   ├── F6
│   │   │   │   ├── F7
│   │   │   │   ├── F8
│   │   │   │   └── F9
│   │   │   ├── INPUT_MOVE
│   │   │   │   ├── ARROWS
│   │   │   │   │   ├── down
│   │   │   │   │   ├── left
│   │   │   │   │   ├── right
│   │   │   │   │   └── up
│   │   │   │   └── WORD
│   │   │   │       ├── END
│   │   │   │       ├── HOME
│   │   │   │       ├── PGDN
│   │   │   │       └── PGUP
│   │   │   ├── INPUT_NUMBERS
│   │   │   │   ├── 0
│   │   │   │   ├── 1
│   │   │   │   ├── 2
│   │   │   │   ├── 3
│   │   │   │   ├── 4
│   │   │   │   ├── 5
│   │   │   │   ├── 6
│   │   │   │   ├── 7
│   │   │   │   ├── 8
│   │   │   │   └── 9
│   │   │   ├── INPUT_REMOVE
│   │   │   │   ├── BKSP
│   │   │   │   └── DELETE
│   │   │   ├── INPUT_SYMBOLS
│   │   │   │   ├── ANDSYMBOL
│   │   │   │   ├── AROWLEFTSYMBOL
│   │   │   │   ├── ARROWRIGHSYMBOL
│   │   │   │   ├── ASTERISK
│   │   │   │   ├── ATTHERATESYMBOL
│   │   │   │   ├── BACKTICK
│   │   │   │   ├── BADCKWARD_SLASH
│   │   │   │   ├── COLON
│   │   │   │   ├── COMMA
│   │   │   │   ├── CURLYBRACKETCLOSE
│   │   │   │   ├── CURLYBRACKETOPEN
│   │   │   │   ├── DASH
│   │   │   │   ├── DOLLARSYMBOL
│   │   │   │   ├── DOUBLEINVERTEDCOMMA
│   │   │   │   ├── EQUAL
│   │   │   │   ├── EXCLAMATION
│   │   │   │   ├── HASHTAG
│   │   │   │   ├── INVERTEDCOMMA
│   │   │   │   ├── PERCENT
│   │   │   │   ├── PLUS
│   │   │   │   ├── QUESTION
│   │   │   │   ├── ROUNDBRACKETCLOSE
│   │   │   │   ├── ROUNDBRACKETOPEN
│   │   │   │   ├── SLAH
│   │   │   │   ├── SQUAREBRACK_CLOSE
│   │   │   │   ├── SQUREBRACK_OPEN
│   │   │   │   ├── STANDINGLINE
│   │   │   │   ├── STOP
│   │   │   │   ├── UNDERSCORE
│   │   │   │   └── UPARROWSYMBOL
│   │   │   ├── INPUT_UTILS
│   │   │   │   ├── ALT_LEFT
│   │   │   │   ├── ALT_RIGHT
│   │   │   │   ├── CAPS
│   │   │   │   ├── CTRL_LEFT
│   │   │   │   ├── CTRL_RIGHT
│   │   │   │   ├── ESC
│   │   │   │   ├── FN
│   │   │   │   ├── PRT_SRC
│   │   │   │   ├── SHIFT_LEFT
│   │   │   │   ├── SHIFT_RIGHT
│   │   │   │   ├── SUPER
│   │   │   │   └── TAB
│   │   │   └── MAPPER
│   │   │       └── what.txt
│   │   ├── MOUSE
│   │   │   ├── LEFT
│   │   │   ├── MOVE
│   │   │   ├── RIGHT
│   │   │   ├── SCROLLDOWN
│   │   │   └── SCROLLUP
│   │   └── USB
│   │       ├── C-PORT
│   │       ├── HDMI
│   │       ├── HEADPHONE
│   │       ├── POWERIN
│   │       ├── USBPORT1
│   │       └── USBPORT2
│   ├── kernel.elf
│   ├── kernel.ld
│   ├── main.c
│   ├── main.o
│   ├── Makefile
│   ├── MOTHERBOARD
│   ├── OUTPUT
│   │   ├── DISPLAY
│   │   ├── HDMI
│   │   ├── HEADPHONE
│   │   └── SPEAKERS
│   ├── SHARED
│   │   └── bootinfo.h
│   ├── STORAGE
│   │   ├── HDD
│   │   ├── NVME
│   │   ├── RAM
│   │   ├── SATA
│   │   ├── SSD
│   │   └── USB
│   ├── UEFI
│   │   └── elf.h
│   └── VIRTULIZATION
├── LICENSE
├── NOTICE
├── OS
│   ├── Applications
│   │   ├── AI
│   │   ├── Browsers
│   │   ├── Cloud
│   │   ├── Devlopers
│   │   ├── Entertainment
│   │   ├── Social
│   │   ├── Study
│   │   └── Utilities
│   ├── System
│   │   ├── <APPNAME>.cache
│   │   ├── Drivers
│   │   └── Logs
│   └── User
│       └── aarav
│           ├── Desktop
│           ├── Documents
│           ├── Downloads
│           ├── Music
│           └── Photos
│               ├── Camera
│               ├── Screen Records
│               └── ScreenShots
└── README.md

```
