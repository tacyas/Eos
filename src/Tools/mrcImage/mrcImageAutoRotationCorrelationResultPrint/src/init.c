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
init0(mrcImageAutoRotationCorrelationResultPrintInfo* info)
{
    info->fptIn = NULL;    info->flagIn = 0;
    info->fptInData = NULL;    info->flagInData = 0;
    info->fptRef = NULL;    info->flagRef = 0;
    info->fptPDB = NULL;    info->flagPDB = 0;
    info->fptOut = stdout;    info->flagOut = 0;
    info->fptMax = NULL;    info->flagMax = 0;
    info->fptMaxRot = NULL;    info->flagMaxRot = 0;
    info->fptMaxPDB = NULL;    info->flagMaxPDB = 0;
    info->fptMaxPDBForRasmol = NULL;    info->flagMaxPDBForRasmol = 0;
    info->Sx = 0.0;    info->flagSx = 0;
    info->Sy = 0.0;    info->flagSy = 0;
    info->Sz = 0.0;    info->flagSz = 0;
    info->Top = 1;    info->flagTop = 0;
    info->wish=0;
    info->fptconfigFile = NULL;    info->flagconfigFile = 0;
    info->mode = 0;    info->flagmode = 0;
}

void
init1(mrcImageAutoRotationCorrelationResultPrintInfo* info)
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
    
    if(info->flagInData) {
        info->fptInData = fileOpen(info->InData, "r");
    }
    
    if(!info->flagRef) {
        stringGetFromFile(s, "Ref", stdin, stdout, 0);
        info->Ref = stringGetNthWord(s, 1, " ,\t");
        info->flagRef++;
    }
    if(info->flagRef) {
        info->fptRef = fileOpen(info->Ref, "r");
    }
    
    if(info->flagPDB) {
        info->fptPDB = fileOpen(info->PDB, "r");
    }
    
    if(info->flagOut) {
        info->fptOut = fileOpen(info->Out, "w");
    }
    
    if(info->flagMax) {
        info->fptMax = fileOpen(info->Max, "w");
    }
    
    if(info->flagMaxRot) {
        info->fptMaxRot = fileOpen(info->MaxRot, "w");
    }
    
    if(info->flagMaxPDB) {
        info->fptMaxPDB = fileOpen(info->MaxPDB, "w");
    }
    
    if(info->flagMaxPDBForRasmol) {
        info->fptMaxPDBForRasmol = fileOpen(info->MaxPDBForRasmol, "w");
    }
    
    if(info->flagSx) {
    }
    
    if(info->flagSy) {
    }
    
    if(info->flagSz) {
    }
    
    if(info->flagTop) {
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
    sprintf(panepath, "%s/src/Tools/mrcImage/mrcImageAutoRotationCorrelationResultPrint/src/mrcImageAutoRotationCorrelationResultPrint.pane", eospath);
    khoros_initialize(argc, argv, "EOS");
    fpt = fopen(panepath, "r");    if(NULL!=fpt) {
        fclose(fpt);
        kclui_initialize(panepath, KGEN_NONE, "EOS", "mrcImageAutoRotationCorrelationResultPrint",
                     func_usage_additions,
                     func_get_args,
                     func_free_args);
    }
}
#endif /* KHOROS */ 
