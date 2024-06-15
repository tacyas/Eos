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
init0(vector2pdbInfo* info)
{
    info->vx = 1;    info->flagvx = 0;
    info->vy = 0;    info->flagvy = 0;
    info->vz = 0;    info->flagvz = 0;
    info->phi = 0;    info->flagphi = 0;
    info->theta = 0;    info->flagtheta = 0;
    info->zx = 0;    info->flagzx = 0;
    info->zy = 0;    info->flagzy = 0;
    info->zz = 1;    info->flagzz = 0;
    info->xx = 1;    info->flagxx = 0;
    info->xy = 0;    info->flagxy = 0;
    info->xz = 0;    info->flagxz = 0;
    info->sx = 0;    info->flagsx = 0;
    info->sy = 3;    info->flagsy = 0;
    info->sz = 0;    info->flagsz = 0;
    info->step = 1.6;    info->flagstep = 0;
    info->fptOut = stdout;    info->flagOut = 0;
    info->n = 20;    info->flagn = 0;
    info->ID = 'A';    info->flagID = 0;
    info->Res = stringGetNthWord("GLY", 1, "\0");    info->flagRes = 0;
    info->fptconfigFile = NULL;    info->flagconfigFile = 0;
    info->mode = 0;    info->flagmode = 0;
}

void
init1(vector2pdbInfo* info)
{
    char s[1024];
    int i;
    if(info->flagvx) {
    }
    
    if(info->flagvy) {
    }
    
    if(info->flagvz) {
    }
    
    if(info->flagphi) {
    }
    
    if(info->flagtheta) {
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
    
    if(info->flagsx) {
    }
    
    if(info->flagsy) {
    }
    
    if(info->flagsz) {
    }
    
    if(info->flagstep) {
    }
    
    if(info->flagOut) {
        info->fptOut = fileOpen(info->Out, "w");
    }
    
    if(info->flagn) {
    }
    
    if(info->flagID) {
    }
    
    if(info->flagRes) {
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
    sprintf(panepath, "%s/src/Tools/pdbUtil/vector2pdb/src/vector2pdb.pane", eospath);
    khoros_initialize(argc, argv, "EOS");
    fpt = fopen(panepath, "r");    if(NULL!=fpt) {
        fclose(fpt);
        kclui_initialize(panepath, KGEN_NONE, "EOS", "vector2pdb",
                     func_usage_additions,
                     func_get_args,
                     func_free_args);
    }
}
#endif /* KHOROS */ 
