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
init0(mrcImageCurlInfo* info)
{
    info->fptIn2x = NULL;    info->flagIn2x = 0;
    info->fptIn2y = NULL;    info->flagIn2y = 0;
    info->fptIn3x = NULL;    info->flagIn3x = 0;
    info->fptIn3y = NULL;    info->flagIn3y = 0;
    info->fptIn3z = NULL;    info->flagIn3z = 0;
    info->fptOut = NULL;    info->flagOut = 0;
    info->fptOut3x = NULL;    info->flagOut3x = 0;
    info->fptOut3y = NULL;    info->flagOut3y = 0;
    info->fptOut3z = NULL;    info->flagOut3z = 0;
    info->fptconfigFile = NULL;    info->flagconfigFile = 0;
    info->mode = 0;    info->flagmode = 0;
}

void
init1(mrcImageCurlInfo* info)
{
    char s[1024];
    int i;
    if(info->flagIn2x) {
        info->fptIn2x = fileOpen(info->In2x, "r");
    }
    
    if(info->flagIn2y) {
        info->fptIn2y = fileOpen(info->In2y, "r");
    }
    
    if(info->flagIn3x) {
        info->fptIn3x = fileOpen(info->In3x, "r");
    }
    
    if(info->flagIn3y) {
        info->fptIn3y = fileOpen(info->In3y, "r");
    }
    
    if(info->flagIn3z) {
        info->fptIn3z = fileOpen(info->In3z, "r");
    }
    
    if(!info->flagOut) {
        stringGetFromFile(s, "Out", stdin, stdout, 0);
        info->Out = stringGetNthWord(s, 1, " ,\t");
        info->flagOut++;
    }
    if(info->flagOut) {
        info->fptOut = fileOpen(info->Out, "w");
    }
    
    if(info->flagOut3x) {
        info->fptOut3x = fileOpen(info->Out3x, "w");
    }
    
    if(info->flagOut3y) {
        info->fptOut3y = fileOpen(info->Out3y, "w");
    }
    
    if(info->flagOut3z) {
        info->fptOut3z = fileOpen(info->Out3z, "w");
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
    sprintf(panepath, "%s/src/Tools/mrcImage/mrcImageCurl/src/mrcImageCurl.pane", eospath);
    khoros_initialize(argc, argv, "EOS");
    fpt = fopen(panepath, "r");    if(NULL!=fpt) {
        fclose(fpt);
        kclui_initialize(panepath, KGEN_NONE, "EOS", "mrcImageCurl",
                     func_usage_additions,
                     func_get_args,
                     func_free_args);
    }
}
#endif /* KHOROS */ 
