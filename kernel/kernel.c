/* kernel.c */
#include <stdint.h>
#include "graphics/vga.h"

void _start() 
{
    Draw->Init();
    
    if (Draw->_BytesPerPixel == 1) {
        const int COLORS_PER_ROW = 16;
        const int COLORS_PER_COL = 16;
        const int CELL_WIDTH = Draw->_Width / COLORS_PER_ROW;
        const int CELL_HEIGHT = Draw->_Height / COLORS_PER_COL;
        
        for (int Row = 0; Row < COLORS_PER_COL; Row++) {
            for (int Col = 0; Col < COLORS_PER_ROW; Col++) {
                const int X = Col * CELL_WIDTH;
                const int Y = Row * CELL_HEIGHT;
                
                uint8_t Color = Row * COLORS_PER_ROW + Col;
                
                Draw->DrawRectangle(
                    X,
                    Y,
                    CELL_WIDTH,
                    CELL_HEIGHT,
                    Color
                );
            }
        }
    } else {
        const int COLORS_PER_ROW = 64;
        const int COLORS_PER_COL = 48;
        const int CELL_WIDTH = Draw->_Width / COLORS_PER_ROW;
        const int CELL_HEIGHT = Draw->_Height / COLORS_PER_COL;
        
        for (int Row = 0; Row < COLORS_PER_COL; Row++) {
            for (int Col = 0; Col < COLORS_PER_ROW; Col++) {
                const int X = Col * CELL_WIDTH;
                const int Y = Row * CELL_HEIGHT;
                
                float _NormalizedX = (float)Col / (COLORS_PER_ROW - 1);
                float _NormalizedY = (float)Row / (COLORS_PER_COL - 1);
                
                uint32_t Red = (uint32_t)(255 * _NormalizedX);
                uint32_t Green = (uint32_t)(255 * (1.0f - _NormalizedY));
                uint32_t Blue = (uint32_t)(255 * (_NormalizedX + _NormalizedY) / 2.0f);
                
                if (Red > 255) Red = 255;
                if (Green > 255) Green = 255;
                if (Blue > 255) Blue = 255;
                
                uint32_t Color = (Red << 16) | (Green << 8) | Blue;
                
                Draw->DrawRectangle(
                    X,
                    Y,
                    CELL_WIDTH,
                    CELL_HEIGHT,
                    Color
                );
            }
        }
    }
    
    while(1) {
        __asm__("hlt");
    }
}
