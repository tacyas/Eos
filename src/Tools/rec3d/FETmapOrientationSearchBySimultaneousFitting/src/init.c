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
init0(FETmapOrientationSearchBySimultaneousFittingInfo* info)
{
    info->fptInML = NULL;    info->flagInML = 0;
    info->fptInNL = NULL;    info->flagInNL = 0;
    info->fptInCL = NULL;    info->flagInCL = 0;
    info->PM = 0;    info->flagPM = 0;
    info->PN = 10;    info->flagPN = 0;
    info->PDT = 0.2;    info->flagPDT = 0;
    info->fptOut = NULL;    info->flagOut = 0;
    info->fptconfigFile = NULL;    info->flagconfigFile = 0;
    info->mode = 0;    info->flagmode = 0;
}

void
init1(FETmapOrientationSearchBySimultaneousFittingInfo* info)
{
    char s[1024];
    int i;
    if(!info->flagInML) {
        stringGetFromFile(s, "InML", stdin, stdout, 0);
        info->InML = stringGetNthWord(s, 1, " ,\t");
        info->flagInML++;
    }
    if(info->flagInML) {
        info->fptInML = fileOpen(info->InML, "r");
    }
    
    if(!info->flagInNL) {
        stringGetFromFile(s, "InNL", stdin, stdout, 0);
        info->InNL = stringGetNthWord(s, 1, " ,\t");
        info->flagInNL++;
    }
    if(info->flagInNL) {
        info->fptInNL = fileOpen(info->InNL, "r");
    }
    
    if(!info->flagInCL) {
        stringGetFromFile(s, "InCL", stdin, stdout, 0);
        info->InCL = stringGetNthWord(s, 1, " ,\t");
        info->flagInCL++;
    }
    if(info->flagInCL) {
        info->fptInCL = fileOpen(info->InCL, "r");
    }
    
    if(info->flagPM) {
    }
    
    if(info->flagPN) {
    }
    
    if(info->flagPDT) {
    }
    
    if(!info->flagOut) {
        stringGetFromFile(s, "Out", stdin, stdout, 0);
        info->Out = stringGetNthWord(s, 1, " ,\t");
        info->flagOut++;
    }
    if(info->flagOut) {
        info->fptOut = fileOpen(info->Out, "w");
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
    sprintf(panepath, "%s/src/Tools/rec3d/FETmapOrientationSearchBySimultaneousFitting/src/FETmapOrientationSearchBySimultaneousFitting.pane", eospath);
    khoros_initialize(argc, argv, "EOS");
    fpt = fopen(panepath, "r");    if(NULL!=fpt) {
        fclose(fpt);
        kclui_initialize(panepath, KGEN_NONE, "EOS", "FETmapOrientationSearchBySimultaneousFitting",
                     func_usage_additions,
                     func_get_args,
                     func_free_args);
    }
}
#endif /* KHOROS */ 
