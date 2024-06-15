#ifndef DISPLAY2_H
#define DISPLAY2_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct Display2Info {
    long flagRedirect;

    long flagIn;
    char* In;
    FILE* fptIn;
    
    long flagTemplate;
    char* Template;
    
    long flagThresHigh;
    float ThresHigh;
    
    long flagThresLow;
    float ThresLow;
    
    long flagZoom;
    float Zoom;
    
    long Inverse;

    long flagOut;
    char* Out;
    
    long flagDefault;
    char* Default;
    
    long flaggeometry;
    char* geometry;
    
    long flagdisplay;
    char* display;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} Display2Info;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(Display2Info* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(Display2Info* info);
extern void init1(Display2Info* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* DISPLAY2_H */
