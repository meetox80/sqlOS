/* kernel.c */
#include <stdint.h>
#include "graphics/vga.h"

void _start() 
{
    Draw->Init();
    
    for (uint32_t i = 0; i < _WIDTH * _HEIGHT; i++) 
    {
        Draw->_FrameBuffer[i] = 0x0F;
    }

    const int CELL_SIZE = 10;
    const int SPACING = 2;
    const int COLS = 16; // (sqrt(256)

    for (uint32_t i = 0; i < 256; i++) {
        const int col = i % COLS;
        const int row = i / COLS;
        
        const int x = col * (CELL_SIZE + SPACING);
        const int y = row * (CELL_SIZE + SPACING);
        
        Draw->DrawRectangle(
            x,
            y,
            CELL_SIZE,
            CELL_SIZE,
            (uint8_t)i
        );
    }

    
    while(1) {
        __asm__("hlt");
    }
}