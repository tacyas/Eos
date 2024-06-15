#ifndef DISPLAY3_H
#define DISPLAY3_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct Display3Info {
    long flagRedirect;

    long flagIn;
    char* In;
    FILE* fptIn;
    
    long flagIn2;
    char** In2;
    char* In2List;
    FILE** fptIn2;
    FILE* fptIn2List;
    
    long flagContour;
    float Contour;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
} Display3Info;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(Display3Info* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(Display3Info* info);
extern void init1(Display3Info* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* DISPLAY3_H */
