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
init0(mrcImageOrientationSearchBySimultaneousMinimizationInfo* info)
{
    info->fptIn     = NULL;    info->fptInList = NULL;    info->flagIn = 0;
    info->fptOut = NULL;    info->flagOut = 0;
    info->fptconfigFile = NULL;    info->flagconfigFile = 0;
    info->mode = 0;    info->flagmode = 0;
    info->dtheta = 1;    info->flagdtheta = 0;
    info->dpsi = 1;    info->flagdpsi = 0;
    info->ms = 0;    info->flagms = 0;
    info->ird = 1;    info->flagird = 0;
    info->MC = 100;    info->flagMC = 0;
    info->FileNameHeader = stringGetNthWord("EulerAngle", 1, "\0");    info->flagFileNameHeader = 0;
    info->mid = 0;    info->flagmid = 0;
    info->fptInInitial = NULL;    info->flagInInitial = 0;
    info->msp = 0;    info->flagmsp = 0;
    info->maa = 0;    info->flagmaa = 0;
    info->pdtheta = 0;    info->flagpdtheta = 0;
    info->pdpsi = 0;    info->flagpdpsi = 0;
    info->modeL = 0;    info->flagmodeL = 0;
    info->modeTA = 0;    info->flagmodeTA = 0;
    info->modeCA = 0;    info->flagmodeCA = 0;
    info->TCA = 0;    info->flagTCA = 0;
    info->modeF = 0;    info->flagmodeF = 0;
}

void
init1(mrcImageOrientationSearchBySimultaneousMinimizationInfo* info)
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
    
    if(!info->flagOut) {
        stringGetFromFile(s, "Out", stdin, stdout, 0);
        info->Out = stringGetNthWord(s, 1, " ,\t");
        info->flagOut++;
    }
    if(info->flagOut) {
    }
    
    if(info->flagconfigFile) {
        info->fptconfigFile = fileOpen(info->configFile, "r");
    }
    
    if(info->flagmode) {
    }
    
    if(info->flagdtheta) {
    }
    
    if(info->flagdpsi) {
    }
    
    if(info->flagms) {
    }
    
    if(info->flagird) {
    }
    
    if(info->flagMC) {
    }
    
    if(info->flagFileNameHeader) {
    }
    
    if(info->flagmid) {
    }
    
    if(info->flagInInitial) {
        info->fptInInitial = fileOpen(info->InInitial, "r");
    }
    
    if(info->flagmsp) {
    }
    
    if(info->flagmaa) {
    }
    
    if(info->flagpdtheta) {
    }
    
    if(info->flagpdpsi) {
    }
    
    if(info->flagmodeL) {
    }
    
    if(info->flagmodeTA) {
    }
    
    if(info->flagmodeCA) {
    }
    
    if(info->flagTCA) {
    }
    
    if(info->flagmodeF) {
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
    sprintf(panepath, "%s/src/Tools/rec3d/mrcImageOrientationSearchBySimultaneousMinimization/src/mrcImageOrientationSearchBySimultaneousMinimization.pane", eospath);
    khoros_initialize(argc, argv, "EOS");
    fpt = fopen(panepath, "r");    if(NULL!=fpt) {
        fclose(fpt);
        kclui_initialize(panepath, KGEN_NONE, "EOS", "mrcImageOrientationSearchBySimultaneousMinimization",
                     func_usage_additions,
                     func_get_args,
                     func_free_args);
    }
}
#endif /* KHOROS */ 
