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
init0(mrcImageFourierNeighborCorrelationInfo* info)
{
    info->fptIn = NULL;    info->flagIn = 0;
    info->fptOut = stdout;    info->flagOut = 0;
    info->delta = 0.0;    info->flagdelta = 0;
    info->Centre = 0;    info->flagCentre = 0;
    info->GetMode = 0;    info->flagGetMode = 0;
    info->FSC=0;
    info->Cref=0;
    info->FSCfull=0;
    info->Brestore = 0.0;    info->flagBrestore = 0;
    info->fptInMask = NULL;    info->flagInMask = 0;
    info->fptInBackMask = NULL;    info->flagInBackMask = 0;
    info->fptconfigFile = NULL;    info->flagconfigFile = 0;
    info->mode = 0;    info->flagmode = 0;
}

void
init1(mrcImageFourierNeighborCorrelationInfo* info)
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
    
    if(info->flagdelta) {
    }
    
    if(info->flagCentre) {
    }
    
    if(info->flagGetMode) {
    }
    
    if(info->flagBrestore) {
    }
    
    if(info->flagInMask) {
        info->fptInMask = fileOpen(info->InMask, "r");
    }
    
    if(info->flagInBackMask) {
        info->fptInBackMask = fileOpen(info->InBackMask, "r");
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
    sprintf(panepath, "%s/src/Tools/mrcImage/mrcImageFourierNeighborCorrelation/src/mrcImageFourierNeighborCorrelation.pane", eospath);
    khoros_initialize(argc, argv, "EOS");
    fpt = fopen(panepath, "r");    if(NULL!=fpt) {
        fclose(fpt);
        kclui_initialize(panepath, KGEN_NONE, "EOS", "mrcImageFourierNeighborCorrelation",
                     func_usage_additions,
                     func_get_args,
                     func_free_args);
    }
}
#endif /* KHOROS */ 
