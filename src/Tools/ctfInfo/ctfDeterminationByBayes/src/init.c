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
init0(ctfDeterminationByBayesInfo* info)
{
    info->fptIn = NULL;    info->flagIn = 0;
    info->fptIn2 = NULL;    info->flagIn2 = 0;
    info->fptIn3 = NULL;    info->flagIn3 = 0;
    info->fptIn4     = NULL;    info->fptIn4List = NULL;    info->flagIn4 = 0;
    info->numDistribution = 3;    info->flagnumDistribution = 0;
    info->numLikelihood = 3;    info->flagnumLikelihood = 0;
    info->rmax = 250;    info->flagrmax = 0;
    info->rintermediate = 250;    info->flagrintermediate = 0;
    info->rfirstpeak = 0.001;    info->flagrfirstpeak = 0;
    info->rmin = 0;    info->flagrmin = 0;
    info->fptconfigFile = NULL;    info->flagconfigFile = 0;
    info->mode = 0;    info->flagmode = 0;
    info->MTFmode = 0;    info->flagMTFmode = 0;
    info->Ainmode = 0;    info->flagAinmode = 0;
    info->Intensitymode = 0;    info->flagIntensitymode = 0;
}

void
init1(ctfDeterminationByBayesInfo* info)
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
    
    if(!info->flagIn2) {
        stringGetFromFile(s, "In2", stdin, stdout, 0);
        info->In2 = stringGetNthWord(s, 1, " ,\t");
        info->flagIn2++;
    }
    if(info->flagIn2) {
        info->fptIn2 = fileOpen(info->In2, "r");
    }
    
    if(!info->flagIn3) {
        stringGetFromFile(s, "In3", stdin, stdout, 0);
        info->In3 = stringGetNthWord(s, 1, " ,\t");
        info->flagIn3++;
    }
    if(info->flagIn3) {
        info->fptIn3 = fileOpen(info->In3, "r");
    }
    
    if(!info->flagIn4) {
        stringGetFromFile(s, "In4", stdin, stdout, 0);
        info->In4List = stringGetNthWord(s, 1, " ,\t");
        info->flagIn4++;
    }
    if(info->flagIn4) {
        info->fptIn4List = fileOpen(info->In4List, "r");
        fseek(info->fptIn4List, 0L, SEEK_SET);
        i=0;
        while(NULL!=stringGetFromFile(s, "", info->fptIn4List, stdout, 1)) {
            i++;
        }
        info->fptIn4 = (FILE**)memoryAllocate(i*sizeof(FILE*), "in init1");
        info->In4    = (char**)memoryAllocate(i*sizeof(char*), "in init1");
        info->flagIn4 = i;
        fseek(info->fptIn4List, 0L, SEEK_SET);
        i=0;
        while(NULL!=stringGetFromFile(s, "", info->fptIn4List, stdout, 1)) {
            info->In4[i] = stringGetNthWord(s, 1, " ,\t");
            i++;
        }
    }
    
    if(!info->flagnumDistribution) {
        stringGetFromFile(s, "numDistribution", stdin, stdout, 0);
        info->numDistribution = stringGetNthIntegerData(s, 1, ", \t");
        info->flagnumDistribution++;
    }
    if(info->flagnumDistribution) {
    }
    
    if(!info->flagnumLikelihood) {
        stringGetFromFile(s, "numLikelihood", stdin, stdout, 0);
        info->numLikelihood = stringGetNthIntegerData(s, 1, ", \t");
        info->flagnumLikelihood++;
    }
    if(info->flagnumLikelihood) {
    }
    
    if(info->flagrmax) {
    }
    
    if(info->flagrintermediate) {
    }
    
    if(info->flagrfirstpeak) {
    }
    
    if(info->flagrmin) {
    }
    
    if(info->flagconfigFile) {
        info->fptconfigFile = fileOpen(info->configFile, "r");
    }
    
    if(info->flagmode) {
    }
    
    if(info->flagMTFmode) {
    }
    
    if(info->flagAinmode) {
    }
    
    if(info->flagIntensitymode) {
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
    sprintf(panepath, "%s/src/Tools/ctfInfo/ctfDeterminationByBayes/src/ctfDeterminationByBayes.pane", eospath);
    khoros_initialize(argc, argv, "EOS");
    fpt = fopen(panepath, "r");    if(NULL!=fpt) {
        fclose(fpt);
        kclui_initialize(panepath, KGEN_NONE, "EOS", "ctfDeterminationByBayes",
                     func_usage_additions,
                     func_get_args,
                     func_free_args);
    }
}
#endif /* KHOROS */ 
