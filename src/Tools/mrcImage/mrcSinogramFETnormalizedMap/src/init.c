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
init0(mrcSinogramFETnormalizedMapInfo* info)
{
    info->fptIn = NULL;    info->flagIn = 0;
    info->fptOutFET = NULL;    info->flagOutFET = 0;
    info->fptcomList = NULL;    info->flagcomList = 0;
    info->fptOutMAP = NULL;    info->flagOutMAP = 0;
    info->fptWeight = NULL;    info->flagWeight = 0;
    info->AAtm = 1;    info->flagAAtm = 0;
    info->fptconfigFile = NULL;    info->flagconfigFile = 0;
    info->mode = 0;    info->flagmode = 0;
}

void
init1(mrcSinogramFETnormalizedMapInfo* info)
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
    
    if(!info->flagOutFET) {
        stringGetFromFile(s, "OutFET", stdin, stdout, 0);
        info->OutFET = stringGetNthWord(s, 1, " ,\t");
        info->flagOutFET++;
    }
    if(info->flagOutFET) {
        info->fptOutFET = fileOpen(info->OutFET, "w");
    }
    
    if(info->flagcomList) {
        info->fptcomList = fileOpen(info->comList, "r");
    }
    
    if(info->flagOutMAP) {
        info->fptOutMAP = fileOpen(info->OutMAP, "w");
    }
    
    if(info->flagWeight) {
        info->fptWeight = fileOpen(info->Weight, "r");
    }
    
    if(info->flagAAtm) {
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
    sprintf(panepath, "%s/src/Tools/mrcImage/mrcSinogramFETnormalizedMap/src/mrcSinogramFETnormalizedMap.pane", eospath);
    khoros_initialize(argc, argv, "EOS");
    fpt = fopen(panepath, "r");    if(NULL!=fpt) {
        fclose(fpt);
        kclui_initialize(panepath, KGEN_NONE, "EOS", "mrcSinogramFETnormalizedMap",
                     func_usage_additions,
                     func_get_args,
                     func_free_args);
    }
}
#endif /* KHOROS */ 
