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
init0(FETOrientationSearchByAnnealingInfo* info)
{
    info->fptInMS = NULL;    info->flagInMS = 0;
    info->fptInFL = NULL;    info->flagInFL = 0;
    info->fptInML = NULL;    info->flagInML = 0;
    info->ITemp = 300.0;    info->flagITemp = 0;
    info->AS1 = 10;    info->flagAS1 = 0;
    info->AS2 = 0.9;    info->flagAS2 = 0;
    info->AS3 = 10;    info->flagAS3 = 0;
    info->fptOut = NULL;    info->flagOut = 0;
    info->fptconfigFile = NULL;    info->flagconfigFile = 0;
    info->mode = 0;    info->flagmode = 0;
}

void
init1(FETOrientationSearchByAnnealingInfo* info)
{
    char s[1024];
    int i;
    if(!info->flagInMS) {
        stringGetFromFile(s, "InMS", stdin, stdout, 0);
        info->InMS = stringGetNthWord(s, 1, " ,\t");
        info->flagInMS++;
    }
    if(info->flagInMS) {
        info->fptInMS = fileOpen(info->InMS, "r");
    }
    
    if(info->flagInFL) {
        info->fptInFL = fileOpen(info->InFL, "r");
    }
    
    if(info->flagInML) {
        info->fptInML = fileOpen(info->InML, "r");
    }
    
    if(info->flagITemp) {
    }
    
    if(info->flagAS1) {
    }
    
    if(info->flagAS2) {
    }
    
    if(info->flagAS3) {
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
    sprintf(panepath, "%s/src/Tools/rec3d/FETOrientationSearchByAnnealing/src/FETOrientationSearchByAnnealing.pane", eospath);
    khoros_initialize(argc, argv, "EOS");
    fpt = fopen(panepath, "r");    if(NULL!=fpt) {
        fclose(fpt);
        kclui_initialize(panepath, KGEN_NONE, "EOS", "FETOrientationSearchByAnnealing",
                     func_usage_additions,
                     func_get_args,
                     func_free_args);
    }
}
#endif /* KHOROS */ 
