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
init0(mrcImageResolutionEstimateForFilamentsInfo* info)
{
    info->fptIn1 = NULL;    info->flagIn1 = 0;
    info->fptIn2 = NULL;    info->flagIn2 = 0;
    info->delta = 0;    info->flagdelta = 0;
    info->H = 0;    info->flagH = 0;
    info->fptconfigFile = NULL;    info->flagconfigFile = 0;
    info->mode = 0;    info->flagmode = 0;
    info->mode2 = 0;    info->flagmode2 = 0;
}

void
init1(mrcImageResolutionEstimateForFilamentsInfo* info)
{
    char s[1024];
    int i;
    if(info->flagIn1) {
        info->fptIn1 = fileOpen(info->In1, "r");
    }
    
    if(info->flagIn2) {
        info->fptIn2 = fileOpen(info->In2, "r");
    }
    
    if(info->flagdelta) {
    }
    
    if(info->flagH) {
    }
    
    if(info->flagconfigFile) {
        info->fptconfigFile = fileOpen(info->configFile, "r");
    }
    
    if(info->flagmode) {
    }
    
    if(info->flagmode2) {
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
    sprintf(panepath, "%s/src/Tools/mrcImage/mrcImageResolutionEstimateForFilaments/src/mrcImageResolutionEstimateForFilaments.pane", eospath);
    khoros_initialize(argc, argv, "EOS");
    fpt = fopen(panepath, "r");    if(NULL!=fpt) {
        fclose(fpt);
        kclui_initialize(panepath, KGEN_NONE, "EOS", "mrcImageResolutionEstimateForFilaments",
                     func_usage_additions,
                     func_get_args,
                     func_free_args);
    }
}
#endif /* KHOROS */ 