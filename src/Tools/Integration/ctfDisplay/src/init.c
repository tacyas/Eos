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
init0(ctfDisplayInfo* info)
{
    info->fptinMRC = NULL;    info->flaginMRC = 0;
    info->fptoutCTF = stdout;    info->flagoutCTF = 0;
    info->Rmax = 0.2;    info->flagRmax = 0;
    info->Imax = 0.2;    info->flagImax = 0;
    info->Imin = 0.02;    info->flagImin = 0;
    info->AutoRange=0;
    info->Log=0;
    info->fptconfigFile = NULL;    info->flagconfigFile = 0;
    info->mode = 0;    info->flagmode = 0;
}

void
init1(ctfDisplayInfo* info)
{
    char s[1024];
    int i;
    if(info->flaginMRC) {
        info->fptinMRC = fileOpen(info->inMRC, "r");
    }
    
    if(info->flagoutCTF) {
        info->fptoutCTF = fopen(info->outCTF, "a+");
    }
    
    if(info->flagRmax) {
    }
    
    if(info->flagImax) {
    }
    
    if(info->flagImin) {
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
    sprintf(panepath, "%s/src/Tools/Integration/ctfDisplay/src/ctfDisplay.pane", eospath);
    khoros_initialize(argc, argv, "EOS");
    fpt = fopen(panepath, "r");    if(NULL!=fpt) {
        fclose(fpt);
        kclui_initialize(panepath, KGEN_NONE, "EOS", "ctfDisplay",
                     func_usage_additions,
                     func_get_args,
                     func_free_args);
    }
}
#endif /* KHOROS */ 
