#ifndef MRCIMAGE3DCTFOBSERVATION_H
#define MRCIMAGE3DCTFOBSERVATION_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct mrcImage3DCTFObservationInfo {
    long flagRedirect;

    long flagIn;
    char* In;
    FILE* fptIn;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagIn;
    char* In;
    FILE* fptIn;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} mrcImage3DCTFObservationInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(mrcImage3DCTFObservationInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(mrcImage3DCTFObservationInfo* info);
extern void init1(mrcImage3DCTFObservationInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* MRCIMAGE3DCTFOBSERVATION_H */
