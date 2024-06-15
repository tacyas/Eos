#ifndef PDBSURFACE_H
#define PDBSURFACE_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct pdbSurfaceInfo {
    long flagRedirect;

    long flagIn;
    char* In;
    FILE* fptIn;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagorder;
    float order;
    
    long flagrefine;
    long refine;
    
    long flagsize;
    long size;
    
    long flagweight;
    float weight;
    
    long flagmergin;
    float mergin;
    
    long flagthresHold;
    float thresHold;
    
    long flagDensityMode;
    long DensityMode;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} pdbSurfaceInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(pdbSurfaceInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(pdbSurfaceInfo* info);
extern void init1(pdbSurfaceInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* PDBSURFACE_H */
