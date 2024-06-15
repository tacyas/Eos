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
    
    long flagStartX;
    float StartX;
    
    long flagStartY;
    float StartY;
    
    long flagStartZ;
    float StartZ;
    
    long flagAX;
    float AX;
    
    long flagAY;
    float AY;
    
    long flagAZ;
    float AZ;
    
    long flagBX;
    float BX;
    
    long flagBY;
    float BY;
    
    long flagBZ;
    float BZ;
    
    long flagCX;
    float CX;
    
    long flagCY;
    float CY;
    
    long flagCZ;
    float CZ;
    
    long flagMode;
    long Mode;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} mrcImageCrystalCreateInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(mrcImageCrystalCreateInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(mrcImageCrystalCreateInfo* info);
extern void init1(mrcImageCrystalCreateInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* MRCIMAGECRYSTALCREATE_H */
