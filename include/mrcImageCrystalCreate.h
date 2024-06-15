#ifndef MRCIMAGECRYSTALCREATE_H
#define MRCIMAGECRYSTALCREATE_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct mrcImageCrystalCreateInfo {
    long flagRedirect;

    long flagIn;
    char* In;
    FILE* fptIn;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagnx;
    long nx;
    
    long flagny;
    long ny;
    
    long flagnz;
    long nz;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} mrcImageCrystalCreateInfo;
extern void argCheck(mrcImageCrystalCreateInfo* info, int argc, char* avgv[]);
extern void init0(mrcImageCrystalCreateInfo* info);
extern void init1(mrcImageCrystalCreateInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#endif /* MRCIMAGECRYSTALCREATE_H */
