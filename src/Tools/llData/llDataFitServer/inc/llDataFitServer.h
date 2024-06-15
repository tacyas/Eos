#ifndef LLDATAFITSERVER_H
#define LLDATAFITSERVER_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct llDataFitServerInfo {
    long flagRedirect;

    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} llDataFitServerInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(llDataFitServerInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(llDataFitServerInfo* info);
extern void init1(llDataFitServerInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* LLDATAFITSERVER_H */
