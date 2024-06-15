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
init0(mrcImageClusterAnalysisInfo* info)
{
    info->fptIn     = NULL;    info->fptInList = NULL;    info->flagIn = 0;
    info->fptOut = stdout;    info->flagOut = 0;
    info->Output=0;
    info->N = 1;    info->flagN = 0;
    info->Min = 0.0;    info->flagMin = 0;
    info->Iteration=0;
    info->AutoRotation = 72;    info->flagAutoRotation = 0;
    info->ARMin = 0;    info->flagARMin = 0;
    info->ARMax = 360;    info->flagARMax = 0;
    info->AutoRotationIteration = 2;    info->flagAutoRotationIteration = 0;
    info->AutoRotationMethod = 0;    info->flagAutoRotationMethod = 0;
    info->correlationMode = 19;    info->flagcorrelationMode = 0;
    info->fptLog = stdout;    info->flagLog = 0;
    info->fptLog2 = NULL;    info->flagLog2 = 0;
    info->fptLogIn = NULL;    info->flagLogIn = 0;
    info->prevFileNum = 0;    info->flagprevFileNum = 0;
    info->pthread = 0;    info->flagpthread = 0;
    info->NoRecalc=0;
    info->pvm=0;
    info->fptpvmList = NULL;    info->flagpvmList = 0;
    info->fptconfigFile = NULL;    info->flagconfigFile = 0;
    info->mode = 2;    info->flagmode = 0;
}

void
init1(mrcImageClusterAnalysisInfo* info)
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
            i++;
        }
    }
    
    if(info->flagOut) {
        info->fptOut = fileOpen(info->Out, "w");
    }
    
    if(info->flagN) {
    }
    
    if(info->flagMin) {
    }
    
    if(info->flagAutoRotation) {
    }
    
    if(info->flagARMin) {
    }
    
    if(info->flagARMax) {
    }
    
    if(info->flagAutoRotationIteration) {
    }
    
    if(info->flagAutoRotationMethod) {
    }
    
    if(info->flagcorrelationMode) {
    }
    
    if(info->flagLog) {
        info->fptLog = fopen(info->Log, "a+");
    }
    
    if(info->flagLog2) {
        info->fptLog2 = fopen(info->Log2, "a+");
    }
    
    if(info->flagLogIn) {
        info->fptLogIn = fileOpen(info->LogIn, "r");
    }
    
    if(info->flagprevFileNum) {
    }
    
    if(info->flagpthread) {
    }
    
    if(info->flagpvmList) {
        info->fptpvmList = fileOpen(info->pvmList, "r");
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
    sprintf(panepath, "%s/src/Tools/mrcImage/mrcImageClusterAnalysis/src/mrcImageClusterAnalysis.pane", eospath);
    khoros_initialize(argc, argv, "EOS");
    fpt = fopen(panepath, "r");    if(NULL!=fpt) {
        fclose(fpt);
        kclui_initialize(panepath, KGEN_NONE, "EOS", "mrcImageClusterAnalysis",
                     func_usage_additions,
                     func_get_args,
                     func_free_args);
    }
}
#endif /* KHOROS */ 
