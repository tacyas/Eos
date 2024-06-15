#ifndef LLEXTRACTCTFINFFILECREATE_H
#define LLEXTRACTCTFINFFILECREATE_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct llExtractCtfinfFileCreateInfo {
    long flagRedirect;

    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagFirstZero;
    float FirstZero;
    
    long flagDefocus;
    float Defocus;
    
    long flagAoverP;
    float AoverP;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} llExtractCtfinfFileCreateInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(llExtractCtfinfFileCreateInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(llExtractCtfinfFileCreateInfo* info);
extern void init1(llExtractCtfinfFileCreateInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* LLEXTRACTCTFINFFILECREATE_H */
