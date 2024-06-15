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
init0(mrcImageNfoldAxisSearchInfo* info)
{
    info->fptIn = NULL;    info->flagIn = 0;
    info->fptOut = stdout;    info->flagOut = 0;
    info->fptOut2 = stdout;    info->flagOut2 = 0;
    info->fptRes = NULL;    info->flagRes = 0;
    info->nFold = 2;    info->flagnFold = 0;
    info->delPHI = 1.0;    info->flagdelPHI = 0;
    info->minx = -3;    info->flagminx = 0;
    info->maxx = 3;    info->flagmaxx = 0;
    info->delx = 1;    info->flagdelx = 0;
    info->miny = -3;    info->flagminy = 0;
    info->maxy = 3;    info->flagmaxy = 0;
    info->dely = 1;    info->flagdely = 0;
    info->minz = 0;    info->flagminz = 0;
    info->maxz = 0;    info->flagmaxz = 0;
    info->delz = 1;    info->flagdelz = 0;
    info->fptconfigFile = NULL;    info->flagconfigFile = 0;
    info->mode = 0;    info->flagmode = 0;
}

void
init1(mrcImageNfoldAxisSearchInfo* info)
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
    
    if(info->flagOut2) {
        info->fptOut2 = fileOpen(info->Out2, "w");
    }
    
    if(info->flagRes) {
        info->fptRes = fileOpen(info->Res, "w");
    }
    
    if(!info->flagnFold) {
        stringGetFromFile(s, "nFold", stdin, stdout, 0);
        info->nFold = stringGetNthIntegerData(s, 1, ", \t");
        info->flagnFold++;
    }
    if(info->flagnFold) {
    }
    
    if(info->flagdelPHI) {
    }
    
    if(info->flagminx) {
    }
    
    if(info->flagmaxx) {
    }
    
    if(info->flagdelx) {
    }
    
    if(info->flagminy) {
    }
    
    if(info->flagmaxy) {
    }
    
    if(info->flagdely) {
    }
    
    if(info->flagminz) {
    }
    
    if(info->flagmaxz) {
    }
    
    if(info->flagdelz) {
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
    sprintf(panepath, "%s/src/Tools/mrcImage/mrcImageNfoldAxisSearch/src/mrcImageNfoldAxisSearch.pane", eospath);
    khoros_initialize(argc, argv, "EOS");
    fpt = fopen(panepath, "r");    if(NULL!=fpt) {
        fclose(fpt);
        kclui_initialize(panepath, KGEN_NONE, "EOS", "mrcImageNfoldAxisSearch",
                     func_usage_additions,
                     func_get_args,
                     func_free_args);
    }
}
#endif /* KHOROS */ 
