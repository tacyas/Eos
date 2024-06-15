#ifndef MRCIMAGECONNECTION_H
#define MRCIMAGECONNECTION_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct mrcImageConnectionInfo {
    long flagRedirect;

    long flagIn1;
    char* In1;
    FILE* fptIn1;
    
    long flagIn2;
    char* In2;
    FILE* fptIn2;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} mrcImageConnectionInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(mrcImageConnectionInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(mrcImageConnectionInfo* info);
extern void init1(mrcImageConnectionInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* MRCIMAGECONNECTION_H */
