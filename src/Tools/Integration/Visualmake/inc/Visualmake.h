#ifndef VISUALMAKE_H
#define VISUALMAKE_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct VisualmakeInfo {
    long flagRedirect;

    long flagIn;
    char* In;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} VisualmakeInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(VisualmakeInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(VisualmakeInfo* info);
extern void init1(VisualmakeInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* VISUALMAKE_H */
