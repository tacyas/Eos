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
init0(mrcImageColoringInfo* info)
{
    info->fptrIn = NULL;    info->flagrIn = 0;
    info->fptgIn = NULL;    info->flaggIn = 0;
    info->fptbIn = NULL;    info->flagbIn = 0;
    info->rHigh = 1;    info->flagrHigh = 0;
    info->rLow = 0;    info->flagrLow = 0;
    info->gHigh = 1;    info->flaggHigh = 0;
    info->gLow = 0;    info->flaggLow = 0;
    info->bHigh = 1;    info->flagbHigh = 0;
    info->bLow = 0;    info->flagbLow = 0;
    info->fptOut = NULL;    info->flagOut = 0;
    info->fptconfigFile = NULL;    info->flagconfigFile = 0;
    info->mode = 0;    info->flagmode = 0;
}

void
init1(mrcImageColoringInfo* info)
{
    char s[1024];
    int i;
    if(info->flagrIn) {
        info->fptrIn = fileOpen(info->rIn, "r");
    }
    
    if(info->flaggIn) {
        info->fptgIn = fileOpen(info->gIn, "r");
    }
    
    if(info->flagbIn) {
        info->fptbIn = fileOpen(info->bIn, "r");
    }
    
    if(info->flagrHigh) {
    }
    
    if(info->flagrLow) {
    }
    
    if(info->flaggHigh) {
    }
    
    if(info->flaggLow) {
    }
    
    if(info->flagbHigh) {
    }
    
    if(info->flagbLow) {
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
    sprintf(panepath, "%s/src/Tools/mrcImage/mrcImageColoring/src/mrcImageColoring.pane", eospath);
    khoros_initialize(argc, argv, "EOS");
    fpt = fopen(panepath, "r");    if(NULL!=fpt) {
        fclose(fpt);
        kclui_initialize(panepath, KGEN_NONE, "EOS", "mrcImageColoring",
                     func_usage_additions,
                     func_get_args,
                     func_free_args);
    }
}
#endif /* KHOROS */ 
