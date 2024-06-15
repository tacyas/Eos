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
init0(mrcImage1dShiftAverageByAnnealingInfo* info)
{
    info->fptIn = NULL;    info->flagIn = 0;
    info->fptSignal = NULL;    info->flagSignal = 0;
    info->fptOut = NULL;    info->flagOut = 0;
    info->range = 0;    info->flagrange = 0;
    info->delta = 1.0;    info->flagdelta = 0;
    info->temperature = 1.0;    info->flagtemperature = 0;
    info->iter = 1000;    info->flagiter = 0;
    info->eps = 0.001;    info->flageps = 0;
    info->tol = 1e-2;    info->flagtol = 0;
    info->fptconfigFile = NULL;    info->flagconfigFile = 0;
    info->mode = 0;    info->flagmode = 0;
    info->mode2 = 0;    info->flagmode2 = 0;
}

void
init1(mrcImage1dShiftAverageByAnnealingInfo* info)
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
    
    if(!info->flagSignal) {
        stringGetFromFile(s, "Signal", stdin, stdout, 0);
        info->Signal = stringGetNthWord(s, 1, " ,\t");
        info->flagSignal++;
    }
    if(info->flagSignal) {
        info->fptSignal = fileOpen(info->Signal, "r");
    }
    
    if(!info->flagOut) {
        stringGetFromFile(s, "Out", stdin, stdout, 0);
        info->Out = stringGetNthWord(s, 1, " ,\t");
        info->flagOut++;
    }
    if(info->flagOut) {
        info->fptOut = fileOpen(info->Out, "w");
    }
    
    if(info->flagrange) {
    }
    
    if(info->flagdelta) {
    }
    
    if(info->flagtemperature) {
    }
    
    if(info->flagiter) {
    }
    
    if(info->flageps) {
    }
    
    if(info->flagtol) {
    }
    
    if(info->flagconfigFile) {
        info->fptconfigFile = fileOpen(info->configFile, "r");
    }
    
    if(info->flagmode) {
    }
    
    if(info->flagmode2) {
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
    sprintf(panepath, "%s/src/Tools/mrcImage/mrcImage1dShiftAverageByAnnealing/src/mrcImage1dShiftAverageByAnnealing.pane", eospath);
    khoros_initialize(argc, argv, "EOS");
    fpt = fopen(panepath, "r");    if(NULL!=fpt) {
        fclose(fpt);
        kclui_initialize(panepath, KGEN_NONE, "EOS", "mrcImage1dShiftAverageByAnnealing",
                     func_usage_additions,
                     func_get_args,
                     func_free_args);
    }
}
#endif /* KHOROS */ 
