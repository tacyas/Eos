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
init0(mrcSinogramFETcorrelationMapInfo* info)
{
    info->fptIn1 = NULL;    info->flagIn1 = 0;
    info->fptIn2 = NULL;    info->flagIn2 = 0;
    info->fptOut = NULL;    info->flagOut = 0;
    info->fptWeight = NULL;    info->flagWeight = 0;
    info->fptSD = NULL;    info->flagSD = 0;
    info->NM = 0;    info->flagNM = 0;
    info->CMode = 0;    info->flagCMode = 0;
    info->fptconfigFile = NULL;    info->flagconfigFile = 0;
    info->mode = 0;    info->flagmode = 0;
}

void
init1(mrcSinogramFETcorrelationMapInfo* info)
{
    char s[1024];
    int i;
    if(!info->flagIn1) {
        stringGetFromFile(s, "In1", stdin, stdout, 0);
        info->In1 = stringGetNthWord(s, 1, " ,\t");
        info->flagIn1++;
    }
    if(info->flagIn1) {
        info->fptIn1 = fileOpen(info->In1, "r");
    }
    
    if(!info->flagIn2) {
        stringGetFromFile(s, "In2", stdin, stdout, 0);
        info->In2 = stringGetNthWord(s, 1, " ,\t");
        info->flagIn2++;
    }
    if(info->flagIn2) {
        info->fptIn2 = fileOpen(info->In2, "r");
    }
    
    if(!info->flagOut) {
        stringGetFromFile(s, "Out", stdin, stdout, 0);
        info->Out = stringGetNthWord(s, 1, " ,\t");
        info->flagOut++;
    }
    if(info->flagOut) {
        info->fptOut = fileOpen(info->Out, "w");
    }
    
    if(info->flagWeight) {
        info->fptWeight = fileOpen(info->Weight, "r");
    }
    
    if(info->flagSD) {
        info->fptSD = fileOpen(info->SD, "r");
    }
    
    if(info->flagNM) {
    }
    
    if(info->flagCMode) {
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
    sprintf(panepath, "%s/src/Tools/mrcImage/mrcSinogramFETcorrelationMap/src/mrcSinogramFETcorrelationMap.pane", eospath);
    khoros_initialize(argc, argv, "EOS");
    fpt = fopen(panepath, "r");    if(NULL!=fpt) {
        fclose(fpt);
        kclui_initialize(panepath, KGEN_NONE, "EOS", "mrcSinogramFETcorrelationMap",
                     func_usage_additions,
                     func_get_args,
                     func_free_args);
    }
}
#endif /* KHOROS */ 
