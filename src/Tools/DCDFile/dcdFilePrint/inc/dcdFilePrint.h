#ifndef DCDFILEPRINT_H
#define DCDFILEPRINT_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct dcdFilePrintInfo {
    long flagRedirect;

    long flagIn;
    char* In;
    FILE* fptIn;
    
    long flagInPDB;
    char* InPDB;
    FILE* fptInPDB;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagOutPDB;
    char* OutPDB;
    FILE* fptOutPDB;
    
    long flagrStart;
    long rStart;
    
    long flagrEnd;
    long rEnd;
    
    long flagrDelta;
    long rDelta;
    
    long flagStart;
    long Start;
    
    long flagEnd;
    long End;
    
    long flagDelta;
    long Delta;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} dcdFilePrintInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(dcdFilePrintInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(dcdFilePrintInfo* info);
extern void init1(dcdFilePrintInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* DCDFILEPRINT_H */
