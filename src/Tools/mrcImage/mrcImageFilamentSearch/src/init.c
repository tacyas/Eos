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
init0(mrcImageFilamentSearchInfo* info)
{
    info->fptIn = NULL;    info->flagIn = 0;
    info->fptRef = NULL;    info->flagRef = 0;
    info->fptOutCorr = NULL;    info->flagOutCorr = 0;
    info->fptOut = NULL;    info->flagOut = 0;
    info->fptOutAngle = NULL;    info->flagOutAngle = 0;
    info->fptOutTheta = NULL;    info->flagOutTheta = 0;
    info->dtheta = 5.0;    info->flagdtheta = 0;
    info->fptconfigFile = NULL;    info->flagconfigFile = 0;
    info->mode = 0;    info->flagmode = 0;
}

void
init1(mrcImageFilamentSearchInfo* info)
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
    
    if(info->flagRef) {
        info->fptRef = fileOpen(info->Ref, "r");
    }
    
    if(info->flagOutCorr) {
        info->fptOutCorr = fileOpen(info->OutCorr, "w");
    }
    
    if(info->flagOut) {
        info->fptOut = fileOpen(info->Out, "w");
    }
    
    if(info->flagOutAngle) {
        info->fptOutAngle = fileOpen(info->OutAngle, "w");
    }
    
    if(!info->flagOutTheta) {
        stringGetFromFile(s, "OutTheta", stdin, stdout, 0);
        info->OutTheta = stringGetNthWord(s, 1, " ,\t");
        info->flagOutTheta++;
    }
    if(info->flagOutTheta) {
        info->fptOutTheta = fileOpen(info->OutTheta, "w");
    }
    
    if(info->flagdtheta) {
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
    sprintf(panepath, "%s/src/Tools/mrcImage/mrcImageFilamentSearch/src/mrcImageFilamentSearch.pane", eospath);
    khoros_initialize(argc, argv, "EOS");
    fpt = fopen(panepath, "r");    if(NULL!=fpt) {
        fclose(fpt);
        kclui_initialize(panepath, KGEN_NONE, "EOS", "mrcImageFilamentSearch",
                     func_usage_additions,
                     func_get_args,
                     func_free_args);
    }
}
#endif /* KHOROS */ 
