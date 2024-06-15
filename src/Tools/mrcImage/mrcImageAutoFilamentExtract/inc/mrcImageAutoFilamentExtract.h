#ifndef MRCIMAGEAUTOFILAMENTEXTRACT_H
#define MRCIMAGEAUTOFILAMENTEXTRACT_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct mrcImageAutoFilamentExtractInfo {
    long flagRedirect;

    long flagIn;
    char* In;
    FILE* fptIn;
    
    long flagInS;
    char* InS;
    FILE* fptInS;
    
    long flagOutE;
    char* OutE;
    FILE* fptOutE;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagOutF;
    char* OutF;
    FILE* fptOutF;
    
    long flagblx;
    float blx;
    
    long flagbly;
    float bly;
    
    long flagbrx;
    float brx;
    
    long flagbry;
    float bry;
    
    long flagtrx;
    float trx;
    
    long flagtry;
    float try;
    
    long flagtlx;
    float tlx;
    
    long flagtly;
    float tly;
    
    long flagroiLine;
    float* roiLine;
    
    long flagx;
    float x;
    
    long flagddYmax;
    float ddYmax;
    
    long flagddYmin;
    float ddYmin;
    
    long flagT;
    long T;
    
    long flagmaxdY;
    long maxdY;
    
    long flagHeightRange;
    long HeightRange;
    
    long flagRMaxX;
    float RMaxX;
    
    long flagmag;
    float mag;
    
    long flagtruePitch;
    float truePitch;
    
    long flagPixelSize;
    float PixelSize;
    
    long flagfinaly;
    long finaly;
    
    long flagIgnore;
    long Ignore;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} mrcImageAutoFilamentExtractInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(mrcImageAutoFilamentExtractInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(mrcImageAutoFilamentExtractInfo* info);
extern void init1(mrcImageAutoFilamentExtractInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* MRCIMAGEAUTOFILAMENTEXTRACT_H */
