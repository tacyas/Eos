/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% llExtractWithLayerSeparation ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : llDatallExtractWithLayerSeparation
#%Z% Attention
#%Z%
*/

static char __sccs_id[] = "%Z%llDataWithLayerSeparation ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"

#define DEBUG
#include "genUtil.h"
#include "eosString.h"
#include "File.h"
#include "Memory.h"
#include "mrcImage.h"
#include "llData.h"
#include "ctfInfo.h"
#include "lllExtract.h"
#include "lllDataLowPassFiltering.h"
#include "lllDataDifferenceCalc.h"
#include "lllDataMergeDifferentN.h"
#include "lllDataContributionCalcDifferentN.h"
#include "lllDataCTF.h"
#include "lllDataFit.h"
#include "lllDataFitAndAverage.h"
#include "lllDataFitParamInverse.h"
#include "lllDataAxisSearch.h"
#include "lllDataRescaling.h"
#include "lllDataCTFCompensation.h"

typedef struct lllExtractWithLayerSeparationInfo {
	/* Fourier Space */ 
	char**           In;

	/* Separated LL Space */
	int              flagInLLNea;
	char**           InLLNea;
	FILE**           fptInLLNea;
	int              flagInLLFar;
	char**           InLLFar;
	FILE**           fptInLLFar;

	llDataParaTypeReal* weight;
	int                 fileNum;

	lllDataRescalingInfo*  rescaleInfo;
	llDataParamToFit    range;
	llDataFittedParam*  paraFit; 

	/* For Output */
	llData*          llSepASAvg;
	llData*          llSepDifASAvg;
	llData*          llSepNea;
	llData*          llSepFar;
	int              flagPvalueMap;
	char**           PvalueMap;
	int              flagQvalueMap;
	char**           QvalueMap;

	/* Log file */
	char*            Log;
	FILE*            fptLog;

	/* Continue */
	int              flagContinue;
	char*            Continue;
	FILE*			 fptContinue;
	int              flagForContinue;
	char*            ForContinue;
	FILE* 			 fptForContinue;

	/* Iteration Parameter */
	int times;
	int iter;
	int iter2;
	int iter3;

	/* Output Information */
	char*            Avg;
	char**           llSepASAvgOut; 

	/* Layer Line Separation Information */
	char**           llInfo;
	FILE**           fptllInfo;
	lllExtractInfo*  leInfo;

	/* Important Layer Line Separation */
	int 		     flagllInfoImportant;
	char**           llInfoImportant;
	FILE**           fptllInfoImportant;
	lllExtractInfo*  leInfoImportant;
	float            WeightOfllInfoImportant;
	float            WeightStartOfllInfoImportant;
	float            WeightStepOfllInfoImportant;

	/* Important Layer Line Separation */
	int 		     flagllInfoImportantForAxis;
	char**           llInfoImportantForAxis;
	FILE**           fptllInfoImportantForAxis;
	lllExtractInfo*  leInfoImportantForAxis;
	float            WeightOfllInfoImportantForAxis;
	float            WeightStartOfllInfoImportantForAxis;
	float            WeightStepOfllInfoImportantForAxis;
	
	int              flagtruePitch;
	double           truePitch;
	
	int flagrMax;
	lllDatarMaxLimitInfo rMaxInfo;

	int				 flagRMax;
	double           RMax;
	double           RMaxFirst;
	double           RMaxStep;
	double			 currentRMax;

	int				 flagRRMax;
	double           RRMax;
	double           RRMaxFirst;
	double           RRMaxStep;
	double			 currentRRMax;

	/* Iteration Control */ 
	int              MaxIteration;
	int				 flagMaxIteration2;
	int              MaxIteration2;
	int				 flagMaxIteration3;
	int              MaxIteration3;

	/* rms */
	double           rms;
	double           currentRMS;
	double           oldRMS;
	double           currentP;
	double           oldP;
	double           currentQ;
	double           oldQ;

	double           narrowSearch;
	double           nextTimes;
	double           lambda;

	int              flagBelow;
	float            threshold;
	
	int              noAntiPole;

	int              magLimit;

	int				 eachTime;

	/* CTF Compensation */
	int 			 flagCTF;
	int				 ctfMode;
	ctfInfo* 		 CTF;

	int 			 flagWhiteNoise;
	float            WhiteNoise;

	/* delBR */ 
	int 			 flagdelBR;
	double			 delBR;

	int              flagRef;
	char*            Ref;
	FILE*            fptRef;

	int              flagNormalization;
	lllDataDifferenceCalcInfo* DifCalcNea;	
	lllDataDifferenceCalcInfo* DifCalcFar;	
	lllDataDifferenceCalcInfo* DifCalcTotal;	

	int              algorism;
#ifdef PVM
	int flagpvmList;
	FILE* fptpvmList;
	int flagpvm;	
	int pvm;
#endif

} lllExtractWithLayerSeparationInfo;

extern void lllExtractWithLayerSeparationInfoSet(
							lllExtractWithLayerSeparationInfo* linfo, 
							llExtractWithLayerSeparationInfo  info);

extern void lllExtractWithLayerSeparationInfoPrint(
							FILE* fpt,
							lllExtractWithLayerSeparationInfo* linfo, 
							char* ID,
							int mode);

extern void lllExtractWithLayerSeparation0(
	llData* llAvg, 
	char**  In, 
	int     fileNumber, 
	lllExtractWithLayerSeparationInfo* linfo);

extern void lllExtractWithLayerSeparation1(
	llData* llAvg, 
	char**  In, 
	int     fileNumber, 
	lllExtractWithLayerSeparationInfo* linfo);

extern void lllExtractWithLayerSeparation2(
	llData* llAvg, 
	char**  In, 
	int     fileNumber, 
	lllExtractWithLayerSeparationInfo* linfo);

extern void
lllExtractInformationToBeContinuedRead(lllExtractWithLayerSeparationInfo* linfo, int mode);
extern void
lllExtractInformationToBeContinuedWrite(lllExtractWithLayerSeparationInfo* linfo, int mode);
extern void
lllExtractInitialization0(lllExtractWithLayerSeparationInfo* linfo, int filNumber, int mode);
extern void
lllExtractMixedLayerLine(llData** llMixNea, llData** llMaxFar, llDataFittedParam** paraFit, char** In, int filNumber, 
	lllExtractWithLayerSeparationInfo* linfo, int mode);

extern void 
lllExtractFittingParameterPrint(FILE* fpt, char** In, llDataFittedParam* paraFit, int filNumber, 
	lllExtractWithLayerSeparationInfo* linfo, int mode);

extern void
lllExtractNextStepParamterSet(FILE* fpt, llDataFittedParam* paraFit, int filNumber, lllExtractWithLayerSeparationInfo* linfo, int mode);

int
main(int argc, char* argv[]) 
{
	llData    llAvg;
	llExtractWithLayerSeparationInfo   info;
	lllExtractWithLayerSeparationInfo linfo;
	llDataParaTypeInteger mode;	
	
	int i, j;

	char  s[1024];
	FILE* fpt;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	lllExtractWithLayerSeparationInfoSet(&linfo, info);
	DEBUGPRINT("Program Start\n");
	switch(info.mode) {
		case 0: {
			LOGPRINT(linfo.fptLog, "#", "ALGORISM", "Share method")
			linfo.algorism = info.mode;
			lllExtractWithLayerSeparation0(&llAvg, info.In, info.flagIn, &linfo);
			break;
		}
		case 1: {
			LOGPRINT(linfo.fptLog, "#", "ALGORISM", "Least Sqare method")
			linfo.algorism = info.mode;
			lllExtractWithLayerSeparation0(&llAvg, info.In, info.flagIn, &linfo);
			break;
		}
		default: {
			fprintf(stderr, "Not supported mode: %ld\n", info.mode);
			exit(EXIT_FAILURE);
		}
	}
	/* Output */
	sprintf(s, "%s.%s", info.Out, info.InComment);
	fpt = fileOpen(s, "w");
	llDataFileWrite(fpt, &llAvg, &mode);

	if(info.flagOut2) {
		for(i=0; i<info.flagOut2; i++) {
			sprintf(s, "%s.%s", info.Out2[i], info.InComment);
			fpt = fileOpen(s, "w");
			llDataFileWrite(fpt, &(linfo.llSepASAvg[i]), &mode);
			fclose(fpt);
		}	
	}
	if(info.flagOut3) {
		for(i=0; i<info.flagOut3; i++) {
			sprintf(s, "%s.%s", info.Out3[i], info.InComment);
			fpt = fileOpen(s, "w");
			llDataFileWrite(fpt,  &(linfo.llSepDifASAvg[i]), &mode);
			fclose(fpt);
		}	

	}
	if(info.flagOut4) {
		for(i=0; i<info.flagOut4; i++) {
			sprintf(s, "%s.Nea.%s", info.Out4[i], info.InComment);
			fpt = fileOpen(s, "w");
			llDataFileWrite(fpt, &(linfo.llSepNea[i]), &mode);
			fclose(fpt);
			sprintf(s, "%s.Far.%s", info.Out4[i], info.InComment);
			fpt = fileOpen(s, "w");
			llDataFileWrite(fpt, &(linfo.llSepFar[i]), &mode);
			fclose(fpt);
		}	

	}
	/* Output Two subsets for resolution estimation */
	if(info.flagOut7) {
		int* phiNumber; 
		int  minPhiNumber; 
		int  maxPhiNumber; 
		double minPhi;
		double maxPhi;
		char  s1[1024];
		FILE* fpt1;
		char  s2[1024];
		FILE* fpt2;
		phiNumber = (int*)memoryAllocate(sizeof(int)*info.flagIn, "in two subsets");
		DEBUGPRINT("in two subsets\n");	
		maxPhi = linfo.paraFit[0].PPara.phi.Value*DEGREE; 
		minPhiNumber = 0;
		maxPhiNumber = 0;
		/* Initialize */
		for(i=0; i<info.flagIn; i++) {  
			phiNumber[i] = -1;
		}
		/* Search MaxPhi Number */
		for(i=0; i<info.flagIn; i++) {  
			if (maxPhi <= linfo.paraFit[i].PPara.phi.Value*DEGREE){
				maxPhi = linfo.paraFit[i].PPara.phi.Value*DEGREE;
				maxPhiNumber = i; 
			}
		}
		/* Search MinPhi Number */
		for(i=0; i<info.flagIn; i++) {
			minPhi = linfo.paraFit[maxPhiNumber].PPara.phi.Value*DEGREE; 
			for(j=0; j<info.flagIn; j++) {
				if (phiNumber[j] == -1 && minPhi >= linfo.paraFit[j].PPara.phi.Value*DEGREE){
					minPhi = linfo.paraFit[j].PPara.phi.Value*DEGREE;
					minPhiNumber = j;
				}
			}
			phiNumber [minPhiNumber] = i;
		}
		/* Result Display */
		for(i=0; i<info.flagIn; i++) {  
			fprintf(stderr, "Number=%d  Phi=%15.6f  PhiNumber=%d\n",
			i,linfo.paraFit[i].PPara.phi.Value*DEGREE, phiNumber[i]);
		}
		/* Text File Write */
		sprintf(s1, "%s.part1.%s", info.Out7, info.InComment);
		fpt1 = fileOpen(s1, "w");
		sprintf(s2, "%s.part2.%s", info.Out7, info.InComment);
		fpt2 = fileOpen(s2, "w");
		for(i=0; i<info.flagIn; i++) {
			sprintf(s, "%s.%s %15.6f %15.6f %15.6f %15.6f %15.6f %15.6f %15.6f %15.6f %15.6f\n", 
								info.Out2[i],
								info.InComment,
								linfo.weight[i],
								linfo.CTF[i].defocus,
								linfo.CTF[i].Cs,
								linfo.CTF[i].kV,
								linfo.CTF[i].ratioOfAmpToPhase,
								linfo.paraFit[i].PPara.phi.Value*DEGREE,
								linfo.paraFit[i].Para.z.Value,
								linfo.paraFit[i].Para.r.Value,
								linfo.paraFit[i].Para.R*DEGREE);
			if (IsEven(phiNumber[i])){
				fprintf(fpt1, s);
			} else {
				fprintf(fpt2, s);
			}
		}
		fclose(fpt1);
		fclose(fpt2);
	}
	/* Output Text: For Back Projection */
	if(info.flagOut8) {
		sprintf(s, "%s.%s", info.Out8, info.InComment);
		fpt = fileOpen(s, "w");
		for(i=0; i<info.symmetry; i++) {
			for(j=0; j<info.flagIn; j++) {
				sprintf(s, "%s YOYS %15.6f 0 0 \n", 
								info.In[j],
								linfo.paraFit[j].PPara.phi.Value*DEGREE+ i*360/info.symmetry);
				fprintf(fpt, s);
			}
		}
			fclose(fpt);
	}
	/* Output Text: x shift, z shift and dY information */
	if(info.flagOut9) {
		for(i=0; i<info.flagOut9; i++) {
			sprintf(s, "%s.%s", info.Out9[i], info.InComment);
			fpt = fileOpen(s, "w");
				sprintf(s, "%s %15.6f %15.6f %15.6f\n", 
								info.In[i],
								linfo.paraFit[i].Para.x.Value, 
								linfo.paraFit[i].Para.z.Value,
								linfo.weight[i]);
				fprintf(fpt, s);
			fclose(fpt);
		}	
	}
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
	fprintf(stderr, "-m 0: The 1st version algorism(Sharing)\n");
	fprintf(stderr, "-m 1: The 2nd version algorism(Least Square)\n");

	fprintf(stderr, ">> -ctf option <<\n");
	lllDataMultiCTFCompensationModePrint(stderr);
	fprintf(stderr, ">> If -ctf, the file list indicated by -i must include the below information\n");
	fprintf(stderr, "filename weight  defocus[A] Cs[mm] AccV[kV] ratioOfAmpToPhase mode\n");
	fprintf(stderr, ">> llDataSepartionControlFile <<\n");
	fprintf(stderr, "llMax(different)\n");
	fprintf(stderr, "nl Z numberOfN n0 n1 n2...\n");
}

void
lllExtractWithLayerSeparationInfoSet(lllExtractWithLayerSeparationInfo* linfo, 
									  llExtractWithLayerSeparationInfo  info)
{
	int i;

	DEBUGPRINT("Fitting Parameter Set\n"); 
	memoryClear(&(linfo->range), sizeof(linfo->range), 0);
	linfo->range.Omega.Min   = 0.0;
	linfo->range.Omega.Max   = 0.0;
	linfo->range.Omega.Delta = 1.0;
	linfo->range.x.Min       = info.shiftmin;
	linfo->range.x.Max       = info.shiftmax;
	linfo->range.x.Delta     = info.delshift;
	linfo->range.z.Min       = info.zmin;
	linfo->range.z.Max       = info.zmax;
	linfo->range.z.Delta     = info.delz;
	linfo->range.phi.Min     = info.phimin*RADIAN;
	linfo->range.phi.Max     = info.phimax*RADIAN;
	linfo->range.phi.Delta   = info.delphi*RADIAN;
	linfo->range.r.Min       = 1.0;
	linfo->range.r.Max       = 1.0;
	linfo->range.r.Delta     = 1.0;

	DEBUGPRINT("Information Setting\n"); 
	linfo->In        = info.In;
	linfo->fileNum   = info.flagIn;

	linfo->flagInLLNea  = info.flagInLLNea;
	if(linfo->flagInLLNea) {
		linfo->InLLNea = info.InLLNea;
		linfo->fptInLLNea = info.fptInLLNea;
	}
	linfo->flagInLLFar  = info.flagInLLFar;
	if(linfo->flagInLLFar) {
		linfo->InLLFar = info.InLLFar;
		linfo->fptInLLFar = info.fptInLLFar;
	}

	linfo->Log    	 = info.Log;
	linfo->fptLog    = info.fptLog;

	linfo->flagContinue   = info.flagContinue;
	linfo->Continue       = info.Continue;
	linfo->fptContinue    = info.fptContinue;
	linfo->flagForContinue= info.flagForContinue;
	linfo->ForContinue 	  = info.ForContinue;
	linfo->fptForContinue = info.fptForContinue;

	linfo->llInfo = info.llInfo;
	linfo->fptllInfo = info.fptllInfo;

	linfo->flagllInfoImportant = info.flagllInfoImp;
	linfo->llInfoImportant     = info.llInfoImp;
	linfo->fptllInfoImportant  = info.fptllInfoImp;
	linfo->WeightOfllInfoImportant = info.liWeight;  
	linfo->WeightStartOfllInfoImportant = info.liWeightStart;  
	linfo->WeightStepOfllInfoImportant = info.liWeightStep;  

	linfo->flagllInfoImportantForAxis = info.flagllInfoAxis;
	linfo->llInfoImportantForAxis     = info.llInfoAxis;
	linfo->fptllInfoImportantForAxis      = info.fptllInfoAxis;
	linfo->WeightOfllInfoImportantForAxis = info.laWeight;  
	linfo->WeightStartOfllInfoImportantForAxis = info.laWeightStart;  
	linfo->WeightStepOfllInfoImportantForAxis  = info.laWeightStep;  

	linfo->Avg           = info.Out;
	linfo->llSepASAvgOut = info.Out2;

	linfo->truePitch     = info.truePitch;
	linfo->flagtruePitch = info.flagtruePitch;
	
	linfo->flagrMax             = info.flagrMax;
	linfo->rMaxInfo.rMax 		= info.rMax;
	linfo->rMaxInfo.flagrMaxMin = info.flagrMaxMin;
	linfo->rMaxInfo.rMaxMin     = info.rMaxMin;

	linfo->RMax     = info.RMax;
	linfo->flagRMax = info.flagRMax;
	if(info.flagRMaxFirst) {
		linfo->RMaxFirst = info.RMaxFirst;
	} else {
		linfo->RMaxFirst = info.RMax;
	}
	linfo->RMaxStep = info.RMaxStep;

	linfo->RRMax     = info.RRMax;
	linfo->flagRRMax = info.flagRRMax;
	if(info.flagRRMaxFirst) {
		linfo->RRMaxFirst = info.RRMaxFirst;
	} else {
		linfo->RRMaxFirst = info.RRMax;
	}
	linfo->RRMaxStep = info.RRMaxStep;

	linfo->MaxIteration  = info.MaxIteration;
	linfo->flagMaxIteration2 = info.flagMaxIter2;
	if(linfo->flagMaxIteration2) {
		linfo->MaxIteration2 = info.MaxIter2;
	} else {
		linfo->MaxIteration2 = 1;
	}
	linfo->flagMaxIteration3 = info.flagMaxIter3;
	if(linfo->flagMaxIteration3) {
		linfo->MaxIteration3 = info.MaxIter3;
	} else {
		linfo->MaxIteration3 = 1;
	}
	linfo->rms          = info.rms;
	linfo->narrowSearch = info.narrowSearch*RADIAN;
	linfo->nextTimes    = info.nextTimes;
	linfo->lambda       = info.lambda;

	linfo->flagBelow    = info.flagbelow;
	linfo->threshold    = info.below*RADIAN;

	linfo->noAntiPole   = info.noantipole;

	linfo->magLimit = info.magLimit;

	linfo->eachTime = info.eachTime;

	linfo->flagCTF  = info.flagCTF;
	linfo->ctfMode  = info.CTF;
	if(linfo->flagCTF) {
		char s[1024];

		linfo->CTF    = (ctfInfo*)           memoryAllocate(sizeof(ctfInfo)*linfo->fileNum, "in ");
		linfo->weight = (llDataParaTypeReal*)memoryAllocate(sizeof(llDataParaTypeReal)*linfo->fileNum, "in ");
		fseek(info.fptInList, 0L, SEEK_SET); 
		for(i=0; i<linfo->fileNum; i++) {
			stringGetFromFile(s, "", info.fptInList, stdout, 3);			
			linfo->weight[i]                = stringGetNthRealData(s, 2, " ,\t");
			linfo->CTF[i].defocus           = stringGetNthRealData(s, 3, " ,\t");
			linfo->CTF[i].Cs                = stringGetNthRealData(s, 4, " ,\t");
			linfo->CTF[i].kV                = stringGetNthRealData(s, 5, " ,\t");
			linfo->CTF[i].ratioOfAmpToPhase = stringGetNthRealData(s, 6, " ,\t");
			linfo->CTF[i].mode              = ctfInfoModePhaseAndAmpCTF;
			linfo->CTF[i].Cc      = 0.0;
			linfo->CTF[i].Ain     = 0.0;
			linfo->CTF[i].BofMTF  = 0.0;
			linfo->CTF[i].MolecEnv = 0.0;
			linfo->CTF[i].flagWhiteNoise = info.flagWhiteNoise;
			linfo->CTF[i].WhiteNoise     = info.WhiteNoise;
		}
	}
	
	linfo->flagWhiteNoise = info.flagWhiteNoise;
	linfo->WhiteNoise     = info.WhiteNoise;

	linfo->flagRef      = info.flagRef;
	linfo->Ref          = info.Ref;
	linfo->fptRef       = info.fptRef;
	
	linfo->flagdelBR = info.flagdelBR;
	linfo->delBR = info.delBR;

	linfo->flagNormalization = info.Normalization;
	if(linfo->flagNormalization) {
		linfo->DifCalcNea = (lllDataDifferenceCalcInfo*)memoryAllocate(sizeof(lllDataDifferenceCalcInfo)*linfo->fileNum, "in set");
		linfo->DifCalcFar = (lllDataDifferenceCalcInfo*)memoryAllocate(sizeof(lllDataDifferenceCalcInfo)*linfo->fileNum, "in set");
		linfo->DifCalcTotal = (lllDataDifferenceCalcInfo*)memoryAllocate(sizeof(lllDataDifferenceCalcInfo)*linfo->fileNum, "in set");
	}
#ifdef PVM
	linfo->flagpvmList = info.flagpvmList;
	linfo->fptpvmList  = info.fptpvmList;
	linfo->flagpvm     = info.flagpvm;
	linfo->pvm         = info.pvm;
#endif
}

void
lllExtractWithLayerSeparationInfoPrint(
	FILE* fpt,
	lllExtractWithLayerSeparationInfo* linfo, 
	char* ID,
	int mode)
{
	int i;

	LOGPRINT1(fpt, ID, "#", "%s", "lllExtractWithSeparationInfo");	
	LOGPRINT1(fpt, ID, "#", "%s", "Fitting Parameter"); 
	LOGPRINT3(fpt, ID, "omega", "Min: %15.6f Max: %15.6f Delta: %15.6f",
		linfo->range.Omega.Min*DEGREE,
		linfo->range.Omega.Max*DEGREE,
		linfo->range.Omega.Delta*DEGREE);
	LOGPRINT3(fpt, ID, "x",   "Min: %15.6f Max: %15.6f Delta: %15.6f",
		linfo->range.x.Min,
		linfo->range.x.Max,
		linfo->range.x.Delta);
	LOGPRINT3(fpt, ID, "z",   "Min: %15.6f Max: %15.6f Delta: %15.6f",
		linfo->range.z.Min,
		linfo->range.z.Max,
		linfo->range.z.Delta);
	LOGPRINT3(fpt, ID, "phi", "Min: %15.6f Max: %15.6f Delta: %15.6f",
		linfo->range.phi.Min*DEGREE,
		linfo->range.phi.Max*DEGREE,
		linfo->range.phi.Delta*DEGREE);
	LOGPRINT3(fpt, ID, "r",   "Min: %15.6f Max: %15.6f Delta: %15.6f",
		linfo->range.r.Min,
		linfo->range.r.Max,
		linfo->range.r.Delta);

	LOGPRINT1(fpt, ID, "#", "%s", "Used File");
	LOGPRINT1(fpt, ID, "#", "%s", "Input File"); 
	for(i=0; i<linfo->fileNum; i++) {
		LOGPRINT1(fpt, ID, "fft(in)", "%s", linfo->In[i]);
	}
	if(linfo->flagInLLNea) {
		for(i=0; i<linfo->fileNum; i++) {
			LOGPRINT1(fpt, ID, "ll(in)", "%s", linfo->InLLNea[i]);
		}
	}
	if(linfo->flagInLLFar) {
		for(i=0; i<linfo->fileNum; i++) {
			LOGPRINT1(fpt, ID, "ll(in)", "%s", linfo->InLLFar[i]);
		}
	}
	if(NULL!=linfo->fptLog) {
		LOGPRINT1(fpt, ID, "log(out)", "%s", linfo->Log);
	} else {
		LOGPRINT1(fpt, ID, "log(out)", "%s", "NULL");
	}
	for(i=0; i<linfo->fileNum; i++) {
		LOGPRINT1(fpt, ID, "llinfo(in)", "%s", linfo->llInfo[i]);
	}
	if(NULL!=linfo->fptllInfoImportant) {
		for(i=0; i<linfo->fileNum; i++) {
			LOGPRINT4(fpt, ID, "llinfoImp(in)", "%15.6f %15.6f %15.6f : %s",
				linfo->WeightOfllInfoImportant, 
				linfo->WeightStartOfllInfoImportant, 
				linfo->WeightStepOfllInfoImportant, 
				linfo->llInfoImportant[i]);
		}
	} else {
		for(i=0; i<linfo->fileNum; i++) {
			LOGPRINT4(fpt, ID, "llinfoImp(in)", "%15.6f %15.6f %15.6f : %s", 
				linfo->WeightOfllInfoImportant, 
				linfo->WeightStartOfllInfoImportant, 
				linfo->WeightStepOfllInfoImportant, 
				"NULL");
		}
	}
	if(NULL!=linfo->fptllInfoImportantForAxis) {
		for(i=0; i<linfo->fileNum; i++) {
			LOGPRINT4(fpt, ID, "llinfoImpForAxis(in)", "%15.6f %15.6f %15.6f : %s", 
				linfo->WeightOfllInfoImportantForAxis, 
				linfo->WeightStartOfllInfoImportantForAxis, 
				linfo->WeightStepOfllInfoImportantForAxis, 
				linfo->llInfoImportantForAxis[i]);
		}
	} else {
		for(i=0; i<linfo->fileNum; i++) {
			LOGPRINT4(fpt, ID, "llinfoImpForAxis(in)", "%15.6f %15.6f %15.6f : %s", 
				linfo->WeightOfllInfoImportantForAxis, 
				linfo->WeightStartOfllInfoImportantForAxis, 
				linfo->WeightStepOfllInfoImportantForAxis, 
				"NULL");
		}
	}
	LOGPRINT1(fpt, ID, "avg(out)", "%s", linfo->Avg);

	LOGPRINT1(fpt, ID, "truePitch", "%15.6f", linfo->truePitch);
	LOGPRINT1(fpt, ID, "rMax",      "%15.6f", linfo->rMaxInfo.rMax);
	if(linfo->rMaxInfo.flagrMaxMin) {
		LOGPRINT1(fpt, ID, "rMaxMin",      "%15.6f", linfo->rMaxInfo.rMaxMin);
	} else {
		LOGPRINT1(fpt, ID, "rMaxMin",      "%15s", "NotDetermined");
	}
	LOGPRINT3(fpt, ID, "RMax",   "Max: %15.6f First: %15.6f Step: %15.6f", linfo->RMax,  linfo->RMaxFirst,  linfo->RMaxStep);
	LOGPRINT3(fpt, ID, "RRMax",  "Max: %15.6f First: %15.6f Step: %15.6f", linfo->RRMax, linfo->RRMaxFirst, linfo->RRMaxStep);
	LOGPRINT1(fpt, ID, "maxIter",  "%15d",   linfo->MaxIteration);
	LOGPRINT2(fpt, ID, "maxIter2", "%15d Use? %d",   linfo->MaxIteration2, linfo->flagMaxIteration2);
	LOGPRINT2(fpt, ID, "maxIter3", "%15d Use? %d",   linfo->MaxIteration3, linfo->flagMaxIteration3);
	LOGPRINT1(fpt, ID, "rms",     "%15.6f", linfo->rms);
	LOGPRINT1(fpt, ID, "narrowSearch",     "%15.6f", linfo->narrowSearch*DEGREE);
	LOGPRINT1(fpt, ID, "nextTimes",     "%15.6f", linfo->nextTimes);
	LOGPRINT1(fpt, ID, "lambda",  "%15.6f", linfo->lambda);
	LOGPRINT2(fpt, ID, "below",  "%2d : %15.6f", linfo->flagBelow, linfo->threshold);
	LOGPRINT1(fpt, ID, "noantipole",  "%2d", linfo->noAntiPole);
	LOGPRINT1(fpt, ID, "magLimit",  "%2d", linfo->magLimit);
	LOGPRINT1(fpt, ID, "eachTime",  "%2d", linfo->eachTime);
	LOGPRINT2(fpt, ID, "CTF", "flag: %2d mode: %2d", linfo->flagCTF, linfo->ctfMode);
	if(linfo->flagCTF) {
		for(i=0; i<linfo->fileNum; i++) {
			LOGPRINT6(fpt, ID, "CTF", "weight: %15.6f defocus: %15.6f Cs: %15.6f kV: %15.6f ratio: %15.6f : %s", 
				linfo->weight[i], 
				linfo->CTF[i].defocus,
				linfo->CTF[i].Cs,
				linfo->CTF[i].kV,
				linfo->CTF[i].ratioOfAmpToPhase,
				linfo->In[i]);
		}
	}
	LOGPRINT2(fpt, ID, "WhiteNoise", "noise: %15.6f mode: %4d", linfo->WhiteNoise, linfo->flagWhiteNoise);
	if(linfo->flagRef) {
		LOGPRINT1(fpt, ID, "ref(in)", "%s", linfo->Ref);
	} else {
		LOGPRINT1(fpt, ID, "ref(in)", "%s", "NULL");
	}
	if(linfo->flagdelBR) {
		LOGPRINT1(fpt, ID, "delBR", "%15.6f", linfo->delBR)
	} else {
		LOGPRINT1(fpt, ID, "delBR", "%s", "DefaultFromFFT")
	}
}

void 
lllExtractWithLayerSeparation0(
	llData* llAvg, 
	char**  In, 
	int     filNumber, 
	lllExtractWithLayerSeparationInfo* linfo)
{
	int i;
	int times, oldtimes;  /* Step number of Rmax and RRmax */
	int iter;   /* Iteration */ 
	int iter2;  /* Iteration of same Rmax and RRMax */
	int iter3;  /* Iteration of same Rmax, RRMax, Weight */
	double subStep;
	double rms, rmsFar, rmsNea, rmsAvg, oldrms;
	double totalP = M_PI, oldTotalP = M_PI;
	double totalQ = M_PI, oldTotalQ = M_PI;
	FILE* fpt;

	lllDataFitAndAverageInfo lfitinfo;
	llDataFittedParam* paraFit;
	llDataParaTypeInteger mode;	
	llDataParamToFit range;

	llData*   llMixNea;  /* Mixed Layer Line */
	llData*   llMixFar;
	llData    llEstNea;  /* Estimated Layer Line */
	llData    llEstFar;
	llData    llNorNea;  /* Estimated Layer Line */
	llData    llNorFar;
	llData*   llSepNea;  /* Separated Layer Line */
	llData*   llSepFar;
	llData    llSepWeight;  /* Separated Layer Line */
	llData*   llSepFitAvg;
	llData*   llSepDifNea;  /* Separated Layer Line */
	llData*   llSepDifFar;
	llData*   llSepASAvg;
	llData*   llSepDifASAvg;
	llData*   llDifNea;
	llData*   llDifFar;
	llData    llRef;
	llData    llNea;
	llData    llFar;
	llDataBoth srcLL;
	llDataBoth dstLL;
	llDataBoth* srcLLs;
	llDataBoth* dstLLs;
	double RMax;
	double RRMax;
	char s[1024];
	FILE* tmpfpt;
	llDataParaTypeInteger status;

	range = linfo->range;	
	fpt   = linfo->fptLog;

	LOGPRINT1(fpt,    "#", "#", "%s", "Start: in lllExtractWithLayerSeparation0");

	/* Log of Parameters */
	lllExtractWithLayerSeparationInfoPrint(fpt,    linfo, "INIT", 0);

	/* Continue */
	lllExtractInformationToBeContinuedRead(linfo, 0); 

	/* Initialization */
	lllExtractInitialization0(linfo, filNumber, 0);

	/*  Mixed Layer Line Extract */
	lllExtractMixedLayerLine(&llMixNea, &llMixFar, &paraFit, In, filNumber, linfo, mode);

	/* Initial Phase : The 0th turn for separation */
	LOGPRINT1(fpt, "#", "INIT", "%s", "Initial Separation Phase");
	times = 0;

	llSepNea  = (llData*)memoryAllocate(sizeof(llData)*filNumber, "in main");
	llSepFar  = (llData*)memoryAllocate(sizeof(llData)*filNumber, "in main");
	llDifNea  = (llData*)memoryAllocate(sizeof(llData)*filNumber, "in main");
	llDifFar  = (llData*)memoryAllocate(sizeof(llData)*filNumber, "in main");
	srcLLs    = (llDataBoth*)memoryAllocate(sizeof(llDataBoth)*filNumber, "in main");
	dstLLs    = (llDataBoth*)memoryAllocate(sizeof(llDataBoth)*filNumber, "in main");

	RMax  = linfo->RMaxFirst;
	RRMax = linfo->RRMaxFirst;
	LOGPRINT2(fpt,    "#", "INIT", "RMax: %15.6f RRMax: %15.6f", RMax, RRMax); 
	rms = 0;
	for(i=0; i<filNumber; i++) {
		/* Layer Line Separation */
		if(linfo->flagInLLNea&&linfo->flagInLLFar) { /* Already Separated */
			srcLL.Nea = llMixNea[i]; srcLL.Far = llMixFar[i];
			lllExtractWithSeparation(&dstLL, &srcLL, &(linfo->leInfo[i]), 0); 

			tmpfpt = fileOpen(linfo->InLLNea[i], "r");	
			llDataFileReadFollowingllData(tmpfpt, &(llSepNea[i]), &(dstLL.Nea), &status);	
			fclose(tmpfpt);
			tmpfpt = fileOpen(linfo->InLLFar[i], "r");	
			llDataFileReadFollowingllData(tmpfpt, &(llSepFar[i]), &(dstLL.Far), &status);	
			fclose(tmpfpt);

			llDataFree(&(dstLL.Nea));
			llDataFree(&(dstLL.Far));
		} else {                                     /* First time separation */
			srcLL.Nea = llMixNea[i]; srcLL.Far = llMixFar[i];
			dstLL.Nea = llSepNea[i]; dstLL.Far = llSepFar[i];
			lllExtractWithSeparation(&dstLL, &srcLL, &(linfo->leInfo[i]), 0); 
			llSepNea[i] = dstLL.Nea; llSepFar[i] = dstLL.Far;
		}

		lllDataLowPassFiltering(&(llSepNea[i]), RMax, lllDataLowPassFilteringModeSameMemorySize);
		lllDataLowPassFiltering(&(llSepFar[i]), RMax, lllDataLowPassFilteringModeSameMemorySize);

		lllDataRadialLowPassFiltering(&(llSepNea[i]), RRMax, lllDataLowPassFilteringModeSameMemorySize);
		lllDataRadialLowPassFiltering(&(llSepFar[i]), RRMax, lllDataLowPassFilteringModeSameMemorySize);

		/* Check of each filaments */
		llDataInitWithReference(&llEstNea, &(llMixNea[i])); 
		llDataInitWithReference(&llEstFar, &(llMixFar[i])); 

		srcLL.Nea = llSepNea[i]; srcLL.Far = llSepFar[i];
		dstLL.Nea = llEstNea;    dstLL.Far = llEstFar;
		lllDataMergeDifferentN(&dstLL, &srcLL, 1);
		llEstNea  = dstLL.Nea;   llEstFar = dstLL.Far;

		rmsNea = lllDataDifferenceCalc(&(llDifNea[i]), &(llMixNea[i]), &llEstNea, 0);
		rmsFar = lllDataDifferenceCalc(&(llDifFar[i]), &(llMixFar[i]), &llEstFar, 0);

		llDataFree(&llEstNea);
		llDataFree(&llEstFar);

		rmsAvg = sqrt((SQR(rmsNea) + SQR(rmsFar))/2.0); 
		rms    = sqrt(SQR(rms) + SQR(rmsAvg)); 
		LOGPRINT4(fpt,    "INIT", "DIF", "times: %04d : %04d %s rms: %15.6f", times, i, In[i], rmsAvg);
	}
	rms = sqrt(SQR(rms)/filNumber);
	LOGPRINT2(fpt,    "INIT", "DIF", "times: %04d total-rms: %15.6f", times, rms);


	DEBUGPRINT("Iteration Start\n");
	/* Initialization */	
	llSepDifNea   = (llData*)memoryAllocate(sizeof(llData)*filNumber, "in main");
	llSepDifFar   = (llData*)memoryAllocate(sizeof(llData)*filNumber, "in main");
	llSepDifASAvg = (llData*)memoryAllocate(sizeof(llData)*filNumber, "in main");
	llSepASAvg    = (llData*)memoryAllocate(sizeof(llData)*filNumber, "in main");
	for(i=0; i<filNumber; i++) {
		llDataInitWithReference2(&(llSepASAvg[i]), &(llSepNea[i]), AverageSide);
		llDataInitWithReference2(&(llSepDifASAvg[i]), &(llSepNea[i]), AverageSide);
	}
	llDataInitWithReference(&llRef, &(llSepASAvg[0]));
	llDataInitWithReference( llAvg, &(llSepASAvg[0]));
	llDataInitWithReference(&llNea, &(llSepNea[0]));
	llDataInitWithReference(&llFar, &(llSepFar[0]));
	llDataInitWithReference(&llSepWeight, &(llSepASAvg[0]));

	llSepFitAvg = (llData*)memoryAllocate(sizeof(llData)*filNumber, "in main");
	for(i=0; i<filNumber; i++) {
		llDataInitWithReference(&(llSepFitAvg[i]), llAvg);
	}
	oldrms = rms*2;
	times = oldtimes = iter = iter2 = iter3 = 0;
	while(times < linfo->MaxIteration 
	  &&  linfo->rms < fabs(rms-oldrms)) {
		DEBUGPRINT("Required: llSepNea/llSepFar and llDifNea/llDifFar\n");
		LOGPRINT4(fpt,    "ITER", "#", "times: %04d iter: %04d iter2: %04d %s", times, iter, iter2, "Iteration Phase");
		linfo->times = times; 			linfo->iter  = iter; linfo->iter2 = iter2; linfo->iter3 = iter3;
		oldtimes = times;

		DEBUGPRINT("---- Estimation of Intra-parameter : llSepASAvg ----\n");
		LOGPRINT5(fpt,    "ITER", "Axis", "times: %04d iter: %04d iter2: %04d RMax: %15.6f RRMax: %15.6f", times, iter, iter2, RMax, RRMax);
		for(i=0; i<filNumber; i++) {
			if(linfo->flagllInfoImportantForAxis) {
			 	float weight;
				weight = linfo->WeightStartOfllInfoImportantForAxis + (iter2 - iter3/linfo->MaxIteration3)*linfo->WeightStepOfllInfoImportantForAxis;
				if(linfo->WeightStepOfllInfoImportantForAxis < 0) {
					weight = MAX(weight, linfo->WeightOfllInfoImportantForAxis);
				} else {
					weight = MIN(weight, linfo->WeightOfllInfoImportantForAxis);
				}
				LOGPRINT5(fpt,    "ITER", "Axis", "times: %04d iter: %04d iter2: %04d iter3: %04d WeightOfImportantAxis: %15.6f", times, iter, iter2, iter3, weight);
				lllExtractWeightSetFollowingllExtractInfo(&llSepNea[i], 
					&(linfo->leInfoImportantForAxis[i]), weight, 0);
				lllExtractWeightSetFollowingllExtractInfo(&llSepFar[i], 
					&(linfo->leInfoImportantForAxis[i]), weight, 0);
			} else {
				lllExtractWeightSetFollowingllExtractInfo(&llSepNea[i], 
					&(linfo->leInfo[i]), 1.0, 0);
				lllExtractWeightSetFollowingllExtractInfo(&llSepFar[i], 
					&(linfo->leInfo[i]), 1.0, 0);
			}
		}

		DEBUGPRINT("AxisSearch And Average\n");
		for(i=0; i<filNumber; i++) {
			lllDataAxisSearchAndAverage(&(llSepASAvg[i]), &(llSepNea[i]), &(llSepFar[i]),
				&(paraFit[i]), 
				lllDataAxisSearchModeSearchProcessPrint|lllDataAxisSearchModeSearchProcessSameLLStructure);
			DEBUGPRINT2("AxisSearch: %f -> %f at (0, 0)\n", llSepNea[i].LL[0].data[0].Re, llSepASAvg[i].LL[0].data[0].Re);
			LOGPRINT8(fpt, "ITER", "Axis", "times: %04d iter: %04d iter2: %04d R: %15.6f x: %15.6f omega: %15.6f : %04d %s", 
										times,
										iter,
										iter2,
										paraFit[i].Para.R*DEGREE, 
									   	paraFit[i].Para.x.Value, 
									   	paraFit[i].Para.Omega.Value,
										i,	
										In[i]);
		}

		DEBUGPRINT("----- llRef Set -----\n");
		if(iter==0) { /* First Model */
			if(linfo->flagRef) { /* Reference */
				llDataFileReadFollowingllData(linfo->fptRef, &llRef, llAvg, &mode); 
				LOGPRINT4(fpt,    "ITER", "Ref", "times: %04d iter: %04d iter2: %04d Reference: %s", times, iter, iter2, linfo->Ref);
			} else {             /* No reference */
				LOGPRINT4(fpt,    "ITER", "Ref", "times: %04d iter: %04d iter2: %04d Reference: %s", times, iter, iter2, linfo->In[0]);
				lllDataCopy(&llRef, &(llSepASAvg[0]));
				if(linfo->flagCTF) {
					lllDataSingleCTFCompensationInfo sinfo;
					sinfo.flagllCTF = 0;
					sinfo.CTF       = linfo->CTF[0];
					DEBUGPRINT2("Before llRef: %f %f at (0,0)\n", llRef.LL[0].data[0].Re, llRef.LL[0].data[0].Im);
					DEBUGPRINT2("Before llSep: %f %f at (0,0)\n", llSepASAvg[0].LL[0].data[0].Re, llSepASAvg[0].LL[0].data[0].Im);
					lllDataSingleCTFCompensation(&llRef, &llRef, sinfo, linfo->ctfMode);
					DEBUGPRINT2("After  llRef: %f %f at (0,0)\n", llRef.LL[0].data[0].Re, llRef.LL[0].data[0].Im);
				}
				LOGPRINT4(fpt,    "ITER", "Ref", "times: %04d iter: %04d iter2: %04d Reference: %s", times, iter, iter2, In[0]);
			}
			lllDatarMaxLimit(&llRef, linfo->rMaxInfo, 0);
			lllDataLowPassFiltering      (&llRef, linfo->RMax,  lllDataLowPassFilteringModeSavedMemorySize);
			lllDataRadialLowPassFiltering(&llRef, linfo->RRMax, lllDataLowPassFilteringModeSavedMemorySize);
		} else {       /* New Model */
			LOGPRINT4(fpt,    "ITER", "Ref", "times: %04d iter: %04d iter2: %04d Reference: %s", times, iter, iter2, "llAvg");
			lllDataCopy(&llRef, llAvg);
		}

		LOGPRINT5(fpt,    "ITER", "Ref", "times: %04d iter: %04d iter2: %04d RMax: %15.6f RRMax: %15.6f", times, iter, iter2, RMax, RRMax);
		if(RMax<linfo->RMax) {
			lllDataLowPassFiltering      (&llRef, RMax,  lllDataLowPassFilteringModeSameMemorySize);
		}
		if(RRMax<linfo->RRMax) {
			lllDataRadialLowPassFiltering(&llRef, RRMax, lllDataLowPassFilteringModeSameMemorySize);
		}

		if(linfo->flagllInfoImportant) {
			float weight;

			weight = linfo->WeightStartOfllInfoImportant + iter2*linfo->WeightStepOfllInfoImportant;
			if(linfo->WeightStepOfllInfoImportant < 0) {
				weight = MAX(weight, linfo->WeightOfllInfoImportant);
			} else {
				weight = MIN(weight, linfo->WeightOfllInfoImportant);
			}
			lllExtractWeightSetFollowingllExtractInfo(&llRef, &(linfo->leInfoImportant[0]), weight, 0);
			LOGPRINT5(fpt,    "ITER", "Ref", "times: %04d iter: %04d iter2: %04d iter3: %04d WeightOfImporantFit: %15.6f ", times, iter, iter2, iter3, weight);
		} else {
			lllExtractWeightSetFollowingllExtractInfo(&llRef, &(linfo->leInfo[0]),          1.0,    0);
		}

		DEBUGPRINT("----- Set FitAndAverageParameters -----\n");
		if(iter==0) { /* First Try */
			memoryClear(&lfitinfo, sizeof(lfitinfo), 0);
			lfitinfo.times          = times;
			lfitinfo.nFile          = filNumber;
			lfitinfo.flagOutParam2  = 0; 
			lfitinfo.OutParam2      = NULL; 
			lfitinfo.fptLog         = linfo->fptLog;
			lfitinfo.In             = linfo->In;
			lfitinfo.flagCTF        = linfo->flagCTF;
			lfitinfo.CTF            = linfo->CTF;
			lfitinfo.ctfMode        = linfo->ctfMode;
			lfitinfo.weight         = linfo->weight;
			lfitinfo.noise          = linfo->WhiteNoise;
			lfitinfo.flagAveragingBelowThreshold = linfo->flagBelow;	
			lfitinfo.threshold                   = linfo->threshold;	
			lfitinfo.flagAveragingWithoutAntiPole = linfo->noAntiPole;	
			lfitinfo.mode           = PVALUE_MODE|lllDataFitFitProcessPrint;
		 	if(lfitinfo.flagCTF) { 
				for(i=0; i<filNumber; i++) {
					llDataInitWithReference(&(paraFit[i].Para.llCTF), &llRef);
					lllDataFitllCTFSet(&(paraFit[i].Para.llCTF), paraFit[i].Para.CTF, 0);
					paraFit[i].Para.flagllCTF = 1;
					paraFit[i].PPara.llCTF     = paraFit[i].Para.llCTF; 
					paraFit[i].PPara.flagllCTF = paraFit[i].Para.flagllCTF; 
				}
			}
#ifdef PVM
    		if(linfo->flagpvmList) {
        		lfitinfo.flagPVM = 1;
        		lllDataFitServerStart(&(lfitinfo.vPVM), linfo->fptpvmList, 0);
    		} else if(linfo->flagpvm) {
        		lfitinfo.flagPVM = 1;
        		lllDataFitServerStart(&(lfitinfo.vPVM), NULL, linfo->pvm);
    		} else {
        		lfitinfo.flagPVM = 0;
    		}
#endif
		}
		DEBUGPRINT("----- FitAndAverage Start -----\n");
		LOGPRINT2(fpt, "ITER", "Fit", "PVM: flag %d numTask: %d\n", lfitinfo.flagPVM, lfitinfo.vPVM.numTask);
		LOGPRINT5(fpt, "ITER", "Fit", "times: %04d iter: %04d iter2: %04d RMax: %15.6f RRMax: %15.6f", times, iter, iter2, RMax, RRMax);
		lllDataFitAndAverage(llAvg, llSepFitAvg, llSepASAvg, llRef, paraFit, lfitinfo); 
		lllExtractFittingParameterPrint(fpt, In, paraFit, filNumber, linfo, 0);

		switch(linfo->algorism) {
			case 0: {
				break;
			}
			case 1: {
				for(i=0; i<filNumber; i++) {
					srcLLs[i].Nea = llMixNea[i];   srcLLs[i].Far = llMixFar[i];
				}
				lllExtractWithSeparationUsingFittingParameter(llAvg, srcLLs, paraFit, 
						filNumber, linfo->leInfo, 1);
				break;
			}
			default: {
				fprintf(stderr, "Not supported Alogrism");
				exit(EXIT_FAILURE);
				break;
			}
		}

		DEBUGPRINT("----- Estimation of each filament : llSepNea and llSepFar -----\n"); 
		lllDataAvgToNea(&llNea, llAvg);
		lllDataAvgToFar(&llFar, llAvg);
		for(i=0; i<filNumber; i++) {
			lllDataPhaseShiftInverse(&(llSepNea[i]), &llNea, &(paraFit[i]));  
			lllDataPhaseShiftInverse(&(llSepFar[i]), &llFar, &(paraFit[i])); 
			if(linfo->flagCTF) {
				switch(linfo->ctfMode) {
					case 0: {
						lllDataCTFObservation(&(llSepNea[i]), paraFit[i].Para.CTF, 0);
						lllDataCTFObservation(&(llSepFar[i]), paraFit[i].Para.CTF, 0);
						break;
					}
					case 1: {
						lllDataCTFObservation(&(llSepNea[i]), paraFit[i].Para.CTF, 1);
						lllDataCTFObservation(&(llSepFar[i]), paraFit[i].Para.CTF, 1);
						break;
					}
					default: {
						fprintf(stderr, "Not supported Mode: linfo->ctfMode: %d \n", linfo->ctfMode);
						exit(EXIT_FAILURE);
					}
				}
			}
		}

		DEBUGPRINT("----- Output Information For Continue -----\n"); 
		lllExtractInformationToBeContinuedWrite(linfo, 0); 

		DEBUGPRINT("----- Evaluation of each filament : llDifNea and llDifFar -----\n");
		for(i=0, rms=0; i<filNumber; i++) {
			llDataInitWithReference(&llEstNea, &(llMixNea[i])); 
			llDataInitWithReference(&llEstFar, &(llMixFar[i])); 

			srcLL.Nea = llSepNea[i]; srcLL.Far = llSepFar[i];
			dstLL.Nea = llEstNea;    dstLL.Far = llEstFar;
			lllDataMergeDifferentN(&dstLL, &srcLL, 1);
			llEstNea = dstLL.Nea; llEstFar = dstLL.Far;

			if(linfo->flagNormalization) {
				llDataInitWithReference(&llNorNea, &(llMixNea[i])); 
				llDataInitWithReference(&llNorFar, &(llMixFar[i])); 
				DEBUGPRINT5("%f = (%f=test(%f)/%f)-ref(%f) : Before\n", 
					llDifNea[i].LL[0].data[0].F,
					llNorNea.LL[0].data[0].F,
					llMixNea[i].LL[0].data[0].F,
					linfo->DifCalcNea[i].A,
					llEstNea.LL[0].data[0].F);
				rmsNea = lllDataDifferenceCalcWithNormalizing(&(llDifNea[i]), &llNorNea, &(llMixNea[i]), &llEstNea, 
					&(linfo->DifCalcNea[i]), 1);
				rmsFar = lllDataDifferenceCalcWithNormalizing(&(llDifFar[i]), &llNorFar, &(llMixFar[i]), &llEstFar, 
					&(linfo->DifCalcFar[i]), 1);
				linfo->DifCalcTotal[i].A    = (linfo->DifCalcNea[i].A + linfo->DifCalcFar[i].A)/2.0;
				LOGPRINT6(fpt, "ITER", "DIF", "NormalizingFactor %s times: %d %d %f %f %f\n", 
								linfo->In[i], times, i, linfo->DifCalcTotal[i].A, linfo->DifCalcNea[i].A, linfo->DifCalcFar[i].A);
				DEBUGPRINT5("%f = (%f=test(%f)/%f)-ref(%f) : After\n", 
					llDifNea[i].LL[0].data[0].F,
					llNorNea.LL[0].data[0].F,
					llMixNea[i].LL[0].data[0].F,
					linfo->DifCalcNea[i].A,
					llEstNea.LL[0].data[0].F);
				llDataFree(&llNorNea);
				llDataFree(&llNorFar);
			} else {
				rmsNea = lllDataDifferenceCalc(&(llDifNea[i]), &(llMixNea[i]), &llEstNea, 1);
				rmsFar = lllDataDifferenceCalc(&(llDifFar[i]), &(llMixFar[i]), &llEstFar, 1);
				DEBUGPRINT3("%f = test(%f)-ref(%f)\n", 
					llDifNea[i].LL[0].data[0].F,
					llMixNea[i].LL[0].data[0].F,
					llEstNea.LL[0].data[0].F);
			}
			llDataFree(&llEstNea);
			llDataFree(&llEstFar);
			
			rmsAvg = sqrt((SQR(rmsNea) + SQR(rmsFar))/2.0); 
			rms    = sqrt(SQR(rms) + SQR(rmsAvg)); 
			LOGPRINT6(fpt,    "ITER", "DIF", "times: %04d iter: %04d iter2: %04d %04d %s rms: %15.6f", times, iter, iter2, i, In[i], rmsAvg);
		}
		linfo->currentRMS = rms = sqrt(SQR(rms)/filNumber);
		LOGPRINT4(fpt,    "ITER", "DIF", "times: %04d iter: %04d iter2: %04d total-rms: %15.6f", times, iter, iter2, rms);

		if(linfo->flagNormalization) {
			double A=0;
			for(i=0; i<filNumber; i++) {
				A += (linfo->DifCalcTotal[i].A); 
			}
			A = A/filNumber;
			LOGPRINT4(fpt,    "ITER", "DIF", "times: %04d iter: %04d iter2: %04d AverageOfA: %15.6f", times, iter, iter2, A);
			for(i=0; i<filNumber; i++) {
				lllDataMultiplyReal(&(llSepNea[i]), A);	
				lllDataMultiplyReal(&(llSepFar[i]), A);
			}
		}

		DEBUGPRINT("----- Evaluation of Q-Value(AxisSearch) and P-Value(FitAndAverage)");
		for(i=0, totalP = 0, totalQ = 0; i<filNumber; i++) {
			if(llDataPoleNormal == paraFit[i].Para.Pole) {
				totalP += SQR(paraFit[i].PPara.R);
			} else {
				totalP += SQR(paraFit[i].PParaInv.R);
			}
			totalQ += paraFit[i].QPara.R; 
		}
		linfo->currentP = totalP = sqrt(totalP/filNumber); 
		linfo->currentQ = totalQ = totalQ/filNumber; 
		LOGPRINT4(fpt,    "ITER", "DIF", "times: %04d iter: %04d iter2: %04d total-P: %15.6f", times, iter, iter2, totalP*DEGREE);
		LOGPRINT4(fpt,    "ITER", "DIF", "times: %04d iter: %04d iter2: %04d total-Q: %15.6f", times, iter, iter2, totalQ*DEGREE);

		DEBUGPRINT("----- Next Turn -----\n");
		linfo->oldRMS = oldrms;
		linfo->oldP   = oldTotalP;
		linfo->oldQ   = oldTotalQ;
		linfo->iter = iter; linfo->iter2 = iter2; linfo->iter3 = iter3; linfo->times = times;
		lllExtractNextStepParamterSet(fpt, paraFit, filNumber, linfo, 0);
		iter = linfo->iter; iter2 = linfo->iter2; iter3 = linfo->iter3; times = linfo->times;

		DEBUGPRINT("---- Estimation of difference : llSepDifNea and llSepDifFar ----\n"); 
		LOGPRINT3(fpt,    "ITER", "Diff", "times: %04d RMax: %15.6f RRMax: %15.6f", times, RMax, RRMax);
		for(i=0; i<filNumber; i++) {
			llDataInitWithReference(&(llSepDifNea[i]), &(llSepNea[i]));
			llDataInitWithReference(&(llSepDifFar[i]), &(llSepFar[i]));

			srcLLs[i].Nea = llDifNea[i]; 
			srcLLs[i].Far = llDifFar[i]; 
			dstLLs[i].Nea = llSepDifNea[i]; 
			dstLLs[i].Far = llSepDifFar[i]; 
		}

		switch(linfo->algorism) {
			case 0: {
				for(i=0; i<filNumber; i++) {
					lllExtractWithSeparation(&(dstLLs[i]), &(srcLLs[i]), &(linfo->leInfo[i]), 1); 
				}
				break;
			}
			case 1: {
			/*
				lllExtractWithSeparationUsingFittingParameter(dstLLs, srcLLs, paraFit, 
						filNumber, linfo->leInfo, 1);
			*/
				break;
			}
			default: {
				fprintf(stderr, "Not supported Alogrism");
				exit(EXIT_FAILURE);
				break;
			}
		}	
		for(i=0; i<filNumber; i++) {
			llSepDifNea[i] = dstLLs[i].Nea; 
			llSepDifFar[i] = dstLLs[i].Far;
		}


		for(i=0; i<filNumber; i++) {
			/* Dif-shift */ 
			lllDataLowPassFiltering      (&(llSepDifNea[i]), RMax,  lllDataLowPassFilteringModeSameMemorySize);
			lllDataLowPassFiltering      (&(llSepDifFar[i]), RMax,  lllDataLowPassFilteringModeSameMemorySize);
			lllDataRadialLowPassFiltering(&(llSepDifNea[i]), RRMax, lllDataLowPassFilteringModeSameMemorySize);
			lllDataRadialLowPassFiltering(&(llSepDifFar[i]), RRMax, lllDataLowPassFilteringModeSameMemorySize);
			lllDatarMaxLimit(&(llSepDifNea[i]), linfo->rMaxInfo, 0);
			lllDatarMaxLimit(&(llSepDifFar[i]), linfo->rMaxInfo, 0);
		}

		DEBUGPRINT("----- Estimation of New llSepASAvg -----");	
		if(0<linfo->MaxIteration3) {
			subStep = ((double)iter3)/((double)linfo->MaxIteration3);	
		} else {
			subStep = 0.0;
		}
		linfo->currentRMax  = RMax  = MIN(linfo->RMax,  linfo->RMaxFirst +(times - subStep)*linfo->RMaxStep);
		linfo->currentRRMax = RRMax = MIN(linfo->RRMax, linfo->RRMaxFirst+(times - subStep)*linfo->RRMaxStep);
		LOGPRINT3(fpt,    "ITER", "newllSep", "times: %04d RMax: %15.6f RRMax: %15.6f", times, RMax, RRMax);

		/*
			Estimation of new llSepNea and llSepFar 
			F(i) = F(i-1) + lambda*Dif(i-1); Dif(i-1) = Observe - F(i-1)
				If lambda = 1, Jacobi's method
				If lambda = 2, SIRT method
		*/
		for(i=0; i<filNumber; i++) {
			/* Multiply weight: lambda */
			lllDataMultiplyReal(&(llSepDifNea[i]), linfo->lambda);
			lllDataMultiplyReal(&(llSepDifFar[i]), linfo->lambda);

			/* Estimate */
			lllDataAdd(&(llSepNea[i]), &(llSepDifNea[i]));
			lllDataAdd(&(llSepFar[i]), &(llSepDifFar[i]));

			llDataFree(&(llSepDifNea[i]));
			llDataFree(&(llSepDifFar[i]));
		}

		DEBUGPRINT("----- Output a new model: llAvg -----\n"); 
		if(linfo->eachTime || linfo->flagForContinue) {
			sprintf(s, "%s.%03d", linfo->Avg, times);
			tmpfpt = fileOpen(s, "w");
			llDataFileWrite(tmpfpt, llAvg, &status);
			fclose(tmpfpt);
		}

		DEBUGPRINT("----- Output each filament : llSepNea and llSepFar -----\n"); 
		if(linfo->eachTime && linfo->flagForContinue && oldtimes < times) {
			for(i=0; i<filNumber; i++) {
				sprintf(s, "%s.Nea.%03d", In[i], times);
				tmpfpt = fileOpen(s, "w");
				llDataFileWrite(tmpfpt, &(llSepNea[i]), &status);
				fclose(tmpfpt);
				sprintf(s, "%s.Far.%03d", In[i], times);
				tmpfpt = fileOpen(s, "w");
				llDataFileWrite(tmpfpt, &(llSepFar[i]), &status);
				fclose(tmpfpt);
			}
		}
	}
#ifdef PVM
    if(linfo->flagpvmList || linfo->flagpvm) {
        lfitinfo.flagPVM = 0;
        lllDataFitServerEnd(lfitinfo.vPVM);
    }
#endif
	linfo->llSepASAvg    = llSepFitAvg;
	linfo->llSepDifASAvg = llSepDifASAvg;
	linfo->llSepNea      = llSepNea;
	linfo->llSepFar      = llSepFar;
	linfo->paraFit       = paraFit;
	if(linfo->flagPvalueMap || linfo->flagQvalueMap) {
			
	}
}

void
lllExtractInformationToBeContinuedRead(lllExtractWithLayerSeparationInfo* linfo, int mode) 
{
	char s[1024];
	DEBUGPRINT("----- Input Information For Continue -----\n"); 
	if(linfo->flagContinue) {
		fseek(linfo->fptContinue, 0L, SEEK_SET);
		/* First Line */
		stringGetFromFile(s, "", linfo->fptContinue, stdout, 3);  	
		linfo->RMaxFirst  = linfo->currentRMax  = MIN(stringGetNthRealData(s, 1, " ,\t"), linfo->RMax);
		linfo->RRMaxFirst = linfo->currentRRMax = MIN(stringGetNthRealData(s, 2, " ,\t"), linfo->RRMax);
	} else {
		linfo->currentRMax  = linfo->RMaxFirst;
		linfo->currentRRMax = linfo->RRMaxFirst; 
	}
}

void
lllExtractInformationToBeContinuedWrite(lllExtractWithLayerSeparationInfo* linfo, int mode) 
{
	char  s[1024];
	FILE* fpt;

	DEBUGPRINT("----- Output Information For Continue -----\n"); 
	if(linfo->flagForContinue) {
		sprintf(s, "%s.%03d", linfo->ForContinue, linfo->times);
		fpt = fileOpen(s, "w");
		fprintf(fpt, "%15.6f %15.6f # CurrentRMax CurrentRRMax\n",  linfo->currentRMax,  linfo->currentRRMax); 
		fclose(fpt);
	} 
}

void
lllExtractInitialization0(lllExtractWithLayerSeparationInfo* linfo, int filNumber, int mode)
{
	/* Initialization */
	linfo->leInfo = (lllExtractInfo*)memoryAllocate(sizeof(lllExtractInfo)      *filNumber, "in main");
	if(linfo->flagllInfoImportant) {
		linfo->leInfoImportant      	= (lllExtractInfo*)memoryAllocate(sizeof(lllExtractInfo)      *filNumber, "in main");
	}
	if(linfo->flagllInfoImportantForAxis) {
		linfo->leInfoImportantForAxis   = (lllExtractInfo*)memoryAllocate(sizeof(lllExtractInfo)      *filNumber, "in main");
	}

	linfo->rescaleInfo = (lllDataRescalingInfo*)memoryAllocate(sizeof(lllDataRescalingInfo)*filNumber, "in main");
}


/* 
*   Mixed Layer Line Extract 
*	The averaged model is made from these data.
*/
void
lllExtractMixedLayerLine(llData** llMixNea, llData** llMixFar, llDataFittedParam** paraFit, char** In, int filNumber, lllExtractWithLayerSeparationInfo* linfo, int mode)
{
	FILE* fpt;
	double RMax, RRMax;
	mrcImage mrcIn;
	llData   llTmpNea;
	llData   llTmpFar;
	llDataParamToFit range;
	int i;

	fpt   = linfo->fptLog;
	range = linfo->range;	

	LOGPRINT1(fpt,    "#", "INIT", "%s", "Extract MixedLayer");

	*paraFit   = (llDataFittedParam*)memoryAllocate(sizeof(llDataFittedParam)*filNumber, "in main");
	*llMixNea  = (llData*)           memoryAllocate(sizeof(llData)           *filNumber, "in main");
	*llMixFar  = (llData*)           memoryAllocate(sizeof(llData)           *filNumber, "in main");

	RMax  = linfo->RMax; 
	RRMax = linfo->RRMax; 
	LOGPRINT2(fpt,    "#", "INIT", "RMax: %15.6f RRMax: %15.6f", RMax, RRMax); 

	for(i=0; i<filNumber; i++) {
		/* FT Space Read */
		linfo->fptllInfo[i] = fileOpen(linfo->llInfo[i], "r");
		linfo->fptllInfoImportant[i] = fileOpen(linfo->llInfoImportant[i], "r");
		linfo->fptllInfoImportantForAxis[i] = fileOpen(linfo->llInfoImportantForAxis[i], "r");

		mrcFileRead(&mrcIn, In[i], "main routine", 0);
		
		lllDataSeparationInfoRead(&(linfo->leInfo[i]), &mrcIn, linfo->fptllInfo[i]);

		if(linfo->flagtruePitch) {
			linfo->leInfo[i].truePitch = linfo->truePitch;
		}
		if(linfo->flagrMax) {
			linfo->leInfo[i].rMax      = linfo->rMaxInfo;
		}
		if(linfo->flagRMax) {
			linfo->leInfo[i].RMax      = linfo->RMax;
		}
		linfo->leInfo[i].RMaxFirst = linfo->RMaxFirst;
		if(linfo->flagllInfoImportant) {
			lllDataSeparationInfoRead(&(linfo->leInfoImportant[i]), &mrcIn, linfo->fptllInfoImportant[i]);
		}
		if(linfo->flagllInfoImportantForAxis) {
			lllDataSeparationInfoRead(&(linfo->leInfoImportantForAxis[i]), &mrcIn, linfo->fptllInfoImportantForAxis[i]);
		}
		linfo->leInfo[i].flagMagnitudeLimit = linfo->magLimit; 

		/* Set Fitting Parameters */
		(*paraFit)[i].Para                     = range;
		(*paraFit)[i].Para.flagCTF             = linfo->flagCTF;
		if(linfo->flagCTF) {
			(*paraFit)[i].Para.ctfCompensationMode = linfo->ctfMode;
			(*paraFit)[i].Para.CTF                 = linfo->CTF[i];
			(*paraFit)[i].Para.ctfCutOff           = 0.1;
		}

		/* FT Space -> Mixed G(R, n, l) Space */
		lllExtract(&llTmpNea, &llTmpFar, &mrcIn, &(linfo->leInfo[i])); 

		/* delBR Rescaling */
		if(linfo->flagdelBR) {
			linfo->rescaleInfo[i].rScale = 1.0;
			linfo->rescaleInfo[i].delBR  = linfo->delBR;
			lllDataRescaling(&((*llMixNea)[i]), &llTmpNea, linfo->rescaleInfo[i], 0);
			lllDataRescaling(&((*llMixFar)[i]), &llTmpFar, linfo->rescaleInfo[i], 0);
			llDataFree(&llTmpNea);
			llDataFree(&llTmpFar);
		} else {
			(*llMixNea)[i] = llTmpNea;
			(*llMixFar)[i] = llTmpFar;
		}
		(*llMixNea)[i].Weight    = (*llMixFar)[i].Weight    = 1.0;

		mrcImageFree(&mrcIn, "in lllExtractWithLayerSeparation0");

		/* RMax         : Low pass filtering */
		lllDataLowPassFiltering(&((*llMixNea)[i]), RMax, lllDataLowPassFilteringModeSavedMemorySize);
		lllDataLowPassFiltering(&((*llMixFar)[i]), RMax, lllDataLowPassFilteringModeSavedMemorySize);
		/* Radial RMax  : Low pass filtering */
		lllDataRadialLowPassFiltering(&((*llMixNea)[i]), RRMax, lllDataLowPassFilteringModeSavedMemorySize);
		lllDataRadialLowPassFiltering(&((*llMixFar)[i]), RRMax, lllDataLowPassFilteringModeSavedMemorySize);

		/* File Close */
		fclose(linfo->fptllInfo[i]);
		fclose(linfo->fptllInfoImportant[i]);
		fclose(linfo->fptllInfoImportantForAxis[i]);
	}
}

void lllExtractFittingParameterPrint(FILE* fpt, char** In, llDataFittedParam* paraFit, int filNumber, lllExtractWithLayerSeparationInfo* linfo, int mode) 
{
	int i;

	for(i=0; i<filNumber; i++) {
		LOGPRINT9(fpt,    "ITER", "BestFit", "P: %15.6f phi: %15.6f z: %15.6f r: %15.6f pole: %1d times: %04d iter: %04d iter2: %04d : %s", 
								   paraFit[i].Para.R*DEGREE, 
								   paraFit[i].Para.phi.Value*DEGREE, 
								   paraFit[i].Para.z.Value,
								   paraFit[i].Para.r.Value,
								   paraFit[i].Para.Pole,
								   linfo->times,
								   linfo->iter, 
								   linfo->iter2,
								   In[i]);
		if(0==paraFit[i].Para.Pole) {
			LOGPRINT9(fpt,    "ITER", "AntiFit", "P: %15.6f phi: %15.6f z: %15.6f r: %15.6f pole: %1d times: %04d iter: %04d iter2: %04d : %s", 
								   paraFit[i].PParaInv.R*DEGREE,
								   paraFit[i].PParaInv.phi.Value*DEGREE,
								   paraFit[i].PParaInv.z.Value,
								   paraFit[i].PParaInv.r.Value,
								   paraFit[i].PParaInv.Pole,
								   linfo->times,
								   linfo->iter, 
								   linfo->iter2,
								   In[i]);
			LOGPRINT8(fpt,    "ITER", "P-Pprim", "P: %1d %15.6f %1d %15.6f times: %04d iter: %04d iter2: %04d : %s", 
								   llDataPoleNormal,		
								   paraFit[i].PPara.R   *DEGREE,
								   llDataPoleAnti,
								   paraFit[i].PParaInv.R*DEGREE,
								   linfo->times,
								   linfo->iter,
								   linfo->iter2,
								   In[i]);
		} else {
			LOGPRINT9(fpt,    "ITER", "AntiFit", "P: %15.6f phi: %15.6f z: %15.6f r: %15.6f pole: %1d times: %04d iter: %04d iter2: %04d : %s", 
								   paraFit[i].PPara.R*DEGREE, 
								   paraFit[i].PPara.phi.Value*DEGREE, 
								   paraFit[i].PPara.z.Value,
								   paraFit[i].PPara.r.Value,
								   paraFit[i].PPara.Pole,
								   linfo->times,
								   linfo->iter,
								   linfo->iter2,
								   In[i]);
			LOGPRINT8(fpt,    "ITER", "P-Pprim", "P: %1d %15.6f %1d %15.6f times: %04d iter: %04d iter2: %04d : %s", 
								   llDataPoleAnti,		
								   paraFit[i].PParaInv.R   *DEGREE,
								   llDataPoleNormal,
								   paraFit[i].PPara.R*DEGREE,
								   linfo->times,
								   linfo->iter,
								   linfo->iter2,
								   In[i]);
		}
	}	
}

void
lllExtractNextStepParamterSet(FILE* fpt, llDataFittedParam* paraFit, int filNumber, lllExtractWithLayerSeparationInfo* linfo, int mode)
{
	int i;
	int iter;
	int iter2;
	int iter3;
	int times;
	double totalP, oldTotalP;
	double totalQ, oldTotalQ;
	double rms, oldrms;
	llDataParamToFit range;

	iter  = linfo->iter;
	iter2 = linfo->iter2;
	iter3 = linfo->iter3;
	times = linfo->times;
	oldrms = linfo->oldRMS;
	rms    = linfo->currentRMS;
	oldTotalP = linfo->oldP;
	totalP	  = linfo->currentP;
	oldTotalQ = linfo->oldQ;
	totalQ	  = linfo->currentQ;
	range     = linfo->range;

	if(iter2<linfo->MaxIteration2 - 1) { /* */
		if(0==iter2) {                                    /* Start: New RRMax and RMax */
			iter3 = 0;
			iter2++;
		} else {
			if(oldrms < rms) { 	                           /* Next Iter3: Diverse */
				LOGPRINT6(fpt, "ITER", "Diverse",
						"total-rms: %15.6f oldTotal-rms: %15.6f iter: %04d iter2: %04d iter3: %04d times: %04d", 
						rms, oldrms, iter, iter2, iter3, times);
				if(iter3 <= linfo->MaxIteration3-1) {       
					LOGPRINT4(fpt, "ITER", "Diverse","RangeReset iter: %04d iter2: %04d iter3: %04d times: %04d\n", iter, iter2, iter3, times);
					for(i=0; i<filNumber; i++) {
						lllDataFittedParameterSet(&(paraFit[i].Para), &range);
					}
				} else { 
					LOGPRINT(fpt, "ITER","Diverse","Diversed Data: Check your parameters. But now I reduce iter2.");
					if(0<iter2) {
						iter2--;
					}
				}
				iter2 = iter2;
				iter3++;
			} else if(rms+linfo->nextTimes < oldrms) { /* Next Iter2: Converge */
				if(0<iter3) {  /* If in substep,  substep back  */ 
					iter3--;
				} else {       /* If in mainstep, next weight   */
					iter3 = 0;
					iter2++;
				}
			} else {                                   /* Next Times: Finish */ 
				iter3 = 0;
				iter2 = 0;
				times ++;
			}

			if(oldTotalP < totalP) {                                /* Diverse */
				LOGPRINT6(fpt, "ITER", "DiverseP",
					"total-P: %15.6f oldTotal-P: %15.6f iter: %04d iter2: %04d iter3: %04d times: %04d", 
					totalP, oldTotalP, iter, iter2, iter3, times);
				for(i=0; i<filNumber; i++) {
					lllDataFittedParameterSet0(&(paraFit[i].Para.phi), &(range.phi));
					lllDataFittedParameterSet0(&(paraFit[i].Para.z),   &(range.z));
					lllDataFittedParameterSet0(&(paraFit[i].Para.r),   &(range.r));
				}
			} else if(totalP+linfo->narrowSearch < oldTotalP) {      /* Converge */
				
			} else {                                                /* Converge: Final Step */ 
				if(iter3 == 0
				&& 1.0*RADIAN  < paraFit[0].Para.phi.Delta 
				&& 1.0         < paraFit[0].Para.z.Delta 
				&& 1e-4        < paraFit[0].Para.r.Delta ) {
					for(i=0; i<filNumber; i++) {
						lllDataNewFittedParameterSet0(&(paraFit[i].Para.phi));
						lllDataNewFittedParameterSet0(&(paraFit[i].Para.z));
						lllDataNewFittedParameterSet0(&(paraFit[i].Para.r));
					}
				}
			}

			if(oldTotalQ < totalQ) {                                /* Diverse */
				LOGPRINT6(fpt, "ITER", "DiverseQ",
					"total-Q: %15.6f oldTotal-Q: %15.6f iter: %04d iter2: %04d iter3: %04d times: %04d", 
					totalQ, oldTotalQ, iter, iter2, iter3, times);
				for(i=0; i<filNumber; i++) {
					lllDataFittedParameterSet0(&(paraFit[i].Para.x),     &(range.x));
					lllDataFittedParameterSet0(&(paraFit[i].Para.Omega), &(range.Omega));
				}
			} else if(totalQ+linfo->narrowSearch < oldTotalQ) {      /* Converge: */

			} else {
				if(iter3 == 0 
				&& 1.0        < paraFit[0].Para.x.Delta 
				&& 1.0*RADIAN < paraFit[0].Para.Omega.Delta ) {
					for(i=0; i<filNumber; i++) {                        /* Converge: Final Step */
						lllDataNewFittedParameterSet0(&(paraFit[i].Para.x));
						lllDataNewFittedParameterSet0(&(paraFit[i].Para.Omega));
					}
				}
			}
		}
	} else { /* Next Times */
		for(i=0; i<filNumber; i++) {
			lllDataFittedParameterSet(&(paraFit[i].Para), &range);
		}
		iter2 = 0;
		iter3 = 0;
		times++;
	}
	iter++;

	linfo->iter  = iter;
	linfo->iter2 = iter2;
	linfo->iter3 = iter3;
	linfo->times = times;
}
