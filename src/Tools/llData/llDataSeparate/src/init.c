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
init0(llDataSeparateInfo* info)
{
    info->fptIn = NULL;    info->flagIn = 0;
    info->fptSepNea = NULL;    info->flagSepNea = 0;
    info->fptSepFar = NULL;    info->flagSepFar = 0;
    info->fptMixNea = NULL;    info->flagMixNea = 0;
    info->fptMixFar = NULL;    info->flagMixFar = 0;
    info->delRInv = 0.0;    info->flagdelRInv = 0;
    info->truePitch = 0.0;    info->flagtruePitch = 0;
    info->rMax = 50.0;    info->flagrMax = 0;
    info->RMax = 0.2;    info->flagRMax = 0;
    info->xShift = 0.0;    info->flagxShift = 0;
    info->fptLog = stdout;    info->flagLog = 0;
    info->fptconfigFile = NULL;    info->flagconfigFile = 0;
    info->mode = 0;    info->flagmode = 0;
}

void
init1(llDataSeparateInfo* info)
{
    char s[1024];
    int i;
    if(!info->flagIn) {
        stringGetFromFile(s, "In", stdin, stdout, 0);
        info->In = stringGetNthWord(s, 1, " ,\t");
        info->flagIn++;
    }
    if(info->flagIn) {
        info->fptIn = fileOpen(info->In, "r");
    }
    
    if(!info->flagSepNea) {
        stringGetFromFile(s, "SepNea", stdin, stdout, 0);
        info->SepNea = stringGetNthWord(s, 1, " ,\t");
        info->flagSepNea++;
    }
    if(info->flagSepNea) {
        info->fptSepNea = fileOpen(info->SepNea, "w");
    }
    
    if(!info->flagSepFar) {
        stringGetFromFile(s, "SepFar", stdin, stdout, 0);
        info->SepFar = stringGetNthWord(s, 1, " ,\t");
        info->flagSepFar++;
    }
    if(info->flagSepFar) {
        info->fptSepFar = fileOpen(info->SepFar, "w");
    }
    
    if(info->flagMixNea) {
        info->fptMixNea = fileOpen(info->MixNea, "w");
    }
    
    if(info->flagMixFar) {
        info->fptMixFar = fileOpen(info->MixFar, "w");
    }
    
    if(info->flagdelRInv) {
    }
    
    if(info->flagtruePitch) {
    }
    
    if(!info->flagrMax) {
        stringGetFromFile(s, "rMax", stdin, stdout, 0);
        info->rMax = stringGetNthRealData(s, 1, ", \t");
        info->flagrMax++;
    }
    if(info->flagrMax) {
    }
    
    if(info->flagRMax) {
    }
    
    if(info->flagxShift) {
    }
    
    if(info->flagLog) {
        info->fptLog = fileOpen(info->Log, "w");
    }
    
    if(!info->flagconfigFile) {
        stringGetFromFile(s, "configFile", stdin, stdout, 0);
        info->configFile = stringGetNthWord(s, 1, " ,\t");
        info->flagconfigFile++;
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
    sprintf(panepath, "%s/src/Tools/llData/llDataSeparate/src/llDataSeparate.pane", eospath);
    khoros_initialize(argc, argv, "EOS");
    fpt = fopen(panepath, "r");    if(NULL!=fpt) {
        fclose(fpt);
        kclui_initialize(panepath, KGEN_NONE, "EOS", "llDataSeparate",
                     func_usage_additions,
                     func_get_args,
                     func_free_args);
    }
}
#endif /* KHOROS */ 
