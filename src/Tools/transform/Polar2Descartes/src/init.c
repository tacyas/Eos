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
init0(Polar2DescartesInfo* info)
{
    info->r = 1.0;    info->flagr = 0;
    info->phi = 90.0;    info->flagphi = 0;
    info->theta = 0.0;    info->flagtheta = 0;
    info->fptOut = stdout;    info->flagOut = 0;
    info->cx = 0.0;    info->flagcx = 0;
    info->cy = 0.0;    info->flagcy = 0;
    info->cz = 0.0;    info->flagcz = 0;
    info->xx = 1.0;    info->flagxx = 0;
    info->xy = 0.0;    info->flagxy = 0;
    info->xz = 0.0;    info->flagxz = 0;
    info->zx = 0.0;    info->flagzx = 0;
    info->zy = 0.0;    info->flagzy = 0;
    info->zz = 1.0;    info->flagzz = 0;
    info->fptconfigFile = NULL;    info->flagconfigFile = 0;
    info->mode = 0;    info->flagmode = 0;
}

void
init1(Polar2DescartesInfo* info)
{
    char s[1024];
    int i;
    if(info->flagr) {
    }
    
    if(info->flagphi) {
    }
    
    if(info->flagtheta) {
    }
    
    if(info->flagOut) {
        info->fptOut = fileOpen(info->Out, "w");
    }
    
    if(info->flagcx) {
    }
    
    if(info->flagcy) {
    }
    
    if(info->flagcz) {
    }
    
    if(info->flagxx) {
    }
    
    if(info->flagxy) {
    }
    
    if(info->flagxz) {
    }
    
    if(info->flagzx) {
    }
    
    if(info->flagzy) {
    }
    
    if(info->flagzz) {
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
    sprintf(panepath, "%s/src/Tools/transform/Polar2Descartes/src/Polar2Descartes.pane", eospath);
    khoros_initialize(argc, argv, "EOS");
    fpt = fopen(panepath, "r");    if(NULL!=fpt) {
        fclose(fpt);
        kclui_initialize(panepath, KGEN_NONE, "EOS", "Polar2Descartes",
                     func_usage_additions,
                     func_get_args,
                     func_free_args);
    }
}
#endif /* KHOROS */ 
