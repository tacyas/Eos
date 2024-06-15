#ifndef OBJ3DON2DIMAGEVIEW_H
#define OBJ3DON2DIMAGEVIEW_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct obj3Don2DImageViewInfo {
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
    
    long flagmode;
    long mode;
    
} obj3Don2DImageViewInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(obj3Don2DImageViewInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(obj3Don2DImageViewInfo* info);
extern void init1(obj3Don2DImageViewInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* OBJ3DON2DIMAGEVIEW_H */
