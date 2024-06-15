#ifndef MRCIMAGERECTANGLEGET_H
#define MRCIMAGERECTANGLEGET_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct mrcImageRectangleGetInfo {
    long flagRedirect;

    long flagIn;
    char* In;
    FILE* fptIn;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagblx;
    long blx;
    
    long flagbly;
    long bly;
    
    long flagtrx;
    long trx;
    
    long flagtry;
    long try;
    
    long flagmode;
    long mode;
    
} mrcImageRectangleGetInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(mrcImageRectangleGetInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(mrcImageRectangleGetInfo* info);
extern void init1(mrcImageRectangleGetInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* MRCIMAGERECTANGLEGET_H */
