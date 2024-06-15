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
init0(mrc2tiffInfo* info)
{
    info->fptinFile = NULL;    info->flaginFile = 0;
    info->fptoutFile = NULL;    info->flagoutFile = 0;
    info->High = 0;    info->flagHigh = 0;
    info->Low = 0;    info->flagLow = 0;
    info->Inverse=0;
    info->raw=0;
    info->Offset = 0;    info->flagOffset = 0;
    info->Z = 0;    info->flagZ = 0;
    info->Resolution = 1.0;    info->flagResolution = 0;
    info->ResolutionX = 1.0;    info->flagResolutionX = 0;
    info->ResolutionY = 1.0;    info->flagResolutionY = 0;
    info->ResolutionZ = 1.0;    info->flagResolutionZ = 0;
    info->format = stringGetNthWord("%s.%04d", 1, "\0");    info->flagformat = 0;
    info->colorMode = 0;    info->flagcolorMode = 0;
    info->colorRangeMin = 0;    info->flagcolorRangeMin = 0;
    info->colorRangeMax = 100;    info->flagcolorRangeMax = 0;
    info->fptconfigFile = NULL;    info->flagconfigFile = 0;
    info->Mode = 0;    info->flagMode = 0;
    info->mode = 0;    info->flagmode = 0;
}

void
init1(mrc2tiffInfo* info)
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
    
    if(info->flagHigh) {
    }
    
    if(info->flagLow) {
    }
    
    if(info->flagOffset) {
    }
    
    if(info->flagZ) {
    }
    
    if(info->flagResolution) {
    }
    
    if(info->flagResolutionX) {
    }
    
    if(info->flagResolutionY) {
    }
    
    if(info->flagResolutionZ) {
    }
    
    if(info->flagformat) {
    }
    
    if(info->flagcolorMode) {
    }
    
    if(info->flagcolorRangeMin) {
    }
    
    if(info->flagcolorRangeMax) {
    }
    
    if(info->flagconfigFile) {
        info->fptconfigFile = fileOpen(info->configFile, "r");
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
    sprintf(panepath, "%s/src/Tools/filter/mrc2tiff/src/mrc2tiff.pane", eospath);
    khoros_initialize(argc, argv, "EOS");
    fpt = fopen(panepath, "r");    if(NULL!=fpt) {
        fclose(fpt);
        kclui_initialize(panepath, KGEN_NONE, "EOS", "mrc2tiff",
                     func_usage_additions,
                     func_get_args,
                     func_free_args);
    }
}
#endif /* KHOROS */ 
