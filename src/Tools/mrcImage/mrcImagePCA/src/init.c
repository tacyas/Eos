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
init0(mrcImagePCAInfo* info)
{
    info->fptInList     = NULL;    info->fptInListList = NULL;    info->flagInList = 0;
    info->fptOutList     = NULL;    info->fptOutListList = NULL;    info->flagOutList = 0;
    info->EPS = 1e2;    info->flagEPS = 0;
    info->NX = 30;    info->flagNX = 0;
    info->NY = 30;    info->flagNY = 0;
    info->fptOutvector = NULL;    info->flagOutvector = 0;
    info->fptEPSOutcaletime = NULL;    info->flagEPSOutcaletime = 0;
    info->EigenImage = stringGetNthWord("eigen", 1, "\0");    info->flagEigenImage = 0;
    info->numOfEigenImage = 10;    info->flagnumOfEigenImage = 0;
    info->fptconfigFile = NULL;    info->flagconfigFile = 0;
    info->mode = 0;    info->flagmode = 0;
}

void
init1(mrcImagePCAInfo* info)
{
    char s[1024];
    int i;
    if(!info->flagInList) {
        stringGetFromFile(s, "InList", stdin, stdout, 0);
        info->InListList = stringGetNthWord(s, 1, " ,\t");
        info->flagInList++;
    }
    if(info->flagInList) {
        info->fptInListList = fileOpen(info->InListList, "r");
        fseek(info->fptInListList, 0L, SEEK_SET);
        i=0;
        while(NULL!=stringGetFromFile(s, "", info->fptInListList, stdout, 1)) {
            i++;
        }
        info->fptInList = (FILE**)memoryAllocate(i*sizeof(FILE*), "in init1");
        info->InList    = (char**)memoryAllocate(i*sizeof(char*), "in init1");
        info->flagInList = i;
        fseek(info->fptInListList, 0L, SEEK_SET);
        i=0;
        while(NULL!=stringGetFromFile(s, "", info->fptInListList, stdout, 1)) {
            info->InList[i] = stringGetNthWord(s, 1, " ,\t");
            i++;
        }
    }
    
    if(!info->flagOutList) {
        stringGetFromFile(s, "OutList", stdin, stdout, 0);
        info->OutListList = stringGetNthWord(s, 1, " ,\t");
        info->flagOutList++;
    }
    if(info->flagOutList) {
        info->fptOutListList = fileOpen(info->OutListList, "r");
        fseek(info->fptOutListList, 0L, SEEK_SET);
        i=0;
        while(NULL!=stringGetFromFile(s, "", info->fptOutListList, stdout, 1)) {
            i++;
        }
        info->fptOutList = (FILE**)memoryAllocate(i*sizeof(FILE*), "in init1");
        info->OutList    = (char**)memoryAllocate(i*sizeof(char*), "in init1");
        info->flagOutList = i;
        fseek(info->fptOutListList, 0L, SEEK_SET);
        i=0;
        while(NULL!=stringGetFromFile(s, "", info->fptOutListList, stdout, 1)) {
            info->OutList[i] = stringGetNthWord(s, 1, " ,\t");
            i++;
        }
    }
    
    if(info->flagEPS) {
    }
    
    if(info->flagNX) {
    }
    
    if(info->flagNY) {
    }
    
    if(info->flagOutvector) {
        info->fptOutvector = fileOpen(info->Outvector, "w");
    }
    
    if(info->flagEPSOutcaletime) {
        info->fptEPSOutcaletime = fileOpen(info->EPSOutcaletime, "w");
    }
    
    if(info->flagEigenImage) {
    }
    
    if(info->flagnumOfEigenImage) {
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
    sprintf(panepath, "%s/src/Tools/mrcImage/mrcImagePCA/src/mrcImagePCA.pane", eospath);
    khoros_initialize(argc, argv, "EOS");
    fpt = fopen(panepath, "r");    if(NULL!=fpt) {
        fclose(fpt);
        kclui_initialize(panepath, KGEN_NONE, "EOS", "mrcImagePCA",
                     func_usage_additions,
                     func_get_args,
                     func_free_args);
    }
}
#endif /* KHOROS */ 
