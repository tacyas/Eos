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
init0(mrc2mrcInfo* info)
{
    info->fptIn = NULL;    info->flagIn = 0;
    info->InType = stringGetNthWord("FEIextendedMRC", 1, "\0");    info->flagInType = 0;
    info->fptOut = NULL;    info->flagOut = 0;
    info->OutType = stringGetNthWord("Eos", 1, "\0");    info->flagOutType = 0;
    info->LenX = 1.0;    info->flagLenX = 0;
    info->LenY = 1.0;    info->flagLenY = 0;
    info->LenZ = 1.0;    info->flagLenZ = 0;
    info->Mx = 1;    info->flagMx = 0;
    info->My = 1;    info->flagMy = 0;
    info->Mz = 1;    info->flagMz = 0;
    info->flagStat=0;
    info->fptconfigFile = NULL;    info->flagconfigFile = 0;
    info->mode = 0;    info->flagmode = 0;
}

void
init1(mrc2mrcInfo* info)
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
    
    if(info->flagInType) {
    }
    
    if(!info->flagOut) {
        stringGetFromFile(s, "Out", stdin, stdout, 0);
        info->Out = stringGetNthWord(s, 1, " ,\t");
        info->flagOut++;
    }
    if(info->flagOut) {
        info->fptOut = fileOpen(info->Out, "w");
    }
    
    if(info->flagOutType) {
    }
    
    if(info->flagLenX) {
    }
    
    if(info->flagLenY) {
    }
    
    if(info->flagLenZ) {
    }
    
    if(info->flagMx) {
    }
    
    if(info->flagMy) {
    }
    
    if(info->flagMz) {
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
    sprintf(panepath, "%s/src/Tools/filter/mrc2mrc/src/mrc2mrc.pane", eospath);
    khoros_initialize(argc, argv, "EOS");
    fpt = fopen(panepath, "r");    if(NULL!=fpt) {
        fclose(fpt);
        kclui_initialize(panepath, KGEN_NONE, "EOS", "mrc2mrc",
                     func_usage_additions,
                     func_get_args,
                     func_free_args);
    }
}
#endif /* KHOROS */ 
