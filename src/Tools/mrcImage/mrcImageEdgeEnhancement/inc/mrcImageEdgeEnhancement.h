#ifndef MRCIMAGEEDGEENHANCEMENT_H
#define MRCIMAGEEDGEENHANCEMENT_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct mrcImageEdgeEnhancementInfo {
    long flagRedirect;

    long flagIn;
    char* In;
    FILE* fptIn;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagOutDirection;
    char* OutDirection;
    FILE* fptOutDirection;
    
    long flagNeighborMode;
    long NeighborMode;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} mrcImageEdgeEnhancementInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(mrcImageEdgeEnhancementInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(mrcImageEdgeEnhancementInfo* info);
extern void init1(mrcImageEdgeEnhancementInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* MRCIMAGEEDGEENHANCEMENT_H */
