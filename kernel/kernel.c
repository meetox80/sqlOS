#include <stdint.h>
#include "graphics/vga.h"

void _start() 
{
    Draw->Init();
    
    const int _CenterX = 320;
    const int _CenterY = 240;
    const int _Radius = 100;
    
    for (int Y = _CenterY - _Radius; Y <= _CenterY + _Radius; Y++) {
        for (int X = _CenterX - _Radius; X <= _CenterX + _Radius; X++) {
            int _Dx = X - _CenterX;
            int _Dy = Y - _CenterY;
            int _DistanceSquared = _Dx * _Dx + _Dy * _Dy;
            int _RadiusSquared = _Radius * _Radius;
            
            if (_DistanceSquared <= _RadiusSquared) {
                if (_Dx == 0 && _Dy == 0) {
                    Draw->SetPixel(X, Y, 0xFFFFFF);
                    continue;
                }

                int _Hue;

                if (_Dy >= 0) {
                    if (_Dx >= 0) {
                        if (_Dx >= _Dy) {
                            _Hue = (_Dy * 45) / _Dx;
                        } else {
                            _Hue = 90 - ((_Dx * 45) / _Dy);
                        }
                    } else {
                        if (-_Dx < _Dy) {
                            _Hue = 90 + ((-_Dx * 45) / _Dy);
                        } else {
                            _Hue = 180 - ((_Dy * 45) / -_Dx);
                        }
                    }
                } else {
                    if (_Dx < 0) {
                        if (-_Dx >= -_Dy) {
                            _Hue = 180 + ((-_Dy * 45) / -_Dx);
                        } else {
                            _Hue = 270 - ((-_Dx * 45) / -_Dy);
                        }
                    } else {
                        if (_Dx < -_Dy) {
                             _Hue = 270 + ((_Dx * 45) / -_Dy);
                        } else {
                             _Hue = 360 - ((-_Dy * 45) / _Dx);
                        }
                    }
                }
                
                if (_Hue >= 360) _Hue = 359;
                
                int _R, _G, _B;
                int _Hi = _Hue / 60;
                int _Remainder = _Hue % 60;
                int _T = (_Remainder * 255) / 60;
                int _Q = 255 - _T;
                int _P = 0;
                
                switch(_Hi) {
                    case 0: _R = 255; _G = _T; _B = _P; break;
                    case 1: _R = _Q; _G = 255; _B = _P; break;
                    case 2: _R = _P; _G = 255; _B = _T; break;
                    case 3: _R = _P; _G = _Q; _B = 255; break;
                    case 4: _R = _T; _G = _P; _B = 255; break;
                    case 5: _R = 255; _G = _P; _B = _Q; break;
                }
                
                uint32_t _Color = (_R << 16) | (_G << 8) | _B;
                Draw->SetPixel(X, Y, _Color);
            }
        }
    }
    
    while(1) {
        __asm__("hlt");
    }
}
