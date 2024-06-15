#ifndef CTFDISPLAY_H
#define CTFDISPLAY_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct ctfDisplayInfo {
    long flagRedirect;

    long flaginMRC;
    char* inMRC;
    FILE* fptinMRC;
    
    long flagoutCTF;
    char* outCTF;
    FILE* fptoutCTF;
    
    long flagRmax;
    float Rmax;
    
    long flagImax;
    float Imax;
    
    long flagImin;
    float Imin;
    
    long AutoRange;

    long Log;

    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} ctfDisplayInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(ctfDisplayInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(ctfDisplayInfo* info);
extern void init1(ctfDisplayInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* CTFDISPLAY_H */
