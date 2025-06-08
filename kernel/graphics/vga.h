/* graphics/vga.h */
#ifndef VGA_H
#define VGA_H

#include <stdint.h>

#define _VGA_BUFFER_VBE 0xFD000000
#define _VGA_BUFFER_STD 0xA0000
#define _WIDTH_VBE      640
#define _HEIGHT_VBE     480
#define _WIDTH_STD      320
#define _HEIGHT_STD     200

typedef struct {
    volatile uint8_t *_FrameBuffer;
    int _Width;
    int _Height;
    int _BytesPerPixel;

    void (*Init)(void);
    
    void (*DrawRectangle)(int X, int Y, int Width, int Height, uint32_t Color);

    void (*SetPixel)(int X, int Y, uint32_t Color);
    uint32_t (*GetPixel)(int X, int Y);
} Draw_t;

extern Draw_t* Draw;

void Init(void);
void SetPixel(int X, int Y, uint32_t Color);
uint32_t GetPixel(int X, int Y);

#endif
