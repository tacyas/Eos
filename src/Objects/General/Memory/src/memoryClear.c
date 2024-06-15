#include "../inc/Memory.h"

Memory
memoryClear(Memory src, size_t nbyte, char n)
{
	Memory stmp;

	stmp = src + nbyte -1;
	while(src<=stmp) {
		*((char*)stmp) = n;
		stmp--;
	}
	return src;
}

