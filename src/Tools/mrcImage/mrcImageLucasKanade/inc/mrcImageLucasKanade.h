#ifndef MRCIMAGELUCASKANADE_H
#define MRCIMAGELUCASKANADE_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct mrcImageLucasKanadeInfo {
    long flagRedirect;

    long flagInVx;
    char* InVx;
    FILE* fptInVx;
    
    long flagInVy;
    char* InVy;
    FILE* fptInVy;
    
    long flagInVz;
    char* InVz;
    FILE* fptInVz;
    
    long flagInVxList;
    char** InVxList;
    char* InVxListList;
    FILE** fptInVxList;
    FILE* fptInVxListList;
    
    long flagInVyList;
    char** InVyList;
    char* InVyListList;
    FILE** fptInVyList;
    FILE* fptInVyListList;
    
    long flagInVzList;
    char** InVzList;
    char* InVzListList;
    FILE** fptInVzList;
    FILE* fptInVzListList;
    
    long flagIn1Vx;
    char* In1Vx;
    FILE* fptIn1Vx;
    
    long flagIn1Vy;
    char* In1Vy;
    FILE* fptIn1Vy;
    
    long flagIn1Vz;
    char* In1Vz;
    FILE* fptIn1Vz;
    
    long flagIn2Vx;
    char* In2Vx;
    FILE* fptIn2Vx;
    
    long flagIn2Vy;
    char* In2Vy;
    FILE* fptIn2Vy;
    
    long flagIn2Vz;
    char* In2Vz;
    FILE* fptIn2Vz;
    
    long flagIn3Vx;
    char* In3Vx;
    FILE* fptIn3Vx;
    
    long flagIn3Vy;
    char* In3Vy;
    FILE* fptIn3Vy;
    
    long flagIn3Vz;
    char* In3Vz;
    FILE* fptIn3Vz;
    
    long flagIn4Vx;
    char* In4Vx;
    FILE* fptIn4Vx;
    
    long flagIn4Vy;
    char* In4Vy;
    FILE* fptIn4Vy;
    
    long flagIn4Vz;
    char* In4Vz;
    FILE* fptIn4Vz;
    
    long flagoutVx;
    char* outVx;
    FILE* fptoutVx;
    
    long flagoutVy;
    char* outVy;
    FILE* fptoutVy;
    
    long flagoutVz;
    char* outVz;
    FILE* fptoutVz;
    
    long flagNOS;
    float NOS;
    
    long flagSize;
    char* Size;
    FILE* fptSize;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} mrcImageLucasKanadeInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(mrcImageLucasKanadeInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(mrcImageLucasKanadeInfo* info);
extern void init1(mrcImageLucasKanadeInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* MRCIMAGELUCASKANADE_H */
