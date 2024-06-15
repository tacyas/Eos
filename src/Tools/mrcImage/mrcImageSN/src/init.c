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
init0(mrcImageSNInfo* info)
{
    info->fptIn     = NULL;    info->fptInList = NULL;    info->flagIn = 0;
    info->fptAvg = NULL;    info->flagAvg = 0;
    info->fptTrimmedAvg = NULL;    info->flagTrimmedAvg = 0;
    info->fptMedian = NULL;    info->flagMedian = 0;
    info->fptSN = NULL;    info->flagSN = 0;
    info->fptt = NULL;    info->flagt = 0;
    info->fptSE = NULL;    info->flagSE = 0;
    info->fptSD = NULL;    info->flagSD = 0;
    info->fptVar = NULL;    info->flagVar = 0;
    info->TrimmedRange = 0.1;    info->flagTrimmedRange = 0;
    info->fptconfigFile = NULL;    info->flagconfigFile = 0;
    info->mode = 0;    info->flagmode = 0;
}

void
init1(mrcImageSNInfo* info)
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
    
    if(info->flagAvg) {
        info->fptAvg = fileOpen(info->Avg, "w");
    }
    
    if(info->flagTrimmedAvg) {
        info->fptTrimmedAvg = fileOpen(info->TrimmedAvg, "w");
    }
    
    if(info->flagMedian) {
        info->fptMedian = fileOpen(info->Median, "w");
    }
    
    if(info->flagSN) {
        info->fptSN = fileOpen(info->SN, "w");
    }
    
    if(info->flagt) {
        info->fptt = fileOpen(info->t, "w");
    }
    
    if(info->flagSE) {
        info->fptSE = fileOpen(info->SE, "w");
    }
    
    if(info->flagSD) {
        info->fptSD = fileOpen(info->SD, "w");
    }
    
    if(info->flagVar) {
        info->fptVar = fileOpen(info->Var, "w");
    }
    
    if(info->flagTrimmedRange) {
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
    sprintf(panepath, "%s/src/Tools/mrcImage/mrcImageSN/src/mrcImageSN.pane", eospath);
    khoros_initialize(argc, argv, "EOS");
    fpt = fopen(panepath, "r");    if(NULL!=fpt) {
        fclose(fpt);
        kclui_initialize(panepath, KGEN_NONE, "EOS", "mrcImageSN",
                     func_usage_additions,
                     func_get_args,
                     func_free_args);
    }
}
#endif /* KHOROS */ 
