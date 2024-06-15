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
init0(llExtractInfo* info)
{
    info->Title = stringGetNthWord("NULL", 1, "\0");    info->flagTitle = 0;
    info->xStep = 1.0;    info->flagxStep = 0;
    info->yStep = 1.0;    info->flagyStep = 0;
    info->MaxX = 1.0;    info->flagMaxX = 0;
    info->MaxY = 1.0;    info->flagMaxY = 0;
    info->fptIn = NULL;    info->flagIn = 0;
    info->fptNea = NULL;    info->flagNea = 0;
    info->fptFar = NULL;    info->flagFar = 0;
    info->RotationAngle = 0.0;    info->flagRotationAngle = 0;
    info->Omega = 0.0;    info->flagOmega = 0;
    info->Shear = 0.0;    info->flagShear = 0;
    info->ievery = 0;    info->flagievery = 0;
    info->axl = 0.0;    info->flagaxl = 0;
    info->ayl = 0.0;    info->flagayl = 0;
    info->xShift = 0.0;    info->flagxShift = 0;
    info->llMax = 0;    info->flagllMax = 0;
    info->delRInv = 0.0;    info->flagdelRInv = 0;
    info->flagOutputInfo=0;
    info->n = NULL;    info->flagn = 0;
    info->l = NULL;    info->flagl = 0;
    info->Y = NULL;    info->flagY = 0;
    info->leftMin = NULL;    info->flagleftMin = 0;
    info->leftMax = NULL;    info->flagleftMax = 0;
    info->rightMin = NULL;    info->flagrightMin = 0;
    info->rightMax = NULL;    info->flagrightMax = 0;
    info->weight = NULL;    info->flagweight = 0;
    info->fptconfigFile = NULL;    info->flagconfigFile = 0;
}

void
init1(llExtractInfo* info)
{
    char s[1024];
    int i;
    if(info->flagTitle) {
    }
    
    if(info->flagxStep) {
    }
    
    if(info->flagyStep) {
    }
    
    if(info->flagMaxX) {
    }
    
    if(info->flagMaxY) {
    }
    
    if(info->flagIn) {
        info->fptIn = fileOpen(info->In, "r");
    }
    
    if(info->flagNea) {
        info->fptNea = fileOpen(info->Nea, "w");
    }
    
    if(info->flagFar) {
        info->fptFar = fileOpen(info->Far, "w");
    }
    
    if(info->flagRotationAngle) {
    }
    
    if(info->flagOmega) {
    }
    
    if(info->flagShear) {
    }
    
    if(info->flagievery) {
    }
    
    if(info->flagaxl) {
    }
    
    if(info->flagayl) {
    }
    
    if(info->flagxShift) {
    }
    
    if(info->flagllMax) {
    }
    
    if(info->flagdelRInv) {
    }
    
    if(info->flagn) {
    }
    
    if(info->flagl) {
    }
    
    if(info->flagY) {
    }
    
    if(info->flagleftMin) {
    }
    
    if(info->flagleftMax) {
    }
    
    if(info->flagrightMin) {
    }
    
    if(info->flagrightMax) {
    }
    
    if(info->flagweight) {
    }
    
    if(info->flagconfigFile) {
        info->fptconfigFile = fileOpen(info->configFile, "r");
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
    sprintf(panepath, "%s/src/Tools/rec3d/llExtract/src/llExtract.pane", eospath);
    khoros_initialize(argc, argv, "EOS");
    fpt = fopen(panepath, "r");    if(NULL!=fpt) {
        fclose(fpt);
        kclui_initialize(panepath, KGEN_NONE, "EOS", "llExtract",
                     func_usage_additions,
                     func_get_args,
                     func_free_args);
    }
}
#endif /* KHOROS */ 
