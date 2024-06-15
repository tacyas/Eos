#ifndef MRCIMAGEROITOPCAOUTPUTIMAGE_H
#define MRCIMAGEROITOPCAOUTPUTIMAGE_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct mrcImageROItoPCAoutputImageInfo {
    long flagRedirect;

    long flagInList;
    char** InList;
    char* InListList;
    FILE** fptInList;
    FILE* fptInListList;
    
    long flagOutList;
    char** OutList;
    char* OutListList;
    FILE** fptOutList;
    FILE* fptOutListList;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} mrcImageROItoPCAoutputImageInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(mrcImageROItoPCAoutputImageInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(mrcImageROItoPCAoutputImageInfo* info);
extern void init1(mrcImageROItoPCAoutputImageInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* MRCIMAGEROITOPCAOUTPUTIMAGE_H */
