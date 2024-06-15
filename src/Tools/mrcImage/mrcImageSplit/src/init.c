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
init0(mrcImageSplitInfo* info)
{
    info->fptIn = NULL;    info->flagIn = 0;
    info->Out = stringGetNthWord("", 1, "\0");    info->flagOut = 0;
    info->Suffix = stringGetNthWord("%04d%04d%04d.splt", 1, "\0");    info->flagSuffix = 0;
    info->Height = 0;    info->flagHeight = 0;
    info->Width = 0;    info->flagWidth = 0;
    info->Section = 0;    info->flagSection = 0;
    info->HeightA = 0;    info->flagHeightA = 0;
    info->WidthA = 0;    info->flagWidthA = 0;
    info->SectionA = 0;    info->flagSectionA = 0;
    info->fptconfigFile = NULL;    info->flagconfigFile = 0;
    info->mode = 0;    info->flagmode = 0;
}

void
init1(mrcImageSplitInfo* info)
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
    }
    
    if(info->flagSuffix) {
    }
    
    if(info->flagHeight) {
    }
    
    if(info->flagWidth) {
    }
    
    if(info->flagSection) {
    }
    
    if(info->flagHeightA) {
    }
    
    if(info->flagWidthA) {
    }
    
    if(info->flagSectionA) {
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
    sprintf(panepath, "%s/src/Tools/mrcImage/mrcImageSplit/src/mrcImageSplit.pane", eospath);
    khoros_initialize(argc, argv, "EOS");
    fpt = fopen(panepath, "r");    if(NULL!=fpt) {
        fclose(fpt);
        kclui_initialize(panepath, KGEN_NONE, "EOS", "mrcImageSplit",
                     func_usage_additions,
                     func_get_args,
                     func_free_args);
    }
}
#endif /* KHOROS */ 
