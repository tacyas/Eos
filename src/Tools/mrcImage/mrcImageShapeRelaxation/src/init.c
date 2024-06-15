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
init0(mrcImageShapeRelaxationInfo* info)
{
    info->fptIn = NULL;    info->flagIn = 0;
    info->fptInVec0 = NULL;    info->flagInVec0 = 0;
    info->fptInVec1 = NULL;    info->flagInVec1 = 0;
    info->fptInVec2 = NULL;    info->flagInVec2 = 0;
    info->fptOut = NULL;    info->flagOut = 0;
    info->fptconfigFile = NULL;    info->flagconfigFile = 0;
    info->mode = 0;    info->flagmode = 0;
}

void
init1(mrcImageShapeRelaxationInfo* info)
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
    
    if(!info->flagInVec0) {
        stringGetFromFile(s, "InVec0", stdin, stdout, 0);
        info->InVec0 = stringGetNthWord(s, 1, " ,\t");
        info->flagInVec0++;
    }
    if(info->flagInVec0) {
        info->fptInVec0 = fileOpen(info->InVec0, "r");
    }
    
    if(!info->flagInVec1) {
        stringGetFromFile(s, "InVec1", stdin, stdout, 0);
        info->InVec1 = stringGetNthWord(s, 1, " ,\t");
        info->flagInVec1++;
    }
    if(info->flagInVec1) {
        info->fptInVec1 = fileOpen(info->InVec1, "r");
    }
    
    if(!info->flagInVec2) {
        stringGetFromFile(s, "InVec2", stdin, stdout, 0);
        info->InVec2 = stringGetNthWord(s, 1, " ,\t");
        info->flagInVec2++;
    }
    if(info->flagInVec2) {
        info->fptInVec2 = fileOpen(info->InVec2, "r");
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
    sprintf(panepath, "%s/src/Tools/mrcImage/mrcImageShapeRelaxation/src/mrcImageShapeRelaxation.pane", eospath);
    khoros_initialize(argc, argv, "EOS");
    fpt = fopen(panepath, "r");    if(NULL!=fpt) {
        fclose(fpt);
        kclui_initialize(panepath, KGEN_NONE, "EOS", "mrcImageShapeRelaxation",
                     func_usage_additions,
                     func_get_args,
                     func_free_args);
    }
}
#endif /* KHOROS */ 
