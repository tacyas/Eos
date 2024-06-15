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
init0(mrcImageNullImageCreateInfo* info)
{
    info->fptOut = NULL;    info->flagOut = 0;
    info->fptRef = NULL;    info->flagRef = 0;
    info->Nx = 0;    info->flagNx = 0;
    info->Ny = 0;    info->flagNy = 0;
    info->Nz = 0;    info->flagNz = 0;
    info->Value = 0.0;    info->flagValue = 0;
    info->d = 0.0;    info->flagd = 0;
    info->Mode = 2;    info->flagMode = 0;
    info->Default=0;
    info->fptconfigFile = NULL;    info->flagconfigFile = 0;
    info->mode = 0;    info->flagmode = 0;
}

void
init1(mrcImageNullImageCreateInfo* info)
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
    
    if(info->flagRef) {
        info->fptRef = fileOpen(info->Ref, "r");
    }
    
    if(info->flagNx) {
    }
    
    if(info->flagNy) {
    }
    
    if(info->flagNz) {
    }
    
    if(info->flagValue) {
    }
    
    if(info->flagd) {
    }
    
    if(info->flagMode) {
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
    sprintf(panepath, "%s/src/Tools/mrcImage/mrcImageNullImageCreate/src/mrcImageNullImageCreate.pane", eospath);
    khoros_initialize(argc, argv, "EOS");
    fpt = fopen(panepath, "r");    if(NULL!=fpt) {
        fclose(fpt);
        kclui_initialize(panepath, KGEN_NONE, "EOS", "mrcImageNullImageCreate",
                     func_usage_additions,
                     func_get_args,
                     func_free_args);
    }
}
#endif /* KHOROS */ 
