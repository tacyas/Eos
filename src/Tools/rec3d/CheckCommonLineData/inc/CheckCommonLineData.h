#ifndef CHECKCOMMONLINEDATA_H
#define CHECKCOMMONLINEDATA_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct CheckCommonLineDataInfo {
    long flagRedirect;

    long flagIn;
    char** In;
    char* InList;
    FILE** fptIn;
    FILE* fptInList;
    
    long flagOutR;
    char* OutR;
    FILE* fptOutR;
    
    long flagOutI;
    char* OutI;
    FILE* fptOutI;
    
    long flagOutL;
    char* OutL;
    FILE* fptOutL;
    
    long flagOutP;
    char* OutP;
    FILE* fptOutP;
    
    long flagOutLL;
    char* OutLL;
    FILE* fptOutLL;
    
    long flagLog;
    char* Log;
    FILE* fptLog;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} CheckCommonLineDataInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(CheckCommonLineDataInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(CheckCommonLineDataInfo* info);
extern void init1(CheckCommonLineDataInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* CHECKCOMMONLINEDATA_H */
