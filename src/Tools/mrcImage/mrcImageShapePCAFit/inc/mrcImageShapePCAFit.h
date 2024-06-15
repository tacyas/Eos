#ifndef MRCIMAGESHAPEPCAFIT_H
#define MRCIMAGESHAPEPCAFIT_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct mrcImageShapePCAFitInfo {
    long flagRedirect;

    long flagIn;
    char* In;
    FILE* fptIn;
    
    long flagRef;
    char* Ref;
    FILE* fptRef;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagFit;
    char* Fit;
    FILE* fptFit;
    
    long flagFitMat;
    char* FitMat;
    FILE* fptFitMat;
    
    long flagIMode;
    long IMode;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
    long flagContour;
    float* Contour;
    
} mrcImageShapePCAFitInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(mrcImageShapePCAFitInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(mrcImageShapePCAFitInfo* info);
extern void init1(mrcImageShapePCAFitInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* MRCIMAGESHAPEPCAFIT_H */
