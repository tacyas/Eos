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
init0(mrc2gifInfo* info)
{
    info->fptinFile = NULL;    info->flaginFile = 0;
    info->fptoutFile = NULL;    info->flagoutFile = 0;
    info->High = 0;    info->flagHigh = 0;
    info->Low = 0;    info->flagLow = 0;
    info->Inverse=0;
    info->Z = 0;    info->flagZ = 0;
    info->format = stringGetNthWord("%s.%04d", 1, "\0");    info->flagformat = 0;
    info->fptconfigFile = NULL;    info->flagconfigFile = 0;
    info->mode = 0;    info->flagmode = 0;
}

void
init1(mrc2gifInfo* info)
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
    
    if(info->flagZ) {
    }
    
    if(info->flagformat) {
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
    sprintf(panepath, "%s/src/Tools/filter/mrc2gif/src/mrc2gif.pane", eospath);
    khoros_initialize(argc, argv, "EOS");
    fpt = fopen(panepath, "r");    if(NULL!=fpt) {
        fclose(fpt);
        kclui_initialize(panepath, KGEN_NONE, "EOS", "mrc2gif",
                     func_usage_additions,
                     func_get_args,
                     func_free_args);
    }
}
#endif /* KHOROS */ 
