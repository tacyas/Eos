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
init0(llDataNEstimationInfo* info)
{
    info->r = 220;    info->flagr = 0;
    info->R = 24;    info->flagR = 0;
    info->xstep = 7;    info->flagxstep = 0;
    info->Width = 500;    info->flagWidth = 0;
    info->fptOut = stdout;    info->flagOut = 0;
    info->fptconfigFile = NULL;    info->flagconfigFile = 0;
    info->mode = 0;    info->flagmode = 0;
}

void
init1(llDataNEstimationInfo* info)
{
    char s[1024];
    int i;
    if(!info->flagr) {
        stringGetFromFile(s, "r", stdin, stdout, 0);
        info->r = stringGetNthRealData(s, 1, ", \t");
        info->flagr++;
    }
    if(info->flagr) {
    }
    
    if(!info->flagR) {
        stringGetFromFile(s, "R", stdin, stdout, 0);
        info->R = stringGetNthRealData(s, 1, ", \t");
        info->flagR++;
    }
    if(info->flagR) {
    }
    
    if(!info->flagxstep) {
        stringGetFromFile(s, "xstep", stdin, stdout, 0);
        info->xstep = stringGetNthRealData(s, 1, ", \t");
        info->flagxstep++;
    }
    if(info->flagxstep) {
    }
    
    if(!info->flagWidth) {
        stringGetFromFile(s, "Width", stdin, stdout, 0);
        info->Width = stringGetNthRealData(s, 1, ", \t");
        info->flagWidth++;
    }
    if(info->flagWidth) {
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
    sprintf(panepath, "%s/src/Tools/llData/llDataNEstimation/src/llDataNEstimation.pane", eospath);
    khoros_initialize(argc, argv, "EOS");
    fpt = fopen(panepath, "r");    if(NULL!=fpt) {
        fclose(fpt);
        kclui_initialize(panepath, KGEN_NONE, "EOS", "llDataNEstimation",
                     func_usage_additions,
                     func_get_args,
                     func_free_args);
    }
}
#endif /* KHOROS */ 
