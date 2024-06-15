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
init0(pdb2mrc2dWithCTFInfo* info)
{
    info->fptIn = NULL;    info->flagIn = 0;
    info->fptOut = NULL;    info->flagOut = 0;
    info->Nx = 2048;    info->flagNx = 0;
    info->Ny = 2048;    info->flagNy = 0;
    info->dx = 1.72;    info->flagdx = 0;
    info->dy = 1.72;    info->flagdy = 0;
    info->cx = 0;    info->flagcx = 0;
    info->cy = 0;    info->flagcy = 0;
    info->cz = 0;    info->flagcz = 0;
    info->nx = 64;    info->flagnx = 0;
    info->ny = 64;    info->flagny = 0;
    info->kV = 200.;    info->flagkV = 0;
    info->Cs = 1.7;    info->flagCs = 0;
    info->Defocus = 10000;    info->flagDefocus = 0;
    info->AoverP = 0.07;    info->flagAoverP = 0;
    info->Ain = 0.2;    info->flagAin = 0;
    info->ctfMode = 33;    info->flagctfMode = 0;
    info->EulerAngle = stringGetNthWord("XEYS", 1, "\0");    info->flagEulerAngle = 0;
    info->Rot1 = 0;    info->flagRot1 = 0;
    info->Rot2 = 0;    info->flagRot2 = 0;
    info->Rot3 = 0;    info->flagRot3 = 0;
    info->fptconfigFile = NULL;    info->flagconfigFile = 0;
    info->mode = 0;    info->flagmode = 0;
}

void
init1(pdb2mrc2dWithCTFInfo* info)
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
    
    if(info->flagNx) {
    }
    
    if(info->flagNy) {
    }
    
    if(info->flagdx) {
    }
    
    if(info->flagdy) {
    }
    
    if(info->flagcx) {
    }
    
    if(info->flagcy) {
    }
    
    if(info->flagcz) {
    }
    
    if(info->flagnx) {
    }
    
    if(info->flagny) {
    }
    
    if(info->flagkV) {
    }
    
    if(info->flagCs) {
    }
    
    if(info->flagDefocus) {
    }
    
    if(info->flagAoverP) {
    }
    
    if(info->flagAin) {
    }
    
    if(info->flagctfMode) {
    }
    
    if(info->flagEulerAngle) {
    }
    
    if(info->flagRot1) {
    }
    
    if(info->flagRot2) {
    }
    
    if(info->flagRot3) {
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
    sprintf(panepath, "%s/src/Tools/pdbUtil/pdb2mrc2dWithCTF/src/pdb2mrc2dWithCTF.pane", eospath);
    khoros_initialize(argc, argv, "EOS");
    fpt = fopen(panepath, "r");    if(NULL!=fpt) {
        fclose(fpt);
        kclui_initialize(panepath, KGEN_NONE, "EOS", "pdb2mrc2dWithCTF",
                     func_usage_additions,
                     func_get_args,
                     func_free_args);
    }
}
#endif /* KHOROS */ 
