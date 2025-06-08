/* graphics/vga.c */
#include "vga.h"
#include <stddef.h>

#include "shapes/rectangle.h"

static Draw_t _DrawInstance = {
    ._FrameBuffer = NULL,
    ._Width = 0,
    ._Height = 0,
    ._BytesPerPixel = 0,
    .Init = Init,
    .SetPixel = SetPixel,
    .GetPixel = GetPixel,
    
    .DrawRectangle = DrawRectangle
};

Draw_t* Draw = &_DrawInstance;

static int _IsVBEMode() {
    volatile uint32_t* _TestPtr = (volatile uint32_t*)_VGA_BUFFER_VBE;
    *_TestPtr = 0x12345678;
    return (*_TestPtr == 0x12345678);
}

void Init(void) {
    if (_IsVBEMode()) {
        Draw->_FrameBuffer = (uint8_t*)_VGA_BUFFER_VBE;
        Draw->_Width = _WIDTH_VBE;
        Draw->_Height = _HEIGHT_VBE;
        Draw->_BytesPerPixel = 3;
    } else {
        Draw->_FrameBuffer = (uint8_t*)_VGA_BUFFER_STD;
        Draw->_Width = _WIDTH_STD;
        Draw->_Height = _HEIGHT_STD;
        Draw->_BytesPerPixel = 1;
    }
}

void SetPixel(int X, int Y, uint32_t Color) {
    if (
        X < 0 ||
        X >= Draw->_Width ||
        Y < 0 ||
        Y >= Draw->_Height
    ) {
        return;
    }

    if (Draw->_BytesPerPixel == 1) {
        Draw->_FrameBuffer[Y * Draw->_Width + X] = (uint8_t)Color;
    } else {
        int _Offset = (Y * Draw->_Width + X) * 3;
        Draw->_FrameBuffer[_Offset] = (uint8_t)(Color & 0xFF);
        Draw->_FrameBuffer[_Offset + 1] = (uint8_t)((Color >> 8) & 0xFF);
        Draw->_FrameBuffer[_Offset + 2] = (uint8_t)((Color >> 16) & 0xFF);
    }
}

uint32_t GetPixel(int X, int Y) {
    if (
        X < 0 ||
        X >= Draw->_Width ||
        Y < 0 ||
        Y >= Draw->_Height
    ) {
        return 0;
    }

    if (Draw->_BytesPerPixel == 1) {
        return Draw->_FrameBuffer[Y * Draw->_Width + X];
    } else {
        int _Offset = (Y * Draw->_Width + X) * 3;
        return (Draw->_FrameBuffer[_Offset + 2] << 16) |
               (Draw->_FrameBuffer[_Offset + 1] << 8) |
               Draw->_FrameBuffer[_Offset];
    }
}
