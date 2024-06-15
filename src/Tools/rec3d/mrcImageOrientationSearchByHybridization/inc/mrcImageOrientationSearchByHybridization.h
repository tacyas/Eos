#ifndef MRCIMAGEORIENTATIONSEARCHBYHYBRIDIZATION_H
#define MRCIMAGEORIENTATIONSEARCHBYHYBRIDIZATION_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct mrcImageOrientationSearchByHybridizationInfo {
    long flagRedirect;

    long flagIn;
    char** In;
    char* InList;
    FILE** fptIn;
    FILE* fptInList;
    
    long flagOut;
    char* Out;
    
    long flagextension;
    char* extension;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
    long flagir;
    long ir;
    
    long flaghpn;
    long hpn;
    
    long flagms;
    long ms;
    
    long flagird;
    long ird;
    
} mrcImageOrientationSearchByHybridizationInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(mrcImageOrientationSearchByHybridizationInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(mrcImageOrientationSearchByHybridizationInfo* info);
extern void init1(mrcImageOrientationSearchByHybridizationInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* MRCIMAGEORIENTATIONSEARCHBYHYBRIDIZATION_H */
