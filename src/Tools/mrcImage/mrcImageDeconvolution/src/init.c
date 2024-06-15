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
init0(mrcImageDeconvolutionInfo* info)
{
    info->fptIn = NULL;    info->flagIn = 0;
    info->fptKernel = NULL;    info->flagKernel = 0;
    info->KernelCentre = 1;    info->flagKernelCentre = 0;
    info->fptOut = NULL;    info->flagOut = 0;
    info->fptOutConv = NULL;    info->flagOutConv = 0;
    info->fptOutASCII = stdout;    info->flagOutASCII = 0;
    info->fptOutRMSD = NULL;    info->flagOutRMSD = 0;
    info->thresCTF = 1e-4;    info->flagthresCTF = 0;
    info->NSRatio = 0.0;    info->flagNSRatio = 0;
    info->NSCoeff = 0.0;    info->flagNSCoeff = 0;
    info->Pad3DMode = 1;    info->flagPad3DMode = 0;
    info->r = 0;    info->flagr = 0;
    info->w = 1;    info->flagw = 0;
    info->v = 0;    info->flagv = 0;
    info->Floating=0;
    info->maxIter = 0;    info->flagmaxIter = 0;
    info->minRMSD = 0.0;    info->flagminRMSD = 0;
    info->lambda = 0.5;    info->flaglambda = 0;
    info->fptconfigFile = NULL;    info->flagconfigFile = 0;
    info->mode = 0;    info->flagmode = 0;
}

void
init1(mrcImageDeconvolutionInfo* info)
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
    
    if(!info->flagKernel) {
        stringGetFromFile(s, "Kernel", stdin, stdout, 0);
        info->Kernel = stringGetNthWord(s, 1, " ,\t");
        info->flagKernel++;
    }
    if(info->flagKernel) {
        info->fptKernel = fileOpen(info->Kernel, "r");
    }
    
    if(info->flagKernelCentre) {
    }
    
    if(!info->flagOut) {
        stringGetFromFile(s, "Out", stdin, stdout, 0);
        info->Out = stringGetNthWord(s, 1, " ,\t");
        info->flagOut++;
    }
    if(info->flagOut) {
        info->fptOut = fileOpen(info->Out, "w");
    }
    
    if(info->flagOutConv) {
        info->fptOutConv = fileOpen(info->OutConv, "w");
    }
    
    if(info->flagOutASCII) {
        info->fptOutASCII = fileOpen(info->OutASCII, "w");
    }
    
    if(info->flagOutRMSD) {
        info->fptOutRMSD = fileOpen(info->OutRMSD, "w");
    }
    
    if(info->flagthresCTF) {
    }
    
    if(info->flagNSRatio) {
    }
    
    if(info->flagNSCoeff) {
    }
    
    if(info->flagPad3DMode) {
    }
    
    if(info->flagr) {
    }
    
    if(info->flagw) {
    }
    
    if(info->flagv) {
    }
    
    if(info->flagmaxIter) {
    }
    
    if(info->flagminRMSD) {
    }
    
    if(info->flaglambda) {
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
    sprintf(panepath, "%s/src/Tools/mrcImage/mrcImageDeconvolution/src/mrcImageDeconvolution.pane", eospath);
    khoros_initialize(argc, argv, "EOS");
    fpt = fopen(panepath, "r");    if(NULL!=fpt) {
        fclose(fpt);
        kclui_initialize(panepath, KGEN_NONE, "EOS", "mrcImageDeconvolution",
                     func_usage_additions,
                     func_get_args,
                     func_free_args);
    }
}
#endif /* KHOROS */ 
