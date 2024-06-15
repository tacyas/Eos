/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% mrcImageVarianceAnalysis ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : mrcImageVarianceAnalysis
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%mrcImageVarianceAnalysis ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"

#define DEBUG
#include "genUtil.h"
#include "File.h"
#include "eosString.h"
#include "Memory.h"
#include "mrcImage.h"
#include "lmrcImagesStatDataGet.h"
#include "lmrcImageMultiplying.h"

int
main(int argc, char* argv[]) 
{
	mrcImageVarianceAnalysisInfo info;
	mrcImage** in=NULL;
	mrcImage** inNor=NULL;
	int*       in1; 
	int        in2; 
	mrcImage Out;
	mrcImage OutV;
	int i, j;
	char s[1024];
	char* filename;
	double A, B;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");

	/* Read files */
	if(info.flagIn) {
		in2 = info.flagIn;
		if(in2<3) {
			fprintf(stderr, "You cannot analyze this algorithm because in2 is less than 3.");
			fprintf(stderr, "than 3.");
		}
		in     = (mrcImage**)memoryAllocate(sizeof(mrcImage*)*in2, "In ");
		inNor  = (mrcImage**)memoryAllocate(sizeof(mrcImage*)*in2, "In ");
		in1    = (int*)memoryAllocate(sizeof(int)*in2, "In "); 
		for(i=0; i<in2; i++) {
			in1[i]    = fileLineNumberGet2(info.fptIn[i], "#");
			in[i]     = (mrcImage*)memoryAllocate(sizeof(mrcImage)*in1[i], "In ");
			inNor[i]  = (mrcImage*)memoryAllocate(sizeof(mrcImage)*in1[i], "In ");

			for(j=0; j<in1[i]; j++) {
				stringGetFromFileWithSkippingComment(s, "", info.fptIn[i], stdout, 3);
				filename = stringGetNthWord(s, 1, " ,\t");
				A = stringGetNthRealData(s, 2, " ,\t");
				B = stringGetNthRealData(s, 3, " ,\t");
				mrcFileRead(&(in[i][j]),  filename,  "Read In in main", 0);
				inNor[i][j] =  in[i][j];
				lmrcImageMultiplying(&(in[i][j]), &(inNor[i][j]), B,   mrcFloatImage);
				mrcImageFree(&(inNor[i][j]), "");
				lmrcImageAddedByReal(&(in[i][j]), A);
			}
			free(inNor[i]);
		}
	} else {
		fprintf(stderr, "You need -I or -i \n");	
		usage(argv[0]);
		exit(EXIT_FAILURE);
	}

	/* Student T-Test */
	if(info.flagIn) {
		lmrcImagesVarianceAnalysis(&Out, &OutV, in, in1, in2, info.mode);
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
	fprintf(stderr, "-i inFileList\n");
	fprintf(stderr, ">>>>> Within inFileList\n");
	fprintf(stderr, "In1 \n");
	fprintf(stderr, "In2 \n");
	fprintf(stderr, "... \n");
	fprintf(stderr, ">>>>> Within In1 etc. A + B*density \n");
	fprintf(stderr, "filename1-1 A B \n");
	fprintf(stderr, ".....\n");
	lmrcImagesVarianceAnalysisInformationPrint(stderr);
}

