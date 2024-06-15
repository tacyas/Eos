#ifndef PDBHELIX_H
#define PDBHELIX_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct pdbHelixInfo {
    long flagRedirect;

    long flagIn;
    char* In;
    FILE* fptIn;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagOut3D;
    char* Out3D;
    FILE* fptOut3D;
    
    long flagOut2D;
    char* Out2D;
    FILE* fptOut2D;
    
    long flagdelta;
    float delta;
    
    long flagdelphi;
    float delphi;
    
    long flagdeldelphi;
    float deldelphi;
    
    long flagdelz;
    float delz;
    
    long flagnMolecule;
    long nMolecule;
    
    long flagnx;
    long nx;
    
    long flagny;
    long ny;
    
    long flagnz;
    long nz;
    
    long flagStartx;
    float Startx;
    
    long flagStarty;
    float Starty;
    
    long flagStartz;
    float Startz;
    
    long flagWeight;
    float Weight;
    
    long flagdx;
    float dx;
    
    long flagdy;
    float dy;
    
    long flagdz;
    float dz;
    
    long flagstartn;
    long startn;
    
    long flagstartID;
    char  startID;
    
    long flagdeltaSeq;
    long deltaSeq;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} pdbHelixInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(pdbHelixInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(pdbHelixInfo* info);
extern void init1(pdbHelixInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* PDBHELIX_H */
