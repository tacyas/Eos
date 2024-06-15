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
init0(mrcImageCTFDeterminationInfo* info)
{
    info->fptIn = NULL;    info->flagIn = 0;
    info->fptRef = NULL;    info->flagRef = 0;
    info->fptOut = stdout;    info->flagOut = 0;
    info->fptOut2 = NULL;    info->flagOut2 = 0;
    info->fptOutC = NULL;    info->flagOutC = 0;
    info->fptOutF = NULL;    info->flagOutF = 0;
    info->kV = 200;    info->flagkV = 0;
    info->Cs = 2.1;    info->flagCs = 0;
    info->Ain = 0.02;    info->flagAin = 0;
    info->WhiteNoise = 1.0;    info->flagWhiteNoise = 0;
    info->mindf = 0.0;    info->flagmindf = 0;
    info->maxdf = 200000;    info->flagmaxdf = 0;
    info->deldf = 1000;    info->flagdeldf = 0;
    info->minAoverP = 0.0;    info->flagminAoverP = 0;
    info->maxAoverP = 1.0;    info->flagmaxAoverP = 0;
    info->delAoverP = 0.01;    info->flagdelAoverP = 0;
    info->Rmin = 0.0;    info->flagRmin = 0;
    info->Rmax = 0.1;    info->flagRmax = 0;
    info->fptconfigFile = NULL;    info->flagconfigFile = 0;
    info->mF = 1;    info->flagmF = 0;
    info->mW = 0;    info->flagmW = 0;
    info->mS = 0;    info->flagmS = 0;
    info->mC = 0;    info->flagmC = 0;
    info->M = 0;    info->flagM = 0;
    info->PixelSize = 5;    info->flagPixelSize = 0;
    info->Width = 120;    info->flagWidth = 0;
    info->truePitch = 430;    info->flagtruePitch = 0;
    info->firstDf = 70000;    info->flagfirstDf = 0;
    info->withinDf = 1000;    info->flagwithinDf = 0;
    info->firstAoverP = 0.05;    info->flagfirstAoverP = 0;
    info->withinAoverP = 0.01;    info->flagwithinAoverP = 0;
    info->maxiter = 10;    info->flagmaxiter = 0;
    info->mode = 0;    info->flagmode = 0;
}

void
init1(mrcImageCTFDeterminationInfo* info)
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
    
    if(!info->flagRef) {
        stringGetFromFile(s, "Ref", stdin, stdout, 0);
        info->Ref = stringGetNthWord(s, 1, " ,\t");
        info->flagRef++;
    }
    if(info->flagRef) {
        info->fptRef = fileOpen(info->Ref, "r");
    }
    
    if(info->flagOut) {
        info->fptOut = fileOpen(info->Out, "w");
    }
    
    if(info->flagOut2) {
        info->fptOut2 = fileOpen(info->Out2, "w");
    }
    
    if(info->flagOutC) {
        info->fptOutC = fileOpen(info->OutC, "w");
    }
    
    if(info->flagOutF) {
        info->fptOutF = fileOpen(info->OutF, "w");
    }
    
    if(info->flagkV) {
    }
    
    if(info->flagCs) {
    }
    
    if(info->flagAin) {
    }
    
    if(info->flagWhiteNoise) {
    }
    
    if(info->flagmindf) {
    }
    
    if(info->flagmaxdf) {
    }
    
    if(info->flagdeldf) {
    }
    
    if(info->flagminAoverP) {
    }
    
    if(info->flagmaxAoverP) {
    }
    
    if(info->flagdelAoverP) {
    }
    
    if(info->flagRmin) {
    }
    
    if(info->flagRmax) {
    }
    
    if(info->flagconfigFile) {
        info->fptconfigFile = fileOpen(info->configFile, "r");
    }
    
    if(info->flagmF) {
    }
    
    if(info->flagmW) {
    }
    
    if(info->flagmS) {
    }
    
    if(info->flagmC) {
    }
    
    if(info->flagM) {
    }
    
    if(info->flagPixelSize) {
    }
    
    if(info->flagWidth) {
    }
    
    if(info->flagtruePitch) {
    }
    
    if(info->flagfirstDf) {
    }
    
    if(info->flagwithinDf) {
    }
    
    if(info->flagfirstAoverP) {
    }
    
    if(info->flagwithinAoverP) {
    }
    
    if(info->flagmaxiter) {
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
    sprintf(panepath, "%s/src/Tools/mrcImage/mrcImageCTFDetermination/src/mrcImageCTFDetermination.pane", eospath);
    khoros_initialize(argc, argv, "EOS");
    fpt = fopen(panepath, "r");    if(NULL!=fpt) {
        fclose(fpt);
        kclui_initialize(panepath, KGEN_NONE, "EOS", "mrcImageCTFDetermination",
                     func_usage_additions,
                     func_get_args,
                     func_free_args);
    }
}
#endif /* KHOROS */ 
