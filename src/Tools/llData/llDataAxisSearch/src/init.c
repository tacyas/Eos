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
init0(llDataAxisSearchInfo* info)
{
    info->fptIn1 = NULL;    info->flagIn1 = 0;
    info->fptIn2 = NULL;    info->flagIn2 = 0;
    info->fptOut1 = NULL;    info->flagOut1 = 0;
    info->fptOut2 = NULL;    info->flagOut2 = 0;
    info->fptAvg = NULL;    info->flagAvg = 0;
    info->fptOut = NULL;    info->flagOut = 0;
    info->fptOutP2 = NULL;    info->flagOutP2 = 0;
    info->truePitch = 0.0;    info->flagtruePitch = 0;
    info->fptL = NULL;    info->flagL = 0;
    info->Omin = 0.0;    info->flagOmin = 0;
    info->Omax = 0.0;    info->flagOmax = 0;
    info->Odelta = 1.0;    info->flagOdelta = 0;
    info->xmin = -10.0;    info->flagxmin = 0;
    info->xmax = 10.0;    info->flagxmax = 0;
    info->xdelta = 0.1;    info->flagxdelta = 0;
    info->R = 10.0;    info->flagR = 0;
    info->mode = 0;    info->flagmode = 0;
    info->fptconfigFile = NULL;    info->flagconfigFile = 0;
}

void
init1(llDataAxisSearchInfo* info)
{
    char s[1024];
    int i;
    if(info->flagIn1) {
        info->fptIn1 = fileOpen(info->In1, "r");
    }
    
    if(info->flagIn2) {
        info->fptIn2 = fileOpen(info->In2, "r");
    }
    
    if(info->flagOut1) {
        info->fptOut1 = fileOpen(info->Out1, "w");
    }
    
    if(info->flagOut2) {
        info->fptOut2 = fileOpen(info->Out2, "w");
    }
    
    if(info->flagAvg) {
        info->fptAvg = fileOpen(info->Avg, "w");
    }
    
    if(info->flagOut) {
        info->fptOut = fileOpen(info->Out, "w");
    }
    
    if(info->flagOutP2) {
        info->fptOutP2 = fileOpen(info->OutP2, "w");
    }
    
    if(info->flagtruePitch) {
    }
    
    if(info->flagL) {
        info->fptL = fileOpen(info->L, "r");
    }
    
    if(info->flagOmin) {
    }
    
    if(info->flagOmax) {
    }
    
    if(info->flagOdelta) {
    }
    
    if(info->flagxmin) {
    }
    
    if(info->flagxmax) {
    }
    
    if(info->flagxdelta) {
    }
    
    if(info->flagR) {
    }
    
    if(info->flagmode) {
    }
    
    if(info->flagconfigFile) {
        info->fptconfigFile = fileOpen(info->configFile, "r");
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
    sprintf(panepath, "%s/src/Tools/llData/llDataAxisSearch/src/llDataAxisSearch.pane", eospath);
    khoros_initialize(argc, argv, "EOS");
    fpt = fopen(panepath, "r");    if(NULL!=fpt) {
        fclose(fpt);
        kclui_initialize(panepath, KGEN_NONE, "EOS", "llDataAxisSearch",
                     func_usage_additions,
                     func_get_args,
                     func_free_args);
    }
}
#endif /* KHOROS */ 
