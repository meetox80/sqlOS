/* graphics/shapes/rectangle.c */
#include "../vga.h"

void DrawRectangle(int X, int Y, int Width, int Height, uint32_t Color) {
    for (int Dy = 0; Dy < Height; Dy++) {
        for (int Dx = 0; Dx < Width; Dx++) {
            if (X + Dx < Draw->_Width && Y + Dy < Draw->_Height) {
                Draw->SetPixel(X + Dx, Y + Dy, Color);
            }
        }
    }  
}
