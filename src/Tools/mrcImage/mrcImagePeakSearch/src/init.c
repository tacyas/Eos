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
init0(mrcImagePeakSearchInfo* info)
{
    info->fptIn = NULL;    info->flagIn = 0;
    info->fptOut = NULL;    info->flagOut = 0;
    info->fptOutB = NULL;    info->flagOutB = 0;
    info->fptOutL = NULL;    info->flagOutL = 0;
    info->fptOutA = NULL;    info->flagOutA = 0;
    info->fptOutStatics = stdout;    info->flagOutStatics = 0;
    info->Sigma = 3.0;    info->flagSigma = 0;
    info->Threshold = 0.0;    info->flagThreshold = 0;
    info->Area = 6.0;    info->flagArea = 0;
    info->AreaPixel = 9;    info->flagAreaPixel = 0;
    info->fptconfigFile = NULL;    info->flagconfigFile = 0;
    info->mode = 0;    info->flagmode = 0;
}

void
init1(mrcImagePeakSearchInfo* info)
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
    
    if(info->flagOut) {
        info->fptOut = fileOpen(info->Out, "w");
    }
    
    if(info->flagOutB) {
        info->fptOutB = fileOpen(info->OutB, "w");
    }
    
    if(info->flagOutL) {
        info->fptOutL = fileOpen(info->OutL, "w");
    }
    
    if(info->flagOutA) {
        info->fptOutA = fileOpen(info->OutA, "w");
    }
    
    if(info->flagOutStatics) {
        info->fptOutStatics = fileOpen(info->OutStatics, "w");
    }
    
    if(info->flagSigma) {
    }
    
    if(info->flagThreshold) {
    }
    
    if(info->flagArea) {
    }
    
    if(info->flagAreaPixel) {
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
    sprintf(panepath, "%s/src/Tools/mrcImage/mrcImagePeakSearch/src/mrcImagePeakSearch.pane", eospath);
    khoros_initialize(argc, argv, "EOS");
    fpt = fopen(panepath, "r");    if(NULL!=fpt) {
        fclose(fpt);
        kclui_initialize(panepath, KGEN_NONE, "EOS", "mrcImagePeakSearch",
                     func_usage_additions,
                     func_get_args,
                     func_free_args);
    }
}
#endif /* KHOROS */ 
