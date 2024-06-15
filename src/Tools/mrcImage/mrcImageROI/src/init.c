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
init0(mrcImageROIInfo* info)
{
    info->fptIn = NULL;    info->flagIn = 0;
    info->fptOut = NULL;    info->flagOut = 0;
    info->blx = 0.0;    info->flagblx = 0;
    info->bly = 0.0;    info->flagbly = 0;
    info->brx = 0.0;    info->flagbrx = 0;
    info->bry = 0.0;    info->flagbry = 0;
    info->trx = 0.0;    info->flagtrx = 0;
    info->try = 0.0;    info->flagtry = 0;
    info->tlx = 0.0;    info->flagtlx = 0;
    info->tly = 0.0;    info->flagtly = 0;
    info->WidthBeforeExpansion = 1.0;    info->flagWidthBeforeExpansion = 0;
    info->HeightBeforeExpansion = 1.0;    info->flagHeightBeforeExpansion = 0;
    info->Angle = 0.0;    info->flagAngle = 0;
    info->WidthAfterExpansion = 1.0;    info->flagWidthAfterExpansion = 0;
    info->HeightAfterExpansion = 1.0;    info->flagHeightAfterExpansion = 0;
    info->ShiftX = 0.0;    info->flagShiftX = 0;
    info->ShiftY = 0.0;    info->flagShiftY = 0;
    info->truePitch = 430.0;    info->flagtruePitch = 0;
    info->dY = 0.0;    info->flagdY = 0;
    info->Ly = 5.0;    info->flagLy = 0;
    info->Shrink = 1;    info->flagShrink = 0;
    info->fptconfigFile = NULL;    info->flagconfigFile = 0;
    info->ROIShapeMode = 0;    info->flagROIShapeMode = 0;
    info->mode = 0;    info->flagmode = 0;
}

void
init1(mrcImageROIInfo* info)
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
    
    if(info->flagblx) {
    }
    
    if(info->flagbly) {
    }
    
    if(info->flagbrx) {
    }
    
    if(info->flagbry) {
    }
    
    if(info->flagtrx) {
    }
    
    if(info->flagtry) {
    }
    
    if(info->flagtlx) {
    }
    
    if(info->flagtly) {
    }
    
    if(info->flagWidthBeforeExpansion) {
    }
    
    if(info->flagHeightBeforeExpansion) {
    }
    
    if(info->flagAngle) {
    }
    
    if(info->flagWidthAfterExpansion) {
    }
    
    if(info->flagHeightAfterExpansion) {
    }
    
    if(info->flagShiftX) {
    }
    
    if(info->flagShiftY) {
    }
    
    if(info->flagtruePitch) {
    }
    
    if(info->flagdY) {
    }
    
    if(info->flagLy) {
    }
    
    if(info->flagShrink) {
    }
    
    if(info->flagconfigFile) {
        info->fptconfigFile = fileOpen(info->configFile, "r");
    }
    
    if(info->flagROIShapeMode) {
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
    sprintf(panepath, "%s/src/Tools/mrcImage/mrcImageROI/src/mrcImageROI.pane", eospath);
    khoros_initialize(argc, argv, "EOS");
    fpt = fopen(panepath, "r");    if(NULL!=fpt) {
        fclose(fpt);
        kclui_initialize(panepath, KGEN_NONE, "EOS", "mrcImageROI",
                     func_usage_additions,
                     func_get_args,
                     func_free_args);
    }
}
#endif /* KHOROS */ 
