#ifndef EOSPOINTROTATION_H
#define EOSPOINTROTATION_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct eosPointRotationInfo {
    long flagRedirect;

    long flagIn;
    char* In;
    FILE* fptIn;
    
    long flagInType;
    long InType;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagOutType;
    long OutType;
    
    long flagEAMode;
    char* EAMode;
    
    long flagRot1;
    float Rot1;
    
    long flagRot2;
    float Rot2;
    
    long flagRot3;
    float Rot3;
    
    long flagInList;
    char** InList;
    char* InListList;
    FILE** fptInList;
    FILE* fptInListList;
    
    long flagOutList;
    char** OutList;
    char* OutListList;
    FILE** fptOutList;
    FILE* fptOutListList;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} eosPointRotationInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(eosPointRotationInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(eosPointRotationInfo* info);
extern void init1(eosPointRotationInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* EOSPOINTROTATION_H */
