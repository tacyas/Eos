#ifndef LLDATANORMALIZATION_H
#define LLDATANORMALIZATION_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct llDataNormalizationInfo {
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
    
    long flagDif;
    char* Dif;
    FILE* fptDif;
    
    long flagOutParam;
    char* OutParam;
    FILE* fptOutParam;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} llDataNormalizationInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(llDataNormalizationInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(llDataNormalizationInfo* info);
extern void init1(llDataNormalizationInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* LLDATANORMALIZATION_H */
