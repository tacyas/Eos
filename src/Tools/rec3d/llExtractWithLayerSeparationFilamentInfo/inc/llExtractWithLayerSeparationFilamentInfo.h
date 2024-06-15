#ifndef LLEXTRACTWITHLAYERSEPARATIONFILAMENTINFO_H
#define LLEXTRACTWITHLAYERSEPARATIONFILAMENTINFO_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct llExtractWithLayerSeparationFilamentInfoInfo {
    long flagRedirect;

    long flagIn;
    char* In;
    FILE* fptIn;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagOutF;
    char* OutF;
    FILE* fptOutF;
    
    long flagOutI;
    char* OutI;
    FILE* fptOutI;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagtruePitch;
    float truePitch;
    
    long flagPixelSize;
    float PixelSize;
    
    long flagdeltadY;
    float deltadY;
    
    long flagkV;
    float kV;
    
    long flagCs;
    float Cs;
    
    long flagDefocus;
    float Defocus;
    
    long flagAoverP;
    float AoverP;
    
    long flagmode;
    long mode;
    
} llExtractWithLayerSeparationFilamentInfoInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(llExtractWithLayerSeparationFilamentInfoInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(llExtractWithLayerSeparationFilamentInfoInfo* info);
extern void init1(llExtractWithLayerSeparationFilamentInfoInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* LLEXTRACTWITHLAYERSEPARATIONFILAMENTINFO_H */
