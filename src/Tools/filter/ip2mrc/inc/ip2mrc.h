#ifndef IP2MRC_H
#define IP2MRC_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct ip2mrcInfo {
    long flagRedirect;

    long flagIn;
    char* In;
    FILE* fptIn;
    
    long flagInTem;
    char* InTem;
    FILE* fptInTem;
    
    long flagInInf;
    char* InInf;
    FILE* fptInInf;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagOut2;
    char* Out2;
    FILE* fptOut2;
    
    long flagMag;
    float Mag;
    
    long flagSE;
    float SE;
    
    long flagOutMode;
    long OutMode;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} ip2mrcInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(ip2mrcInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(ip2mrcInfo* info);
extern void init1(ip2mrcInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* IP2MRC_H */
