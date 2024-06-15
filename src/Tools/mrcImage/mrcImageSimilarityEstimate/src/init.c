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
init0(mrcImageSimilarityEstimateInfo* info)
{
    info->fptIn = NULL;    info->flagIn = 0;
    info->fptOut = NULL;    info->flagOut = 0;
    info->fptOutCor = NULL;    info->flagOutCor = 0;
    info->fptref     = stdin;    info->fptrefList = stdin;    info->flagref = 0;
    info->fptcorfilename     = stdin;    info->fptcorfilenameList = stdin;    info->flagcorfilename = 0;
    info->cormode = 0;    info->flagcormode = 0;
    info->fptctfinfo = NULL;    info->flagctfinfo = 0;
    info->fptconfigFile = NULL;    info->flagconfigFile = 0;
    info->mode = 0;    info->flagmode = 0;
}

void
init1(mrcImageSimilarityEstimateInfo* info)
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
    
    if(info->flagOut) {
        info->fptOut = fileOpen(info->Out, "w");
    }
    
    if(info->flagOutCor) {
        info->fptOutCor = fileOpen(info->OutCor, "w");
    }
    
    if(!info->flagref) {
        stringGetFromFile(s, "ref", stdin, stdout, 0);
        info->refList = stringGetNthWord(s, 1, " ,\t");
        info->flagref++;
    }
    if(info->flagref) {
        info->fptrefList = fileOpen(info->refList, "r");
        fseek(info->fptrefList, 0L, SEEK_SET);
        i=0;
        while(NULL!=stringGetFromFile(s, "", info->fptrefList, stdout, 1)) {
            i++;
        }
        info->fptref = (FILE**)memoryAllocate(i*sizeof(FILE*), "in init1");
        info->ref    = (char**)memoryAllocate(i*sizeof(char*), "in init1");
        info->flagref = i;
        fseek(info->fptrefList, 0L, SEEK_SET);
        i=0;
        while(NULL!=stringGetFromFile(s, "", info->fptrefList, stdout, 1)) {
            info->ref[i] = stringGetNthWord(s, 1, " ,\t");
            i++;
        }
    }
    
    if(info->flagcorfilename) {
        info->fptcorfilenameList = fileOpen(info->corfilenameList, "r");
        fseek(info->fptcorfilenameList, 0L, SEEK_SET);
        i=0;
        while(NULL!=stringGetFromFile(s, "", info->fptcorfilenameList, stdout, 1)) {
            i++;
        }
        info->fptcorfilename = (FILE**)memoryAllocate(i*sizeof(FILE*), "in init1");
        info->corfilename    = (char**)memoryAllocate(i*sizeof(char*), "in init1");
        info->flagcorfilename = i;
        fseek(info->fptcorfilenameList, 0L, SEEK_SET);
        i=0;
        while(NULL!=stringGetFromFile(s, "", info->fptcorfilenameList, stdout, 1)) {
            info->corfilename[i] = stringGetNthWord(s, 1, " ,\t");
            i++;
        }
    }
    
    if(info->flagcormode) {
    }
    
    if(info->flagctfinfo) {
        info->fptctfinfo = fileOpen(info->ctfinfo, "r");
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
    sprintf(panepath, "%s/src/Tools/mrcImage/mrcImageSimilarityEstimate/src/mrcImageSimilarityEstimate.pane", eospath);
    khoros_initialize(argc, argv, "EOS");
    fpt = fopen(panepath, "r");    if(NULL!=fpt) {
        fclose(fpt);
        kclui_initialize(panepath, KGEN_NONE, "EOS", "mrcImageSimilarityEstimate",
                     func_usage_additions,
                     func_get_args,
                     func_free_args);
    }
}
#endif /* KHOROS */ 
