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
init0(FETsmallMapSetCreate_forSimultaneousMinimizationInfo* info)
{
    info->fptInML = NULL;    info->flagInML = 0;
    info->fptOutMS = NULL;    info->flagOutMS = 0;
    info->InSS = 5;    info->flagInSS = 0;
    info->InSR = 15;    info->flagInSR = 0;
    info->fptconfigFile = NULL;    info->flagconfigFile = 0;
    info->mode = 0;    info->flagmode = 0;
}

void
init1(FETsmallMapSetCreate_forSimultaneousMinimizationInfo* info)
{
    char s[1024];
    int i;
    if(!info->flagInML) {
        stringGetFromFile(s, "InML", stdin, stdout, 0);
        info->InML = stringGetNthWord(s, 1, " ,\t");
        info->flagInML++;
    }
    if(info->flagInML) {
        info->fptInML = fileOpen(info->InML, "r");
    }
    
    if(!info->flagOutMS) {
        stringGetFromFile(s, "OutMS", stdin, stdout, 0);
        info->OutMS = stringGetNthWord(s, 1, " ,\t");
        info->flagOutMS++;
    }
    if(info->flagOutMS) {
        info->fptOutMS = fileOpen(info->OutMS, "w");
    }
    
    if(info->flagInSS) {
    }
    
    if(info->flagInSR) {
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
    sprintf(panepath, "%s/src/Tools/rec3d/FETsmallMapSetCreate_forSimultaneousMinimization/src/FETsmallMapSetCreate_forSimultaneousMinimization.pane", eospath);
    khoros_initialize(argc, argv, "EOS");
    fpt = fopen(panepath, "r");    if(NULL!=fpt) {
        fclose(fpt);
        kclui_initialize(panepath, KGEN_NONE, "EOS", "FETsmallMapSetCreate_forSimultaneousMinimization",
                     func_usage_additions,
                     func_get_args,
                     func_free_args);
    }
}
#endif /* KHOROS */ 
