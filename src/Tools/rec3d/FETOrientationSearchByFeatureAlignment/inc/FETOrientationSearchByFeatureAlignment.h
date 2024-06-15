#ifndef FETORIENTATIONSEARCHBYFEATUREALIGNMENT_H
#define FETORIENTATIONSEARCHBYFEATUREALIGNMENT_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct FETOrientationSearchByFeatureAlignmentInfo {
    long flagRedirect;

    long flagInS;
    char* InS;
    FILE* fptInS;
    
    long flagInS2;
    char* InS2;
    FILE* fptInS2;
    
    long flagInF;
    char* InF;
    FILE* fptInF;
    
    long flagInA;
    char* InA;
    FILE* fptInA;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagOutLOG;
    char* OutLOG;
    FILE* fptOutLOG;
    
    long flagOutA;
    char* OutA;
    FILE* fptOutA;
    
    long flagOut2D;
    char* Out2D;
    FILE* fptOut2D;
    
    long flagITMAX;
    long ITMAX;
    
    long flagDEVMAX;
    long DEVMAX;
    
    long flagMITMAX;
    long MITMAX;
    
    long flagMDEVMAX;
    long MDEVMAX;
    
    long flagLDN;
    long LDN;
    
    long flagSRL;
    float SRL;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} FETOrientationSearchByFeatureAlignmentInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(FETOrientationSearchByFeatureAlignmentInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(FETOrientationSearchByFeatureAlignmentInfo* info);
extern void init1(FETOrientationSearchByFeatureAlignmentInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* FETORIENTATIONSEARCHBYFEATUREALIGNMENT_H */
