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
init0(mrcImageSeriesNormalizingInfo* info)
{
    info->fptIn     = NULL;    info->fptInList = NULL;    info->flagIn = 0;
    info->fptWeight = NULL;    info->flagWeight = 0;
    info->fptOut     = NULL;    info->fptOutList = NULL;    info->flagOut = 0;
    info->fptParam = stdout;    info->flagParam = 0;
    info->thresOfLowValueArea = 0.01;    info->flagthresOfLowValueArea = 0;
    info->thresOfHighValueArea = 0.99;    info->flagthresOfHighValueArea = 0;
    info->Low = 0.1;    info->flagLow = 0;
    info->High = 0.9;    info->flagHigh = 0;
    info->UseLow = 1;    info->flagUseLow = 0;
    info->UseHigh = 1;    info->flagUseHigh = 0;
    info->ALow = 1.0;    info->flagALow = 0;
    info->KLow = 0.1;    info->flagKLow = 0;
    info->BLow = 1.0;    info->flagBLow = 0;
    info->AHigh = 0.1;    info->flagAHigh = 0;
    info->KHigh = 0.1;    info->flagKHigh = 0;
    info->BHigh = 0.0;    info->flagBHigh = 0;
    info->maxIter = 100;    info->flagmaxIter = 0;
    info->xtol = 1e-8;    info->flagxtol = 0;
    info->gtol = 1e-8;    info->flaggtol = 0;
    info->ftol = 0.0;    info->flagftol = 0;
    info->fptconfigFile = NULL;    info->flagconfigFile = 0;
    info->mode = 0;    info->flagmode = 0;
}

void
init1(mrcImageSeriesNormalizingInfo* info)
{
    char s[1024];
    int i;
    if(!info->flagIn) {
        stringGetFromFile(s, "In", stdin, stdout, 0);
        info->InList = stringGetNthWord(s, 1, " ,\t");
        info->flagIn++;
    }
    if(info->flagIn) {
        info->fptInList = fileOpen(info->InList, "r");
        fseek(info->fptInList, 0L, SEEK_SET);
        i=0;
        while(NULL!=stringGetFromFile(s, "", info->fptInList, stdout, 1)) {
            i++;
        }
        info->fptIn = (FILE**)memoryAllocate(i*sizeof(FILE*), "in init1");
        info->In    = (char**)memoryAllocate(i*sizeof(char*), "in init1");
        info->flagIn = i;
        fseek(info->fptInList, 0L, SEEK_SET);
        i=0;
        while(NULL!=stringGetFromFile(s, "", info->fptInList, stdout, 1)) {
            info->In[i] = stringGetNthWord(s, 1, " ,\t");
            info->fptIn[i] = fileOpen(info->In[i],"r");
            i++;
        }
    }
    
    if(info->flagWeight) {
        info->fptWeight = fileOpen(info->Weight, "r");
    }
    
    if(!info->flagOut) {
        stringGetFromFile(s, "Out", stdin, stdout, 0);
        info->OutList = stringGetNthWord(s, 1, " ,\t");
        info->flagOut++;
    }
    if(info->flagOut) {
        info->fptOutList = fileOpen(info->OutList, "r");
        fseek(info->fptOutList, 0L, SEEK_SET);
        i=0;
        while(NULL!=stringGetFromFile(s, "", info->fptOutList, stdout, 1)) {
            i++;
        }
        info->fptOut = (FILE**)memoryAllocate(i*sizeof(FILE*), "in init1");
        info->Out    = (char**)memoryAllocate(i*sizeof(char*), "in init1");
        info->flagOut = i;
        fseek(info->fptOutList, 0L, SEEK_SET);
        i=0;
        while(NULL!=stringGetFromFile(s, "", info->fptOutList, stdout, 1)) {
            info->Out[i] = stringGetNthWord(s, 1, " ,\t");
            info->fptOut[i] = fileOpen(info->Out[i],"w");
            i++;
        }
    }
    
    if(info->flagParam) {
        info->fptParam = fileOpen(info->Param, "w");
    }
    
    if(info->flagthresOfLowValueArea) {
    }
    
    if(info->flagthresOfHighValueArea) {
    }
    
    if(info->flagLow) {
    }
    
    if(info->flagHigh) {
    }
    
    if(info->flagUseLow) {
    }
    
    if(info->flagUseHigh) {
    }
    
    if(info->flagALow) {
    }
    
    if(info->flagKLow) {
    }
    
    if(info->flagBLow) {
    }
    
    if(info->flagAHigh) {
    }
    
    if(info->flagKHigh) {
    }
    
    if(info->flagBHigh) {
    }
    
    if(info->flagmaxIter) {
    }
    
    if(info->flagxtol) {
    }
    
    if(info->flaggtol) {
    }
    
    if(info->flagftol) {
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
    sprintf(panepath, "%s/src/Tools/mrcImage/mrcImageSeriesNormalizing/src/mrcImageSeriesNormalizing.pane", eospath);
    khoros_initialize(argc, argv, "EOS");
    fpt = fopen(panepath, "r");    if(NULL!=fpt) {
        fclose(fpt);
        kclui_initialize(panepath, KGEN_NONE, "EOS", "mrcImageSeriesNormalizing",
                     func_usage_additions,
                     func_get_args,
                     func_free_args);
    }
}
#endif /* KHOROS */ 
