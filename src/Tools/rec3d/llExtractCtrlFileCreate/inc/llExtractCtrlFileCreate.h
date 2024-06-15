#ifndef LLEXTRACTCTRLFILECREATE_H
#define LLEXTRACTCTRLFILECREATE_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct llExtractCtrlFileCreateInfo {
    long flagRedirect;

    long flagIn;
    char* In;
    FILE* fptIn;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagturn;
    long turn;
    
    long flagunit;
    long unit;
    
    long flagnstrand;
    long nstrand;
    
    long flagY1;
    long Y1;
    
    long flagY0;
    long Y0;
    
    long flagrmax;
    float rmax;
    
    long flagRmax;
    float Rmax;
    
    long flaglx;
    float lx;
    
    long flagly;
    float ly;
    
    long flagnx;
    float nx;
    
    long flagny;
    float ny;
    
    long flagcenter;
    float center;
    
    long flaglayerline;
    float layerline;
    
    long flagAx;
    float Ax;
    
    long flagdY;
    float dY;
    
    long flagtruePitch;
    float truePitch;
    
    long flagPixelSize;
    float PixelSize;
    
    long flagdeltadY;
    float deltadY;
    
    long flagmode;
    long mode;
    
} llExtractCtrlFileCreateInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(llExtractCtrlFileCreateInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(llExtractCtrlFileCreateInfo* info);
extern void init1(llExtractCtrlFileCreateInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* LLEXTRACTCTRLFILECREATE_H */
