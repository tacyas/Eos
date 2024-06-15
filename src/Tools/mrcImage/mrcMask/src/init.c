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
init0(mrcMaskInfo* info)
{
    info->fptIn = NULL;    info->flagIn = 0;
    info->fptOut = NULL;    info->flagOut = 0;
    info->fptconfigFile = NULL;    info->flagconfigFile = 0;
    info->sizeX = 1;    info->flagsizeX = 0;
    info->sizeY = 1;    info->flagsizeY = 0;
    info->v1x = 1;    info->flagv1x = 0;
    info->v1y = 0;    info->flagv1y = 0;
    info->v2x = 0;    info->flagv2x = 0;
    info->v2y = 1;    info->flagv2y = 0;
    info->inum = 1;    info->flaginum = 0;
    info->num = 0;    info->flagnum = 0;
    info->exnum = 0;    info->flagexnum = 0;
    info->mode = 0;    info->flagmode = 0;
}

void
init1(mrcMaskInfo* info)
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
    
    if(info->flagconfigFile) {
        info->fptconfigFile = fileOpen(info->configFile, "r");
    }
    
    if(info->flagsizeX) {
    }
    
    if(info->flagsizeY) {
    }
    
    if(!info->flagv1x) {
        stringGetFromFile(s, "v1x", stdin, stdout, 0);
        info->v1x = stringGetNthRealData(s, 1, ", \t");
        info->flagv1x++;
    }
    if(info->flagv1x) {
    }
    
    if(!info->flagv1y) {
        stringGetFromFile(s, "v1y", stdin, stdout, 0);
        info->v1y = stringGetNthRealData(s, 1, ", \t");
        info->flagv1y++;
    }
    if(info->flagv1y) {
    }
    
    if(info->flagv2x) {
    }
    
    if(info->flagv2y) {
    }
    
    if(info->flaginum) {
    }
    
    if(info->flagnum) {
    }
    
    if(info->flagexnum) {
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
    sprintf(panepath, "%s/src/Tools/mrcImage/mrcMask/src/mrcMask.pane", eospath);
    khoros_initialize(argc, argv, "EOS");
    fpt = fopen(panepath, "r");    if(NULL!=fpt) {
        fclose(fpt);
        kclui_initialize(panepath, KGEN_NONE, "EOS", "mrcMask",
                     func_usage_additions,
                     func_get_args,
                     func_free_args);
    }
}
#endif /* KHOROS */ 
