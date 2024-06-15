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
init0(mrcImageSpatialFrequencyFilterInfo* info)
{
    info->fptIn = NULL;    info->flagIn = 0;
    info->fptfilterIn = NULL;    info->flagfilterIn = 0;
    info->colR = 1;    info->flagcolR = 0;
    info->colW = 2;    info->flagcolW = 0;
    info->fptOut = NULL;    info->flagOut = 0;
    info->Low = -0.1;    info->flagLow = 0;
    info->High = 1.0;    info->flagHigh = 0;
    info->fptconfigFile = NULL;    info->flagconfigFile = 0;
    info->mode = 0;    info->flagmode = 0;
}

void
init1(mrcImageSpatialFrequencyFilterInfo* info)
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
    
    if(!info->flagfilterIn) {
        stringGetFromFile(s, "filterIn", stdin, stdout, 0);
        info->filterIn = stringGetNthWord(s, 1, " ,\t");
        info->flagfilterIn++;
    }
    if(info->flagfilterIn) {
        info->fptfilterIn = fileOpen(info->filterIn, "r");
    }
    
    if(info->flagcolR) {
    }
    
    if(info->flagcolW) {
    }
    
    if(!info->flagOut) {
        stringGetFromFile(s, "Out", stdin, stdout, 0);
        info->Out = stringGetNthWord(s, 1, " ,\t");
        info->flagOut++;
    }
    if(info->flagOut) {
        info->fptOut = fileOpen(info->Out, "w");
    }
    
    if(info->flagLow) {
    }
    
    if(info->flagHigh) {
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
    sprintf(panepath, "%s/src/Tools/mrcImage/mrcImageSpatialFrequencyFilter/src/mrcImageSpatialFrequencyFilter.pane", eospath);
    khoros_initialize(argc, argv, "EOS");
    fpt = fopen(panepath, "r");    if(NULL!=fpt) {
        fclose(fpt);
        kclui_initialize(panepath, KGEN_NONE, "EOS", "mrcImageSpatialFrequencyFilter",
                     func_usage_additions,
                     func_get_args,
                     func_free_args);
    }
}
#endif /* KHOROS */ 
