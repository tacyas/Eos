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
init0(mrcMultiFFTCentralSectionsCompareInfo* info)
{
    info->fptIn2D = NULL;    info->flagIn2D = 0;
    info->fptIn3D = NULL;    info->flagIn3D = 0;
    info->volPath = stringGetNthWord("NULL", 1, "\0");    info->flagvolPath = 0;
    info->fptPrior = NULL;    info->flagPrior = 0;
    info->PriPath = stringGetNthWord("./", 1, "\0");    info->flagPriPath = 0;
    info->EulerMode = stringGetNthWord("YOYS", 1, "\0");    info->flagEulerMode = 0;
    info->Rot1Start = 0.0;    info->flagRot1Start = 0;
    info->Rot1End = 360.0;    info->flagRot1End = 0;
    info->Rot1Delta = 10;    info->flagRot1Delta = 0;
    info->Rot2Start = 0.0;    info->flagRot2Start = 0;
    info->Rot2End = 360.0;    info->flagRot2End = 0;
    info->Rot2Delta = 10;    info->flagRot2Delta = 0;
    info->Rot3Start = 0.0;    info->flagRot3Start = 0;
    info->Rot3End = 360.0;    info->flagRot3End = 0;
    info->Rot3Delta = 10;    info->flagRot3Delta = 0;
    info->TransX = 0.0;    info->flagTransX = 0;
    info->TransY = 0.0;    info->flagTransY = 0;
    info->InterpMode = 0;    info->flagInterpMode = 0;
    info->fptOut1 = stdout;    info->flagOut1 = 0;
    info->fptOutLikelihood = stdout;    info->flagOutLikelihood = 0;
    info->fptconfigFile = NULL;    info->flagconfigFile = 0;
    info->Lcalcmode = 0;    info->flagLcalcmode = 0;
    info->Lmode1 = 0.0;    info->flagLmode1 = 0;
    info->Lmode2 = 0.0;    info->flagLmode2 = 0;
    info->mode = 0;    info->flagmode = 0;
}

void
init1(mrcMultiFFTCentralSectionsCompareInfo* info)
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
    
    if(!info->flagvolPath) {
        stringGetFromFile(s, "volPath", stdin, stdout, 0);
        info->volPath = stringGetNthWord(s, 1, " ,\t");
        info->flagvolPath++;
    }
    if(info->flagvolPath) {
    }
    
    if(info->flagPrior) {
        info->fptPrior = fileOpen(info->Prior, "r");
    }
    
    if(info->flagPriPath) {
    }
    
    if(info->flagEulerMode) {
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
    
    if(info->flagTransX) {
    }
    
    if(info->flagTransY) {
    }
    
    if(info->flagInterpMode) {
    }
    
    if(info->flagOut1) {
        info->fptOut1 = fileOpen(info->Out1, "w");
    }
    
    if(info->flagOutLikelihood) {
        info->fptOutLikelihood = fileOpen(info->OutLikelihood, "w");
    }
    
    if(info->flagconfigFile) {
        info->fptconfigFile = fileOpen(info->configFile, "r");
    }
    
    if(info->flagLcalcmode) {
    }
    
    if(info->flagLmode1) {
    }
    
    if(info->flagLmode2) {
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
    sprintf(panepath, "%s/src/Tools/mrcImage/mrcMultiFFTCentralSectionsCompare/src/mrcMultiFFTCentralSectionsCompare.pane", eospath);
    khoros_initialize(argc, argv, "EOS");
    fpt = fopen(panepath, "r");    if(NULL!=fpt) {
        fclose(fpt);
        kclui_initialize(panepath, KGEN_NONE, "EOS", "mrcMultiFFTCentralSectionsCompare",
                     func_usage_additions,
                     func_get_args,
                     func_free_args);
    }
}
#endif /* KHOROS */ 
