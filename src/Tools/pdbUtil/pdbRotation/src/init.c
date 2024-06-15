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
init0(pdbRotationInfo* info)
{
    info->fptIn = NULL;    info->flagIn = 0;
    info->fptOut = NULL;    info->flagOut = 0;
    info->ZXYrotx = 0.0;    info->flagZXYrotx = 0;
    info->ZXYroty = 0.0;    info->flagZXYroty = 0;
    info->ZXYrotz = 0.0;    info->flagZXYrotz = 0;
    info->ZYXrotx = 0.0;    info->flagZYXrotx = 0;
    info->ZYXroty = 0.0;    info->flagZYXroty = 0;
    info->ZYXrotz = 0.0;    info->flagZYXrotz = 0;
    info->YXZrotx = 0.0;    info->flagYXZrotx = 0;
    info->YXZroty = 0.0;    info->flagYXZroty = 0;
    info->YXZrotz = 0.0;    info->flagYXZrotz = 0;
    info->XYZrotx = 0.0;    info->flagXYZrotx = 0;
    info->XYZroty = 0.0;    info->flagXYZroty = 0;
    info->XYZrotz = 0.0;    info->flagXYZrotz = 0;
    info->RotMode = stringGetNthWord("YOYS", 1, "\0");    info->flagRotMode = 0;
    info->Rot1 = 0.0;    info->flagRot1 = 0;
    info->Rot2 = 0.0;    info->flagRot2 = 0;
    info->Rot3 = 0.0;    info->flagRot3 = 0;
    info->cudaDeviceID = 0;    info->flagcudaDeviceID = 0;
    info->fptconfigFile = NULL;    info->flagconfigFile = 0;
    info->mode = 0;    info->flagmode = 0;
}

void
init1(pdbRotationInfo* info)
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
    
    if(info->flagZXYrotx) {
    }
    
    if(info->flagZXYroty) {
    }
    
    if(info->flagZXYrotz) {
    }
    
    if(info->flagZYXrotx) {
    }
    
    if(info->flagZYXroty) {
    }
    
    if(info->flagZYXrotz) {
    }
    
    if(info->flagYXZrotx) {
    }
    
    if(info->flagYXZroty) {
    }
    
    if(info->flagYXZrotz) {
    }
    
    if(info->flagXYZrotx) {
    }
    
    if(info->flagXYZroty) {
    }
    
    if(info->flagXYZrotz) {
    }
    
    if(info->flagRotMode) {
    }
    
    if(info->flagRot1) {
    }
    
    if(info->flagRot2) {
    }
    
    if(info->flagRot3) {
    }
    
    if(info->flagcudaDeviceID) {
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
    sprintf(panepath, "%s/src/Tools/pdbUtil/pdbRotation/src/pdbRotation.pane", eospath);
    khoros_initialize(argc, argv, "EOS");
    fpt = fopen(panepath, "r");    if(NULL!=fpt) {
        fclose(fpt);
        kclui_initialize(panepath, KGEN_NONE, "EOS", "pdbRotation",
                     func_usage_additions,
                     func_get_args,
                     func_free_args);
    }
}
#endif /* KHOROS */ 
