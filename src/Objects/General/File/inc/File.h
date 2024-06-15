#ifndef FILE_H
#define FILE_H

#include <stdio.h>

#define FILE_MAX_STRING_LENGTH (1024)

typedef unsigned long fileParaTypeInteger;
typedef float         fileParaTypeReal;

typedef struct File {
	char name[FILE_MAX_STRING_LENGTH];
	char mode[FILE_MAX_STRING_LENGTH];
	FILE* fpt;
} File;

#ifdef __cplusplus
extern "C" {
#endif
extern FILE* fileOpen(char* filename, char* mode);
extern void fileInit(File* a);
extern long fileLineNumberGet(File* file, char* e);
extern long fileLineNumberGet2(FILE* fpt, char* e);
#ifdef __cplusplus
};
#endif

#endif /* FILE_H */
