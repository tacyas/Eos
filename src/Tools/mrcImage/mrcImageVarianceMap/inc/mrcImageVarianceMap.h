#ifndef MRCIMAGEVARIANCEMAP_H
#define MRCIMAGEVARIANCEMAP_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct mrcImageVarianceMapInfo {
    long flagRedirect;

    long flagIn;
    char** In;
    char* InList;
    FILE** fptIn;
    FILE* fptInList;
    
    long flagIn2;
    char* In2;
    FILE* fptIn2;
    
    long flagIn2Var;
    char* In2Var;
    FILE* fptIn2Var;
    
    long flagIn2N;
    long In2N;
    
    long flagNorA;
    float NorA;
    
    long flagNorB;
    float NorB;
    
    long flagRef;
    char** Ref;
    char* RefList;
    FILE** fptRef;
    FILE* fptRefList;
    
    long flagRef2;
    char* Ref2;
    FILE* fptRef2;
    
    long flagRef2Var;
    char* Ref2Var;
    FILE* fptRef2Var;
    
    long flagRef2N;
    long Ref2N;
    
    long flagNorARef;
    float NorARef;
    
    long flagNorBRef;
    float NorBRef;
    
    long flagInAndRef2;
    char* InAndRef2;
    FILE* fptInAndRef2;
    
    long flagInAndRef2Var;
    char* InAndRef2Var;
    FILE* fptInAndRef2Var;
    
    long flagInAndRef2N;
    long InAndRef2N;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagOutV;
    char* OutV;
    FILE* fptOutV;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} mrcImageVarianceMapInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(mrcImageVarianceMapInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(mrcImageVarianceMapInfo* info);
extern void init1(mrcImageVarianceMapInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* MRCIMAGEVARIANCEMAP_H */
