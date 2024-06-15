#ifndef LLDATAMULTICTFCOMPENSATION_H
#define LLDATAMULTICTFCOMPENSATION_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct llDataMultiCTFCompensationInfo {
    long flagRedirect;

    long flagIn;
    char** In;
    char* InList;
    FILE** fptIn;
    FILE* fptInList;
    
    long flagRef;
    char* Ref;
    FILE* fptRef;
    
    long flagllInfo;
    char* llInfo;
    FILE* fptllInfo;
    
    long flagAve;
    char* Ave;
    FILE* fptAve;
    
    long flagOutParam;
    char* OutParam;
    FILE* fptOutParam;
    
    long flagOut;
    char** Out;
    char* OutList;
    FILE** fptOut;
    FILE* fptOutList;
    
    long flagOutParam2;
    char** OutParam2;
    char* OutParam2List;
    FILE** fptOutParam2;
    FILE* fptOutParam2List;
    
    long flagOutParamP2;
    char* OutParamP2;
    FILE* fptOutParamP2;
    
    long flagNoise;
    float Noise;
    
    long flagtruePitch;
    float truePitch;
    
    long flagdeltaR;
    float deltaR;
    
    long flagrmin;
    float rmin;
    
    long flagrmax;
    float rmax;
    
    long flagdr;
    float dr;
    
    long flagphimin;
    float phimin;
    
    long flagphimax;
    float phimax;
    
    long flagdphi;
    float dphi;
    
    long flagzmin;
    float zmin;
    
    long flagzmax;
    float zmax;
    
    long flagdz;
    float dz;
    
    long flagRmax;
    float Rmax;
    
    long flagMaxIter;
    long MaxIter;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} llDataMultiCTFCompensationInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(llDataMultiCTFCompensationInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(llDataMultiCTFCompensationInfo* info);
extern void init1(llDataMultiCTFCompensationInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* LLDATAMULTICTFCOMPENSATION_H */
