#ifndef CALCCOMMONLINE_H
#define CALCCOMMONLINE_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct calcCommonLineInfo {
    long flagRedirect;

    long flagIn;
    char* In;
    FILE* fptIn;
    
    long flagEMode1;
    char* EMode1;
    
    long flagRot1_1;
    float Rot1_1;
    
    long flagRot1_2;
    float Rot1_2;
    
    long flagRot1_3;
    float Rot1_3;
    
    long flagEMode2;
    char* EMode2;
    
    long flagRot2_1;
    float Rot2_1;
    
    long flagRot2_2;
    float Rot2_2;
    
    long flagRot2_3;
    float Rot2_3;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} calcCommonLineInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(calcCommonLineInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(calcCommonLineInfo* info);
extern void init1(calcCommonLineInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* CALCCOMMONLINE_H */
