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
init0(mrcImageCoreImageCalcInfo* info)
{
    info->fptIn = NULL;    info->flagIn = 0;
    info->EL = 180;    info->flagEL = 0;
    info->fptBG     = NULL;    info->fptBGList = NULL;    info->flagBG = 0;
    info->fptOut = NULL;    info->flagOut = 0;
    info->fptOutBG = NULL;    info->flagOutBG = 0;
    info->fptOutChi = NULL;    info->flagOutChi = 0;
    info->A1 = 5040;    info->flagA1 = 0;
    info->A2 = 500;    info->flagA2 = 0;
    info->A3 = -12;    info->flagA3 = 0;
    info->LimitA3Min = -16;    info->flagLimitA3Min = 0;
    info->LimitA3Max = -5;    info->flagLimitA3Max = 0;
    info->BaseEELS = 160.0;    info->flagBaseEELS = 0;
    info->fptconfigFile = NULL;    info->flagconfigFile = 0;
    info->mode = 0;    info->flagmode = 0;
}

void
init1(mrcImageCoreImageCalcInfo* info)
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
    
    if(!info->flagEL) {
        stringGetFromFile(s, "EL", stdin, stdout, 0);
        info->EL = stringGetNthRealData(s, 1, ", \t");
        info->flagEL++;
    }
    if(info->flagEL) {
    }
    
    if(!info->flagBG) {
        stringGetFromFile(s, "BG", stdin, stdout, 0);
        info->BGList = stringGetNthWord(s, 1, " ,\t");
        info->flagBG++;
    }
    if(info->flagBG) {
        info->fptBGList = fileOpen(info->BGList, "r");
        fseek(info->fptBGList, 0L, SEEK_SET);
        i=0;
        while(NULL!=stringGetFromFile(s, "", info->fptBGList, stdout, 1)) {
            i++;
        }
        info->fptBG = (FILE**)memoryAllocate(i*sizeof(FILE*), "in init1");
        info->BG    = (char**)memoryAllocate(i*sizeof(char*), "in init1");
        info->flagBG = i;
        fseek(info->fptBGList, 0L, SEEK_SET);
        i=0;
        while(NULL!=stringGetFromFile(s, "", info->fptBGList, stdout, 1)) {
            info->BG[i] = stringGetNthWord(s, 1, " ,\t");
            info->fptBG[i] = fileOpen(info->BG[i],"r");
            i++;
        }
    }
    
    if(!info->flagOut) {
        stringGetFromFile(s, "Out", stdin, stdout, 0);
        info->Out = stringGetNthWord(s, 1, " ,\t");
        info->flagOut++;
    }
    if(info->flagOut) {
        info->fptOut = fileOpen(info->Out, "w");
    }
    
    if(info->flagOutBG) {
        info->fptOutBG = fileOpen(info->OutBG, "w");
    }
    
    if(info->flagOutChi) {
        info->fptOutChi = fileOpen(info->OutChi, "w");
    }
    
    if(info->flagA1) {
    }
    
    if(info->flagA2) {
    }
    
    if(info->flagA3) {
    }
    
    if(info->flagLimitA3Min) {
    }
    
    if(info->flagLimitA3Max) {
    }
    
    if(info->flagBaseEELS) {
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
    sprintf(panepath, "%s/src/Tools/mrcImage/mrcImageCoreImageCalc/src/mrcImageCoreImageCalc.pane", eospath);
    khoros_initialize(argc, argv, "EOS");
    fpt = fopen(panepath, "r");    if(NULL!=fpt) {
        fclose(fpt);
        kclui_initialize(panepath, KGEN_NONE, "EOS", "mrcImageCoreImageCalc",
                     func_usage_additions,
                     func_get_args,
                     func_free_args);
    }
}
#endif /* KHOROS */ 
