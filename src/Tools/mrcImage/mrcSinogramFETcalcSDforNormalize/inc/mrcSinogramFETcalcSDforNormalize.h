#ifndef MRCSINOGRAMFETCALCSDFORNORMALIZE_H
#define MRCSINOGRAMFETCALCSDFORNORMALIZE_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct mrcSinogramFETcalcSDforNormalizeInfo {
    long flagRedirect;

    long flagIn;
    char* In;
    FILE* fptIn;
    
    long flagSm;
    long Sm;
    
    long flagLibl;
    char* Libl;
    FILE* fptLibl;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagOW;
    char* OW;
    FILE* fptOW;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} mrcSinogramFETcalcSDforNormalizeInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(mrcSinogramFETcalcSDforNormalizeInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(mrcSinogramFETcalcSDforNormalizeInfo* info);
extern void init1(mrcSinogramFETcalcSDforNormalizeInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* MRCSINOGRAMFETCALCSDFORNORMALIZE_H */
