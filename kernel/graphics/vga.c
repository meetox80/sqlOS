/* graphics/vga.c */
#include "vga.h"
#include <stddef.h>

static Draw_t _DrawInstance = {
    ._FrameBuffer = NULL,
    .Init = Init,
    .SetPixel = SetPixel,
    .GetPixel = GetPixel,
    .Rectangle = NULL
};

Draw_t* Draw = &_DrawInstance;


void Init(void) {
    Draw->_FrameBuffer = (uint8_t*)_VGA_BUFFER;
}

/*

    Pixel Operations

*/

void SetPixel(int X, int Y, unsigned char Color) {
    if (
        X < 0 ||
        X >= _WIDTH ||

        Y < 0 ||
        Y >= _HEIGHT
    ) {
        return;
    }

    Draw->_FrameBuffer[Y * _WIDTH + X] = Color;
}

unsigned char GetPixel(int X, int Y) {
    if (
        X < 0 ||
        X >= _WIDTH ||

        Y < 0 ||
        Y >= _HEIGHT
    ) {
        return -1;
    }

    return Draw->_FrameBuffer[Y * _WIDTH + X];
}