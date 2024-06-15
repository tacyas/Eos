#ifndef LLEXTRACTWITHLAYERSEPARATION_H
#define LLEXTRACTWITHLAYERSEPARATION_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct llExtractWithLayerSeparationInfo {
    long flagRedirect;

    long flagIn;
    char** In;
    char* InList;
    FILE** fptIn;
    FILE* fptInList;
    
    long flagInLLNea;
    char** InLLNea;
    char* InLLNeaList;
    FILE** fptInLLNea;
    FILE* fptInLLNeaList;
    
    long flagInLLFar;
    char** InLLFar;
    char* InLLFarList;
    FILE** fptInLLFar;
    FILE* fptInLLFarList;
    
    long flagRef;
    char* Ref;
    FILE* fptRef;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagOut2;
    char** Out2;
    char* Out2List;
    FILE** fptOut2;
    FILE* fptOut2List;
    
    long flagOut3;
    char** Out3;
    char* Out3List;
    FILE** fptOut3;
    FILE* fptOut3List;
    
    long flagOut4;
    char** Out4;
    char* Out4List;
    FILE** fptOut4;
    FILE* fptOut4List;
    
    long flagOut5;
    char** Out5;
    char* Out5List;
    FILE** fptOut5;
    FILE* fptOut5List;
    
    long flagOut6;
    char** Out6;
    char* Out6List;
    FILE** fptOut6;
    FILE* fptOut6List;
    
    long flagOut7;
    char* Out7;
    FILE* fptOut7;
    
    long flagOut8;
    char* Out8;
    FILE* fptOut8;
    
    long flagOut9;
    char** Out9;
    char* Out9List;
    FILE** fptOut9;
    FILE* fptOut9List;
    
    long flagInComment;
    char* InComment;
    
    long flagsymmetry;
    float symmetry;
    
    long flagllInfo;
    char** llInfo;
    char* llInfoList;
    FILE** fptllInfo;
    FILE* fptllInfoList;
    
    long flagllInfoFinal;
    char* llInfoFinal;
    FILE* fptllInfoFinal;
    
    long flagllInfoImp;
    char** llInfoImp;
    char* llInfoImpList;
    FILE** fptllInfoImp;
    FILE* fptllInfoImpList;
    
    long flagliWeight;
    float liWeight;
    
    long flagliWeightStart;
    float liWeightStart;
    
    long flagliWeightStep;
    float liWeightStep;
    
    long flagllInfoAxis;
    char** llInfoAxis;
    char* llInfoAxisList;
    FILE** fptllInfoAxis;
    FILE* fptllInfoAxisList;
    
    long flaglaWeight;
    float laWeight;
    
    long flaglaWeightStart;
    float laWeightStart;
    
    long flaglaWeightStep;
    float laWeightStep;
    
    long flagtruePitch;
    float truePitch;
    
    long flagrMax;
    float rMax;
    
    long flagrMaxMin;
    float rMaxMin;
    
    long flagRMax;
    float RMax;
    
    long flagRMaxFirst;
    float RMaxFirst;
    
    long flagRMaxStep;
    float RMaxStep;
    
    long flagRRMax;
    float RRMax;
    
    long flagRRMaxFirst;
    float RRMaxFirst;
    
    long flagRRMaxStep;
    float RRMaxStep;
    
    long flagdelBR;
    float delBR;
    
    long flagrms;
    float rms;
    
    long flagnarrowSearch;
    float narrowSearch;
    
    long flagnextTimes;
    float nextTimes;
    
    long flagMaxIteration;
    long MaxIteration;
    
    long flagMaxIter2;
    long MaxIter2;
    
    long flagMaxIter3;
    long MaxIter3;
    
    long flaglambda;
    float lambda;
    
    long flagCTF;
    long CTF;
    
    long flagWhiteNoise;
    float WhiteNoise;
    
    long flagbelow;
    float below;
    
    long noantipole;

    long magLimit;

    long eachTime;

    long flagContinue;
    char* Continue;
    FILE* fptContinue;
    
    long flagForContinue;
    char* ForContinue;
    FILE* fptForContinue;
    
    long flagphimin;
    float phimin;
    
    long flagphimax;
    float phimax;
    
    long flagdelphi;
    float delphi;
    
    long flagzmin;
    float zmin;
    
    long flagzmax;
    float zmax;
    
    long flagdelz;
    float delz;
    
    long flagshiftmin;
    float shiftmin;
    
    long flagshiftmax;
    float shiftmax;
    
    long flagdelshift;
    float delshift;
    
    long flagLog;
    char* Log;
    FILE* fptLog;
    
    long Normalization;

    long flagpvm;
    long pvm;
    
    long flagpvmList;
    char* pvmList;
    FILE* fptpvmList;
    
    long pvmServer;

    long pvmClient;

    long flagWorkingDir;
    char* WorkingDir;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} llExtractWithLayerSeparationInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(llExtractWithLayerSeparationInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(llExtractWithLayerSeparationInfo* info);
extern void init1(llExtractWithLayerSeparationInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* LLEXTRACTWITHLAYERSEPARATION_H */
