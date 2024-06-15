#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "../inc/config.h"
#include "genUtil.h"
#include "eosString.h"
#include "File.h"
#include "Memory.h"


void
init0(mrcImageFeatureCalcInfo* info)
{
    info->fptIn = NULL;    info->flagIn = 0;
    info->fptRef = NULL;    info->flagRef = 0;
    info->fptOut = stdout;    info->flagOut = 0;
    info->fptOutGC = NULL;    info->flagOutGC = 0;
    info->fptOutLabel = NULL;    info->flagOutLabel = 0;
    info->fptOutPerimeter = NULL;    info->flagOutPerimeter = 0;
    info->fptOutChain = NULL;    info->flagOutChain = 0;
    info->fptOutSurfaceArea = NULL;    info->flagOutSurfaceArea = 0;
    info->fptOutDensityWeightedArea = NULL;    info->flagOutDensityWeightedArea = 0;
    info->neighbor = 0;    info->flagneighbor = 0;
    info->fptInDensity = NULL;    info->flagInDensity = 0;
    info->fptconfigFile = NULL;    info->flagconfigFile = 0;
    info->mode = 0;    info->flagmode = 0;
}

void
init1(mrcImageFeatureCalcInfo* info)
{
    char s[1024];
    int i;
    if(!info->flagIn) {
        stringGetFromFile(s, "In", stdin, stdout, 0);
        info->In = stringGetNthWord(s, 1, " ,\t");
        info->flagIn++;
    }
    if(info->flagIn) {
        info->fptIn = fileOpen(info->In, "r");
    }
    
    if(info->flagRef) {
        info->fptRef = fileOpen(info->Ref, "r");
    }
    
    if(info->flagOut) {
        info->fptOut = fileOpen(info->Out, "w");
    }
    
    if(info->flagOutGC) {
        info->fptOutGC = fileOpen(info->OutGC, "w");
    }
    
    if(info->flagOutLabel) {
        info->fptOutLabel = fileOpen(info->OutLabel, "w");
    }
    
    if(info->flagOutPerimeter) {
        info->fptOutPerimeter = fileOpen(info->OutPerimeter, "w");
    }
    
    if(info->flagOutChain) {
        info->fptOutChain = fileOpen(info->OutChain, "w");
    }
    
    if(info->flagOutSurfaceArea) {
        info->fptOutSurfaceArea = fileOpen(info->OutSurfaceArea, "w");
    }
    
    if(info->flagOutDensityWeightedArea) {
        info->fptOutDensityWeightedArea = fileOpen(info->OutDensityWeightedArea, "w");
    }
    
    if(info->flagneighbor) {
    }
    
    if(info->flagInDensity) {
        info->fptInDensity = fileOpen(info->InDensity, "r");
    }
    
    if(info->flagconfigFile) {
        info->fptconfigFile = fileOpen(info->configFile, "r");
    }
    
    if(info->flagmode) {
    }
    
}
#ifdef KHOROS
#include <stdio.h>
#include "bootstrap.h"
#include "dataserv.h"
#include "datamanip.h"
extern void func_usage_additions(void);
extern void func_free_args(kexit_status status, kaddr client_data);
extern void func_get_args(kform* pane);

void
func_usage_additions(void)
{
}
void
func_free_args(kexit_status status, kaddr client_data)
{
}
void
func_get_args(kform* pane)
{
}
void
khorosInit(int argc, char* argv[])
{
    char* eospath;
    char  panepath[1024];
    FILE* fpt;
    
    eospath = getenv("EOS_HOME");
    sprintf(panepath, "%s/src/Tools/mrcImage/mrcImageFeatureCalc/src/mrcImageFeatureCalc.pane", eospath);
    khoros_initialize(argc, argv, "EOS");
    fpt = fopen(panepath, "r");    if(NULL!=fpt) {
        fclose(fpt);
        kclui_initialize(panepath, KGEN_NONE, "EOS", "mrcImageFeatureCalc",
                     func_usage_additions,
                     func_get_args,
                     func_free_args);
    }
}
#endif /* KHOROS */ 
