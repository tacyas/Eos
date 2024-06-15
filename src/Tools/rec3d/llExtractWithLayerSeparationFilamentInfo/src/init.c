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
init0(llExtractWithLayerSeparationFilamentInfoInfo* info)
{
    info->fptIn = NULL;    info->flagIn = 0;
    info->fptOut = NULL;    info->flagOut = 0;
    info->fptOutF = NULL;    info->flagOutF = 0;
    info->fptOutI = NULL;    info->flagOutI = 0;
    info->fptconfigFile = NULL;    info->flagconfigFile = 0;
    info->truePitch = 430;    info->flagtruePitch = 0;
    info->PixelSize = 5;    info->flagPixelSize = 0;
    info->deltadY = 0.5;    info->flagdeltadY = 0;
    info->kV = 200;    info->flagkV = 0;
    info->Cs = 2.1;    info->flagCs = 0;
    info->Defocus = 27000;    info->flagDefocus = 0;
    info->AoverP = 0.1;    info->flagAoverP = 0;
    info->mode = 0;    info->flagmode = 0;
}

void
init1(llExtractWithLayerSeparationFilamentInfoInfo* info)
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
    
    if(info->flagOutF) {
        info->fptOutF = fileOpen(info->OutF, "w");
    }
    
    if(info->flagOutI) {
        info->fptOutI = fileOpen(info->OutI, "w");
    }
    
    if(info->flagconfigFile) {
        info->fptconfigFile = fileOpen(info->configFile, "r");
    }
    
    if(info->flagtruePitch) {
    }
    
    if(info->flagPixelSize) {
    }
    
    if(info->flagdeltadY) {
    }
    
    if(info->flagkV) {
    }
    
    if(info->flagCs) {
    }
    
    if(info->flagDefocus) {
    }
    
    if(info->flagAoverP) {
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
    sprintf(panepath, "%s/src/Tools/rec3d/llExtractWithLayerSeparationFilamentInfo/src/llExtractWithLayerSeparationFilamentInfo.pane", eospath);
    khoros_initialize(argc, argv, "EOS");
    fpt = fopen(panepath, "r");    if(NULL!=fpt) {
        fclose(fpt);
        kclui_initialize(panepath, KGEN_NONE, "EOS", "llExtractWithLayerSeparationFilamentInfo",
                     func_usage_additions,
                     func_get_args,
                     func_free_args);
    }
}
#endif /* KHOROS */ 
