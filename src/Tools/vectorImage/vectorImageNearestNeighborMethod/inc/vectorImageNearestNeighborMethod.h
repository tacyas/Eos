#ifndef VECTORIMAGENEARESTNEIGHBORMETHOD_H
#define VECTORIMAGENEARESTNEIGHBORMETHOD_H
#include <stdio.h>
#include <stdlib.h>

#define OPTION_FLAG     '-'
#define OPTION_FLAG_POS (0)
#define OPTION_POS      (1)




typedef struct vectorImageNearestNeighborMethodInfo {
    long flagRedirect;

    long flagInList;
    char** InList;
    char* InListList;
    FILE** fptInList;
    FILE* fptInListList;
    
    long flagOutclassification;
    char* Outclassification;
    FILE* fptOutclassification;
    
    long flagOutClassificationIntegrationRate;
    char* OutClassificationIntegrationRate;
    FILE* fptOutClassificationIntegrationRate;
    
    long flagOutDistance;
    char* OutDistance;
    FILE* fptOutDistance;
    
    long flagOutDistanceRate;
    char* OutDistanceRate;
    FILE* fptOutDistanceRate;
    
    long flagOutUpperDistanceRate;
    char* OutUpperDistanceRate;
    FILE* fptOutUpperDistanceRate;
    
    long flagOutClassName;
    char* OutClassName;
    FILE* fptOutClassName;
    
    long flagconfigFile;
    char* configFile;
    FILE* fptconfigFile;
    
    long flagmode;
    long mode;
    
} vectorImageNearestNeighborMethodInfo;
#ifdef __cplusplus
extern "C" {
#endif
extern void argCheck(vectorImageNearestNeighborMethodInfo* info, int argc, char* avgv[]);
extern void khorosInit(int argc, char* avgv[]);
extern void init0(vectorImageNearestNeighborMethodInfo* info);
extern void init1(vectorImageNearestNeighborMethodInfo* info);
extern void usage(char* usage);
extern void additionalUsage(void);
extern void htmlBeforeUsage(char* usage);
extern void htmlAfterUsage(char* usage);
#ifdef __cplusplus
};
#endif
#endif /* VECTORIMAGENEARESTNEIGHBORMETHOD_H */
