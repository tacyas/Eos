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
init0(mrcImagesSinogramCorrelationInfo* info)
{
    info->fptIn     = NULL;    info->fptInList = NULL;    info->flagIn = 0;
    info->OutHeader = stringGetNthWord("test", 1, "\0");    info->flagOutHeader = 0;
    info->Rd = stringGetNthWord("Result", 1, "\0");    info->flagRd = 0;
    info->Nd = stringGetNthWord("Normal", 1, "\0");    info->flagNd = 0;
    info->D1d = stringGetNthWord("Derivation1D", 1, "\0");    info->flagD1d = 0;
    info->D2d = stringGetNthWord("Derivation2D", 1, "\0");    info->flagD2d = 0;
    info->Ld = stringGetNthWord("Length", 1, "\0");    info->flagLd = 0;
    info->CorrelationExtension = stringGetNthWord("cor", 1, "\0");    info->flagCorrelationExtension = 0;
    info->ListExtension = stringGetNthWord("list", 1, "\0");    info->flagListExtension = 0;
    info->fptconfigFile = NULL;    info->flagconfigFile = 0;
    info->mode = 0;    info->flagmode = 0;
    info->Nmode = 0;    info->flagNmode = 0;
    info->D1mode = 0;    info->flagD1mode = 0;
    info->D2mode = 0;    info->flagD2mode = 0;
    info->Lmode = 0;    info->flagLmode = 0;
    info->LengthThresholdMode = 0;    info->flagLengthThresholdMode = 0;
    info->LengthThresholdRatio = 0.25;    info->flagLengthThresholdRatio = 0;
    info->CM = 0;    info->flagCM = 0;
}

void
init1(mrcImagesSinogramCorrelationInfo* info)
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
    
    if(info->flagOutHeader) {
    }
    
    if(info->flagRd) {
    }
    
    if(info->flagNd) {
    }
    
    if(info->flagD1d) {
    }
    
    if(info->flagD2d) {
    }
    
    if(info->flagLd) {
    }
    
    if(info->flagCorrelationExtension) {
    }
    
    if(info->flagListExtension) {
    }
    
    if(info->flagconfigFile) {
        info->fptconfigFile = fileOpen(info->configFile, "r");
    }
    
    if(info->flagmode) {
    }
    
    if(info->flagNmode) {
    }
    
    if(info->flagD1mode) {
    }
    
    if(info->flagD2mode) {
    }
    
    if(info->flagLmode) {
    }
    
    if(info->flagLengthThresholdMode) {
    }
    
    if(info->flagLengthThresholdRatio) {
    }
    
    if(info->flagCM) {
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
    sprintf(panepath, "%s/src/Tools/mrcImage/mrcImagesSinogramCorrelation/src/mrcImagesSinogramCorrelation.pane", eospath);
    khoros_initialize(argc, argv, "EOS");
    fpt = fopen(panepath, "r");    if(NULL!=fpt) {
        fclose(fpt);
        kclui_initialize(panepath, KGEN_NONE, "EOS", "mrcImagesSinogramCorrelation",
                     func_usage_additions,
                     func_get_args,
                     func_free_args);
    }
}
#endif /* KHOROS */ 
