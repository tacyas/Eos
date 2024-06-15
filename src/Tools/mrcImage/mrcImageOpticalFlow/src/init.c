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
init0(mrcImageOpticalFlowInfo* info)
{
    info->fptIn1 = NULL;    info->flagIn1 = 0;
    info->fptIn2 = NULL;    info->flagIn2 = 0;
    info->fptIn3 = NULL;    info->flagIn3 = 0;
    info->fptVx = NULL;    info->flagVx = 0;
    info->fptVy = NULL;    info->flagVy = 0;
    info->fptVz = NULL;    info->flagVz = 0;
    info->fptOutFx = NULL;    info->flagOutFx = 0;
    info->fptOutFy = NULL;    info->flagOutFy = 0;
    info->fptOutFz = NULL;    info->flagOutFz = 0;
    info->fptOutDi = NULL;    info->flagOutDi = 0;
    info->fptSize = NULL;    info->flagSize = 0;
    info->fptOutCOMMAND = NULL;    info->flagOutCOMMAND = 0;
    info->fptOutBILD = NULL;    info->flagOutBILD = 0;
    info->BG = 3000;    info->flagBG = 0;
    info->BildThresLow = 0.0;    info->flagBildThresLow = 0;
    info->BildThresHigh = 1.0;    info->flagBildThresHigh = 0;
    info->BildRangeLow = 0.0;    info->flagBildRangeLow = 0;
    info->BildRangeHigh = 1.0;    info->flagBildRangeHigh = 0;
    info->fptconfigFile = NULL;    info->flagconfigFile = 0;
    info->mode = 0;    info->flagmode = 0;
}

void
init1(mrcImageOpticalFlowInfo* info)
{
    char s[1024];
    int i;
    if(!info->flagIn1) {
        stringGetFromFile(s, "In1", stdin, stdout, 0);
        info->In1 = stringGetNthWord(s, 1, " ,\t");
        info->flagIn1++;
    }
    if(info->flagIn1) {
        info->fptIn1 = fileOpen(info->In1, "r");
    }
    
    if(!info->flagIn2) {
        stringGetFromFile(s, "In2", stdin, stdout, 0);
        info->In2 = stringGetNthWord(s, 1, " ,\t");
        info->flagIn2++;
    }
    if(info->flagIn2) {
        info->fptIn2 = fileOpen(info->In2, "r");
    }
    
    if(info->flagIn3) {
        info->fptIn3 = fileOpen(info->In3, "r");
    }
    
    if(info->flagVx) {
        info->fptVx = fileOpen(info->Vx, "w");
    }
    
    if(info->flagVy) {
        info->fptVy = fileOpen(info->Vy, "w");
    }
    
    if(info->flagVz) {
        info->fptVz = fileOpen(info->Vz, "w");
    }
    
    if(info->flagOutFx) {
        info->fptOutFx = fileOpen(info->OutFx, "w");
    }
    
    if(info->flagOutFy) {
        info->fptOutFy = fileOpen(info->OutFy, "w");
    }
    
    if(info->flagOutFz) {
        info->fptOutFz = fileOpen(info->OutFz, "w");
    }
    
    if(info->flagOutDi) {
        info->fptOutDi = fileOpen(info->OutDi, "w");
    }
    
    if(info->flagSize) {
        info->fptSize = fileOpen(info->Size, "w");
    }
    
    if(info->flagOutCOMMAND) {
        info->fptOutCOMMAND = fileOpen(info->OutCOMMAND, "w");
    }
    
    if(info->flagOutBILD) {
        info->fptOutBILD = fileOpen(info->OutBILD, "w");
    }
    
    if(info->flagBG) {
    }
    
    if(info->flagBildThresLow) {
    }
    
    if(info->flagBildThresHigh) {
    }
    
    if(info->flagBildRangeLow) {
    }
    
    if(info->flagBildRangeHigh) {
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
    sprintf(panepath, "%s/src/Tools/mrcImage/mrcImageOpticalFlow/src/mrcImageOpticalFlow.pane", eospath);
    khoros_initialize(argc, argv, "EOS");
    fpt = fopen(panepath, "r");    if(NULL!=fpt) {
        fclose(fpt);
        kclui_initialize(panepath, KGEN_NONE, "EOS", "mrcImageOpticalFlow",
                     func_usage_additions,
                     func_get_args,
                     func_free_args);
    }
}
#endif /* KHOROS */ 
