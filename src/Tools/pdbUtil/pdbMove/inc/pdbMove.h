#ifndef PDBMOVE_H
#define PDBMOVE_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct pdbMoveInfo {
    long flagRedirect;

    long flagIn;
    char* In;
    FILE* fptIn;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagX;
    float X;
    
    long flagY;
    float Y;
    
    long flagZ;
    float Z;
    
    long flagtoX;
    float toX;
    
    long flagtoY;
    float toY;
    
    long flagtoZ;
    float toZ;
    
    long flagfromX;
    float fromX;
    
    long flagfromY;
    float fromY;
    
    long flagfromZ;
    float fromZ;
    
    long GCtoOrigin;

    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} pdbMoveInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(pdbMoveInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(pdbMoveInfo* info);
extern void init1(pdbMoveInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* PDBMOVE_H */
