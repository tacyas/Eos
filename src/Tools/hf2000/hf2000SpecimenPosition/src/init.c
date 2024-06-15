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
init0(hf2000SpecimenPositionInfo* info)
{
    info->fptIn = NULL;    info->flagIn = 0;
    info->fptOut = stdout;    info->flagOut = 0;
    info->tty = stringGetNthWord("/dev/ttyS1", 1, "\0");    info->flagtty = 0;
    info->Speed = 4800;    info->flagSpeed = 0;
    info->posX = 0.0;    info->flagposX = 0;
    info->posY = 0.0;    info->flagposY = 0;
    info->Interactive = 5;    info->flagInteractive = 0;
    info->Host = stringGetNthWord("tkyemg-pc06", 1, "\0");    info->flagHost = 0;
    info->Port = 6000;    info->flagPort = 0;
    info->fptconfigFile = NULL;    info->flagconfigFile = 0;
    info->mode = 0;    info->flagmode = 0;
}

void
init1(hf2000SpecimenPositionInfo* info)
{
    char s[1024];
    int i;
    if(info->flagIn) {
        info->fptIn = fileOpen(info->In, "r");
    }
    
    if(info->flagOut) {
        info->fptOut = fileOpen(info->Out, "w");
    }
    
    if(info->flagtty) {
    }
    
    if(info->flagSpeed) {
    }
    
    if(info->flagposX) {
    }
    
    if(info->flagposY) {
    }
    
    if(info->flagInteractive) {
    }
    
    if(info->flagHost) {
    }
    
    if(info->flagPort) {
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
    sprintf(panepath, "%s/src/Tools/hf2000/hf2000SpecimenPosition/src/hf2000SpecimenPosition.pane", eospath);
    khoros_initialize(argc, argv, "EOS");
    fpt = fopen(panepath, "r");    if(NULL!=fpt) {
        fclose(fpt);
        kclui_initialize(panepath, KGEN_NONE, "EOS", "hf2000SpecimenPosition",
                     func_usage_additions,
                     func_get_args,
                     func_free_args);
    }
}
#endif /* KHOROS */ 
