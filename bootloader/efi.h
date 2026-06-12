#pragma once

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#define EFI_ERR(x) ((x) | (1ULL << 63))

#define EFI_SUCCESS 0
#define EFI_LOAD_ERROR EFI_ERR(1)
#define EFI_INVALID_PARAMETER EFI_ERR(2)
#define EFI_UNSUPPORTED EFI_ERR(3)
#define EFI_BAD_BUFFER_SIZE EFI_ERR(4)
#define EFI_BUFFER_TOO_SMALL EFI_ERR(5)
#define EFI_NOT_READY EFI_ERR(6)
#define EFI_DEVICE_ERROR EFI_ERR(7)
#define EFI_WRITE_PROTECTED EFI_ERR(8)
#define EFI_OUT_OF_RESOURCES EFI_ERR(9)
#define EFI_VOLUME_CORRUPTED EFI_ERR(10)
#define EFI_VOLUME_FULL EFI_ERR(11)
#define EFI_NO_MEDIA EFI_ERR(12)
#define EFI_MEDIA_CHANGED EFI_ERR(13)
#define EFI_NOT_FOUND EFI_ERR(14)
#define EFI_ACCESS_DENIED EFI_ERR(15)
#define EFI_NO_RESPONSE EFI_ERR(16)
#define EFI_NO_MAPPING EFI_ERR(17)
#define EFI_TIMEOUT EFI_ERR(18)
#define EFI_NOT_STARTED EFI_ERR(19)
#define EFI_ALREADY_STARTED EFI_ERR(20)
#define EFI_ABORTED EFI_ERR(21)
#define EFI_ICMP_ERROR EFI_ERR(22)
#define EFI_TFTP_ERROR EFI_ERR(23)
#define EFI_PROTOCOL_ERROR EFI_ERR(24)
#define EFI_INCOMPATIBLE_VERSION EFI_ERR(25)
#define EFI_SECURITY_VIOLATION EFI_ERR(26)
#define EFI_CRC_ERROR EFI_ERR(27)
#define EFI_END_OF_MEDIA EFI_ERR(28)
#define EFI_END_OF_FILE EFI_ERR(31)

#define EFI_ERROR(status) (((status) & (1ULL << 63)) != 0)

typedef uint64_t UINTN;
typedef uint64_t EFI_STATUS;
typedef void* EFI_HANDLE;

typedef struct {
    uint32_t Data1;
    uint16_t Data2;
    uint16_t Data3;
    uint8_t  Data4[8];
} EFI_GUID;

#define EFI_GRAPHICS_OUTPUT_PROTOCOL_GUID \
    { 0x9042a9de, 0x23dc, 0x4a38, { 0x96, 0xfb, 0x7a, 0xde, 0xd0, 0x80, 0x51, 0x6a } }
#define EFI_SIMPLE_FILE_SYSTEM_PROTOCOL_GUID \
    { 0x0964e5b22, 0x6459, 0x11d2, { 0x8e, 0x39, 0x00, 0xa0, 0xc9, 0x69, 0x72, 0x3b } }

typedef struct EFI_FILE_PROTOCOL EFI_FILE_PROTOCOL;
struct EFI_FILE_PROTOCOL {
    uint64_t Revision;
    EFI_STATUS (*Open)(EFI_FILE_PROTOCOL *This, EFI_FILE_PROTOCOL **NewHandle, uint16_t *FileName, uint64_t OpenMode, uint64_t Attributes);
    EFI_STATUS (*Close)(EFI_FILE_PROTOCOL *This);
    EFI_STATUS (*Delete)(EFI_FILE_PROTOCOL *This);
    EFI_STATUS (*Read)(EFI_FILE_PROTOCOL *This, UINTN *BufferSize, void *Buffer);
    EFI_STATUS (*Write)(EFI_FILE_PROTOCOL *This, UINTN *BufferSize, void *Buffer);
    EFI_STATUS (*SetPosition)(EFI_FILE_PROTOCOL *This, uint64_t Position);
    EFI_STATUS (*GetPosition)(EFI_FILE_PROTOCOL *This, uint64_t *Position);
    EFI_STATUS (*GetInfo)(EFI_FILE_PROTOCOL *This, EFI_GUID *InformationType, UINTN *BufferSize, void *Buffer);
    EFI_STATUS (*SetInfo)(EFI_FILE_PROTOCOL *This, EFI_GUID *InformationType, UINTN BufferSize, void *Buffer);
    EFI_STATUS (*Flush)(EFI_FILE_PROTOCOL *This);
};

typedef struct {
    uint64_t Revision;
    EFI_STATUS (*OpenVolume)(void *This, EFI_FILE_PROTOCOL **Root);
} EFI_SIMPLE_FILE_SYSTEM_PROTOCOL;

#define EFI_FILE_MODE_READ 1

#define EFI_GLOBAL_VARIABLE \
    { 0x8BE4DF61, 0x93CA, 0x11d2, { 0xAA, 0x0D, 0x00, 0xE0, 0x98, 0x03, 0x2B, 0x8C } }

#define EFI_VARIABLE_NON_VOLATILE 0x00000001
#define EFI_VARIABLE_BOOTSERVICE_ACCESS 0x00000002
#define EFI_VARIABLE_RUNTIME_ACCESS 0x00000004

typedef struct {
    uint32_t Attributes;
    uint16_t FilePathListLength;

} EFI_LOAD_OPTION;

typedef struct {
    uint16_t ScanCode;
    uint16_t UnicodeChar;
} EFI_INPUT_KEY;

typedef struct EFI_SIMPLE_TEXT_INPUT_PROTOCOL EFI_SIMPLE_TEXT_INPUT_PROTOCOL;
struct EFI_SIMPLE_TEXT_INPUT_PROTOCOL {
    EFI_STATUS (*Reset)(EFI_SIMPLE_TEXT_INPUT_PROTOCOL *This, bool ExtendedVerification);
    EFI_STATUS (*ReadKeyStroke)(EFI_SIMPLE_TEXT_INPUT_PROTOCOL *This, EFI_INPUT_KEY *Key);
    void *WaitForKey;
};

typedef struct EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL;

typedef struct {
    int32_t MaxMode;
    int32_t Mode;
    int32_t Attribute;
    int32_t CursorColumn;
    int32_t CursorRow;
    bool CursorVisible;
} EFI_SIMPLE_TEXT_OUTPUT_MODE;

struct EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL {
    EFI_STATUS (*Reset)(EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This, bool ExtendedVerification);
    EFI_STATUS (*OutputString)(EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This, uint16_t *String);
    EFI_STATUS (*TestString)(EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This, uint16_t *String);
    EFI_STATUS (*QueryMode)(EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This, UINTN ModeNumber, UINTN *Columns, UINTN *Rows);
    EFI_STATUS (*SetMode)(EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This, UINTN ModeNumber);
    EFI_STATUS (*SetAttribute)(EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This, UINTN Attribute);
    EFI_STATUS (*ClearScreen)(EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This);
    EFI_STATUS (*SetCursorPosition)(EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This, UINTN Column, UINTN Row);
    EFI_STATUS (*EnableCursor)(EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This, bool Visible);
    EFI_SIMPLE_TEXT_OUTPUT_MODE *Mode;
};

#define EVT_TIMER 0x80000000
#define TPL_CALLBACK 8
#define TimerRelative 1

#define EFI_BLACK 0x00
#define EFI_BLUE 0x01
#define EFI_GREEN 0x02
#define EFI_CYAN 0x03
#define EFI_RED 0x04
#define EFI_MAGENTA 0x05
#define EFI_BROWN 0x06
#define EFI_LIGHTGRAY 0x07
#define EFI_DARKGRAY 0x08
#define EFI_LIGHTBLUE 0x09
#define EFI_LIGHTGREEN 0x0A
#define EFI_LIGHTCYAN 0x0B
#define EFI_LIGHTRED 0x0C
#define EFI_LIGHTMAGENTA 0x0D
#define EFI_YELLOW 0x0E
#define EFI_WHITE 0x0F

#define EFI_BACKGROUND_BLACK 0x00
#define EFI_BACKGROUND_BLUE 0x10
#define EFI_BACKGROUND_GREEN 0x20
#define EFI_BACKGROUND_CYAN 0x30
#define EFI_BACKGROUND_RED 0x40
#define EFI_BACKGROUND_MAGENTA 0x50
#define EFI_BACKGROUND_BROWN 0x60
#define EFI_BACKGROUND_LIGHTGRAY 0x70

typedef struct {
    uint64_t Signature;
    uint32_t Revision;
    uint32_t HeaderSize;
    uint32_t CRC32;
    uint32_t Reserved;
} EFI_TABLE_HEADER;

typedef struct EFI_BOOT_SERVICES EFI_BOOT_SERVICES;
struct EFI_BOOT_SERVICES {
    EFI_TABLE_HEADER Hdr;

    void *RaiseTPL;
    void *RestoreTPL;

    EFI_STATUS (*AllocatePages)(uint32_t Type, uint32_t MemoryType, UINTN Pages, void *Memory);
    EFI_STATUS (*FreePages)(void *Memory, UINTN Pages);
    EFI_STATUS (*GetMemoryMap)(UINTN *MemoryMapSize, void *MemoryMap, UINTN *MapKey, UINTN *DescriptorSize, uint32_t *DescriptorVersion);
    EFI_STATUS (*AllocatePool)(uint32_t PoolType, UINTN Size, void **Buffer);
    EFI_STATUS (*FreePool)(void *Buffer);

    EFI_STATUS (*CreateEvent)(uint32_t Type, UINTN NotifyTpl, void *NotifyFunction, void *NotifyContext, void **Event);
    EFI_STATUS (*SetTimer)(void *Event, uint32_t Type, uint64_t TriggerTime);
    EFI_STATUS (*WaitForEvent)(UINTN NumberOfEvents, void **Event, UINTN *Index);
    EFI_STATUS (*SignalEvent)(void *Event);
    EFI_STATUS (*CloseEvent)(void *Event);
    EFI_STATUS (*CheckEvent)(void *Event);

    void *InstallProtocolInterface;
    void *ReinstallProtocolInterface;
    void *UninstallProtocolInterface;
    void *HandleProtocol;
    void *Reserved;
    void *RegisterProtocolNotify;
    EFI_STATUS (*LocateHandle)(uint32_t SearchType, EFI_GUID *Protocol, void *SearchKey, UINTN *BufferSize, EFI_HANDLE *Buffer);
    void *LocateDevicePath;
    void *InstallConfigurationTable;

    EFI_STATUS (*LoadImage)(bool BootPolicy, EFI_HANDLE ParentImageHandle, void *DevicePath, void *SourceBuffer, UINTN SourceSize, EFI_HANDLE *ImageHandle);
    EFI_STATUS (*StartImage)(EFI_HANDLE ImageHandle, UINTN *ExitDataSize, uint16_t **ExitData);
    void *Exit;
    void *UnloadImage;
    EFI_STATUS (*ExitBootServices)(EFI_HANDLE ImageHandle, UINTN MapKey);

    void *GetNextMonotonicCount;
    EFI_STATUS (*Stall)(UINTN Microseconds);
    void *SetWatchdogTimer;

    void *ConnectController;
    void *DisconnectController;

    void *OpenProtocol;
    void *CloseProtocol;
    void *OpenProtocolInformation;

    EFI_STATUS (*ProtocolsPerHandle)(EFI_HANDLE Handle, EFI_GUID ***ProtocolBuffer, UINTN *ProtocolBufferCount);
    void *LocateHandleBuffer;
    EFI_STATUS (*LocateProtocol)(EFI_GUID *Protocol, void *Registration, void **Interface);

};

typedef struct EFI_RUNTIME_SERVICES EFI_RUNTIME_SERVICES;
struct EFI_RUNTIME_SERVICES {
    EFI_TABLE_HEADER Hdr;
    void *GetTime;
    void *SetTime;
    void *GetWakeupTime;
    void *SetWakeupTime;
    void *SetVirtualAddressMap;
    void *ConvertPointer;
    EFI_STATUS (*GetVariable)(uint16_t *VariableName, EFI_GUID *VendorGuid, uint32_t *Attributes, UINTN *DataSize, void *Data);
    EFI_STATUS (*GetNextVariableName)(UINTN *VariableNameSize, uint16_t *VariableName, EFI_GUID *VendorGuid);
    EFI_STATUS (*SetVariable)(uint16_t *VariableName, EFI_GUID *VendorGuid, uint32_t Attributes, UINTN DataSize, void *Data);
    void *GetNextHighMonotonicCount;
    EFI_STATUS (*ResetSystem)(uint32_t ResetType, EFI_STATUS ResetStatus, UINTN DataSize, void *ResetData);
    void *UpdateCapsule;
    void *QueryCapsuleCapabilities;
    void *QueryVariableInfo;
};

#define EfiResetCold 0
#define EfiResetWarm 1
#define EfiResetShutdown 2
#define EfiResetPlatformSpecific 3

typedef struct {
    EFI_GUID VendorGuid;
    void *VendorTable;
} EFI_CONFIGURATION_TABLE;

typedef struct {
    EFI_TABLE_HEADER Hdr;
    uint16_t *FirmwareVendor;
    uint32_t FirmwareRevision;
    EFI_HANDLE ConsoleInHandle;
    EFI_SIMPLE_TEXT_INPUT_PROTOCOL *ConIn;
    EFI_HANDLE ConsoleOutHandle;
    EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *ConOut;
    EFI_HANDLE StandardErrorHandle;
    EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *StdErr;
    EFI_RUNTIME_SERVICES *RuntimeServices;
    EFI_BOOT_SERVICES *BootServices;
    UINTN NumberOfTableEntries;
    EFI_CONFIGURATION_TABLE *ConfigurationTable;
} EFI_SYSTEM_TABLE;

typedef struct {
    uint32_t RedMask;
    uint32_t GreenMask;
    uint32_t BlueMask;
    uint32_t ReservedMask;
} EFI_PIXEL_BITMASK;

typedef enum {
    PixelRedGreenBlueReserved8BitPerColor,
    PixelBlueGreenRedReserved8BitPerColor,
    PixelBitMask,
    PixelBltOnly,
    PixelFormatMax
} EFI_GRAPHICS_PIXEL_FORMAT;

typedef struct {
    uint32_t Version;
    uint32_t HorizontalResolution;
    uint32_t VerticalResolution;
    EFI_GRAPHICS_PIXEL_FORMAT PixelFormat;
    EFI_PIXEL_BITMASK PixelInformation;
    uint32_t PixelsPerScanLine;
} EFI_GRAPHICS_OUTPUT_MODE_INFORMATION;

typedef struct {
    uint32_t MaxMode;
    uint32_t Mode;
    EFI_GRAPHICS_OUTPUT_MODE_INFORMATION *Info;
    UINTN SizeOfInfo;
    void *FrameBufferBase;
    UINTN FrameBufferSize;
} EFI_GRAPHICS_OUTPUT_PROTOCOL_MODE;

typedef struct EFI_GRAPHICS_OUTPUT_PROTOCOL EFI_GRAPHICS_OUTPUT_PROTOCOL;
struct EFI_GRAPHICS_OUTPUT_PROTOCOL {
    EFI_STATUS (*QueryMode)(EFI_GRAPHICS_OUTPUT_PROTOCOL *This, uint32_t ModeNumber, UINTN *SizeOfInfo, EFI_GRAPHICS_OUTPUT_MODE_INFORMATION **Info);
    EFI_STATUS (*SetMode)(EFI_GRAPHICS_OUTPUT_PROTOCOL *This, uint32_t ModeNumber);
    EFI_STATUS (*Blt)(EFI_GRAPHICS_OUTPUT_PROTOCOL *This, void *BltBuffer, uint32_t BltOperation, UINTN SourceX, UINTN SourceY, UINTN DestinationX, UINTN DestinationY, UINTN Width, UINTN Height, UINTN Delta);
    EFI_GRAPHICS_OUTPUT_PROTOCOL_MODE *Mode;
};

extern EFI_SYSTEM_TABLE *gST;
extern EFI_BOOT_SERVICES *gBS;
extern EFI_RUNTIME_SERVICES *gRT;
extern EFI_HANDLE gImageHandle;

#define SCAN_NULL 0x00
#define SCAN_UP 0x01
#define SCAN_DOWN 0x02
#define SCAN_RIGHT 0x03
#define SCAN_LEFT 0x04
#define SCAN_HOME 0x05
#define SCAN_END 0x06
#define SCAN_INSERT 0x07
#define SCAN_DELETE 0x08
#define SCAN_PAGE_UP 0x09
#define SCAN_PAGE_DOWN 0x0A
#define SCAN_F1 0x0B
#define SCAN_F2 0x0C
#define SCAN_F3 0x0D
#define SCAN_F4 0x0E
#define SCAN_F5 0x0F
#define SCAN_F6 0x10
#define SCAN_F7 0x11
#define SCAN_F8 0x12
#define SCAN_F9 0x13
#define SCAN_F10 0x14
#define SCAN_ESC 0x17

