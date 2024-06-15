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
init0(energyTransferModelCheckInfo* info)
{
    info->fptIn = NULL;    info->flagIn = 0;
    info->fptOut = NULL;    info->flagOut = 0;
    info->fptPDB = NULL;    info->flagPDB = 0;
    info->fptPDBs     = NULL;    info->fptPDBsList = NULL;    info->flagPDBs = 0;
    info->PDBsWithInfo=0;
    info->sigma = 1.0;    info->flagsigma = 0;
    info->sigmaA = 1.0;    info->flagsigmaA = 0;
    info->fptMRC = NULL;    info->flagMRC = 0;
    info->fptMRCs     = NULL;    info->fptMRCsList = NULL;    info->flagMRCs = 0;
    info->MRCWithInfo=0;
    info->EContour = 10.;    info->flagEContour = 0;
    info->ENear = 1.;    info->flagENear = 0;
    info->ENearA = 1.;    info->flagENearA = 0;
    info->fptRest = NULL;    info->flagRest = 0;
    info->fptRests     = NULL;    info->fptRestsList = NULL;    info->flagRests = 0;
    info->Contour = 10.;    info->flagContour = 0;
    info->Near = 1.;    info->flagNear = 0;
    info->NearA = 1.;    info->flagNearA = 0;
    info->RestrictWithInfo=0;
    info->fptRestP = NULL;    info->flagRestP = 0;
    info->fptRestsP     = NULL;    info->fptRestsPList = NULL;    info->flagRestsP = 0;
    info->SigmaP = 1.;    info->flagSigmaP = 0;
    info->SigmaPA = 1.;    info->flagSigmaPA = 0;
    info->NearP = 1.;    info->flagNearP = 0;
    info->NearPA = 1.;    info->flagNearPA = 0;
    info->RestrictPW=0;
    info->deltax = 5;    info->flagdeltax = 0;
    info->deltay = 5;    info->flagdeltay = 0;
    info->deltaz = 5;    info->flagdeltaz = 0;
    info->sdeltax = 5;    info->flagsdeltax = 0;
    info->sdeltay = 5;    info->flagsdeltay = 0;
    info->sdeltaz = 5;    info->flagsdeltaz = 0;
    info->startx = 5;    info->flagstartx = 0;
    info->starty = 5;    info->flagstarty = 0;
    info->startz = 5;    info->flagstartz = 0;
    info->endx = 5;    info->flagendx = 0;
    info->endy = 5;    info->flagendy = 0;
    info->endz = 5;    info->flagendz = 0;
    info->maxIter = 1;    info->flagmaxIter = 0;
    info->startIter = 0;    info->flagstartIter = 0;
    info->neglect = 1e-4;    info->flagneglect = 0;
    info->fptconfigFile = NULL;    info->flagconfigFile = 0;
    info->mode = 0;    info->flagmode = 0;
}

void
init1(energyTransferModelCheckInfo* info)
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
    
    if(info->flagPDB) {
        info->fptPDB = fileOpen(info->PDB, "r");
    }
    
    if(info->flagPDBs) {
        info->fptPDBsList = fileOpen(info->PDBsList, "r");
        fseek(info->fptPDBsList, 0L, SEEK_SET);
        i=0;
        while(NULL!=stringGetFromFile(s, "", info->fptPDBsList, stdout, 1)) {
            i++;
        }
        info->fptPDBs = (FILE**)memoryAllocate(i*sizeof(FILE*), "in init1");
        info->PDBs    = (char**)memoryAllocate(i*sizeof(char*), "in init1");
        info->flagPDBs = i;
        fseek(info->fptPDBsList, 0L, SEEK_SET);
        i=0;
        while(NULL!=stringGetFromFile(s, "", info->fptPDBsList, stdout, 1)) {
            info->PDBs[i] = stringGetNthWord(s, 1, " ,\t");
            info->fptPDBs[i] = fileOpen(info->PDBs[i],"r");
            i++;
        }
    }
    
    if(info->flagsigma) {
    }
    
    if(info->flagsigmaA) {
    }
    
    if(info->flagMRC) {
        info->fptMRC = fileOpen(info->MRC, "r");
    }
    
    if(info->flagMRCs) {
        info->fptMRCsList = fileOpen(info->MRCsList, "r");
        fseek(info->fptMRCsList, 0L, SEEK_SET);
        i=0;
        while(NULL!=stringGetFromFile(s, "", info->fptMRCsList, stdout, 1)) {
            i++;
        }
        info->fptMRCs = (FILE**)memoryAllocate(i*sizeof(FILE*), "in init1");
        info->MRCs    = (char**)memoryAllocate(i*sizeof(char*), "in init1");
        info->flagMRCs = i;
        fseek(info->fptMRCsList, 0L, SEEK_SET);
        i=0;
        while(NULL!=stringGetFromFile(s, "", info->fptMRCsList, stdout, 1)) {
            info->MRCs[i] = stringGetNthWord(s, 1, " ,\t");
            info->fptMRCs[i] = fileOpen(info->MRCs[i],"r");
            i++;
        }
    }
    
    if(info->flagEContour) {
    }
    
    if(info->flagENear) {
    }
    
    if(info->flagENearA) {
    }
    
    if(info->flagRest) {
        info->fptRest = fileOpen(info->Rest, "r");
    }
    
    if(info->flagRests) {
        info->fptRestsList = fileOpen(info->RestsList, "r");
        fseek(info->fptRestsList, 0L, SEEK_SET);
        i=0;
        while(NULL!=stringGetFromFile(s, "", info->fptRestsList, stdout, 1)) {
            i++;
        }
        info->fptRests = (FILE**)memoryAllocate(i*sizeof(FILE*), "in init1");
        info->Rests    = (char**)memoryAllocate(i*sizeof(char*), "in init1");
        info->flagRests = i;
        fseek(info->fptRestsList, 0L, SEEK_SET);
        i=0;
        while(NULL!=stringGetFromFile(s, "", info->fptRestsList, stdout, 1)) {
            info->Rests[i] = stringGetNthWord(s, 1, " ,\t");
            info->fptRests[i] = fileOpen(info->Rests[i],"r");
            i++;
        }
    }
    
    if(info->flagContour) {
    }
    
    if(info->flagNear) {
    }
    
    if(info->flagNearA) {
    }
    
    if(info->flagRestP) {
        info->fptRestP = fileOpen(info->RestP, "r");
    }
    
    if(info->flagRestsP) {
        info->fptRestsPList = fileOpen(info->RestsPList, "r");
        fseek(info->fptRestsPList, 0L, SEEK_SET);
        i=0;
        while(NULL!=stringGetFromFile(s, "", info->fptRestsPList, stdout, 1)) {
            i++;
        }
        info->fptRestsP = (FILE**)memoryAllocate(i*sizeof(FILE*), "in init1");
        info->RestsP    = (char**)memoryAllocate(i*sizeof(char*), "in init1");
        info->flagRestsP = i;
        fseek(info->fptRestsPList, 0L, SEEK_SET);
        i=0;
        while(NULL!=stringGetFromFile(s, "", info->fptRestsPList, stdout, 1)) {
            info->RestsP[i] = stringGetNthWord(s, 1, " ,\t");
            info->fptRestsP[i] = fileOpen(info->RestsP[i],"r");
            i++;
        }
    }
    
    if(info->flagSigmaP) {
    }
    
    if(info->flagSigmaPA) {
    }
    
    if(info->flagNearP) {
    }
    
    if(info->flagNearPA) {
    }
    
    if(info->flagdeltax) {
    }
    
    if(info->flagdeltay) {
    }
    
    if(info->flagdeltaz) {
    }
    
    if(info->flagsdeltax) {
    }
    
    if(info->flagsdeltay) {
    }
    
    if(info->flagsdeltaz) {
    }
    
    if(info->flagstartx) {
    }
    
    if(info->flagstarty) {
    }
    
    if(info->flagstartz) {
    }
    
    if(info->flagendx) {
    }
    
    if(info->flagendy) {
    }
    
    if(info->flagendz) {
    }
    
    if(info->flagmaxIter) {
    }
    
    if(info->flagstartIter) {
    }
    
    if(info->flagneglect) {
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
    sprintf(panepath, "%s/src/Tools/simulation/energyTransferModelCheck/src/energyTransferModelCheck.pane", eospath);
    khoros_initialize(argc, argv, "EOS");
    fpt = fopen(panepath, "r");    if(NULL!=fpt) {
        fclose(fpt);
        kclui_initialize(panepath, KGEN_NONE, "EOS", "energyTransferModelCheck",
                     func_usage_additions,
                     func_get_args,
                     func_free_args);
    }
}
#endif /* KHOROS */ 
