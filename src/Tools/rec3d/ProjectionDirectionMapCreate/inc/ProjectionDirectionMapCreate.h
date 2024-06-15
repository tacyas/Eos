#ifndef PROJECTIONDIRECTIONMAPCREATE_H
#define PROJECTIONDIRECTIONMAPCREATE_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct ProjectionDirectionMapCreateInfo {
    long flagRedirect;

    long flagIn;
    char* In;
    FILE* fptIn;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagPs;
    char* Ps;
    FILE* fptPs;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
    long flagRmode;
    long Rmode;
    
} ProjectionDirectionMapCreateInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(ProjectionDirectionMapCreateInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(ProjectionDirectionMapCreateInfo* info);
extern void init1(ProjectionDirectionMapCreateInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* PROJECTIONDIRECTIONMAPCREATE_H */
