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
init0(mrcImageLucasKanadeInfo* info)
{
    info->fptInVx = NULL;    info->flagInVx = 0;
    info->fptInVy = NULL;    info->flagInVy = 0;
    info->fptInVz = NULL;    info->flagInVz = 0;
    info->fptInVxList     = NULL;    info->fptInVxListList = NULL;    info->flagInVxList = 0;
    info->fptInVyList     = NULL;    info->fptInVyListList = NULL;    info->flagInVyList = 0;
    info->fptInVzList     = NULL;    info->fptInVzListList = NULL;    info->flagInVzList = 0;
    info->fptIn1Vx = NULL;    info->flagIn1Vx = 0;
    info->fptIn1Vy = NULL;    info->flagIn1Vy = 0;
    info->fptIn1Vz = NULL;    info->flagIn1Vz = 0;
    info->fptIn2Vx = NULL;    info->flagIn2Vx = 0;
    info->fptIn2Vy = NULL;    info->flagIn2Vy = 0;
    info->fptIn2Vz = NULL;    info->flagIn2Vz = 0;
    info->fptIn3Vx = NULL;    info->flagIn3Vx = 0;
    info->fptIn3Vy = NULL;    info->flagIn3Vy = 0;
    info->fptIn3Vz = NULL;    info->flagIn3Vz = 0;
    info->fptIn4Vx = NULL;    info->flagIn4Vx = 0;
    info->fptIn4Vy = NULL;    info->flagIn4Vy = 0;
    info->fptIn4Vz = NULL;    info->flagIn4Vz = 0;
    info->fptoutVx = NULL;    info->flagoutVx = 0;
    info->fptoutVy = NULL;    info->flagoutVy = 0;
    info->fptoutVz = NULL;    info->flagoutVz = 0;
    info->NOS = 4;    info->flagNOS = 0;
    info->fptSize = NULL;    info->flagSize = 0;
    info->fptconfigFile = NULL;    info->flagconfigFile = 0;
    info->mode = 0;    info->flagmode = 0;
}

void
init1(mrcImageLucasKanadeInfo* info)
{
    char s[1024];
    int i;
    if(info->flagInVx) {
        info->fptInVx = fileOpen(info->InVx, "r");
    }
    
    if(info->flagInVy) {
        info->fptInVy = fileOpen(info->InVy, "r");
    }
    
    if(info->flagInVz) {
        info->fptInVz = fileOpen(info->InVz, "r");
    }
    
    if(info->flagInVxList) {
        info->fptInVxListList = fileOpen(info->InVxListList, "r");
        fseek(info->fptInVxListList, 0L, SEEK_SET);
        i=0;
        while(NULL!=stringGetFromFile(s, "", info->fptInVxListList, stdout, 1)) {
            i++;
        }
        info->fptInVxList = (FILE**)memoryAllocate(i*sizeof(FILE*), "in init1");
        info->InVxList    = (char**)memoryAllocate(i*sizeof(char*), "in init1");
        info->flagInVxList = i;
        fseek(info->fptInVxListList, 0L, SEEK_SET);
        i=0;
        while(NULL!=stringGetFromFile(s, "", info->fptInVxListList, stdout, 1)) {
            info->InVxList[i] = stringGetNthWord(s, 1, " ,\t");
            info->fptInVxList[i] = fileOpen(info->InVxList[i],"r");
            i++;
        }
    }
    
    if(info->flagInVyList) {
        info->fptInVyListList = fileOpen(info->InVyListList, "r");
        fseek(info->fptInVyListList, 0L, SEEK_SET);
        i=0;
        while(NULL!=stringGetFromFile(s, "", info->fptInVyListList, stdout, 1)) {
            i++;
        }
        info->fptInVyList = (FILE**)memoryAllocate(i*sizeof(FILE*), "in init1");
        info->InVyList    = (char**)memoryAllocate(i*sizeof(char*), "in init1");
        info->flagInVyList = i;
        fseek(info->fptInVyListList, 0L, SEEK_SET);
        i=0;
        while(NULL!=stringGetFromFile(s, "", info->fptInVyListList, stdout, 1)) {
            info->InVyList[i] = stringGetNthWord(s, 1, " ,\t");
            info->fptInVyList[i] = fileOpen(info->InVyList[i],"r");
            i++;
        }
    }
    
    if(info->flagInVzList) {
        info->fptInVzListList = fileOpen(info->InVzListList, "r");
        fseek(info->fptInVzListList, 0L, SEEK_SET);
        i=0;
        while(NULL!=stringGetFromFile(s, "", info->fptInVzListList, stdout, 1)) {
            i++;
        }
        info->fptInVzList = (FILE**)memoryAllocate(i*sizeof(FILE*), "in init1");
        info->InVzList    = (char**)memoryAllocate(i*sizeof(char*), "in init1");
        info->flagInVzList = i;
        fseek(info->fptInVzListList, 0L, SEEK_SET);
        i=0;
        while(NULL!=stringGetFromFile(s, "", info->fptInVzListList, stdout, 1)) {
            info->InVzList[i] = stringGetNthWord(s, 1, " ,\t");
            info->fptInVzList[i] = fileOpen(info->InVzList[i],"r");
            i++;
        }
    }
    
    if(info->flagIn1Vx) {
        info->fptIn1Vx = fileOpen(info->In1Vx, "r");
    }
    
    if(info->flagIn1Vy) {
        info->fptIn1Vy = fileOpen(info->In1Vy, "r");
    }
    
    if(info->flagIn1Vz) {
        info->fptIn1Vz = fileOpen(info->In1Vz, "r");
    }
    
    if(info->flagIn2Vx) {
        info->fptIn2Vx = fileOpen(info->In2Vx, "r");
    }
    
    if(info->flagIn2Vy) {
        info->fptIn2Vy = fileOpen(info->In2Vy, "r");
    }
    
    if(info->flagIn2Vz) {
        info->fptIn2Vz = fileOpen(info->In2Vz, "r");
    }
    
    if(info->flagIn3Vx) {
        info->fptIn3Vx = fileOpen(info->In3Vx, "r");
    }
    
    if(info->flagIn3Vy) {
        info->fptIn3Vy = fileOpen(info->In3Vy, "r");
    }
    
    if(info->flagIn3Vz) {
        info->fptIn3Vz = fileOpen(info->In3Vz, "r");
    }
    
    if(info->flagIn4Vx) {
        info->fptIn4Vx = fileOpen(info->In4Vx, "r");
    }
    
    if(info->flagIn4Vy) {
        info->fptIn4Vy = fileOpen(info->In4Vy, "r");
    }
    
    if(info->flagIn4Vz) {
        info->fptIn4Vz = fileOpen(info->In4Vz, "r");
    }
    
    if(!info->flagoutVx) {
        stringGetFromFile(s, "outVx", stdin, stdout, 0);
        info->outVx = stringGetNthWord(s, 1, " ,\t");
        info->flagoutVx++;
    }
    if(info->flagoutVx) {
        info->fptoutVx = fileOpen(info->outVx, "w");
    }
    
    if(!info->flagoutVy) {
        stringGetFromFile(s, "outVy", stdin, stdout, 0);
        info->outVy = stringGetNthWord(s, 1, " ,\t");
        info->flagoutVy++;
    }
    if(info->flagoutVy) {
        info->fptoutVy = fileOpen(info->outVy, "w");
    }
    
    if(!info->flagoutVz) {
        stringGetFromFile(s, "outVz", stdin, stdout, 0);
        info->outVz = stringGetNthWord(s, 1, " ,\t");
        info->flagoutVz++;
    }
    if(info->flagoutVz) {
        info->fptoutVz = fileOpen(info->outVz, "w");
    }
    
    if(info->flagNOS) {
    }
    
    if(info->flagSize) {
        info->fptSize = fileOpen(info->Size, "w");
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
    sprintf(panepath, "%s/src/Tools/mrcImage/mrcImageLucasKanade/src/mrcImageLucasKanade.pane", eospath);
    khoros_initialize(argc, argv, "EOS");
    fpt = fopen(panepath, "r");    if(NULL!=fpt) {
        fclose(fpt);
        kclui_initialize(panepath, KGEN_NONE, "EOS", "mrcImageLucasKanade",
                     func_usage_additions,
                     func_get_args,
                     func_free_args);
    }
}
#endif /* KHOROS */ 
