#ifndef MRCIMAGETILTAXISSEARCH_H
#define MRCIMAGETILTAXISSEARCH_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct mrcImageTiltAxisSearchInfo {
    long flagRedirect;

    long flagIn;
    char* In;
    FILE* fptIn;
    
    long flagInList;
    char** InList;
    char* InListList;
    FILE** fptInList;
    FILE* fptInListList;
    
    long flagRef;
    char* Ref;
    FILE* fptRef;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagOut2;
    char* Out2;
    FILE* fptOut2;
    
    long flagthetaMin;
    float thetaMin;
    
    long flagthetaMax;
    float thetaMax;
    
    long flagthetaDelta;
    float thetaDelta;
    
    long flagWidth;
    float Width;
    
    long flagMode;
    long Mode;
    
    long flagCorrelationMode;
    long CorrelationMode;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} mrcImageTiltAxisSearchInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(mrcImageTiltAxisSearchInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(mrcImageTiltAxisSearchInfo* info);
extern void init1(mrcImageTiltAxisSearchInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* MRCIMAGETILTAXISSEARCH_H */
