#include "display.h"

EFI_GRAPHICS_OUTPUT_PROTOCOL *gGOP = NULL;

EFI_STATUS InitDisplay(void) {
    EFI_GUID gopGuid = EFI_GRAPHICS_OUTPUT_PROTOCOL_GUID;
    EFI_STATUS status = gBS->LocateProtocol(&gopGuid, NULL, (void**)&gGOP);

    if (status == EFI_SUCCESS && gGOP != NULL) {

    }
    return status;
}

void Print(const uint16_t* str) {
    if (gST && gST->ConOut) {
        gST->ConOut->OutputString(gST->ConOut, (uint16_t*)str);
    }
}

void ClearScreen(uint8_t bgColor) {
    if (gST && gST->ConOut) {
        gST->ConOut->SetAttribute(gST->ConOut, EFI_WHITE | (bgColor << 4));
        gST->ConOut->ClearScreen(gST->ConOut);
    }
}

#pragma pack(push, 1)
typedef struct {
    uint16_t bfType;
    uint32_t bfSize;
    uint16_t bfReserved1;
    uint16_t bfReserved2;
    uint32_t bfOffBits;
} BMP_FILE_HEADER;

typedef struct {
    uint32_t biSize;
    int32_t  biWidth;
    int32_t  biHeight;
    uint16_t biPlanes;
    uint16_t biBitCount;
    uint32_t biCompression;
} BMP_INFO_HEADER;
#pragma pack(pop)

EFI_STATUS DrawBmpCentered(void* bmpBuffer, UINTN bufferSize) {
    if (!gGOP || !bmpBuffer) return EFI_UNSUPPORTED;

    BMP_FILE_HEADER* fileHdr = (BMP_FILE_HEADER*)bmpBuffer;
    if (fileHdr->bfType != 0x4D42) {
        return EFI_UNSUPPORTED;
    }

    BMP_INFO_HEADER* infoHdr = (BMP_INFO_HEADER*)((uint8_t*)bmpBuffer + sizeof(BMP_FILE_HEADER));
    if (infoHdr->biBitCount != 24 && infoHdr->biBitCount != 32) {

        return EFI_UNSUPPORTED;
    }

    uint8_t* pixelData = (uint8_t*)bmpBuffer + fileHdr->bfOffBits;
    UINTN width = (UINTN)infoHdr->biWidth;
    UINTN height = (UINTN)(infoHdr->biHeight < 0 ? -infoHdr->biHeight : infoHdr->biHeight);
    bool flipY = (infoHdr->biHeight > 0);

    UINTN screenW = gGOP->Mode->Info->HorizontalResolution;
    UINTN screenH = gGOP->Mode->Info->VerticalResolution;

    uint32_t* bltBuffer = NULL;
    EFI_STATUS status = gBS->AllocatePool(2, width * height * sizeof(uint32_t), (void**)&bltBuffer);
    if (EFI_ERROR(status)) return status;

    UINTN padding = (4 - ((width * (infoHdr->biBitCount / 8)) % 4)) % 4;

    for (UINTN y = 0; y < height; y++) {
        UINTN srcY = flipY ? (height - 1 - y) : y;
        uint8_t* row = pixelData + srcY * (width * (infoHdr->biBitCount / 8) + padding);
        for (UINTN x = 0; x < width; x++) {
            uint8_t b = row[x * (infoHdr->biBitCount / 8) + 0];
            uint8_t g = row[x * (infoHdr->biBitCount / 8) + 1];
            uint8_t r = row[x * (infoHdr->biBitCount / 8) + 2];
            bltBuffer[y * width + x] = (r << 16) | (g << 8) | b;
        }
    }

    UINTN destX = (screenW > width) ? (screenW - width) / 2 : 0;
    UINTN destY = (screenH > height) ? (screenH - height) / 2 : 0;

    uint32_t whitePixel = 0x00FFFFFF;
    gGOP->Blt(gGOP, &whitePixel, 0, 0, 0, 0, 0, screenW, screenH, 0);

    status = gGOP->Blt(gGOP, bltBuffer, 2, 0, 0, destX, destY, width, height, 0);

    gBS->FreePool(bltBuffer);
    return status;
}

