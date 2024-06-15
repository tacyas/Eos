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
init0(llExtractCtrlFileCreateInfo* info)
{
    info->fptIn = NULL;    info->flagIn = 0;
    info->fptOut = stdout;    info->flagOut = 0;
    info->fptconfigFile = NULL;    info->flagconfigFile = 0;
    info->turn = -6;    info->flagturn = 0;
    info->unit = 13;    info->flagunit = 0;
    info->nstrand = 1;    info->flagnstrand = 0;
    info->Y1 = 36;    info->flagY1 = 0;
    info->Y0 = 78;    info->flagY0 = 0;
    info->rmax = 250;    info->flagrmax = 0;
    info->Rmax = 0.1;    info->flagRmax = 0;
    info->lx = 5.0;    info->flaglx = 0;
    info->ly = 5.0;    info->flagly = 0;
    info->nx = 1000.0;    info->flagnx = 0;
    info->ny = 1000.0;    info->flagny = 0;
    info->center = 500.0;    info->flagcenter = 0;
    info->layerline = 21.0;    info->flaglayerline = 0;
    info->Ax = 5000.0;    info->flagAx = 0;
    info->dY = 12.0;    info->flagdY = 0;
    info->truePitch = 430;    info->flagtruePitch = 0;
    info->PixelSize = 5;    info->flagPixelSize = 0;
    info->deltadY = 0.5;    info->flagdeltadY = 0;
    info->mode = 1;    info->flagmode = 0;
}

void
init1(llExtractCtrlFileCreateInfo* info)
{
    char s[1024];
    int i;
    if(info->flagIn) {
        info->fptIn = fileOpen(info->In, "r");
    }
    
    if(info->flagOut) {
        info->fptOut = fileOpen(info->Out, "w");
    }
    
    if(info->flagconfigFile) {
        info->fptconfigFile = fileOpen(info->configFile, "r");
    }
    
    if(info->flagturn) {
    }
    
    if(info->flagunit) {
    }
    
    if(info->flagnstrand) {
    }
    
    if(info->flagY1) {
    }
    
    if(info->flagY0) {
    }
    
    if(info->flagrmax) {
    }
    
    if(info->flagRmax) {
    }
    
    if(info->flaglx) {
    }
    
    if(info->flagly) {
    }
    
    if(info->flagnx) {
    }
    
    if(info->flagny) {
    }
    
    if(info->flagcenter) {
    }
    
    if(info->flaglayerline) {
    }
    
    if(info->flagAx) {
    }
    
    if(info->flagdY) {
    }
    
    if(info->flagtruePitch) {
    }
    
    if(info->flagPixelSize) {
    }
    
    if(info->flagdeltadY) {
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
    sprintf(panepath, "%s/src/Tools/rec3d/llExtractCtrlFileCreate/src/llExtractCtrlFileCreate.pane", eospath);
    khoros_initialize(argc, argv, "EOS");
    fpt = fopen(panepath, "r");    if(NULL!=fpt) {
        fclose(fpt);
        kclui_initialize(panepath, KGEN_NONE, "EOS", "llExtractCtrlFileCreate",
                     func_usage_additions,
                     func_get_args,
                     func_free_args);
    }
}
#endif /* KHOROS */ 
