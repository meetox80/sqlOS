/* graphics/shapes/rectangle.c */
#include "../vga.h"

void DrawRectangle(int X, int Y, int Width, int Height, unsigned char Color) {
    for (int dy = 0; dy < Height; dy++) {
        int offset = (Y + dy) * _WIDTH + X;

        for (int dx = 0; dx < Width; dx++) {
            Draw->_FrameBuffer[offset + dx] = Color;
        }
    }  
}