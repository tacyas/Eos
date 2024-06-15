#ifndef PDBMOLECULARINTERFACEFIND_H
#define PDBMOLECULARINTERFACEFIND_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct pdbMolecularInterfaceFindInfo {
    long flagRedirect;

    long flagIn;
    char* In;
    FILE* fptIn;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagID1;
    char  ID1;
    
    long flagID2;
    char  ID2;
    
    long flagd;
    float d;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} pdbMolecularInterfaceFindInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(pdbMolecularInterfaceFindInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(pdbMolecularInterfaceFindInfo* info);
extern void init1(pdbMolecularInterfaceFindInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* PDBMOLECULARINTERFACEFIND_H */
