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
init0(pdb2mrcInfo* info)
{
    info->fptIn = NULL;    info->flagIn = 0;
    info->fptOut = NULL;    info->flagOut = 0;
    info->nx = 1;    info->flagnx = 0;
    info->ny = 1;    info->flagny = 0;
    info->nz = 1;    info->flagnz = 0;
    info->Startx = 0.0;    info->flagStartx = 0;
    info->Starty = 0.0;    info->flagStarty = 0;
    info->Startz = 0.0;    info->flagStartz = 0;
    info->dx = 2.5;    info->flagdx = 0;
    info->dy = 2.5;    info->flagdy = 0;
    info->dz = 2.5;    info->flagdz = 0;
    info->Weight = 1.0;    info->flagWeight = 0;
    info->Sigma = 0.0;    info->flagSigma = 0;
    info->fptconfigFile = NULL;    info->flagconfigFile = 0;
    info->mode = 0;    info->flagmode = 0;
}

void
init1(pdb2mrcInfo* info)
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
    
    if(info->flagOut) {
        info->fptOut = fileOpen(info->Out, "w");
    }
    
    if(info->flagnx) {
    }
    
    if(info->flagny) {
    }
    
    if(info->flagnz) {
    }
    
    if(info->flagStartx) {
    }
    
    if(info->flagStarty) {
    }
    
    if(info->flagStartz) {
    }
    
    if(info->flagdx) {
    }
    
    if(info->flagdy) {
    }
    
    if(info->flagdz) {
    }
    
    if(info->flagWeight) {
    }
    
    if(info->flagSigma) {
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
    sprintf(panepath, "%s/src/Tools/pdbUtil/pdb2mrc/src/pdb2mrc.pane", eospath);
    khoros_initialize(argc, argv, "EOS");
    fpt = fopen(panepath, "r");    if(NULL!=fpt) {
        fclose(fpt);
        kclui_initialize(panepath, KGEN_NONE, "EOS", "pdb2mrc",
                     func_usage_additions,
                     func_get_args,
                     func_free_args);
    }
}
#endif /* KHOROS */ 
