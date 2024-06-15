#ifndef MRC3DTO2DFFT_H
#define MRC3DTO2DFFT_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct mrc3Dto2DFFTInfo {
    long flagRedirect;

    long flagIn;
    char* In;
    FILE* fptIn;
    
    long flagTemplate;
    char* Template;
    FILE* fptTemplate;
    
    long flagInPri;
    char* InPri;
    FILE* fptInPri;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagEulerMode;
    char* EulerMode;
    
    long flagRot1Start;
    float Rot1Start;
    
    long flagRot1End;
    float Rot1End;
    
    long flagRot1Delta;
    float Rot1Delta;
    
    long flagRot2Start;
    float Rot2Start;
    
    long flagRot2End;
    float Rot2End;
    
    long flagRot2Delta;
    float Rot2Delta;
    
    long flagRot3Start;
    float Rot3Start;
    
    long flagRot3End;
    float Rot3End;
    
    long flagRot3Delta;
    float Rot3Delta;
    
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
    
} mrc3Dto2DFFTInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(mrc3Dto2DFFTInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(mrc3Dto2DFFTInfo* info);
extern void init1(mrc3Dto2DFFTInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* MRC3DTO2DFFT_H */
