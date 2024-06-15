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
init0(mrcMultiFFTCentralSectionsSigmaCalcInfo* info)
{
    info->fptIn = NULL;    info->flagIn = 0;
    info->PathIn = stringGetNthWord("./", 1, "\0");    info->flagPathIn = 0;
    info->fptInLikelihood     = NULL;    info->fptInLikelihoodList = NULL;    info->flagInLikelihood = 0;
    info->PathL = stringGetNthWord("./", 1, "\0");    info->flagPathL = 0;
    info->fptIn3D     = NULL;    info->fptIn3DList = NULL;    info->flagIn3D = 0;
    info->Path3D = stringGetNthWord("./", 1, "\0");    info->flagPath3D = 0;
    info->fptOut = NULL;    info->flagOut = 0;
    info->EulerMode = stringGetNthWord("YOYS", 1, "\0");    info->flagEulerMode = 0;
    info->Rot1Start = 0.0;    info->flagRot1Start = 0;
    info->Rot1End = 360.0;    info->flagRot1End = 0;
    info->Rot1Delta = 10;    info->flagRot1Delta = 0;
    info->Rot2Start = 0.0;    info->flagRot2Start = 0;
    info->Rot2End = 360.0;    info->flagRot2End = 0;
    info->Rot2Delta = 10;    info->flagRot2Delta = 0;
    info->Rot3Start = 0.0;    info->flagRot3Start = 0;
    info->Rot3End = 360.0;    info->flagRot3End = 0;
    info->Rot3Delta = 10;    info->flagRot3Delta = 0;
    info->TransX = 0.0;    info->flagTransX = 0;
    info->TransY = 0.0;    info->flagTransY = 0;
    info->InterpMode = 0;    info->flagInterpMode = 0;
    info->fptconfigFile = NULL;    info->flagconfigFile = 0;
    info->mode = 0;    info->flagmode = 0;
}

void
init1(mrcMultiFFTCentralSectionsSigmaCalcInfo* info)
{
    char s[1024];
    int i;
    if(!info->flagIn) {
        stringGetFromFile(s, "In", stdin, stdout, 0);
        info->In = stringGetNthWord(s, 1, " ,\t");
        info->flagIn++;
    }
    if(info->flagIn) {
    }
    
    if(!info->flagPathIn) {
        stringGetFromFile(s, "PathIn", stdin, stdout, 0);
        info->PathIn = stringGetNthWord(s, 1, " ,\t");
        info->flagPathIn++;
    }
    if(info->flagPathIn) {
    }
    
    if(!info->flagInLikelihood) {
        stringGetFromFile(s, "InLikelihood", stdin, stdout, 0);
        info->InLikelihoodList = stringGetNthWord(s, 1, " ,\t");
        info->flagInLikelihood++;
    }
    if(info->flagInLikelihood) {
        info->fptInLikelihoodList = fileOpen(info->InLikelihoodList, "r");
        fseek(info->fptInLikelihoodList, 0L, SEEK_SET);
        i=0;
        while(NULL!=stringGetFromFile(s, "", info->fptInLikelihoodList, stdout, 1)) {
            i++;
        }
        info->fptInLikelihood = (FILE**)memoryAllocate(i*sizeof(FILE*), "in init1");
        info->InLikelihood    = (char**)memoryAllocate(i*sizeof(char*), "in init1");
        info->flagInLikelihood = i;
        fseek(info->fptInLikelihoodList, 0L, SEEK_SET);
        i=0;
        while(NULL!=stringGetFromFile(s, "", info->fptInLikelihoodList, stdout, 1)) {
            info->InLikelihood[i] = stringGetNthWord(s, 1, " ,\t");
            i++;
        }
    }
    
    if(!info->flagPathL) {
        stringGetFromFile(s, "PathL", stdin, stdout, 0);
        info->PathL = stringGetNthWord(s, 1, " ,\t");
        info->flagPathL++;
    }
    if(info->flagPathL) {
    }
    
    if(!info->flagIn3D) {
        stringGetFromFile(s, "In3D", stdin, stdout, 0);
        info->In3DList = stringGetNthWord(s, 1, " ,\t");
        info->flagIn3D++;
    }
    if(info->flagIn3D) {
        info->fptIn3DList = fileOpen(info->In3DList, "r");
        fseek(info->fptIn3DList, 0L, SEEK_SET);
        i=0;
        while(NULL!=stringGetFromFile(s, "", info->fptIn3DList, stdout, 1)) {
            i++;
        }
        info->fptIn3D = (FILE**)memoryAllocate(i*sizeof(FILE*), "in init1");
        info->In3D    = (char**)memoryAllocate(i*sizeof(char*), "in init1");
        info->flagIn3D = i;
        fseek(info->fptIn3DList, 0L, SEEK_SET);
        i=0;
        while(NULL!=stringGetFromFile(s, "", info->fptIn3DList, stdout, 1)) {
            info->In3D[i] = stringGetNthWord(s, 1, " ,\t");
            i++;
        }
    }
    
    if(!info->flagPath3D) {
        stringGetFromFile(s, "Path3D", stdin, stdout, 0);
        info->Path3D = stringGetNthWord(s, 1, " ,\t");
        info->flagPath3D++;
    }
    if(info->flagPath3D) {
    }
    
    if(!info->flagOut) {
        stringGetFromFile(s, "Out", stdin, stdout, 0);
        info->Out = stringGetNthWord(s, 1, " ,\t");
        info->flagOut++;
    }
    if(info->flagOut) {
        info->fptOut = fileOpen(info->Out, "w");
    }
    
    if(info->flagEulerMode) {
    }
    
    if(info->flagRot1Start) {
    }
    
    if(info->flagRot1End) {
    }
    
    if(info->flagRot1Delta) {
    }
    
    if(info->flagRot2Start) {
    }
    
    if(info->flagRot2End) {
    }
    
    if(info->flagRot2Delta) {
    }
    
    if(info->flagRot3Start) {
    }
    
    if(info->flagRot3End) {
    }
    
    if(info->flagRot3Delta) {
    }
    
    if(info->flagTransX) {
    }
    
    if(info->flagTransY) {
    }
    
    if(info->flagInterpMode) {
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
    sprintf(panepath, "%s/src/Tools/mrcImage/mrcMultiFFTCentralSectionsSigmaCalc/src/mrcMultiFFTCentralSectionsSigmaCalc.pane", eospath);
    khoros_initialize(argc, argv, "EOS");
    fpt = fopen(panepath, "r");    if(NULL!=fpt) {
        fclose(fpt);
        kclui_initialize(panepath, KGEN_NONE, "EOS", "mrcMultiFFTCentralSectionsSigmaCalc",
                     func_usage_additions,
                     func_get_args,
                     func_free_args);
    }
}
#endif /* KHOROS */ 
