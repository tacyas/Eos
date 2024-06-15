#ifndef PDBATOMSECTION_H
#define PDBATOMSECTION_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct pdbAtomSectionInfo {
    long flagRedirect;

    long flagIn;
    char* In;
    FILE* fptIn;
    
    long flagInFlags;
    char* InFlags;
    FILE* fptInFlags;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagdistance;
    float distance;
    
    long flagzmin;
    float zmin;
    
    long flagzmax;
    float zmax;
    
    long flagflagMode;
    long flagMode;
    
    long flagradius;
    float radius;
    
    long flagclinewidth;
    float clinewidth;
    
    long flagplinewidth;
    float plinewidth;
    
    long flagfontsize;
    float fontsize;
    
    long flagscale;
    float scale;
    
    long flagshiftx;
    float shiftx;
    
    long flagshifty;
    float shifty;
    
    long flagshiftz;
    float shiftz;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} pdbAtomSectionInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(pdbAtomSectionInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(pdbAtomSectionInfo* info);
extern void init1(pdbAtomSectionInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* PDBATOMSECTION_H */
