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
init0(mrcImageModelCreateInfo* info)
{
    info->fptOut = NULL;    info->flagOut = 0;
    info->fptIn = NULL;    info->flagIn = 0;
    info->nx = 70;    info->flagnx = 0;
    info->ny = 70;    info->flagny = 0;
    info->nz = 100;    info->flagnz = 0;
    info->r = 1;    info->flagr = 0;
    info->l = 1;    info->flagl = 0;
    info->lx = 5.0;    info->flaglx = 0;
    info->ly = 5.0;    info->flagly = 0;
    info->lz = 5.0;    info->flaglz = 0;
    info->radius = 150;    info->flagradius = 0;
    info->nHelix = 3;    info->flagnHelix = 0;
    info->zPitch = 143;    info->flagzPitch = 0;
    info->deltaPhi = 40;    info->flagdeltaPhi = 0;
    info->phiAngle = 120;    info->flagphiAngle = 0;
    info->startZ = 0;    info->flagstartZ = 0;
    info->endZ = 500;    info->flagendZ = 0;
    info->startPhi = 0;    info->flagstartPhi = 0;
    info->startPhi2 = 40;    info->flagstartPhi2 = 0;
    info->inMode = 0;    info->flaginMode = 0;
    info->units = 9;    info->flagunits = 0;
    info->fm = 0;    info->flagfm = 0;
    info->min = 0;    info->flagmin = 0;
    info->max = 10;    info->flagmax = 0;
    info->fptconfigFile = NULL;    info->flagconfigFile = 0;
    info->mode = 0;    info->flagmode = 0;
}

void
init1(mrcImageModelCreateInfo* info)
{
    char s[1024];
    int i;
    if(!info->flagOut) {
        stringGetFromFile(s, "Out", stdin, stdout, 0);
        info->Out = stringGetNthWord(s, 1, " ,\t");
        info->flagOut++;
    }
    if(info->flagOut) {
        info->fptOut = fileOpen(info->Out, "w");
    }
    
    if(info->flagIn) {
        info->fptIn = fileOpen(info->In, "r");
    }
    
    if(info->flagnx) {
    }
    
    if(info->flagny) {
    }
    
    if(info->flagnz) {
    }
    
    if(info->flagr) {
    }
    
    if(info->flagl) {
    }
    
    if(info->flaglx) {
    }
    
    if(info->flagly) {
    }
    
    if(info->flaglz) {
    }
    
    if(info->flagradius) {
    }
    
    if(info->flagnHelix) {
    }
    
    if(info->flagzPitch) {
    }
    
    if(info->flagdeltaPhi) {
    }
    
    if(info->flagphiAngle) {
    }
    
    if(info->flagstartZ) {
    }
    
    if(info->flagendZ) {
    }
    
    if(info->flagstartPhi) {
    }
    
    if(info->flagstartPhi2) {
    }
    
    if(info->flaginMode) {
    }
    
    if(info->flagunits) {
    }
    
    if(info->flagfm) {
    }
    
    if(info->flagmin) {
    }
    
    if(info->flagmax) {
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
    sprintf(panepath, "%s/src/Tools/mrcImage/mrcImageModelCreate/src/mrcImageModelCreate.pane", eospath);
    khoros_initialize(argc, argv, "EOS");
    fpt = fopen(panepath, "r");    if(NULL!=fpt) {
        fclose(fpt);
        kclui_initialize(panepath, KGEN_NONE, "EOS", "mrcImageModelCreate",
                     func_usage_additions,
                     func_get_args,
                     func_free_args);
    }
}
#endif /* KHOROS */ 
