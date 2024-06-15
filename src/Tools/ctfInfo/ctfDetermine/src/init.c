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
init0(ctfDetermineInfo* info)
{
    info->fptIn = NULL;    info->flagIn = 0;
    info->fptOut = NULL;    info->flagOut = 0;
    info->Defocus = 0.0;    info->flagDefocus = 0;
    info->Cs = 1.7;    info->flagCs = 0;
    info->Cc = 1.2;    info->flagCc = 0;
    info->dE = 0.2;    info->flagdE = 0;
    info->Ac = 200;    info->flagAc = 0;
    info->CutLow = 0.05;    info->flagCutLow = 0;
    info->CutHigh = 0.5;    info->flagCutHigh = 0;
    info->I0 = 1.0;    info->flagI0 = 0;
    info->ratioOfAmpToPhase = 0.1;    info->flagratioOfAmpToPhase = 0;
    info->Ai = 0.03;    info->flagAi = 0;
    info->BofMTF = 15.0;    info->flagBofMTF = 0;
    info->BofVibration = 3.0;    info->flagBofVibration = 0;
    info->Magnification = 1.0;    info->flagMagnification = 0;
    info->WhiteNoise = 0.0;    info->flagWhiteNoise = 0;
    info->WhiteNoise2 = 0.0;    info->flagWhiteNoise2 = 0;
    info->MolcEnv = 0.0;    info->flagMolcEnv = 0;
    info->fptMolcEnvTable = NULL;    info->flagMolcEnvTable = 0;
    info->fptconfigFile = NULL;    info->flagconfigFile = 0;
    info->mode = 0;    info->flagmode = 0;
    info->min = -10;    info->flagmin = 0;
    info->max = 10;    info->flagmax = 0;
    info->step = 0.01;    info->flagstep = 0;
    info->degree = 6;    info->flagdegree = 0;
    info->section = 4;    info->flagsection = 0;
}

void
init1(ctfDetermineInfo* info)
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
        info->fptOut = fopen(info->Out, "a+");
    }
    
    if(info->flagDefocus) {
    }
    
    if(info->flagCs) {
    }
    
    if(info->flagCc) {
    }
    
    if(info->flagdE) {
    }
    
    if(info->flagAc) {
    }
    
    if(info->flagCutLow) {
    }
    
    if(info->flagCutHigh) {
    }
    
    if(info->flagI0) {
    }
    
    if(info->flagratioOfAmpToPhase) {
    }
    
    if(info->flagAi) {
    }
    
    if(info->flagBofMTF) {
    }
    
    if(info->flagBofVibration) {
    }
    
    if(info->flagMagnification) {
    }
    
    if(info->flagWhiteNoise) {
    }
    
    if(info->flagWhiteNoise2) {
    }
    
    if(info->flagMolcEnv) {
    }
    
    if(info->flagMolcEnvTable) {
        info->fptMolcEnvTable = fileOpen(info->MolcEnvTable, "r");
    }
    
    if(info->flagconfigFile) {
        info->fptconfigFile = fileOpen(info->configFile, "r");
    }
    
    if(info->flagmode) {
    }
    
    if(info->flagmin) {
    }
    
    if(info->flagmax) {
    }
    
    if(info->flagstep) {
    }
    
    if(info->flagdegree) {
    }
    
    if(info->flagsection) {
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
    sprintf(panepath, "%s/src/Tools/ctfInfo/ctfDetermine/src/ctfDetermine.pane", eospath);
    khoros_initialize(argc, argv, "EOS");
    fpt = fopen(panepath, "r");    if(NULL!=fpt) {
        fclose(fpt);
        kclui_initialize(panepath, KGEN_NONE, "EOS", "ctfDetermine",
                     func_usage_additions,
                     func_get_args,
                     func_free_args);
    }
}
#endif /* KHOROS */ 
