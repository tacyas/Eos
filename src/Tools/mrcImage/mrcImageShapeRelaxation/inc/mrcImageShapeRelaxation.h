#ifndef MRCIMAGESHAPERELAXATION_H
#define MRCIMAGESHAPERELAXATION_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct mrcImageShapeRelaxationInfo {
    long flagRedirect;

    long flagIn;
    char* In;
    FILE* fptIn;
    
    long flagInVec0;
    char* InVec0;
    FILE* fptInVec0;
    
    long flagInVec1;
    char* InVec1;
    FILE* fptInVec1;
    
    long flagInVec2;
    char* InVec2;
    FILE* fptInVec2;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} mrcImageShapeRelaxationInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(mrcImageShapeRelaxationInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(mrcImageShapeRelaxationInfo* info);
extern void init1(mrcImageShapeRelaxationInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* MRCIMAGESHAPERELAXATION_H */
