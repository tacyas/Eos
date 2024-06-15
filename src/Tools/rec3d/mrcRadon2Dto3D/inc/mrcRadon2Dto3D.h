#ifndef MRCRADON2DTO3D_H
#define MRCRADON2DTO3D_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct mrcRadon2Dto3DInfo {
    long flagRedirect;

    long flagIn2;
    char** In2;
    char* In2List;
    FILE** fptIn2;
    FILE* fptIn2List;
    
    long flagInBefore;
    char** InBefore;
    char* InBeforeList;
    FILE** fptInBefore;
    FILE* fptInBeforeList;
    
    long flaginbefore;
    char* inbefore;
    FILE* fptinbefore;
    
    long flaginWbefore;
    char* inWbefore;
    FILE* fptinWbefore;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagOutW;
    char* OutW;
    FILE* fptOutW;
    
    long flagdp;
    float dp;
    
    long flagdtheta;
    float dtheta;
    
    long flagdphi;
    float dphi;
    
    long flagT;
    float T;
    
    long flagInterpolationMode;
    long InterpolationMode;
    
    long flagmode;
    long mode;
    
} mrcRadon2Dto3DInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(mrcRadon2Dto3DInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(mrcRadon2Dto3DInfo* info);
extern void init1(mrcRadon2Dto3DInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* MRCRADON2DTO3D_H */
