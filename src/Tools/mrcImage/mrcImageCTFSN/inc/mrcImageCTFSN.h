#ifndef MRCIMAGECTFSN_H
#define MRCIMAGECTFSN_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct mrcImageCTFSNInfo {
    long flagRedirect;

    long flagIn;
    char* In;
    FILE* fptIn;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagkV;
    float kV;
    
    long flagCs;
    float Cs;
    
    long flagDefocus;
    float Defocus;
    
    long flagdeg1;
    long deg1;
    
    long flagdeg2;
    long deg2;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} mrcImageCTFSNInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(mrcImageCTFSNInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(mrcImageCTFSNInfo* info);
extern void init1(mrcImageCTFSNInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* MRCIMAGECTFSN_H */
