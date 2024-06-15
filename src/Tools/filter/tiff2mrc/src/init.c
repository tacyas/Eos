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
init0(tiff2mrcInfo* info)
{
    info->fptinFile = NULL;    info->flaginFile = 0;
    info->fptoutFile = NULL;    info->flagoutFile = 0;
    info->Resolution = 1.0;    info->flagResolution = 0;
    info->ResolutionX = 1.0;    info->flagResolutionX = 0;
    info->ResolutionY = 1.0;    info->flagResolutionY = 0;
    info->ResolutionZ = 1.0;    info->flagResolutionZ = 0;
    info->time = 1.0;    info->flagtime = 0;
    info->dirnum = -1;    info->flagdirnum = 0;
    info->Inverse=0;
    info->Signed=0;
    info->Offset = 0.0;    info->flagOffset = 0;
    info->Max = 16;    info->flagMax = 0;
    info->Min = 1;    info->flagMin = 0;
    info->realMin = 0.0;    info->flagrealMin = 0;
    info->realMax = 0.0;    info->flagrealMax = 0;
    info->realMaxBit = 14;    info->flagrealMaxBit = 0;
    info->fptsinFile = NULL;    info->flagsinFile = 0;
    info->fptconfigFile = NULL;    info->flagconfigFile = 0;
    info->Shrink = 8;    info->flagShrink = 0;
    info->Mode = 0;    info->flagMode = 0;
    info->mode = 0;    info->flagmode = 0;
}

void
init1(tiff2mrcInfo* info)
{
    char s[1024];
    int i;
    if(!info->flaginFile) {
        stringGetFromFile(s, "inFile", stdin, stdout, 0);
        info->inFile = stringGetNthWord(s, 1, " ,\t");
        info->flaginFile++;
    }
    if(info->flaginFile) {
        info->fptinFile = fileOpen(info->inFile, "r");
    }
    
    if(!info->flagoutFile) {
        stringGetFromFile(s, "outFile", stdin, stdout, 0);
        info->outFile = stringGetNthWord(s, 1, " ,\t");
        info->flagoutFile++;
    }
    if(info->flagoutFile) {
        info->fptoutFile = fileOpen(info->outFile, "w");
    }
    
    if(info->flagResolution) {
    }
    
    if(info->flagResolutionX) {
    }
    
    if(info->flagResolutionY) {
    }
    
    if(info->flagResolutionZ) {
    }
    
    if(info->flagtime) {
    }
    
    if(info->flagdirnum) {
    }
    
    if(info->flagOffset) {
    }
    
    if(info->flagMax) {
    }
    
    if(info->flagMin) {
    }
    
    if(info->flagrealMin) {
    }
    
    if(info->flagrealMax) {
    }
    
    if(info->flagrealMaxBit) {
    }
    
    if(info->flagsinFile) {
        info->fptsinFile = fileOpen(info->sinFile, "r");
    }
    
    if(info->flagconfigFile) {
        info->fptconfigFile = fileOpen(info->configFile, "r");
    }
    
    if(info->flagShrink) {
    }
    
    if(info->flagMode) {
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
    sprintf(panepath, "%s/src/Tools/filter/tiff2mrc/src/tiff2mrc.pane", eospath);
    khoros_initialize(argc, argv, "EOS");
    fpt = fopen(panepath, "r");    if(NULL!=fpt) {
        fclose(fpt);
        kclui_initialize(panepath, KGEN_NONE, "EOS", "tiff2mrc",
                     func_usage_additions,
                     func_get_args,
                     func_free_args);
    }
}
#endif /* KHOROS */ 
