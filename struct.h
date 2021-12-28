#pragma once
#include <stddef.h>
#include <stdint.h>

struct Point{
    unsigned int x;
    unsigned int y;
};

struct Framebuffer{
	void* BaseAddress;
	size_t BufferSize;
	unsigned int Width;
	unsigned int Height;
	unsigned int PixelsPerScanLine;
};

struct PSF1_HEADER{
	unsigned char magic[2];
	unsigned char mode;
	unsigned char charsize;
};

struct PSF1_FONT{
	PSF1_HEADER* psf1_Header;
	void* glyphBuffer;

};

struct EFI_MEMORY_DESCRIPTOR{
	uint32_t type;
	void* physAddr;
	void* virtAddr;
	uint64_t numPages;
	uint64_t attribs;
};

struct BootInfo{
	Framebuffer* framebuffer;
	PSF1_FONT* psf1_Font;
	EFI_MEMORY_DESCRIPTOR* mMap;	
	uint64_t mMapSize;
	uint64_t mMapDescriptorSize;
};

