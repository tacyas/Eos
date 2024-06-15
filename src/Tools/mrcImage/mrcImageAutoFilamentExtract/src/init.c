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
init0(mrcImageAutoFilamentExtractInfo* info)
{
    info->fptIn = NULL;    info->flagIn = 0;
    info->fptInS = NULL;    info->flagInS = 0;
    info->fptOutE = NULL;    info->flagOutE = 0;
    info->fptOut = stdout;    info->flagOut = 0;
    info->fptOutF = stdout;    info->flagOutF = 0;
    info->blx = 0.0;    info->flagblx = 0;
    info->bly = 0.0;    info->flagbly = 0;
    info->brx = 0.0;    info->flagbrx = 0;
    info->bry = 0.0;    info->flagbry = 0;
    info->trx = 0.0;    info->flagtrx = 0;
    info->try = 0.0;    info->flagtry = 0;
    info->tlx = 0.0;    info->flagtlx = 0;
    info->tly = 0.0;    info->flagtly = 0;
    info->roiLine = NULL;    info->flagroiLine = 0;
    info->x = 120;    info->flagx = 0;
    info->ddYmax = 0.9;    info->flagddYmax = 0;
    info->ddYmin = 0.2;    info->flagddYmin = 0;
    info->T = 0;    info->flagT = 0;
    info->maxdY = 12;    info->flagmaxdY = 0;
    info->HeightRange = 0;    info->flagHeightRange = 0;
    info->RMaxX = 0.05;    info->flagRMaxX = 0;
    info->mag = 1.1;    info->flagmag = 0;
    info->truePitch = 430;    info->flagtruePitch = 0;
    info->PixelSize = 5;    info->flagPixelSize = 0;
    info->finaly = 0;    info->flagfinaly = 0;
    info->Ignore = 0;    info->flagIgnore = 0;
    info->fptconfigFile = NULL;    info->flagconfigFile = 0;
    info->mode = 0;    info->flagmode = 0;
}

void
init1(mrcImageAutoFilamentExtractInfo* info)
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
    
    if(!info->flagInS) {
        stringGetFromFile(s, "InS", stdin, stdout, 0);
        info->InS = stringGetNthWord(s, 1, " ,\t");
        info->flagInS++;
    }
    if(info->flagInS) {
        info->fptInS = fileOpen(info->InS, "r");
    }
    
    if(!info->flagOutE) {
        stringGetFromFile(s, "OutE", stdin, stdout, 0);
        info->OutE = stringGetNthWord(s, 1, " ,\t");
        info->flagOutE++;
    }
    if(info->flagOutE) {
        info->fptOutE = fileOpen(info->OutE, "r");
    }
    
    if(info->flagOut) {
        info->fptOut = fopen(info->Out, "a+");
    }
    
    if(info->flagOutF) {
        info->fptOutF = fileOpen(info->OutF, "w");
    }
    
    if(info->flagblx) {
    }
    
    if(info->flagbly) {
    }
    
    if(info->flagbrx) {
    }
    
    if(info->flagbry) {
    }
    
    if(info->flagtrx) {
    }
    
    if(info->flagtry) {
    }
    
    if(info->flagtlx) {
    }
    
    if(info->flagtly) {
    }
    
    if(info->flagroiLine) {
    }
    
    if(info->flagx) {
    }
    
    if(info->flagddYmax) {
    }
    
    if(info->flagddYmin) {
    }
    
    if(info->flagT) {
    }
    
    if(info->flagmaxdY) {
    }
    
    if(info->flagHeightRange) {
    }
    
    if(info->flagRMaxX) {
    }
    
    if(info->flagmag) {
    }
    
    if(info->flagtruePitch) {
    }
    
    if(info->flagPixelSize) {
    }
    
    if(info->flagfinaly) {
    }
    
    if(info->flagIgnore) {
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
    sprintf(panepath, "%s/src/Tools/mrcImage/mrcImageAutoFilamentExtract/src/mrcImageAutoFilamentExtract.pane", eospath);
    khoros_initialize(argc, argv, "EOS");
    fpt = fopen(panepath, "r");    if(NULL!=fpt) {
        fclose(fpt);
        kclui_initialize(panepath, KGEN_NONE, "EOS", "mrcImageAutoFilamentExtract",
                     func_usage_additions,
                     func_get_args,
                     func_free_args);
    }
}
#endif /* KHOROS */ 
