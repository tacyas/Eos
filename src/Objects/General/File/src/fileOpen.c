#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../inc/File.h"

FILE* 
fileOpen(char* filename, char* mode)
{
    FILE* fpt;

    if(NULL==(fpt=fopen(filename, mode))) {
        fprintf(stderr, "File not Opened : %s mode %s\n", filename, mode);
        exit(EXIT_FAILURE);
    }
    return fpt;
}
