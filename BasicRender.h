#pragma once
#include "struct.h"

class BasicRender{
    public:
        BasicRender(Framebuffer* targetBuffer, PSF1_FONT* psf1_font, unsigned int color = 0xffffffff);
        Framebuffer* TargetBuffer;
        PSF1_FONT* PSF1_font;
        Point CursorPosition;
        unsigned int Color;
        void Print(const char* str);
        void putChar(char chr, unsigned int xOff, unsigned int yOff);
};