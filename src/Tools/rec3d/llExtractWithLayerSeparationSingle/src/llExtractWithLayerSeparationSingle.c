/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% llExtractWithLayerSeparationSingle ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : llExtractWithLayerSeparationSingle
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%llExtractWithLayerSeparationSingle ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"

#define DEBUG
#include "genUtil.h"
#include "mrcImage.h"
#include "llData.h"

typedef struct lllExtractWithLayerSeparationSingleInfo {
	int Y;
	ctfInfo ctf;	
	llDataFittedParam paraFit; 		
} lllExtractWithLayerSeparationSingleInfo;

/*
typedef enum lllExtractWithLayerSeparationSingleMode {
	a=0,
	b=1
} lllExtractWithLayerSeparationSingleMode;
*/

int
main(int argc, char* argv[]) 
{
	llData ref;
	mrcImage* in;
	llData* out;
	llExtractWithLayerSeparationSingleInfo   info;
	lllExtractWithLayerSeparationSingleInfo* linfo;
	llDataParaTypeInteger status;
	int i, num;
	char s[1024];

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");
	llDataFileRead(info.fptRef, &ref, &status)
	num = info.flagIn;	
    in  = (mrcImage*)memoryAllocate(sizeof(mrcImage)*num, "main"); 	
    out = (llData*)memoryAllocate(sizeof(llData)*num, "main"); 	
    linfo = (lllExtractWithLayerSeparationSingle*)memoryAllocate(sizeof(lllExtractWithLayerSeparationSingle)*num, "main"); 	
	fseek(info.fptInList, 0L, SEEK_SET);
	for(i=0; i<num; i++) {
		mrcFileRead(&(in[i]), info.In[i], "main", 0);
		stringGetFromFile(s, "", info.fptInList, stdout, 3); 
		linfo.Y              = stringGetNthIntegerData(s, 2, " \t,"); 
		linfo[i].ctf.defocus = stringGetNthRealData(s, 3, " \t,"); 
		linfo[i].ctf.Cs      = stringGetNthRealData(s, 4, " \t,"); 
		linfo[i].ctf.kV      = stringGetNthRealData(s, 5, " \t,"); 
		linfo[i].ctf.AoverP  = stringGetNthRealData(s, 6, " \t,"); 
		linfo[i].paraFit.Para.r.Min     = info.rMin; 
		linfo[i].paraFit.Para.r.Max     = info.rMin; 
		linfo[i].paraFit.Para.r.Delta   = info.rDelta; 
		linfo[i].paraFit.Para.phi.Min   = info.phiMin; 
		linfo[i].paraFit.Para.phi.Max   = info.phiMin; 
		linfo[i].paraFit.Para.phi.Delta = info.phiDelta; 
		linfo[i].paraFit.Para.z.Min     = info.zMin; 
		linfo[i].paraFit.Para.z.Max     = info.zMin; 
		linfo[i].paraFit.Para.z.Delta   = info.zDelta; 
	}

	lllDataFit();

	llDataFileWrite(info->flagOut, &out, &status)
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
	fprintf(stderr, ">> In: Content <<\n");
	fprintf(stderr, "filename Y defocus[A] Cs[mm] AccV[kV] ratioOfAmpToPhase mode\n");
}

