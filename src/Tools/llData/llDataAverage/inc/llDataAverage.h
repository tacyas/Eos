#ifndef LLDATAAVERAGE_H
#define LLDATAAVERAGE_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct llDataAverageInfo {
    long flagRedirect;

    long flagModel;
    char* Model;
    FILE* fptModel;
    
    long flagIn;
    char** In;
    char* InList;
    FILE** fptIn;
    FILE* fptInList;
    
    long flagllInfo;
    char* llInfo;
    FILE* fptllInfo;
    
    long flagAve;
    char* Ave;
    FILE* fptAve;
    
    long flagOutParam;
    char* OutParam;
    FILE* fptOutParam;
    
    long flagOutParam2;
    char** OutParam2;
    char* OutParam2List;
    FILE** fptOutParam2;
    FILE* fptOutParam2List;
    
    long flagOut;
    char** Out;
    char* OutList;
    FILE** fptOut;
    FILE* fptOutList;
    
    long flagP2;
    char* P2;
    FILE* fptP2;
    
    long flagtruePitch;
    float truePitch;
    
    long flagdR;
    float dR;
    
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
    
    long withoutAntiPole;

    long flagCutValue;
    float CutValue;
    
    long flagpvm;
    long pvm;
    
    long flagpvmList;
    char* pvmList;
    FILE* fptpvmList;
    
    long flagLog;
    char* Log;
    FILE* fptLog;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} llDataAverageInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(llDataAverageInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(llDataAverageInfo* info);
extern void init1(llDataAverageInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* LLDATAAVERAGE_H */
