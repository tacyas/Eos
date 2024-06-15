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
init0(mrcImageTransformDescartesIntoPolarInfo* info)
{
    info->fptIn = NULL;    info->flagIn = 0;
    info->fptOut = NULL;    info->flagOut = 0;
    info->dr = 1;    info->flagdr = 0;
    info->dtheta = 1;    info->flagdtheta = 0;
    info->dphi = 1;    info->flagdphi = 0;
    info->zx = 0;    info->flagzx = 0;
    info->zy = 0;    info->flagzy = 0;
    info->zz = 1;    info->flagzz = 0;
    info->xx = 1;    info->flagxx = 0;
    info->xy = 0;    info->flagxy = 0;
    info->xz = 0;    info->flagxz = 0;
    info->cx = 0;    info->flagcx = 0;
    info->cy = 0;    info->flagcy = 0;
    info->cz = 0;    info->flagcz = 0;
    info->rweight=0;
    info->fptconfigFile = NULL;    info->flagconfigFile = 0;
    info->mode = 0;    info->flagmode = 0;
}

void
init1(mrcImageTransformDescartesIntoPolarInfo* info)
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
    
    if(!info->flagOut) {
        stringGetFromFile(s, "Out", stdin, stdout, 0);
        info->Out = stringGetNthWord(s, 1, " ,\t");
        info->flagOut++;
    }
    if(info->flagOut) {
        info->fptOut = fileOpen(info->Out, "w");
    }
    
    if(info->flagdr) {
    }
    
    if(info->flagdtheta) {
    }
    
    if(info->flagdphi) {
    }
    
    if(info->flagzx) {
    }
    
    if(info->flagzy) {
    }
    
    if(info->flagzz) {
    }
    
    if(info->flagxx) {
    }
    
    if(info->flagxy) {
    }
    
    if(info->flagxz) {
    }
    
    if(info->flagcx) {
    }
    
    if(info->flagcy) {
    }
    
    if(info->flagcz) {
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
    sprintf(panepath, "%s/src/Tools/mrcImage/mrcImageTransformDescartesIntoPolar/src/mrcImageTransformDescartesIntoPolar.pane", eospath);
    khoros_initialize(argc, argv, "EOS");
    fpt = fopen(panepath, "r");    if(NULL!=fpt) {
        fclose(fpt);
        kclui_initialize(panepath, KGEN_NONE, "EOS", "mrcImageTransformDescartesIntoPolar",
                     func_usage_additions,
                     func_get_args,
                     func_free_args);
    }
}
#endif /* KHOROS */ 
