#ifndef MRCIMAGEPCA_H
#define MRCIMAGEPCA_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct mrcImagePCAInfo {
    long flagRedirect;

    long flagInList;
    char** InList;
    char* InListList;
    FILE** fptInList;
    FILE* fptInListList;
    
    long flagOutList;
    char** OutList;
    char* OutListList;
    FILE** fptOutList;
    FILE* fptOutListList;
    
    long flagEPS;
    float EPS;
    
    long flagNX;
    long NX;
    
    long flagNY;
    long NY;
    
    long flagOutvector;
    char* Outvector;
    FILE* fptOutvector;
    
    long flagEPSOutcaletime;
    char* EPSOutcaletime;
    FILE* fptEPSOutcaletime;
    
    long flagEigenImage;
    char* EigenImage;
    
    long flagnumOfEigenImage;
    long numOfEigenImage;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} mrcImagePCAInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(mrcImagePCAInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(mrcImagePCAInfo* info);
extern void init1(mrcImagePCAInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* MRCIMAGEPCA_H */
