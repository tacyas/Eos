#ifndef HF2000LENZCURRENT_H
#define HF2000LENZCURRENT_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct hf2000LenzCurrentInfo {
    long flagRedirect;

    long flagIn;
    char* In;
    FILE* fptIn;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagtty;
    char* tty;
    
    long flagspeed;
    long speed;
    
    long flagwhich;
    char* which;
    
    long flagInteractive;
    long Interactive;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} hf2000LenzCurrentInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(hf2000LenzCurrentInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(hf2000LenzCurrentInfo* info);
extern void init1(hf2000LenzCurrentInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* HF2000LENZCURRENT_H */
