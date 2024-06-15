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
init0(pdbChargeFitInfo* info)
{
    info->fptInFix = NULL;    info->flagInFix = 0;
    info->fptInMove = NULL;    info->flagInMove = 0;
    info->fptOutTxt = NULL;    info->flagOutTxt = 0;
    info->symmetry = 0.47096;    info->flagsymmetry = 0;
    info->zmin = -28;    info->flagzmin = 0;
    info->zmax = 28;    info->flagzmax = 0;
    info->zDel = 1;    info->flagzDel = 0;
    info->mind = 1;    info->flagmind = 0;
    info->maxd = 5;    info->flagmaxd = 0;
    info->axisX = 70;    info->flagaxisX = 0;
    info->axisY = 70;    info->flagaxisY = 0;
    info->fptconfigFile = NULL;    info->flagconfigFile = 0;
    info->mode = 0;    info->flagmode = 0;
}

void
init1(pdbChargeFitInfo* info)
{
    char s[1024];
    int i;
    if(!info->flagInFix) {
        stringGetFromFile(s, "InFix", stdin, stdout, 0);
        info->InFix = stringGetNthWord(s, 1, " ,\t");
        info->flagInFix++;
    }
    if(info->flagInFix) {
        info->fptInFix = fileOpen(info->InFix, "r");
    }
    
    if(!info->flagInMove) {
        stringGetFromFile(s, "InMove", stdin, stdout, 0);
        info->InMove = stringGetNthWord(s, 1, " ,\t");
        info->flagInMove++;
    }
    if(info->flagInMove) {
        info->fptInMove = fileOpen(info->InMove, "r");
    }
    
    if(!info->flagOutTxt) {
        stringGetFromFile(s, "OutTxt", stdin, stdout, 0);
        info->OutTxt = stringGetNthWord(s, 1, " ,\t");
        info->flagOutTxt++;
    }
    if(info->flagOutTxt) {
        info->fptOutTxt = fileOpen(info->OutTxt, "w");
    }
    
    if(info->flagsymmetry) {
    }
    
    if(info->flagzmin) {
    }
    
    if(info->flagzmax) {
    }
    
    if(info->flagzDel) {
    }
    
    if(info->flagmind) {
    }
    
    if(info->flagmaxd) {
    }
    
    if(info->flagaxisX) {
    }
    
    if(info->flagaxisY) {
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
    sprintf(panepath, "%s/src/Tools/pdbUtil/pdbChargeFit/src/pdbChargeFit.pane", eospath);
    khoros_initialize(argc, argv, "EOS");
    fpt = fopen(panepath, "r");    if(NULL!=fpt) {
        fclose(fpt);
        kclui_initialize(panepath, KGEN_NONE, "EOS", "pdbChargeFit",
                     func_usage_additions,
                     func_get_args,
                     func_free_args);
    }
}
#endif /* KHOROS */ 
