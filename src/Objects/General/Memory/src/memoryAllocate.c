#include <stdio.h>
#include <stdlib.h>
#include "Memory.h"

Memory
memoryAllocate(size_t size, char* message)
{
    Memory ptr;
    
    if(NULL==(ptr=(Memory)malloc(size))) {
        fprintf(stderr, "Memory Not Allocated %s : size %zu\n", message, size);
        exit(EXIT_FAILURE);
    }
	memoryClear(ptr, size, 0);
    return ptr;
}
