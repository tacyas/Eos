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
init0(mrcImageCTFCompensationInfo* info)
{
    info->fptIn = stdin;    info->flagIn = 0;
    info->fptOut = stdout;    info->flagOut = 0;
    info->fptInfo = NULL;    info->flagInfo = 0;
    info->fptInfo2 = NULL;    info->flagInfo2 = 0;
    info->kV = 200;    info->flagkV = 0;
    info->Cs = 2.1;    info->flagCs = 0;
    info->Defocus = 27000;    info->flagDefocus = 0;
    info->WhiteNoise = 0.1;    info->flagWhiteNoise = 0;
    info->WhiteNoiseRaising = 0.1;    info->flagWhiteNoiseRaising = 0;
    info->SinWinRmin = 0.1;    info->flagSinWinRmin = 0;
    info->SinWinRmax = 1.0;    info->flagSinWinRmax = 0;
    info->Amp = 0.1;    info->flagAmp = 0;
    info->dfMin = 0;    info->flagdfMin = 0;
    info->dfMax = 0;    info->flagdfMax = 0;
    info->asAxis = 0;    info->flagasAxis = 0;
    info->NoAstigmatism=0;
    info->fptconfigFile = NULL;    info->flagconfigFile = 0;
    info->mode = 0;    info->flagmode = 0;
}

void
init1(mrcImageCTFCompensationInfo* info)
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
    
    if(info->flagInfo) {
        info->fptInfo = fileOpen(info->Info, "r");
    }
    
    if(info->flagInfo2) {
        info->fptInfo2 = fileOpen(info->Info2, "r");
    }
    
    if(info->flagkV) {
    }
    
    if(info->flagCs) {
    }
    
    if(info->flagDefocus) {
    }
    
    if(info->flagWhiteNoise) {
    }
    
    if(info->flagWhiteNoiseRaising) {
    }
    
    if(info->flagSinWinRmin) {
    }
    
    if(info->flagSinWinRmax) {
    }
    
    if(info->flagAmp) {
    }
    
    if(info->flagdfMin) {
    }
    
    if(info->flagdfMax) {
    }
    
    if(info->flagasAxis) {
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
    sprintf(panepath, "%s/src/Tools/mrcImage/mrcImageCTFCompensation/src/mrcImageCTFCompensation.pane", eospath);
    khoros_initialize(argc, argv, "EOS");
    fpt = fopen(panepath, "r");    if(NULL!=fpt) {
        fclose(fpt);
        kclui_initialize(panepath, KGEN_NONE, "EOS", "mrcImageCTFCompensation",
                     func_usage_additions,
                     func_get_args,
                     func_free_args);
    }
}
#endif /* KHOROS */ 
