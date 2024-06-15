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
init0(mrcImageMultiCTFCompensationInfo* info)
{
    info->fptIn     = stdin;    info->fptInList = stdin;    info->flagIn = 0;
    info->fptCTF     = stdin;    info->fptCTFList = stdin;    info->flagCTF = 0;
    info->fptOut = stdout;    info->flagOut = 0;
    info->fptfftOut = stdout;    info->flagfftOut = 0;
    info->WhiteNoise = 1.0;    info->flagWhiteNoise = 0;
    info->WhiteNoiseRaising = 1.0;    info->flagWhiteNoiseRaising = 0;
    info->MaxWhiteNoise = 1.0;    info->flagMaxWhiteNoise = 0;
    info->NdependentWhiteNoise = 1;    info->flagNdependentWhiteNoise = 0;
    info->SinWinRmin = 0.1;    info->flagSinWinRmin = 0;
    info->SinWinRmax = 1.0;    info->flagSinWinRmax = 0;
    info->MaxIter = 10;    info->flagMaxIter = 0;
    info->CTFMode = 1;    info->flagCTFMode = 0;
    info->solventMode = 0;    info->flagsolventMode = 0;
    info->solventSTD = -1.0;    info->flagsolventSTD = 0;
    info->fptLog = stderr;    info->flagLog = 0;
    info->fptconfigFile = NULL;    info->flagconfigFile = 0;
    info->mode = 0;    info->flagmode = 0;
}

void
init1(mrcImageMultiCTFCompensationInfo* info)
{
    char s[1024];
    int i;
    if(!info->flagIn) {
        stringGetFromFile(s, "In", stdin, stdout, 0);
        info->InList = stringGetNthWord(s, 1, " ,\t");
        info->flagIn++;
    }
    if(info->flagIn) {
        info->fptInList = fileOpen(info->InList, "r");
        fseek(info->fptInList, 0L, SEEK_SET);
        i=0;
        while(NULL!=stringGetFromFile(s, "", info->fptInList, stdout, 1)) {
            i++;
        }
        info->fptIn = (FILE**)memoryAllocate(i*sizeof(FILE*), "in init1");
        info->In    = (char**)memoryAllocate(i*sizeof(char*), "in init1");
        info->flagIn = i;
        fseek(info->fptInList, 0L, SEEK_SET);
        i=0;
        while(NULL!=stringGetFromFile(s, "", info->fptInList, stdout, 1)) {
            info->In[i] = stringGetNthWord(s, 1, " ,\t");
            info->fptIn[i] = fileOpen(info->In[i],"r");
            i++;
        }
    }
    
    if(info->flagCTF) {
        info->fptCTFList = fileOpen(info->CTFList, "r");
        fseek(info->fptCTFList, 0L, SEEK_SET);
        i=0;
        while(NULL!=stringGetFromFile(s, "", info->fptCTFList, stdout, 1)) {
            i++;
        }
        info->fptCTF = (FILE**)memoryAllocate(i*sizeof(FILE*), "in init1");
        info->CTF    = (char**)memoryAllocate(i*sizeof(char*), "in init1");
        info->flagCTF = i;
        fseek(info->fptCTFList, 0L, SEEK_SET);
        i=0;
        while(NULL!=stringGetFromFile(s, "", info->fptCTFList, stdout, 1)) {
            info->CTF[i] = stringGetNthWord(s, 1, " ,\t");
            info->fptCTF[i] = fileOpen(info->CTF[i],"r");
            i++;
        }
    }
    
    if(!info->flagOut) {
        stringGetFromFile(s, "Out", stdin, stdout, 0);
        info->Out = stringGetNthWord(s, 1, " ,\t");
        info->flagOut++;
    }
    if(info->flagOut) {
        info->fptOut = fileOpen(info->Out, "w");
    }
    
    if(info->flagfftOut) {
        info->fptfftOut = fileOpen(info->fftOut, "w");
    }
    
    if(info->flagWhiteNoise) {
    }
    
    if(info->flagWhiteNoiseRaising) {
    }
    
    if(info->flagMaxWhiteNoise) {
    }
    
    if(info->flagNdependentWhiteNoise) {
    }
    
    if(info->flagSinWinRmin) {
    }
    
    if(info->flagSinWinRmax) {
    }
    
    if(info->flagMaxIter) {
    }
    
    if(info->flagCTFMode) {
    }
    
    if(info->flagsolventMode) {
    }
    
    if(info->flagsolventSTD) {
    }
    
    if(info->flagLog) {
        info->fptLog = fileOpen(info->Log, "w");
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
    sprintf(panepath, "%s/src/Tools/mrcImage/mrcImageMultiCTFCompensation/src/mrcImageMultiCTFCompensation.pane", eospath);
    khoros_initialize(argc, argv, "EOS");
    fpt = fopen(panepath, "r");    if(NULL!=fpt) {
        fclose(fpt);
        kclui_initialize(panepath, KGEN_NONE, "EOS", "mrcImageMultiCTFCompensation",
                     func_usage_additions,
                     func_get_args,
                     func_free_args);
    }
}
#endif /* KHOROS */ 
