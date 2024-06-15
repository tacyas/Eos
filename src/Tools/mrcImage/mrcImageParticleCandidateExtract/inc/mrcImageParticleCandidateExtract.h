#ifndef MRCIMAGEPARTICLECANDIDATEEXTRACT_H
#define MRCIMAGEPARTICLECANDIDATEEXTRACT_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct mrcImageParticleCandidateExtractInfo {
    long flagRedirect;

    long flagIn;
    char* In;
    FILE* fptIn;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagRingRadius;
    float RingRadius;
    
    long flagRingWidth;
    float RingWidth;
    
    long flagThreshold;
    float Threshold;
    
    long flagoutFileThres;
    char* outFileThres;
    FILE* fptoutFileThres;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} mrcImageParticleCandidateExtractInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(mrcImageParticleCandidateExtractInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(mrcImageParticleCandidateExtractInfo* info);
extern void init1(mrcImageParticleCandidateExtractInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* MRCIMAGEPARTICLECANDIDATEEXTRACT_H */
