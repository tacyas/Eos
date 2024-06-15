#ifndef MALLOCCHECK_H
#define MALLOCCHECK_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct mallocCheckInfo {
    long flagRedirect;

    long flagbyte;
    long byte;
    
    long flagitem;
    long item;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} mallocCheckInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(mallocCheckInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(mallocCheckInfo* info);
extern void init1(mallocCheckInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* MALLOCCHECK_H */
