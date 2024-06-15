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
init0(Display2Info* info)
{
    info->fptIn = NULL;    info->flagIn = 0;
    info->Template = stringGetNthWord("%d.roi", 1, "\0");    info->flagTemplate = 0;
    info->ThresHigh = 0.0;    info->flagThresHigh = 0;
    info->ThresLow = 0.0;    info->flagThresLow = 0;
    info->Zoom = 1.0;    info->flagZoom = 0;
    info->Inverse=0;
    info->Out = stringGetNthWord(".EosLog", 1, "\0");    info->flagOut = 0;
    info->Default = stringGetNthWord("~/.Eos/Display2", 1, "\0");    info->flagDefault = 0;
    info->geometry = stringGetNthWord(":0.0", 1, "\0");    info->flaggeometry = 0;
    info->display = stringGetNthWord("1024x1024+0+0", 1, "\0");    info->flagdisplay = 0;
    info->fptconfigFile = NULL;    info->flagconfigFile = 0;
    info->mode = 0;    info->flagmode = 0;
}

void
init1(Display2Info* info)
{
    char s[1024];
    int i;
    if(info->flagIn) {
        info->fptIn = fileOpen(info->In, "r");
    }
    
    if(info->flagTemplate) {
    }
    
    if(info->flagThresHigh) {
    }
    
    if(info->flagThresLow) {
    }
    
    if(info->flagZoom) {
    }
    
    if(info->flagOut) {
    }
    
    if(info->flagDefault) {
    }
    
    if(info->flaggeometry) {
    }
    
    if(info->flagdisplay) {
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
    sprintf(panepath, "%s/src/Tools/Integration/Display2/src/Display2.pane", eospath);
    khoros_initialize(argc, argv, "EOS");
    fpt = fopen(panepath, "r");    if(NULL!=fpt) {
        fclose(fpt);
        kclui_initialize(panepath, KGEN_NONE, "EOS", "Display2",
                     func_usage_additions,
                     func_get_args,
                     func_free_args);
    }
}
#endif /* KHOROS */ 
