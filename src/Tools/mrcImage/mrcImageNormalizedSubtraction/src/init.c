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
init0(mrcImageNormalizedSubtractionInfo* info)
{
    info->fptIn1 = NULL;    info->flagIn1 = 0;
    info->fptIn2 = NULL;    info->flagIn2 = 0;
    info->fptIn2_tmp = NULL;    info->flagIn2_tmp = 0;
    info->fptOut = NULL;    info->flagOut = 0;
    info->fptRMSD = stdout;    info->flagRMSD = 0;
    info->fptParamFile = stdout;    info->flagParamFile = 0;
    info->mode = 0;    info->flagmode = 0;
}

void
init1(mrcImageNormalizedSubtractionInfo* info)
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
    
    if(info->flagIn2_tmp) {
        info->fptIn2_tmp = fileOpen(info->In2_tmp, "w");
    }
    
    if(!info->flagOut) {
        stringGetFromFile(s, "Out", stdin, stdout, 0);
        info->Out = stringGetNthWord(s, 1, " ,\t");
        info->flagOut++;
    }
    if(info->flagOut) {
        info->fptOut = fileOpen(info->Out, "w");
    }
    
    if(info->flagRMSD) {
        info->fptRMSD = fileOpen(info->RMSD, "w");
    }
    
    if(info->flagParamFile) {
        info->fptParamFile = fileOpen(info->ParamFile, "w");
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
    sprintf(panepath, "%s/src/Tools/mrcImage/mrcImageNormalizedSubtraction/src/mrcImageNormalizedSubtraction.pane", eospath);
    khoros_initialize(argc, argv, "EOS");
    fpt = fopen(panepath, "r");    if(NULL!=fpt) {
        fclose(fpt);
        kclui_initialize(panepath, KGEN_NONE, "EOS", "mrcImageNormalizedSubtraction",
                     func_usage_additions,
                     func_get_args,
                     func_free_args);
    }
}
#endif /* KHOROS */ 
