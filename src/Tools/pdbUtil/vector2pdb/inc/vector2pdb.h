#ifndef VECTOR2PDB_H
#define VECTOR2PDB_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct vector2pdbInfo {
    long flagRedirect;

    long flagvx;
    float vx;
    
    long flagvy;
    float vy;
    
    long flagvz;
    float vz;
    
    long flagphi;
    float phi;
    
    long flagtheta;
    float theta;
    
    long flagzx;
    float zx;
    
    long flagzy;
    float zy;
    
    long flagzz;
    float zz;
    
    long flagxx;
    float xx;
    
    long flagxy;
    float xy;
    
    long flagxz;
    float xz;
    
    long flagsx;
    float sx;
    
    long flagsy;
    float sy;
    
    long flagsz;
    float sz;
    
    long flagstep;
    float step;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagn;
    long n;
    
    long flagID;
    char  ID;
    
    long flagRes;
    char* Res;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} vector2pdbInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(vector2pdbInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(vector2pdbInfo* info);
extern void init1(vector2pdbInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* VECTOR2PDB_H */
