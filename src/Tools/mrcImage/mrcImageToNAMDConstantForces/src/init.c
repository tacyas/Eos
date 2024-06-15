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
init0(mrcImageToNAMDConstantForcesInfo* info)
{
    info->fptIn = NULL;    info->flagIn = 0;
    info->fptInPDB = NULL;    info->flagInPDB = 0;
    info->fptOut = stdout;    info->flagOut = 0;
    info->Weight = 1.0;    info->flagWeight = 0;
    info->ScalingFactor = 1.0;    info->flagScalingFactor = 0;
    info->Contour = 0.0;    info->flagContour = 0;
    info->Rotate = 0;    info->flagRotate = 0;
    info->RWeight = 0.1;    info->flagRWeight = 0;
    info->Seed = 0.0;    info->flagSeed = 0;
    info->nowater=0;
    info->fptconfigFile = NULL;    info->flagconfigFile = 0;
    info->mode = 0;    info->flagmode = 0;
}

void
init1(mrcImageToNAMDConstantForcesInfo* info)
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
    
    if(!info->flagInPDB) {
        stringGetFromFile(s, "InPDB", stdin, stdout, 0);
        info->InPDB = stringGetNthWord(s, 1, " ,\t");
        info->flagInPDB++;
    }
    if(info->flagInPDB) {
        info->fptInPDB = fileOpen(info->InPDB, "r");
    }
    
    if(info->flagOut) {
        info->fptOut = fileOpen(info->Out, "w");
    }
    
    if(info->flagWeight) {
    }
    
    if(info->flagScalingFactor) {
    }
    
    if(info->flagContour) {
    }
    
    if(info->flagRotate) {
    }
    
    if(info->flagRWeight) {
    }
    
    if(info->flagSeed) {
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
    sprintf(panepath, "%s/src/Tools/mrcImage/mrcImageToNAMDConstantForces/src/mrcImageToNAMDConstantForces.pane", eospath);
    khoros_initialize(argc, argv, "EOS");
    fpt = fopen(panepath, "r");    if(NULL!=fpt) {
        fclose(fpt);
        kclui_initialize(panepath, KGEN_NONE, "EOS", "mrcImageToNAMDConstantForces",
                     func_usage_additions,
                     func_get_args,
                     func_free_args);
    }
}
#endif /* KHOROS */ 
