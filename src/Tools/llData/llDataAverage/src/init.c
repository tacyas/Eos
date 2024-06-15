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
init0(llDataAverageInfo* info)
{
    info->fptModel = NULL;    info->flagModel = 0;
    info->fptIn     = NULL;    info->fptInList = NULL;    info->flagIn = 0;
    info->fptllInfo = NULL;    info->flagllInfo = 0;
    info->fptAve = NULL;    info->flagAve = 0;
    info->fptOutParam = stdout;    info->flagOutParam = 0;
    info->fptOutParam2     = NULL;    info->fptOutParam2List = NULL;    info->flagOutParam2 = 0;
    info->fptOut     = NULL;    info->fptOutList = NULL;    info->flagOut = 0;
    info->fptP2 = NULL;    info->flagP2 = 0;
    info->truePitch = 1.0;    info->flagtruePitch = 0;
    info->dR = 1.0;    info->flagdR = 0;
    info->rmin = 1.0;    info->flagrmin = 0;
    info->rmax = 1.0;    info->flagrmax = 0;
    info->dr = 1.0;    info->flagdr = 0;
    info->phimin = 0.0;    info->flagphimin = 0;
    info->phimax = 180.0;    info->flagphimax = 0;
    info->dphi = 5.0;    info->flagdphi = 0;
    info->zmin = 0.0;    info->flagzmin = 0;
    info->zmax = 60.0;    info->flagzmax = 0;
    info->dz = 5.0;    info->flagdz = 0;
    info->withoutAntiPole=0;
    info->CutValue = 1.0;    info->flagCutValue = 0;
    info->pvm = 0;    info->flagpvm = 0;
    info->fptpvmList = stdin;    info->flagpvmList = 0;
    info->fptLog = stdout;    info->flagLog = 0;
    info->fptconfigFile = NULL;    info->flagconfigFile = 0;
    info->mode = 0;    info->flagmode = 0;
}

void
init1(llDataAverageInfo* info)
{
    char s[1024];
    int i;
    if(!info->flagModel) {
        stringGetFromFile(s, "Model", stdin, stdout, 0);
        info->Model = stringGetNthWord(s, 1, " ,\t");
        info->flagModel++;
    }
    if(info->flagModel) {
        info->fptModel = fileOpen(info->Model, "r");
    }
    
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
    
    if(!info->flagllInfo) {
        stringGetFromFile(s, "llInfo", stdin, stdout, 0);
        info->llInfo = stringGetNthWord(s, 1, " ,\t");
        info->flagllInfo++;
    }
    if(info->flagllInfo) {
        info->fptllInfo = fileOpen(info->llInfo, "r");
    }
    
    if(!info->flagAve) {
        stringGetFromFile(s, "Ave", stdin, stdout, 0);
        info->Ave = stringGetNthWord(s, 1, " ,\t");
        info->flagAve++;
    }
    if(info->flagAve) {
        info->fptAve = fileOpen(info->Ave, "w");
    }
    
    if(info->flagOutParam) {
        info->fptOutParam = fopen(info->OutParam, "a+");
    }
    
    if(info->flagOutParam2) {
        info->fptOutParam2List = fileOpen(info->OutParam2List, "r");
        fseek(info->fptOutParam2List, 0L, SEEK_SET);
        i=0;
        while(NULL!=stringGetFromFile(s, "", info->fptOutParam2List, stdout, 1)) {
            i++;
        }
        info->fptOutParam2 = (FILE**)memoryAllocate(i*sizeof(FILE*), "in init1");
        info->OutParam2    = (char**)memoryAllocate(i*sizeof(char*), "in init1");
        info->flagOutParam2 = i;
        fseek(info->fptOutParam2List, 0L, SEEK_SET);
        i=0;
        while(NULL!=stringGetFromFile(s, "", info->fptOutParam2List, stdout, 1)) {
            info->OutParam2[i] = stringGetNthWord(s, 1, " ,\t");
            info->fptOutParam2[i] = fileOpen(info->OutParam2[i],"w");
            i++;
        }
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
    
    if(info->flagP2) {
        info->fptP2 = fileOpen(info->P2, "w");
    }
    
    if(info->flagtruePitch) {
    }
    
    if(info->flagdR) {
    }
    
    if(info->flagrmin) {
    }
    
    if(info->flagrmax) {
    }
    
    if(info->flagdr) {
    }
    
    if(info->flagphimin) {
    }
    
    if(info->flagphimax) {
    }
    
    if(info->flagdphi) {
    }
    
    if(info->flagzmin) {
    }
    
    if(info->flagzmax) {
    }
    
    if(info->flagdz) {
    }
    
    if(info->flagCutValue) {
    }
    
    if(info->flagpvm) {
    }
    
    if(info->flagpvmList) {
        info->fptpvmList = fileOpen(info->pvmList, "r");
    }
    
    if(info->flagLog) {
        info->fptLog = fopen(info->Log, "a+");
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
    sprintf(panepath, "%s/src/Tools/llData/llDataAverage/src/llDataAverage.pane", eospath);
    khoros_initialize(argc, argv, "EOS");
    fpt = fopen(panepath, "r");    if(NULL!=fpt) {
        fclose(fpt);
        kclui_initialize(panepath, KGEN_NONE, "EOS", "llDataAverage",
                     func_usage_additions,
                     func_get_args,
                     func_free_args);
    }
}
#endif /* KHOROS */ 
