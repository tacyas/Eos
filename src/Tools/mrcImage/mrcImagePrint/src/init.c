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
init0(mrcImagePrintInfo* info)
{
    info->fptIn = NULL;    info->flagIn = 0;
    info->fptOut = stdout;    info->flagOut = 0;
    info->thresHigh = 0.0;    info->flagthresHigh = 0;
    info->thresLow = 1.0;    info->flagthresLow = 0;
    info->section = 'z';    info->flagsection = 0;
    info->xMin = 0;    info->flagxMin = 0;
    info->xMax = 0;    info->flagxMax = 0;
    info->yMin = 0;    info->flagyMin = 0;
    info->yMax = 0;    info->flagyMax = 0;
    info->zMin = 0;    info->flagzMin = 0;
    info->zMax = 0;    info->flagzMax = 0;
    info->Scale = 1.0;    info->flagScale = 0;
    info->AbScale = 1.0;    info->flagAbScale = 0;
    info->Enlarge = 1.0;    info->flagEnlarge = 0;
    info->cx = 0.0/* in case of FT or N.x/2.0 in case of Image*/;    info->flagcx = 0;
    info->cy = 0.0/* in case of FT or N.y/2.0 in case of Image */;    info->flagcy = 0;
    info->contourLevel = NULL;    info->flagcontourLevel = 0;
    info->Inverse=0;
    info->Auto=0;
    info->AutoContour = 10;    info->flagAutoContour = 0;
    info->PeakContour = 10;    info->flagPeakContour = 0;
    info->AutoContour2 = 10;    info->flagAutoContour2 = 0;
    info->Yexpand = 1;    info->flagYexpand = 0;
    info->Red = 0;    info->flagRed = 0;
    info->Green = 0;    info->flagGreen = 0;
    info->Blue = 0;    info->flagBlue = 0;
    info->RedFirst = 0;    info->flagRedFirst = 0;
    info->GreenFirst = 0;    info->flagGreenFirst = 0;
    info->BlueFirst = 0;    info->flagBlueFirst = 0;
    info->RedLast = 0;    info->flagRedLast = 0;
    info->GreenLast = 0;    info->flagGreenLast = 0;
    info->BlueLast = 0;    info->flagBlueLast = 0;
    info->Hue = 0;    info->flagHue = 0;
    info->Saturation = 0;    info->flagSaturation = 0;
    info->Brightness = 0;    info->flagBrightness = 0;
    info->HueFirst = 0;    info->flagHueFirst = 0;
    info->SaturationFirst = 0;    info->flagSaturationFirst = 0;
    info->BrightnessFirst = 0;    info->flagBrightnessFirst = 0;
    info->HueLast = 0;    info->flagHueLast = 0;
    info->SaturationLast = 0;    info->flagSaturationLast = 0;
    info->BrightnessLast = 0;    info->flagBrightnessLast = 0;
    info->LineRed = 0;    info->flagLineRed = 0;
    info->LineGreen = 0;    info->flagLineGreen = 0;
    info->LineBlue = 0;    info->flagLineBlue = 0;
    info->LineRedFirst = 0;    info->flagLineRedFirst = 0;
    info->LineGreenFirst = 0;    info->flagLineGreenFirst = 0;
    info->LineBlueFirst = 0;    info->flagLineBlueFirst = 0;
    info->LineRedLast = 0;    info->flagLineRedLast = 0;
    info->LineGreenLast = 0;    info->flagLineGreenLast = 0;
    info->LineBlueLast = 0;    info->flagLineBlueLast = 0;
    info->LineHue = 0;    info->flagLineHue = 0;
    info->LineSaturation = 0;    info->flagLineSaturation = 0;
    info->LineBrightness = 0;    info->flagLineBrightness = 0;
    info->LineHueFirst = 0;    info->flagLineHueFirst = 0;
    info->LineSaturationFirst = 0;    info->flagLineSaturationFirst = 0;
    info->LineBrightnessFirst = 0;    info->flagLineBrightnessFirst = 0;
    info->LineHueLast = 0;    info->flagLineHueLast = 0;
    info->LineSaturationLast = 0;    info->flagLineSaturationLast = 0;
    info->LineBrightnessLast = 0;    info->flagLineBrightnessLast = 0;
    info->LineColorChange = 0.1;    info->flagLineColorChange = 0;
    info->LineWidthStart = 0.1;    info->flagLineWidthStart = 0;
    info->LineWidthStep = 0.05;    info->flagLineWidthStep = 0;
    info->ReverseOrder=0;
    info->untwist = 0.0;    info->flaguntwist = 0;
    info->UpsideDown=0;
    info->Centre=0;
    info->CircleRadius = 0.5;    info->flagCircleRadius = 0;
    info->mode = 49;    info->flagmode = 0;
}

void
init1(mrcImagePrintInfo* info)
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
    
    if(info->flagthresHigh) {
    }
    
    if(info->flagthresLow) {
    }
    
    if(info->flagsection) {
    }
    
    if(info->flagxMin) {
    }
    
    if(info->flagxMax) {
    }
    
    if(info->flagyMin) {
    }
    
    if(info->flagyMax) {
    }
    
    if(info->flagzMin) {
    }
    
    if(info->flagzMax) {
    }
    
    if(info->flagScale) {
    }
    
    if(info->flagAbScale) {
    }
    
    if(info->flagEnlarge) {
    }
    
    if(info->flagcx) {
    }
    
    if(info->flagcy) {
    }
    
    if(info->flagcontourLevel) {
    }
    
    if(info->flagAutoContour) {
    }
    
    if(info->flagPeakContour) {
    }
    
    if(info->flagAutoContour2) {
    }
    
    if(info->flagYexpand) {
    }
    
    if(info->flagRed) {
    }
    
    if(info->flagGreen) {
    }
    
    if(info->flagBlue) {
    }
    
    if(info->flagRedFirst) {
    }
    
    if(info->flagGreenFirst) {
    }
    
    if(info->flagBlueFirst) {
    }
    
    if(info->flagRedLast) {
    }
    
    if(info->flagGreenLast) {
    }
    
    if(info->flagBlueLast) {
    }
    
    if(info->flagHue) {
    }
    
    if(info->flagSaturation) {
    }
    
    if(info->flagBrightness) {
    }
    
    if(info->flagHueFirst) {
    }
    
    if(info->flagSaturationFirst) {
    }
    
    if(info->flagBrightnessFirst) {
    }
    
    if(info->flagHueLast) {
    }
    
    if(info->flagSaturationLast) {
    }
    
    if(info->flagBrightnessLast) {
    }
    
    if(info->flagLineRed) {
    }
    
    if(info->flagLineGreen) {
    }
    
    if(info->flagLineBlue) {
    }
    
    if(info->flagLineRedFirst) {
    }
    
    if(info->flagLineGreenFirst) {
    }
    
    if(info->flagLineBlueFirst) {
    }
    
    if(info->flagLineRedLast) {
    }
    
    if(info->flagLineGreenLast) {
    }
    
    if(info->flagLineBlueLast) {
    }
    
    if(info->flagLineHue) {
    }
    
    if(info->flagLineSaturation) {
    }
    
    if(info->flagLineBrightness) {
    }
    
    if(info->flagLineHueFirst) {
    }
    
    if(info->flagLineSaturationFirst) {
    }
    
    if(info->flagLineBrightnessFirst) {
    }
    
    if(info->flagLineHueLast) {
    }
    
    if(info->flagLineSaturationLast) {
    }
    
    if(info->flagLineBrightnessLast) {
    }
    
    if(info->flagLineColorChange) {
    }
    
    if(info->flagLineWidthStart) {
    }
    
    if(info->flagLineWidthStep) {
    }
    
    if(info->flaguntwist) {
    }
    
    if(info->flagCircleRadius) {
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
    sprintf(panepath, "%s/src/Tools/mrcImage/mrcImagePrint/src/mrcImagePrint.pane", eospath);
    khoros_initialize(argc, argv, "EOS");
    fpt = fopen(panepath, "r");    if(NULL!=fpt) {
        fclose(fpt);
        kclui_initialize(panepath, KGEN_NONE, "EOS", "mrcImagePrint",
                     func_usage_additions,
                     func_get_args,
                     func_free_args);
    }
}
#endif /* KHOROS */ 
