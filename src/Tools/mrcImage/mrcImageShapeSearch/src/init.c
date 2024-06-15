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
init0(mrcImageShapeSearchInfo* info)
{
    info->fptIn = NULL;    info->flagIn = 0;
    info->fptOut = NULL;    info->flagOut = 0;
    info->fptShape = NULL;    info->flagShape = 0;
    info->nCube = 0;    info->flagnCube = 0;
    info->Refine=0;
    info->minR = 3;    info->flagminR = 0;
    info->maxR = 5;    info->flagmaxR = 0;
    info->delR = 1;    info->flagdelR = 0;
    info->minL = 3;    info->flagminL = 0;
    info->maxL = 5;    info->flagmaxL = 0;
    info->delL = 1;    info->flagdelL = 0;
    info->minPhi = 0.0;    info->flagminPhi = 0;
    info->maxPhi = 359.0;    info->flagmaxPhi = 0;
    info->delPhi = 45.0;    info->flagdelPhi = 0;
    info->minTheta = 0.0;    info->flagminTheta = 0;
    info->maxTheta = 359.0;    info->flagmaxTheta = 0;
    info->delTheta = 45.0;    info->flagdelTheta = 0;
    info->minPsi = 0.0;    info->flagminPsi = 0;
    info->maxPsi = 350.0;    info->flagmaxPsi = 0;
    info->delPsi = 45.0;    info->flagdelPsi = 0;
    info->thresZscore = 1.0;    info->flagthresZscore = 0;
    info->interpMode = 0;    info->flaginterpMode = 0;
    info->OVMode = 0;    info->flagOVMode = 0;
    info->fptOutVectorBILD = NULL;    info->flagOutVectorBILD = 0;
    info->OutVector = stringGetNthWord("NULL", 1, "\0");    info->flagOutVector = 0;
    info->ArrowR1 = 0.1;    info->flagArrowR1 = 0;
    info->ArrowR2 = 0.4;    info->flagArrowR2 = 0;
    info->ArrowRho = 0.75;    info->flagArrowRho = 0;
    info->ZoomVector = 1.0;    info->flagZoomVector = 0;
    info->ArrowColorDisk0 = 0.0;    info->flagArrowColorDisk0 = 0;
    info->ArrowColorDisk1 = 1.0;    info->flagArrowColorDisk1 = 0;
    info->ArrowColorDisk2 = 0.0;    info->flagArrowColorDisk2 = 0;
    info->ArrowColorSylinder0 = 1.0;    info->flagArrowColorSylinder0 = 0;
    info->ArrowColorSylinder1 = 0.0;    info->flagArrowColorSylinder1 = 0;
    info->ArrowColorSylinder2 = 0.0;    info->flagArrowColorSylinder2 = 0;
    info->fptconfigFile = NULL;    info->flagconfigFile = 0;
    info->mode = 0;    info->flagmode = 0;
}

void
init1(mrcImageShapeSearchInfo* info)
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
    
    if(info->flagShape) {
        info->fptShape = fileOpen(info->Shape, "w");
    }
    
    if(info->flagnCube) {
    }
    
    if(info->flagminR) {
    }
    
    if(info->flagmaxR) {
    }
    
    if(info->flagdelR) {
    }
    
    if(info->flagminL) {
    }
    
    if(info->flagmaxL) {
    }
    
    if(info->flagdelL) {
    }
    
    if(info->flagminPhi) {
    }
    
    if(info->flagmaxPhi) {
    }
    
    if(info->flagdelPhi) {
    }
    
    if(info->flagminTheta) {
    }
    
    if(info->flagmaxTheta) {
    }
    
    if(info->flagdelTheta) {
    }
    
    if(info->flagminPsi) {
    }
    
    if(info->flagmaxPsi) {
    }
    
    if(info->flagdelPsi) {
    }
    
    if(info->flagthresZscore) {
    }
    
    if(info->flaginterpMode) {
    }
    
    if(info->flagOVMode) {
    }
    
    if(info->flagOutVectorBILD) {
        info->fptOutVectorBILD = fileOpen(info->OutVectorBILD, "w");
    }
    
    if(info->flagOutVector) {
    }
    
    if(info->flagArrowR1) {
    }
    
    if(info->flagArrowR2) {
    }
    
    if(info->flagArrowRho) {
    }
    
    if(info->flagZoomVector) {
    }
    
    if(info->flagArrowColorDisk0) {
    }
    
    if(info->flagArrowColorDisk1) {
    }
    
    if(info->flagArrowColorDisk2) {
    }
    
    if(info->flagArrowColorSylinder0) {
    }
    
    if(info->flagArrowColorSylinder1) {
    }
    
    if(info->flagArrowColorSylinder2) {
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
    sprintf(panepath, "%s/src/Tools/mrcImage/mrcImageShapeSearch/src/mrcImageShapeSearch.pane", eospath);
    khoros_initialize(argc, argv, "EOS");
    fpt = fopen(panepath, "r");    if(NULL!=fpt) {
        fclose(fpt);
        kclui_initialize(panepath, KGEN_NONE, "EOS", "mrcImageShapeSearch",
                     func_usage_additions,
                     func_get_args,
                     func_free_args);
    }
}
#endif /* KHOROS */ 
