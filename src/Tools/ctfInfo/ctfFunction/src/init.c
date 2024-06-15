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
init0(ctfFunctionInfo* info)
{
    info->fptOut = stdout;    info->flagOut = 0;
    info->Rmax = 0.1;    info->flagRmax = 0;
    info->dR = 0.0001;    info->flagdR = 0;
    info->kV = 200;    info->flagkV = 0;
    info->Cs = 2.1;    info->flagCs = 0;
    info->Defocus = 27000;    info->flagDefocus = 0;
    info->AoverP = 0.0;    info->flagAoverP = 0;
    info->Ain = 0.02;    info->flagAin = 0;
    info->ctfMode = 32;    info->flagctfMode = 0;
    info->pvm = 0;    info->flagpvm = 0;
    info->fptpvmList = stdin;    info->flagpvmList = 0;
    info->fptconfigFile = NULL;    info->flagconfigFile = 0;
    info->mode = 0;    info->flagmode = 0;
}

void
init1(ctfFunctionInfo* info)
{
    char s[1024];
    int i;
    if(info->flagOut) {
        info->fptOut = fileOpen(info->Out, "w");
    }
    
    if(info->flagRmax) {
    }
    
    if(info->flagdR) {
    }
    
    if(info->flagkV) {
    }
    
    if(info->flagCs) {
    }
    
    if(!info->flagDefocus) {
        stringGetFromFile(s, "Defocus", stdin, stdout, 0);
        info->Defocus = stringGetNthRealData(s, 1, ", \t");
        info->flagDefocus++;
    }
    if(info->flagDefocus) {
    }
    
    if(info->flagAoverP) {
    }
    
    if(info->flagAin) {
    }
    
    if(info->flagctfMode) {
    }
    
    if(info->flagpvm) {
    }
    
    if(info->flagpvmList) {
        info->fptpvmList = fileOpen(info->pvmList, "r");
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
    sprintf(panepath, "%s/src/Tools/ctfInfo/ctfFunction/src/ctfFunction.pane", eospath);
    khoros_initialize(argc, argv, "EOS");
    fpt = fopen(panepath, "r");    if(NULL!=fpt) {
        fclose(fpt);
        kclui_initialize(panepath, KGEN_NONE, "EOS", "ctfFunction",
                     func_usage_additions,
                     func_get_args,
                     func_free_args);
    }
}
#endif /* KHOROS */ 
