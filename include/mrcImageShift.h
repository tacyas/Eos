#ifndef MRCIMAGESHIFT_H
#define MRCIMAGESHIFT_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct mrcImageShiftInfo {
    long flagRedirect;

    long flagIn;
    char* In;
    FILE* fptIn;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagxshift;
    float xshift;
    
    long flagyshift;
    float yshift;
    
    long flagzshift;
    float zshift;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} mrcImageShiftInfo;
extern void argCheck(mrcImageShiftInfo* info, int argc, char* avgv[]);
extern void init0(mrcImageShiftInfo* info);
extern void init1(mrcImageShiftInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#endif /* MRCIMAGESHIFT_H */
