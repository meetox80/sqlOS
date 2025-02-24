/* kernel.c */
#include <stdint.h>
#include "graphics/vga.h"

void _start() 
{
    Draw->Init();
    
    for (uint32_t I = 0; I < _WIDTH * _HEIGHT; I++) 
    {
        Draw->_FrameBuffer[I] = 0x0F;
    }
    
    while(1) {
        __asm__("hlt");
    }
}