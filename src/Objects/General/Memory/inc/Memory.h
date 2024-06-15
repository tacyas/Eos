#ifndef MEMORY_H
#define MEMORY_H

#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

#define MemoryAllocate(type,num,message) (type*)memoryAllocate(sizeof(type)*(num),message)

/* struct begin */
typedef void* Memory;

/* struct end */

/* prototype begin */
#ifdef __cplusplus
extern "C" {
#endif

extern Memory memoryAllocate(size_t byte, char* message);

/* This function must be created later in memory object. */

#define memoryFree(ptr) free(ptr)

extern Memory memoryCopy(Memory dst, Memory src, size_t byte);
extern Memory memoryDuplicate(Memory src, size_t byte);

extern Memory memoryClear(Memory src, size_t, char n);

extern Memory memoryByteSwap(Memory src, size_t, int n);

/* prototype end */

#ifdef __cplusplus
};
#endif

#endif /* MEMORY_H */
