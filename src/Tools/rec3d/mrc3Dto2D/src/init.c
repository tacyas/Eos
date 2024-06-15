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
init0(mrc3Dto2DInfo* info)
{
    info->fptIn = NULL;    info->flagIn = 0;
    info->fptOut = NULL;    info->flagOut = 0;
    info->filenamePrefix = stringGetNthWord("2D", 1, "\0");    info->flagfilenamePrefix = 0;
    info->filenameSuffix = stringGetNthWord("2d", 1, "\0");    info->flagfilenameSuffix = 0;
    info->filenameFormat = stringGetNthWord("%s-%05d.%s", 1, "\0");    info->flagfilenameFormat = 0;
    info->Rot1Start = 0.0;    info->flagRot1Start = 0;
    info->Rot1End = 360.0;    info->flagRot1End = 0;
    info->Rot1Delta = 10;    info->flagRot1Delta = 0;
    info->Rot2Start = 0.0;    info->flagRot2Start = 0;
    info->Rot2End = 360.0;    info->flagRot2End = 0;
    info->Rot2Delta = 10;    info->flagRot2Delta = 0;
    info->Rot3Start = 0.0;    info->flagRot3Start = 0;
    info->Rot3End = 360.0;    info->flagRot3End = 0;
    info->Rot3Delta = 10;    info->flagRot3Delta = 0;
    info->EulerMode = stringGetNthWord("ZOYS", 1, "\0");    info->flagEulerMode = 0;
    info->InterpolationMode = 1;    info->flagInterpolationMode = 0;
    info->AreaMode = 0;    info->flagAreaMode = 0;
    info->pthreadMax = 1;    info->flagpthreadMax = 0;
    info->fptconfigFile = NULL;    info->flagconfigFile = 0;
    info->mode = 0;    info->flagmode = 0;
}

void
init1(mrc3Dto2DInfo* info)
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
    
    if(info->flagfilenamePrefix) {
    }
    
    if(info->flagfilenameSuffix) {
    }
    
    if(info->flagfilenameFormat) {
    }
    
    if(info->flagRot1Start) {
    }
    
    if(info->flagRot1End) {
    }
    
    if(info->flagRot1Delta) {
    }
    
    if(info->flagRot2Start) {
    }
    
    if(info->flagRot2End) {
    }
    
    if(info->flagRot2Delta) {
    }
    
    if(info->flagRot3Start) {
    }
    
    if(info->flagRot3End) {
    }
    
    if(info->flagRot3Delta) {
    }
    
    if(info->flagEulerMode) {
    }
    
    if(info->flagInterpolationMode) {
    }
    
    if(info->flagAreaMode) {
    }
    
    if(info->flagpthreadMax) {
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
    sprintf(panepath, "%s/src/Tools/rec3d/mrc3Dto2D/src/mrc3Dto2D.pane", eospath);
    khoros_initialize(argc, argv, "EOS");
    fpt = fopen(panepath, "r");    if(NULL!=fpt) {
        fclose(fpt);
        kclui_initialize(panepath, KGEN_NONE, "EOS", "mrc3Dto2D",
                     func_usage_additions,
                     func_get_args,
                     func_free_args);
    }
}
#endif /* KHOROS */ 
