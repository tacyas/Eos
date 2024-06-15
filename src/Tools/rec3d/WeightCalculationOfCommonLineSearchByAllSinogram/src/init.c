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
init0(WeightCalculationOfCommonLineSearchByAllSinogramInfo* info)
{
    info->fptIn1     = NULL;    info->fptIn1List = NULL;    info->flagIn1 = 0;
    info->fptIn2     = NULL;    info->fptIn2List = NULL;    info->flagIn2 = 0;
    info->fptIn3     = NULL;    info->fptIn3List = NULL;    info->flagIn3 = 0;
    info->fptIn4     = NULL;    info->fptIn4List = NULL;    info->flagIn4 = 0;
    info->fptOut = NULL;    info->flagOut = 0;
    info->fptconfigFile = NULL;    info->flagconfigFile = 0;
    info->mode = 0;    info->flagmode = 0;
    info->Mode = 15;    info->flagMode = 0;
    info->variance = 5;    info->flagvariance = 0;
}

void
init1(WeightCalculationOfCommonLineSearchByAllSinogramInfo* info)
{
    char s[1024];
    int i;
    if(info->flagIn1) {
        info->fptIn1List = fileOpen(info->In1List, "r");
        fseek(info->fptIn1List, 0L, SEEK_SET);
        i=0;
        while(NULL!=stringGetFromFile(s, "", info->fptIn1List, stdout, 1)) {
            i++;
        }
        info->fptIn1 = (FILE**)memoryAllocate(i*sizeof(FILE*), "in init1");
        info->In1    = (char**)memoryAllocate(i*sizeof(char*), "in init1");
        info->flagIn1 = i;
        fseek(info->fptIn1List, 0L, SEEK_SET);
        i=0;
        while(NULL!=stringGetFromFile(s, "", info->fptIn1List, stdout, 1)) {
            info->In1[i] = stringGetNthWord(s, 1, " ,\t");
            i++;
        }
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
    
    if(info->flagIn3) {
        info->fptIn3List = fileOpen(info->In3List, "r");
        fseek(info->fptIn3List, 0L, SEEK_SET);
        i=0;
        while(NULL!=stringGetFromFile(s, "", info->fptIn3List, stdout, 1)) {
            i++;
        }
        info->fptIn3 = (FILE**)memoryAllocate(i*sizeof(FILE*), "in init1");
        info->In3    = (char**)memoryAllocate(i*sizeof(char*), "in init1");
        info->flagIn3 = i;
        fseek(info->fptIn3List, 0L, SEEK_SET);
        i=0;
        while(NULL!=stringGetFromFile(s, "", info->fptIn3List, stdout, 1)) {
            info->In3[i] = stringGetNthWord(s, 1, " ,\t");
            i++;
        }
    }
    
    if(info->flagIn4) {
        info->fptIn4List = fileOpen(info->In4List, "r");
        fseek(info->fptIn4List, 0L, SEEK_SET);
        i=0;
        while(NULL!=stringGetFromFile(s, "", info->fptIn4List, stdout, 1)) {
            i++;
        }
        info->fptIn4 = (FILE**)memoryAllocate(i*sizeof(FILE*), "in init1");
        info->In4    = (char**)memoryAllocate(i*sizeof(char*), "in init1");
        info->flagIn4 = i;
        fseek(info->fptIn4List, 0L, SEEK_SET);
        i=0;
        while(NULL!=stringGetFromFile(s, "", info->fptIn4List, stdout, 1)) {
            info->In4[i] = stringGetNthWord(s, 1, " ,\t");
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
    
    if(info->flagconfigFile) {
        info->fptconfigFile = fileOpen(info->configFile, "r");
    }
    
    if(info->flagmode) {
    }
    
    if(info->flagMode) {
    }
    
    if(info->flagvariance) {
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
    sprintf(panepath, "%s/src/Tools/rec3d/WeightCalculationOfCommonLineSearchByAllSinogram/src/WeightCalculationOfCommonLineSearchByAllSinogram.pane", eospath);
    khoros_initialize(argc, argv, "EOS");
    fpt = fopen(panepath, "r");    if(NULL!=fpt) {
        fclose(fpt);
        kclui_initialize(panepath, KGEN_NONE, "EOS", "WeightCalculationOfCommonLineSearchByAllSinogram",
                     func_usage_additions,
                     func_get_args,
                     func_free_args);
    }
}
#endif /* KHOROS */ 
