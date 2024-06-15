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
init0(mrc2Dto3DInfo* info)
{
    info->fptIn = NULL;    info->flagIn = 0;
    info->fptIn2     = NULL;    info->fptIn2List = NULL;    info->flagIn2 = 0;
    info->each=0;
    info->fptOut = NULL;    info->flagOut = 0;
    info->fptOut2 = NULL;    info->flagOut2 = 0;
    info->Rmax = 1.0;    info->flagRmax = 0;
    info->single = 1;    info->flagsingle = 0;
    info->singleFilter = 0;    info->flagsingleFilter = 0;
    info->InterpolationMode = 1;    info->flagInterpolationMode = 0;
    info->Double=0;
    info->fptDoubleCounter = NULL;    info->flagDoubleCounter = 0;
    info->CounterThreshold = 1e-6;    info->flagCounterThreshold = 0;
    info->CounterThresholdMode = 0;    info->flagCounterThresholdMode = 0;
    info->WeightMode = 0;    info->flagWeightMode = 0;
    info->thicknessWeight=0;
    info->SubSampling = 1;    info->flagSubSampling = 0;
    info->PlusXrot=0;
    info->Nx = 0;    info->flagNx = 0;
    info->Ny = 0;    info->flagNy = 0;
    info->Nz = 0;    info->flagNz = 0;
    info->SIRT=0;
    info->maxIter = 30;    info->flagmaxIter = 0;
    info->rms = 1.0;    info->flagrms = 0;
    info->fptCTFInfo     = NULL;    info->fptCTFInfoList = NULL;    info->flagCTFInfo = 0;
    info->pthreadMax = 1;    info->flagpthreadMax = 0;
    info->fptconfigFile = NULL;    info->flagconfigFile = 0;
    info->mode = 0;    info->flagmode = 0;
}

void
init1(mrc2Dto3DInfo* info)
{
    char s[1024];
    int i;
    if(info->flagIn) {
        info->fptIn = fileOpen(info->In, "r");
    }
    
    if(info->flagIn2) {
        info->fptIn2List = fileOpen(info->In2List, "r");
        fseek(info->fptIn2List, 0L, SEEK_SET);
        i=0;
        while(NULL!=stringGetFromFile(s, "", info->fptIn2List, stdout, 1)) {
            i++;
        }
        info->fptIn2 = (FILE**)memoryAllocate(i*sizeof(FILE*), "in init1");
        info->In2    = (char**)memoryAllocate(i*sizeof(char*), "in init1");
        info->flagIn2 = i;
        fseek(info->fptIn2List, 0L, SEEK_SET);
        i=0;
        while(NULL!=stringGetFromFile(s, "", info->fptIn2List, stdout, 1)) {
            info->In2[i] = stringGetNthWord(s, 1, " ,\t");
            i++;
        }
    }
    
    if(!info->flagOut) {
        stringGetFromFile(s, "Out", stdin, stdout, 0);
        info->Out = stringGetNthWord(s, 1, " ,\t");
        info->flagOut++;
    }
    if(info->flagOut) {
        info->fptOut = fileOpen(info->Out, "w");
    }
    
    if(info->flagOut2) {
        info->fptOut2 = fileOpen(info->Out2, "w");
    }
    
    if(info->flagRmax) {
    }
    
    if(info->flagsingle) {
    }
    
    if(info->flagsingleFilter) {
    }
    
    if(info->flagInterpolationMode) {
    }
    
    if(info->flagDoubleCounter) {
        info->fptDoubleCounter = fileOpen(info->DoubleCounter, "w");
    }
    
    if(info->flagCounterThreshold) {
    }
    
    if(info->flagCounterThresholdMode) {
    }
    
    if(info->flagWeightMode) {
    }
    
    if(info->flagSubSampling) {
    }
    
    if(info->flagNx) {
    }
    
    if(info->flagNy) {
    }
    
    if(info->flagNz) {
    }
    
    if(info->flagmaxIter) {
    }
    
    if(info->flagrms) {
    }
    
    if(info->flagCTFInfo) {
        info->fptCTFInfoList = fileOpen(info->CTFInfoList, "r");
        fseek(info->fptCTFInfoList, 0L, SEEK_SET);
        i=0;
        while(NULL!=stringGetFromFile(s, "", info->fptCTFInfoList, stdout, 1)) {
            i++;
        }
        info->fptCTFInfo = (FILE**)memoryAllocate(i*sizeof(FILE*), "in init1");
        info->CTFInfo    = (char**)memoryAllocate(i*sizeof(char*), "in init1");
        info->flagCTFInfo = i;
        fseek(info->fptCTFInfoList, 0L, SEEK_SET);
        i=0;
        while(NULL!=stringGetFromFile(s, "", info->fptCTFInfoList, stdout, 1)) {
            info->CTFInfo[i] = stringGetNthWord(s, 1, " ,\t");
            info->fptCTFInfo[i] = fileOpen(info->CTFInfo[i],"r");
            i++;
        }
    }
    
    if(info->flagpthreadMax) {
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
    sprintf(panepath, "%s/src/Tools/rec3d/mrc2Dto3D/src/mrc2Dto3D.pane", eospath);
    khoros_initialize(argc, argv, "EOS");
    fpt = fopen(panepath, "r");    if(NULL!=fpt) {
        fclose(fpt);
        kclui_initialize(panepath, KGEN_NONE, "EOS", "mrc2Dto3D",
                     func_usage_additions,
                     func_get_args,
                     func_free_args);
    }
}
#endif /* KHOROS */ 
