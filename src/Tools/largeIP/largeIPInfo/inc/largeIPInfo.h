#ifndef LARGEIPINFO_H
#define LARGEIPINFO_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct largeIPInfoInfo {
    long flagRedirect;

    long flagIn;
    char* In;
    FILE* fptIn;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagstartx;
    long startx;
    
    long flagstarty;
    long starty;
    
    long flagstepx;
    long stepx;
    
    long flagstepy;
    long stepy;
    
    long flagwidth;
    long width;
    
    long flagheight;
    long height;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} largeIPInfoInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(largeIPInfoInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(largeIPInfoInfo* info);
extern void init1(largeIPInfoInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* LARGEIPINFO_H */
