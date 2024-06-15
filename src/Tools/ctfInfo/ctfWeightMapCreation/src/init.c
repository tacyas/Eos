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
init0(ctfWeightMapCreationInfo* info)
{
    info->fptOut = stdout;    info->flagOut = 0;
    info->kV = 200;    info->flagkV = 0;
    info->Cs = 1.7;    info->flagCs = 0;
    info->Defocus = 2.7;    info->flagDefocus = 0;
    info->WhiteNoise = 1.0;    info->flagWhiteNoise = 0;
    info->fptNoise = NULL;    info->flagNoise = 0;
    info->fptSplusN = NULL;    info->flagSplusN = 0;
    info->dRinv = 1024*5/3;    info->flagdRinv = 0;
    info->dRmaxInv = 10.0;    info->flagdRmaxInv = 0;
    info->SinWinRminInv = 20.0;    info->flagSinWinRminInv = 0;
    info->SinWinRmaxInv = 10.0;    info->flagSinWinRmaxInv = 0;
    info->fptconfigFile = NULL;    info->flagconfigFile = 0;
    info->mode = 0;    info->flagmode = 0;
}

void
init1(ctfWeightMapCreationInfo* info)
{
    char s[1024];
    int i;
    if(info->flagOut) {
        info->fptOut = fileOpen(info->Out, "w");
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
    
    if(info->flagWhiteNoise) {
    }
    
    if(info->flagNoise) {
        info->fptNoise = fileOpen(info->Noise, "r");
    }
    
    if(info->flagSplusN) {
        info->fptSplusN = fileOpen(info->SplusN, "r");
    }
    
    if(!info->flagdRinv) {
        stringGetFromFile(s, "dRinv", stdin, stdout, 0);
        info->dRinv = stringGetNthRealData(s, 1, ", \t");
        info->flagdRinv++;
    }
    if(info->flagdRinv) {
    }
    
    if(!info->flagdRmaxInv) {
        stringGetFromFile(s, "dRmaxInv", stdin, stdout, 0);
        info->dRmaxInv = stringGetNthRealData(s, 1, ", \t");
        info->flagdRmaxInv++;
    }
    if(info->flagdRmaxInv) {
    }
    
    if(info->flagSinWinRminInv) {
    }
    
    if(info->flagSinWinRmaxInv) {
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
    sprintf(panepath, "%s/src/Tools/ctfInfo/ctfWeightMapCreation/src/ctfWeightMapCreation.pane", eospath);
    khoros_initialize(argc, argv, "EOS");
    fpt = fopen(panepath, "r");    if(NULL!=fpt) {
        fclose(fpt);
        kclui_initialize(panepath, KGEN_NONE, "EOS", "ctfWeightMapCreation",
                     func_usage_additions,
                     func_get_args,
                     func_free_args);
    }
}
#endif /* KHOROS */ 
