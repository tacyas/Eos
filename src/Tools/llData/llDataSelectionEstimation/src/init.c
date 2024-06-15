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
init0(llDataSelectionEstimationInfo* info)
{
    info->N1 = 0;    info->flagN1 = 0;
    info->L1 = 161;    info->flagL1 = 0;
    info->N2 = 14;    info->flagN2 = 0;
    info->L2 = 12;    info->flagL2 = 0;
    info->tmax = 100;    info->flagtmax = 0;
    info->umax = 200;    info->flagumax = 0;
    info->r = 0.1;    info->flagr = 0;
    info->fptOut = stdout;    info->flagOut = 0;
    info->fptconfigFile = NULL;    info->flagconfigFile = 0;
    info->mode = 0;    info->flagmode = 0;
}

void
init1(llDataSelectionEstimationInfo* info)
{
    char s[1024];
    int i;
    if(!info->flagN1) {
        stringGetFromFile(s, "N1", stdin, stdout, 0);
        info->N1 = stringGetNthRealData(s, 1, ", \t");
        info->flagN1++;
    }
    if(info->flagN1) {
    }
    
    if(!info->flagL1) {
        stringGetFromFile(s, "L1", stdin, stdout, 0);
        info->L1 = stringGetNthRealData(s, 1, ", \t");
        info->flagL1++;
    }
    if(info->flagL1) {
    }
    
    if(!info->flagN2) {
        stringGetFromFile(s, "N2", stdin, stdout, 0);
        info->N2 = stringGetNthRealData(s, 1, ", \t");
        info->flagN2++;
    }
    if(info->flagN2) {
    }
    
    if(!info->flagL2) {
        stringGetFromFile(s, "L2", stdin, stdout, 0);
        info->L2 = stringGetNthRealData(s, 1, ", \t");
        info->flagL2++;
    }
    if(info->flagL2) {
    }
    
    if(info->flagtmax) {
    }
    
    if(info->flagumax) {
    }
    
    if(info->flagr) {
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
    sprintf(panepath, "%s/src/Tools/llData/llDataSelectionEstimation/src/llDataSelectionEstimation.pane", eospath);
    khoros_initialize(argc, argv, "EOS");
    fpt = fopen(panepath, "r");    if(NULL!=fpt) {
        fclose(fpt);
        kclui_initialize(panepath, KGEN_NONE, "EOS", "llDataSelectionEstimation",
                     func_usage_additions,
                     func_get_args,
                     func_free_args);
    }
}
#endif /* KHOROS */ 
