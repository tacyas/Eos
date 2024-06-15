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
init0(mrcImageVolumeCalcInfo* info)
{
    info->fptIn = NULL;    info->flagIn = 0;
    info->fptOut = stdout;    info->flagOut = 0;
    info->nMolecule = 1.0;    info->flagnMolecule = 0;
    info->MolecularWeight = 1.0;    info->flagMolecularWeight = 0;
    info->Density = 1.35;    info->flagDensity = 0;
    info->Delta = 5.0;    info->flagDelta = 0;
    info->MinVol = 0.0;    info->flagMinVol = 0;
    info->MaxVol = 200.0;    info->flagMaxVol = 0;
    info->DeltaVol = 10.0;    info->flagDeltaVol = 0;
    info->Inverse=0;
    info->Format = strdup("ContourLevel(%3g): %g %lu");    info->flagFormat = 0;
    info->fptconfigFile = NULL;    info->flagconfigFile = 0;
    info->mode = 0;    info->flagmode = 0;
}

void
init1(mrcImageVolumeCalcInfo* info)
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
    
    if(info->flagnMolecule) {
    }
    
    if(info->flagMolecularWeight) {
    }
    
    if(info->flagDensity) {
    }
    
    if(info->flagDelta) {
    }
    
    if(info->flagMinVol) {
    }
    
    if(info->flagMaxVol) {
    }
    
    if(info->flagDeltaVol) {
    }
    
    if(info->flagFormat) {
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
    sprintf(panepath, "%s/src/Tools/mrcImage/mrcImageVolumeCalc/src/mrcImageVolumeCalc.pane", eospath);
    khoros_initialize(argc, argv, "EOS");
    fpt = fopen(panepath, "r");    if(NULL!=fpt) {
        fclose(fpt);
        kclui_initialize(panepath, KGEN_NONE, "EOS", "mrcImageVolumeCalc",
                     func_usage_additions,
                     func_get_args,
                     func_free_args);
    }
}
#endif /* KHOROS */ 
