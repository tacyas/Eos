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
		linfo->oldRMS = oldrms = rms; 	
		linfo->oldP = oldTotalP = totalP; linfo->oldQ = oldTotalQ = totalQ;

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
				lllDataAxisSearchModeSearchProcessPrint
			   |lllDataAxisSearchModeSearchProcessSameLLStructure);
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

			rmsNea = lllDataDifferenceCalc(&(llDifNea[i]), &(llMixNea[i]), &llEstNea, 1);
			rmsFar = lllDataDifferenceCalc(&(llDifFar[i]), &(llMixFar[i]), &llEstFar, 1);

			llDataFree(&llEstNea);
			llDataFree(&llEstFar);
			
			rmsAvg = sqrt((SQR(rmsNea) + SQR(rmsFar))/2.0); 
			rms    = sqrt(SQR(rms) + SQR(rmsAvg)); 
			LOGPRINT6(fpt,    "ITER", "DIF", "times: %04d iter: %04d iter2: %04d %04d %s rms: %15.6f", times, iter, iter2, i, In[i], rmsAvg);
		}
		linfo->currentRMS = rms = sqrt(SQR(rms)/filNumber);
		LOGPRINT4(fpt,    "ITER", "DIF", "times: %04d iter: %04d iter2: %04d total-rms: %15.6f", times, iter, iter2, rms);

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
}
