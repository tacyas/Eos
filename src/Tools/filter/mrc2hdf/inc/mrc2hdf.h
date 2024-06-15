#ifndef MRC2HDF_H
#define MRC2HDF_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct mrc2hdfInfo {
    long flagRedirect;

    long flagIn;
    char* In;
    FILE* fptIn;
    
    long flagInList;
    char** InList;
    char* InListList;
    FILE** fptInList;
    FILE* fptInListList;
    
    long flagInList2;
    char** InList2;
    char* InList2List;
    FILE** fptInList2;
    FILE* fptInList2List;
    
    long flagIR;
    float IR;
    
    long flagIG;
    float IG;
    
    long flagIB;
    float IB;
    
    long flagIA;
    float IA;
    
    long flagI2R;
    float I2R;
    
    long flagI2G;
    float I2G;
    
    long flagI2B;
    float I2B;
    
    long flagI2A;
    float I2A;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagnResolution;
    long nResolution;
    
    long flaghdf5mode;
    long hdf5mode;
    
    long flagmode;
    long mode;
    
} mrc2hdfInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(mrc2hdfInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(mrc2hdfInfo* info);
extern void init1(mrc2hdfInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* MRC2HDF_H */
