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
init0(mrcImageBilateralFilterInfo* info)
{
    info->fptIn = NULL;    info->flagIn = 0;
    info->fptOut = NULL;    info->flagOut = 0;
    info->SigmaDensity = 2.0;    info->flagSigmaDensity = 0;
    info->KernelTypeDensity = 0;    info->flagKernelTypeDensity = 0;
    info->SigmaSpace = 1.0;    info->flagSigmaSpace = 0;
    info->SigmaSpaceX = 1.0;    info->flagSigmaSpaceX = 0;
    info->SigmaSpaceY = 1.0;    info->flagSigmaSpaceY = 0;
    info->SigmaSpaceZ = 1.0;    info->flagSigmaSpaceZ = 0;
    info->KernelTypeSpace = 0;    info->flagKernelTypeSpace = 0;
    info->KernelSize = 5;    info->flagKernelSize = 0;
    info->KernelSizeX = 5;    info->flagKernelSizeX = 0;
    info->KernelSizeY = 5;    info->flagKernelSizeY = 0;
    info->KernelSizeZ = 5;    info->flagKernelSizeZ = 0;
    info->fptconfigFile = NULL;    info->flagconfigFile = 0;
    info->mode = 0;    info->flagmode = 0;
}

void
init1(mrcImageBilateralFilterInfo* info)
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
    
    if(!info->flagOut) {
        stringGetFromFile(s, "Out", stdin, stdout, 0);
        info->Out = stringGetNthWord(s, 1, " ,\t");
        info->flagOut++;
    }
    if(info->flagOut) {
        info->fptOut = fileOpen(info->Out, "w");
    }
    
    if(info->flagSigmaDensity) {
    }
    
    if(info->flagKernelTypeDensity) {
    }
    
    if(info->flagSigmaSpace) {
    }
    
    if(info->flagSigmaSpaceX) {
    }
    
    if(info->flagSigmaSpaceY) {
    }
    
    if(info->flagSigmaSpaceZ) {
    }
    
    if(info->flagKernelTypeSpace) {
    }
    
    if(info->flagKernelSize) {
    }
    
    if(info->flagKernelSizeX) {
    }
    
    if(info->flagKernelSizeY) {
    }
    
    if(info->flagKernelSizeZ) {
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
    sprintf(panepath, "%s/src/Tools/mrcImage/mrcImageBilateralFilter/src/mrcImageBilateralFilter.pane", eospath);
    khoros_initialize(argc, argv, "EOS");
    fpt = fopen(panepath, "r");    if(NULL!=fpt) {
        fclose(fpt);
        kclui_initialize(panepath, KGEN_NONE, "EOS", "mrcImageBilateralFilter",
                     func_usage_additions,
                     func_get_args,
                     func_free_args);
    }
}
#endif /* KHOROS */ 
