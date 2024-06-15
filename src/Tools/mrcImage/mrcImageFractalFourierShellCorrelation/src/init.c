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
init0(mrcImageFractalFourierShellCorrelationInfo* info)
{
    info->fptIn = NULL;    info->flagIn = 0;
    info->fptRef = NULL;    info->flagRef = 0;
    info->fptOut = NULL;    info->flagOut = 0;
    info->Threshold = 0.5;    info->flagThreshold = 0;
    info->stepx = 1;    info->flagstepx = 0;
    info->stepy = 1;    info->flagstepy = 0;
    info->stepz = 1;    info->flagstepz = 0;
    info->maxN = 32;    info->flagmaxN = 0;
    info->scaling = 1.25;    info->flagscaling = 0;
    info->getMode = 0;    info->flaggetMode = 0;
    info->fptLog = NULL;    info->flagLog = 0;
    info->xmin = 0;    info->flagxmin = 0;
    info->ymin = 0;    info->flagymin = 0;
    info->zmin = 0;    info->flagzmin = 0;
    info->xmax = 0;    info->flagxmax = 0;
    info->ymax = 0;    info->flagymax = 0;
    info->zmax = 0;    info->flagzmax = 0;
    info->densityThreshold = 0;    info->flagdensityThreshold = 0;
    info->fptconfigFile = NULL;    info->flagconfigFile = 0;
    info->mode = 0;    info->flagmode = 0;
}

void
init1(mrcImageFractalFourierShellCorrelationInfo* info)
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
    
    if(info->flagThreshold) {
    }
    
    if(info->flagstepx) {
    }
    
    if(info->flagstepy) {
    }
    
    if(info->flagstepz) {
    }
    
    if(info->flagmaxN) {
    }
    
    if(info->flagscaling) {
    }
    
    if(info->flaggetMode) {
    }
    
    if(info->flagLog) {
        info->fptLog = fileOpen(info->Log, "w");
    }
    
    if(info->flagxmin) {
    }
    
    if(info->flagymin) {
    }
    
    if(info->flagzmin) {
    }
    
    if(info->flagxmax) {
    }
    
    if(info->flagymax) {
    }
    
    if(info->flagzmax) {
    }
    
    if(info->flagdensityThreshold) {
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
    sprintf(panepath, "%s/src/Tools/mrcImage/mrcImageFractalFourierShellCorrelation/src/mrcImageFractalFourierShellCorrelation.pane", eospath);
    khoros_initialize(argc, argv, "EOS");
    fpt = fopen(panepath, "r");    if(NULL!=fpt) {
        fclose(fpt);
        kclui_initialize(panepath, KGEN_NONE, "EOS", "mrcImageFractalFourierShellCorrelation",
                     func_usage_additions,
                     func_get_args,
                     func_free_args);
    }
}
#endif /* KHOROS */ 
