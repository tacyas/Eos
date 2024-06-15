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
init0(ctfDeterminationFromThonRingInfo* info)
{
    info->fptIn = stdin;    info->flagIn = 0;
    info->fptOut = stdout;    info->flagOut = 0;
    info->fptOut2 = NULL;    info->flagOut2 = 0;
    info->kV = 200;    info->flagkV = 0;
    info->Cs = 1.7;    info->flagCs = 0;
    info->minDef = 0.0;    info->flagminDef = 0;
    info->maxDef = 200000.0;    info->flagmaxDef = 0;
    info->delDef = 1000.0;    info->flagdelDef = 0;
    info->minAmp = 0.0;    info->flagminAmp = 0;
    info->maxAmp = 0.4;    info->flagmaxAmp = 0;
    info->delAmp = 0.005;    info->flagdelAmp = 0;
    info->fptconfigFile = NULL;    info->flagconfigFile = 0;
    info->mode = 0;    info->flagmode = 0;
    info->R = NULL;    info->flagR = 0;
}

void
init1(ctfDeterminationFromThonRingInfo* info)
{
    char s[1024];
    int i;
    if(info->flagIn) {
        info->fptIn = fileOpen(info->In, "r");
    }
    
    if(info->flagOut) {
        info->fptOut = fileOpen(info->Out, "w");
    }
    
    if(info->flagOut2) {
        info->fptOut2 = fileOpen(info->Out2, "w");
    }
    
    if(info->flagkV) {
    }
    
    if(info->flagCs) {
    }
    
    if(info->flagminDef) {
    }
    
    if(info->flagmaxDef) {
    }
    
    if(info->flagdelDef) {
    }
    
    if(info->flagminAmp) {
    }
    
    if(info->flagmaxAmp) {
    }
    
    if(info->flagdelAmp) {
    }
    
    if(info->flagconfigFile) {
        info->fptconfigFile = fileOpen(info->configFile, "r");
    }
    
    if(info->flagmode) {
    }
    
    if(info->flagR) {
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
    sprintf(panepath, "%s/src/Tools/ctfInfo/ctfDeterminationFromThonRing/src/ctfDeterminationFromThonRing.pane", eospath);
    khoros_initialize(argc, argv, "EOS");
    fpt = fopen(panepath, "r");    if(NULL!=fpt) {
        fclose(fpt);
        kclui_initialize(panepath, KGEN_NONE, "EOS", "ctfDeterminationFromThonRing",
                     func_usage_additions,
                     func_get_args,
                     func_free_args);
    }
}
#endif /* KHOROS */ 
