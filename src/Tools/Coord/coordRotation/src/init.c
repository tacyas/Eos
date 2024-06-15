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
init0(coordRotationInfo* info)
{
    info->x = 0;    info->flagx = 0;
    info->y = 0;    info->flagy = 0;
    info->z = 0;    info->flagz = 0;
    info->fptMat = stdin;    info->flagMat = 0;
    info->fptOut = stdout;    info->flagOut = 0;
    info->fptconfigFile = NULL;    info->flagconfigFile = 0;
    info->mode = 0;    info->flagmode = 0;
}

void
init1(coordRotationInfo* info)
{
    char s[1024];
    int i;
    if(!info->flagx) {
        stringGetFromFile(s, "x", stdin, stdout, 0);
        info->x = stringGetNthRealData(s, 1, ", \t");
        info->flagx++;
    }
    if(info->flagx) {
    }
    
    if(!info->flagy) {
        stringGetFromFile(s, "y", stdin, stdout, 0);
        info->y = stringGetNthRealData(s, 1, ", \t");
        info->flagy++;
    }
    if(info->flagy) {
    }
    
    if(!info->flagz) {
        stringGetFromFile(s, "z", stdin, stdout, 0);
        info->z = stringGetNthRealData(s, 1, ", \t");
        info->flagz++;
    }
    if(info->flagz) {
    }
    
    if(!info->flagMat) {
        stringGetFromFile(s, "Mat", stdin, stdout, 0);
        info->Mat = stringGetNthWord(s, 1, " ,\t");
        info->flagMat++;
    }
    if(info->flagMat) {
        info->fptMat = fileOpen(info->Mat, "r");
    }
    
    if(info->flagOut) {
        info->fptOut = fileOpen(info->Out, "w");
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
    sprintf(panepath, "%s/src/Tools/Coord/coordRotation/src/coordRotation.pane", eospath);
    khoros_initialize(argc, argv, "EOS");
    fpt = fopen(panepath, "r");    if(NULL!=fpt) {
        fclose(fpt);
        kclui_initialize(panepath, KGEN_NONE, "EOS", "coordRotation",
                     func_usage_additions,
                     func_get_args,
                     func_free_args);
    }
}
#endif /* KHOROS */ 
