#ifndef MRCFFTCENTRALSECTION_H
#define MRCFFTCENTRALSECTION_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct mrcFFTCentralSectionInfo {
    long flagRedirect;

    long flagIn;
    char* In;
    FILE* fptIn;
    
    long flagTemplate;
    char* Template;
    FILE* fptTemplate;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagOutImage;
    char* OutImage;
    FILE* fptOutImage;
    
    long flagEAMode;
    char* EAMode;
    
    long flagRot1;
    float Rot1;
    
    long flagRot2;
    float Rot2;
    
    long flagRot3;
    float Rot3;
    
    long flagTransX;
    float TransX;
    
    long flagTransY;
    float TransY;
    
    long flagInterpMode;
    long InterpMode;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} mrcFFTCentralSectionInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(mrcFFTCentralSectionInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(mrcFFTCentralSectionInfo* info);
extern void init1(mrcFFTCentralSectionInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* MRCFFTCENTRALSECTION_H */
