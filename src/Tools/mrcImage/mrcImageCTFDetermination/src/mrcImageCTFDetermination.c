/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% mrcImageCTFDetermination ver %I%
#%Z% Created by tacyas
#%Z%
#%Z% Usage : mrcImageCTFDetermination
#%Z% Attention
#%Z%
*/

static char __sccs_id[] = "%Z%mrcImageCTFDetermination ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"

#define DEBUG
#include "genUtil.h"
#include "mrcImage.h"
#include "lmrcImageCTFDetermination.h"
#include "ctfInfo.h"
#include "lllExtractCtfinfFileCreate.h"

int
main(int argc, char* argv[]) 
{
	mrcImage in, inFFT, ref, refFFT;
	mrcImageCTFDeterminationInfo info;
	lmrcImageCTFDeterminationInfo linfo;
	lmrcImageCTFDeterminationInfoMode Mode;
	lmrcImageCTFDeterminationInfoRef refinfo;
	/*### lmrcImageCTFDeterminationCreateRefFilebyNerFar3DReconst ###*/
	lllDataCTFCompensateInfo llctfinfo;
	lll2ltlgInfo ll2ltlginfo;
	lltlg2mrcInfo ltlg2mrcinfo;
	mrcImageInformation solinfo;
	lmrcImageProjectionInfo projinfo;
	lmrcImageCrystalCreateInfo cryinfo;
	lmrcImagePadInfo padinfo;
	/*### out put file###*/
	infoDataList ctfResultInfo;
	ctfInfo CTFResultInfo;
	ctfInfoZeroPoint CTFInfoZeroPoint;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");

	DEBUGPRINT("CTF Determination\n");
	linfo.val.Ain   = info.Ain; 
	linfo.val.Cs    = info.Cs;
	linfo.val.kV    = info.kV;
	linfo.val.WhiteNoise = info.WhiteNoise;
	linfo.val.mode  = ctfInfoModePhaseAndAmpCTF;
	linfo.Rmax        = info.Rmax;
	linfo.Rmin        = info.Rmin;
	linfo.min.defocus = info.mindf;
	linfo.max.defocus = info.maxdf;
	linfo.del.defocus = info.deldf;
	linfo.min.ratioOfAmpToPhase= info.minAoverP;
	linfo.max.ratioOfAmpToPhase= info.maxAoverP;
	linfo.del.ratioOfAmpToPhase= info.delAoverP;

	linfo.Out      = info.fptOut;	
	linfo.flagOutF = info.flagOutF;

	Mode.FilterType  = info.mF;
	Mode.WeightType  = info.mW;
	Mode.SumType     = info.mS;
	Mode.CTFInfoType = info.mC;
	
	refinfo.fptIn        = info.fptIn;
	refinfo.In           = info.In;
	refinfo.fptRef       = info.fptRef;
	refinfo.Ref          = info.Ref;
	refinfo.fptOut       = info.fptOut;
	refinfo.Out          = info.Out;
	refinfo.Width        = info.Width;
	refinfo.PixelSize    = info.PixelSize;
	refinfo.truePitch    = info.truePitch;
	refinfo.firstDf      = info.firstDf;
	refinfo.withinDf     = info.withinDf;
	refinfo.firstAoverP  = info.firstAoverP;
	refinfo.withinAoverP = info.withinAoverP;
	refinfo.maxiter      = info.maxiter;

	linfo.Dif.HeaderLength.x = linfo.del.defocus;
	linfo.Dif.HeaderLength.y = linfo.del.ratioOfAmpToPhase;
	linfo.Dif.HeaderLength.z = 1.0;
	linfo.Dif.HeaderN.x = floor((linfo.max.defocus - linfo.min.defocus)/linfo.del.defocus) + 1;
	linfo.Dif.HeaderN.y = floor((linfo.max.ratioOfAmpToPhase - linfo.min.ratioOfAmpToPhase)
														     /linfo.del.ratioOfAmpToPhase) + 1;
	linfo.Dif.HeaderN.z = refinfo.maxiter;
	linfo.Dif.HeaderMode = mrcFloatImage;
	mrcInit(&(linfo.Dif), NULL);

	/* out file */ 
	ctfResultInfo.FirstZero     = 0;
	ctfResultInfo.flagFirstZero = 0;
	ctfResultInfo.Out           = info.OutC;
	ctfResultInfo.fptOut        = info.fptOutC;

	CTFResultInfo.Cs = info.Cs;
	CTFResultInfo.kV = info.kV;
	CTFResultInfo.mode = 1;
	CTFResultInfo.Ain  = info.Ain;

	CTFInfoZeroPoint.RMax = 0.1;
	CTFInfoZeroPoint.dR   = 0.0001;
	CTFInfoZeroPoint.N    = 1;

	switch(info.M) {
		case 0:{
			DEBUGPRINT("in M=0\n");
			mrcFileRead(&in, info.In, "in main", 0);  
			mrcFileRead(&ref, info.Ref, "in main", 0);  
			/*
			lmrcImageCheckFFT(&in , &inFFT);
			lmrcImageCheckFFT(&ref, &refFFT);
			lmrcImageCTFDetermination(&linfo, &refinfo, &inFFT, &refFFT, &Mode);
			*/
			lmrcImageCTFDetermination(&linfo, &refinfo, &in, &ref, &Mode);
			fprintf(linfo.Out, "(%f %f): %f\n", 	
								linfo.minDef, linfo.minRatio, linfo.minResidual);
		break;
		}
		case 1:{
			mrcFileRead(&in, info.In, "in main", 0);  
			lmrcImageCheckFFT(&in , &inFFT);

			for (refinfo.iter=0; refinfo.iter<=refinfo.maxiter ;refinfo.iter++) {
				DEBUGPRINT("in 3D Reconst\n");
				lmrcImageCTFDeterminationCreateRefFilebyNearFar3DReconstInitializeLL
									(&refinfo, &llctfinfo, &ll2ltlginfo, &ltlg2mrcinfo);
				DEBUGPRINT("Initial LL Set Finished\n");
				lmrcImageCTFDeterminationCreateRefFilebyNearFar3DReconstInitializeMRC
									(&refinfo,
									 &solinfo, &projinfo, &cryinfo, &padinfo);
				DEBUGPRINT("Initial MRC Set Finished\n");
				lmrcImageCTFDeterminationCreateRefFilebyNearFar3DReconstLL
									(&refinfo, &llctfinfo, &ll2ltlginfo, &ltlg2mrcinfo);
				DEBUGPRINT("LL Finished\n");
				lmrcImageCTFDeterminationCreateRefFilebyNearFar3DReconstMRC
									(&refinfo,
									 &solinfo, &projinfo, &cryinfo, &padinfo);
				DEBUGPRINT("MRC Finished\n");
				lmrcImageCTFDetermination(&linfo, &refinfo, &inFFT, refinfo.out, &Mode);
				LOGPRINT4(linfo.Out,"#", "#", "(%f %f): %f Iter:%15.6f",
									linfo.minDef, linfo.minRatio, linfo.minResidual, refinfo.iter);
				DEBUGPRINT4("(%f %f): %f Iter:%15.6f\n", 
									linfo.minDef, linfo.minRatio, linfo.minResidual, refinfo.iter);
				refinfo.firstDf     = linfo.minDef;
				refinfo.firstAoverP = linfo.minRatio;
			}
			break;
		}
		case 2:{
			mrcFileRead(&in, info.In, "in main", 0);  
			mrcFileRead(&ref, info.Ref, "in main", 0);  
			lmrcImageCheckFFT(&in , &inFFT);
			lmrcImageCheckFFT(&ref, &refFFT);
			lmrcImageCTFDeterminationResultFFT(&linfo, &refinfo, &inFFT, &refFFT, &Mode);
			if(linfo.flagOutF){
				mrcFileWrite(&(linfo.resFFT), info.OutF, "in main", 0);
			}
			break;
		}
		default:{
			fprintf(stderr, "Not supported Mode: %ld\n", info.M);
			exit(EXIT_FAILURE);
		}
	}

	if(info.flagOut2) {
		mrcFileWrite(&(linfo.Dif), info.Out2, "in main", 0);
	}

	if(info.flagOutC) {
		CTFResultInfo.defocus = linfo.minDef;
		CTFResultInfo.ratioOfAmpToPhase = linfo.minRatio;
		switch(info.mC) {
			case 0:{
				llExtractCtfinfFileCreateI(&ctfResultInfo, &CTFResultInfo, &CTFInfoZeroPoint);
				break;
			}
			case 1:{
				llExtractCtfinfFileCreateII(&ctfResultInfo, &CTFResultInfo);
				break;
			}
			default:{
				fprintf(stderr, "Not supported Mode: %ld\n", info.mC);
				exit(EXIT_FAILURE);
			}			
		}
	}

	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
	fprintf(stderr, "----- mrcFile -----\n");
	fprintf(stderr, "in  <- Original Image \n");
	fprintf(stderr, "ref <- CTF Compensated Image\n");
	fprintf(stderr, "----- in <- Fiter Type (-mF) -----\n");
	fprintf(stderr, "\t\t0: No CTF compensation\n");
	fprintf(stderr, "\t\t1: Phase only: W = CTF/|CTF|\n");
	fprintf(stderr, "\t\t2: Multiply  : W = CTF\n");
	fprintf(stderr, "\t\t3: Multiply  : W = 1/CTF\n");
	fprintf(stderr, "\t\t4: Wiener filter (constant noise): W = CTF/(|CTF|^2+N^2)\n");
	fprintf(stderr, "\t\t5: Multiply  : W = CTF^2\n");
	fprintf(stderr, "----- in <- Wight Type (-mW) -----\n");
	fprintf(stderr, "\t\t0: Weight = 1\n");
	fprintf(stderr, "\t\t1: Weight = (|in| + |ref|)/2\n");
	fprintf(stderr, "----- in <- Sum Type (-mS) -----\n");
	fprintf(stderr, "\t\t0: Sigma[Phase(i)]\n");
	fprintf(stderr, "\t\t1: Sigma[Phase(i)*Weight(i)] / Sigma[Weight(i)]\n");
	fprintf(stderr, "----- ref <- Type (-M) -----\n");
	fprintf(stderr, "\t\t0: CTF compensated single image\n");
	fprintf(stderr, "\t\t1: Three-dimentional reconstruction images that were made by \n");
	fprintf(stderr, "\t\t   nea and far Bessel separation.\n");
	fprintf(stderr, "\t\t   CTF compensatation were done between min defocus to max defocus.\n");
	fprintf(stderr, "\t\t   This mode is for myosin filaments.\n");
	fprintf(stderr, "\t\t   (Options) -PixelSize -Width -truePitch\n");
	fprintf(stderr, "\t\t             -dfRef -AoverPRef -MaxIter\n");
	fprintf(stderr, "\t\t2: Result FFT\n");
	fprintf(stderr, "\t\t   (Options) -oF, -dfRef, -AoverPRef\n");
	fprintf(stderr, "----- OutPut File-----\n");
	fprintf(stderr, "\t\t  -o : defocus and amlitude-contrast at minimum point\n");
	fprintf(stderr, "\t\t  -oP: mrc file\n");
	fprintf(stderr, "\t\t  -oC: ctf information file for ctf compensation\n");
	fprintf(stderr, "\t\t        Type (-mC)\n");
	fprintf(stderr, "\t\t        	0: lllExtractCtfinfFileCreate (mode 0) \n");
	fprintf(stderr, "\t\t        	1: lllExtractCtfinfFileCreate (mode 1) \n");
}

