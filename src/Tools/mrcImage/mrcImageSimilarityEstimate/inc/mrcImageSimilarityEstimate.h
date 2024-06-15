#ifndef MRCIMAGESIMILARITYESTIMATE_H
#define MRCIMAGESIMILARITYESTIMATE_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct mrcImageSimilarityEstimateInfo {
    long flagRedirect;

    long flagIn;
    char* In;
    FILE* fptIn;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagOutCor;
    char* OutCor;
    FILE* fptOutCor;
    
    long flagref;
    char** ref;
    char* refList;
    FILE** fptref;
    FILE* fptrefList;
    
    long flagcorfilename;
    char** corfilename;
    char* corfilenameList;
    FILE** fptcorfilename;
    FILE* fptcorfilenameList;
    
    long flagcormode;
    long cormode;
    
    long flagctfinfo;
    char* ctfinfo;
    FILE* fptctfinfo;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} mrcImageSimilarityEstimateInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(mrcImageSimilarityEstimateInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(mrcImageSimilarityEstimateInfo* info);
extern void init1(mrcImageSimilarityEstimateInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* MRCIMAGESIMILARITYESTIMATE_H */
