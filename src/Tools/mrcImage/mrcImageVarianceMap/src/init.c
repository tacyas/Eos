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
init0(mrcImageVarianceMapInfo* info)
{
    info->fptIn     = NULL;    info->fptInList = NULL;    info->flagIn = 0;
    info->fptIn2 = NULL;    info->flagIn2 = 0;
    info->fptIn2Var = NULL;    info->flagIn2Var = 0;
    info->In2N = 0;    info->flagIn2N = 0;
    info->NorA = 0.0;    info->flagNorA = 0;
    info->NorB = 1.0;    info->flagNorB = 0;
    info->fptRef     = NULL;    info->fptRefList = NULL;    info->flagRef = 0;
    info->fptRef2 = NULL;    info->flagRef2 = 0;
    info->fptRef2Var = NULL;    info->flagRef2Var = 0;
    info->Ref2N = 0;    info->flagRef2N = 0;
    info->NorARef = 0.0;    info->flagNorARef = 0;
    info->NorBRef = 1.0;    info->flagNorBRef = 0;
    info->fptInAndRef2 = NULL;    info->flagInAndRef2 = 0;
    info->fptInAndRef2Var = NULL;    info->flagInAndRef2Var = 0;
    info->InAndRef2N = 0;    info->flagInAndRef2N = 0;
    info->fptOut = NULL;    info->flagOut = 0;
    info->fptOutV = NULL;    info->flagOutV = 0;
    info->fptconfigFile = NULL;    info->flagconfigFile = 0;
    info->mode = 0;    info->flagmode = 0;
}

void
init1(mrcImageVarianceMapInfo* info)
{
    char s[1024];
    int i;
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
    
    if(info->flagIn2) {
        info->fptIn2 = fileOpen(info->In2, "r");
    }
    
    if(info->flagIn2Var) {
        info->fptIn2Var = fileOpen(info->In2Var, "r");
    }
    
    if(info->flagIn2N) {
    }
    
    if(info->flagNorA) {
    }
    
    if(info->flagNorB) {
    }
    
    if(info->flagRef) {
        info->fptRefList = fileOpen(info->RefList, "r");
        fseek(info->fptRefList, 0L, SEEK_SET);
        i=0;
        while(NULL!=stringGetFromFile(s, "", info->fptRefList, stdout, 1)) {
            i++;
        }
        info->fptRef = (FILE**)memoryAllocate(i*sizeof(FILE*), "in init1");
        info->Ref    = (char**)memoryAllocate(i*sizeof(char*), "in init1");
        info->flagRef = i;
        fseek(info->fptRefList, 0L, SEEK_SET);
        i=0;
        while(NULL!=stringGetFromFile(s, "", info->fptRefList, stdout, 1)) {
            info->Ref[i] = stringGetNthWord(s, 1, " ,\t");
            info->fptRef[i] = fileOpen(info->Ref[i],"r");
            i++;
        }
    }
    
    if(info->flagRef2) {
        info->fptRef2 = fileOpen(info->Ref2, "r");
    }
    
    if(info->flagRef2Var) {
        info->fptRef2Var = fileOpen(info->Ref2Var, "r");
    }
    
    if(info->flagRef2N) {
    }
    
    if(info->flagNorARef) {
    }
    
    if(info->flagNorBRef) {
    }
    
    if(info->flagInAndRef2) {
        info->fptInAndRef2 = fileOpen(info->InAndRef2, "r");
    }
    
    if(info->flagInAndRef2Var) {
        info->fptInAndRef2Var = fileOpen(info->InAndRef2Var, "r");
    }
    
    if(info->flagInAndRef2N) {
    }
    
    if(info->flagOut) {
        info->fptOut = fileOpen(info->Out, "w");
    }
    
    if(info->flagOutV) {
        info->fptOutV = fileOpen(info->OutV, "w");
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
    sprintf(panepath, "%s/src/Tools/mrcImage/mrcImageVarianceMap/src/mrcImageVarianceMap.pane", eospath);
    khoros_initialize(argc, argv, "EOS");
    fpt = fopen(panepath, "r");    if(NULL!=fpt) {
        fclose(fpt);
        kclui_initialize(panepath, KGEN_NONE, "EOS", "mrcImageVarianceMap",
                     func_usage_additions,
                     func_get_args,
                     func_free_args);
    }
}
#endif /* KHOROS */ 
