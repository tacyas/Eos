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
init0(mrcImageFOMCalcInfo* info)
{
    info->fptIn = NULL;    info->flagIn = 0;
    info->Weight = 1.0;    info->flagWeight = 0;
    info->fptInList     = NULL;    info->fptInListList = NULL;    info->flagInList = 0;
    info->fptRef = NULL;    info->flagRef = 0;
    info->fptOut = stdout;    info->flagOut = 0;
    info->Rmin = 0.0;    info->flagRmin = 0;
    info->Rmax = 0.1;    info->flagRmax = 0;
    info->dR = 0.0;    info->flagdR = 0;
    info->nSector = 1;    info->flagnSector = 0;
    info->dAlpha = 5;    info->flagdAlpha = 0;
    info->XMax = 0.0;    info->flagXMax = 0;
    info->AutoScale=0;
    info->AASRMax = 0.05;    info->flagAASRMax = 0;
    info->RScale=0;
    info->fptconfigFile = NULL;    info->flagconfigFile = 0;
    info->mode = 0;    info->flagmode = 0;
}

void
init1(mrcImageFOMCalcInfo* info)
{
    char s[1024];
    int i;
    if(info->flagIn) {
        info->fptIn = fileOpen(info->In, "r");
    }
    
    if(info->flagWeight) {
    }
    
    if(info->flagInList) {
        info->fptInListList = fileOpen(info->InListList, "r");
        fseek(info->fptInListList, 0L, SEEK_SET);
        i=0;
        while(NULL!=stringGetFromFile(s, "", info->fptInListList, stdout, 1)) {
            i++;
        }
        info->fptInList = (FILE**)memoryAllocate(i*sizeof(FILE*), "in init1");
        info->InList    = (char**)memoryAllocate(i*sizeof(char*), "in init1");
        info->flagInList = i;
        fseek(info->fptInListList, 0L, SEEK_SET);
        i=0;
        while(NULL!=stringGetFromFile(s, "", info->fptInListList, stdout, 1)) {
            info->InList[i] = stringGetNthWord(s, 1, " ,\t");
            info->fptInList[i] = fileOpen(info->InList[i],"r");
            i++;
        }
    }
    
    if(!info->flagRef) {
        stringGetFromFile(s, "Ref", stdin, stdout, 0);
        info->Ref = stringGetNthWord(s, 1, " ,\t");
        info->flagRef++;
    }
    if(info->flagRef) {
        info->fptRef = fileOpen(info->Ref, "r");
    }
    
    if(info->flagOut) {
        info->fptOut = fileOpen(info->Out, "w");
    }
    
    if(info->flagRmin) {
    }
    
    if(info->flagRmax) {
    }
    
    if(info->flagdR) {
    }
    
    if(info->flagnSector) {
    }
    
    if(info->flagdAlpha) {
    }
    
    if(info->flagXMax) {
    }
    
    if(info->flagAASRMax) {
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
    sprintf(panepath, "%s/src/Tools/mrcImage/mrcImageFOMCalc/src/mrcImageFOMCalc.pane", eospath);
    khoros_initialize(argc, argv, "EOS");
    fpt = fopen(panepath, "r");    if(NULL!=fpt) {
        fclose(fpt);
        kclui_initialize(panepath, KGEN_NONE, "EOS", "mrcImageFOMCalc",
                     func_usage_additions,
                     func_get_args,
                     func_free_args);
    }
}
#endif /* KHOROS */ 
