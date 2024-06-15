#ifndef HF2000INIT_H
#define HF2000INIT_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct hf2000InitInfo {
    long flagRedirect;

    long flagtty;
    char* tty;
    
    long flagspeed;
    long speed;
    
    long flagHost;
    char* Host;
    
    long flagServer;
    long Server;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} hf2000InitInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(hf2000InitInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(hf2000InitInfo* info);
extern void init1(hf2000InitInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* HF2000INIT_H */
