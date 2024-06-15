#ifndef PDBTRANS_H
#define PDBTRANS_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct pdbTransInfo {
    long flagRedirect;

    long flaginFile;
    char* inFile;
    FILE* fptinFile;
    
    long flagoutFile;
    char* outFile;
    FILE* fptoutFile;
    
    long flagmatFile;
    char* matFile;
    FILE* fptmatFile;
    
    long flagRotMode;
    char* RotMode;
    
    long flagRot1;
    float Rot1;
    
    long flagRot2;
    float Rot2;
    
    long flagRot3;
    float Rot3;
    
    long flagcudaDeviceID;
    long cudaDeviceID;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} pdbTransInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(pdbTransInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(pdbTransInfo* info);
extern void init1(pdbTransInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* PDBTRANS_H */
