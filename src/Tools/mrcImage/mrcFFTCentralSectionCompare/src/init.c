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
init0(mrcFFTCentralSectionCompareInfo* info)
{
    info->fptIn2D = NULL;    info->flagIn2D = 0;
    info->fptIn3D = NULL;    info->flagIn3D = 0;
    info->EAMode = stringGetNthWord("YOYS", 1, "\0");    info->flagEAMode = 0;
    info->Rot1 = 0.0;    info->flagRot1 = 0;
    info->Rot2 = 0.0;    info->flagRot2 = 0;
    info->Rot3 = 0.0;    info->flagRot3 = 0;
    info->TransX = 0.0;    info->flagTransX = 0;
    info->TransY = 0.0;    info->flagTransY = 0;
    info->InterpMode = 0;    info->flagInterpMode = 0;
    info->fptOut = stdout;    info->flagOut = 0;
    info->fptconfigFile = NULL;    info->flagconfigFile = 0;
    info->mode = 0;    info->flagmode = 0;
}

void
init1(mrcFFTCentralSectionCompareInfo* info)
{
    char s[1024];
    int i;
    if(!info->flagIn2D) {
        stringGetFromFile(s, "In2D", stdin, stdout, 0);
        info->In2D = stringGetNthWord(s, 1, " ,\t");
        info->flagIn2D++;
    }
    if(info->flagIn2D) {
        info->fptIn2D = fileOpen(info->In2D, "r");
    }
    
    if(!info->flagIn3D) {
        stringGetFromFile(s, "In3D", stdin, stdout, 0);
        info->In3D = stringGetNthWord(s, 1, " ,\t");
        info->flagIn3D++;
    }
    if(info->flagIn3D) {
        info->fptIn3D = fileOpen(info->In3D, "r");
    }
    
    if(info->flagEAMode) {
    }
    
    if(info->flagRot1) {
    }
    
    if(info->flagRot2) {
    }
    
    if(info->flagRot3) {
    }
    
    if(info->flagTransX) {
    }
    
    if(info->flagTransY) {
    }
    
    if(info->flagInterpMode) {
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
    sprintf(panepath, "%s/src/Tools/mrcImage/mrcFFTCentralSectionCompare/src/mrcFFTCentralSectionCompare.pane", eospath);
    khoros_initialize(argc, argv, "EOS");
    fpt = fopen(panepath, "r");    if(NULL!=fpt) {
        fclose(fpt);
        kclui_initialize(panepath, KGEN_NONE, "EOS", "mrcFFTCentralSectionCompare",
                     func_usage_additions,
                     func_get_args,
                     func_free_args);
    }
}
#endif /* KHOROS */ 
