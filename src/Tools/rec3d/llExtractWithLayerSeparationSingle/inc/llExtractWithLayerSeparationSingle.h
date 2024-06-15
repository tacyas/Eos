#ifndef LLEXTRACTWITHLAYERSEPARATIONSINGLE_H
#define LLEXTRACTWITHLAYERSEPARATIONSINGLE_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct llExtractWithLayerSeparationSingleInfo {
    long flagRedirect;

    long flagIn;
    char** In;
    char* InList;
    FILE** fptIn;
    FILE* fptInList;
    
    long flagRef;
    char* Ref;
    FILE* fptRef;
    
    long flagOut;
    char** Out;
    char* OutList;
    FILE** fptOut;
    FILE* fptOutList;
    
    long flagphiMin;
    float phiMin;
    
    long flagphiMax;
    float phiMax;
    
    long flagphiDelta;
    float phiDelta;
    
    long flagzMin;
    float zMin;
    
    long flagzMax;
    float zMax;
    
    long flagzDelta;
    float zDelta;
    
    long flagrMin;
    float rMin;
    
    long flagrMax;
    float rMax;
    
    long flagrDelta;
    float rDelta;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} llExtractWithLayerSeparationSingleInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(llExtractWithLayerSeparationSingleInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(llExtractWithLayerSeparationSingleInfo* info);
extern void init1(llExtractWithLayerSeparationSingleInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* LLEXTRACTWITHLAYERSEPARATIONSINGLE_H */
