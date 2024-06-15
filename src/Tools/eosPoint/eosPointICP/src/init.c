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
init0(eosPointICPInfo* info)
{
    info->fptIn = NULL;    info->flagIn = 0;
    info->InType = 2;    info->flagInType = 0;
    info->fptInMat = NULL;    info->flagInMat = 0;
    info->fptRef = NULL;    info->flagRef = 0;
    info->RefType = 2;    info->flagRefType = 0;
    info->fptRefMat = NULL;    info->flagRefMat = 0;
    info->fptOut = NULL;    info->flagOut = 0;
    info->OutType = 2;    info->flagOutType = 0;
    info->EAMode = stringGetNthWord("ZEYS", 1, "\0");    info->flagEAMode = 0;
    info->Ratio = 1.0;    info->flagRatio = 0;
    info->IterationLimit = 10000;    info->flagIterationLimit = 0;
    info->Pattern = 10;    info->flagPattern = 0;
    info->ScoreThreshold = 0.0;    info->flagScoreThreshold = 0;
    info->Omit = 100000.0;    info->flagOmit = 0;
    info->Pickup = 0.8;    info->flagPickup = 0;
    info->flag2D = 0;    info->flagflag2D = 0;
    info->Debug = 0;    info->flagDebug = 0;
    info->mode = 0;    info->flagmode = 0;
    info->fptconfigFile = NULL;    info->flagconfigFile = 0;
}

void
init1(eosPointICPInfo* info)
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
    
    if(info->flagInType) {
    }
    
    if(info->flagInMat) {
        info->fptInMat = fileOpen(info->InMat, "r");
    }
    
    if(!info->flagRef) {
        stringGetFromFile(s, "Ref", stdin, stdout, 0);
        info->Ref = stringGetNthWord(s, 1, " ,\t");
        info->flagRef++;
    }
    if(info->flagRef) {
        info->fptRef = fileOpen(info->Ref, "r");
    }
    
    if(info->flagRefType) {
    }
    
    if(info->flagRefMat) {
        info->fptRefMat = fileOpen(info->RefMat, "r");
    }
    
    if(!info->flagOut) {
        stringGetFromFile(s, "Out", stdin, stdout, 0);
        info->Out = stringGetNthWord(s, 1, " ,\t");
        info->flagOut++;
    }
    if(info->flagOut) {
        info->fptOut = fileOpen(info->Out, "w");
    }
    
    if(!info->flagOutType) {
        stringGetFromFile(s, "OutType", stdin, stdout, 0);
        info->OutType = stringGetNthIntegerData(s, 1, ", \t");
        info->flagOutType++;
    }
    if(info->flagOutType) {
    }
    
    if(info->flagEAMode) {
    }
    
    if(info->flagRatio) {
    }
    
    if(info->flagIterationLimit) {
    }
    
    if(info->flagPattern) {
    }
    
    if(info->flagScoreThreshold) {
    }
    
    if(info->flagOmit) {
    }
    
    if(info->flagPickup) {
    }
    
    if(info->flagflag2D) {
    }
    
    if(info->flagDebug) {
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
    sprintf(panepath, "%s/src/Tools/eosPoint/eosPointICP/src/eosPointICP.pane", eospath);
    khoros_initialize(argc, argv, "EOS");
    fpt = fopen(panepath, "r");    if(NULL!=fpt) {
        fclose(fpt);
        kclui_initialize(panepath, KGEN_NONE, "EOS", "eosPointICP",
                     func_usage_additions,
                     func_get_args,
                     func_free_args);
    }
}
#endif /* KHOROS */ 
