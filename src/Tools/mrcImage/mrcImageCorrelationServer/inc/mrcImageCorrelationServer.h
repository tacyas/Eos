#ifndef MRCIMAGECORRELATIONSERVER_H
#define MRCIMAGECORRELATIONSERVER_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct mrcImageCorrelationServerInfo {
    long flagRedirect;

    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} mrcImageCorrelationServerInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(mrcImageCorrelationServerInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(mrcImageCorrelationServerInfo* info);
extern void init1(mrcImageCorrelationServerInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* MRCIMAGECORRELATIONSERVER_H */
