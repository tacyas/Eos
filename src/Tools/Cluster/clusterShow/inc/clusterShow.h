#ifndef CLUSTERSHOW_H
#define CLUSTERSHOW_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct clusterShowInfo {
    long flagRedirect;

    long flagIn;
    char* In;
    FILE* fptIn;
    
    long flagIn2;
    char* In2;
    FILE* fptIn2;
    
    long flagInB;
    char* InB;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagOut2;
    char* Out2;
    FILE* fptOut2;
    
    long flagOutPS;
    char* OutPS;
    FILE* fptOutPS;
    
    long flagOutOL;
    char* OutOL;
    FILE* fptOutOL;
    
    long flagTreeInfo;
    char* TreeInfo;
    FILE* fptTreeInfo;
    
    long flagOutAL;
    char* OutAL;
    FILE* fptOutAL;
    
    long flagOutALRange;
    long OutALRange;
    
    long flagOutALSuffix;
    char* OutALSuffix;
    
    long flagLastNum;
    long LastNum;
    
    long flagShoulderScale;
    float ShoulderScale;
    
    long flagArmScale;
    float ArmScale;
    
    long flagPosX;
    float PosX;
    
    long flagPosY;
    float PosY;
    
    long flagOffset;
    float Offset;
    
    long flagInList;
    char** InList;
    char* InListList;
    FILE** fptInList;
    FILE* fptInListList;
    
    long Log;

    long Scaling;

    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} clusterShowInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(clusterShowInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(clusterShowInfo* info);
extern void init1(clusterShowInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* CLUSTERSHOW_H */
