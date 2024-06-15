#ifndef MRCSINOGRAMFETNORMALIZEDMAP_H
#define MRCSINOGRAMFETNORMALIZEDMAP_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct mrcSinogramFETnormalizedMapInfo {
    long flagRedirect;

    long flagIn;
    char* In;
    FILE* fptIn;
    
    long flagOutFET;
    char* OutFET;
    FILE* fptOutFET;
    
    long flagcomList;
    char* comList;
    FILE* fptcomList;
    
    long flagOutMAP;
    char* OutMAP;
    FILE* fptOutMAP;
    
    long flagWeight;
    char* Weight;
    FILE* fptWeight;
    
    long flagAAtm;
    long AAtm;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} mrcSinogramFETnormalizedMapInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(mrcSinogramFETnormalizedMapInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(mrcSinogramFETnormalizedMapInfo* info);
extern void init1(mrcSinogramFETnormalizedMapInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* MRCSINOGRAMFETNORMALIZEDMAP_H */
