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
init0(mrcSinogramFETcalcSDforNormalizeInfo* info)
{
    info->fptIn = NULL;    info->flagIn = 0;
    info->Sm = 1;    info->flagSm = 0;
    info->fptLibl = NULL;    info->flagLibl = 0;
    info->fptOut = NULL;    info->flagOut = 0;
    info->fptOW = NULL;    info->flagOW = 0;
    info->fptconfigFile = NULL;    info->flagconfigFile = 0;
    info->mode = 0;    info->flagmode = 0;
}

void
init1(mrcSinogramFETcalcSDforNormalizeInfo* info)
{
    char s[1024];
    int i;
    if(info->flagIn) {
        info->fptIn = fileOpen(info->In, "r");
    }
    
    if(info->flagSm) {
    }
    
    if(!info->flagLibl) {
        stringGetFromFile(s, "Libl", stdin, stdout, 0);
        info->Libl = stringGetNthWord(s, 1, " ,\t");
        info->flagLibl++;
    }
    if(info->flagLibl) {
        info->fptLibl = fileOpen(info->Libl, "r");
    }
    
    if(info->flagOut) {
        info->fptOut = fileOpen(info->Out, "w");
    }
    
    if(info->flagOW) {
        info->fptOW = fileOpen(info->OW, "w");
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
    sprintf(panepath, "%s/src/Tools/mrcImage/mrcSinogramFETcalcSDforNormalize/src/mrcSinogramFETcalcSDforNormalize.pane", eospath);
    khoros_initialize(argc, argv, "EOS");
    fpt = fopen(panepath, "r");    if(NULL!=fpt) {
        fclose(fpt);
        kclui_initialize(panepath, KGEN_NONE, "EOS", "mrcSinogramFETcalcSDforNormalize",
                     func_usage_additions,
                     func_get_args,
                     func_free_args);
    }
}
#endif /* KHOROS */ 
