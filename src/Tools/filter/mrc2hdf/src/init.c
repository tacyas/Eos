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
init0(mrc2hdfInfo* info)
{
    info->fptIn = NULL;    info->flagIn = 0;
    info->fptInList     = NULL;    info->fptInListList = NULL;    info->flagInList = 0;
    info->fptInList2     = NULL;    info->fptInList2List = NULL;    info->flagInList2 = 0;
    info->IR = 1.0;    info->flagIR = 0;
    info->IG = 0.0;    info->flagIG = 0;
    info->IB = 0.0;    info->flagIB = 0;
    info->IA = 1.0;    info->flagIA = 0;
    info->I2R = 0.0;    info->flagI2R = 0;
    info->I2G = 1.0;    info->flagI2G = 0;
    info->I2B = 0.0;    info->flagI2B = 0;
    info->I2A = 1.0;    info->flagI2A = 0;
    info->fptOut = NULL;    info->flagOut = 0;
    info->fptconfigFile = NULL;    info->flagconfigFile = 0;
    info->nResolution = 1;    info->flagnResolution = 0;
    info->hdf5mode = 1;    info->flaghdf5mode = 0;
    info->mode = 0;    info->flagmode = 0;
}

void
init1(mrc2hdfInfo* info)
{
    char s[1024];
    int i;
    if(info->flagIn) {
        info->fptIn = fileOpen(info->In, "r");
    }
    
    if(info->flagInList) {
        info->fptInListList = fileOpen(info->InListList, "r");
        fseek(info->fptInListList, 0L, SEEK_SET);
        i=0;
        while(NULL!=stringGetFromFile(s, "", info->fptInListList, stdout, 1)) {
            i++;
        }
        info->fptInList = (FILE**)memoryAllocate(i*sizeof(FILE*), "in init1");
        info->InList    = (char**)memoryAllocate(i*sizeof(char*), "in init1");
        info->flagInList = i;
        fseek(info->fptInListList, 0L, SEEK_SET);
        i=0;
        while(NULL!=stringGetFromFile(s, "", info->fptInListList, stdout, 1)) {
            info->InList[i] = stringGetNthWord(s, 1, " ,\t");
            info->fptInList[i] = fileOpen(info->InList[i],"r");
            i++;
        }
    }
    
    if(info->flagInList2) {
        info->fptInList2List = fileOpen(info->InList2List, "r");
        fseek(info->fptInList2List, 0L, SEEK_SET);
        i=0;
        while(NULL!=stringGetFromFile(s, "", info->fptInList2List, stdout, 1)) {
            i++;
        }
        info->fptInList2 = (FILE**)memoryAllocate(i*sizeof(FILE*), "in init1");
        info->InList2    = (char**)memoryAllocate(i*sizeof(char*), "in init1");
        info->flagInList2 = i;
        fseek(info->fptInList2List, 0L, SEEK_SET);
        i=0;
        while(NULL!=stringGetFromFile(s, "", info->fptInList2List, stdout, 1)) {
            info->InList2[i] = stringGetNthWord(s, 1, " ,\t");
            info->fptInList2[i] = fileOpen(info->InList2[i],"r");
            i++;
        }
    }
    
    if(info->flagIR) {
    }
    
    if(info->flagIG) {
    }
    
    if(info->flagIB) {
    }
    
    if(info->flagIA) {
    }
    
    if(info->flagI2R) {
    }
    
    if(info->flagI2G) {
    }
    
    if(info->flagI2B) {
    }
    
    if(info->flagI2A) {
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
    
    if(info->flagnResolution) {
    }
    
    if(info->flaghdf5mode) {
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
    sprintf(panepath, "%s/src/Tools/filter/mrc2hdf/src/mrc2hdf.pane", eospath);
    khoros_initialize(argc, argv, "EOS");
    fpt = fopen(panepath, "r");    if(NULL!=fpt) {
        fclose(fpt);
        kclui_initialize(panepath, KGEN_NONE, "EOS", "mrc2hdf",
                     func_usage_additions,
                     func_get_args,
                     func_free_args);
    }
}
#endif /* KHOROS */ 
