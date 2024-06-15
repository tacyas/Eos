#include <stdio.h>
#include <stdlib.h>
#include "Memory.h"

Memory
memoryCopy(Memory dst, void* src, size_t nbyte)
{
	Memory stmp;
	Memory dtmp;

	stmp = src + nbyte - 1;
	dtmp = dst + nbyte - 1;
	while(stmp!=src) {
		*((char*)dtmp) = *((char*)stmp);
		dtmp--; stmp--;
	}
	*((char*)dst) = *((char*)src);
    return dst;
}

Memory
memoryDuplicate(Memory src, size_t nbyte)
{
	char* dst;

	dst = (Memory)memoryAllocate(nbyte, "in memoryDuplicate");
	memoryCopy(dst, src, nbyte);
	return dst;
}
