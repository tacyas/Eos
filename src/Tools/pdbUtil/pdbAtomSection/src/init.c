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
init0(pdbAtomSectionInfo* info)
{
    info->fptIn = NULL;    info->flagIn = 0;
    info->fptInFlags = NULL;    info->flagInFlags = 0;
    info->fptOut = NULL;    info->flagOut = 0;
    info->distance = 2.5;    info->flagdistance = 0;
    info->zmin = 0.0;    info->flagzmin = 0;
    info->zmax = 90.0;    info->flagzmax = 0;
    info->flagMode = 13;    info->flagflagMode = 0;
    info->radius = 1.0;    info->flagradius = 0;
    info->clinewidth = 0.1;    info->flagclinewidth = 0;
    info->plinewidth = 0.1;    info->flagplinewidth = 0;
    info->fontsize = 2.0;    info->flagfontsize = 0;
    info->scale = 1.0;    info->flagscale = 0;
    info->shiftx = 0.0;    info->flagshiftx = 0;
    info->shifty = 0.0;    info->flagshifty = 0;
    info->shiftz = 0.0;    info->flagshiftz = 0;
    info->fptconfigFile = NULL;    info->flagconfigFile = 0;
    info->mode = 0;    info->flagmode = 0;
}

void
init1(pdbAtomSectionInfo* info)
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
    
    if(info->flagInFlags) {
        info->fptInFlags = fileOpen(info->InFlags, "r");
    }
    
    if(!info->flagOut) {
        stringGetFromFile(s, "Out", stdin, stdout, 0);
        info->Out = stringGetNthWord(s, 1, " ,\t");
        info->flagOut++;
    }
    if(info->flagOut) {
        info->fptOut = fileOpen(info->Out, "w");
    }
    
    if(info->flagdistance) {
    }
    
    if(info->flagzmin) {
    }
    
    if(info->flagzmax) {
    }
    
    if(info->flagflagMode) {
    }
    
    if(info->flagradius) {
    }
    
    if(info->flagclinewidth) {
    }
    
    if(info->flagplinewidth) {
    }
    
    if(info->flagfontsize) {
    }
    
    if(info->flagscale) {
    }
    
    if(info->flagshiftx) {
    }
    
    if(info->flagshifty) {
    }
    
    if(info->flagshiftz) {
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
    sprintf(panepath, "%s/src/Tools/pdbUtil/pdbAtomSection/src/pdbAtomSection.pane", eospath);
    khoros_initialize(argc, argv, "EOS");
    fpt = fopen(panepath, "r");    if(NULL!=fpt) {
        fclose(fpt);
        kclui_initialize(panepath, KGEN_NONE, "EOS", "pdbAtomSection",
                     func_usage_additions,
                     func_get_args,
                     func_free_args);
    }
}
#endif /* KHOROS */ 
