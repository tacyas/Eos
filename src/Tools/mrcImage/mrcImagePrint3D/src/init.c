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
init0(mrcImagePrint3DInfo* info)
{
    info->fptIn = NULL;    info->flagIn = 0;
    info->fptOut = NULL;    info->flagOut = 0;
    info->Stereo = 6.0;    info->flagStereo = 0;
    info->nRotation = 60;    info->flagnRotation = 0;
    info->RotationAngle = 6.0;    info->flagRotationAngle = 0;
    info->eyeX = 100.0;    info->flageyeX = 0;
    info->eyeY = 0.0;    info->flageyeY = 0;
    info->eyeZ = 0.0;    info->flageyeZ = 0;
    info->planeX = 0.0;    info->flagplaneX = 0;
    info->planeY = 0.0;    info->flagplaneY = 0;
    info->planeZ = 0.0;    info->flagplaneZ = 0;
    info->fptconfigFile = NULL;    info->flagconfigFile = 0;
    info->mode = 0;    info->flagmode = 0;
    info->contourLevel = NULL;    info->flagcontourLevel = 0;
}

void
init1(mrcImagePrint3DInfo* info)
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
    
    if(info->flagStereo) {
    }
    
    if(info->flagnRotation) {
    }
    
    if(info->flagRotationAngle) {
    }
    
    if(info->flageyeX) {
    }
    
    if(info->flageyeY) {
    }
    
    if(info->flageyeZ) {
    }
    
    if(info->flagplaneX) {
    }
    
    if(info->flagplaneY) {
    }
    
    if(info->flagplaneZ) {
    }
    
    if(info->flagconfigFile) {
        info->fptconfigFile = fileOpen(info->configFile, "r");
    }
    
    if(info->flagmode) {
    }
    
    if(info->flagcontourLevel) {
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
    sprintf(panepath, "%s/src/Tools/mrcImage/mrcImagePrint3D/src/mrcImagePrint3D.pane", eospath);
    khoros_initialize(argc, argv, "EOS");
    fpt = fopen(panepath, "r");    if(NULL!=fpt) {
        fclose(fpt);
        kclui_initialize(panepath, KGEN_NONE, "EOS", "mrcImagePrint3D",
                     func_usage_additions,
                     func_get_args,
                     func_free_args);
    }
}
#endif /* KHOROS */ 
