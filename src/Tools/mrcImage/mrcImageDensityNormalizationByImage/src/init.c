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
init0(mrcImageDensityNormalizationByImageInfo* info)
{
    info->fptIn = NULL;    info->flagIn = 0;
    info->fptRef = NULL;    info->flagRef = 0;
    info->fptOut = NULL;    info->flagOut = 0;
    info->fptOutParam = stdout;    info->flagOutParam = 0;
    info->fptUsedData = stdout;    info->flagUsedData = 0;
    info->CCenterX = 20;    info->flagCCenterX = 0;
    info->CCenterY = 20;    info->flagCCenterY = 0;
    info->CMinR = 10;    info->flagCMinR = 0;
    info->CMaxR = 20;    info->flagCMaxR = 0;
    info->tstBGMin = -3;    info->flagtstBGMin = 0;
    info->tstBGMax = 3;    info->flagtstBGMax = 0;
    info->tstBGDelta = 0.1;    info->flagtstBGDelta = 0;
    info->fitMode = 0;    info->flagfitMode = 0;
    info->fptconfigFile = NULL;    info->flagconfigFile = 0;
    info->mode = 0;    info->flagmode = 0;
}

void
init1(mrcImageDensityNormalizationByImageInfo* info)
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
    
    if(!info->flagRef) {
        stringGetFromFile(s, "Ref", stdin, stdout, 0);
        info->Ref = stringGetNthWord(s, 1, " ,\t");
        info->flagRef++;
    }
    if(info->flagRef) {
        info->fptRef = fileOpen(info->Ref, "r");
    }
    
    if(!info->flagOut) {
        stringGetFromFile(s, "Out", stdin, stdout, 0);
        info->Out = stringGetNthWord(s, 1, " ,\t");
        info->flagOut++;
    }
    if(info->flagOut) {
        info->fptOut = fileOpen(info->Out, "w");
    }
    
    if(info->flagOutParam) {
        info->fptOutParam = fileOpen(info->OutParam, "w");
    }
    
    if(info->flagUsedData) {
        info->fptUsedData = fileOpen(info->UsedData, "w");
    }
    
    if(info->flagCCenterX) {
    }
    
    if(info->flagCCenterY) {
    }
    
    if(info->flagCMinR) {
    }
    
    if(info->flagCMaxR) {
    }
    
    if(info->flagtstBGMin) {
    }
    
    if(info->flagtstBGMax) {
    }
    
    if(info->flagtstBGDelta) {
    }
    
    if(info->flagfitMode) {
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
    sprintf(panepath, "%s/src/Tools/mrcImage/mrcImageDensityNormalizationByImage/src/mrcImageDensityNormalizationByImage.pane", eospath);
    khoros_initialize(argc, argv, "EOS");
    fpt = fopen(panepath, "r");    if(NULL!=fpt) {
        fclose(fpt);
        kclui_initialize(panepath, KGEN_NONE, "EOS", "mrcImageDensityNormalizationByImage",
                     func_usage_additions,
                     func_get_args,
                     func_free_args);
    }
}
#endif /* KHOROS */ 
