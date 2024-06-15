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
init0(mrc2bildInfo* info)
{
    info->fptIn = NULL;    info->flagIn = 0;
    info->fptIn0 = NULL;    info->flagIn0 = 0;
    info->fptIn1 = NULL;    info->flagIn1 = 0;
    info->fptIn2 = NULL;    info->flagIn2 = 0;
    info->fptInX = NULL;    info->flagInX = 0;
    info->fptInY = NULL;    info->flagInY = 0;
    info->fptInZ = NULL;    info->flagInZ = 0;
    info->fptInWeight = NULL;    info->flagInWeight = 0;
    info->fptOut = stdout;    info->flagOut = 0;
    info->Red = 1.0;    info->flagRed = 0;
    info->Green = 1.0;    info->flagGreen = 0;
    info->Blue = 1.0;    info->flagBlue = 0;
    info->Zoom = 1.0;    info->flagZoom = 0;
    info->R1 = 0.1;    info->flagR1 = 0;
    info->R2 = 0.4;    info->flagR2 = 0;
    info->Rho = 0.75;    info->flagRho = 0;
    info->skipX = 1;    info->flagskipX = 0;
    info->skipY = 1;    info->flagskipY = 0;
    info->skipZ = 1;    info->flagskipZ = 0;
    info->RainbowMode = 0;    info->flagRainbowMode = 0;
    info->RainbowThresLow = 0;    info->flagRainbowThresLow = 0;
    info->RainbowThresHigh = 0;    info->flagRainbowThresHigh = 0;
    info->RainbowRangeLow = 0;    info->flagRainbowRangeLow = 0;
    info->RainbowRangeHigh = 0;    info->flagRainbowRangeHigh = 0;
    info->RangeXMin = 0;    info->flagRangeXMin = 0;
    info->RangeXMax = -1;    info->flagRangeXMax = 0;
    info->RangeYMin = 0;    info->flagRangeYMin = 0;
    info->RangeYMax = -1;    info->flagRangeYMax = 0;
    info->RangeZMin = 0;    info->flagRangeZMin = 0;
    info->RangeZMax = -1;    info->flagRangeZMax = 0;
    info->RangeRCX = 0;    info->flagRangeRCX = 0;
    info->RangeRCY = 0;    info->flagRangeRCY = 0;
    info->RangeRCZ = 0;    info->flagRangeRCZ = 0;
    info->RangeRR = 0;    info->flagRangeRR = 0;
    info->fptconfigFile = NULL;    info->flagconfigFile = 0;
    info->mode = 0;    info->flagmode = 0;
}

void
init1(mrc2bildInfo* info)
{
    char s[1024];
    int i;
    if(info->flagIn) {
        info->fptIn = fileOpen(info->In, "r");
    }
    
    if(info->flagIn0) {
        info->fptIn0 = fileOpen(info->In0, "r");
    }
    
    if(info->flagIn1) {
        info->fptIn1 = fileOpen(info->In1, "r");
    }
    
    if(info->flagIn2) {
        info->fptIn2 = fileOpen(info->In2, "r");
    }
    
    if(info->flagInX) {
        info->fptInX = fileOpen(info->InX, "r");
    }
    
    if(info->flagInY) {
        info->fptInY = fileOpen(info->InY, "r");
    }
    
    if(info->flagInZ) {
        info->fptInZ = fileOpen(info->InZ, "r");
    }
    
    if(info->flagInWeight) {
        info->fptInWeight = fileOpen(info->InWeight, "r");
    }
    
    if(!info->flagOut) {
        stringGetFromFile(s, "Out", stdin, stdout, 0);
        info->Out = stringGetNthWord(s, 1, " ,\t");
        info->flagOut++;
    }
    if(info->flagOut) {
        info->fptOut = fileOpen(info->Out, "w");
    }
    
    if(info->flagRed) {
    }
    
    if(info->flagGreen) {
    }
    
    if(info->flagBlue) {
    }
    
    if(info->flagZoom) {
    }
    
    if(info->flagR1) {
    }
    
    if(info->flagR2) {
    }
    
    if(info->flagRho) {
    }
    
    if(info->flagskipX) {
    }
    
    if(info->flagskipY) {
    }
    
    if(info->flagskipZ) {
    }
    
    if(info->flagRainbowMode) {
    }
    
    if(info->flagRainbowThresLow) {
    }
    
    if(info->flagRainbowThresHigh) {
    }
    
    if(info->flagRainbowRangeLow) {
    }
    
    if(info->flagRainbowRangeHigh) {
    }
    
    if(info->flagRangeXMin) {
    }
    
    if(info->flagRangeXMax) {
    }
    
    if(info->flagRangeYMin) {
    }
    
    if(info->flagRangeYMax) {
    }
    
    if(info->flagRangeZMin) {
    }
    
    if(info->flagRangeZMax) {
    }
    
    if(info->flagRangeRCX) {
    }
    
    if(info->flagRangeRCY) {
    }
    
    if(info->flagRangeRCZ) {
    }
    
    if(info->flagRangeRR) {
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
    sprintf(panepath, "%s/src/Tools/filter/mrc2bild/src/mrc2bild.pane", eospath);
    khoros_initialize(argc, argv, "EOS");
    fpt = fopen(panepath, "r");    if(NULL!=fpt) {
        fclose(fpt);
        kclui_initialize(panepath, KGEN_NONE, "EOS", "mrc2bild",
                     func_usage_additions,
                     func_get_args,
                     func_free_args);
    }
}
#endif /* KHOROS */ 
