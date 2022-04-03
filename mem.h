#pragma once

uintptr_t  findMemoryAddress(uintptr_t  ptr, std::vector<int> offsets);

void  patch(BYTE*  destination, BYTE*  source,  unsigned int size);

void  nop(BYTE* destination, unsigned int size);

bool hook(void* target, void* myFunc, int size);

