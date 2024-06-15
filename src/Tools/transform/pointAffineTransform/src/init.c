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
init0(pointAffineTransformInfo* info)
{
    info->X = 0;    info->flagX = 0;
    info->Y = 0;    info->flagY = 0;
    info->Z = 0;    info->flagZ = 0;
    info->Euler = stringGetNthWord("YOYS", 1, "\0");    info->flagEuler = 0;
    info->Rot1 = 0;    info->flagRot1 = 0;
    info->Rot2 = 0;    info->flagRot2 = 0;
    info->Rot3 = 0;    info->flagRot3 = 0;
    info->dX = 0;    info->flagdX = 0;
    info->dY = 0;    info->flagdY = 0;
    info->dZ = 0;    info->flagdZ = 0;
    info->fptOut = stdout;    info->flagOut = 0;
    info->fptconfigFile = NULL;    info->flagconfigFile = 0;
    info->mode = 0;    info->flagmode = 0;
}

void
init1(pointAffineTransformInfo* info)
{
    char s[1024];
    int i;
    if(!info->flagX) {
        stringGetFromFile(s, "X", stdin, stdout, 0);
        info->X = stringGetNthRealData(s, 1, ", \t");
        info->flagX++;
    }
    if(info->flagX) {
    }
    
    if(!info->flagY) {
        stringGetFromFile(s, "Y", stdin, stdout, 0);
        info->Y = stringGetNthRealData(s, 1, ", \t");
        info->flagY++;
    }
    if(info->flagY) {
    }
    
    if(!info->flagZ) {
        stringGetFromFile(s, "Z", stdin, stdout, 0);
        info->Z = stringGetNthRealData(s, 1, ", \t");
        info->flagZ++;
    }
    if(info->flagZ) {
    }
    
    if(info->flagEuler) {
    }
    
    if(info->flagRot1) {
    }
    
    if(info->flagRot2) {
    }
    
    if(info->flagRot3) {
    }
    
    if(info->flagdX) {
    }
    
    if(info->flagdY) {
    }
    
    if(info->flagdZ) {
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
    sprintf(panepath, "%s/src/Tools/transform/pointAffineTransform/src/pointAffineTransform.pane", eospath);
    khoros_initialize(argc, argv, "EOS");
    fpt = fopen(panepath, "r");    if(NULL!=fpt) {
        fclose(fpt);
        kclui_initialize(panepath, KGEN_NONE, "EOS", "pointAffineTransform",
                     func_usage_additions,
                     func_get_args,
                     func_free_args);
    }
}
#endif /* KHOROS */ 
