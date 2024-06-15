#ifndef MRCIMAGEASSIGNEDTOTFOFPDB_H
#define MRCIMAGEASSIGNEDTOTFOFPDB_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct mrcImageAssignedToTFofPDBInfo {
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
    
    long flagHighLevel;
    float HighLevel;
    
    long flagLowLevel;
    float LowLevel;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} mrcImageAssignedToTFofPDBInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(mrcImageAssignedToTFofPDBInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(mrcImageAssignedToTFofPDBInfo* info);
extern void init1(mrcImageAssignedToTFofPDBInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* MRCIMAGEASSIGNEDTOTFOFPDB_H */
