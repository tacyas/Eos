#ifndef MRCIMAGEORIENTATIONSEARCHBYSIMULTANEOUSMINIMIZATION_H
#define MRCIMAGEORIENTATIONSEARCHBYSIMULTANEOUSMINIMIZATION_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct mrcImageOrientationSearchBySimultaneousMinimizationInfo {
    long flagRedirect;

    long flagIn;
    char** In;
    char* InList;
    FILE** fptIn;
    FILE* fptInList;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
    long flagdtheta;
    float dtheta;
    
    long flagdpsi;
    float dpsi;
    
    long flagms;
    long ms;
    
    long flagird;
    long ird;
    
    long flagMC;
    long MC;
    
    long flagFileNameHeader;
    char* FileNameHeader;
    
    long flagmid;
    long mid;
    
    long flagInInitial;
    char* InInitial;
    FILE* fptInInitial;
    
    long flagmsp;
    long msp;
    
    long flagmaa;
    long maa;
    
    long flagpdtheta;
    long pdtheta;
    
    long flagpdpsi;
    long pdpsi;
    
    long flagmodeL;
    long modeL;
    
    long flagmodeTA;
    long modeTA;
    
    long flagmodeCA;
    long modeCA;
    
    long flagTCA;
    float TCA;
    
    long flagmodeF;
    long modeF;
    
} mrcImageOrientationSearchBySimultaneousMinimizationInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(mrcImageOrientationSearchBySimultaneousMinimizationInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(mrcImageOrientationSearchBySimultaneousMinimizationInfo* info);
extern void init1(mrcImageOrientationSearchBySimultaneousMinimizationInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* MRCIMAGEORIENTATIONSEARCHBYSIMULTANEOUSMINIMIZATION_H */
