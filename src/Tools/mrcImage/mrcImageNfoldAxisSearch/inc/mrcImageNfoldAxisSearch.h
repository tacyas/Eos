#ifndef MRCIMAGENFOLDAXISSEARCH_H
#define MRCIMAGENFOLDAXISSEARCH_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct mrcImageNfoldAxisSearchInfo {
    long flagRedirect;

    long flagIn;
    char* In;
    FILE* fptIn;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagOut2;
    char* Out2;
    FILE* fptOut2;
    
    long flagRes;
    char* Res;
    FILE* fptRes;
    
    long flagnFold;
    long nFold;
    
    long flagdelPHI;
    float delPHI;
    
    long flagminx;
    float minx;
    
    long flagmaxx;
    float maxx;
    
    long flagdelx;
    float delx;
    
    long flagminy;
    float miny;
    
    long flagmaxy;
    float maxy;
    
    long flagdely;
    float dely;
    
    long flagminz;
    float minz;
    
    long flagmaxz;
    float maxz;
    
    long flagdelz;
    float delz;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} mrcImageNfoldAxisSearchInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(mrcImageNfoldAxisSearchInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(mrcImageNfoldAxisSearchInfo* info);
extern void init1(mrcImageNfoldAxisSearchInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* MRCIMAGENFOLDAXISSEARCH_H */
