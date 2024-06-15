/*
# eosStarFile.h : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : eosStarFile.h 
# Attention
#   $Loccker$
#  	$State$ 
#
*/
/* $Log$ */
#ifndef EOS_STAR_FILE
#define EOS_STAR_FILE

#include <stdio.h>

/* constant begin */


/* constant end */

/* struct begin */
typedef struct eosStarFileData {
    char* key;
    char**  valueS;
    double* valueR;
    int*    valueI;
} eosStarFileData;

typedef struct eosStgrFileDataBlock {
    char* dataBlockName;

    int   numDataItem;
    eosStarFileData* data;

    int numLoopKey;
    int numLoopData;
    eosStarFileData* loop;
} eosStgrFileDataBlock;

typedef struct eosStarFile {
    int numDataBlock;
    eosStgrFileDataBlock*  block;
} eosStarFile;

/* struct end */

#ifdef __cplusplus
extern "C" {
#endif

/* prototype begin */

extern void eosStarFileDataSizeSet(eosStarFile* star, int mode);


// 
void eosStarFileDataKeySet(eosStarFile* star, char* key, int index, int mode);
void eosStarFileDataValueSSet(eosStarFile* star, char* key, char* value, int mode);
void eosStarFileDataValueRSet(eosStarFile* star, char* key, double value, int mode);
void eosStarFileDataValueISet(eosStarFile* star, char* key, int    value, int mode);

void eosStarFileLoopDataKeySet(eosStarFile* star, int index, int mode);
void eosStarFileLoopDataValueSSet(eosStarFile* star, char* key, char**  value, int mode);
void eosStarFileLoopDataValueRSet(eosStarFile* star, char* key, double* value, int mode);
void eosStarFileLoopDataValueISet(eosStarFile* star, char* key, int*    value, int mode);

// esoStarFileRead.c
extern void eosStarFileRead (FILE* fpt, eosStarFile* star, int mode);
extern void eosStarFileDataSizeGet(FILE* fpt, eosStarFile* star, int mode);
extern void eosStarFileRead0 (FILE* fpt, eosStarFile* star, int mode);

// data: block==NULL, ignore datablock
extern int eosStarFileDataGetIndex(eosStarFile* star, char* block, char* dataKey, int* blockIndex, int* dataIndex, int mode);

extern char** eosStarFileDataGetStringP(eosStarFile* star, char* block, char* key, int mode);
extern char* eosStarFileDataGetString (eosStarFile* star, char* block, char* key, char** value, int mode);

extern double* eosStarFileDataGetRealP(eosStarFile* star, char* block, char* key, int mode);
extern double eosStarFileDataGetReal (eosStarFile* star, char* block, char* key, double* value, int mode);

extern int* eosStarFileDataGetIntegerP(eosStarFile* star, char* block, char* key, int mode);
extern int  eosStarFilDataGetInterger (eosStarFile* star, char* block, char* key, int* value, int mode);

// Loop
extern char** eosStarFileLoopDataGetStringP(eosStarFile* star, char* key, int mode);
extern void eosStarFileLoopDataGetString(eosStarFile* star, char* key, char*** value, int mode);

extern double* eosStarFileLoopDataGetRealP(eosStarFile* star, char* key, int mode);
extern void eosStarFileLoopDataGetReal(eosStarFile* star, char* key, double** value, int mode);

extern int* eosStarFileLoopDataGetIntergerP(eosStarFile* star, char* key, int mode);
extern void eosStarFileLoopDataGetInterger(eosStarFile* star, char* key, int** value, int mode);

// Write
extern void eosStarFileWrite(FILE* fpt, eosStarFile* star, int mode);
/* prototype end */

#ifdef __cplusplus
};
#endif

#endif  /* EOS_STAR_FILE */ 
