#ifndef MRCIMAGEUNEXPECTEDMASSFROMPDB_H
#define MRCIMAGEUNEXPECTEDMASSFROMPDB_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct mrcImageUnexpectedMassFromPDBInfo {
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
    
    long flagThres;
    float Thres;
    
    long flagData;
    float Data;
    
    long flagAtomMode;
    long AtomMode;
    
    long flagradius;
    float radius;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} mrcImageUnexpectedMassFromPDBInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(mrcImageUnexpectedMassFromPDBInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(mrcImageUnexpectedMassFromPDBInfo* info);
extern void init1(mrcImageUnexpectedMassFromPDBInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* MRCIMAGEUNEXPECTEDMASSFROMPDB_H */
