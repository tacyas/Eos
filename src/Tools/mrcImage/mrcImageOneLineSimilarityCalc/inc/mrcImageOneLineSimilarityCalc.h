#ifndef MRCIMAGEONELINESIMILARITYCALC_H
#define MRCIMAGEONELINESIMILARITYCALC_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct mrcImageOneLineSimilarityCalcInfo {
    long flagRedirect;

    long flagIn1;
    char* In1;
    FILE* fptIn1;
    
    long flagIn2;
    char* In2;
    FILE* fptIn2;
    
    long flagshiftflag;
    long shiftflag;
    
    long flagvalue;
    long value;
    
    long flagmethodmode;
    long methodmode;
    
} mrcImageOneLineSimilarityCalcInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(mrcImageOneLineSimilarityCalcInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(mrcImageOneLineSimilarityCalcInfo* info);
extern void init1(mrcImageOneLineSimilarityCalcInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* MRCIMAGEONELINESIMILARITYCALC_H */
