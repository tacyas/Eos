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
init0(pdbTransInfo* info)
{
    info->fptinFile = NULL;    info->flaginFile = 0;
    info->fptoutFile = NULL;    info->flagoutFile = 0;
    info->fptmatFile = NULL;    info->flagmatFile = 0;
    info->RotMode = stringGetNthWord("YOYS", 1, "\0");    info->flagRotMode = 0;
    info->Rot1 = 0.0;    info->flagRot1 = 0;
    info->Rot2 = 0.0;    info->flagRot2 = 0;
    info->Rot3 = 0.0;    info->flagRot3 = 0;
    info->cudaDeviceID = 0;    info->flagcudaDeviceID = 0;
    info->fptconfigFile = NULL;    info->flagconfigFile = 0;
    info->mode = 0;    info->flagmode = 0;
}

void
init1(pdbTransInfo* info)
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
    
    if(info->flagmatFile) {
        info->fptmatFile = fileOpen(info->matFile, "r");
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
    sprintf(panepath, "%s/src/Tools/pdbUtil/pdbTrans/src/pdbTrans.pane", eospath);
    khoros_initialize(argc, argv, "EOS");
    fpt = fopen(panepath, "r");    if(NULL!=fpt) {
        fclose(fpt);
        kclui_initialize(panepath, KGEN_NONE, "EOS", "pdbTrans",
                     func_usage_additions,
                     func_get_args,
                     func_free_args);
    }
}
#endif /* KHOROS */ 