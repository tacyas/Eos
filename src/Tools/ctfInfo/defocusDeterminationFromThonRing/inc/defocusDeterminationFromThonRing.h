#ifndef DEFOCUSDETERMINATIONFROMTHONRING_H
#define DEFOCUSDETERMINATIONFROMTHONRING_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct defocusDeterminationFromThonRingInfo {
    long flagRedirect;

    long flagIn;
    char* In;
    FILE* fptIn;
    
    long flagInN;
    char* InN;
    
    long flagInR;
    char* InR;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagOutI;
    char* OutI;
    FILE* fptOutI;
    
    long flagOutI2;
    char* OutI2;
    FILE* fptOutI2;
    
    long flagOutI3;
    char* OutI3;
    FILE* fptOutI3;
    
    long flagkV;
    float kV;
    
    long flagCs;
    float Cs;
    
    long flagAoverP;
    float AoverP;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
    long flagctfMode;
    long ctfMode;
    
    long flagtruePitch;
    float truePitch;
    
    long flagPixelSize;
    float PixelSize;
    
    long flagdeltadY;
    float deltadY;
    
    long flagR;
    float* R;
    
} defocusDeterminationFromThonRingInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(defocusDeterminationFromThonRingInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(defocusDeterminationFromThonRingInfo* info);
extern void init1(defocusDeterminationFromThonRingInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* DEFOCUSDETERMINATIONFROMTHONRING_H */
