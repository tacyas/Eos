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
init0(crystalGetLatticeVolumeInfo* info)
{
    info->fptIn = stdin;    info->flagIn = 0;
    info->ax = 2;    info->flagax = 0;
    info->ay = 3;    info->flagay = 0;
    info->az = 0;    info->flagaz = 0;
    info->bx = 2;    info->flagbx = 0;
    info->by = 3;    info->flagby = 0;
    info->bz = 0;    info->flagbz = 0;
    info->cx = 2;    info->flagcx = 0;
    info->cy = 3;    info->flagcy = 0;
    info->cz = 1;    info->flagcz = 0;
    info->fptOut = stdout;    info->flagOut = 0;
    info->fptconfigFile = NULL;    info->flagconfigFile = 0;
    info->mode = 0;    info->flagmode = 0;
}

void
init1(crystalGetLatticeVolumeInfo* info)
{
    char s[1024];
    int i;
    if(info->flagIn) {
        info->fptIn = fileOpen(info->In, "r");
    }
    
    if(info->flagax) {
    }
    
    if(info->flagay) {
    }
    
    if(info->flagaz) {
    }
    
    if(info->flagbx) {
    }
    
    if(info->flagby) {
    }
    
    if(info->flagbz) {
    }
    
    if(info->flagcx) {
    }
    
    if(info->flagcy) {
    }
    
    if(info->flagcz) {
    }
    
    if(info->flagOut) {
        info->fptOut = fileOpen(info->Out, "w");
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
    sprintf(panepath, "%s/src/Tools/Crystal/crystalGetLatticeVolume/src/crystalGetLatticeVolume.pane", eospath);
    khoros_initialize(argc, argv, "EOS");
    fpt = fopen(panepath, "r");    if(NULL!=fpt) {
        fclose(fpt);
        kclui_initialize(panepath, KGEN_NONE, "EOS", "crystalGetLatticeVolume",
                     func_usage_additions,
                     func_get_args,
                     func_free_args);
    }
}
#endif /* KHOROS */ 
