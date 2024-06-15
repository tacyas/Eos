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
init0(mrcImageFourierShellCorrelationInfo* info)
{
    info->fptIn1 = NULL;    info->flagIn1 = 0;
    info->fptIn2 = NULL;    info->flagIn2 = 0;
    info->fptOut = stdout;    info->flagOut = 0;
    info->SNR=0;
    info->FSCfull=0;
    info->Cref=0;
    info->Brestore = -1000;    info->flagBrestore = 0;
    info->delta = 0;    info->flagdelta = 0;
    info->z = 0;    info->flagz = 0;
    info->L = 0;    info->flagL = 0;
    info->H = 0;    info->flagH = 0;
    info->fptconfigFile = NULL;    info->flagconfigFile = 0;
    info->mode = 0;    info->flagmode = 0;
    info->mode2 = 0;    info->flagmode2 = 0;
    info->fptIn1Array     = stdin;    info->fptIn1ArrayList = stdin;    info->flagIn1Array = 0;
}

void
init1(mrcImageFourierShellCorrelationInfo* info)
{
    char s[1024];
    int i;
    if(info->flagIn1) {
        info->fptIn1 = fileOpen(info->In1, "r");
    }
    
    if(info->flagIn2) {
        info->fptIn2 = fileOpen(info->In2, "r");
    }
    
    if(info->flagOut) {
        info->fptOut = fileOpen(info->Out, "w");
    }
    
    if(info->flagBrestore) {
    }
    
    if(info->flagdelta) {
    }
    
    if(info->flagz) {
    }
    
    if(info->flagL) {
    }
    
    if(info->flagH) {
    }
    
    if(info->flagconfigFile) {
        info->fptconfigFile = fileOpen(info->configFile, "r");
    }
    
    if(info->flagmode) {
    }
    
    if(info->flagmode2) {
    }
    
    if(info->flagIn1Array) {
        info->fptIn1ArrayList = fileOpen(info->In1ArrayList, "r");
        fseek(info->fptIn1ArrayList, 0L, SEEK_SET);
        i=0;
        while(NULL!=stringGetFromFile(s, "", info->fptIn1ArrayList, stdout, 1)) {
            i++;
        }
        info->fptIn1Array = (FILE**)memoryAllocate(i*sizeof(FILE*), "in init1");
        info->In1Array    = (char**)memoryAllocate(i*sizeof(char*), "in init1");
        info->flagIn1Array = i;
        fseek(info->fptIn1ArrayList, 0L, SEEK_SET);
        i=0;
        while(NULL!=stringGetFromFile(s, "", info->fptIn1ArrayList, stdout, 1)) {
            info->In1Array[i] = stringGetNthWord(s, 1, " ,\t");
            info->fptIn1Array[i] = fileOpen(info->In1Array[i],"r");
            i++;
        }
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
    sprintf(panepath, "%s/src/Tools/mrcImage/mrcImageFourierShellCorrelation/src/mrcImageFourierShellCorrelation.pane", eospath);
    khoros_initialize(argc, argv, "EOS");
    fpt = fopen(panepath, "r");    if(NULL!=fpt) {
        fclose(fpt);
        kclui_initialize(panepath, KGEN_NONE, "EOS", "mrcImageFourierShellCorrelation",
                     func_usage_additions,
                     func_get_args,
                     func_free_args);
    }
}
#endif /* KHOROS */ 
