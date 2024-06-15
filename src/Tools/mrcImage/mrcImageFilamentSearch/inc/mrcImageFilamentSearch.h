#ifndef MRCIMAGEFILAMENTSEARCH_H
#define MRCIMAGEFILAMENTSEARCH_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct mrcImageFilamentSearchInfo {
    long flagRedirect;

    long flagIn;
    char* In;
    FILE* fptIn;
    
    long flagRef;
    char* Ref;
    FILE* fptRef;
    
    long flagOutCorr;
    char* OutCorr;
    FILE* fptOutCorr;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagOutAngle;
    char* OutAngle;
    FILE* fptOutAngle;
    
    long flagOutTheta;
    char* OutTheta;
    FILE* fptOutTheta;
    
    long flagdtheta;
    float dtheta;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} mrcImageFilamentSearchInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(mrcImageFilamentSearchInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(mrcImageFilamentSearchInfo* info);
extern void init1(mrcImageFilamentSearchInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* MRCIMAGEFILAMENTSEARCH_H */
