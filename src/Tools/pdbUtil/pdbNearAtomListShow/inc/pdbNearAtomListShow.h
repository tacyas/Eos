#ifndef PDBNEARATOMLISTSHOW_H
#define PDBNEARATOMLISTSHOW_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct pdbNearAtomListShowInfo {
    long flagRedirect;

    long flagIn;
    char* In;
    FILE* fptIn;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagPx;
    float Px;
    
    long flagPy;
    float Py;
    
    long flagPz;
    float Pz;
    
    long flagMRC;
    char* MRC;
    FILE* fptMRC;
    
    long flagContour;
    float Contour;
    
    long flagdistance;
    float distance;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} pdbNearAtomListShowInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(pdbNearAtomListShowInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(pdbNearAtomListShowInfo* info);
extern void init1(pdbNearAtomListShowInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* PDBNEARATOMLISTSHOW_H */
