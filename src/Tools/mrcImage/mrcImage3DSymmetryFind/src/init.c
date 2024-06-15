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
init0(mrcImage3DSymmetryFindInfo* info)
{
    info->fptIn = NULL;    info->flagIn = 0;
    info->fptOut = stdout;    info->flagOut = 0;
    info->fptAvg = NULL;    info->flagAvg = 0;
    info->ISGN = 0;    info->flagISGN = 0;
    info->RotMode = stringGetNthWord("XOYS", 1, "\0");    info->flagRotMode = 0;
    info->minRot1 = 0.;    info->flagminRot1 = 0;
    info->maxRot1 = 360.;    info->flagmaxRot1 = 0;
    info->dRot1 = 1.0;    info->flagdRot1 = 0;
    info->minRot2 = -90.;    info->flagminRot2 = 0;
    info->maxRot2 = 90.;    info->flagmaxRot2 = 0;
    info->dRot2 = 1.0;    info->flagdRot2 = 0;
    info->dCos = 1;    info->flagdCos = 0;
    info->corMode = 16;    info->flagcorMode = 0;
    info->OffsetMode = 0;    info->flagOffsetMode = 0;
    info->InterpolationMode = 2;    info->flagInterpolationMode = 0;
    info->fptconfigFile = NULL;    info->flagconfigFile = 0;
    info->mode = 0;    info->flagmode = 0;
}

void
init1(mrcImage3DSymmetryFindInfo* info)
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
    
    if(info->flagOut) {
        info->fptOut = fileOpen(info->Out, "w");
    }
    
    if(info->flagAvg) {
        info->fptAvg = fileOpen(info->Avg, "w");
    }
    
    if(info->flagISGN) {
    }
    
    if(info->flagRotMode) {
    }
    
    if(info->flagminRot1) {
    }
    
    if(info->flagmaxRot1) {
    }
    
    if(info->flagdRot1) {
    }
    
    if(info->flagminRot2) {
    }
    
    if(info->flagmaxRot2) {
    }
    
    if(info->flagdRot2) {
    }
    
    if(info->flagdCos) {
    }
    
    if(info->flagcorMode) {
    }
    
    if(info->flagOffsetMode) {
    }
    
    if(info->flagInterpolationMode) {
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
    sprintf(panepath, "%s/src/Tools/mrcImage/mrcImage3DSymmetryFind/src/mrcImage3DSymmetryFind.pane", eospath);
    khoros_initialize(argc, argv, "EOS");
    fpt = fopen(panepath, "r");    if(NULL!=fpt) {
        fclose(fpt);
        kclui_initialize(panepath, KGEN_NONE, "EOS", "mrcImage3DSymmetryFind",
                     func_usage_additions,
                     func_get_args,
                     func_free_args);
    }
}
#endif /* KHOROS */ 
