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
init0(mrcImageNeuralNetParticleLearningInfo* info)
{
    info->fptInPositive     = NULL;    info->fptInPositiveList = NULL;    info->flagInPositive = 0;
    info->fptInNegative     = NULL;    info->fptInNegativeList = NULL;    info->flagInNegative = 0;
    info->fptOut     = NULL;    info->fptOutList = NULL;    info->flagOut = 0;
    info->Bias = 1.0;    info->flagBias = 0;
    info->MaxCounter = 10;    info->flagMaxCounter = 0;
    info->EPS = 0.005;    info->flagEPS = 0;
    info->Lambda = 0.1;    info->flagLambda = 0;
    info->fptconfigFile = NULL;    info->flagconfigFile = 0;
    info->mode = 0;    info->flagmode = 0;
}

void
init1(mrcImageNeuralNetParticleLearningInfo* info)
{
    char s[1024];
    int i;
    if(!info->flagInPositive) {
        stringGetFromFile(s, "InPositive", stdin, stdout, 0);
        info->InPositiveList = stringGetNthWord(s, 1, " ,\t");
        info->flagInPositive++;
    }
    if(info->flagInPositive) {
        info->fptInPositiveList = fileOpen(info->InPositiveList, "r");
        fseek(info->fptInPositiveList, 0L, SEEK_SET);
        i=0;
        while(NULL!=stringGetFromFile(s, "", info->fptInPositiveList, stdout, 1)) {
            i++;
        }
        info->fptInPositive = (FILE**)memoryAllocate(i*sizeof(FILE*), "in init1");
        info->InPositive    = (char**)memoryAllocate(i*sizeof(char*), "in init1");
        info->flagInPositive = i;
        fseek(info->fptInPositiveList, 0L, SEEK_SET);
        i=0;
        while(NULL!=stringGetFromFile(s, "", info->fptInPositiveList, stdout, 1)) {
            info->InPositive[i] = stringGetNthWord(s, 1, " ,\t");
            info->fptInPositive[i] = fileOpen(info->InPositive[i],"r");
            i++;
        }
    }
    
    if(!info->flagInNegative) {
        stringGetFromFile(s, "InNegative", stdin, stdout, 0);
        info->InNegativeList = stringGetNthWord(s, 1, " ,\t");
        info->flagInNegative++;
    }
    if(info->flagInNegative) {
        info->fptInNegativeList = fileOpen(info->InNegativeList, "r");
        fseek(info->fptInNegativeList, 0L, SEEK_SET);
        i=0;
        while(NULL!=stringGetFromFile(s, "", info->fptInNegativeList, stdout, 1)) {
            i++;
        }
        info->fptInNegative = (FILE**)memoryAllocate(i*sizeof(FILE*), "in init1");
        info->InNegative    = (char**)memoryAllocate(i*sizeof(char*), "in init1");
        info->flagInNegative = i;
        fseek(info->fptInNegativeList, 0L, SEEK_SET);
        i=0;
        while(NULL!=stringGetFromFile(s, "", info->fptInNegativeList, stdout, 1)) {
            info->InNegative[i] = stringGetNthWord(s, 1, " ,\t");
            info->fptInNegative[i] = fileOpen(info->InNegative[i],"r");
            i++;
        }
    }
    
    if(!info->flagOut) {
        stringGetFromFile(s, "Out", stdin, stdout, 0);
        info->OutList = stringGetNthWord(s, 1, " ,\t");
        info->flagOut++;
    }
    if(info->flagOut) {
        info->fptOutList = fileOpen(info->OutList, "r");
        fseek(info->fptOutList, 0L, SEEK_SET);
        i=0;
        while(NULL!=stringGetFromFile(s, "", info->fptOutList, stdout, 1)) {
            i++;
        }
        info->fptOut = (FILE**)memoryAllocate(i*sizeof(FILE*), "in init1");
        info->Out    = (char**)memoryAllocate(i*sizeof(char*), "in init1");
        info->flagOut = i;
        fseek(info->fptOutList, 0L, SEEK_SET);
        i=0;
        while(NULL!=stringGetFromFile(s, "", info->fptOutList, stdout, 1)) {
            info->Out[i] = stringGetNthWord(s, 1, " ,\t");
            info->fptOut[i] = fileOpen(info->Out[i],"w");
            i++;
        }
    }
    
    if(info->flagBias) {
    }
    
    if(info->flagMaxCounter) {
    }
    
    if(info->flagEPS) {
    }
    
    if(info->flagLambda) {
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
    sprintf(panepath, "%s/src/Tools/pickup/mrcImageNeuralNetParticleLearning/src/mrcImageNeuralNetParticleLearning.pane", eospath);
    khoros_initialize(argc, argv, "EOS");
    fpt = fopen(panepath, "r");    if(NULL!=fpt) {
        fclose(fpt);
        kclui_initialize(panepath, KGEN_NONE, "EOS", "mrcImageNeuralNetParticleLearning",
                     func_usage_additions,
                     func_get_args,
                     func_free_args);
    }
}
#endif /* KHOROS */ 
