#ifndef MRCIMAGEOPTICALFLOW_H
#define MRCIMAGEOPTICALFLOW_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct mrcImageOpticalFlowInfo {
    long flagRedirect;

    long flagIn1;
    char* In1;
    FILE* fptIn1;
    
    long flagIn2;
    char* In2;
    FILE* fptIn2;
    
    long flagIn3;
    char* In3;
    FILE* fptIn3;
    
    long flagVx;
    char* Vx;
    FILE* fptVx;
    
    long flagVy;
    char* Vy;
    FILE* fptVy;
    
    long flagVz;
    char* Vz;
    FILE* fptVz;
    
    long flagOutFx;
    char* OutFx;
    FILE* fptOutFx;
    
    long flagOutFy;
    char* OutFy;
    FILE* fptOutFy;
    
    long flagOutFz;
    char* OutFz;
    FILE* fptOutFz;
    
    long flagOutDi;
    char* OutDi;
    FILE* fptOutDi;
    
    long flagSize;
    char* Size;
    FILE* fptSize;
    
    long flagOutCOMMAND;
    char* OutCOMMAND;
    FILE* fptOutCOMMAND;
    
    long flagOutBILD;
    char* OutBILD;
    FILE* fptOutBILD;
    
    long flagBG;
    float BG;
    
    long flagBildThresLow;
    float BildThresLow;
    
    long flagBildThresHigh;
    float BildThresHigh;
    
    long flagBildRangeLow;
    float BildRangeLow;
    
    long flagBildRangeHigh;
    float BildRangeHigh;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} mrcImageOpticalFlowInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(mrcImageOpticalFlowInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(mrcImageOpticalFlowInfo* info);
extern void init1(mrcImageOpticalFlowInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* MRCIMAGEOPTICALFLOW_H */
