/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% lllDataMultiCTFCompensation ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : lllDataMultiCTFCompensation 
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%lllDataMultiCTFCompensation ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#undef DEBUG
#include "genUtil.h"
#include "Memory.h"
#include "llData.h"
#include "lllDataFitAndAverage.h"
#include "lllDataCTFCompensation.h"

void
lllDataMultiCTFCompensationModePrint(FILE* fpt)
{
	fprintf(fpt, "----- Mode -----\n");
	fprintf(fpt, "    0: |CTFi|/Sigma(SQR(CTFi))\n");
	fprintf(fpt, "    1:  CTFi /Sigma(SQR(CTFi))\n");
}

void
lllDataMultiCTFCompensation(llData* llAve, llData* llOut, 
							llData* llIn, llData llRef, 
							llDataFittedParam* paraFit, 
							lllDataFitAndAverageInfo info, 
							lllDataMultiCTFCompensationMode mode)
{
    long ll, iR, i;
    double Z, R, CTF, Weight;
    double Sum, F, Re, Im, phi;
	int* flag;

	DEBUGPRINT("----- lllDataMultiCTFCompensation -----\n");
    lllDataClear(llAve);

	flag = (int*)memoryAllocate(sizeof(int)*info.nFile, "in lllDataMultiCTF");
	for(i=0; i<info.nFile; i++) {
		lllDataPhaseShiftInter(&(llOut[i]), &(llIn[i]), &(paraFit[i]));	
		flag[i] = 0;

		if(info.flagAveragingWithoutAntiPole) {
			if(llDataPoleAnti==paraFit[i].Para.Pole) {
				flag[i]++;
			}
		}
		if(info.flagAveragingBelowThreshold) {
			if(info.threshold < paraFit[i].Para.R) {
				flag[i]++;
			}
		}
	}

	CTF = 1.0;
    DEBUGPRINT1("in lllDataMultiCTFCompensation: llMax %d\n", llAve->llMax);
    DEBUGPRINT("Start---\n");
    for(ll=0; ll<llAve->llMax; ll++) {
        Z = llAve->LL[ll].Z;
        for(iR = 0; iR<llAve->LL[ll].nR; iR++) {
            Sum = 0.0;
            Re  = 0.0;
            Im  = 0.0;
            for(i=0; i<info.nFile; i++) {
                F   = llOut[i].LL[ll].data[iR].F;
                phi = llOut[i].LL[ll].data[iR].PHI;
#ifdef DEBUG
					if(ll==0 && iR<=10) {
						DEBUGPRINT4("mode: %d : flagCTF: %d, ctfMode: %d: llCTF: %d\n",
							mode, info.flagCTF, info.ctfMode, paraFit[i].Para.flagllCTF);
					}
#endif
				if(0==flag[i] && 0 < F) {
					switch(mode) {
						case 0: {
							CTF = 1.0; 
							break;
						}
						case 1:  {
							if(info.flagCTF) {
								if(paraFit[i].Para.flagllCTF) {
                					switch(info.ctfMode) {
					                    case 0: {
					                        CTF = paraFit[i].Para.llCTF.LL[ll].data[iR].F;
#ifdef DEBUG
										   	if(ll==0 && iR<=10) {
												DEBUGPRINT3("Already Phase: R: %f PHI: %f: CTF: %f\n", \
													llOut[i].LL[ll].data[iR].R, 
													phi, 
													CTF);	
											}
#endif
											break;
										}
					                    case 1: {
					                        CTF = paraFit[i].Para.llCTF.LL[ll].data[iR].Re;
#ifdef DEBUG
										   	if(ll==0 && iR<=10) {
												DEBUGPRINT3("PhaseAlso R: %f PHI: %f: CTF: %f\n", \
													llOut[i].LL[ll].data[iR].R, 
													phi, 
													CTF);	
											}
#endif
					                        break;
					                    }
   						                default: {
                       						ERRORPRINT1("Not supported mode: %d\n", info.ctfMode);
                        					exit(EXIT_FAILURE);
                        					break;
                    					}
									}
								} else {
                					switch(info.ctfMode) {
					                    case 0: {
					                        CTF = ctfFunction(&(info.CTF[i]),
					                                         llOut[i].LL[ll].data[iR].R, 0);
					                        CTF = fabs(CTF);
											break;
										}
					                    case 1: {
					                        CTF = ctfFunction(&(info.CTF[i]),
					                                         llOut[i].LL[ll].data[iR].R, 0);
					                        break;
					                    }
   						                default: {
                       						ERRORPRINT1("Not supported mode: %d\n", info.ctfMode);
                        					exit(EXIT_FAILURE);
                        					break;
                    					}
									}
								}
							} else {
								CTF = 1.0;
							}
							break;
						}
						default: {
                       		ERRORPRINT1("Not supported mode: %d\n", mode);
							break;
						}
					}
					if(info.flagWeight) {
                		Weight =info.weight[i];
					} else {
						Weight = 1.0;
					}
                	Re += Weight*CTF*F*cos(phi);
                	Im += Weight*CTF*F*sin(phi);
                	Sum+= (Weight*SQR(CTF) + SQR(info.noise));
				}
            }
            if(Sum==0.0) {
                Re = 0.0;
                Im = 0.0;
            } else {
                Re /= Sum;
                Im /= Sum;
            }
			llAve->LL[ll].data[iR].Re  = Re;
            llAve->LL[ll].data[iR].Im  = Im;
        }
    }
	llDataFandPHISet(llAve);
}
