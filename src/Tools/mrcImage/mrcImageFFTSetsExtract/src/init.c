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
init0(mrcImageFFTSetsExtractInfo* info)
{
    info->fptIn = NULL;    info->flagIn = 0;
    info->FTBBase = stringGetNthWord("out", 1, "\0");    info->flagFTBBase = 0;
    info->FTABase = stringGetNthWord("Out", 1, "\0");    info->flagFTABase = 0;
    info->width = 256;    info->flagwidth = 0;
    info->height = 256;    info->flagheight = 0;
    info->fptconfigFile = NULL;    info->flagconfigFile = 0;
    info->mode = 0;    info->flagmode = 0;
}

void
init1(mrcImageFFTSetsExtractInfo* info)
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
    
    if(!info->flagFTBBase) {
        stringGetFromFile(s, "FTBBase", stdin, stdout, 0);
        info->FTBBase = stringGetNthWord(s, 1, " ,\t");
        info->flagFTBBase++;
    }
    if(info->flagFTBBase) {
    }
    
    if(!info->flagFTABase) {
        stringGetFromFile(s, "FTABase", stdin, stdout, 0);
        info->FTABase = stringGetNthWord(s, 1, " ,\t");
        info->flagFTABase++;
    }
    if(info->flagFTABase) {
    }
    
    if(info->flagwidth) {
    }
    
    if(info->flagheight) {
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
    sprintf(panepath, "%s/src/Tools/mrcImage/mrcImageFFTSetsExtract/src/mrcImageFFTSetsExtract.pane", eospath);
    khoros_initialize(argc, argv, "EOS");
    fpt = fopen(panepath, "r");    if(NULL!=fpt) {
        fclose(fpt);
        kclui_initialize(panepath, KGEN_NONE, "EOS", "mrcImageFFTSetsExtract",
                     func_usage_additions,
                     func_get_args,
                     func_free_args);
    }
}
#endif /* KHOROS */ 
