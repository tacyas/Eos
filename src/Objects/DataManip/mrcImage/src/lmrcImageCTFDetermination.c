/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% lmrcImageCTFDetemination ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : lmrcImageCTFDetemination 
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%mrcImageCTFDetermination ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  

#define UNDEBUG
#define UNDEBUG2
#include "genUtil.h"
#include "./lmrcImageCTFDetermination.h"


void 
lmrcImageCTFDetermination(lmrcImageCTFDeterminationInfo *linfo,
						  lmrcImageCTFDeterminationInfoRef *refinfo,
				    	   mrcImage* inFFT, mrcImage* refFFT,
						  lmrcImageCTFDeterminationInfoMode *Mode)
{
	ctfInfo  tmp;
	mrcImageParaTypeReal X, Y, delX, delY;
	mrcImageParaTypeReal def, ratio;
	double ctfWeight, R, inPhase, refPhase, inMag, inMagBeforeCTFCompensation, refMag; 
	double Phase, tmpPhase;
	double sumOfMagWeight, sumOfDeltaPhasexMagWeight;
	double magWeight, residual;
	int n;
	int flagminResidual=0;

	lmrcImageCheckSameSize(inFFT, refFFT);

	if(1!=inFFT->HeaderN.z) {
		fprintf(stderr, "2D Only Supported\n");
		fprintf(stderr, "Size inFFT(%d %d %d) refFFT(%d %d %d)\n",
						(int)inFFT->HeaderN.x, (int)inFFT->HeaderN.y, (int)inFFT->HeaderN.z,
						(int)refFFT->HeaderN.x, (int)refFFT->HeaderN.y, (int)refFFT->HeaderN.z);
		exit(EXIT_FAILURE);
	}

	DEBUGPRINT("in lmrcImageCTFDetermination\n");
	tmp = linfo->val;
	delX = 1.0/(inFFT->HeaderLength.x*inFFT->HeaderN.x);
	delY = 1.0/(inFFT->HeaderLength.y*inFFT->HeaderN.y);

	for(tmp.defocus=linfo->min.defocus, def=0;
		tmp.defocus<=linfo->max.defocus; 
		tmp.defocus += linfo->del.defocus, def++) {
		DEBUG2PRINT1("tmp.defocus:%f\n", tmp.defocus);

		for(tmp.ratioOfAmpToPhase=linfo->min.ratioOfAmpToPhase, ratio=0; 
			tmp.ratioOfAmpToPhase<=linfo->max.ratioOfAmpToPhase; 
			tmp.ratioOfAmpToPhase += linfo->del.ratioOfAmpToPhase, ratio++) {

			Phase = 0;
			n = 0;
			sumOfMagWeight = 0;
			sumOfDeltaPhasexMagWeight = 0;

			for(X=0; X<=inFFT->HeaderN.x/2.0; X++) {
				for(Y=-inFFT->HeaderN.y/2.0; Y<inFFT->HeaderN.y/2.0; Y++) {
					R = sqrt(SQR(X*delX) + SQR(Y*delY));
					if(R>linfo->Rmin && R<linfo->Rmax) {
						ctfWeight = ctfWeightForCorrection(&tmp, R, Mode->FilterType); 
						/*
						CTF = ctfFunction(&tmp, R, 0); 
						*/
						mrcPixelDataGet(inFFT,  X, Y, 0.0, &inPhase , mrcPixelPhase, mrcPixelHowNearest);
						mrcPixelDataGet(inFFT,  X, Y, 0.0, &inMagBeforeCTFCompensation, 
																      mrcPixelMag,   mrcPixelHowNearest);
						mrcPixelDataGet(refFFT, X, Y, 0.0, &refPhase, mrcPixelPhase, mrcPixelHowNearest);
						mrcPixelDataGet(refFFT, X, Y, 0.0, &refMag  , mrcPixelMag,   mrcPixelHowNearest);
						inMag = fabs(ctfWeight)*inMagBeforeCTFCompensation;

						if(ctfWeight<0) {
							tmpPhase = MIN_NORMAL_PHASE(inPhase - refPhase + M_PI);
						} else {
							tmpPhase = MIN_NORMAL_PHASE(inPhase - refPhase);
						}
						magWeight = MagWeightForCTFDetermine(inMag, refMag, Mode->WeightType);
						if(tmpPhase<0 || magWeight<0 || inMag < 0 || refMag <0) {
							fprintf(stderr, "Something wrong: negative value: tmpPhase: %f magWeight: %f\n", 
								tmpPhase, magWeight);
							fprintf(stderr, "							      ctfWeight: %f inMag: %f refMag: %f\n", 
								ctfWeight, inMag, refMag);
						}
						switch(Mode->SumType){
							case 0:{	
								Phase += tmpPhase;
								break;
							}	
							case 1:{	
								sumOfDeltaPhasexMagWeight += tmpPhase*magWeight;
								sumOfMagWeight            += magWeight;
								break;
							}	
							default: {
								fprintf(stderr, "Not supported mode : %ld in SumForCTFDetermine \n", Mode->SumType);	
								exit(EXIT_FAILURE);
							}
						}
						n++;
					}
				}
			}

			switch(Mode->SumType){
				case 0:{	
					residual = Phase/n;
					break;
				}	
				case 1:{	
					residual  = (sumOfDeltaPhasexMagWeight/sumOfMagWeight);
					break;
				}	
				default: {
					fprintf(stderr, "Not supported mode : %ld in SumForCTFDetermine \n", Mode->WeightType);	
					exit(EXIT_FAILURE);
				}
			}
			switch(flagminResidual){
				case 0:{
					DEBUG2PRINT("FIRST MIN");
					linfo->minResidual = residual;
					linfo->minDef   = tmp.defocus;
					linfo->minRatio = tmp.ratioOfAmpToPhase;
					flagminResidual=1;
				break;
				}
				case 1:{
					if(residual<linfo->minResidual) {
						DEBUG2PRINT("NOT FIRST MIN");
						linfo->minResidual = residual;
						linfo->minDef   = tmp.defocus;
						linfo->minRatio = tmp.ratioOfAmpToPhase;
					}
				break;
				}
				default: {
					fprintf(stderr, "Not supported flag: %d in flagminResidual\n", flagminResidual);	
					exit(EXIT_FAILURE);
				}
			}
			DEBUGPRINT4("%15.6e: (%15.6e, %15.6e) Iter: %15.6f\n", 
							residual, tmp.defocus, tmp.ratioOfAmpToPhase, refinfo->iter);
			mrcPixelDataSet(&(linfo->Dif), def, ratio, refinfo->iter, residual, mrcPixelRePart);
			DEBUGPRINT4("(x, y, z)=( %15.6f,%15.6f, %15.6f) residual: %15.6f\n", 
							def, ratio, refinfo->iter, residual);

		}/* tmp.ratioOfAmpToPhase */
	}/* tmp.defocus */
}

void 
lmrcImageCTFDeterminationResultFFT(lmrcImageCTFDeterminationInfo *linfo,
						             lmrcImageCTFDeterminationInfoRef *refinfo,
				    	              mrcImage* inFFT, mrcImage* refFFT,
						             lmrcImageCTFDeterminationInfoMode *Mode)
{
	ctfInfo  tmp;
	mrcImageParaTypeReal X, Y, delX, delY;
	double CTF, R, inPhase, refPhase; 
	double Phase;

	DEBUGPRINT("in lmrcImageCTFDeterminationResultFFT\n");

	lmrcImageCheckSameSize(inFFT, refFFT);

	if(1!=inFFT->HeaderN.z) {
		fprintf(stderr, "2D Only Supported\n");
		exit(EXIT_FAILURE);
	}

	tmp = linfo->val;
	delX = 1.0/(inFFT->HeaderLength.x*inFFT->HeaderN.x);
	delY = 1.0/(inFFT->HeaderLength.y*inFFT->HeaderN.y);

	tmp.defocus = refinfo->firstDf;
	tmp.ratioOfAmpToPhase = refinfo->firstAoverP;
	DEBUGPRINT2("df: %15.6f AoverP: %15.6f\n", refinfo->firstDf, refinfo->firstAoverP);

	Phase = 0;

	linfo->resFFT.HeaderN.x      = inFFT->HeaderN.x;
	linfo->resFFT.HeaderN.y      = inFFT->HeaderN.y;
	linfo->resFFT.HeaderN.z      = inFFT->HeaderN.z;
	linfo->resFFT.HeaderLength.x = inFFT->HeaderLength.x;
	linfo->resFFT.HeaderLength.y = inFFT->HeaderLength.y;
	linfo->resFFT.HeaderLength.z = inFFT->HeaderLength.z;
	linfo->resFFT.HeaderMode     = mrcComplexFloatFT;

	mrcInit(&linfo->resFFT, NULL);

	for(X=0; X<=inFFT->HeaderN.x/2.0; X++) {
		for(Y=-inFFT->HeaderN.y/2.0; Y<inFFT->HeaderN.y/2.0-1; Y++) {
			R = sqrt(SQR(X*delX) + SQR(Y*delY));
			if(R>linfo->Rmin && R<linfo->Rmax) {

				CTF = ctfFunction(&tmp, R, 0); 

				mrcPixelDataGet(inFFT,  X, Y, 0.0, &inPhase , mrcPixelPhase, mrcPixelHowNearest);
				mrcPixelDataGet(refFFT, X, Y, 0.0, &refPhase, mrcPixelPhase, mrcPixelHowNearest);

				if(CTF<0) {
					Phase = MIN_NORMAL_PHASE(inPhase - refPhase + M_PI);
				} else {
					Phase = MIN_NORMAL_PHASE(inPhase - refPhase);
				}
			
				mrcPixelDataSet(&linfo->resFFT, X, Y, 0.0,  cos(Phase), mrcPixelRePart);
				mrcPixelDataSet(&linfo->resFFT, X, Y, 0.0,  sin(Phase), mrcPixelImPart);


			}
		}
	}
}

double
MagWeightForCTFDetermine(double inMag, double refMag, long mode)
{
double weight;

	switch(mode){
		case 0:{	
			weight =1;
			break;
		}	
		case 1:{	
			weight = (inMag + refMag)/2;
			break;
		}	
		default: {
			fprintf(stderr, "Not supported mode : %ld in MagWeightForCTFDetermine \n", mode);	
			exit(EXIT_FAILURE);
		}
	}
	return weight;
}

void
lmrcImageCTFDeterminationCreateRefFilebyNearFar3DReconstInitializeLL
							(lmrcImageCTFDeterminationInfoRef *refinfo,
							lllDataCTFCompensateInfo *llctfinfo,
							lll2ltlgInfo *ll2ltlginfo,
							lltlg2mrcInfo *ltlg2mrcinfo)
{
}

void
lmrcImageCTFDeterminationCreateRefFilebyNearFar3DReconstInitializeMRC
							(lmrcImageCTFDeterminationInfoRef *refinfo,
							  mrcImageInformation* solinfo,
							 lmrcImageProjectionInfo *projinfo,
							 lmrcImageCrystalCreateInfo *cryinfo,
							 lmrcImagePadInfo *padinfo)
{
/* for info */
	lllExtractdYEstimateInfo extractdYinfo;
	refinfo->in  = (mrcImage*)memoryAllocate(sizeof(mrcImage), 
					"in lmrcImageCTFDeterminationCreateRefFilebyNearFar3DReconstInitializeMRC");
	mrcHeaderRead(refinfo->in, refinfo->In, 
					"in lmrcImageCTFDeterminationCreateRefFilebyNearFar3DReconstInitializeMRC", 0);
/* mrcImageInformation *solinfo */
	solinfo->mode     = 2; /* 2: mean of cylinder surface density at rmax */
	solinfo->rmax     = 250;
	solinfo->flagrmax = 1;
/* lmrcImageProjection *projinfo  */
	projinfo->mode = 1.0; /* y-z sufacae along x-axis */
/* lmrcImageCrystalCreate *cryinfo */
	extractdYinfo.truePitch = refinfo->truePitch;
	extractdYinfo.deltadY = 0.1;
	extractdYinfo.mag = 1.0;
	extractdYinfo.PixelSize = refinfo->PixelSize;
	cryinfo->nx = 1.0;
	cryinfo->ny = lllExtractdYEstimate(refinfo->in, &extractdYinfo);
	cryinfo->nz = 1.0;
	DEBUGPRINT1("ny %ld \n", cryinfo->ny);
/* lmrcImagePad *padinfo */
	padinfo->Width  = refinfo->Width; 
	padinfo->Height = cryinfo->ny*extractdYinfo.truePitch/extractdYinfo.PixelSize; 
	padinfo->Value  = 0; 
	padinfo->AWSize = 0; 
	DEBUGPRINT4("Width=%ld   Height=%ld   Value=%15.6f   AWSize=%15.6f\n", 
						padinfo->Width, padinfo->Height, padinfo->Value, padinfo->AWSize);

}

void
lmrcImageCTFDeterminationCreateRefFilebyNearFar3DReconstLL
							(lmrcImageCTFDeterminationInfoRef *refinfo,
							lllDataCTFCompensateInfo *llctfinfo,
							lll2ltlgInfo *ll2ltlginfo,
							lltlg2mrcInfo *ltlg2mrcinfo)
{
	char commandllExtractCtfinfFileCreate[200];
	char FilenameOutllExtractCtfinfFileCreate[100];
	char commandllDataCTFCompensate[200];
	char FilenameInllDataCTFCompensate[100];
	char FilenameOutllDataCTFCompensate[100];
	char commandll2ltlg[200];
	char FilenameInll2ltlg[100];
	char FilenameOutll2ltlg[100];
	char commandltlg2mrc[200];
	char FilenameInltlg2mrc[100];
	char FilenameOutltlg2mrc[100];
	char commandRM1[200];
	char commandRM2[200];
	char commandRM3[200];

	sprintf(FilenameOutllExtractCtfinfFileCreate, "%s.ctfinf",refinfo->Ref);
	sprintf(commandllExtractCtfinfFileCreate, "llExtractCtfinfFileCreate -o %s -df %f -A %f -m 1\n", 
						FilenameOutllExtractCtfinfFileCreate,
						refinfo->firstDf,
						refinfo->firstAoverP);
	DEBUGPRINT(commandllExtractCtfinfFileCreate);
	system(commandllExtractCtfinfFileCreate);

	sprintf(FilenameInllDataCTFCompensate,  "%s", refinfo->Ref);
	sprintf(FilenameOutllDataCTFCompensate, "%s.ctf", refinfo->Ref);
	sprintf(commandllDataCTFCompensate, "llDataCTFCompensate -i %s -o %s -I2  %s -t %f \n", 
				FilenameInllDataCTFCompensate,
				FilenameOutllDataCTFCompensate,
				FilenameOutllExtractCtfinfFileCreate,
				refinfo->truePitch);
	DEBUGPRINT(commandllDataCTFCompensate);
	system(commandllDataCTFCompensate);

	sprintf(FilenameInll2ltlg,  "%s", FilenameOutllDataCTFCompensate);
	sprintf(FilenameOutll2ltlg, "%s.ltlg", refinfo->Ref);
	sprintf(commandll2ltlg, "ll2ltlg -i %s -o %s -t %s -D 5000 -l 21 -R 5 -d 5 -r 250\n", 
				FilenameInll2ltlg,
				FilenameOutll2ltlg,
				FilenameOutll2ltlg);
	DEBUGPRINT(commandll2ltlg);
	system(commandll2ltlg);

	sprintf(FilenameInltlg2mrc,  "%s", FilenameOutll2ltlg);
	sprintf(FilenameOutltlg2mrc, "%s.mrc3d", refinfo->Ref);
	sprintf(commandltlg2mrc, "ltlg2mrc -i %s -o %s -d 5 -C 430 -r 250 -p 0 -zmi 0 -zma 425 -zde 5 -w 0.5 -a 0 -s 20\n", 
				FilenameInltlg2mrc,
				FilenameOutltlg2mrc);
	DEBUGPRINT(commandltlg2mrc);
	system(commandltlg2mrc);

	sprintf(refinfo->MrcOut, FilenameOutltlg2mrc);
	DEBUGPRINT1("MRC:%s\n",refinfo->MrcOut); 

	sprintf (commandRM1, "rm -f %s\n", FilenameOutllExtractCtfinfFileCreate);
	fprintf(stderr, commandRM1);
	system (commandRM1);
	sprintf (commandRM2, "rm -f %s\n", FilenameOutllDataCTFCompensate);
	fprintf(stderr, commandRM2);
	system (commandRM2);
	sprintf (commandRM3, "rm -f %s\n", FilenameOutll2ltlg);
	fprintf(stderr, commandRM3);
	system (commandRM3);
}

void
lmrcImageCTFDeterminationCreateRefFilebyNearFar3DReconstMRC
							(lmrcImageCTFDeterminationInfoRef *refinfo,
							  mrcImageInformation* solinfo,
							lmrcImageProjectionInfo *projinfo,
							lmrcImageCrystalCreateInfo *cryinfo,
							lmrcImagePadInfo *padinfo)
{
	mrcImage outsol;
	mrcImage outproj;
	mrcImage outcry;
	mrcImage outpad;
	lmrcImageSolventFlatteningInfo lsolfinfo;
	char commandRM[200];

/* mrc file allocate */
	DEBUGPRINT("in lmrcImageCTFDeterminationCreateRefFilebyNearFar3DReconstMRC\n");
	refinfo->in  = (mrcImage*)memoryAllocate(sizeof(mrcImage), 
					"in lmrcImageCTFDeterminationCreateRefFilebyNearFar3DReconstMRC");
	DEBUGPRINT1("MRC:%s in lmrcImageCTFDeterminationCreateRefFilebyNearFar3DReconstMRC\n",refinfo->MrcOut); 
	mrcFileRead(refinfo->in, refinfo->MrcOut, 
					"in lmrcImageCTFDeterminationCreateRefFilebyNearFar3DReconstMRC", 0);
/* lmrcImageInformation */
	lmrcImageInformation(solinfo, refinfo->in);
/* lmrcImageSolventFlatteing */
	lmrcImageSolventFlattening(&outsol, refinfo->in, &lsolfinfo, solinfo);
/* lmrcImageProjection */
	lmrcImageProjection(&outproj, refinfo->in, projinfo);						
	DEBUGPRINT("Projection Finished\n");
/* lmrcImageCrystalCreate */
	lmrcImageCrystalCreate(&outcry, &outproj, cryinfo);						
	DEBUGPRINT("Crystal Create Finished\n");
/* lmrcImagePad */
	lmrcImagePad(&outpad, &outcry, padinfo, 1); /* Pad average density of x=0 and x=MAX(x)(Image Center) */
	DEBUGPRINT("Pad Finished\n");
/* lmrcImageFFT */
	refinfo->out = (mrcImage*)memoryAllocate(sizeof(mrcImage), 
					"in lmrcImageCTFDeterminationCreateRefFilebyNearFar3DReconstMRC");
	lmrcImageFFT(refinfo->out, &outpad, 0);
	DEBUGPRINT("FFT Finished\n");

/* free */
	mrcImageFree(refinfo->in,"in lmrcImageCTFDeterminationCreateRefFilebyNearFar3DReconstMRC");
	sprintf (commandRM, "rm -f %s\n", refinfo->MrcOut);
	fprintf(stderr, commandRM);
	system (commandRM);
}
