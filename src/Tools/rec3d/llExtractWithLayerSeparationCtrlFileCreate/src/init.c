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
init0(llExtractWithLayerSeparationCtrlFileCreateInfo* info)
{
    info->fptIn = NULL;    info->flagIn = 0;
    info->fptOut = stdout;    info->flagOut = 0;
    info->Turn = -13;    info->flagTurn = 0;
    info->Unit = 28;    info->flagUnit = 0;
    info->nHelix = 1;    info->flagnHelix = 0;
    info->dY = 3;    info->flagdY = 0;
    info->truePitch = 770;    info->flagtruePitch = 0;
    info->rMax = 50;    info->flagrMax = 0;
    info->RMax = 0.1;    info->flagRMax = 0;
    info->RZMax = 0.1;    info->flagRZMax = 0;
    info->fptconfigFile = NULL;    info->flagconfigFile = 0;
    info->mode = 0;    info->flagmode = 0;
}

void
init1(llExtractWithLayerSeparationCtrlFileCreateInfo* info)
{
    char s[1024];
    int i;
    if(info->flagIn) {
        info->fptIn = fileOpen(info->In, "r");
    }
    
    if(info->flagOut) {
        info->fptOut = fileOpen(info->Out, "w");
    }
    
    if(!info->flagTurn) {
        stringGetFromFile(s, "Turn", stdin, stdout, 0);
        info->Turn = stringGetNthIntegerData(s, 1, ", \t");
        info->flagTurn++;
    }
    if(info->flagTurn) {
    }
    
    if(!info->flagUnit) {
        stringGetFromFile(s, "Unit", stdin, stdout, 0);
        info->Unit = stringGetNthIntegerData(s, 1, ", \t");
        info->flagUnit++;
    }
    if(info->flagUnit) {
    }
    
    if(info->flagnHelix) {
    }
    
    if(info->flagdY) {
    }
    
    if(!info->flagtruePitch) {
        stringGetFromFile(s, "truePitch", stdin, stdout, 0);
        info->truePitch = stringGetNthIntegerData(s, 1, ", \t");
        info->flagtruePitch++;
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
    
    if(info->flagRZMax) {
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
    sprintf(panepath, "%s/src/Tools/rec3d/llExtractWithLayerSeparationCtrlFileCreate/src/llExtractWithLayerSeparationCtrlFileCreate.pane", eospath);
    khoros_initialize(argc, argv, "EOS");
    fpt = fopen(panepath, "r");    if(NULL!=fpt) {
        fclose(fpt);
        kclui_initialize(panepath, KGEN_NONE, "EOS", "llExtractWithLayerSeparationCtrlFileCreate",
                     func_usage_additions,
                     func_get_args,
                     func_free_args);
    }
}
#endif /* KHOROS */ 
