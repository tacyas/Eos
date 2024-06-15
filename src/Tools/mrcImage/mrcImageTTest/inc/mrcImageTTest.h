#ifndef MRCIMAGETTEST_H
#define MRCIMAGETTEST_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct mrcImageTTestInfo {
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
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagOutT;
    char* OutT;
    FILE* fptOutT;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} mrcImageTTestInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(mrcImageTTestInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(mrcImageTTestInfo* info);
extern void init1(mrcImageTTestInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* MRCIMAGETTEST_H */
