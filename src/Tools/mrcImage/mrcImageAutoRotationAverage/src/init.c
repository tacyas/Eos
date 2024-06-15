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
init0(mrcImageAutoRotationAverageInfo* info)
{
    info->fptIn     = stdin;    info->fptInList = stdin;    info->flagIn = 0;
    info->fptRef = NULL;    info->flagRef = 0;
    info->fptOut = NULL;    info->flagOut = 0;
    info->Min = 0.0;    info->flagMin = 0;
    info->Max = 360.0;    info->flagMax = 0;
    info->Delta = 5.0;    info->flagDelta = 0;
    info->Iter = 2;    info->flagIter = 0;
    info->iter = 2;    info->flagiter = 0;
    info->CorMode = 16;    info->flagCorMode = 0;
    info->Method = 0;    info->flagMethod = 0;
    info->Periodic=0;
    info->maxIter = 10;    info->flagmaxIter = 0;
    info->rmsd = 1e-2;    info->flagrmsd = 0;
    info->fptLog = stdout;    info->flagLog = 0;
    info->Thres = 0.2;    info->flagThres = 0;
    info->fptconfigFile = NULL;    info->flagconfigFile = 0;
    info->mode = 0;    info->flagmode = 0;
}

void
init1(mrcImageAutoRotationAverageInfo* info)
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
    
    if(info->flagMin) {
    }
    
    if(info->flagMax) {
    }
    
    if(info->flagDelta) {
    }
    
    if(info->flagIter) {
    }
    
    if(info->flagiter) {
    }
    
    if(info->flagCorMode) {
    }
    
    if(info->flagMethod) {
    }
    
    if(info->flagmaxIter) {
    }
    
    if(info->flagrmsd) {
    }
    
    if(info->flagLog) {
        info->fptLog = fileOpen(info->Log, "w");
    }
    
    if(info->flagThres) {
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
    sprintf(panepath, "%s/src/Tools/mrcImage/mrcImageAutoRotationAverage/src/mrcImageAutoRotationAverage.pane", eospath);
    khoros_initialize(argc, argv, "EOS");
    fpt = fopen(panepath, "r");    if(NULL!=fpt) {
        fclose(fpt);
        kclui_initialize(panepath, KGEN_NONE, "EOS", "mrcImageAutoRotationAverage",
                     func_usage_additions,
                     func_get_args,
                     func_free_args);
    }
}
#endif /* KHOROS */ 
