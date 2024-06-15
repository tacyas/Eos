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
init0(dcdFilePrintInfo* info)
{
    info->fptIn = NULL;    info->flagIn = 0;
    info->fptInPDB = NULL;    info->flagInPDB = 0;
    info->fptOut = NULL;    info->flagOut = 0;
    info->fptOutPDB = NULL;    info->flagOutPDB = 0;
    info->rStart = 10;    info->flagrStart = 0;
    info->rEnd = 100;    info->flagrEnd = 0;
    info->rDelta = 10;    info->flagrDelta = 0;
    info->Start = 10;    info->flagStart = 0;
    info->End = 100;    info->flagEnd = 0;
    info->Delta = 10;    info->flagDelta = 0;
    info->fptconfigFile = NULL;    info->flagconfigFile = 0;
    info->mode = 0;    info->flagmode = 0;
}

void
init1(dcdFilePrintInfo* info)
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
    
    if(info->flagInPDB) {
        info->fptInPDB = fileOpen(info->InPDB, "r");
    }
    
    if(!info->flagOut) {
        stringGetFromFile(s, "Out", stdin, stdout, 0);
        info->Out = stringGetNthWord(s, 1, " ,\t");
        info->flagOut++;
    }
    if(info->flagOut) {
        info->fptOut = fileOpen(info->Out, "w");
    }
    
    if(info->flagOutPDB) {
        info->fptOutPDB = fileOpen(info->OutPDB, "w");
    }
    
    if(info->flagrStart) {
    }
    
    if(info->flagrEnd) {
    }
    
    if(info->flagrDelta) {
    }
    
    if(info->flagStart) {
    }
    
    if(info->flagEnd) {
    }
    
    if(info->flagDelta) {
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
    sprintf(panepath, "%s/src/Tools/DCDFile/dcdFilePrint/src/dcdFilePrint.pane", eospath);
    khoros_initialize(argc, argv, "EOS");
    fpt = fopen(panepath, "r");    if(NULL!=fpt) {
        fclose(fpt);
        kclui_initialize(panepath, KGEN_NONE, "EOS", "dcdFilePrint",
                     func_usage_additions,
                     func_get_args,
                     func_free_args);
    }
}
#endif /* KHOROS */ 
