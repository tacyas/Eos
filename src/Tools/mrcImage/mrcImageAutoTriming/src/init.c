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
init0(mrcImageAutoTrimingInfo* info)
{
    info->fptIn = NULL;    info->flagIn = 0;
    info->fptOut = NULL;    info->flagOut = 0;
    info->fptOutParam = stdout;    info->flagOutParam = 0;
    info->EAMode = stringGetNthWord("ZONS", 1, "\0");    info->flagEAMode = 0;
    info->Rot1Min = -5;    info->flagRot1Min = 0;
    info->Rot1Max = 5;    info->flagRot1Max = 0;
    info->Rot1Delta = 1;    info->flagRot1Delta = 0;
    info->Rot2Min = -5;    info->flagRot2Min = 0;
    info->Rot2Max = 5;    info->flagRot2Max = 0;
    info->Rot2Delta = 1;    info->flagRot2Delta = 0;
    info->Rot3Min = -5;    info->flagRot3Min = 0;
    info->Rot3Max = 5;    info->flagRot3Max = 0;
    info->Rot3Delta = 1;    info->flagRot3Delta = 0;
    info->InterpolationMode = 0;    info->flagInterpolationMode = 0;
    info->fptconfigFile = NULL;    info->flagconfigFile = 0;
    info->mode = 0;    info->flagmode = 0;
}

void
init1(mrcImageAutoTrimingInfo* info)
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
    
    if(!info->flagOut) {
        stringGetFromFile(s, "Out", stdin, stdout, 0);
        info->Out = stringGetNthWord(s, 1, " ,\t");
        info->flagOut++;
    }
    if(info->flagOut) {
        info->fptOut = fileOpen(info->Out, "w");
    }
    
    if(info->flagOutParam) {
        info->fptOutParam = fileOpen(info->OutParam, "w");
    }
    
    if(info->flagEAMode) {
    }
    
    if(info->flagRot1Min) {
    }
    
    if(info->flagRot1Max) {
    }
    
    if(info->flagRot1Delta) {
    }
    
    if(info->flagRot2Min) {
    }
    
    if(info->flagRot2Max) {
    }
    
    if(info->flagRot2Delta) {
    }
    
    if(info->flagRot3Min) {
    }
    
    if(info->flagRot3Max) {
    }
    
    if(info->flagRot3Delta) {
    }
    
    if(info->flagInterpolationMode) {
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
    sprintf(panepath, "%s/src/Tools/mrcImage/mrcImageAutoTriming/src/mrcImageAutoTriming.pane", eospath);
    khoros_initialize(argc, argv, "EOS");
    fpt = fopen(panepath, "r");    if(NULL!=fpt) {
        fclose(fpt);
        kclui_initialize(panepath, KGEN_NONE, "EOS", "mrcImageAutoTriming",
                     func_usage_additions,
                     func_get_args,
                     func_free_args);
    }
}
#endif /* KHOROS */ 
