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
init0(mrcImageSiemensStarInfo* info)
{
    info->fptOut = stdout;    info->flagOut = 0;
    info->Nx = 256;    info->flagNx = 0;
    info->Ny = 256;    info->flagNy = 0;
    info->R = 64;    info->flagR = 0;
    info->nRadial = 18;    info->flagnRadial = 0;
    info->Delta = 1.72;    info->flagDelta = 0;
    info->fptconfigFile = NULL;    info->flagconfigFile = 0;
    info->Shape = 0;    info->flagShape = 0;
    info->mode = 0;    info->flagmode = 0;
}

void
init1(mrcImageSiemensStarInfo* info)
{
    char s[1024];
    int i;
    if(!info->flagOut) {
        stringGetFromFile(s, "Out", stdin, stdout, 0);
        info->Out = stringGetNthWord(s, 1, " ,\t");
        info->flagOut++;
    }
    if(info->flagOut) {
        info->fptOut = fileOpen(info->Out, "w");
    }
    
    if(info->flagNx) {
    }
    
    if(info->flagNy) {
    }
    
    if(info->flagR) {
    }
    
    if(info->flagnRadial) {
    }
    
    if(info->flagDelta) {
    }
    
    if(info->flagconfigFile) {
        info->fptconfigFile = fileOpen(info->configFile, "r");
    }
    
    if(info->flagShape) {
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
    sprintf(panepath, "%s/src/Tools/mrcImage/mrcImageSiemensStar/src/mrcImageSiemensStar.pane", eospath);
    khoros_initialize(argc, argv, "EOS");
    fpt = fopen(panepath, "r");    if(NULL!=fpt) {
        fclose(fpt);
        kclui_initialize(panepath, KGEN_NONE, "EOS", "mrcImageSiemensStar",
                     func_usage_additions,
                     func_get_args,
                     func_free_args);
    }
}
#endif /* KHOROS */ 
