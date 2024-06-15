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
init0(mrcImageAutoRotationCorrelationInfo* info)
{
    info->fptIn = NULL;    info->flagIn = 0;
    info->fptRef = NULL;    info->flagRef = 0;
    info->nRot1 = 1;    info->flagnRot1 = 0;
    info->nRot2 = 1;    info->flagnRot2 = 0;
    info->nRot3 = 1;    info->flagnRot3 = 0;
    info->dRot1 = 1.0;    info->flagdRot1 = 0;
    info->dRot2 = 1.0;    info->flagdRot2 = 0;
    info->dRot3 = 1.0;    info->flagdRot3 = 0;
    info->startRot1 = 0.0;    info->flagstartRot1 = 0;
    info->startRot2 = 0.0;    info->flagstartRot2 = 0;
    info->startRot3 = 0.0;    info->flagstartRot3 = 0;
    info->StackOrder = 0;    info->flagStackOrder = 0;
    info->fptOut = NULL;    info->flagOut = 0;
    info->fptOutASC = stdout;    info->flagOutASC = 0;
    info->fptcorFile = NULL;    info->flagcorFile = 0;
    info->fptcorFile2 = NULL;    info->flagcorFile2 = 0;
    info->fptcorAllFile = NULL;    info->flagcorAllFile = 0;
    info->fptfitFile = NULL;    info->flagfitFile = 0;
    info->fptfitFile2 = NULL;    info->flagfitFile2 = 0;
    info->RefineMode = 0;    info->flagRefineMode = 0;
    info->Rot = 36;    info->flagRot = 0;
    info->minAngle = -5.0;    info->flagminAngle = 0;
    info->maxAngle = 5.0;    info->flagmaxAngle = 0;
    info->refStep1 = 1;    info->flagrefStep1 = 0;
    info->refStep2 = 1;    info->flagrefStep2 = 0;
    info->refStep3 = 1;    info->flagrefStep3 = 0;
    info->nRot1AreaMin = -360;    info->flagnRot1AreaMin = 0;
    info->nRot1AreaMax = 360;    info->flagnRot1AreaMax = 0;
    info->nRot1AreaStep = 25;    info->flagnRot1AreaStep = 0;
    info->nRot2AreaMin = -360;    info->flagnRot2AreaMin = 0;
    info->nRot2AreaMax = 360;    info->flagnRot2AreaMax = 0;
    info->nRot2AreaStep = 25;    info->flagnRot2AreaStep = 0;
    info->nRot3AreaMin = -360;    info->flagnRot3AreaMin = 0;
    info->nRot3AreaMax = 360;    info->flagnRot3AreaMax = 0;
    info->nRot3AreaStep = 25;    info->flagnRot3AreaStep = 0;
    info->MagRangeMin = 1.0;    info->flagMagRangeMin = 0;
    info->MagRangeMax = 1.0;    info->flagMagRangeMax = 0;
    info->MagRangeStep = 0.1;    info->flagMagRangeStep = 0;
    info->Iter = 1;    info->flagIter = 0;
    info->Method = 0;    info->flagMethod = 0;
    info->sminx = 0;    info->flagsminx = 0;
    info->sminy = 0;    info->flagsminy = 0;
    info->smaxx = 0/*N.x-1*/;    info->flagsmaxx = 0;
    info->smaxy = 0/*N.y-1*/;    info->flagsmaxy = 0;
    info->Shift=0;
    info->RepeatX = 27.3;    info->flagRepeatX = 0;
    info->RepeatXDelta = 5;    info->flagRepeatXDelta = 0;
    info->RepeatY = 27.3;    info->flagRepeatY = 0;
    info->RepeatYDelta = 5;    info->flagRepeatYDelta = 0;
    info->Xshift=0;
    info->NoShift=0;
    info->fptLog = stdout;    info->flagLog = 0;
    info->pvm = 1;    info->flagpvm = 0;
    info->fptpvmList = NULL;    info->flagpvmList = 0;
    info->fptconfigFile = NULL;    info->flagconfigFile = 0;
    info->mode = 0;    info->flagmode = 0;
}

void
init1(mrcImageAutoRotationCorrelationInfo* info)
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
    
    if(info->flagnRot1) {
    }
    
    if(info->flagnRot2) {
    }
    
    if(info->flagnRot3) {
    }
    
    if(info->flagdRot1) {
    }
    
    if(info->flagdRot2) {
    }
    
    if(info->flagdRot3) {
    }
    
    if(info->flagstartRot1) {
    }
    
    if(info->flagstartRot2) {
    }
    
    if(info->flagstartRot3) {
    }
    
    if(info->flagStackOrder) {
    }
    
    if(info->flagOut) {
        info->fptOut = fileOpen(info->Out, "w");
    }
    
    if(info->flagOutASC) {
        info->fptOutASC = fileOpen(info->OutASC, "w");
    }
    
    if(info->flagcorFile) {
        info->fptcorFile = fileOpen(info->corFile, "w");
    }
    
    if(info->flagcorFile2) {
        info->fptcorFile2 = fileOpen(info->corFile2, "w");
    }
    
    if(info->flagcorAllFile) {
        info->fptcorAllFile = fileOpen(info->corAllFile, "w");
    }
    
    if(info->flagfitFile) {
        info->fptfitFile = fileOpen(info->fitFile, "w");
    }
    
    if(info->flagfitFile2) {
        info->fptfitFile2 = fileOpen(info->fitFile2, "w");
    }
    
    if(info->flagRefineMode) {
    }
    
    if(info->flagRot) {
    }
    
    if(info->flagminAngle) {
    }
    
    if(info->flagmaxAngle) {
    }
    
    if(info->flagrefStep1) {
    }
    
    if(info->flagrefStep2) {
    }
    
    if(info->flagrefStep3) {
    }
    
    if(info->flagnRot1AreaMin) {
    }
    
    if(info->flagnRot1AreaMax) {
    }
    
    if(info->flagnRot1AreaStep) {
    }
    
    if(info->flagnRot2AreaMin) {
    }
    
    if(info->flagnRot2AreaMax) {
    }
    
    if(info->flagnRot2AreaStep) {
    }
    
    if(info->flagnRot3AreaMin) {
    }
    
    if(info->flagnRot3AreaMax) {
    }
    
    if(info->flagnRot3AreaStep) {
    }
    
    if(info->flagMagRangeMin) {
    }
    
    if(info->flagMagRangeMax) {
    }
    
    if(info->flagMagRangeStep) {
    }
    
    if(info->flagIter) {
    }
    
    if(info->flagMethod) {
    }
    
    if(info->flagsminx) {
    }
    
    if(info->flagsminy) {
    }
    
    if(info->flagsmaxx) {
    }
    
    if(info->flagsmaxy) {
    }
    
    if(info->flagRepeatX) {
    }
    
    if(info->flagRepeatXDelta) {
    }
    
    if(info->flagRepeatY) {
    }
    
    if(info->flagRepeatYDelta) {
    }
    
    if(info->flagLog) {
        info->fptLog = fileOpen(info->Log, "w");
    }
    
    if(info->flagpvm) {
    }
    
    if(info->flagpvmList) {
        info->fptpvmList = fileOpen(info->pvmList, "r");
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
    sprintf(panepath, "%s/src/Tools/mrcImage/mrcImageAutoRotationCorrelation/src/mrcImageAutoRotationCorrelation.pane", eospath);
    khoros_initialize(argc, argv, "EOS");
    fpt = fopen(panepath, "r");    if(NULL!=fpt) {
        fclose(fpt);
        kclui_initialize(panepath, KGEN_NONE, "EOS", "mrcImageAutoRotationCorrelation",
                     func_usage_additions,
                     func_get_args,
                     func_free_args);
    }
}
#endif /* KHOROS */ 
