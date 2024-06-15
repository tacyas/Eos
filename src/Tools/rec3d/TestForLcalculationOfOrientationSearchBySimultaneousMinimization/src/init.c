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
init0(TestForLcalculationOfOrientationSearchBySimultaneousMinimizationInfo* info)
{
    info->fptIn     = NULL;    info->fptInList = NULL;    info->flagIn = 0;
    info->fptiid = NULL;    info->flagiid = 0;
    info->fptOut = NULL;    info->flagOut = 0;
    info->fptconfigFile = NULL;    info->flagconfigFile = 0;
    info->mode = 0;    info->flagmode = 0;
    info->mode2 = 0;    info->flagmode2 = 0;
    info->dtheta = 0;    info->flagdtheta = 0;
    info->dpsi = 0;    info->flagdpsi = 0;
    info->ep = 0;    info->flagep = 0;
    info->modeL = 0;    info->flagmodeL = 0;
    info->modeTA = 0;    info->flagmodeTA = 0;
    info->fptLog = stdout;    info->flagLog = 0;
    info->fptLog2 = stdout;    info->flagLog2 = 0;
    info->fptm2 = NULL;    info->flagm2 = 0;
    info->fptm3 = NULL;    info->flagm3 = 0;
}

void
init1(TestForLcalculationOfOrientationSearchBySimultaneousMinimizationInfo* info)
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
    
    if(!info->flagiid) {
        stringGetFromFile(s, "iid", stdin, stdout, 0);
        info->iid = stringGetNthWord(s, 1, " ,\t");
        info->flagiid++;
    }
    if(info->flagiid) {
        info->fptiid = fileOpen(info->iid, "r");
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
    
    if(info->flagmode2) {
    }
    
    if(info->flagdtheta) {
    }
    
    if(info->flagdpsi) {
    }
    
    if(info->flagep) {
    }
    
    if(info->flagmodeL) {
    }
    
    if(info->flagmodeTA) {
    }
    
    if(info->flagLog) {
        info->fptLog = fileOpen(info->Log, "w");
    }
    
    if(info->flagLog2) {
        info->fptLog2 = fileOpen(info->Log2, "w");
    }
    
    if(info->flagm2) {
        info->fptm2 = fileOpen(info->m2, "w");
    }
    
    if(info->flagm3) {
        info->fptm3 = fileOpen(info->m3, "w");
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
    sprintf(panepath, "%s/src/Tools/rec3d/TestForLcalculationOfOrientationSearchBySimultaneousMinimization/src/TestForLcalculationOfOrientationSearchBySimultaneousMinimization.pane", eospath);
    khoros_initialize(argc, argv, "EOS");
    fpt = fopen(panepath, "r");    if(NULL!=fpt) {
        fclose(fpt);
        kclui_initialize(panepath, KGEN_NONE, "EOS", "TestForLcalculationOfOrientationSearchBySimultaneousMinimization",
                     func_usage_additions,
                     func_get_args,
                     func_free_args);
    }
}
#endif /* KHOROS */ 
