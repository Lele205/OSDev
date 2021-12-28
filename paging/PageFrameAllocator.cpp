#include "PageFrameAllocator.h"
#include <stddef.h>

uint64_t freeMemory;
uint64_t reservedMemory;
uint64_t usedMemory;
bool Initialize = false;
PageFrameAllocator GlobalAllocator;

void PageFrameAllocator::InitBitmap(size_t bitmapSize, void* bufferAddress){
    PageBitmap.Size = bitmapSize;
    PageBitmap.Buffer = (uint8_t*)bufferAddress;
    for(int i=0; i< bitmapSize; i++){
        *(uint8_t*)(PageBitmap.Buffer + i) = 0;
    }
}
void PageFrameAllocator::FreePage(void* address){
    uint64_t index = (uint64_t)address / 4096;
    if(PageBitmap[index] == false) {return;}
    PageBitmap.Set(index, false);
        freeMemory += 4096;
        usedMemory -= 4096;
    
}

void PageFrameAllocator::LockPage(void* address){
    uint64_t index = (uint64_t)address / 4096;
    if(PageBitmap[index] == true) {return;}
    PageBitmap.Set(index, true);
    freeMemory -= 4096;
    usedMemory += 4096;
}

void PageFrameAllocator::ReservedPage(void* address){
    uint64_t index = (uint64_t)address / 4096;
    if(PageBitmap[index] == true) {return;}
    PageBitmap.Set(index, true);
    freeMemory -= 4096;
    reservedMemory += 4096;
}
void PageFrameAllocator::UnreservedPage(void* address){
    uint64_t index = (uint64_t)address / 4096;
    if(PageBitmap[index] == false) {return;}
    PageBitmap.Set(index, false);
    freeMemory += 4096;
    reservedMemory -= 4096;
}

void PageFrameAllocator::ReservedPages(void* address, uint64_t pageCount){
    for(int i = 0; i<pageCount;i++){
        ReservedPage((void*)((uint64_t)address + (i * 4096)));
    }
}

void PageFrameAllocator::UnreservedPages(void* address, uint64_t pageCount){
    for(int i = 0; i<pageCount;i++){
        UnreservedPage((void*)((uint64_t)address + (i * 4096)));
    }
}

void PageFrameAllocator::LockPages(void* address, uint64_t pageCount){
    for(int i = 0; i<pageCount;i++){
        LockPage((void*)((uint64_t)address + (i * 4096)));
    }
}

void PageFrameAllocator::FreePages(void* address, uint64_t pageCount){
    for(int i = 0; i<pageCount;i++){
        FreePage((void*)((uint64_t)address + (i * 4096)));
    }
}

void* PageFrameAllocator::RequestPage(){
    for(uint64_t index=0; index < PageBitmap.Size * 8; index++)
    {
        if(PageBitmap[index] == true) continue;
        LockPage((void*)(index * 4096));
        return (void*)(index * 4096);
    }

    return NULL;
}

void PageFrameAllocator::ReadEFIMemoryMap(EFI_MEMORY_DESCRIPTOR* mMap, size_t mMapSize, size_t mMapDescSize){
    if(Initialize) {return;}

    Initialize = true;

    uint64_t mMapEntries = mMapSize / mMapDescSize;

    void* largestFreeMemSeg = NULL;
    size_t largestFreeMemSegSize = 0;

    for(int i=0; i<mMapEntries; i++){
        EFI_MEMORY_DESCRIPTOR* desc = (EFI_MEMORY_DESCRIPTOR*)((uint64_t)mMap + (i * mMapDescSize));
        if(desc->type == 7){
            if(desc->numPages * 4096 > largestFreeMemSegSize)
            {
                largestFreeMemSeg = desc->physAddr;
                largestFreeMemSegSize = desc->numPages * 4096;
            }
        }
    }

    uint64_t memorySize = GetMemorySize(mMap, mMapEntries, mMapDescSize);
    freeMemory = memorySize;
    uint64_t bitmapSize = memorySize / 4096 / 8 + 1;

    InitBitmap(bitmapSize, largestFreeMemSeg);

    LockPages(&PageBitmap, PageBitmap.Size / 4096 + 1);

     for(int i=0; i<mMapEntries; i++){
        EFI_MEMORY_DESCRIPTOR* desc = (EFI_MEMORY_DESCRIPTOR*)((uint64_t)mMap + (i * mMapDescSize));
        if(desc->type != 7){
            ReservedPages(desc->physAddr, desc->numPages);
        }
     }

}

uint64_t PageFrameAllocator::GetFreeRAM(){
    return freeMemory;
}
uint64_t PageFrameAllocator::GetUsedRAM(){
    return usedMemory;
}
uint64_t PageFrameAllocator::GetReservedRAM(){
    return reservedMemory;
}