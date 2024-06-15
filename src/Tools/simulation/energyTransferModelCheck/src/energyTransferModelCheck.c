/* 
typedef struct energyTransferPoint {
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% energyTransferModelCheck ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : energyTransferModelCheck
#%Z% Attention
#%Z%
*/

static char __sccs_id[] = "%Z%energyTransferModelCheck ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"

#undef DEBUG
#include "genUtil.h"
#include "eosString.h"
#include "Memory.h"
#include "mrcImage.h"
#include "mrcImage.h"
#include "lmrcImageAsProbability.h"
#include "lmrcImageBinarization.h"
#include "lmrcImageMultiplying.h"
#include "pdbFile.h"
#include "lpdb2mrcInfo.h"
#include "nr2.h"
#include "lFRET.h"

int
main(int argc, char* argv[]) 
{
	static energyTransferData etData; /* Energy Transfer Data */
	mrcImage* fix;             /* Unfixed point distribution estimated from fixed points only */
	mrcImage* unfix;           /* Unfixed point distribution estimated from unfixed points.   */
	pdbFile   pdb;             /* pdbFile for exluding */ 
	pdbFile*  pdbs;            /* pdbFile for exluding */ 
	mrcImage  exclude;
	mrcImage  mrc;
	mrcImage  exclBinary;
	mrcImage  rest;            /* mrcFile for restriction */
	mrcImage  restBinary;
	long n;

	energyTransferModelCheckInfo info; 
	static lenergyTransferModelCheckInfo linfo;
	static lpdb2mrc2dInfo lpdbInfo;
	static lmrcImageBinarizationInfo lbinaryInfo;

	long i;
	double max;
	char s[1024];
	FILE* fpt;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");
	/* Energy Transfer Data Read */
	energyTransferDataRead(&etData, info.fptIn, 0);
	energyTransferDataWrite(&etData, info.fptOut, 0);

	/* Data Allocation */
	fix   = (mrcImage*)memoryAllocate(sizeof(mrcImage)*etData.numUnfix, "in main");
	unfix = (mrcImage*)memoryAllocate(sizeof(mrcImage)*etData.numUnfix, "in main");

	if(0==info.startIter) { /* When first trial  */
		/* The 0th unfixed point distribution set */
		for(i=0; i<etData.numUnfix; i++) { /* Allocation for unfixed point distribution */
				unfix[i].HeaderMode = mrcDoubleImage;		
				unfix[i].HeaderN.x  = (info.endx - info.startx)/info.deltax + 1;
				unfix[i].HeaderN.y  = (info.endy - info.starty)/info.deltay + 1;
				unfix[i].HeaderN.z  = (info.endz - info.startz)/info.deltaz + 1;
				unfix[i].HeaderLength.x  = info.deltax;
				unfix[i].HeaderLength.y  = info.deltay;
				unfix[i].HeaderLength.z  = info.deltaz;
				unfix[i].HeaderStartN.x  = floor(info.startx/info.deltax+0.5);
				unfix[i].HeaderStartN.y  = floor(info.starty/info.deltay+0.5);
				unfix[i].HeaderStartN.z  = floor(info.startz/info.deltaz+0.5);
				mrcInit(&(unfix[i]), NULL);
				fix[i].Header = unfix[i].Header;
				mrcInit(&(fix[i]), NULL);
		}
		n=1; /* For lmrcImageAdd. n must be more than 0. */
		/* 
		The areas with zero of probability are determined in the below procedure. 
		   When initial probability of fix[i] is negative,
		   the probability is zero in the routine. 
		   This is because we can easily check whether the restricted/rejected areas are correct or not.
		*/
		/* Volume rejection by pdbFile */ 
		if(info.flagPDBs || info.flagPDB) {
			lpdbInfo.sx = info.startx;      lpdbInfo.sy = info.starty;      lpdbInfo.sz = info.startz;
			lpdbInfo.dx = info.deltax;      lpdbInfo.dy = info.deltay;      lpdbInfo.dz = info.deltaz;
			lpdbInfo.nx = fix[0].HeaderN.x; lpdbInfo.ny = fix[0].HeaderN.y; lpdbInfo.nz = fix[0].HeaderN.z;
			lpdbInfo.Weight = -1.0/sqrt(M_PI)/1.6;
			if(info.flagsigmaA) {
				lpdbInfo.Sigma  =  info.sigmaA;
			} else  {
				lpdbInfo.Sigma  =  info.sigma*info.deltax;
			}
		}
		/* Each unfixed point has a different pdb model to be excluded. */
		if(info.flagPDBs) {
			fprintf(stdout, "## Exclusion by PDBs\n");
			if(info.flagPDBs!=etData.numUnfix) {
				fprintf(stderr, "The number of pdbFiles is wrong: %d (unfixed point) != %ld (pdbFile)\n", 
					etData.numUnfix, info.flagPDBs);
				exit(EXIT_FAILURE);
			} else {
			 	pdbs = (pdbFile*)memoryAllocate(sizeof(pdbFile)*info.flagPDBs, "in main");
			}
			if(info.PDBsWithInfo) {
				fseek(info.fptPDBsList, 0L, SEEK_SET);		
			}
			for(i=0; i<etData.numUnfix; i++) { 
				linfo.excludedPDB = info.flagPDBs; 
				pdbFileRead(info.fptPDBs[i], &(pdbs[i]));
				if(info.PDBsWithInfo) {
					stringGetFromFile(s, "PW", info.fptPDBsList, stdout, 3);
					lpdbInfo.Sigma = stringGetNthRealData(s, 2, " ,\t");
				}
				exclude.Header = fix[i].Header; mrcInit(&exclude, NULL);
				lpdb2mrc3d(&exclude, &(pdbs[i]), &lpdbInfo, 0);  
				lmrcImageAdd(&(fix[i]), &exclude, &n);
				mrcImageFree(&exclude, "in main");
			}
		}
		/* Each unfixed point has the same model to be excluded. */
		if(info.flagPDB) { /* All unfixed point have a pdb model. */
			fprintf(stdout, "## Exclusion by PDB\n");
			linfo.excludedPDB = info.flagPDB; 
			pdbFileRead(info.fptPDB, &pdb);
			exclude.Header = fix[0].Header; mrcInit(&exclude, NULL);
			lpdb2mrc3d(&exclude, &pdb, &lpdbInfo, 0);  
			for(i=0; i<etData.numUnfix; i++) {
				lmrcImageAdd(&(fix[i]), &exclude, &n);  
			}
			mrcImageFree(&exclude, "in main");
		} 

		/* Volume rejection by mrcFile */ 
		if(info.flagMRCs || info.flagMRC) {
			lbinaryInfo.thresHold     = info.EContour;
			if(info.flagENearA) {
				lbinaryInfo.flagNear  = info.flagENearA; 
				lbinaryInfo.near      = info.ENearA/fix[0].HeaderLength.x; 
			} else {
				lbinaryInfo.flagNear  = info.flagENear; 
				lbinaryInfo.near      = info.ENear; 
			}
		}
		/* Each unfixed point has a different mrcFile to be excluded. */
		if(info.flagMRCs) {
			fprintf(stdout, "## Exclusion by MRCs\n");
			if(info.flagMRCs!=etData.numUnfix) {
				fprintf(stderr, "The number of mrcFiles is wrong: %d (unfixed point) != %ld (pdbFile)\n", 
					etData.numUnfix, info.flagMRCs);
				exit(EXIT_FAILURE);
			} 
			linfo.excludedPDB = info.flagMRCs; 
			if(info.MRCWithInfo) {
				fseek(info.fptMRCsList, 0L, SEEK_SET);		
			}
			for(i=0; i<etData.numUnfix; i++) { 
				mrcFileRead(&mrc, info.MRCs[i], "in main", 0);
				if(info.MRCWithInfo) {
					stringGetFromFile(s, "MRCW", info.fptMRCsList, stdout, 3);
					lbinaryInfo.thresHold = stringGetNthRealData(s, 2, " ,\t");
					lbinaryInfo.flagNear  = 1; 
					lbinaryInfo.near      = stringGetNthRealData(s, 3, " ,\t")/fix[i].HeaderLength.x; 
				}
				lmrcImageBinarization(&exclBinary, &mrc, lbinaryInfo, 0); 
				lmrcImageMultiplying2(&exclBinary, -1.0, 0);
				lmrcImageAdd(&(fix[i]), &exclBinary, &n);
				mrcImageFree(&mrc, "in main");
				mrcImageFree(&exclude, "in main");
			}
		}
		/* Each unfixed point has the same model to be excluded. */
		if(info.flagMRC) { /* All unfixed point have a pdb model. */
			fprintf(stdout, "## Exclusion by MRC\n");
			linfo.excludedPDB = info.flagMRC; 
			mrcFileRead(&mrc, info.MRC, "in main", 0);
			lmrcImageBinarization(&exclBinary, &mrc, lbinaryInfo, 0); 
			lmrcImageMultiplying2(&exclBinary, -1.0, 0);
			for(i=0; i<etData.numUnfix; i++) { 
				lmrcImageAdd(&(fix[i]), &exclBinary, &n);
			}
			mrcImageFree(&exclBinary, "in main");
			mrcImageFree(&mrc, "in main");
		} 

		/* Restriction by MRC */
		if(info.flagRests || info.flagRest) {
			lbinaryInfo.thresHold = info.Contour;
			if(info.flagNearA) {
				lbinaryInfo.flagNear  = info.flagNearA; 
				lbinaryInfo.near      = info.Near/fix[0].HeaderLength.x; 
			} else {
				lbinaryInfo.flagNear  = info.flagNear; 
				lbinaryInfo.near      = info.Near; 
			}
		}
		if(info.flagRests) {
			fprintf(stdout, "## Restriction by MRCs: flagRests\n");
			if(info.flagRests!=etData.numUnfix) {
				fprintf(stderr, "The number of files for restriction is wrong: %d (unfixed point) != %ld (Rests)\n", 
					etData.numUnfix, info.flagRests);
				exit(EXIT_FAILURE);
			}
			linfo.restriction = info.flagRests; 
			if(info.RestrictWithInfo) {
				fseek(info.fptRestsList, 0L, SEEK_SET);		
			}
			for(i=0; i<etData.numUnfix; i++) { 
				fprintf(stdout, "## %d %s\n", i, info.Rests[i]);  
				mrcFileRead(&rest, info.Rests[i], "in main", 0);
				if(info.RestrictWithInfo) {
					stringGetFromFile(s, "RW", info.fptRestsList, stdout, 3);
					lbinaryInfo.thresHold = stringGetNthRealData(s, 2, " ,\t");
					lbinaryInfo.near      = stringGetNthRealData(s, 3, " ,\t")/fix[i].HeaderLength.x;
					lbinaryInfo.flagNear  = 1;
				}
				lmrcImageBinarization(&restBinary, &rest, lbinaryInfo, 0); 
				lmrcImageAddedByReal(&restBinary, -1.0);
				lmrcImageAdd(&(fix[i]), &restBinary, &n);
				mrcImageFree(&restBinary, "in main");
				mrcImageFree(&rest, "in main");
			}
		}
		if(info.flagRest) { /* All unfixed point have the restriction area. */
			fprintf(stdout, "## Restriction by MRC: flagRest\n");	
			linfo.restriction = info.flagRest; 
			mrcFileRead(&rest, info.Rest, "in main", 0);
			lmrcImageBinarization(&restBinary, &rest, lbinaryInfo, 0); 
			lmrcImageAddedByReal(&restBinary, -1.0);
			for(i=0; i<etData.numUnfix; i++) {
				lmrcImageAdd(&(fix[i]), &restBinary, &n);
			}
			mrcImageFree(&restBinary, "in main");
			mrcImageFree(&rest, "in main");
		}

		/* Restriction by PDB */
		if(info.flagRestsP || info.flagRestP) {
			lpdbInfo.sx = info.startx;      lpdbInfo.sy = info.starty;      lpdbInfo.sz = info.startz;
			lpdbInfo.dx = info.deltax;      lpdbInfo.dy = info.deltay;      lpdbInfo.dz = info.deltaz;
			lpdbInfo.nx = fix[0].HeaderN.x; lpdbInfo.ny = fix[0].HeaderN.y; lpdbInfo.nz = fix[0].HeaderN.z;
			lpdbInfo.Weight = 1.0/sqrt(M_PI)/1.6;
			if(info.flagSigmaPA) {
				lpdbInfo.Sigma  = info.sigma;
			} else {
				lpdbInfo.Sigma  = info.deltax*info.sigma;
			}
			lbinaryInfo.thresHold = 0;
			if(info.flagNearPA) {
				lbinaryInfo.flagNear  = info.flagNearPA; 
				lbinaryInfo.near      = info.NearPA/fix[0].HeaderLength.x; 
			} else {
				lbinaryInfo.flagNear  = info.flagNearP; 
				lbinaryInfo.near      = info.NearP; 
			}
		}
		if(info.flagRestsP) {
			fprintf(stdout, "## Restriction by PDBs\n");	
			if(info.flagRestsP!=etData.numUnfix) {
				fprintf(stderr, "The number of files for restriction is wrong: %d (unfixed point) != %ld (Rests)\n", 
					etData.numUnfix, info.flagRestsP);
				exit(EXIT_FAILURE);
			} else {
			 	pdbs  = (pdbFile*) memoryAllocate(sizeof(pdbFile)*info.flagRestsP, "in main");
			}
			linfo.restriction = info.flagRestsP; 
			if(info.RestrictPW) {
				fseek(info.fptRestsPList, 0L, SEEK_SET);		
			}
			for(i=0; i<etData.numUnfix; i++) { 
				pdbFileRead(info.fptRestsP[i], &(pdbs[i]));
				if(info.RestrictPW) {
					stringGetFromFile(s, "PW", info.fptRestsPList, stdout, 3);
					lbinaryInfo.flagNear  = 1; 
					lbinaryInfo.near      = stringGetNthRealData(s, 2, " ,\t")/fix[i].HeaderLength.x; 
					lpdbInfo.Sigma        = stringGetNthRealData(s, 3, " ,\t");
				}
				rest.Header = fix[0].Header;
				mrcInit(&rest, NULL);
				lpdb2mrc3d(&rest, &(pdbs[i]), &lpdbInfo, 0);  
				lmrcImageBinarization(&restBinary, &rest, lbinaryInfo, 0); 
				lmrcImageAddedByReal(&restBinary, -1.0);
				lmrcImageAdd(&(fix[i]), &restBinary, &n);
				mrcImageFree(&restBinary, "in main");
				mrcImageFree(&rest, "in main");
			}
		} 
		if(info.flagRestP) { /* All unfixed point have the restriction area. */
			fprintf(stdout, "## Restriction by PDB\n");	
			linfo.restriction = info.flagRest; 
			mrcFileRead(&rest, info.Rest, "in main", 0);
			lmrcImageBinarization(&restBinary, &rest, lbinaryInfo, 0); 
			lmrcImageAddedByReal(&restBinary, -1.0);
			for(i=0; i<etData.numUnfix; i++) {
				lmrcImageAdd(&(fix[i]), &restBinary, &n);
			}
			mrcImageFree(&restBinary, "in main");
			mrcImageFree(&rest, "in main");
		}
	} else { /* When we checked once, */ 
		for(i=0; i<etData.numUnfix; i++) { /* Read Unfixed point distribution */
			sprintf(s, "%s.%s.%02ld",     info.Out, etData.unfix[i].ID, info.startIter - 1);
			mrcFileRead(&(unfix[i]), s, "in main", 0);
			sprintf(s, "%s.%s.%02ld.fix", info.Out, etData.unfix[i].ID, info.startIter - 1);
			mrcFileRead(&(fix[i]), s, "in main", 0);
		}
	}

	/* Starting Delta */
	linfo.flagStartingDelta = info.flagsdeltax;	
	linfo.sdx = info.sdeltax;
	linfo.sdy = info.sdeltay;
	linfo.sdz = info.sdeltaz;

	linfo.neglect = info.neglect;
	linfo.iter = info.startIter;          /* To be continued */

	while(linfo.iter < info.maxIter) { /* Iteration */
		lenergyTransferModelCheck(&etData, unfix, fix, linfo, 0); 

		/* Unfixed data output */
		for(i=0; i<etData.numUnfix; i++) {
			DEBUGPRINT("Unfix Data Output Start -----\n");
			sprintf(s, "%s.%s.%02d",     info.Out, etData.unfix[i].ID, linfo.iter);
			fpt = fopen(s, "w"); fclose(fpt);
			mrcFileWrite(&(unfix[i]), s, "in main", 0);
			sprintf(s, "%s.%s.%02d.fix", info.Out, etData.unfix[i].ID, linfo.iter);
			fpt = fopen(s, "w"); fclose(fpt);
			mrcFileWrite(&(fix[i]), s, "in main", 0);
			DEBUGPRINT("----- Unfix Data Output End\n");
		}

		/* Comparison with FRET data */
		lenergyTransferModelExpectedFRET(info.fptOut, &etData, unfix, linfo, 0); 
	
		/* Re-normalization */
		max = 0.0;
		for(i=0; i<etData.numUnfix; i++) {
			max = MAX(max, etData.unfix[i].probability);
		}
		for(i=0; i<etData.numUnfix; i++) {
			lmrcImageDividedByRealForOnlyPositive(&(unfix[i]), max);
			lmrcImageDividedByRealForOnlyPositive(&(  fix[i]), max);
		}

		linfo.iter++;
	}

	/* Distribution Output */
	for(i=0; i<etData.numUnfix; i++) {
		sprintf(s, "%s.%s",     info.Out, etData.unfix[i].ID);
		fpt = fopen(s, "w"); fclose(fpt);
		mrcFileWrite(&(unfix[i]), s, "in main", 0); /* Final Data */ 
		sprintf(s, "%s.%s.fix",     info.Out, etData.unfix[i].ID);
		fpt = fopen(s, "w"); fclose(fpt);
		mrcFileWrite(&(  fix[i]), s, "in main", 0); /* Fixed only Data */
	}
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
	fprintf(stderr, "----- Point Information : Each ID has no space character. -----\n");
	fprintf(stderr, "ID fix     x y z rootB radius(noUse)\n");
	fprintf(stderr, "......\n");
	fprintf(stderr, "ID unfix   x y z rootB radius\n");
	fprintf(stderr, "......\n");
	fprintf(stderr, "ID connect ID length rootB\n");
	fprintf(stderr, "......\n");
}


