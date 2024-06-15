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
init0(mrcImageMeanFreePathCalcInfo* info)
{
    info->fptIn = NULL;    info->flagIn = 0;
    info->fptOut = stdout;    info->flagOut = 0;
    info->fptOutWhiteAll = NULL;    info->flagOutWhiteAll = 0;
    info->fptOutWhite = NULL;    info->flagOutWhite = 0;
    info->fptOutBlackAll = NULL;    info->flagOutBlackAll = 0;
    info->fptOutBlack = NULL;    info->flagOutBlack = 0;
    info->fptOutWhiteEdge = NULL;    info->flagOutWhiteEdge = 0;
    info->fptOutBlackEdge = NULL;    info->flagOutBlackEdge = 0;
    info->Direction = stringGetNthWord("direction", 1, "\0");    info->flagDirection = 0;
    info->LineThicknessX = 1;    info->flagLineThicknessX = 0;
    info->LineThicknessY = 1;    info->flagLineThicknessY = 0;
    info->LineMode = 0;    info->flagLineMode = 0;
    info->LineShape = 0;    info->flagLineShape = 0;
    info->deltaPhi = 30;    info->flagdeltaPhi = 0;
    info->deltaTheta = 30;    info->flagdeltaTheta = 0;
    info->fptconfigFile = NULL;    info->flagconfigFile = 0;
    info->mode = 0;    info->flagmode = 0;
}

void
init1(mrcImageMeanFreePathCalcInfo* info)
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
    
    if(info->flagOutWhiteAll) {
        info->fptOutWhiteAll = fileOpen(info->OutWhiteAll, "w");
    }
    
    if(info->flagOutWhite) {
        info->fptOutWhite = fileOpen(info->OutWhite, "w");
    }
    
    if(info->flagOutBlackAll) {
        info->fptOutBlackAll = fileOpen(info->OutBlackAll, "w");
    }
    
    if(info->flagOutBlack) {
        info->fptOutBlack = fileOpen(info->OutBlack, "w");
    }
    
    if(info->flagOutWhiteEdge) {
        info->fptOutWhiteEdge = fileOpen(info->OutWhiteEdge, "w");
    }
    
    if(info->flagOutBlackEdge) {
        info->fptOutBlackEdge = fileOpen(info->OutBlackEdge, "w");
    }
    
    if(info->flagDirection) {
    }
    
    if(info->flagLineThicknessX) {
    }
    
    if(info->flagLineThicknessY) {
    }
    
    if(info->flagLineMode) {
    }
    
    if(info->flagLineShape) {
    }
    
    if(info->flagdeltaPhi) {
    }
    
    if(info->flagdeltaTheta) {
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
    sprintf(panepath, "%s/src/Tools/mrcImage/mrcImageMeanFreePathCalc/src/mrcImageMeanFreePathCalc.pane", eospath);
    khoros_initialize(argc, argv, "EOS");
    fpt = fopen(panepath, "r");    if(NULL!=fpt) {
        fclose(fpt);
        kclui_initialize(panepath, KGEN_NONE, "EOS", "mrcImageMeanFreePathCalc",
                     func_usage_additions,
                     func_get_args,
                     func_free_args);
    }
}
#endif /* KHOROS */ 
