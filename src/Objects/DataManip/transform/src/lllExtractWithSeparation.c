/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% lllExtractWithSeparation ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : lllExtractWithSeparation 
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%lllExtractWithSeparation ver%I%; Date:%D% %Z%";
#include <stdlib.h>
#undef DEBUG
#include "genUtil.h"
#include "nr2.h"
#include "lllExtract.h"
#include "lllDataMergeDifferentN.h"

extern void lllExtractInitWithSeparation(
	llDataBoth* dst, llDataBoth* src, lllExtractInfo* info, int mode);

void
lllExtractWithSeparationUsingFittingParameter(llData* dst, llDataBoth* src,
	llDataFittedParam* param, int numFile, lllExtractInfo* info, int mode)
{
#ifdef DEBUG000
	long ll, l, ltot;
	long i, j;
	long iR, jR;
	long llMax;
    float** ANea;
	float** bNea;
    float** AFar;
	float** bFar;
	double phi, z, C;
	long n1, n2, nl;
	long l1, l2;

	DEBUGPRINT("lllExtractWithSeparation\n");
	switch(mode) {
		case 0: {
			for(i=0; i<numFile; i++) {
				llDataInitWithReference2(&(dst[i]), &(src[0].Nea), AverageSide);
			}
			break;
		}
		case 1: {
			break;
		}
		default: {
			fprintf(stderr, "Not supported mode: %d\n", mode);
			exit(EXIT_FAILURE);
			break;
		}
	}
	
	llMax = 0;
	for(ll=0; ll<info->llMax; ll++) {
		llMax += info->nn[ll];
	}

	ltot = 0;
	for(ll = 0; ll < info->llMax; ll++) {
		/* Near Side */
		nl   = info->nn[ll];
		ANea = matrix(1, 2*nl, 1, 2*nl);
		bNea = matrix(1, 2*nl, 1, src[0].Nea.LL[ll].nR);
		for(l1=0; l1<nl; l1++) { 
			for(l2=0; l2<nl; l2++) { 
				ANea[l2   +1][l1   +1] = 0.0;
				ANea[l2+nl+1][l1   +1] = 0.0;
				ANea[l2   +1][l1+nl+1] = 0.0;
				ANea[l2+nl+1][l1+nl+1] = 0.0;
				for(i=0; i<numFile; i++) {
					phi = param[i].Para.phi.Value;
					n1 = info->ns[ll][l1];
					n2 = info->ns[ll][l2];
					ANea[l2   +1][l1   +1] +=  cos((n1 - n2)*phi);
					ANea[l2+nl+1][l1   +1] += -sin((n1 - n2)*phi); 
					ANea[l2   +1][l1+nl+1] +=  sin((n1 - n2)*phi);  
					ANea[l2+nl+1][l1+nl+1] +=  cos((n1 - n2)*phi);
				}
			}
		}
		for(l2=0; l2<nl; l2++) {
			n2 = info->ns[ll][l2];
			for(iR=0; iR<src[0].Nea.LL[ll].nR; iR++) {
				bNea[l2   +1][iR+1] = 0.0;  
				bNea[l2+nl+1][iR+1] = 0.0;
				for(i=0; i<numFile; i++) {
					z   = param[i].Para.z.Value;
					phi = param[i].Para.phi.Value;
					C   = info->truePitch;
					l   = info->l[ll];
					bNea[l2   +1][iR+1] += (src[i].Nea.LL[ll].data[iR].Re*cos(-n2*phi + 2*M_PI*z/C*l)
										   -src[i].Nea.LL[ll].data[iR].Im*sin(-n2*phi + 2*M_PI*z/C*l));  
					bNea[l2+nl+1][iR+1] += (src[i].Nea.LL[ll].data[iR].Re*sin(-n2*phi + 2*M_PI*z/C*l)
										   +src[i].Nea.LL[ll].data[iR].Im*cos(-n2*phi + 2*M_PI*z/C*l)); 
				}
			}
		}

		/* Far Side */
		nl   = info->nn[ll];
		AFar = matrix(1, 2*nl, 1, 2*nl);
		bFar = matrix(1, 2*nl, 1, src[0].Far.LL[ll].nR);
		for(l1=0; l1<nl; l1++) { 
			for(l2=0; l2<nl; l2++) { 
				AFar[l2   +1][l1   +1] = 0.0;
				AFar[l2+nl+1][l1   +1] = 0.0;
				AFar[l2   +1][l1+nl+1] = 0.0;
				AFar[l2+nl+1][l1+nl+1] = 0.0;
				for(i=0; i<numFile; i++) {
					phi = param[i].Para.phi.Value;
					n1 = info->ns[ll][l1];
					n2 = info->ns[ll][l2];
					AFar[l2   +1][l1   +1] +=  cos((n1 - n2)*phi);
					AFar[l2+nl+1][l1   +1] += -sin((n1 - n2)*phi); 
					AFar[l2   +1][l1+nl+1] +=  sin((n1 - n2)*phi);  
					AFar[l2+nl+1][l1+nl+1] +=  cos((n1 - n2)*phi);
				}
			}
		}
		for(l2=0; l2<nl; l2++) {
			n2 = info->ns[ll][l2];
			for(iR=0; iR<src[0].Far.LL[ll].nR; iR++) {
				bFar[l2   +1][iR+1] = 0.0;  
				bFar[l2+nl+1][iR+1] = 0.0;
				for(i=0; i<numFile; i++) {
					z   = param[i].Para.z.Value;
					phi = param[i].Para.phi.Value;
					C   = info->truePitch;
					l   = info->l[ll];
					bFar[l2   +1][iR+1] += (src[i].Far.LL[ll].data[iR].Re*cos(-n2*phi + 2*M_PI*z/C*l)
										   -src[i].Far.LL[ll].data[iR].Im*sin(-n2*phi + 2*M_PI*z/C*l));  
					bFar[l2+nl+1][iR+1] += (src[i].Far.LL[ll].data[iR].Re*sin(-n2*phi + 2*M_PI*z/C*l)
										   +src[i].Far.LL[ll].data[iR].Im*cos(-n2*phi + 2*M_PI*z/C*l)); 
				}
			}
		}


		gaussj(ANea, nl, bNea, src[0].Nea.LL[ll].nR);
		gaussj(AFar, nl, bFar, src[0].Far.LL[ll].nR);

		/* Near Side of DST */
		for(i=0; i<numFile; i++) {
			for(l2=0; l2<nl; l2++) {
				for(iR=0; iR<dst->Nea.LL[ltot+l2].nR; iR++) {
					jR = dst->Nea.LL[ltot+l2].iRMin + iR;
					if(jR<src[0].Nea.LL[ll].nR) {
						if((0 <= info->ns[ll][0] && 0 <= info->ns[ll][l2])
						 ||(info->ns[ll][0] < 0  && info->ns[ll][l2])) {
							dst[i].Nea.LL[ltot+l2].data[iR].Re = bNea[l2   +1][jR+1];
							dst[i].Nea.LL[ltot+l2].data[iR].Im = bNea[l2+nl+1][jR+1];
						} else {
							dst[i].Nea.LL[ltot+l2].data[iR].Re = bFar[l2   +1][jR+1];
							dst[i].Nea.LL[ltot+l2].data[iR].Im = bFar[l2+nl+1][jR+1];
						}
					} else {
						fprintf(stderr, "Something wrong: %d %d %d %d %d in lllExtractWithSeparationUsingFittingParameter\n", 
							ltot, l2, iR, jR, src[0].Nea.LL[ll].nR);
						dst[i].Nea.LL[ltot+l2].data[iR].Re = 0.0;
						dst[i].Nea.LL[ltot+l2].data[iR].Im = 0.0;
					}
				}
			}
		}
		
		free_matrix(ANea, 1, 2*nl, 1, 2*nl);
		free_matrix(bNea, 1, 2*nl, 1, src[0].Nea.LL[l].nR);
		free_matrix(AFar, 1, 2*nl, 1, 2*nl);
		free_matrix(bFar, 1, 2*nl, 1, src[0].Far.LL[l].nR);

		ltot += nl;
	}

	for(i=0; i<numFile; i++) {
		llDataFandPHISet(&(dst[i].Nea));		
		llDataFandPHISet(&(dst[i].Far));		
/*
		lllDataPhaseShiftInverse(&(dst[i].Nea), &(paraFit[i]));
		lllDataPhaseShiftInverse(&(dst[i].Nea), &(paraFit[i]));
*/
	}
#endif 
}


void
lllExtractInitWithSeparation(llDataBoth* dst, llDataBoth* src, lllExtractInfo* info, int mode)
{
	long l, l1, ltot;
	long llMax;

	*dst = *src;
	llMax = 0;
	for(l=0; l<info->llMax; l++) {
		llMax += info->nn[l];
	}

	dst->Nea.llMax = llMax;
	dst->Far.llMax = llMax;
	llDataHeaderInit(&(dst->Nea));
	llDataHeaderInit(&(dst->Far));

	ltot = 0;
	for(l=0; l<src->Nea.llMax; l++) {
		for(l1=0; l1<info->nn[l]; l1++) {
			dst->Nea.LL[ltot]      = src->Nea.LL[l];
			dst->Far.LL[ltot]      = src->Far.LL[l];

			dst->Nea.LL[ltot].nn   = info->ns[l][l1];
			dst->Far.LL[ltot].nn   = info->ns[l][l1];
			ltot++;
		}
	}

	llDataDataInit(&(dst->Nea));
	llDataDataInit(&(dst->Far));
}

void
lllExtractWeightSetFollowingllExtractInfo(llData* dst, lllExtractInfo* info, float weight, int mode)
{
	long l, l1, i;

	for(l=0; l<dst->llMax; l++) {
		dst->LL[l].Weight = 1.0;
		for(l1=0; l1<info->llMax; l1++) {
			if(dst->LL[l].nl == info->l[l1]) {
				for(i=0; i<info->nn[l1]; i++) {
					if(dst->LL[l].nn==info->ns[l1][i]) {
						DEBUGPRINT2("(n,l) = (%d, %d)\n", 
							dst->LL[l].nn, dst->LL[l].nl);
						dst->LL[l].Weight = weight;	
					}
				}
			}
		}
	}
}

void
lllExtractWithSeparation(llDataBoth* dst, llDataBoth* src, lllExtractInfo* info, int mode)
{
	long l, l1;
	long R;

	DEBUGPRINT("lllExtractWithSeparation\n");
	switch(mode) {
		case 0: {
			lllExtractInitWithSeparation(dst, src, info, 0);
			break;
		}
		case 1: {
			break;
		}
		default: {
			fprintf(stderr, "Not supported mode: %d\n", mode);
			exit(EXIT_FAILURE);
			break;
		}
	}

	for(l=0; l<dst->Nea.llMax; l++) {
		for(l1=0; l1<src->Nea.llMax; l1++) {
			if((dst->Nea.LL[l].nl==src->Nea.LL[l1].nl) 
			 &&(dst->Far.LL[l].nl==src->Far.LL[l1].nl)) {

				if(src->Nea.LL[l1].iRMin!=src->Far.LL[l1].iRMin
				 ||src->Nea.LL[l1].iRMax!=src->Far.LL[l1].iRMax
				 ||dst->Nea.LL[l].iRMin!=dst->Far.LL[l].iRMin
				 ||dst->Nea.LL[l].iRMax!=dst->Far.LL[l].iRMax) {
					fprintf(stderr, "NL   : Nea:%d->%d Far:%d->%d in lllExtractWithSeparation\n", 
						dst->Nea.LL[l].nl, src->Nea.LL[l1].nl,
						dst->Far.LL[l].nl, src->Far.LL[l1].nl);
					fprintf(stderr, "iRMin: Nea:%d->%d Far:%d->%d in lllExtractWithSeparation\n", 
						dst->Nea.LL[l].iRMin, src->Nea.LL[l1].iRMin,
						dst->Far.LL[l].iRMin, src->Far.LL[l1].iRMin);
					fprintf(stderr, "iRMax: Nea:%d->%d Far:%d->%d in lllExtractWithSeparation\n", 
						dst->Nea.LL[l].iRMax, src->Nea.LL[l1].iRMax,
						dst->Far.LL[l].iRMax, src->Far.LL[l1].iRMax);
					fprintf(stderr, "Different size between nea and far\n");
					return;
				}	
				
				/* Near Side in dst */
				if((0<=src->Nea.LL[l1].nn   && 0<=dst->Nea.LL[l].nn)
				 ||(   src->Nea.LL[l1].nn<0 &&    dst->Nea.LL[l].nn<0)) {
					for(R=0; R<dst->Nea.LL[l].nR; R++) {
						dst->Nea.LL[l].data[R] = src->Nea.LL[l1].data[R + dst->Nea.LL[l].iRMin];
					}
				} else {
					DEBUGPRINT4("(N,L): src(%d,%d)->dst(%d,%d)\n",
						src->Nea.LL[l1].nn,
						src->Nea.LL[l1].nl,
						dst->Nea.LL[l].nn,
						dst->Nea.LL[l].nl);
					for(R=0; R<dst->Nea.LL[l].nR; R++) {
						dst->Nea.LL[l].data[R] = src->Far.LL[l1].data[R + dst->Nea.LL[l].iRMin];
					}
					DEBUGPRINT3("dstNea: %f src: Far:%f, Nea:%f\n", 
													dst->Nea.LL[l].data[1].Re, 
													src->Far.LL[l1].data[dst->Nea.LL[l].iRMin+1].Re,
													src->Nea.LL[l1].data[dst->Nea.LL[l].iRMin+1].Re);
				}

				/* Far Side in dst */
				if((0<=src->Far.LL[l1].nn   && 0<=dst->Far.LL[l].nn)
				 ||(   src->Far.LL[l1].nn<0 &&    dst->Far.LL[l].nn<0)) {
					for(R=0; R<dst->Far.LL[l].nR; R++) {
						dst->Far.LL[l].data[R] = src->Far.LL[l1].data[R + dst->Far.LL[l].iRMin];
					}
				} else {
					DEBUGPRINT4("(N,L): src(%d,%d)->dst(%d,%d)\n",
						src->Nea.LL[l1].nn,
						src->Nea.LL[l1].nl,
						dst->Nea.LL[l].nn,
						dst->Nea.LL[l].nl);
					for(R=0; R<dst->Far.LL[l].nR; R++) {
						dst->Far.LL[l].data[R] = src->Nea.LL[l1].data[R + dst->Far.LL[l].iRMin];
					}
					DEBUGPRINT3("dstFar: %f, src: Nea:%f Far:%f\n", 
													dst->Far.LL[l].data[1].Re, 
													src->Nea.LL[l1].data[dst->Nea.LL[l].iRMin+1].Re,
													src->Far.LL[l1].data[dst->Nea.LL[l].iRMin+1].Re);
				}
			}
		}
	}
	DEBUGPRINT2("llMax: %d -> %d in lllExtractWithSeparation\n", src->Nea.llMax, dst->Nea.llMax);
	lllDatarMaxLimit(&(dst->Nea), info->rMax, lllDatarMaxLimitModeNoMemorySave);
	lllDatarMaxLimit(&(dst->Far), info->rMax, lllDatarMaxLimitModeNoMemorySave);

	if(info->flagMagnitudeLimit) {
		llDataBoth tmpl;
		float weight;

		llDataInitWithReference(&(tmpl.Nea), &(src->Nea));
		llDataInitWithReference(&(tmpl.Far), &(src->Far));

		lllDataMergeDifferentN(&tmpl, dst, 1); 

		for(l=0; l<dst->Nea.llMax; l++) {
			for(l1=0; l1<src->Nea.llMax; l1++) {
				if((dst->Nea.LL[l].nl==src->Nea.LL[l1].nl) 
				 &&(dst->Far.LL[l].nl==src->Far.LL[l1].nl)) {
					if((0<=src->Nea.LL[l1].nn   && 0<=dst->Nea.LL[l].nn)
					 ||(   src->Nea.LL[l1].nn<0 &&    dst->Nea.LL[l].nn<0)) {
						for(R=0; R<dst->Nea.LL[l].nR; R++) {
							if(0 == tmpl.Nea.LL[l1].data[R + dst->Nea.LL[l].iRMin].F) {
								weight = 1.0;
							} else {
								weight = ( src->Nea.LL[l1].data[R + dst->Nea.LL[l].iRMin].F
									      /tmpl.Nea.LL[l1].data[R + dst->Nea.LL[l].iRMin].F);
								if(1.0<weight) {
									weight = 1.0;
								}
							}
							dst->Nea.LL[l].data[R].F = dst->Nea.LL[l].data[R].F*weight;
						}
					} else {
						for(R=0; R<dst->Nea.LL[l].nR; R++) {
							if(0 == tmpl.Far.LL[l1].data[R + dst->Nea.LL[l].iRMin].F) {
								weight = 1.0;
							} else {
								weight = ( src->Far.LL[l1].data[R + dst->Nea.LL[l].iRMin].F
									      /tmpl.Far.LL[l1].data[R + dst->Nea.LL[l].iRMin].F);
								if(1.0<weight) {
									weight = 1.0;
								}
							}
							dst->Nea.LL[l].data[R].F = dst->Nea.LL[l].data[R].F*weight;
						}
					}

					/* Far Side in dst */
					if((0<=src->Far.LL[l1].nn   && 0<=dst->Far.LL[l].nn)
					 ||(   src->Far.LL[l1].nn<0 &&    dst->Far.LL[l].nn<0)) {
						for(R=0; R<dst->Far.LL[l].nR; R++) {
							if(0 == tmpl.Far.LL[l1].data[R + dst->Far.LL[l].iRMin].F) {
								weight = 1.0;
							} else {
								weight = ( src->Far.LL[l1].data[R + dst->Far.LL[l].iRMin].F
									      /tmpl.Far.LL[l1].data[R + dst->Far.LL[l].iRMin].F);
								if(1.0<weight) {
									weight = 1.0;
								}
							}
							dst->Far.LL[l].data[R].F = dst->Far.LL[l].data[R].F*weight;
						}
					} else {
						for(R=0; R<dst->Far.LL[l].nR; R++) {
							if(0 == tmpl.Nea.LL[l1].data[R + dst->Far.LL[l].iRMin].F) {
								weight = 1.0;
							} else {
								weight = ( src->Nea.LL[l1].data[R + dst->Far.LL[l].iRMin].F
									      /tmpl.Nea.LL[l1].data[R + dst->Far.LL[l].iRMin].F);
								if(1.0<weight) {
									weight = 1.0;
								}
							}
							dst->Far.LL[l].data[R].F = dst->Far.LL[l].data[R].F*weight;
						}
					}
				}
			}
		}
			
		llDataReAndImSet(&(dst->Nea));
		llDataReAndImSet(&(dst->Far));

		llDataFree(&(tmpl.Nea));
		llDataFree(&(tmpl.Far));
	}
}

void
lllExtractWithWeightedSeparation(llDataBoth* dst, llDataBoth* src, llData* weight, lllExtractInfo* info, int mode)
{
	long l;
	long R;

	lllExtractWithSeparation(dst, src, info, mode);
	for(l=0; l<dst->Nea.llMax; l++) {
		for(R=0; R<dst->Nea.nRMax; R++) {
			dst->Nea.LL[l].data[R]     =                         dst->Nea.LL[l].data[R];
			dst->Nea.LL[l].data[R].F   = weight->LL[l].data[R].F*dst->Nea.LL[l].data[R].F;
			dst->Nea.LL[l].data[R].Re  = weight->LL[l].data[R].F*dst->Nea.LL[l].data[R].Re;
			dst->Nea.LL[l].data[R].Im  = weight->LL[l].data[R].F*dst->Nea.LL[l].data[R].Im;

			dst->Far.LL[l].data[R]     =                         dst->Far.LL[l].data[R];
			dst->Far.LL[l].data[R].F   = weight->LL[l].data[R].F*dst->Far.LL[l].data[R].F;
			dst->Far.LL[l].data[R].Re  = weight->LL[l].data[R].F*dst->Far.LL[l].data[R].Re;
			dst->Far.LL[l].data[R].Im  = weight->LL[l].data[R].F*dst->Far.LL[l].data[R].Im;
		}
	}
	DEBUGPRINT2("llMax: %d -> %d in lllExtractWithSeparation\n", src->Nea.llMax, dst->Nea.llMax);
}

