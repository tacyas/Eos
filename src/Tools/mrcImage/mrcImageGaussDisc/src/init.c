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
init0(mrcImageGaussDiscInfo* info)
{
    info->fptOut = NULL;    info->flagOut = 0;
    info->sigmax = 10;    info->flagsigmax = 0;
    info->sigmay = 10;    info->flagsigmay = 0;
    info->sigma_range = 3;    info->flagsigma_range = 0;
    info->weight = 10;    info->flagweight = 0;
    info->size = 5;    info->flagsize = 0;
    info->Width = 0;    info->flagWidth = 0;
    info->Height = 0;    info->flagHeight = 0;
    info->centrex = 0;    info->flagcentrex = 0;
    info->centrey = 0;    info->flagcentrey = 0;
    info->Angle = 0;    info->flagAngle = 0;
    info->fptconfigFile = NULL;    info->flagconfigFile = 0;
    info->mode = 2;    info->flagmode = 0;
}

void
init1(mrcImageGaussDiscInfo* info)
{
    char s[1024];
    int i;
    if(!info->flagOut) {
        stringGetFromFile(s, "Out", stdin, stdout, 0);
        info->Out = stringGetNthWord(s, 1, " ,\t");
        info->flagOut++;
    }
    if(info->flagOut) {
        info->fptOut = fileOpen(info->Out, "w");
    }
    
    if(info->flagsigmax) {
    }
    
    if(info->flagsigmay) {
    }
    
    if(info->flagsigma_range) {
    }
    
    if(info->flagweight) {
    }
    
    if(info->flagsize) {
    }
    
    if(info->flagWidth) {
    }
    
    if(info->flagHeight) {
    }
    
    if(info->flagcentrex) {
    }
    
    if(info->flagcentrey) {
    }
    
    if(info->flagAngle) {
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
    sprintf(panepath, "%s/src/Tools/mrcImage/mrcImageGaussDisc/src/mrcImageGaussDisc.pane", eospath);
    khoros_initialize(argc, argv, "EOS");
    fpt = fopen(panepath, "r");    if(NULL!=fpt) {
        fclose(fpt);
        kclui_initialize(panepath, KGEN_NONE, "EOS", "mrcImageGaussDisc",
                     func_usage_additions,
                     func_get_args,
                     func_free_args);
    }
}
#endif /* KHOROS */ 
