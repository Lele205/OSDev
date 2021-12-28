#include "BasicRender.h"

BasicRender::BasicRender(Framebuffer* targetBuffer, PSF1_FONT* psf1_Font, unsigned int color){
	TargetBuffer = targetBuffer;
	PSF1_font = psf1_Font;
	CursorPosition = {0, 0};
	Color = color;
};

void BasicRender::Print(const char* str){
	
	char* chr = (char*)str;
	while (*chr != 0)
	{
		putChar(*chr, CursorPosition.x, CursorPosition.y);
		CursorPosition.x += 8;
		if(CursorPosition.x + 8 > TargetBuffer->Width)
		{
			CursorPosition.x = 0;
			CursorPosition.y += 18;
		}
		chr++;
	}
	
}

void BasicRender::putChar(char chr, unsigned int xOff, unsigned int yOff){

	unsigned int* pixPtr = (unsigned int*)TargetBuffer->BaseAddress;
	char* fontPtr = (char*)PSF1_font->glyphBuffer + (chr * PSF1_font->psf1_Header->charsize);

	for(unsigned long y = yOff; y < yOff+18; y++){
		for(unsigned long x = xOff; x < xOff+8; x++){
			if((*fontPtr & (0b10000000 >> (x - xOff))) > 0){
				*(unsigned int*)(pixPtr + x + (y * TargetBuffer->PixelsPerScanLine)) = Color;
			}
		}
		fontPtr++;
	}

}