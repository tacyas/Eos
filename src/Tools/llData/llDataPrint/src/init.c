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
init0(llDataPrintInfo* info)
{
    info->fptIn = NULL;    info->flagIn = 0;
    info->fptIns     = NULL;    info->fptInsList = NULL;    info->flagIns = 0;
    info->fptNea = NULL;    info->flagNea = 0;
    info->fptFar = NULL;    info->flagFar = 0;
    info->fptOut = stdout;    info->flagOut = 0;
    info->Rmax = 0.1;    info->flagRmax = 0;
    info->Interactive=0;
    info->fptconfigFile = NULL;    info->flagconfigFile = 0;
    info->mode = 0;    info->flagmode = 0;
}

void
init1(llDataPrintInfo* info)
{
    char s[1024];
    int i;
    if(info->flagIn) {
        info->fptIn = fileOpen(info->In, "r");
    }
    
    if(info->flagIns) {
        info->fptInsList = fileOpen(info->InsList, "r");
        fseek(info->fptInsList, 0L, SEEK_SET);
        i=0;
        while(NULL!=stringGetFromFile(s, "", info->fptInsList, stdout, 1)) {
            i++;
        }
        info->fptIns = (FILE**)memoryAllocate(i*sizeof(FILE*), "in init1");
        info->Ins    = (char**)memoryAllocate(i*sizeof(char*), "in init1");
        info->flagIns = i;
        fseek(info->fptInsList, 0L, SEEK_SET);
        i=0;
        while(NULL!=stringGetFromFile(s, "", info->fptInsList, stdout, 1)) {
            info->Ins[i] = stringGetNthWord(s, 1, " ,\t");
            info->fptIns[i] = fileOpen(info->Ins[i],"r");
            i++;
        }
    }
    
    if(info->flagNea) {
        info->fptNea = fileOpen(info->Nea, "r");
    }
    
    if(info->flagFar) {
        info->fptFar = fileOpen(info->Far, "r");
    }
    
    if(info->flagOut) {
        info->fptOut = fileOpen(info->Out, "w");
    }
    
    if(info->flagRmax) {
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
    sprintf(panepath, "%s/src/Tools/llData/llDataPrint/src/llDataPrint.pane", eospath);
    khoros_initialize(argc, argv, "EOS");
    fpt = fopen(panepath, "r");    if(NULL!=fpt) {
        fclose(fpt);
        kclui_initialize(panepath, KGEN_NONE, "EOS", "llDataPrint",
                     func_usage_additions,
                     func_get_args,
                     func_free_args);
    }
}
#endif /* KHOROS */ 
