#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "../inc/config.h"
#include "genUtil.h"
#include "String.h"
#include "File.h"
#include "Memory.h"


void
init0(mrcImageClusterAnalysisPVMInfo* info)
{
    info->fptIn = stdin;    info->flagIn = 0;
    info->fptOut = stdout;    info->flagOut = 0;
    info->Output=0;
    info->N = 1;    info->flagN = 0;
    info->Iteration=0;
    info->AutoRotation = 72;    info->flagAutoRotation = 0;
    info->AutoRotationIteration = 2;    info->flagAutoRotationIteration = 0;
    info->AutoRotationMethod = 0;    info->flagAutoRotationMethod = 0;
    info->fptconfigFile = NULL;    info->flagconfigFile = 0;
    info->Mirrorimage=0;
    info->correlationMode = 0x00;    info->flagcorrelationMode = 0;
    info->Maxprocess = 8;    info->flagMaxprocess = 0;
    info->mode = 2;    info->flagmode = 0;
}

void
init1(mrcImageClusterAnalysisPVMInfo* info)
{
    char s[1024];
    int i;
    if(!info->flagIn) {
        stringGetFromFile(s, "In", stdin, stdout, 0);
        info->In = stringGetNthWord(s, 1, " ,");
        info->flagIn++;
    }
    if(info->flagIn) {
        info->fptIn = fileOpen(info->In, "r");
    }
    
    if(info->flagOut) {
        info->fptOut = fileOpen(info->Out, "w");
    }
    
    if(info->flagN) {
    }
    
    if(info->flagAutoRotation) {
    }
    
    if(info->flagAutoRotationIteration) {
    }
    
    if(info->flagAutoRotationMethod) {
    }
    
    if(info->flagconfigFile) {
        info->fptconfigFile = fileOpen(info->configFile, "r");
    }
    
    if(info->flagcorrelationMode) {
    }
    
    if(info->flagMaxprocess) {
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
    sprintf(panepath, "%s/src/Tools/mrcImage/mrcImageClusterAnalysisPVM/src/mrcImageClusterAnalysisPVM.pane", eospath);
    khoros_initialize(argc, argv, "EOS");
    fpt = fopen(panepath, "r");    if(NULL!=fpt) {
        fclose(fpt);
        kclui_initialize(panepath, KGEN_NONE, "EOS", "mrcImageClusterAnalysisPVM",
                     func_usage_additions,
                     func_get_args,
                     func_free_args);
    }
}
#endif /* KHOROS */ 
