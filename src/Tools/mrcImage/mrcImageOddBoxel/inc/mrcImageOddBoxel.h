#ifndef MRCIMAGEODDBOXEL_H
#define MRCIMAGEODDBOXEL_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct mrcImageOddBoxelInfo {
    long flagRedirect;

    long flagIn;
    char** In;
    char* InList;
    FILE** fptIn;
    FILE* fptInList;
    
    long Iteration;

    long flagMolecularWeight;
    float MolecularWeight;
    
    long flagnMolecule;
    float nMolecule;
    
    long flagBoxel;
    long Boxel;
    
    long flagDensity;
    float Density;
    
    long Inverse;

    long Absolute;

    long flagTh;
    float Th;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} mrcImageOddBoxelInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(mrcImageOddBoxelInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(mrcImageOddBoxelInfo* info);
extern void init1(mrcImageOddBoxelInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* MRCIMAGEODDBOXEL_H */
