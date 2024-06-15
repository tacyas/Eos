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
init0(mrcImageTiltAxisSearchHelpInfo* info)
{
    info->fptInList     = NULL;    info->fptInListList = NULL;    info->flagInList = 0;
    info->fptOut1D = NULL;    info->flagOut1D = 0;
    info->fptOut1DEnlarged = NULL;    info->flagOut1DEnlarged = 0;
    info->fptOut2D = NULL;    info->flagOut2D = 0;
    info->OriginX = 0.0;    info->flagOriginX = 0;
    info->OriginY = 0.0;    info->flagOriginY = 0;
    info->OriginZ = 0.0;    info->flagOriginZ = 0;
    info->AxisAngleYaw = 0.0;    info->flagAxisAngleYaw = 0;
    info->AxisAnglePitch = 0.0;    info->flagAxisAnglePitch = 0;
    info->Rmin = 0.05;    info->flagRmin = 0;
    info->Rmax = 0.1;    info->flagRmax = 0;
    info->InterpolationMode = 2;    info->flagInterpolationMode = 0;
    info->fptconfigFile = NULL;    info->flagconfigFile = 0;
    info->mode = 0;    info->flagmode = 0;
}

void
init1(mrcImageTiltAxisSearchHelpInfo* info)
{
    char s[1024];
    int i;
    if(!info->flagInList) {
        stringGetFromFile(s, "InList", stdin, stdout, 0);
        info->InListList = stringGetNthWord(s, 1, " ,\t");
        info->flagInList++;
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
    
    if(info->flagOut1D) {
        info->fptOut1D = fileOpen(info->Out1D, "w");
    }
    
    if(info->flagOut1DEnlarged) {
        info->fptOut1DEnlarged = fileOpen(info->Out1DEnlarged, "w");
    }
    
    if(info->flagOut2D) {
        info->fptOut2D = fileOpen(info->Out2D, "w");
    }
    
    if(info->flagOriginX) {
    }
    
    if(info->flagOriginY) {
    }
    
    if(info->flagOriginZ) {
    }
    
    if(info->flagAxisAngleYaw) {
    }
    
    if(info->flagAxisAnglePitch) {
    }
    
    if(info->flagRmin) {
    }
    
    if(info->flagRmax) {
    }
    
    if(info->flagInterpolationMode) {
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
    sprintf(panepath, "%s/src/Tools/mrcImage/mrcImageTiltAxisSearchHelp/src/mrcImageTiltAxisSearchHelp.pane", eospath);
    khoros_initialize(argc, argv, "EOS");
    fpt = fopen(panepath, "r");    if(NULL!=fpt) {
        fclose(fpt);
        kclui_initialize(panepath, KGEN_NONE, "EOS", "mrcImageTiltAxisSearchHelp",
                     func_usage_additions,
                     func_get_args,
                     func_free_args);
    }
}
#endif /* KHOROS */ 
