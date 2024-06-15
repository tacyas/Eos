#ifndef CLUSTERLOGASCII2BINARY_H
#define CLUSTERLOGASCII2BINARY_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct clusterLogASCII2BinaryInfo {
    long flagRedirect;

    long flagIn;
    char* In;
    FILE* fptIn;
    
    long flagOut;
    char* Out;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} clusterLogASCII2BinaryInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(clusterLogASCII2BinaryInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(clusterLogASCII2BinaryInfo* info);
extern void init1(clusterLogASCII2BinaryInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* CLUSTERLOGASCII2BINARY_H */
