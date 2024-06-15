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
init0(mrcImageMaskingInfo* info)
{
    info->fptIn = NULL;    info->flagIn = 0;
    info->fptOut = NULL;    info->flagOut = 0;
    info->nx = 0;    info->flagnx = 0;
    info->ny = 0;    info->flagny = 0;
    info->nz = 0;    info->flagnz = 0;
    info->cx = 0;    info->flagcx = 0;
    info->cy = 0;    info->flagcy = 0;
    info->cz = 0;    info->flagcz = 0;
    info->Euler = stringGetNthWord("0", 1, "\0");    info->flagEuler = 0;
    info->Rot1 = 0;    info->flagRot1 = 0;
    info->Rot2 = 0;    info->flagRot2 = 0;
    info->Rot3 = 0;    info->flagRot3 = 0;
    info->Shape = 0;    info->flagShape = 0;
    info->Soft = 0;    info->flagSoft = 0;
    info->SoftWidth = 0.0;    info->flagSoftWidth = 0;
    info->Normalize = 0;    info->flagNormalize = 0;
    info->fptconfigFile = NULL;    info->flagconfigFile = 0;
    info->mode = 0;    info->flagmode = 0;
}

void
init1(mrcImageMaskingInfo* info)
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
    
    if(info->flagnx) {
    }
    
    if(info->flagny) {
    }
    
    if(info->flagnz) {
    }
    
    if(info->flagcx) {
    }
    
    if(info->flagcy) {
    }
    
    if(info->flagcz) {
    }
    
    if(info->flagEuler) {
    }
    
    if(info->flagRot1) {
    }
    
    if(info->flagRot2) {
    }
    
    if(info->flagRot3) {
    }
    
    if(info->flagShape) {
    }
    
    if(info->flagSoft) {
    }
    
    if(info->flagSoftWidth) {
    }
    
    if(info->flagNormalize) {
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
    sprintf(panepath, "%s/src/Tools/mrcImage/mrcImageMasking/src/mrcImageMasking.pane", eospath);
    khoros_initialize(argc, argv, "EOS");
    fpt = fopen(panepath, "r");    if(NULL!=fpt) {
        fclose(fpt);
        kclui_initialize(panepath, KGEN_NONE, "EOS", "mrcImageMasking",
                     func_usage_additions,
                     func_get_args,
                     func_free_args);
    }
}
#endif /* KHOROS */ 
