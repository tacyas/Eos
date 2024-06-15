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
init0(mrcImageFilterCreateInfo* info)
{
    info->fptIn = stdin;    info->flagIn = 0;
    info->fptOut = stdout;    info->flagOut = 0;
    info->Nx = 512;    info->flagNx = 0;
    info->Ny = 512;    info->flagNy = 0;
    info->Nz = 1;    info->flagNz = 0;
    info->Sx = 3;    info->flagSx = 0;
    info->Sy = 3;    info->flagSy = 0;
    info->Sz = 1;    info->flagSz = 0;
    info->verbose=0;
    info->fptconfigFile = NULL;    info->flagconfigFile = 0;
    info->Mode = 0;    info->flagMode = 0;
    info->mode = 2;    info->flagmode = 0;
}

void
init1(mrcImageFilterCreateInfo* info)
{
    char s[1024];
    int i;
    if(info->flagIn) {
        info->fptIn = fileOpen(info->In, "r");
    }
    
    if(info->flagOut) {
        info->fptOut = fileOpen(info->Out, "w");
    }
    
    if(!info->flagNx) {
        stringGetFromFile(s, "Nx", stdin, stdout, 0);
        info->Nx = stringGetNthIntegerData(s, 1, ", \t");
        info->flagNx++;
    }
    if(info->flagNx) {
    }
    
    if(info->flagNy) {
    }
    
    if(info->flagNz) {
    }
    
    if(!info->flagSx) {
        stringGetFromFile(s, "Sx", stdin, stdout, 0);
        info->Sx = stringGetNthIntegerData(s, 1, ", \t");
        info->flagSx++;
    }
    if(info->flagSx) {
    }
    
    if(info->flagSy) {
    }
    
    if(info->flagSz) {
    }
    
    if(info->flagconfigFile) {
        info->fptconfigFile = fileOpen(info->configFile, "r");
    }
    
    if(info->flagMode) {
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
    sprintf(panepath, "%s/src/Tools/mrcImage/mrcImageFilterCreate/src/mrcImageFilterCreate.pane", eospath);
    khoros_initialize(argc, argv, "EOS");
    fpt = fopen(panepath, "r");    if(NULL!=fpt) {
        fclose(fpt);
        kclui_initialize(panepath, KGEN_NONE, "EOS", "mrcImageFilterCreate",
                     func_usage_additions,
                     func_get_args,
                     func_free_args);
    }
}
#endif /* KHOROS */ 
