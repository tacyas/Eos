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
init0(pdbMoveInfo* info)
{
    info->fptIn = NULL;    info->flagIn = 0;
    info->fptOut = NULL;    info->flagOut = 0;
    info->X = 0.0;    info->flagX = 0;
    info->Y = 0.0;    info->flagY = 0;
    info->Z = 0.0;    info->flagZ = 0;
    info->toX = 0.0;    info->flagtoX = 0;
    info->toY = 0.0;    info->flagtoY = 0;
    info->toZ = 0.0;    info->flagtoZ = 0;
    info->fromX = 0.0;    info->flagfromX = 0;
    info->fromY = 0.0;    info->flagfromY = 0;
    info->fromZ = 0.0;    info->flagfromZ = 0;
    info->GCtoOrigin=0;
    info->fptconfigFile = NULL;    info->flagconfigFile = 0;
    info->mode = 0;    info->flagmode = 0;
}

void
init1(pdbMoveInfo* info)
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
    
    if(info->flagX) {
    }
    
    if(info->flagY) {
    }
    
    if(info->flagZ) {
    }
    
    if(info->flagtoX) {
    }
    
    if(info->flagtoY) {
    }
    
    if(info->flagtoZ) {
    }
    
    if(info->flagfromX) {
    }
    
    if(info->flagfromY) {
    }
    
    if(info->flagfromZ) {
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
    sprintf(panepath, "%s/src/Tools/pdbUtil/pdbMove/src/pdbMove.pane", eospath);
    khoros_initialize(argc, argv, "EOS");
    fpt = fopen(panepath, "r");    if(NULL!=fpt) {
        fclose(fpt);
        kclui_initialize(panepath, KGEN_NONE, "EOS", "pdbMove",
                     func_usage_additions,
                     func_get_args,
                     func_free_args);
    }
}
#endif /* KHOROS */ 