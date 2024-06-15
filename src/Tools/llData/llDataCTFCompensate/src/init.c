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
init0(llDataCTFCompensateInfo* info)
{
    info->fptIn = NULL;    info->flagIn = 0;
    info->fptIn1 = NULL;    info->flagIn1 = 0;
    info->fptIn2 = NULL;    info->flagIn2 = 0;
    info->fptOut = NULL;    info->flagOut = 0;
    info->truePitch = 430.0;    info->flagtruePitch = 0;
    info->mode = 0;    info->flagmode = 0;
    info->fptconfigFile = NULL;    info->flagconfigFile = 0;
}

void
init1(llDataCTFCompensateInfo* info)
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
    
    if(info->flagIn1) {
        info->fptIn1 = fileOpen(info->In1, "r");
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
    
    if(!info->flagtruePitch) {
        stringGetFromFile(s, "truePitch", stdin, stdout, 0);
        info->truePitch = stringGetNthRealData(s, 1, ", \t");
        info->flagtruePitch++;
    }
    if(info->flagtruePitch) {
    }
    
    if(info->flagmode) {
    }
    
    if(info->flagconfigFile) {
        info->fptconfigFile = fileOpen(info->configFile, "r");
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
    sprintf(panepath, "%s/src/Tools/llData/llDataCTFCompensate/src/llDataCTFCompensate.pane", eospath);
    khoros_initialize(argc, argv, "EOS");
    fpt = fopen(panepath, "r");    if(NULL!=fpt) {
        fclose(fpt);
        kclui_initialize(panepath, KGEN_NONE, "EOS", "llDataCTFCompensate",
                     func_usage_additions,
                     func_get_args,
                     func_free_args);
    }
}
#endif /* KHOROS */ 
