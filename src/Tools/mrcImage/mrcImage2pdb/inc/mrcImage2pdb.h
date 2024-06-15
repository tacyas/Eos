#ifndef MRCIMAGE2PDB_H
#define MRCIMAGE2PDB_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct mrcImage2pdbInfo {
    long flagRedirect;

    long flagIn;
    char* In;
    FILE* fptIn;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
    long flagh;
    float h;
    
    long flagl;
    float l;
    
    long Lattice;

    long flagSkip;
    long Skip;
    
    long flagRandom;
    float Random;
    
    long flagdelta;
    float delta;
    
} mrcImage2pdbInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(mrcImage2pdbInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(mrcImage2pdbInfo* info);
extern void init1(mrcImage2pdbInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* MRCIMAGE2PDB_H */
