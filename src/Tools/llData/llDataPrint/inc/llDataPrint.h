#ifndef LLDATAPRINT_H
#define LLDATAPRINT_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct llDataPrintInfo {
    long flagRedirect;

    long flagIn;
    char* In;
    FILE* fptIn;
    
    long flagIns;
    char** Ins;
    char* InsList;
    FILE** fptIns;
    FILE* fptInsList;
    
    long flagNea;
    char* Nea;
    FILE* fptNea;
    
    long flagFar;
    char* Far;
    FILE* fptFar;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagRmax;
    float Rmax;
    
    long Interactive;

    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} llDataPrintInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(llDataPrintInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(llDataPrintInfo* info);
extern void init1(llDataPrintInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* LLDATAPRINT_H */
