#ifndef LLDATAAXISSEARCH_H
#define LLDATAAXISSEARCH_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct llDataAxisSearchInfo {
    long flagRedirect;

    long flagIn1;
    char* In1;
    FILE* fptIn1;
    
    long flagIn2;
    char* In2;
    FILE* fptIn2;
    
    long flagOut1;
    char* Out1;
    FILE* fptOut1;
    
    long flagOut2;
    char* Out2;
    FILE* fptOut2;
    
    long flagAvg;
    char* Avg;
    FILE* fptAvg;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagOutP2;
    char* OutP2;
    FILE* fptOutP2;
    
    long flagtruePitch;
    float truePitch;
    
    long flagL;
    char* L;
    FILE* fptL;
    
    long flagOmin;
    float Omin;
    
    long flagOmax;
    float Omax;
    
    long flagOdelta;
    float Odelta;
    
    long flagxmin;
    float xmin;
    
    long flagxmax;
    float xmax;
    
    long flagxdelta;
    float xdelta;
    
    long flagR;
    float R;
    
    long flagmode;
    long mode;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
} llDataAxisSearchInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(llDataAxisSearchInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(llDataAxisSearchInfo* info);
extern void init1(llDataAxisSearchInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* LLDATAAXISSEARCH_H */
