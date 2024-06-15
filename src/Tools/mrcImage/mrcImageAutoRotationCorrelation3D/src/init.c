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
init0(mrcImageAutoRotationCorrelation3DInfo* info)
{
    info->fptIn = NULL;    info->flagIn = 0;
    info->fptRef = NULL;    info->flagRef = 0;
    info->fptOut = stdout;    info->flagOut = 0;
    info->fptCor = NULL;    info->flagCor = 0;
    info->fptFit = stdout;    info->flagFit = 0;
    info->EulerAngle = stringGetNthWord("YOYS", 1, "\0");    info->flagEulerAngle = 0;
    info->Rot1Min = 0.0;    info->flagRot1Min = 0;
    info->Rot1Max = 360.0;    info->flagRot1Max = 0;
    info->Rot1Delta = 5.0;    info->flagRot1Delta = 0;
    info->Rot2Min = 0.0;    info->flagRot2Min = 0;
    info->Rot2Max = 180.0;    info->flagRot2Max = 0;
    info->Rot2Delta = 5.0;    info->flagRot2Delta = 0;
    info->Rot3Min = 0.0;    info->flagRot3Min = 0;
    info->Rot3Max = 360.0;    info->flagRot3Max = 0;
    info->Rot3Delta = 5.0;    info->flagRot3Delta = 0;
    info->XrangeMin = 0;    info->flagXrangeMin = 0;
    info->XrangeMax = 0;    info->flagXrangeMax = 0;
    info->YrangeMin = 0;    info->flagYrangeMin = 0;
    info->YrangeMax = 0;    info->flagYrangeMax = 0;
    info->ZrangeMin = 0;    info->flagZrangeMin = 0;
    info->ZrangeMax = 0;    info->flagZrangeMax = 0;
    info->Mode = 0;    info->flagMode = 0;
    info->ModeRotation = 0;    info->flagModeRotation = 0;
    info->fptconfigFile = NULL;    info->flagconfigFile = 0;
    info->mode = 0;    info->flagmode = 0;
}

void
init1(mrcImageAutoRotationCorrelation3DInfo* info)
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
    
    if(!info->flagRef) {
        stringGetFromFile(s, "Ref", stdin, stdout, 0);
        info->Ref = stringGetNthWord(s, 1, " ,\t");
        info->flagRef++;
    }
    if(info->flagRef) {
        info->fptRef = fileOpen(info->Ref, "r");
    }
    
    if(info->flagOut) {
        info->fptOut = fileOpen(info->Out, "w");
    }
    
    if(info->flagCor) {
        info->fptCor = fileOpen(info->Cor, "w");
    }
    
    if(info->flagFit) {
        info->fptFit = fileOpen(info->Fit, "w");
    }
    
    if(info->flagEulerAngle) {
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
    
    if(info->flagXrangeMin) {
    }
    
    if(info->flagXrangeMax) {
    }
    
    if(info->flagYrangeMin) {
    }
    
    if(info->flagYrangeMax) {
    }
    
    if(info->flagZrangeMin) {
    }
    
    if(info->flagZrangeMax) {
    }
    
    if(info->flagMode) {
    }
    
    if(info->flagModeRotation) {
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
    sprintf(panepath, "%s/src/Tools/mrcImage/mrcImageAutoRotationCorrelation3D/src/mrcImageAutoRotationCorrelation3D.pane", eospath);
    khoros_initialize(argc, argv, "EOS");
    fpt = fopen(panepath, "r");    if(NULL!=fpt) {
        fclose(fpt);
        kclui_initialize(panepath, KGEN_NONE, "EOS", "mrcImageAutoRotationCorrelation3D",
                     func_usage_additions,
                     func_get_args,
                     func_free_args);
    }
}
#endif /* KHOROS */ 
