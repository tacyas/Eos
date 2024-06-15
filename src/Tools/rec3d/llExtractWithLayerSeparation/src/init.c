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
init0(llExtractWithLayerSeparationInfo* info)
{
    info->fptIn     = NULL;    info->fptInList = NULL;    info->flagIn = 0;
    info->fptInLLNea     = NULL;    info->fptInLLNeaList = NULL;    info->flagInLLNea = 0;
    info->fptInLLFar     = NULL;    info->fptInLLFarList = NULL;    info->flagInLLFar = 0;
    info->fptRef = NULL;    info->flagRef = 0;
    info->fptOut = NULL;    info->flagOut = 0;
    info->fptOut2     = NULL;    info->fptOut2List = NULL;    info->flagOut2 = 0;
    info->fptOut3     = NULL;    info->fptOut3List = NULL;    info->flagOut3 = 0;
    info->fptOut4     = NULL;    info->fptOut4List = NULL;    info->flagOut4 = 0;
    info->fptOut5     = NULL;    info->fptOut5List = NULL;    info->flagOut5 = 0;
    info->fptOut6     = NULL;    info->fptOut6List = NULL;    info->flagOut6 = 0;
    info->fptOut7 = NULL;    info->flagOut7 = 0;
    info->fptOut8 = NULL;    info->flagOut8 = 0;
    info->fptOut9     = NULL;    info->fptOut9List = NULL;    info->flagOut9 = 0;
    info->InComment = stringGetNthWord("NULL", 1, "\0");    info->flagInComment = 0;
    info->symmetry = 1.0;    info->flagsymmetry = 0;
    info->fptllInfo     = NULL;    info->fptllInfoList = NULL;    info->flagllInfo = 0;
    info->fptllInfoFinal = NULL;    info->flagllInfoFinal = 0;
    info->fptllInfoImp     = NULL;    info->fptllInfoImpList = NULL;    info->flagllInfoImp = 0;
    info->liWeight = 1.0;    info->flagliWeight = 0;
    info->liWeightStart = 1.0;    info->flagliWeightStart = 0;
    info->liWeightStep = 1.0;    info->flagliWeightStep = 0;
    info->fptllInfoAxis     = NULL;    info->fptllInfoAxisList = NULL;    info->flagllInfoAxis = 0;
    info->laWeight = 1.0;    info->flaglaWeight = 0;
    info->laWeightStart = 1.0;    info->flaglaWeightStart = 0;
    info->laWeightStep = 1.0;    info->flaglaWeightStep = 0;
    info->truePitch = 430.0;    info->flagtruePitch = 0;
    info->rMax = 100.0;    info->flagrMax = 0;
    info->rMaxMin = 100.0;    info->flagrMaxMin = 0;
    info->RMax = 0.1;    info->flagRMax = 0;
    info->RMaxFirst = 0.04;    info->flagRMaxFirst = 0;
    info->RMaxStep = 0.02;    info->flagRMaxStep = 0;
    info->RRMax = 0.1;    info->flagRRMax = 0;
    info->RRMaxFirst = 0.04;    info->flagRRMaxFirst = 0;
    info->RRMaxStep = 0.02;    info->flagRRMaxStep = 0;
    info->delBR = 0.0002;    info->flagdelBR = 0;
    info->rms = 1e-6;    info->flagrms = 0;
    info->narrowSearch = 1.0;    info->flagnarrowSearch = 0;
    info->nextTimes = 1e-4;    info->flagnextTimes = 0;
    info->MaxIteration = 10;    info->flagMaxIteration = 0;
    info->MaxIter2 = 1;    info->flagMaxIter2 = 0;
    info->MaxIter3 = 1;    info->flagMaxIter3 = 0;
    info->lambda = 1.0;    info->flaglambda = 0;
    info->CTF = 0;    info->flagCTF = 0;
    info->WhiteNoise = 0.0;    info->flagWhiteNoise = 0;
    info->below = 90.0;    info->flagbelow = 0;
    info->noantipole=0;
    info->magLimit=0;
    info->eachTime=0;
    info->fptContinue = NULL;    info->flagContinue = 0;
    info->fptForContinue = NULL;    info->flagForContinue = 0;
    info->phimin = 0.0;    info->flagphimin = 0;
    info->phimax = 360.0;    info->flagphimax = 0;
    info->delphi = 10.0;    info->flagdelphi = 0;
    info->zmin = 0.0;    info->flagzmin = 0;
    info->zmax = 30.0;    info->flagzmax = 0;
    info->delz = 5.0;    info->flagdelz = 0;
    info->shiftmin = -10.0;    info->flagshiftmin = 0;
    info->shiftmax = 10.0;    info->flagshiftmax = 0;
    info->delshift = 1.0;    info->flagdelshift = 0;
    info->fptLog = stdout;    info->flagLog = 0;
    info->Normalization=0;
    info->pvm = 0;    info->flagpvm = 0;
    info->fptpvmList = NULL;    info->flagpvmList = 0;
    info->pvmServer=0;
    info->pvmClient=0;
    info->WorkingDir = stringGetNthWord("./", 1, "\0");    info->flagWorkingDir = 0;
    info->fptconfigFile = NULL;    info->flagconfigFile = 0;
    info->mode = 0;    info->flagmode = 0;
}

void
init1(llExtractWithLayerSeparationInfo* info)
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
            i++;
        }
    }
    
    if(info->flagInLLNea) {
        info->fptInLLNeaList = fileOpen(info->InLLNeaList, "r");
        fseek(info->fptInLLNeaList, 0L, SEEK_SET);
        i=0;
        while(NULL!=stringGetFromFile(s, "", info->fptInLLNeaList, stdout, 1)) {
            i++;
        }
        info->fptInLLNea = (FILE**)memoryAllocate(i*sizeof(FILE*), "in init1");
        info->InLLNea    = (char**)memoryAllocate(i*sizeof(char*), "in init1");
        info->flagInLLNea = i;
        fseek(info->fptInLLNeaList, 0L, SEEK_SET);
        i=0;
        while(NULL!=stringGetFromFile(s, "", info->fptInLLNeaList, stdout, 1)) {
            info->InLLNea[i] = stringGetNthWord(s, 1, " ,\t");
            i++;
        }
    }
    
    if(info->flagInLLFar) {
        info->fptInLLFarList = fileOpen(info->InLLFarList, "r");
        fseek(info->fptInLLFarList, 0L, SEEK_SET);
        i=0;
        while(NULL!=stringGetFromFile(s, "", info->fptInLLFarList, stdout, 1)) {
            i++;
        }
        info->fptInLLFar = (FILE**)memoryAllocate(i*sizeof(FILE*), "in init1");
        info->InLLFar    = (char**)memoryAllocate(i*sizeof(char*), "in init1");
        info->flagInLLFar = i;
        fseek(info->fptInLLFarList, 0L, SEEK_SET);
        i=0;
        while(NULL!=stringGetFromFile(s, "", info->fptInLLFarList, stdout, 1)) {
            info->InLLFar[i] = stringGetNthWord(s, 1, " ,\t");
            i++;
        }
    }
    
    if(info->flagRef) {
        info->fptRef = fileOpen(info->Ref, "r");
    }
    
    if(!info->flagOut) {
        stringGetFromFile(s, "Out", stdin, stdout, 0);
        info->Out = stringGetNthWord(s, 1, " ,\t");
        info->flagOut++;
    }
    if(info->flagOut) {
        info->fptOut = fileOpen(info->Out, "w");
    }
    
    if(info->flagOut2) {
        info->fptOut2List = fileOpen(info->Out2List, "r");
        fseek(info->fptOut2List, 0L, SEEK_SET);
        i=0;
        while(NULL!=stringGetFromFile(s, "", info->fptOut2List, stdout, 1)) {
            i++;
        }
        info->fptOut2 = (FILE**)memoryAllocate(i*sizeof(FILE*), "in init1");
        info->Out2    = (char**)memoryAllocate(i*sizeof(char*), "in init1");
        info->flagOut2 = i;
        fseek(info->fptOut2List, 0L, SEEK_SET);
        i=0;
        while(NULL!=stringGetFromFile(s, "", info->fptOut2List, stdout, 1)) {
            info->Out2[i] = stringGetNthWord(s, 1, " ,\t");
            i++;
        }
    }
    
    if(info->flagOut3) {
        info->fptOut3List = fileOpen(info->Out3List, "r");
        fseek(info->fptOut3List, 0L, SEEK_SET);
        i=0;
        while(NULL!=stringGetFromFile(s, "", info->fptOut3List, stdout, 1)) {
            i++;
        }
        info->fptOut3 = (FILE**)memoryAllocate(i*sizeof(FILE*), "in init1");
        info->Out3    = (char**)memoryAllocate(i*sizeof(char*), "in init1");
        info->flagOut3 = i;
        fseek(info->fptOut3List, 0L, SEEK_SET);
        i=0;
        while(NULL!=stringGetFromFile(s, "", info->fptOut3List, stdout, 1)) {
            info->Out3[i] = stringGetNthWord(s, 1, " ,\t");
            i++;
        }
    }
    
    if(info->flagOut4) {
        info->fptOut4List = fileOpen(info->Out4List, "r");
        fseek(info->fptOut4List, 0L, SEEK_SET);
        i=0;
        while(NULL!=stringGetFromFile(s, "", info->fptOut4List, stdout, 1)) {
            i++;
        }
        info->fptOut4 = (FILE**)memoryAllocate(i*sizeof(FILE*), "in init1");
        info->Out4    = (char**)memoryAllocate(i*sizeof(char*), "in init1");
        info->flagOut4 = i;
        fseek(info->fptOut4List, 0L, SEEK_SET);
        i=0;
        while(NULL!=stringGetFromFile(s, "", info->fptOut4List, stdout, 1)) {
            info->Out4[i] = stringGetNthWord(s, 1, " ,\t");
            i++;
        }
    }
    
    if(info->flagOut5) {
        info->fptOut5List = fileOpen(info->Out5List, "r");
        fseek(info->fptOut5List, 0L, SEEK_SET);
        i=0;
        while(NULL!=stringGetFromFile(s, "", info->fptOut5List, stdout, 1)) {
            i++;
        }
        info->fptOut5 = (FILE**)memoryAllocate(i*sizeof(FILE*), "in init1");
        info->Out5    = (char**)memoryAllocate(i*sizeof(char*), "in init1");
        info->flagOut5 = i;
        fseek(info->fptOut5List, 0L, SEEK_SET);
        i=0;
        while(NULL!=stringGetFromFile(s, "", info->fptOut5List, stdout, 1)) {
            info->Out5[i] = stringGetNthWord(s, 1, " ,\t");
            i++;
        }
    }
    
    if(info->flagOut6) {
        info->fptOut6List = fileOpen(info->Out6List, "r");
        fseek(info->fptOut6List, 0L, SEEK_SET);
        i=0;
        while(NULL!=stringGetFromFile(s, "", info->fptOut6List, stdout, 1)) {
            i++;
        }
        info->fptOut6 = (FILE**)memoryAllocate(i*sizeof(FILE*), "in init1");
        info->Out6    = (char**)memoryAllocate(i*sizeof(char*), "in init1");
        info->flagOut6 = i;
        fseek(info->fptOut6List, 0L, SEEK_SET);
        i=0;
        while(NULL!=stringGetFromFile(s, "", info->fptOut6List, stdout, 1)) {
            info->Out6[i] = stringGetNthWord(s, 1, " ,\t");
            i++;
        }
    }
    
    if(info->flagOut7) {
        info->fptOut7 = fileOpen(info->Out7, "w");
    }
    
    if(info->flagOut8) {
        info->fptOut8 = fileOpen(info->Out8, "w");
    }
    
    if(info->flagOut9) {
        info->fptOut9List = fileOpen(info->Out9List, "r");
        fseek(info->fptOut9List, 0L, SEEK_SET);
        i=0;
        while(NULL!=stringGetFromFile(s, "", info->fptOut9List, stdout, 1)) {
            i++;
        }
        info->fptOut9 = (FILE**)memoryAllocate(i*sizeof(FILE*), "in init1");
        info->Out9    = (char**)memoryAllocate(i*sizeof(char*), "in init1");
        info->flagOut9 = i;
        fseek(info->fptOut9List, 0L, SEEK_SET);
        i=0;
        while(NULL!=stringGetFromFile(s, "", info->fptOut9List, stdout, 1)) {
            info->Out9[i] = stringGetNthWord(s, 1, " ,\t");
            i++;
        }
    }
    
    if(info->flagInComment) {
    }
    
    if(info->flagsymmetry) {
    }
    
    if(!info->flagllInfo) {
        stringGetFromFile(s, "llInfo", stdin, stdout, 0);
        info->llInfoList = stringGetNthWord(s, 1, " ,\t");
        info->flagllInfo++;
    }
    if(info->flagllInfo) {
        info->fptllInfoList = fileOpen(info->llInfoList, "r");
        fseek(info->fptllInfoList, 0L, SEEK_SET);
        i=0;
        while(NULL!=stringGetFromFile(s, "", info->fptllInfoList, stdout, 1)) {
            i++;
        }
        info->fptllInfo = (FILE**)memoryAllocate(i*sizeof(FILE*), "in init1");
        info->llInfo    = (char**)memoryAllocate(i*sizeof(char*), "in init1");
        info->flagllInfo = i;
        fseek(info->fptllInfoList, 0L, SEEK_SET);
        i=0;
        while(NULL!=stringGetFromFile(s, "", info->fptllInfoList, stdout, 1)) {
            info->llInfo[i] = stringGetNthWord(s, 1, " ,\t");
            i++;
        }
    }
    
    if(info->flagllInfoFinal) {
        info->fptllInfoFinal = fileOpen(info->llInfoFinal, "r");
    }
    
    if(info->flagllInfoImp) {
        info->fptllInfoImpList = fileOpen(info->llInfoImpList, "r");
        fseek(info->fptllInfoImpList, 0L, SEEK_SET);
        i=0;
        while(NULL!=stringGetFromFile(s, "", info->fptllInfoImpList, stdout, 1)) {
            i++;
        }
        info->fptllInfoImp = (FILE**)memoryAllocate(i*sizeof(FILE*), "in init1");
        info->llInfoImp    = (char**)memoryAllocate(i*sizeof(char*), "in init1");
        info->flagllInfoImp = i;
        fseek(info->fptllInfoImpList, 0L, SEEK_SET);
        i=0;
        while(NULL!=stringGetFromFile(s, "", info->fptllInfoImpList, stdout, 1)) {
            info->llInfoImp[i] = stringGetNthWord(s, 1, " ,\t");
            i++;
        }
    }
    
    if(info->flagliWeight) {
    }
    
    if(info->flagliWeightStart) {
    }
    
    if(info->flagliWeightStep) {
    }
    
    if(info->flagllInfoAxis) {
        info->fptllInfoAxisList = fileOpen(info->llInfoAxisList, "r");
        fseek(info->fptllInfoAxisList, 0L, SEEK_SET);
        i=0;
        while(NULL!=stringGetFromFile(s, "", info->fptllInfoAxisList, stdout, 1)) {
            i++;
        }
        info->fptllInfoAxis = (FILE**)memoryAllocate(i*sizeof(FILE*), "in init1");
        info->llInfoAxis    = (char**)memoryAllocate(i*sizeof(char*), "in init1");
        info->flagllInfoAxis = i;
        fseek(info->fptllInfoAxisList, 0L, SEEK_SET);
        i=0;
        while(NULL!=stringGetFromFile(s, "", info->fptllInfoAxisList, stdout, 1)) {
            info->llInfoAxis[i] = stringGetNthWord(s, 1, " ,\t");
            i++;
        }
    }
    
    if(info->flaglaWeight) {
    }
    
    if(info->flaglaWeightStart) {
    }
    
    if(info->flaglaWeightStep) {
    }
    
    if(!info->flagtruePitch) {
        stringGetFromFile(s, "truePitch", stdin, stdout, 0);
        info->truePitch = stringGetNthRealData(s, 1, ", \t");
        info->flagtruePitch++;
    }
    if(info->flagtruePitch) {
    }
    
    if(!info->flagrMax) {
        stringGetFromFile(s, "rMax", stdin, stdout, 0);
        info->rMax = stringGetNthRealData(s, 1, ", \t");
        info->flagrMax++;
    }
    if(info->flagrMax) {
    }
    
    if(info->flagrMaxMin) {
    }
    
    if(info->flagRMax) {
    }
    
    if(info->flagRMaxFirst) {
    }
    
    if(info->flagRMaxStep) {
    }
    
    if(info->flagRRMax) {
    }
    
    if(info->flagRRMaxFirst) {
    }
    
    if(info->flagRRMaxStep) {
    }
    
    if(info->flagdelBR) {
    }
    
    if(info->flagrms) {
    }
    
    if(info->flagnarrowSearch) {
    }
    
    if(info->flagnextTimes) {
    }
    
    if(info->flagMaxIteration) {
    }
    
    if(info->flagMaxIter2) {
    }
    
    if(info->flagMaxIter3) {
    }
    
    if(info->flaglambda) {
    }
    
    if(info->flagCTF) {
    }
    
    if(info->flagWhiteNoise) {
    }
    
    if(info->flagbelow) {
    }
    
    if(info->flagContinue) {
        info->fptContinue = fileOpen(info->Continue, "r");
    }
    
    if(info->flagForContinue) {
        info->fptForContinue = fileOpen(info->ForContinue, "w");
    }
    
    if(info->flagphimin) {
    }
    
    if(info->flagphimax) {
    }
    
    if(info->flagdelphi) {
    }
    
    if(info->flagzmin) {
    }
    
    if(info->flagzmax) {
    }
    
    if(info->flagdelz) {
    }
    
    if(info->flagshiftmin) {
    }
    
    if(info->flagshiftmax) {
    }
    
    if(info->flagdelshift) {
    }
    
    if(info->flagLog) {
        info->fptLog = fileOpen(info->Log, "w");
    }
    
    if(info->flagpvm) {
    }
    
    if(info->flagpvmList) {
        info->fptpvmList = fileOpen(info->pvmList, "r");
    }
    
    if(info->flagWorkingDir) {
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
    sprintf(panepath, "%s/src/Tools/rec3d/llExtractWithLayerSeparation/src/llExtractWithLayerSeparation.pane", eospath);
    khoros_initialize(argc, argv, "EOS");
    fpt = fopen(panepath, "r");    if(NULL!=fpt) {
        fclose(fpt);
        kclui_initialize(panepath, KGEN_NONE, "EOS", "llExtractWithLayerSeparation",
                     func_usage_additions,
                     func_get_args,
                     func_free_args);
    }
}
#endif /* KHOROS */ 
