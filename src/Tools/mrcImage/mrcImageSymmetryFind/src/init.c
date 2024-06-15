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
init0(mrcImageSymmetryFindInfo* info)
{
    info->fptIn = NULL;    info->flagIn = 0;
    info->fptOut = NULL;    info->flagOut = 0;
    info->fptOut2 = stdout;    info->flagOut2 = 0;
    info->fptAvg = NULL;    info->flagAvg = 0;
    info->centreMode = 1;    info->flagcentreMode = 0;
    info->threshold1 = 1.8;    info->flagthreshold1 = 0;
    info->threshold2 = 0.9;    info->flagthreshold2 = 0;
    info->mode1 = 3;    info->flagmode1 = 0;
    info->mode2 = 2;    info->flagmode2 = 0;
    info->dr = 1;    info->flagdr = 0;
    info->dtheta = 1;    info->flagdtheta = 0;
    info->n = 10;    info->flagn = 0;
    info->nmin = 2;    info->flagnmin = 0;
    info->nmax = 10;    info->flagnmax = 0;
    info->fptImage     = NULL;    info->fptImageList = NULL;    info->flagImage = 0;
    info->fptBack     = NULL;    info->fptBackList = NULL;    info->flagBack = 0;
    info->minx = -3;    info->flagminx = 0;
    info->maxx = 3;    info->flagmaxx = 0;
    info->delx = 1;    info->flagdelx = 0;
    info->miny = -3;    info->flagminy = 0;
    info->maxy = 3;    info->flagmaxy = 0;
    info->dely = 1;    info->flagdely = 0;
    info->minz = 0;    info->flagminz = 0;
    info->maxz = 0;    info->flagmaxz = 0;
    info->delz = 1;    info->flagdelz = 0;
    info->rmin = 0;    info->flagrmin = 0;
    info->rmax = -1;    info->flagrmax = 0;
    info->Algorythm=0;
    info->fptconfigFile = NULL;    info->flagconfigFile = 0;
}

void
init1(mrcImageSymmetryFindInfo* info)
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
    
    if(info->flagOut2) {
        info->fptOut2 = fileOpen(info->Out2, "w");
    }
    
    if(info->flagAvg) {
        info->fptAvg = fileOpen(info->Avg, "w");
    }
    
    if(info->flagcentreMode) {
    }
    
    if(info->flagthreshold1) {
    }
    
    if(info->flagthreshold2) {
    }
    
    if(info->flagmode1) {
    }
    
    if(info->flagmode2) {
    }
    
    if(info->flagdr) {
    }
    
    if(info->flagdtheta) {
    }
    
    if(info->flagn) {
    }
    
    if(info->flagnmin) {
    }
    
    if(info->flagnmax) {
    }
    
    if(info->flagImage) {
        info->fptImageList = fileOpen(info->ImageList, "r");
        fseek(info->fptImageList, 0L, SEEK_SET);
        i=0;
        while(NULL!=stringGetFromFile(s, "", info->fptImageList, stdout, 1)) {
            i++;
        }
        info->fptImage = (FILE**)memoryAllocate(i*sizeof(FILE*), "in init1");
        info->Image    = (char**)memoryAllocate(i*sizeof(char*), "in init1");
        info->flagImage = i;
        fseek(info->fptImageList, 0L, SEEK_SET);
        i=0;
        while(NULL!=stringGetFromFile(s, "", info->fptImageList, stdout, 1)) {
            info->Image[i] = stringGetNthWord(s, 1, " ,\t");
            info->fptImage[i] = fileOpen(info->Image[i],"r");
            i++;
        }
    }
    
    if(info->flagBack) {
        info->fptBackList = fileOpen(info->BackList, "r");
        fseek(info->fptBackList, 0L, SEEK_SET);
        i=0;
        while(NULL!=stringGetFromFile(s, "", info->fptBackList, stdout, 1)) {
            i++;
        }
        info->fptBack = (FILE**)memoryAllocate(i*sizeof(FILE*), "in init1");
        info->Back    = (char**)memoryAllocate(i*sizeof(char*), "in init1");
        info->flagBack = i;
        fseek(info->fptBackList, 0L, SEEK_SET);
        i=0;
        while(NULL!=stringGetFromFile(s, "", info->fptBackList, stdout, 1)) {
            info->Back[i] = stringGetNthWord(s, 1, " ,\t");
            info->fptBack[i] = fileOpen(info->Back[i],"r");
            i++;
        }
    }
    
    if(info->flagminx) {
    }
    
    if(info->flagmaxx) {
    }
    
    if(info->flagdelx) {
    }
    
    if(info->flagminy) {
    }
    
    if(info->flagmaxy) {
    }
    
    if(info->flagdely) {
    }
    
    if(info->flagminz) {
    }
    
    if(info->flagmaxz) {
    }
    
    if(info->flagdelz) {
    }
    
    if(info->flagrmin) {
    }
    
    if(info->flagrmax) {
    }
    
    if(info->flagconfigFile) {
        info->fptconfigFile = fileOpen(info->configFile, "r");
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
    sprintf(panepath, "%s/src/Tools/mrcImage/mrcImageSymmetryFind/src/mrcImageSymmetryFind.pane", eospath);
    khoros_initialize(argc, argv, "EOS");
    fpt = fopen(panepath, "r");    if(NULL!=fpt) {
        fclose(fpt);
        kclui_initialize(panepath, KGEN_NONE, "EOS", "mrcImageSymmetryFind",
                     func_usage_additions,
                     func_get_args,
                     func_free_args);
    }
}
#endif /* KHOROS */ 
