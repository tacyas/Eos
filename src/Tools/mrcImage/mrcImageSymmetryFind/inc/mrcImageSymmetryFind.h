#ifndef MRCIMAGESYMMETRYFIND_H
#define MRCIMAGESYMMETRYFIND_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct mrcImageSymmetryFindInfo {
    long flagRedirect;

    long flagIn;
    char* In;
    FILE* fptIn;
    
    long flagOut;
    char* Out;
    FILE* fptOut;
    
    long flagOut2;
    char* Out2;
    FILE* fptOut2;
    
    long flagAvg;
    char* Avg;
    FILE* fptAvg;
    
    long flagcentreMode;
    long centreMode;
    
    long flagthreshold1;
    float threshold1;
    
    long flagthreshold2;
    float threshold2;
    
    long flagmode1;
    long mode1;
    
    long flagmode2;
    long mode2;
    
    long flagdr;
    float dr;
    
    long flagdtheta;
    float dtheta;
    
    long flagn;
    long n;
    
    long flagnmin;
    long nmin;
    
    long flagnmax;
    long nmax;
    
    long flagImage;
    char** Image;
    char* ImageList;
    FILE** fptImage;
    FILE* fptImageList;
    
    long flagBack;
    char** Back;
    char* BackList;
    FILE** fptBack;
    FILE* fptBackList;
    
    long flagminx;
    float minx;
    
    long flagmaxx;
    float maxx;
    
    long flagdelx;
    float delx;
    
    long flagminy;
    float miny;
    
    long flagmaxy;
    float maxy;
    
    long flagdely;
    float dely;
    
    long flagminz;
    float minz;
    
    long flagmaxz;
    float maxz;
    
    long flagdelz;
    float delz;
    
    long flagrmin;
    float rmin;
    
    long flagrmax;
    float rmax;
    
    long Algorythm;

    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
} mrcImageSymmetryFindInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(mrcImageSymmetryFindInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(mrcImageSymmetryFindInfo* info);
extern void init1(mrcImageSymmetryFindInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* MRCIMAGESYMMETRYFIND_H */
