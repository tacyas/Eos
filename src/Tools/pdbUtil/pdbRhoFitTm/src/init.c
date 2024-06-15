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
init0(pdbRhoFitTmInfo* info)
{
    info->fptInPdb = NULL;    info->flagInPdb = 0;
    info->fptInMrc = NULL;    info->flagInMrc = 0;
    info->fptOutMrc = NULL;    info->flagOutMrc = 0;
    info->Sx = 50;    info->flagSx = 0;
    info->Sy = 110;    info->flagSy = 0;
    info->Sz = 110;    info->flagSz = 0;
    info->fptOutTxt = NULL;    info->flagOutTxt = 0;
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
    info->normalizeWeight = 100000000.0;    info->flagnormalizeWeight = 0;
    info->normalizeContour = 0.0;    info->flagnormalizeContour = 0;
    info->Inverse=0;
    info->Zminus=0;
    info->Tfactor=0;
    info->Tlim = 60;    info->flagTlim = 0;
    info->Centre=0;
    info->fptconfigFile = NULL;    info->flagconfigFile = 0;
    info->mode = 0;    info->flagmode = 0;
    info->contourLevel = NULL;    info->flagcontourLevel = 0;
}

void
init1(pdbRhoFitTmInfo* info)
{
    char s[1024];
    int i;
    if(!info->flagInPdb) {
        stringGetFromFile(s, "InPdb", stdin, stdout, 0);
        info->InPdb = stringGetNthWord(s, 1, " ,\t");
        info->flagInPdb++;
    }
    if(info->flagInPdb) {
        info->fptInPdb = fileOpen(info->InPdb, "r");
    }
    
    if(!info->flagInMrc) {
        stringGetFromFile(s, "InMrc", stdin, stdout, 0);
        info->InMrc = stringGetNthWord(s, 1, " ,\t");
        info->flagInMrc++;
    }
    if(info->flagInMrc) {
        info->fptInMrc = fileOpen(info->InMrc, "r");
    }
    
    if(!info->flagOutMrc) {
        stringGetFromFile(s, "OutMrc", stdin, stdout, 0);
        info->OutMrc = stringGetNthWord(s, 1, " ,\t");
        info->flagOutMrc++;
    }
    if(info->flagOutMrc) {
        info->fptOutMrc = fileOpen(info->OutMrc, "w");
    }
    
    if(!info->flagSx) {
        stringGetFromFile(s, "Sx", stdin, stdout, 0);
        info->Sx = stringGetNthRealData(s, 1, ", \t");
        info->flagSx++;
    }
    if(info->flagSx) {
    }
    
    if(!info->flagSy) {
        stringGetFromFile(s, "Sy", stdin, stdout, 0);
        info->Sy = stringGetNthRealData(s, 1, ", \t");
        info->flagSy++;
    }
    if(info->flagSy) {
    }
    
    if(!info->flagSz) {
        stringGetFromFile(s, "Sz", stdin, stdout, 0);
        info->Sz = stringGetNthRealData(s, 1, ", \t");
        info->flagSz++;
    }
    if(info->flagSz) {
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
    
    if(info->flagnormalizeWeight) {
    }
    
    if(info->flagnormalizeContour) {
    }
    
    if(info->flagTlim) {
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
    sprintf(panepath, "%s/src/Tools/pdbUtil/pdbRhoFitTm/src/pdbRhoFitTm.pane", eospath);
    khoros_initialize(argc, argv, "EOS");
    fpt = fopen(panepath, "r");    if(NULL!=fpt) {
        fclose(fpt);
        kclui_initialize(panepath, KGEN_NONE, "EOS", "pdbRhoFitTm",
                     func_usage_additions,
                     func_get_args,
                     func_free_args);
    }
}
#endif /* KHOROS */ 
