#pragma once
#include "Paging.h"

class PageTableMenager{
    public:
        PageTableMenager(PageTable* PML4Address);
        PageTable* PML4;
        void MapMemory(void* virtualMemory, void* physicalMemory);
};