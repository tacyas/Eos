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
init0(CheckCommonLineDataInfo* info)
{
    info->fptIn     = NULL;    info->fptInList = NULL;    info->flagIn = 0;
    info->fptOutR = NULL;    info->flagOutR = 0;
    info->fptOutI = NULL;    info->flagOutI = 0;
    info->fptOutL = NULL;    info->flagOutL = 0;
    info->fptOutP = NULL;    info->flagOutP = 0;
    info->fptOutLL = NULL;    info->flagOutLL = 0;
    info->fptLog = NULL;    info->flagLog = 0;
    info->fptconfigFile = NULL;    info->flagconfigFile = 0;
    info->mode = 0;    info->flagmode = 0;
}

void
init1(CheckCommonLineDataInfo* info)
{
    char s[1024];
    int i;
    if(!info->flagIn) {
        stringGetFromFile(s, "In", stdin, stdout, 0);
        info->InList = stringGetNthWord(s, 1, " ,\t");
        info->flagIn++;
    }
    if(info->flagIn) {
        info->fptInList = fileOpen(info->InList, "r");
        fseek(info->fptInList, 0L, SEEK_SET);
        i=0;
        while(NULL!=stringGetFromFile(s, "", info->fptInList, stdout, 1)) {
            i++;
        }
        info->fptIn = (FILE**)memoryAllocate(i*sizeof(FILE*), "in init1");
        info->In    = (char**)memoryAllocate(i*sizeof(char*), "in init1");
        info->flagIn = i;
        fseek(info->fptInList, 0L, SEEK_SET);
        i=0;
        while(NULL!=stringGetFromFile(s, "", info->fptInList, stdout, 1)) {
            info->In[i] = stringGetNthWord(s, 1, " ,\t");
            i++;
        }
    }
    
    if(!info->flagOutR) {
        stringGetFromFile(s, "OutR", stdin, stdout, 0);
        info->OutR = stringGetNthWord(s, 1, " ,\t");
        info->flagOutR++;
    }
    if(info->flagOutR) {
        info->fptOutR = fileOpen(info->OutR, "w");
    }
    
    if(!info->flagOutI) {
        stringGetFromFile(s, "OutI", stdin, stdout, 0);
        info->OutI = stringGetNthWord(s, 1, " ,\t");
        info->flagOutI++;
    }
    if(info->flagOutI) {
        info->fptOutI = fileOpen(info->OutI, "w");
    }
    
    if(!info->flagOutL) {
        stringGetFromFile(s, "OutL", stdin, stdout, 0);
        info->OutL = stringGetNthWord(s, 1, " ,\t");
        info->flagOutL++;
    }
    if(info->flagOutL) {
        info->fptOutL = fileOpen(info->OutL, "w");
    }
    
    if(!info->flagOutP) {
        stringGetFromFile(s, "OutP", stdin, stdout, 0);
        info->OutP = stringGetNthWord(s, 1, " ,\t");
        info->flagOutP++;
    }
    if(info->flagOutP) {
        info->fptOutP = fileOpen(info->OutP, "w");
    }
    
    if(!info->flagOutLL) {
        stringGetFromFile(s, "OutLL", stdin, stdout, 0);
        info->OutLL = stringGetNthWord(s, 1, " ,\t");
        info->flagOutLL++;
    }
    if(info->flagOutLL) {
        info->fptOutLL = fileOpen(info->OutLL, "w");
    }
    
    if(!info->flagLog) {
        stringGetFromFile(s, "Log", stdin, stdout, 0);
        info->Log = stringGetNthWord(s, 1, " ,\t");
        info->flagLog++;
    }
    if(info->flagLog) {
        info->fptLog = fileOpen(info->Log, "w");
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
    sprintf(panepath, "%s/src/Tools/rec3d/CheckCommonLineData/src/CheckCommonLineData.pane", eospath);
    khoros_initialize(argc, argv, "EOS");
    fpt = fopen(panepath, "r");    if(NULL!=fpt) {
        fclose(fpt);
        kclui_initialize(panepath, KGEN_NONE, "EOS", "CheckCommonLineData",
                     func_usage_additions,
                     func_get_args,
                     func_free_args);
    }
}
#endif /* KHOROS */ 
