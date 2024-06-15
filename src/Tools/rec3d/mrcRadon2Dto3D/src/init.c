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
init0(mrcRadon2Dto3DInfo* info)
{
    info->fptIn2     = NULL;    info->fptIn2List = NULL;    info->flagIn2 = 0;
    info->fptInBefore     = NULL;    info->fptInBeforeList = NULL;    info->flagInBefore = 0;
    info->fptinbefore = NULL;    info->flaginbefore = 0;
    info->fptinWbefore = NULL;    info->flaginWbefore = 0;
    info->fptOut = NULL;    info->flagOut = 0;
    info->fptOutW = NULL;    info->flagOutW = 0;
    info->dp = 2.0;    info->flagdp = 0;
    info->dtheta = 1;    info->flagdtheta = 0;
    info->dphi = 1;    info->flagdphi = 0;
    info->T = 1.0;    info->flagT = 0;
    info->InterpolationMode = 0;    info->flagInterpolationMode = 0;
    info->mode = 0;    info->flagmode = 0;
}

void
init1(mrcRadon2Dto3DInfo* info)
{
    char s[1024];
    int i;
    if(!info->flagIn2) {
        stringGetFromFile(s, "In2", stdin, stdout, 0);
        info->In2List = stringGetNthWord(s, 1, " ,\t");
        info->flagIn2++;
    }
    if(info->flagIn2) {
        info->fptIn2List = fileOpen(info->In2List, "r");
        fseek(info->fptIn2List, 0L, SEEK_SET);
        i=0;
        while(NULL!=stringGetFromFile(s, "", info->fptIn2List, stdout, 1)) {
            i++;
        }
        info->fptIn2 = (FILE**)memoryAllocate(i*sizeof(FILE*), "in init1");
        info->In2    = (char**)memoryAllocate(i*sizeof(char*), "in init1");
        info->flagIn2 = i;
        fseek(info->fptIn2List, 0L, SEEK_SET);
        i=0;
        while(NULL!=stringGetFromFile(s, "", info->fptIn2List, stdout, 1)) {
            info->In2[i] = stringGetNthWord(s, 1, " ,\t");
            info->fptIn2[i] = fileOpen(info->In2[i],"r");
            i++;
        }
    }
    
    if(info->flagInBefore) {
        info->fptInBeforeList = fileOpen(info->InBeforeList, "r");
        fseek(info->fptInBeforeList, 0L, SEEK_SET);
        i=0;
        while(NULL!=stringGetFromFile(s, "", info->fptInBeforeList, stdout, 1)) {
            i++;
        }
        info->fptInBefore = (FILE**)memoryAllocate(i*sizeof(FILE*), "in init1");
        info->InBefore    = (char**)memoryAllocate(i*sizeof(char*), "in init1");
        info->flagInBefore = i;
        fseek(info->fptInBeforeList, 0L, SEEK_SET);
        i=0;
        while(NULL!=stringGetFromFile(s, "", info->fptInBeforeList, stdout, 1)) {
            info->InBefore[i] = stringGetNthWord(s, 1, " ,\t");
            info->fptInBefore[i] = fileOpen(info->InBefore[i],"r");
            i++;
        }
    }
    
    if(info->flaginbefore) {
        info->fptinbefore = fileOpen(info->inbefore, "r");
    }
    
    if(info->flaginWbefore) {
        info->fptinWbefore = fileOpen(info->inWbefore, "r");
    }
    
    if(!info->flagOut) {
        stringGetFromFile(s, "Out", stdin, stdout, 0);
        info->Out = stringGetNthWord(s, 1, " ,\t");
        info->flagOut++;
    }
    if(info->flagOut) {
        info->fptOut = fileOpen(info->Out, "w");
    }
    
    if(!info->flagOutW) {
        stringGetFromFile(s, "OutW", stdin, stdout, 0);
        info->OutW = stringGetNthWord(s, 1, " ,\t");
        info->flagOutW++;
    }
    if(info->flagOutW) {
        info->fptOutW = fileOpen(info->OutW, "w");
    }
    
    if(!info->flagdp) {
        stringGetFromFile(s, "dp", stdin, stdout, 0);
        info->dp = stringGetNthRealData(s, 1, ", \t");
        info->flagdp++;
    }
    if(info->flagdp) {
    }
    
    if(!info->flagdtheta) {
        stringGetFromFile(s, "dtheta", stdin, stdout, 0);
        info->dtheta = stringGetNthRealData(s, 1, ", \t");
        info->flagdtheta++;
    }
    if(info->flagdtheta) {
    }
    
    if(!info->flagdphi) {
        stringGetFromFile(s, "dphi", stdin, stdout, 0);
        info->dphi = stringGetNthRealData(s, 1, ", \t");
        info->flagdphi++;
    }
    if(info->flagdphi) {
    }
    
    if(info->flagT) {
    }
    
    if(info->flagInterpolationMode) {
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
    sprintf(panepath, "%s/src/Tools/rec3d/mrcRadon2Dto3D/src/mrcRadon2Dto3D.pane", eospath);
    khoros_initialize(argc, argv, "EOS");
    fpt = fopen(panepath, "r");    if(NULL!=fpt) {
        fclose(fpt);
        kclui_initialize(panepath, KGEN_NONE, "EOS", "mrcRadon2Dto3D",
                     func_usage_additions,
                     func_get_args,
                     func_free_args);
    }
}
#endif /* KHOROS */ 
