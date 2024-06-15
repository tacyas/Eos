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
init0(mrcImagepdbFileReduceInfo* info)
{
    info->fptIn = NULL;    info->flagIn = 0;
    info->fptPdb = NULL;    info->flagPdb = 0;
    info->fptOut = NULL;    info->flagOut = 0;
    info->Th = 0;    info->flagTh = 0;
    info->R = 1;    info->flagR = 0;
    info->Value = 0;    info->flagValue = 0;
    info->fptconfigFile = NULL;    info->flagconfigFile = 0;
    info->ITh = 0;    info->flagITh = 0;
    info->mode = 0;    info->flagmode = 0;
}

void
init1(mrcImagepdbFileReduceInfo* info)
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
    
    if(!info->flagPdb) {
        stringGetFromFile(s, "Pdb", stdin, stdout, 0);
        info->Pdb = stringGetNthWord(s, 1, " ,\t");
        info->flagPdb++;
    }
    if(info->flagPdb) {
        info->fptPdb = fileOpen(info->Pdb, "r");
    }
    
    if(!info->flagOut) {
        stringGetFromFile(s, "Out", stdin, stdout, 0);
        info->Out = stringGetNthWord(s, 1, " ,\t");
        info->flagOut++;
    }
    if(info->flagOut) {
        info->fptOut = fileOpen(info->Out, "w");
    }
    
    if(!info->flagTh) {
        stringGetFromFile(s, "Th", stdin, stdout, 0);
        info->Th = stringGetNthRealData(s, 1, ", \t");
        info->flagTh++;
    }
    if(info->flagTh) {
    }
    
    if(info->flagR) {
    }
    
    if(info->flagValue) {
    }
    
    if(info->flagconfigFile) {
        info->fptconfigFile = fileOpen(info->configFile, "r");
    }
    
    if(info->flagITh) {
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
    sprintf(panepath, "%s/src/Tools/mrcImage/mrcImagepdbFileReduce/src/mrcImagepdbFileReduce.pane", eospath);
    khoros_initialize(argc, argv, "EOS");
    fpt = fopen(panepath, "r");    if(NULL!=fpt) {
        fclose(fpt);
        kclui_initialize(panepath, KGEN_NONE, "EOS", "mrcImagepdbFileReduce",
                     func_usage_additions,
                     func_get_args,
                     func_free_args);
    }
}
#endif /* KHOROS */ 
