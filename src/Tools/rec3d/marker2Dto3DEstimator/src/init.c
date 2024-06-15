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
init0(marker2Dto3DEstimatorInfo* info)
{
    info->fptIn     = NULL;    info->fptInList = NULL;    info->flagIn = 0;
    info->InType = 2;    info->flagInType = 0;
    info->fptOut     = NULL;    info->fptOutList = NULL;    info->flagOut = 0;
    info->OutType = 2;    info->flagOutType = 0;
    info->fptOutEA     = NULL;    info->fptOutEAList = NULL;    info->flagOutEA = 0;
    info->ZeroPlane = 0;    info->flagZeroPlane = 0;
    info->fptconfigFile = NULL;    info->flagconfigFile = 0;
    info->mode = 0;    info->flagmode = 0;
}

void
init1(marker2Dto3DEstimatorInfo* info)
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
    
    if(info->flagInType) {
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
    
    if(info->flagOutType) {
    }
    
    if(!info->flagOutEA) {
        stringGetFromFile(s, "OutEA", stdin, stdout, 0);
        info->OutEAList = stringGetNthWord(s, 1, " ,\t");
        info->flagOutEA++;
    }
    if(info->flagOutEA) {
        info->fptOutEAList = fileOpen(info->OutEAList, "r");
        fseek(info->fptOutEAList, 0L, SEEK_SET);
        i=0;
        while(NULL!=stringGetFromFile(s, "", info->fptOutEAList, stdout, 1)) {
            i++;
        }
        info->fptOutEA = (FILE**)memoryAllocate(i*sizeof(FILE*), "in init1");
        info->OutEA    = (char**)memoryAllocate(i*sizeof(char*), "in init1");
        info->flagOutEA = i;
        fseek(info->fptOutEAList, 0L, SEEK_SET);
        i=0;
        while(NULL!=stringGetFromFile(s, "", info->fptOutEAList, stdout, 1)) {
            info->OutEA[i] = stringGetNthWord(s, 1, " ,\t");
            info->fptOutEA[i] = fileOpen(info->OutEA[i],"w");
            i++;
        }
    }
    
    if(info->flagZeroPlane) {
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
    sprintf(panepath, "%s/src/Tools/rec3d/marker2Dto3DEstimator/src/marker2Dto3DEstimator.pane", eospath);
    khoros_initialize(argc, argv, "EOS");
    fpt = fopen(panepath, "r");    if(NULL!=fpt) {
        fclose(fpt);
        kclui_initialize(panepath, KGEN_NONE, "EOS", "marker2Dto3DEstimator",
                     func_usage_additions,
                     func_get_args,
                     func_free_args);
    }
}
#endif /* KHOROS */ 
