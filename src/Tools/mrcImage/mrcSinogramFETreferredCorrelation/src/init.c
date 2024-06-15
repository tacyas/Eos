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
init0(mrcSinogramFETreferredCorrelationInfo* info)
{
    info->fptIn = NULL;    info->flagIn = 0;
    info->fptOut = NULL;    info->flagOut = 0;
    info->fptInR = NULL;    info->flagInR = 0;
    info->fptInE = NULL;    info->flagInE = 0;
    info->NM = 0;    info->flagNM = 0;
    info->OM = 2;    info->flagOM = 0;
    info->TN = 10;    info->flagTN = 0;
    info->RR = 15;    info->flagRR = 0;
    info->fptWEIGHT = NULL;    info->flagWEIGHT = 0;
    info->fptconfigFile = NULL;    info->flagconfigFile = 0;
    info->mode = 0;    info->flagmode = 0;
}

void
init1(mrcSinogramFETreferredCorrelationInfo* info)
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
    
    if(!info->flagOut) {
        stringGetFromFile(s, "Out", stdin, stdout, 0);
        info->Out = stringGetNthWord(s, 1, " ,\t");
        info->flagOut++;
    }
    if(info->flagOut) {
        info->fptOut = fileOpen(info->Out, "w");
    }
    
    if(!info->flagInR) {
        stringGetFromFile(s, "InR", stdin, stdout, 0);
        info->InR = stringGetNthWord(s, 1, " ,\t");
        info->flagInR++;
    }
    if(info->flagInR) {
        info->fptInR = fileOpen(info->InR, "r");
    }
    
    if(!info->flagInE) {
        stringGetFromFile(s, "InE", stdin, stdout, 0);
        info->InE = stringGetNthWord(s, 1, " ,\t");
        info->flagInE++;
    }
    if(info->flagInE) {
        info->fptInE = fileOpen(info->InE, "r");
    }
    
    if(info->flagNM) {
    }
    
    if(info->flagOM) {
    }
    
    if(info->flagTN) {
    }
    
    if(info->flagRR) {
    }
    
    if(info->flagWEIGHT) {
        info->fptWEIGHT = fileOpen(info->WEIGHT, "r");
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
    sprintf(panepath, "%s/src/Tools/mrcImage/mrcSinogramFETreferredCorrelation/src/mrcSinogramFETreferredCorrelation.pane", eospath);
    khoros_initialize(argc, argv, "EOS");
    fpt = fopen(panepath, "r");    if(NULL!=fpt) {
        fclose(fpt);
        kclui_initialize(panepath, KGEN_NONE, "EOS", "mrcSinogramFETreferredCorrelation",
                     func_usage_additions,
                     func_get_args,
                     func_free_args);
    }
}
#endif /* KHOROS */ 
