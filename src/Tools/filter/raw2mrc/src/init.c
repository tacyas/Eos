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
init0(raw2mrcInfo* info)
{
    info->fptIn = NULL;    info->flagIn = 0;
    info->fptOut = NULL;    info->flagOut = 0;
    info->Nx = 1;    info->flagNx = 0;
    info->Ny = 1;    info->flagNy = 0;
    info->Nz = 1;    info->flagNz = 0;
    info->Offset = 0;    info->flagOffset = 0;
    info->DataType = 1;    info->flagDataType = 0;
    info->fptconfigFile = NULL;    info->flagconfigFile = 0;
    info->mode = 0;    info->flagmode = 0;
}

void
init1(raw2mrcInfo* info)
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
    
    if(!info->flagNx) {
        stringGetFromFile(s, "Nx", stdin, stdout, 0);
        info->Nx = stringGetNthIntegerData(s, 1, ", \t");
        info->flagNx++;
    }
    if(info->flagNx) {
    }
    
    if(!info->flagNy) {
        stringGetFromFile(s, "Ny", stdin, stdout, 0);
        info->Ny = stringGetNthIntegerData(s, 1, ", \t");
        info->flagNy++;
    }
    if(info->flagNy) {
    }
    
    if(!info->flagNz) {
        stringGetFromFile(s, "Nz", stdin, stdout, 0);
        info->Nz = stringGetNthIntegerData(s, 1, ", \t");
        info->flagNz++;
    }
    if(info->flagNz) {
    }
    
    if(info->flagOffset) {
    }
    
    if(info->flagDataType) {
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
    sprintf(panepath, "%s/src/Tools/filter/raw2mrc/src/raw2mrc.pane", eospath);
    khoros_initialize(argc, argv, "EOS");
    fpt = fopen(panepath, "r");    if(NULL!=fpt) {
        fclose(fpt);
        kclui_initialize(panepath, KGEN_NONE, "EOS", "raw2mrc",
                     func_usage_additions,
                     func_get_args,
                     func_free_args);
    }
}
#endif /* KHOROS */ 
