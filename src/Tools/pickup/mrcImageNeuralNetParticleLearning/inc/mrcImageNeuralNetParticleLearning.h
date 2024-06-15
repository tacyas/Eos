#ifndef MRCIMAGENEURALNETPARTICLELEARNING_H
#define MRCIMAGENEURALNETPARTICLELEARNING_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct mrcImageNeuralNetParticleLearningInfo {
    long flagRedirect;

    long flagInPositive;
    char** InPositive;
    char* InPositiveList;
    FILE** fptInPositive;
    FILE* fptInPositiveList;
    
    long flagInNegative;
    char** InNegative;
    char* InNegativeList;
    FILE** fptInNegative;
    FILE* fptInNegativeList;
    
    long flagOut;
    char** Out;
    char* OutList;
    FILE** fptOut;
    FILE* fptOutList;
    
    long flagBias;
    float Bias;
    
    long flagMaxCounter;
    long MaxCounter;
    
    long flagEPS;
    float EPS;
    
    long flagLambda;
    float Lambda;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} mrcImageNeuralNetParticleLearningInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(mrcImageNeuralNetParticleLearningInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(mrcImageNeuralNetParticleLearningInfo* info);
extern void init1(mrcImageNeuralNetParticleLearningInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* MRCIMAGENEURALNETPARTICLELEARNING_H */
