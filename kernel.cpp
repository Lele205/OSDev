#include <stddef.h>
#include "BasicRender.h"
#include "struct.h"
#include "EfiMemory.h"
#include "cstr.h"
#include "Memory.h"
#include "Bitmap.h"
#include "paging/PageFrameAllocator.h"
#include "paging/PageMapIndexer.h"
#include "paging/PageTableMenager.h"

extern uint64_t _KernelStart;
extern uint64_t _KernelEnd;

extern "C" void _start(BootInfo* bootInfo){
	
	BasicRender newRend = BasicRender(bootInfo->framebuffer, bootInfo->psf1_Font, 0xffffff);

	uint64_t mMapEntries = bootInfo->mMapSize / bootInfo->mMapDescriptorSize;

	GlobalAllocator = PageFrameAllocator();
	GlobalAllocator.ReadEFIMemoryMap(bootInfo->mMap, bootInfo->mMapSize, bootInfo->mMapDescriptorSize);

	uint64_t KernelSize = (uint64_t)&_KernelEnd - (uint64_t)&_KernelStart;

	uint64_t kernelPages = (uint64_t)KernelSize / 4096 + 1;
	GlobalAllocator.LockPages(&_KernelStart, kernelPages);

	PageTable* PML4 = (PageTable*)GlobalAllocator.RequestPage();
	memset(PML4, 0, 0x1000);

	PageTableMenager PTM = PageTableMenager(PML4);

	for(uint64_t t = 0; t < GetMemorySize(bootInfo->mMap, mMapEntries, bootInfo->mMapDescriptorSize); t += 0x1000){
		PTM.MapMemory((void*)t, (void*)t);
	}

	uint64_t fbBase = (uint64_t)bootInfo->framebuffer->BaseAddress;
	uint64_t fbSize = (uint64_t)bootInfo->framebuffer->BufferSize + 0x1000;
	GlobalAllocator.LockPages((void*)fbBase, fbSize/ 0x1000 + 1);

	for(uint64_t t = fbBase; t < fbBase + fbSize; t += 4096){
		PTM.MapMemory((void*)t, (void*)t);
	}

	asm ("mov %0, %%cr3" : : "r" (PML4));

	
	newRend.Print("Im in the new PageMap!");

	return;

}