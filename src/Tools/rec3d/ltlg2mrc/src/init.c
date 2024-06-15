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
init0(ltlg2mrcInfo* info)
{
    info->fptIn = NULL;    info->flagIn = 0;
    info->fptOut = NULL;    info->flagOut = 0;
    info->fptconfigFile = NULL;    info->flagconfigFile = 0;
    info->Title = stringGetNthWord("NULL", 1, "\0");    info->flagTitle = 0;
    info->delta = 2.5;    info->flagdelta = 0;
    info->RepeatDistance = 2.5;    info->flagRepeatDistance = 0;
    info->rMax = 2.5;    info->flagrMax = 0;
    info->phiStart = 0;    info->flagphiStart = 0;
    info->zMin = 0.0;    info->flagzMin = 0;
    info->zMax = 55.0;    info->flagzMax = 0;
    info->deltaz = 2.5;    info->flagdeltaz = 0;
    info->WeightOf0thLayer = 0.5;    info->flagWeightOf0thLayer = 0;
    info->fptLayer = NULL;    info->flagLayer = 0;
    info->f99=0;
    info->CUT = 0.5;    info->flagCUT = 0;
    info->Mean = 0.0;    info->flagMean = 0;
    info->Sigma = 0.0;    info->flagSigma = 0;
    info->Inverse=0;
    info->notInteractive=0;
    info->AntiPole=0;
    info->mode = 0;    info->flagmode = 0;
}

void
init1(ltlg2mrcInfo* info)
{
    char s[1024];
    int i;
    if(info->flagIn) {
        info->fptIn = fileOpen(info->In, "r");
    }
    
    if(info->flagOut) {
        info->fptOut = fileOpen(info->Out, "w");
    }
    
    if(info->flagconfigFile) {
        info->fptconfigFile = fileOpen(info->configFile, "r");
    }
    
    if(info->flagTitle) {
    }
    
    if(info->flagdelta) {
    }
    
    if(info->flagRepeatDistance) {
    }
    
    if(info->flagrMax) {
    }
    
    if(info->flagphiStart) {
    }
    
    if(info->flagzMin) {
    }
    
    if(info->flagzMax) {
    }
    
    if(info->flagdeltaz) {
    }
    
    if(info->flagWeightOf0thLayer) {
    }
    
    if(info->flagLayer) {
        info->fptLayer = fileOpen(info->Layer, "r");
    }
    
    if(info->flagCUT) {
    }
    
    if(info->flagMean) {
    }
    
    if(info->flagSigma) {
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
    sprintf(panepath, "%s/src/Tools/rec3d/ltlg2mrc/src/ltlg2mrc.pane", eospath);
    khoros_initialize(argc, argv, "EOS");
    fpt = fopen(panepath, "r");    if(NULL!=fpt) {
        fclose(fpt);
        kclui_initialize(panepath, KGEN_NONE, "EOS", "ltlg2mrc",
                     func_usage_additions,
                     func_get_args,
                     func_free_args);
    }
}
#endif /* KHOROS */ 
