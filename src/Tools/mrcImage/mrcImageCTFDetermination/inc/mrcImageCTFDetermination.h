#ifndef MRCIMAGECTFDETERMINATION_H
#define MRCIMAGECTFDETERMINATION_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct mrcImageCTFDeterminationInfo {
    long flagRedirect;

    long flagIn;
    char* In;
    FILE* fptIn;
    
    long flagRef;
    char* Ref;
    FILE* fptRef;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagOut2;
    char* Out2;
    FILE* fptOut2;
    
    long flagOutC;
    char* OutC;
    FILE* fptOutC;
    
    long flagOutF;
    char* OutF;
    FILE* fptOutF;
    
    long flagkV;
    float kV;
    
    long flagCs;
    float Cs;
    
    long flagAin;
    float Ain;
    
    long flagWhiteNoise;
    float WhiteNoise;
    
    long flagmindf;
    float mindf;
    
    long flagmaxdf;
    float maxdf;
    
    long flagdeldf;
    float deldf;
    
    long flagminAoverP;
    float minAoverP;
    
    long flagmaxAoverP;
    float maxAoverP;
    
    long flagdelAoverP;
    float delAoverP;
    
    long flagRmin;
    float Rmin;
    
    long flagRmax;
    float Rmax;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmF;
    long mF;
    
    long flagmW;
    long mW;
    
    long flagmS;
    long mS;
    
    long flagmC;
    long mC;
    
    long flagM;
    long M;
    
    long flagPixelSize;
    long PixelSize;
    
    long flagWidth;
    long Width;
    
    long flagtruePitch;
    float truePitch;
    
    long flagfirstDf;
    float firstDf;
    
    long flagwithinDf;
    float withinDf;
    
    long flagfirstAoverP;
    float firstAoverP;
    
    long flagwithinAoverP;
    float withinAoverP;
    
    long flagmaxiter;
    long maxiter;
    
    long flagmode;
    long mode;
    
} mrcImageCTFDeterminationInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(mrcImageCTFDeterminationInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(mrcImageCTFDeterminationInfo* info);
extern void init1(mrcImageCTFDeterminationInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* MRCIMAGECTFDETERMINATION_H */
