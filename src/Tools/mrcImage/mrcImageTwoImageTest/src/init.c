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
init0(mrcImageTwoImageTestInfo* info)
{
    info->fptIn1     = NULL;    info->fptIn1List = NULL;    info->flagIn1 = 0;
    info->fptIn2     = NULL;    info->fptIn2List = NULL;    info->flagIn2 = 0;
    info->fpttTest = NULL;    info->flagtTest = 0;
    info->fptFTest = NULL;    info->flagFTest = 0;
    info->fptconfigFile = NULL;    info->flagconfigFile = 0;
    info->mode = 0;    info->flagmode = 0;
}

void
init1(mrcImageTwoImageTestInfo* info)
{
    char s[1024];
    int i;
    if(!info->flagIn1) {
        stringGetFromFile(s, "In1", stdin, stdout, 0);
        info->In1List = stringGetNthWord(s, 1, " ,\t");
        info->flagIn1++;
    }
    if(info->flagIn1) {
        info->fptIn1List = fileOpen(info->In1List, "r");
        fseek(info->fptIn1List, 0L, SEEK_SET);
        i=0;
        while(NULL!=stringGetFromFile(s, "", info->fptIn1List, stdout, 1)) {
            i++;
        }
        info->fptIn1 = (FILE**)memoryAllocate(i*sizeof(FILE*), "in init1");
        info->In1    = (char**)memoryAllocate(i*sizeof(char*), "in init1");
        info->flagIn1 = i;
        fseek(info->fptIn1List, 0L, SEEK_SET);
        i=0;
        while(NULL!=stringGetFromFile(s, "", info->fptIn1List, stdout, 1)) {
            info->In1[i] = stringGetNthWord(s, 1, " ,\t");
            info->fptIn1[i] = fileOpen(info->In1[i],"r");
            i++;
        }
    }
    
    if(!info->flagIn2) {
        stringGetFromFile(s, "In2", stdin, stdout, 0);
        info->In2List = stringGetNthWord(s, 1, " ,\t");
        info->flagIn2++;
    }
    if(info->flagIn2) {
        info->fptIn2List = fileOpen(info->In2List, "r");
        fseek(info->fptIn2List, 0L, SEEK_SET);
        i=0;
        while(NULL!=stringGetFromFile(s, "", info->fptIn2List, stdout, 1)) {
            i++;
        }
        info->fptIn2 = (FILE**)memoryAllocate(i*sizeof(FILE*), "in init1");
        info->In2    = (char**)memoryAllocate(i*sizeof(char*), "in init1");
        info->flagIn2 = i;
        fseek(info->fptIn2List, 0L, SEEK_SET);
        i=0;
        while(NULL!=stringGetFromFile(s, "", info->fptIn2List, stdout, 1)) {
            info->In2[i] = stringGetNthWord(s, 1, " ,\t");
            info->fptIn2[i] = fileOpen(info->In2[i],"r");
            i++;
        }
    }
    
    if(info->flagtTest) {
        info->fpttTest = fileOpen(info->tTest, "w");
    }
    
    if(info->flagFTest) {
        info->fptFTest = fileOpen(info->FTest, "w");
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
    sprintf(panepath, "%s/src/Tools/mrcImage/mrcImageTwoImageTest/src/mrcImageTwoImageTest.pane", eospath);
    khoros_initialize(argc, argv, "EOS");
    fpt = fopen(panepath, "r");    if(NULL!=fpt) {
        fclose(fpt);
        kclui_initialize(panepath, KGEN_NONE, "EOS", "mrcImageTwoImageTest",
                     func_usage_additions,
                     func_get_args,
                     func_free_args);
    }
}
#endif /* KHOROS */ 
