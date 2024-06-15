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
init0(mrcImageSinogramCorrelationInfo* info)
{
    info->fptIn = NULL;    info->flagIn = 0;
    info->fptRef = NULL;    info->flagRef = 0;
    info->fptOut = NULL;    info->flagOut = 0;
    info->w0th = 1.0;    info->flagw0th = 0;
    info->w1st = 0.0;    info->flagw1st = 0;
    info->w2nd = 0.0;    info->flagw2nd = 0;
    info->threshold = 0.0;    info->flagthreshold = 0;
    info->corMode = 0;    info->flagcorMode = 0;
    info->LengthMode = 0;    info->flagLengthMode = 0;
    info->LengthThresholdMode = 0;    info->flagLengthThresholdMode = 0;
    info->LengthThresholdRatio = 1.0;    info->flagLengthThresholdRatio = 0;
    info->LCMode = 0;    info->flagLCMode = 0;
    info->LengthCorrelationThreshold = 0.0;    info->flagLengthCorrelationThreshold = 0;
    info->weightLength = 1.0;    info->flagweightLength = 0;
    info->fptconfigFile = NULL;    info->flagconfigFile = 0;
    info->mode = 0;    info->flagmode = 0;
}

void
init1(mrcImageSinogramCorrelationInfo* info)
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
    
    if(!info->flagOut) {
        stringGetFromFile(s, "Out", stdin, stdout, 0);
        info->Out = stringGetNthWord(s, 1, " ,\t");
        info->flagOut++;
    }
    if(info->flagOut) {
        info->fptOut = fileOpen(info->Out, "w");
    }
    
    if(info->flagw0th) {
    }
    
    if(info->flagw1st) {
    }
    
    if(info->flagw2nd) {
    }
    
    if(info->flagthreshold) {
    }
    
    if(info->flagcorMode) {
    }
    
    if(info->flagLengthMode) {
    }
    
    if(info->flagLengthThresholdMode) {
    }
    
    if(info->flagLengthThresholdRatio) {
    }
    
    if(info->flagLCMode) {
    }
    
    if(info->flagLengthCorrelationThreshold) {
    }
    
    if(info->flagweightLength) {
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
    sprintf(panepath, "%s/src/Tools/mrcImage/mrcImageSinogramCorrelation/src/mrcImageSinogramCorrelation.pane", eospath);
    khoros_initialize(argc, argv, "EOS");
    fpt = fopen(panepath, "r");    if(NULL!=fpt) {
        fclose(fpt);
        kclui_initialize(panepath, KGEN_NONE, "EOS", "mrcImageSinogramCorrelation",
                     func_usage_additions,
                     func_get_args,
                     func_free_args);
    }
}
#endif /* KHOROS */ 
