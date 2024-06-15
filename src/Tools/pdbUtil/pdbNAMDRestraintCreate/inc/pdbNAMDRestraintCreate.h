#ifndef PDBNAMDRESTRAINTCREATE_H
#define PDBNAMDRESTRAINTCREATE_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct pdbNAMDRestraintCreateInfo {
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
    
    long flagOut2;
    char* Out2;
    FILE* fptOut2;
    
    long flagKf;
    float Kf;
    
    long flagAutoKf;
    float AutoKf;
    
    long flagSegName;
    char* SegName;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} pdbNAMDRestraintCreateInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(pdbNAMDRestraintCreateInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(pdbNAMDRestraintCreateInfo* info);
extern void init1(pdbNAMDRestraintCreateInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* PDBNAMDRESTRAINTCREATE_H */
