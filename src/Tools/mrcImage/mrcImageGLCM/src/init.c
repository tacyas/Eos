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
init0(mrcImageGLCMInfo* info)
{
    info->fptIn = NULL;    info->flagIn = 0;
    info->fptOut = NULL;    info->flagOut = 0;
    info->fptOutInfo = stdout;    info->flagOutInfo = 0;
    info->epsilon = 2.2e-16;    info->flagepsilon = 0;
    info->thresHigh = 1.0;    info->flagthresHigh = 0;
    info->thresLow = 0.0;    info->flagthresLow = 0;
    info->exceptValue = 0.0;    info->flagexceptValue = 0;
    info->range = 2.0;    info->flagrange = 0;
    info->nHist = 8;    info->flagnHist = 0;
    info->offset = 1;    info->flagoffset = 0;
    info->angleMode = 15;    info->flagangleMode = 0;
    info->minAreaX = 0;    info->flagminAreaX = 0;
    info->maxAreaX = 1.0;    info->flagmaxAreaX = 0;
    info->minAreaY = 0;    info->flagminAreaY = 0;
    info->maxAreaY = 1.0;    info->flagmaxAreaY = 0;
    info->minAreaZ = 0;    info->flagminAreaZ = 0;
    info->maxAreaZ = 1.0;    info->flagmaxAreaZ = 0;
    info->fptconfigFile = NULL;    info->flagconfigFile = 0;
    info->mode = 0;    info->flagmode = 0;
}

void
init1(mrcImageGLCMInfo* info)
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
    
    if(info->flagOut) {
        info->fptOut = fileOpen(info->Out, "w");
    }
    
    if(info->flagOutInfo) {
        info->fptOutInfo = fileOpen(info->OutInfo, "w");
    }
    
    if(info->flagepsilon) {
    }
    
    if(info->flagthresHigh) {
    }
    
    if(info->flagthresLow) {
    }
    
    if(info->flagexceptValue) {
    }
    
    if(info->flagrange) {
    }
    
    if(info->flagnHist) {
    }
    
    if(info->flagoffset) {
    }
    
    if(info->flagangleMode) {
    }
    
    if(info->flagminAreaX) {
    }
    
    if(info->flagmaxAreaX) {
    }
    
    if(info->flagminAreaY) {
    }
    
    if(info->flagmaxAreaY) {
    }
    
    if(info->flagminAreaZ) {
    }
    
    if(info->flagmaxAreaZ) {
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
    sprintf(panepath, "%s/src/Tools/mrcImage/mrcImageGLCM/src/mrcImageGLCM.pane", eospath);
    khoros_initialize(argc, argv, "EOS");
    fpt = fopen(panepath, "r");    if(NULL!=fpt) {
        fclose(fpt);
        kclui_initialize(panepath, KGEN_NONE, "EOS", "mrcImageGLCM",
                     func_usage_additions,
                     func_get_args,
                     func_free_args);
    }
}
#endif /* KHOROS */ 
