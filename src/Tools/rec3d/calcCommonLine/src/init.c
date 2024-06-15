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
init0(calcCommonLineInfo* info)
{
    info->fptIn = NULL;    info->flagIn = 0;
    info->EMode1 = stringGetNthWord("YOYS", 1, "\0");    info->flagEMode1 = 0;
    info->Rot1_1 = 0.0;    info->flagRot1_1 = 0;
    info->Rot1_2 = 0.0;    info->flagRot1_2 = 0;
    info->Rot1_3 = 0.0;    info->flagRot1_3 = 0;
    info->EMode2 = stringGetNthWord("YOYS", 1, "\0");    info->flagEMode2 = 0;
    info->Rot2_1 = 0.0;    info->flagRot2_1 = 0;
    info->Rot2_2 = 0.0;    info->flagRot2_2 = 0;
    info->Rot2_3 = 0.0;    info->flagRot2_3 = 0;
    info->fptOut = stdout;    info->flagOut = 0;
    info->fptconfigFile = NULL;    info->flagconfigFile = 0;
    info->mode = 0;    info->flagmode = 0;
}

void
init1(calcCommonLineInfo* info)
{
    char s[1024];
    int i;
    if(info->flagIn) {
        info->fptIn = fileOpen(info->In, "r");
    }
    
    if(info->flagEMode1) {
    }
    
    if(info->flagRot1_1) {
    }
    
    if(info->flagRot1_2) {
    }
    
    if(info->flagRot1_3) {
    }
    
    if(info->flagEMode2) {
    }
    
    if(info->flagRot2_1) {
    }
    
    if(info->flagRot2_2) {
    }
    
    if(info->flagRot2_3) {
    }
    
    if(info->flagOut) {
        info->fptOut = fileOpen(info->Out, "w");
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
    sprintf(panepath, "%s/src/Tools/rec3d/calcCommonLine/src/calcCommonLine.pane", eospath);
    khoros_initialize(argc, argv, "EOS");
    fpt = fopen(panepath, "r");    if(NULL!=fpt) {
        fclose(fpt);
        kclui_initialize(panepath, KGEN_NONE, "EOS", "calcCommonLine",
                     func_usage_additions,
                     func_get_args,
                     func_free_args);
    }
}
#endif /* KHOROS */ 
