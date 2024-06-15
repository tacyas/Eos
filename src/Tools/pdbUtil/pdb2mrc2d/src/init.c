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
init0(pdb2mrc2dInfo* info)
{
    info->fptIn = NULL;    info->flagIn = 0;
    info->fptOut = NULL;    info->flagOut = 0;
    info->fptOut3D = NULL;    info->flagOut3D = 0;
    info->dx = 5.0;    info->flagdx = 0;
    info->dy = 5.0;    info->flagdy = 0;
    info->sx = 0.0;    info->flagsx = 0;
    info->sy = 0.0;    info->flagsy = 0;
    info->nx = 0;    info->flagnx = 0;
    info->ny = 0;    info->flagny = 0;
    info->rotnx = 1;    info->flagrotnx = 0;
    info->rotny = 1;    info->flagrotny = 0;
    info->srotx = 0.0;    info->flagsrotx = 0;
    info->sroty = 0.0;    info->flagsroty = 0;
    info->srotz = 0.0;    info->flagsrotz = 0;
    info->sRotMode = stringGetNthWord("YOYS", 1, "\0");    info->flagsRotMode = 0;
    info->sRot1 = 0.0;    info->flagsRot1 = 0;
    info->sRot2 = 0.0;    info->flagsRot2 = 0;
    info->sRot3 = 0.0;    info->flagsRot3 = 0;
    info->RotMode = stringGetNthWord("YOYS", 1, "\0");    info->flagRotMode = 0;
    info->dRot1 = 5.0;    info->flagdRot1 = 0;
    info->minRot1 = 0.0;    info->flagminRot1 = 0;
    info->maxRot1 = 180.0;    info->flagmaxRot1 = 0;
    info->dRot2 = 5.0;    info->flagdRot2 = 0;
    info->minRot2 = 0.0;    info->flagminRot2 = 0;
    info->maxRot2 = 180.0;    info->flagmaxRot2 = 0;
    info->Weight = 1.0;    info->flagWeight = 0;
    info->Sigma = 0.0;    info->flagSigma = 0;
    info->fptconfigFile = NULL;    info->flagconfigFile = 0;
    info->cudaDeviceID = 0;    info->flagcudaDeviceID = 0;
    info->mode = 0;    info->flagmode = 0;
}

void
init1(pdb2mrc2dInfo* info)
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
    
    if(info->flagOut3D) {
        info->fptOut3D = fileOpen(info->Out3D, "w");
    }
    
    if(!info->flagdx) {
        stringGetFromFile(s, "dx", stdin, stdout, 0);
        info->dx = stringGetNthRealData(s, 1, ", \t");
        info->flagdx++;
    }
    if(info->flagdx) {
    }
    
    if(!info->flagdy) {
        stringGetFromFile(s, "dy", stdin, stdout, 0);
        info->dy = stringGetNthRealData(s, 1, ", \t");
        info->flagdy++;
    }
    if(info->flagdy) {
    }
    
    if(info->flagsx) {
    }
    
    if(info->flagsy) {
    }
    
    if(!info->flagnx) {
        stringGetFromFile(s, "nx", stdin, stdout, 0);
        info->nx = stringGetNthIntegerData(s, 1, ", \t");
        info->flagnx++;
    }
    if(info->flagnx) {
    }
    
    if(!info->flagny) {
        stringGetFromFile(s, "ny", stdin, stdout, 0);
        info->ny = stringGetNthIntegerData(s, 1, ", \t");
        info->flagny++;
    }
    if(info->flagny) {
    }
    
    if(info->flagrotnx) {
    }
    
    if(info->flagrotny) {
    }
    
    if(info->flagsrotx) {
    }
    
    if(info->flagsroty) {
    }
    
    if(info->flagsrotz) {
    }
    
    if(info->flagsRotMode) {
    }
    
    if(info->flagsRot1) {
    }
    
    if(info->flagsRot2) {
    }
    
    if(info->flagsRot3) {
    }
    
    if(info->flagRotMode) {
    }
    
    if(info->flagdRot1) {
    }
    
    if(info->flagminRot1) {
    }
    
    if(info->flagmaxRot1) {
    }
    
    if(info->flagdRot2) {
    }
    
    if(info->flagminRot2) {
    }
    
    if(info->flagmaxRot2) {
    }
    
    if(info->flagWeight) {
    }
    
    if(info->flagSigma) {
    }
    
    if(info->flagconfigFile) {
        info->fptconfigFile = fileOpen(info->configFile, "r");
    }
    
    if(info->flagcudaDeviceID) {
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
    sprintf(panepath, "%s/src/Tools/pdbUtil/pdb2mrc2d/src/pdb2mrc2d.pane", eospath);
    khoros_initialize(argc, argv, "EOS");
    fpt = fopen(panepath, "r");    if(NULL!=fpt) {
        fclose(fpt);
        kclui_initialize(panepath, KGEN_NONE, "EOS", "pdb2mrc2d",
                     func_usage_additions,
                     func_get_args,
                     func_free_args);
    }
}
#endif /* KHOROS */ 
