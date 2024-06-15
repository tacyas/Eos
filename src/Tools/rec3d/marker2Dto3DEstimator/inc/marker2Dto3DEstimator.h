#ifndef MARKER2DTO3DESTIMATOR_H
#define MARKER2DTO3DESTIMATOR_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct marker2Dto3DEstimatorInfo {
    long flagRedirect;

    long flagIn;
    char** In;
    char* InList;
    FILE** fptIn;
    FILE* fptInList;
    
    long flagInType;
    long InType;
    
    long flagOut;
    char** Out;
    char* OutList;
    FILE** fptOut;
    FILE* fptOutList;
    
    long flagOutType;
    long OutType;
    
    long flagOutEA;
    char** OutEA;
    char* OutEAList;
    FILE** fptOutEA;
    FILE* fptOutEAList;
    
    long flagZeroPlane;
    long ZeroPlane;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} marker2Dto3DEstimatorInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(marker2Dto3DEstimatorInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(marker2Dto3DEstimatorInfo* info);
extern void init1(marker2Dto3DEstimatorInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* MARKER2DTO3DESTIMATOR_H */
