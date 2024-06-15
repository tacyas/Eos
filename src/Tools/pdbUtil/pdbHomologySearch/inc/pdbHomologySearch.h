#ifndef PDBHOMOLOGYSEARCH_H
#define PDBHOMOLOGYSEARCH_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct pdbHomologySearchInfo {
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
    
    long flagOutMat;
    char* OutMat;
    FILE* fptOutMat;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} pdbHomologySearchInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(pdbHomologySearchInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(pdbHomologySearchInfo* info);
extern void init1(pdbHomologySearchInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* PDBHOMOLOGYSEARCH_H */
