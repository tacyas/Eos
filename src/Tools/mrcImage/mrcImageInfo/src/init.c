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
init0(mrcImageInfoInfo* info)
{
    info->fptIn = NULL;    info->flagIn = 0;
    info->fptOut = stdout;    info->flagOut = 0;
    info->X = 0.0;    info->flagX = 0;
    info->Y = 0.0;    info->flagY = 0;
    info->xProjection=0;
    info->yProjection=0;
    info->Length=0;
    info->H = 256;    info->flagH = 0;
    info->H2 = 1;    info->flagH2 = 0;
    info->H3 = 256;    info->flagH3 = 0;
    info->H4 = 1;    info->flagH4 = 0;
    info->H5 = 1;    info->flagH5 = 0;
    info->H6 = 1;    info->flagH6 = 0;
    info->Low = 1;    info->flagLow = 0;
    info->High = 1;    info->flagHigh = 0;
    info->Thres = 0.5;    info->flagThres = 0;
    info->Info=0;
    info->fptconfigFile = NULL;    info->flagconfigFile = 0;
    info->rmax = 250;    info->flagrmax = 0;
    info->mode = 0;    info->flagmode = 0;
}

void
init1(mrcImageInfoInfo* info)
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
    
    if(info->flagX) {
    }
    
    if(info->flagY) {
    }
    
    if(info->flagH) {
    }
    
    if(info->flagH2) {
    }
    
    if(info->flagH3) {
    }
    
    if(info->flagH4) {
    }
    
    if(info->flagH5) {
    }
    
    if(info->flagH6) {
    }
    
    if(info->flagLow) {
    }
    
    if(info->flagHigh) {
    }
    
    if(info->flagThres) {
    }
    
    if(info->flagconfigFile) {
        info->fptconfigFile = fileOpen(info->configFile, "r");
    }
    
    if(info->flagrmax) {
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
    sprintf(panepath, "%s/src/Tools/mrcImage/mrcImageInfo/src/mrcImageInfo.pane", eospath);
    khoros_initialize(argc, argv, "EOS");
    fpt = fopen(panepath, "r");    if(NULL!=fpt) {
        fclose(fpt);
        kclui_initialize(panepath, KGEN_NONE, "EOS", "mrcImageInfo",
                     func_usage_additions,
                     func_get_args,
                     func_free_args);
    }
}
#endif /* KHOROS */ 
