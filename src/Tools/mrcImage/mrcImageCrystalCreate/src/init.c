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
init0(mrcImageCrystalCreateInfo* info)
{
    info->fptIn = NULL;    info->flagIn = 0;
    info->fptOut = NULL;    info->flagOut = 0;
    info->nx = 1;    info->flagnx = 0;
    info->ny = 1;    info->flagny = 0;
    info->nz = 1;    info->flagnz = 0;
    info->StartX = 0.0;    info->flagStartX = 0;
    info->StartY = 0.0;    info->flagStartY = 0;
    info->StartZ = 0.0;    info->flagStartZ = 0;
    info->AX = 1.0;    info->flagAX = 0;
    info->AY = 0.0;    info->flagAY = 0;
    info->AZ = 0.0;    info->flagAZ = 0;
    info->BX = 0.0;    info->flagBX = 0;
    info->BY = 1.0;    info->flagBY = 0;
    info->BZ = 0.0;    info->flagBZ = 0;
    info->CX = 0.0;    info->flagCX = 0;
    info->CY = 0.0;    info->flagCY = 0;
    info->CZ = 1.0;    info->flagCZ = 0;
    info->Mode = 0;    info->flagMode = 0;
    info->fptconfigFile = NULL;    info->flagconfigFile = 0;
    info->mode = 0;    info->flagmode = 0;
}

void
init1(mrcImageCrystalCreateInfo* info)
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
    
    if(info->flagnx) {
    }
    
    if(info->flagny) {
    }
    
    if(info->flagnz) {
    }
    
    if(info->flagStartX) {
    }
    
    if(info->flagStartY) {
    }
    
    if(info->flagStartZ) {
    }
    
    if(info->flagAX) {
    }
    
    if(info->flagAY) {
    }
    
    if(info->flagAZ) {
    }
    
    if(info->flagBX) {
    }
    
    if(info->flagBY) {
    }
    
    if(info->flagBZ) {
    }
    
    if(info->flagCX) {
    }
    
    if(info->flagCY) {
    }
    
    if(info->flagCZ) {
    }
    
    if(info->flagMode) {
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
    sprintf(panepath, "%s/src/Tools/mrcImage/mrcImageCrystalCreate/src/mrcImageCrystalCreate.pane", eospath);
    khoros_initialize(argc, argv, "EOS");
    fpt = fopen(panepath, "r");    if(NULL!=fpt) {
        fclose(fpt);
        kclui_initialize(panepath, KGEN_NONE, "EOS", "mrcImageCrystalCreate",
                     func_usage_additions,
                     func_get_args,
                     func_free_args);
    }
}
#endif /* KHOROS */ 
