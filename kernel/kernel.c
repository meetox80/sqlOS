/* kernel.c */
#include <stdint.h>

#define _VGA_BUFFER 0xA0000
#define _WIDTH 320
#define _HEIGHT 200

void _start() 
{
    volatile uint8_t *_VideoBuffer = (uint8_t*)_VGA_BUFFER;
    
    for (uint32_t i = 0; i < _WIDTH * _HEIGHT; i++) {
        _VideoBuffer[i] = 0x0F;
    }
    
    while(1) __asm__("hlt");
}
