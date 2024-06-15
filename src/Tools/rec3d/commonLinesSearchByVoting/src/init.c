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
init0(commonLinesSearchByVotingInfo* info)
{
    info->fptIn = NULL;    info->flagIn = 0;
    info->fptInC = NULL;    info->flagInC = 0;
    info->fptInCC = NULL;    info->flagInCC = 0;
    info->fptOut = NULL;    info->flagOut = 0;
    info->fptOutA = NULL;    info->flagOutA = 0;
    info->fptOutDR = NULL;    info->flagOutDR = 0;
    info->fptOutDRA = NULL;    info->flagOutDRA = 0;
    info->fptOutPH = NULL;    info->flagOutPH = 0;
    info->en = 1;    info->flagen = 0;
    info->th = 1;    info->flagth = 0;
    info->histgramCreateFlag=0;
    info->extendVotingFlag=0;
    info->fptconfigFile = NULL;    info->flagconfigFile = 0;
    info->mode = 0;    info->flagmode = 0;
}

void
init1(commonLinesSearchByVotingInfo* info)
{
    char s[1024];
    int i;
    if(info->flagIn) {
        info->fptIn = fileOpen(info->In, "r");
    }
    
    if(info->flagInC) {
        info->fptInC = fileOpen(info->InC, "r");
    }
    
    if(info->flagInCC) {
        info->fptInCC = fileOpen(info->InCC, "r");
    }
    
    if(!info->flagOut) {
        stringGetFromFile(s, "Out", stdin, stdout, 0);
        info->Out = stringGetNthWord(s, 1, " ,\t");
        info->flagOut++;
    }
    if(info->flagOut) {
        info->fptOut = fileOpen(info->Out, "w");
    }
    
    if(info->flagOutA) {
        info->fptOutA = fileOpen(info->OutA, "w");
    }
    
    if(info->flagOutDR) {
        info->fptOutDR = fileOpen(info->OutDR, "w");
    }
    
    if(info->flagOutDRA) {
        info->fptOutDRA = fileOpen(info->OutDRA, "w");
    }
    
    if(info->flagOutPH) {
        info->fptOutPH = fileOpen(info->OutPH, "w");
    }
    
    if(info->flagen) {
    }
    
    if(info->flagth) {
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
    sprintf(panepath, "%s/src/Tools/rec3d/commonLinesSearchByVoting/src/commonLinesSearchByVoting.pane", eospath);
    khoros_initialize(argc, argv, "EOS");
    fpt = fopen(panepath, "r");    if(NULL!=fpt) {
        fclose(fpt);
        kclui_initialize(panepath, KGEN_NONE, "EOS", "commonLinesSearchByVoting",
                     func_usage_additions,
                     func_get_args,
                     func_free_args);
    }
}
#endif /* KHOROS */ 
