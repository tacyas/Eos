#ifndef MRCIMAGEAUTOROTATIONCORRELATION_H
#define MRCIMAGEAUTOROTATIONCORRELATION_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct mrcImageAutoRotationCorrelationInfo {
    long flagRedirect;

    long flagIn;
    char* In;
    FILE* fptIn;
    
    long flagRef;
    char* Ref;
    FILE* fptRef;
    
    long flagnRot1;
    long nRot1;
    
    long flagnRot2;
    long nRot2;
    
    long flagnRot3;
    long nRot3;
    
    long flagdRot1;
    float dRot1;
    
    long flagdRot2;
    float dRot2;
    
    long flagdRot3;
    float dRot3;
    
    long flagstartRot1;
    float startRot1;
    
    long flagstartRot2;
    float startRot2;
    
    long flagstartRot3;
    float startRot3;
    
    long flagStackOrder;
    long StackOrder;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagOutASC;
    char* OutASC;
    FILE* fptOutASC;
    
    long flagcorFile;
    char* corFile;
    FILE* fptcorFile;
    
    long flagcorFile2;
    char* corFile2;
    FILE* fptcorFile2;
    
    long flagcorAllFile;
    char* corAllFile;
    FILE* fptcorAllFile;
    
    long flagfitFile;
    char* fitFile;
    FILE* fptfitFile;
    
    long flagfitFile2;
    char* fitFile2;
    FILE* fptfitFile2;
    
    long flagRefineMode;
    long RefineMode;
    
    long flagRot;
    float Rot;
    
    long flagminAngle;
    float minAngle;
    
    long flagmaxAngle;
    float maxAngle;
    
    long flagrefStep1;
    long refStep1;
    
    long flagrefStep2;
    long refStep2;
    
    long flagrefStep3;
    long refStep3;
    
    long flagnRot1AreaMin;
    float nRot1AreaMin;
    
    long flagnRot1AreaMax;
    float nRot1AreaMax;
    
    long flagnRot1AreaStep;
    float nRot1AreaStep;
    
    long flagnRot2AreaMin;
    float nRot2AreaMin;
    
    long flagnRot2AreaMax;
    float nRot2AreaMax;
    
    long flagnRot2AreaStep;
    float nRot2AreaStep;
    
    long flagnRot3AreaMin;
    float nRot3AreaMin;
    
    long flagnRot3AreaMax;
    float nRot3AreaMax;
    
    long flagnRot3AreaStep;
    float nRot3AreaStep;
    
    long flagMagRangeMin;
    float MagRangeMin;
    
    long flagMagRangeMax;
    float MagRangeMax;
    
    long flagMagRangeStep;
    float MagRangeStep;
    
    long flagIter;
    long Iter;
    
    long flagMethod;
    long Method;
    
    long flagsminx;
    float sminx;
    
    long flagsminy;
    float sminy;
    
    long flagsmaxx;
    float smaxx;
    
    long flagsmaxy;
    float smaxy;
    
    long Shift;

    long flagRepeatX;
    float RepeatX;
    
    long flagRepeatXDelta;
    float RepeatXDelta;
    
    long flagRepeatY;
    float RepeatY;
    
    long flagRepeatYDelta;
    float RepeatYDelta;
    
    long Xshift;

    long NoShift;

    long flagLog;
    char* Log;
    FILE* fptLog;
    
    long flagpvm;
    long pvm;
    
    long flagpvmList;
    char* pvmList;
    FILE* fptpvmList;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} mrcImageAutoRotationCorrelationInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(mrcImageAutoRotationCorrelationInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(mrcImageAutoRotationCorrelationInfo* info);
extern void init1(mrcImageAutoRotationCorrelationInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* MRCIMAGEAUTOROTATIONCORRELATION_H */
