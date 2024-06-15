#ifndef MRC2DFTTO3DFT_H
#define MRC2DFTTO3DFT_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct mrc2DFTto3DFTInfo {
    long flagRedirect;

    long flagIn;
    char** In;
    char* InList;
    FILE** fptIn;
    FILE* fptInList;
    
    long flagtemp3d;
    char* temp3d;
    FILE* fpttemp3d;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagInterpMode;
    long InterpMode;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} mrc2DFTto3DFTInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(mrc2DFTto3DFTInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(mrc2DFTto3DFTInfo* info);
extern void init1(mrc2DFTto3DFTInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* MRC2DFTTO3DFT_H */
