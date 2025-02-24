/* graphics/vga.h */
#ifndef VGA_H
#define VGA_H

#include <stdint.h>

#define _VGA_BUFFER 0xA0000
#define _WIDTH      320
#define _HEIGHT     200

typedef struct {
    /* Values */
    volatile uint8_t *_FrameBuffer;

    /* Functions */
    void (*Init)(void);
    
    /* Shapes */
    void (*DrawRectangle)(int X, int Y, int Width, int Height, unsigned char Color);

    /* Pixel Operations */
    void (*SetPixel)(int X, int Y, unsigned char Color);
    unsigned char (*GetPixel)(int X, int Y);
} Draw_t;

extern Draw_t* Draw;

void Init(void);

void SetPixel(int X, int Y, unsigned char Color);
unsigned char GetPixel(int X, int Y);

#endif