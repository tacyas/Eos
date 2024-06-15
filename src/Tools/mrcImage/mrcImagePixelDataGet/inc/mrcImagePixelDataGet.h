#ifndef MRCIMAGEPIXELDATAGET_H
#define MRCIMAGEPIXELDATAGET_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct mrcImagePixelDataGetInfo {
    long flagRedirect;

    long flagIn;
    char* In;
    FILE* fptIn;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagx;
    float x;
    
    long flagy;
    float y;
    
    long flagz;
    float z;
    
    long flagInCoord;
    char* InCoord;
    FILE* fptInCoord;
    
    long flagcudaDeviceID;
    long cudaDeviceID;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagoutMode;
    long outMode;
    
    long flagmode;
    long mode;
    
} mrcImagePixelDataGetInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(mrcImagePixelDataGetInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(mrcImagePixelDataGetInfo* info);
extern void init1(mrcImagePixelDataGetInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* MRCIMAGEPIXELDATAGET_H */
