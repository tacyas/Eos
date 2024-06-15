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
init0(pdbTwoProteinFitInfo* info)
{
    info->fptIn = NULL;    info->flagIn = 0;
    info->fptInResidue = NULL;    info->flagInResidue = 0;
    info->fptSelectIn = NULL;    info->flagSelectIn = 0;
    info->fptRef = NULL;    info->flagRef = 0;
    info->fptRefResidue = NULL;    info->flagRefResidue = 0;
    info->fptSelectRef = NULL;    info->flagSelectRef = 0;
    info->fptOut = NULL;    info->flagOut = 0;
    info->fptMatrix = stdout;    info->flagMatrix = 0;
    info->fptParam = stdout;    info->flagParam = 0;
    info->fptoutDis = stdout;    info->flagoutDis = 0;
    info->fptoutDis2 = stdout;    info->flagoutDis2 = 0;
    info->fptconfigFile = NULL;    info->flagconfigFile = 0;
    info->mode = 0;    info->flagmode = 0;
}

void
init1(pdbTwoProteinFitInfo* info)
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
    
    if(info->flagInResidue) {
        info->fptInResidue = fileOpen(info->InResidue, "r");
    }
    
    if(info->flagSelectIn) {
        info->fptSelectIn = fileOpen(info->SelectIn, "w");
    }
    
    if(!info->flagRef) {
        stringGetFromFile(s, "Ref", stdin, stdout, 0);
        info->Ref = stringGetNthWord(s, 1, " ,\t");
        info->flagRef++;
    }
    if(info->flagRef) {
        info->fptRef = fileOpen(info->Ref, "r");
    }
    
    if(info->flagRefResidue) {
        info->fptRefResidue = fileOpen(info->RefResidue, "r");
    }
    
    if(info->flagSelectRef) {
        info->fptSelectRef = fileOpen(info->SelectRef, "w");
    }
    
    if(!info->flagOut) {
        stringGetFromFile(s, "Out", stdin, stdout, 0);
        info->Out = stringGetNthWord(s, 1, " ,\t");
        info->flagOut++;
    }
    if(info->flagOut) {
        info->fptOut = fileOpen(info->Out, "w");
    }
    
    if(info->flagMatrix) {
        info->fptMatrix = fileOpen(info->Matrix, "w");
    }
    
    if(info->flagParam) {
        info->fptParam = fileOpen(info->Param, "w");
    }
    
    if(info->flagoutDis) {
        info->fptoutDis = fileOpen(info->outDis, "w");
    }
    
    if(info->flagoutDis2) {
        info->fptoutDis2 = fileOpen(info->outDis2, "w");
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
    sprintf(panepath, "%s/src/Tools/pdbUtil/pdbTwoProteinFit/src/pdbTwoProteinFit.pane", eospath);
    khoros_initialize(argc, argv, "EOS");
    fpt = fopen(panepath, "r");    if(NULL!=fpt) {
        fclose(fpt);
        kclui_initialize(panepath, KGEN_NONE, "EOS", "pdbTwoProteinFit",
                     func_usage_additions,
                     func_get_args,
                     func_free_args);
    }
}
#endif /* KHOROS */ 
