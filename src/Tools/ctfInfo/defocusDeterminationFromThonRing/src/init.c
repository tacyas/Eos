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
init0(defocusDeterminationFromThonRingInfo* info)
{
    info->fptIn = stdin;    info->flagIn = 0;
    info->InN = stringGetNthWord("stdin", 1, "\0");    info->flagInN = 0;
    info->InR = stringGetNthWord("stdin", 1, "\0");    info->flagInR = 0;
    info->fptOut = stdout;    info->flagOut = 0;
    info->fptOutI = stdout;    info->flagOutI = 0;
    info->fptOutI2 = stdout;    info->flagOutI2 = 0;
    info->fptOutI3 = stdout;    info->flagOutI3 = 0;
    info->kV = 200;    info->flagkV = 0;
    info->Cs = 2.1;    info->flagCs = 0;
    info->AoverP = 0.05;    info->flagAoverP = 0;
    info->fptconfigFile = NULL;    info->flagconfigFile = 0;
    info->mode = 0;    info->flagmode = 0;
    info->ctfMode = 0;    info->flagctfMode = 0;
    info->truePitch = 430;    info->flagtruePitch = 0;
    info->PixelSize = 5;    info->flagPixelSize = 0;
    info->deltadY = 0.5;    info->flagdeltadY = 0;
    info->R = NULL;    info->flagR = 0;
}

void
init1(defocusDeterminationFromThonRingInfo* info)
{
    char s[1024];
    int i;
    if(info->flagIn) {
        info->fptIn = fileOpen(info->In, "r");
    }
    
    if(info->flagInN) {
    }
    
    if(info->flagInR) {
    }
    
    if(info->flagOut) {
        info->fptOut = fileOpen(info->Out, "w");
    }
    
    if(info->flagOutI) {
        info->fptOutI = fileOpen(info->OutI, "w");
    }
    
    if(info->flagOutI2) {
        info->fptOutI2 = fileOpen(info->OutI2, "w");
    }
    
    if(info->flagOutI3) {
        info->fptOutI3 = fileOpen(info->OutI3, "w");
    }
    
    if(info->flagkV) {
    }
    
    if(info->flagCs) {
    }
    
    if(info->flagAoverP) {
    }
    
    if(info->flagconfigFile) {
        info->fptconfigFile = fileOpen(info->configFile, "r");
    }
    
    if(info->flagmode) {
    }
    
    if(info->flagctfMode) {
    }
    
    if(info->flagtruePitch) {
    }
    
    if(info->flagPixelSize) {
    }
    
    if(info->flagdeltadY) {
    }
    
    if(info->flagR) {
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
    sprintf(panepath, "%s/src/Tools/ctfInfo/defocusDeterminationFromThonRing/src/defocusDeterminationFromThonRing.pane", eospath);
    khoros_initialize(argc, argv, "EOS");
    fpt = fopen(panepath, "r");    if(NULL!=fpt) {
        fclose(fpt);
        kclui_initialize(panepath, KGEN_NONE, "EOS", "defocusDeterminationFromThonRing",
                     func_usage_additions,
                     func_get_args,
                     func_free_args);
    }
}
#endif /* KHOROS */ 
