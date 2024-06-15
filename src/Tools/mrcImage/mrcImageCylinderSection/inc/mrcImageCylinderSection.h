#ifndef MRCIMAGECYLINDERSECTION_H
#define MRCIMAGECYLINDERSECTION_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct mrcImageCylinderSectionInfo {
    long flagRedirect;

    long flagIn;
    char* In;
    FILE* fptIn;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagangmin;
    float angmin;
    
    long flagangmax;
    float angmax;
    
    long flagdang;
    float dang;
    
    long flagzmin;
    float zmin;
    
    long flagzmax;
    float zmax;
    
    long flagdz;
    float dz;
    
    long flagrmin;
    float rmin;
    
    long flagrmax;
    float rmax;
    
    long flagdr;
    float dr;
    
    long Weight;

    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} mrcImageCylinderSectionInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(mrcImageCylinderSectionInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(mrcImageCylinderSectionInfo* info);
extern void init1(mrcImageCylinderSectionInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* MRCIMAGECYLINDERSECTION_H */
