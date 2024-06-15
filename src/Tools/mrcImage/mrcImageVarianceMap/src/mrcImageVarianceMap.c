/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% mrcImageVarianceMap ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : mrcImageVarianceMap
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%mrcImageVarianceMap ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"

#define DEBUG
#include "genUtil.h"
#include "Memory.h"
#include "mrcImage.h"
#include "lmrcImagesStatDataGet.h"
#include "lmrcImageMultiplying.h"

int
main(int argc, char* argv[]) 
{
	mrcImageVarianceMapInfo info;
	mrcImage* in=NULL;
	mrcImage* inNor=NULL;
	mrcImage  avgIn;
	mrcImage  avgNorIn;
	mrcImage  varIn;
	mrcImage  varNorIn;
	mrcImage* ref=NULL;
	mrcImage* refNor=NULL;
	mrcImage  avgRef;
	mrcImage  avgNorRef;
	mrcImage  varRef;
	mrcImage  varNorRef;
	mrcImage  avgInAndRef;
	mrcImage  varInAndRef;
	mrcImage Out;
	mrcImage OutV;
	int i;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");

	/* Read test files */
	if(info.flagIn) {
		in  = (mrcImage*)memoryAllocate(sizeof(mrcImage)*info.flagIn, "In ");
		for(i=0; i<info.flagIn; i++) {
			mrcFileRead(&(in[i]),  info.In[i],  "Read In in main", 0);
		}
		if(info.flagNorA && info.flagNorB) {
			inNor  = (mrcImage*)memoryAllocate(sizeof(mrcImage)*info.flagIn, "In ");
			for(i=0; i<info.flagIn; i++) {
				inNor[i] =  in[i];
				lmrcImageMultiplying(&(in[i]), &(inNor[i]), info.NorB,   mrcFloatImage); 
				mrcImageFree(&(inNor[i]), "");
				lmrcImageAddedByReal(&(in[i]), info.NorA);
			}
			free(inNor);
		}
	} else if(info.flagIn2) {
		mrcFileRead(&avgIn, info.In2,    "Read In in main", 0);
		mrcFileRead(&varIn, info.In2Var, "Read In in main", 0);
		if(info.flagNorA && info.flagNorB) {
			DEBUGPRINT("Normalize\n");
			avgNorIn = avgIn;
			varNorIn = varIn;
			lmrcImageMultiplying(&avgIn, &avgNorIn, info.NorB,   mrcFloatImage); 
			mrcImageFree(&avgNorIn, "");
			avgNorIn = avgIn;
			lmrcImageAddedByReal(&avgIn, info.NorA);
			lmrcImageMultiplying(&varIn, &varNorIn, info.NorB*info.NorB, mrcFloatImage); 
			mrcImageFree(&varNorIn, "");
		}
	} else {
		fprintf(stderr, "You need -I or -i \n");	
		usage(argv[0]);
		exit(EXIT_FAILURE);
	}

	/* Read reference files */
	if(info.flagRef) {
		ref = (mrcImage*)memoryAllocate(sizeof(mrcImage)*info.flagRef, "Ref");
		for(i=0; i<info.flagRef; i++) {
			mrcFileRead(&(ref[i]), info.Ref[i], "Read Ref in main", 0);
		}
		if(info.flagNorARef && info.flagNorBRef) {
			refNor  = (mrcImage*)memoryAllocate(sizeof(mrcImage)*info.flagRef, "Ref ");
			for(i=0; i<info.flagRef; i++) {
				refNor[i] =  ref[i];
				lmrcImageMultiplying(&(ref[i]), &(refNor[i]), info.NorBRef,   mrcFloatImage); 
				mrcImageFree(&(refNor[i]), "");
				lmrcImageAddedByReal(&(ref[i]), info.NorARef);
			}
			free(refNor);
		}
	} else if(info.flagRef2) {
		mrcFileRead(&avgRef, info.Ref2,    "Read Ref in main", 0);
		mrcFileRead(&varRef, info.Ref2Var, "Read Ref in main", 0);
		if(info.flagNorARef && info.flagNorBRef) {
			DEBUGPRINT("Normalize\n");
			avgNorRef = avgRef;
			varNorRef = varRef;
			lmrcImageMultiplying(&avgRef, &avgNorRef, info.NorBRef,   mrcFloatImage); 
			mrcImageFree(&avgNorRef, "");
			avgNorRef = avgRef;
			lmrcImageAddedByReal(&avgRef, info.NorARef);
			lmrcImageMultiplying(&varRef, &varNorRef, info.NorB*info.NorBRef, mrcFloatImage); 
			mrcImageFree(&varNorRef, "");
		}
	} else {
		fprintf(stderr, "You need -R or -r \n");	
		usage(argv[0]);
		exit(EXIT_FAILURE);
	}
	if(info.flagInAndRef2) {
		mrcFileRead(&avgInAndRef, info.InAndRef2,    "Read Ref in main", 0);
		mrcFileRead(&varInAndRef, info.InAndRef2Var, "Read Ref in main", 0);
	} else {
		if(info.flagIn && info.flagRef) { 
		} else {
			fprintf(stderr, "You need -R or -r \n");	
			usage(argv[0]);
			exit(EXIT_FAILURE);
		}
	}
	
	/* Student T-Test */
	if(info.flagIn && info.flagRef) {
		lmrcImagesVarianceMap(&Out, &OutV, in, info.flagIn, ref, info.flagRef, info.mode);
	} else if(info.flagIn2 && info.flagRef2) {
		lmrcImagesVarianceMap2(&Out, &OutV, &avgInAndRef, &varInAndRef, \
			&avgIn, &varIn, info.In2N, &avgRef, &varRef, info.Ref2N, info.mode);
	} else {
		fprintf(stderr, "You must use the combination of -R/-I or that of -r/-i \n");	
		usage(argv[0]);
		exit(EXIT_FAILURE);
	}

	if(info.flagOut) {
		mrcFileWrite(&Out, info.Out, "Write Out in main", 0); 
	}
	if(info.flagOutV) {
		mrcFileWrite(&OutV, info.OutV, "Write Out in main", 0);
	}
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
	lmrcImagesVarianceMapInformationPrint(stderr);
}

