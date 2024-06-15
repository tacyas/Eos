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
init0(FETOrientationSearchByFeatureAlignmentInfo* info)
{
    info->fptInS = NULL;    info->flagInS = 0;
    info->fptInS2 = NULL;    info->flagInS2 = 0;
    info->fptInF = NULL;    info->flagInF = 0;
    info->fptInA = NULL;    info->flagInA = 0;
    info->fptOut = NULL;    info->flagOut = 0;
    info->fptOutLOG = NULL;    info->flagOutLOG = 0;
    info->fptOutA = NULL;    info->flagOutA = 0;
    info->fptOut2D = NULL;    info->flagOut2D = 0;
    info->ITMAX = 8;    info->flagITMAX = 0;
    info->DEVMAX = 3;    info->flagDEVMAX = 0;
    info->MITMAX = 3;    info->flagMITMAX = 0;
    info->MDEVMAX = 3;    info->flagMDEVMAX = 0;
    info->LDN = 8;    info->flagLDN = 0;
    info->SRL = 0.0;    info->flagSRL = 0;
    info->fptconfigFile = NULL;    info->flagconfigFile = 0;
    info->mode = 202;    info->flagmode = 0;
}

void
init1(FETOrientationSearchByFeatureAlignmentInfo* info)
{
    char s[1024];
    int i;
    if(info->flagInS) {
        info->fptInS = fileOpen(info->InS, "r");
    }
    
    if(info->flagInS2) {
        info->fptInS2 = fileOpen(info->InS2, "r");
    }
    
    if(info->flagInF) {
        info->fptInF = fileOpen(info->InF, "r");
    }
    
    if(info->flagInA) {
        info->fptInA = fileOpen(info->InA, "r");
    }
    
    if(info->flagOut) {
        info->fptOut = fileOpen(info->Out, "w");
    }
    
    if(info->flagOutLOG) {
        info->fptOutLOG = fileOpen(info->OutLOG, "w");
    }
    
    if(info->flagOutA) {
        info->fptOutA = fileOpen(info->OutA, "w");
    }
    
    if(info->flagOut2D) {
        info->fptOut2D = fileOpen(info->Out2D, "w");
    }
    
    if(info->flagITMAX) {
    }
    
    if(info->flagDEVMAX) {
    }
    
    if(info->flagMITMAX) {
    }
    
    if(info->flagMDEVMAX) {
    }
    
    if(info->flagLDN) {
    }
    
    if(info->flagSRL) {
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
    sprintf(panepath, "%s/src/Tools/rec3d/FETOrientationSearchByFeatureAlignment/src/FETOrientationSearchByFeatureAlignment.pane", eospath);
    khoros_initialize(argc, argv, "EOS");
    fpt = fopen(panepath, "r");    if(NULL!=fpt) {
        fclose(fpt);
        kclui_initialize(panepath, KGEN_NONE, "EOS", "FETOrientationSearchByFeatureAlignment",
                     func_usage_additions,
                     func_get_args,
                     func_free_args);
    }
}
#endif /* KHOROS */ 
