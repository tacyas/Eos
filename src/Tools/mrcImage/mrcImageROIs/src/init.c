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
init0(mrcImageROIsInfo* info)
{
    info->fptIn = NULL;    info->flagIn = 0;
    info->fptInfo = NULL;    info->flagInfo = 0;
    info->fptOut = NULL;    info->flagOut = 0;
    info->Shrink = NULL;    info->flagShrink = 0;
    info->Width = 0.0;    info->flagWidth = 0;
    info->Height = 0.0;    info->flagHeight = 0;
    info->NonPeriodic=0;
    info->PadMode = 0;    info->flagPadMode = 0;
    info->Mode = 2;    info->flagMode = 0;
    info->fptconfigFile = NULL;    info->flagconfigFile = 0;
    info->mode = 0;    info->flagmode = 0;
}

void
init1(mrcImageROIsInfo* info)
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
    
    if(!info->flagInfo) {
        stringGetFromFile(s, "Info", stdin, stdout, 0);
        info->Info = stringGetNthWord(s, 1, " ,\t");
        info->flagInfo++;
    }
    if(info->flagInfo) {
        info->fptInfo = fileOpen(info->Info, "r");
    }
    
    if(info->flagOut) {
        info->fptOut = fileOpen(info->Out, "w");
    }
    
    if(info->flagShrink) {
    }
    
    if(info->flagWidth) {
    }
    
    if(info->flagHeight) {
    }
    
    if(info->flagPadMode) {
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
    sprintf(panepath, "%s/src/Tools/mrcImage/mrcImageROIs/src/mrcImageROIs.pane", eospath);
    khoros_initialize(argc, argv, "EOS");
    fpt = fopen(panepath, "r");    if(NULL!=fpt) {
        fclose(fpt);
        kclui_initialize(panepath, KGEN_NONE, "EOS", "mrcImageROIs",
                     func_usage_additions,
                     func_get_args,
                     func_free_args);
    }
}
#endif /* KHOROS */ 
