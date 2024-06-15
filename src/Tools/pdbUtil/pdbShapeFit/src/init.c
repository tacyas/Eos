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
init0(pdbShapeFitInfo* info)
{
    info->fptInPDB = NULL;    info->flagInPDB = 0;
    info->fptInMRC = NULL;    info->flagInMRC = 0;
    info->Contour = 0.0;    info->flagContour = 0;
    info->ContourMode = 0;    info->flagContourMode = 0;
    info->fptOutMRC = NULL;    info->flagOutMRC = 0;
    info->fptOutTxt = stdout;    info->flagOutTxt = 0;
    info->fptOutPDB = NULL;    info->flagOutPDB = 0;
    info->xmin = 0;    info->flagxmin = 0;
    info->xmax = 0;    info->flagxmax = 0;
    info->xDelta = 1;    info->flagxDelta = 0;
    info->ymin = 0;    info->flagymin = 0;
    info->ymax = 0;    info->flagymax = 0;
    info->yDelta = 1;    info->flagyDelta = 0;
    info->zmin = 0;    info->flagzmin = 0;
    info->zmax = 82;    info->flagzmax = 0;
    info->zDelta = 1;    info->flagzDelta = 0;
    info->EulerAngle = stringGetNthWord("ZOYS", 1, "\0");    info->flagEulerAngle = 0;
    info->phimin = 0;    info->flagphimin = 0;
    info->phimax = 194;    info->flagphimax = 0;
    info->phiDelta = 2;    info->flagphiDelta = 0;
    info->psimin = 0;    info->flagpsimin = 0;
    info->psimax = 0;    info->flagpsimax = 0;
    info->psiDelta = 2;    info->flagpsiDelta = 0;
    info->thetamin = 0;    info->flagthetamin = 0;
    info->thetamax = 0;    info->flagthetamax = 0;
    info->thetaDelta = 2;    info->flagthetaDelta = 0;
    info->surfaceMode = 0;    info->flagsurfaceMode = 0;
    info->order = 1.7;    info->flagorder = 0;
    info->refine = 2;    info->flagrefine = 0;
    info->size = 3;    info->flagsize = 0;
    info->weight = 100;    info->flagweight = 0;
    info->mergin = 3.0;    info->flagmergin = 0;
    info->thresHold = 0.0;    info->flagthresHold = 0;
    info->Inverse=0;
    info->Centre=0;
    info->fptconfigFile = NULL;    info->flagconfigFile = 0;
    info->mode = 0;    info->flagmode = 0;
}

void
init1(pdbShapeFitInfo* info)
{
    char s[1024];
    int i;
    if(!info->flagInPDB) {
        stringGetFromFile(s, "InPDB", stdin, stdout, 0);
        info->InPDB = stringGetNthWord(s, 1, " ,\t");
        info->flagInPDB++;
    }
    if(info->flagInPDB) {
        info->fptInPDB = fileOpen(info->InPDB, "r");
    }
    
    if(!info->flagInMRC) {
        stringGetFromFile(s, "InMRC", stdin, stdout, 0);
        info->InMRC = stringGetNthWord(s, 1, " ,\t");
        info->flagInMRC++;
    }
    if(info->flagInMRC) {
        info->fptInMRC = fileOpen(info->InMRC, "r");
    }
    
    if(!info->flagContour) {
        stringGetFromFile(s, "Contour", stdin, stdout, 0);
        info->Contour = stringGetNthRealData(s, 1, ", \t");
        info->flagContour++;
    }
    if(info->flagContour) {
    }
    
    if(info->flagContourMode) {
    }
    
    if(info->flagOutMRC) {
        info->fptOutMRC = fileOpen(info->OutMRC, "w");
    }
    
    if(info->flagOutTxt) {
        info->fptOutTxt = fileOpen(info->OutTxt, "w");
    }
    
    if(info->flagOutPDB) {
        info->fptOutPDB = fileOpen(info->OutPDB, "w");
    }
    
    if(info->flagxmin) {
    }
    
    if(info->flagxmax) {
    }
    
    if(info->flagxDelta) {
    }
    
    if(info->flagymin) {
    }
    
    if(info->flagymax) {
    }
    
    if(info->flagyDelta) {
    }
    
    if(info->flagzmin) {
    }
    
    if(info->flagzmax) {
    }
    
    if(info->flagzDelta) {
    }
    
    if(info->flagEulerAngle) {
    }
    
    if(info->flagphimin) {
    }
    
    if(info->flagphimax) {
    }
    
    if(info->flagphiDelta) {
    }
    
    if(info->flagpsimin) {
    }
    
    if(info->flagpsimax) {
    }
    
    if(info->flagpsiDelta) {
    }
    
    if(info->flagthetamin) {
    }
    
    if(info->flagthetamax) {
    }
    
    if(info->flagthetaDelta) {
    }
    
    if(info->flagsurfaceMode) {
    }
    
    if(info->flagorder) {
    }
    
    if(info->flagrefine) {
    }
    
    if(info->flagsize) {
    }
    
    if(info->flagweight) {
    }
    
    if(info->flagmergin) {
    }
    
    if(info->flagthresHold) {
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
    sprintf(panepath, "%s/src/Tools/pdbUtil/pdbShapeFit/src/pdbShapeFit.pane", eospath);
    khoros_initialize(argc, argv, "EOS");
    fpt = fopen(panepath, "r");    if(NULL!=fpt) {
        fclose(fpt);
        kclui_initialize(panepath, KGEN_NONE, "EOS", "pdbShapeFit",
                     func_usage_additions,
                     func_get_args,
                     func_free_args);
    }
}
#endif /* KHOROS */ 
