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
init0(mrcImageSuperResolutionInfo* info)
{
    info->fptInOriginal = NULL;    info->flagInOriginal = 0;
    info->fptInPrevious = NULL;    info->flagInPrevious = 0;
    info->fptFFTInCount = NULL;    info->flagFFTInCount = 0;
    info->fptOut = NULL;    info->flagOut = 0;
    info->t = 1;    info->flagt = 0;
    info->x00 = 0;    info->flagx00 = 0;
    info->y00 = 0;    info->flagy00 = 0;
    info->z00 = 0;    info->flagz00 = 0;
    info->x01 = 2;    info->flagx01 = 0;
    info->y01 = 2;    info->flagy01 = 0;
    info->z01 = 2;    info->flagz01 = 0;
    info->x10 = 0;    info->flagx10 = 0;
    info->y10 = 0;    info->flagy10 = 0;
    info->z10 = 0;    info->flagz10 = 0;
    info->x11 = 0;    info->flagx11 = 0;
    info->y11 = 0;    info->flagy11 = 0;
    info->z11 = 0;    info->flagz11 = 0;
    info->fptconfigFile = NULL;    info->flagconfigFile = 0;
    info->mode = 0;    info->flagmode = 0;
    info->labelingmode = 0;    info->flaglabelingmode = 0;
    info->max = 800;    info->flagmax = 0;
    info->min = 200;    info->flagmin = 0;
    info->shape = 0;    info->flagshape = 0;
    info->hvp = 0.0;    info->flaghvp = 0;
    info->Inverse=0;
    info->nMolecule = 1;    info->flagnMolecule = 0;
    info->MolecularWeight = 80000;    info->flagMolecularWeight = 0;
    info->Density = 1.35;    info->flagDensity = 0;
    info->incounter = 3.0;    info->flagincounter = 0;
    info->deltaDens = 100.0;    info->flagdeltaDens = 0;
    info->deltaArea = 100.0;    info->flagdeltaArea = 0;
    info->sub = 0.2;    info->flagsub = 0;
    info->ratio = 0.3;    info->flagratio = 0;
    info->tmax = 1000;    info->flagtmax = 0;
    info->WeightDelta = 0.1;    info->flagWeightDelta = 0;
    info->WeightMax = 2;    info->flagWeightMax = 0;
    info->Subtraction=0;
}

void
init1(mrcImageSuperResolutionInfo* info)
{
    char s[1024];
    int i;
    if(!info->flagInOriginal) {
        stringGetFromFile(s, "InOriginal", stdin, stdout, 0);
        info->InOriginal = stringGetNthWord(s, 1, " ,\t");
        info->flagInOriginal++;
    }
    if(info->flagInOriginal) {
        info->fptInOriginal = fileOpen(info->InOriginal, "r");
    }
    
    if(!info->flagInPrevious) {
        stringGetFromFile(s, "InPrevious", stdin, stdout, 0);
        info->InPrevious = stringGetNthWord(s, 1, " ,\t");
        info->flagInPrevious++;
    }
    if(info->flagInPrevious) {
        info->fptInPrevious = fileOpen(info->InPrevious, "r");
    }
    
    if(info->flagFFTInCount) {
        info->fptFFTInCount = fileOpen(info->FFTInCount, "r");
    }
    
    if(!info->flagOut) {
        stringGetFromFile(s, "Out", stdin, stdout, 0);
        info->Out = stringGetNthWord(s, 1, " ,\t");
        info->flagOut++;
    }
    if(info->flagOut) {
        info->fptOut = fileOpen(info->Out, "w");
    }
    
    if(info->flagt) {
    }
    
    if(info->flagx00) {
    }
    
    if(info->flagy00) {
    }
    
    if(info->flagz00) {
    }
    
    if(info->flagx01) {
    }
    
    if(info->flagy01) {
    }
    
    if(info->flagz01) {
    }
    
    if(info->flagx10) {
    }
    
    if(info->flagy10) {
    }
    
    if(info->flagz10) {
    }
    
    if(info->flagx11) {
    }
    
    if(info->flagy11) {
    }
    
    if(info->flagz11) {
    }
    
    if(info->flagconfigFile) {
        info->fptconfigFile = fileOpen(info->configFile, "r");
    }
    
    if(!info->flagmode) {
        stringGetFromFile(s, "mode", stdin, stdout, 0);
        info->mode = stringGetNthIntegerData(s, 1, ", \t");
        info->flagmode++;
    }
    if(info->flagmode) {
    }
    
    if(info->flaglabelingmode) {
    }
    
    if(info->flagmax) {
    }
    
    if(info->flagmin) {
    }
    
    if(info->flagshape) {
    }
    
    if(info->flaghvp) {
    }
    
    if(info->flagnMolecule) {
    }
    
    if(info->flagMolecularWeight) {
    }
    
    if(info->flagDensity) {
    }
    
    if(info->flagincounter) {
    }
    
    if(info->flagdeltaDens) {
    }
    
    if(info->flagdeltaArea) {
    }
    
    if(info->flagsub) {
    }
    
    if(info->flagratio) {
    }
    
    if(info->flagtmax) {
    }
    
    if(info->flagWeightDelta) {
    }
    
    if(info->flagWeightMax) {
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
    sprintf(panepath, "%s/src/Tools/mrcImage/mrcImageSuperResolution/src/mrcImageSuperResolution.pane", eospath);
    khoros_initialize(argc, argv, "EOS");
    fpt = fopen(panepath, "r");    if(NULL!=fpt) {
        fclose(fpt);
        kclui_initialize(panepath, KGEN_NONE, "EOS", "mrcImageSuperResolution",
                     func_usage_additions,
                     func_get_args,
                     func_free_args);
    }
}
#endif /* KHOROS */ 
