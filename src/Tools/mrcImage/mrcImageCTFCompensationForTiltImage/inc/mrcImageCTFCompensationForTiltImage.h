#ifndef MRCIMAGECTFCOMPENSATIONFORTILTIMAGE_H
#define MRCIMAGECTFCOMPENSATIONFORTILTIMAGE_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct mrcImageCTFCompensationForTiltImageInfo {
    long flagRedirect;

    long flagIn;
    char* In;
    FILE* fptIn;
    
    long flagInfo;
    char* Info;
    FILE* fptInfo;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagcut;
    long cut;
    
    long flagmode;
    long mode;
    
} mrcImageCTFCompensationForTiltImageInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(mrcImageCTFCompensationForTiltImageInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(mrcImageCTFCompensationForTiltImageInfo* info);
extern void init1(mrcImageCTFCompensationForTiltImageInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* MRCIMAGECTFCOMPENSATIONFORTILTIMAGE_H */
