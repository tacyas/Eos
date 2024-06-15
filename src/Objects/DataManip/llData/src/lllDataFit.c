/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% lllDataFit ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : lllDataFit
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%lllDataFit ver%I%; Date:%D% %Z%";
#include <math.h>
#include <stdlib.h>

#undef DEBUG
#undef DEBUG2
#undef DEBUG3
#include "genUtil.h"

#include "../inc/llData.h"
#include "lllDataFit.h"
#include "File.h"
#include "Memory.h"
#include "mrcImage.h"

/*
	llDataFit(
		llData* llref,   LayerLineData Pointer to be treated
		llData* llp,     LayerLineData Pointer to be treated
		llDataFittedParam* p);  
*/

#define STEP      (6.0)
#define STEP2     (STEP/2.0)
#define COUNT_MAX (4)
#define END_VALUE (1e-4)

extern inline void __lllDataFit0(llData* llref, llData* llp, llDataParamToFit* p, long mode);
extern inline void __lllDataFitPValue0(llData* llref, llData* llp, llDataParamToFit* p, long mode);
extern inline void __lllDataFitQValue0(llData* llref, llData* llp, llDataParamToFit* p, long mode);
extern inline void __lllDataFitRValue0(llData* llref, llData* llp, llDataParamToFit* p, long mode);
extern inline void __lllDataFitPValueMergedLL0(llData* llref, llData* llp, llDataParamToFit* p, long mode);
extern inline void __lllDataFitQValueMergedLL0(llData* llref, llData* llp, llDataParamToFit* p, long mode);
extern inline void __lllDataFitRValueMergedLL0(llData* llref, llData* llp, llDataParamToFit* p, long mode);
extern inline void __lllDataFit1(llData* llref, llData* llp, llDataParamToFit* cond, llDataParamToFit* res, char* filename, long mode);
extern inline int  __lllDataFitCheck0(llDataParamToFit* fit, llDataParamToFit* p, long mode);

void
lllDataFit(llData* llref, llData* llp, llDataFittedParam* p, long mode)
{
    /* Search */
	fprintf(stdout, "----- lllDataFit Start ----\n");
	if(!llref->RValueSet) {
		llDataRValueSet(llref, 0);
	}
	if(!llp->RValueSet) {
		llDataRValueSet(llp, 0);
	}

	if(!llref->ZValueSet) {
		llDataZValueSet(llref, 0);
	}
	if(!llp->ZValueSet) {
		llDataZValueSet(llp, 0);
	}

	if(!p->Para.flagLLTable) {
		DEBUGPRINT("llDataTableBetweenTwollDataCreate in lllDataFit\n");
		p->Para.flagLLTable = llref->llMax;
		p->Para.llTable = llDataTableBetweenTwollDataCreate(llref, llp, 0);
	}

	if(p->Para.flagCTF) {
		if(!p->Para.flagllCTF) {
			llDataInitWithReference(&(p->Para.llCTF), llref);
			lllDataFitllCTFSet(&(p->Para.llCTF), p->Para.CTF, 0);
			p->Para.flagllCTF = 1; 
		}
	}

	llDataFandPHISet(llp);
    if(0xf&mode&PVALUE_MODE) {
		fprintf(stdout, "----- Normal Pole ----------------------------------\n");
        p->Para.Pole = llDataPoleNormal;
        __lllDataFit1(llref, llp, &(p->Para), &(p->PPara), (char*)p->fitFileName, mode&(PVALUE_MODE|lllDataFitFitProcessPrint));

		fprintf(stdout, "----- Anti Pole   ----------------------------------\n");
        p->Para.Pole = llDataPoleAnti;
        __lllDataFit1(llref, llp, &(p->Para), &(p->PParaInv), (char*)p->fitFileNameAnti, mode&(PVALUE_MODE|lllDataFitFitProcessPrint));

		if(p->PPara.R <= p->PParaInv.R) {
            p->Para.phi.Value = p->PPara.phi.Value;
            p->Para.r.Value   = p->PPara.r.Value;
            p->Para.z.Value   = p->PPara.z.Value;
            p->Para.Pole      = llDataPoleNormal;
            p->Para.R         = p->PPara.R;
        } else {
            p->Para.phi.Value = p->PParaInv.phi.Value;
            p->Para.r.Value   = p->PParaInv.r.Value;
            p->Para.z.Value   = p->PParaInv.z.Value;
            p->Para.Pole      = llDataPoleAnti;
            p->Para.R         = p->PParaInv.R;
        }
        fprintf(stdout, "PValue : %15.6f %15.6f\n", p->PPara.R*DEGREE, p->PParaInv.R*DEGREE);
        fprintf(stdout, "BestFit: %15.6f %s %15.6f %15.6f %15.6f %2d\n",
                p->Para.R*DEGREE,
				"Param:",
                p->Para.phi.Value*DEGREE,
                p->Para.z.Value,
                p->Para.r.Value,
                p->Para.Pole);
    }

    if(0xf&mode&QVALUE_MODE) {
		DEBUGPRINT("Normal Pole\n");
        p->Para.Pole = llDataPoleNormal;
        __lllDataFit1(llref, llp, &(p->Para), &(p->QPara), (char*)p->fitFileName, mode&(QVALUE_MODE|lllDataFitFitProcessPrint));
		DEBUGPRINT("Anti Pole\n");
        p->Para.Pole = llDataPoleAnti;
        __lllDataFit1(llref, llp, &(p->Para), &(p->QParaInv), (char*)p->fitFileNameAnti, mode&(PVALUE_MODE|lllDataFitFitProcessPrint));

		if(p->QPara.R <= p->QParaInv.R) {
            p->Para.phi.Value = p->QPara.phi.Value;
            p->Para.r.Value = p->QPara.r.Value;
            p->Para.z.Value = p->QPara.z.Value;
            p->Para.Pole = llDataPoleNormal;
            p->Para.R = p->QPara.R;
        } else {
            p->Para.phi.Value = p->QParaInv.phi.Value;
            p->Para.r.Value = p->QParaInv.r.Value;
            p->Para.z.Value = p->QParaInv.z.Value;
            p->Para.Pole = llDataPoleAnti;
            p->Para.R = p->QParaInv.R;
        }
        fprintf(stdout, "QValue: %f %f\n", p->QPara.R*DEGREE, p->QParaInv.R*DEGREE);
        fprintf(stdout, "BestFit: %15.6f %16s %15.6f %15.6f %15.6f %2d \n",
                p->Para.R*DEGREE,
				"Param:",
                p->Para.phi.Value*DEGREE,
                p->Para.z.Value,
                p->Para.r.Value,
                p->Para.Pole);
    }

    if(0xf&mode&RVALUE_MODE) {
		DEBUGPRINT("Normal Pole\n");
        p->Para.Pole = llDataPoleNormal;
        __lllDataFit1(llref, llp, &(p->Para), &(p->RPara), (char*)p->fitFileName, mode&(RVALUE_MODE|lllDataFitFitProcessPrint));
		DEBUGPRINT("Anti Pole\n");
        p->Para.Pole = llDataPoleAnti;
        __lllDataFit1(llref, llp, &(p->Para), &(p->RParaInv), (char*)p->fitFileNameAnti, mode&(PVALUE_MODE|lllDataFitFitProcessPrint));

		if(p->RPara.R <= p->RParaInv.R) {
            p->Para.phi.Value = p->RPara.phi.Value;
            p->Para.r.Value = p->RPara.r.Value;
            p->Para.z.Value = p->RPara.z.Value;
            p->Para.Pole = llDataPoleNormal;
            p->Para.R = p->RPara.R;
        } else {
            p->Para.phi.Value = p->RParaInv.phi.Value;
            p->Para.r.Value = p->RParaInv.r.Value;
            p->Para.z.Value = p->RParaInv.z.Value;
            p->Para.Pole = llDataPoleAnti;
            p->Para.R = p->RParaInv.R;
        }
        fprintf(stdout, "RValue: %f %f\n", p->RPara.R, p->RParaInv.R);
        fprintf(stdout, "BestFit: %15.6f %15s %15.6f %15.6f %15.6f %2d\n",
                p->Para.R*DEGREE,
				"Param:",
                p->Para.phi.Value*DEGREE,
                p->Para.z.Value,
                p->Para.r.Value,
                p->Para.Pole);
    }
}

void
lllDataFitWithFile(llData* llref, llData* llp, llDataFittedParam* p, char* filename, long mode)
{
	char filename2[1024];

	sprintf(filename2, "%s.anti", filename);

	p->flagFitFile     = 1;	
	p->fitFileName     = filename;
	p->fitFileNameAnti = filename2;
	
	lllDataFit(llref, llp, p, mode);
}

/*
	P: Initial parameter
	R: Result
*/
void
__lllDataFit1(llData* llref, llData* llp, llDataParamToFit* P, llDataParamToFit* R, char* filename, long mode)
{
  	llDataParaTypeReal iphi, iz, ir;
	llDataParamToFit tmp;
	llDataParamToFit currentR;
	llDataParamToFit otmp;
    llDataParaTypeInteger count;
   	mrcImage mrc;

	DEBUGPRINT("___lllDataAxisFit1 Start\n");
    /* Initialization */
	currentR = *R;
    tmp = *R = *P; /* Order is important */ 

	/* First Trial */
    tmp.r.Value   = P->r.Max;
    tmp.phi.Value = P->phi.Max;
    tmp.z.Value   = P->z.Max;
	__lllDataFit0(llref, llp, &tmp, mode);
	*R = tmp;

	/* Parameter Set */
	if(NULL!=filename) {
		DEBUGPRINT1("fittedParam file name: %s\n", filename);
		mrc.HeaderN.x = fabs((tmp.phi.Max - tmp.phi.Min)/tmp.phi.Delta) + 1.0;
		mrc.HeaderN.y = fabs((tmp.z.Max   - tmp.z.Min)  /tmp.z.Delta)   + 1.0;
		mrc.HeaderN.z = fabs((tmp.r.Max   - tmp.r.Min)  /tmp.r.Delta)   + 1.0;
		mrc.HeaderMode = mrcFloatImage;
		mrc.HeaderLength.x = tmp.phi.Delta*DEGREE;
		mrc.HeaderLength.y = tmp.z.Delta;
		mrc.HeaderLength.z = tmp.r.Delta;
		mrc.HeaderStartN.x = tmp.phi.Min*DEGREE;
		mrc.HeaderStartN.y = tmp.z.Min;
		mrc.HeaderStartN.z = tmp.r.Min;
		mrcInit(&mrc, NULL);
	}

    count = 0;
    while(count<COUNT_MAX) {
		otmp = tmp;

		DEBUGPRINT1("Iteration : %ld\n", count); 
	    for(tmp.r.Value=tmp.r.Min, ir=0; tmp.r.Value<=tmp.r.Max; tmp.r.Value+=tmp.r.Delta, ir++) {
		    for(tmp.phi.Value=tmp.phi.Min, iphi=0; tmp.phi.Value<=tmp.phi.Max; tmp.phi.Value+=tmp.phi.Delta, iphi++) {
   				for(tmp.z.Value=tmp.z.Min, iz=0; tmp.z.Value<=tmp.z.Max; tmp.z.Value+=tmp.z.Delta, iz++) {
   	    			__lllDataFit0(llref, llp, &tmp, mode);

					if(NULL != filename 
					&&    0 == count) {
						mrcPixelDataSet(&mrc, iphi, iz, ir, (double)tmp.R, mrcPixelRePart);
					}

					__lllDataFitCheck0(R, &tmp, mode);
	           	}
    	    }
	    }
        if(R->R <= otmp.R) { /* otmp is old R */
			if(otmp.R - R->R < END_VALUE) {
				break;
			} 
        } else {
            fprintf(stderr, "Something wrong in fitting : R %f old %f\n", R->R, otmp.R);
			break;
        }

		tmp.phi.Value = R->phi.Value;
		tmp.z.Value   = R->z.Value;
		tmp.r.Value   = R->r.Value;
		lllDataNewFittedParameterSet0(&(tmp.phi));
		lllDataNewFittedParameterSet0(&(tmp.z));
		lllDataNewFittedParameterSet0(&(tmp.r));
		count++;
    }
	
	R->flagCTF     =  currentR.flagCTF;
	R->flagllCTF   =  currentR.flagllCTF;
	R->flagLLTable =  currentR.flagCTF;
	if(NULL!=filename) {
		DEBUGPRINT1 ("Write: %s\n", filename);
		mrcFileWrite(&mrc, filename, "in lllDataFit", 0); 
	}
}

/*

*/
inline int
__lllDataFitCheck0(llDataParamToFit* minimum, llDataParamToFit* current, long mode)
{
    if(current->R<=minimum->R) {
		*minimum = *current;
    	if(mode&lllDataFitFitProcessPrint) {
       		fprintf(stdout, "%15.6f %15.6f %15.6f %15.6f %02d\n", 
						(float)current->R*DEGREE, 
						(float)current->phi.Value*DEGREE, 
						(float)current->z.Value, 
						(float)current->r.Value,
						       current->Pole);
    	}
        return 1;
    } else {
        return 0;
    }
}    

/*
	lllDataFit0(
		llData* llref,	# Reference llData;
		llData* llp,    # llData to be fit
		llDataFittedParam* p # Fitting Parameter
		);
	
	Calculation of Residue in *p
*/
inline void
__lllDataFit0(llData* llref, llData* llp, llDataParamToFit* p, long mode)
{
	if(mode&lllDataFitFitProcessMergedLL) {
    	if(mode&PVALUE_MODE) {
       		__lllDataFitPValueMergedLL0(llref, llp, p, mode);
    	}
    	if(mode&QVALUE_MODE) {
        	__lllDataFitQValueMergedLL0(llref, llp, p, mode);
    	}
    	if(mode&RVALUE_MODE) {
        	__lllDataFitRValueMergedLL0(llref, llp, p, mode);
    	}
	} else {
    	if(mode&PVALUE_MODE) {
       		__lllDataFitPValue0(llref, llp, p, mode);
    	}
    	if(mode&QVALUE_MODE) {
        	__lllDataFitQValue0(llref, llp, p, mode);
    	}
    	if(mode&RVALUE_MODE) {
        	__lllDataFitRValue0(llref, llp, p, mode);
    	}
	}
}

void
__lllDataFitPValue0(llData* llref, llData* llp, llDataParamToFit* Para, long mode)
{
    long lp, lref, R;
    llDataParaTypeReal dtheta, Sum, refp, pp0, pp1, pp2, F, Z, weight;
	llDataParaTypeInteger nn, pole;
	llDataParaTypeInteger RMax;
	llDataParaTypeReal  ctfWeight;

	ctfWeight = 1.0;
    Para->R = Sum = 0;
#ifdef DEBUG3
	DEBUGPRINT1("CTFFLAG: %d\n", Para->flagCTF);
#endif
    for(lref=0; lref<llref->llMax; lref++) {
		lp = Para->llTable[lref];
		if(lp < llp->llMax) {
            if(llref->LL[lref].nl==llref->LL[lp].nl 
			&& llref->LL[lref].nn==llref->LL[lp].nn 
			&& llref->LL[lref].Weight != 0.0) { /* Reference Layer Number = Layer Number */
		        Z  = llp->LL[lref].Z;
				nn = llref->LL[lref].nn;
                if(llDataPoleNormal == llp->Pole) {
                    if(llDataPoleNormal == Para->Pole) {
                        pole = llDataPoleNormal;
                    } else {
                        pole = llDataPoleAnti;
                    }
                } else {
                    if(llDataPoleAnti == Para->Pole) {
                        pole = llDataPoleAnti;
                    } else {
                        pole = llDataPoleNormal;
                    }
                }
				RMax = MIN(llref->LL[lref].nR, llp->LL[lp].nR);
		    	for(R=0; R<RMax; R++) {
                    weight = llref->LL[lref].Weight;
    		        F      = fabs((llref->LL[lref].data[R].F+llp->LL[lp].data[R].F)/2.0*weight);
					if(0 < F
					 &&0 < llref->LL[lref].data[R].F) {
						pp0  =   llp->LL[lp  ].data[R].PHI;
						refp = llref->LL[lref].data[R].PHI;
						if(Para->flagCTF) {
							if(Para->flagllCTF) {
								switch(Para->ctfCompensationMode) {
									case 0: 
									case 1: {
										ctfWeight = Para->llCTF.LL[lref].data[R].F;
										break;
									}
									default: {
										fprintf(stderr, "Not supported ctfCompensationMode in lllDataFit\n");
										break;
									}
								}
								switch(Para->ctfCompensationMode) {
									case 0: {
										pp0 = llp->LL[lp].data[R].PHI;
										break;
									}
									case 1: {
#ifdef DEBUG000
										if(lref==0 && R==0) {
											DEBUGPRINT2("Ref: %f Test: %f at (0, 0)\n",
												llref->LL[lref].data[R].PHI,
												llp->LL[lp].data[R].PHI);
										}
#endif
										if(Para->llCTF.LL[lref].data[R].Re<0) {
											pp0 = llp->LL[lp].data[R].PHI + M_PI;
										} else {
											pp0 = llp->LL[lp].data[R].PHI;
										}
										break;
									}
								}
							} else {
								switch(Para->ctfCompensationMode) {
									case 0: 
									case 1: {
										ctfWeight = fabs(ctfFunction(&(Para->CTF), 
											llp->LL[lref].data[R].R, 0));  
										break;
									}
									default: {
										fprintf(stderr, "Not supported ctfCompensationMode in lllDataFit\n");
										break;
									}
								}
								switch(Para->ctfCompensationMode) {
									case 0: {
										pp0 = llp->LL[lp].data[R].PHI;
										break;
									}
									case 1: {
										if(ctfFunction(&(Para->CTF), 
											llp->LL[lref].data[R].R, 0)<0) {
											pp0 = llp->LL[lp].data[R].PHI + M_PI;
										} else {
											pp0 = llp->LL[lp].data[R].PHI;
										}
										break;
									}
								}
							}
						} else {
							pp0  =   llp->LL[lp  ].data[R].PHI;
							ctfWeight = 1.0;
							Para->ctfCutOff = 0.0;
						}

					    if(Para->ctfCutOff < ctfWeight) {
							/* Phase Transform */ 

				            refp = nearSidePhaseGet(refp, nn, llref->LL[lref].Side, llref->Pole);
							pp1  = nearSidePhaseGet(pp0,  nn,   llp->LL[lp  ].Side,     pole);
            				pp2  = NORMAL_PHASE(pp1 - nn*Para->phi.Value + 2*M_PI*Z*Para->z.Value);
                    		/* Phase Residual Calculation */
            				dtheta = NORMAL_PHASE(refp - pp2);
							dtheta = fabs(MIN(2*M_PI-dtheta, dtheta));
                    		Sum     += F*ctfWeight;
			            	Para->R += F*ctfWeight*dtheta*dtheta;
						}
					}
    			}
	    	}	
        }
    }
#ifdef DEBUG2
	DEBUGPRINT4("R: %f Sum:%f phi: %f z: %f\n", Para->R, Sum, Para->phi.Value, Para->z.Value);
#endif
    if(Sum>0) {
		if(0<Para->R) {
    		Para->R = sqrt(Para->R/Sum);
		} else {
			Para->R = 0;
		}
    } else {
        Para->R = M_PI;
    }
}

void
__lllDataFitQValue0(llData* llref, llData* llp, llDataParamToFit* Para, long mode)
{
    long lp, lref, R;
    llDataParaTypeReal dtheta, Sum, refp, pp, pp2, F, Z, weight;
	llDataParaTypeInteger nn, pole, RMax;
	llDataParaTypeReal  RR, ctfWeight;

	
	ctfWeight = 1.0;
    Para->R =  Sum = 0;
    for(lref=0; lref<llref->llMax; lref++) {
		lp = Para->llTable[lref];
		if(lp < llp->llMax) {
            if(  llref->LL[lref].nl==llref->LL[lp].nl 
			  && llref->LL[lref].nn==llref->LL[lp].nn 
			  && llref->LL[lref].Weight!=0.0) { /* Reference Layer Number = Layer Number */
		        Z  = llp->LL[lref].Z;
				nn = llref->LL[lref].nn;
				DEBUGPRINT2("nn: %d, Z: %f\n", nn, Z);
                if(llDataPoleNormal == llp->Pole) {
                    if(llDataPoleNormal == Para->Pole) {
                        pole = llDataPoleNormal;
                    } else {
                        pole = llDataPoleAnti;
                    }
                } else {
                    if(llDataPoleAnti == Para->Pole) {
                        pole = llDataPoleAnti;
                    } else {
                        pole = llDataPoleNormal;
                    }
                }
				RMax = MIN(llref->LL[lref].nR, llp->LL[lp].nR);
		    	for(R=0; R<RMax; R++) {
                    weight = llref->LL[lref].Weight;
    		        F      = fabs((llref->LL[lref].data[R].F+llp->LL[lp].data[R].F)/2.0*weight);
					if(0.0 < F 
					 &&0.0 < llref->LL[lref].data[R].F) {
						if(Para->flagCTF) {
							RR = sqrt(SQR(Z) + SQR(llref->LL[lref].data[R].RR)); 
							switch(Para->ctfCompensationMode) {
								case 0: 
								case 1: {
									ctfWeight = fabs(ctfFunction(&(Para->CTF),
													llref->LL[lref].data[R].R, 0)); 
									break;
								}
								default: {
									fprintf(stderr, "Not supported ctfCompensationMode in lllDataFit\n");
									break;
								}
							}
						} else {
							ctfWeight = 1.0;
							Para->ctfCutOff = 0.0;
						}
					 	if(Para->ctfCutOff < ctfWeight) {
							/* Phase Transform */ 
				            refp = nearSidePhaseGet(llref->LL[lref].data[R].PHI, nn, llref->LL[lref].Side, llref->Pole);
							pp   = nearSidePhaseGet(  llp->LL[lp].data[R].PHI,   nn, llp->LL[lp].Side,     pole);
            				pp2  = pp - nn*Para->phi.Value + 2*M_PI*Z*Para->z.Value;
                    		/* Phase Residual Calculation */
            				dtheta = fabs(fmod(refp - pp2, 2*M_PI));
							dtheta = fabs(MIN(2*M_PI-dtheta, dtheta));
                    		Sum     += F*ctfWeight;
				    	    Para->R += F*ctfWeight*dtheta;
						}
					}
    			}
	    	}	
        }
    }
    if(Sum>0) {
    	Para->R = sqrt(Para->R/Sum);
    } else {
        Para->R = M_PI/2.0;
    }
}

void
__lllDataFitRValue0(llData* llref, llData* llp, llDataParamToFit* Para, long mode)
{
    long lp, lref, R;
    llDataParaTypeReal dtheta, Sum, refp, pp, pp2, F, Z, weight;
	llDataParaTypeInteger nn, pole;
	llDataParaTypeInteger RMax;
	double Residue;
	llDataParaTypeReal  ctfWeight;

	ctfWeight = 1.0;
    Para->R = Sum = 0;
    for(lref=0; lref<llref->llMax; lref++) {
		lp = Para->llTable[lref];
		if(lp < llp->llMax) {
            if(llref->LL[lref].nl==llref->LL[lp].nl 
			 &&llref->LL[lref].nn==llref->LL[lp].nn 
			 &&llref->LL[lref].Weight!=0.0) { /* Reference Layer Number = Layer Number */
		        Z  = llp->LL[lref].Z;
				nn = llref->LL[lref].nn;
                if(llDataPoleNormal == llp->Pole) {
                    if(llDataPoleNormal == Para->Pole) {
                        pole = llDataPoleNormal;
                    } else {
                        pole = llDataPoleAnti;
                    }
                } else {
                    if(llDataPoleAnti==Para->Pole){
                        pole = llDataPoleAnti;
                    } else {
                        pole = llDataPoleNormal;
                    }
                }
				RMax = MIN(llref->LL[lref].nR, llp->LL[lp].nR);
		    	for(R=0; R<RMax; R++) {
					/* Phase Transform */ 
                    weight = llref->LL[lref].Weight;
    		        F      = fabs((llref->LL[lref].data[R].F+llp->LL[lp].data[R].F)/2.0*weight);
					if(0.0 < F 
					 &&0.0 < llref->LL[lref].data[R].F) {
						if(Para->flagCTF) {
							switch(Para->ctfCompensationMode) {
								case 0: 
								case 1: {
									ctfWeight = fabs(ctfFunction(&(Para->CTF), 
										llref->LL[lref].data[R].R, 0));  
									break;
								}
								default: {
									fprintf(stderr, "Not supported ctfCompensationMode in lllDataFit\n");
									break;
								}
							}
						} else {
							ctfWeight = 1.0;
							Para->ctfCutOff = 0.0;
						}
					 	if(Para->ctfCutOff < ctfWeight) {
				        	refp = nearSidePhaseGet(llref->LL[lref].data[R].PHI, nn, llref->LL[lref].Side, llref->Pole);
							pp   = nearSidePhaseGet(  llp->LL[lp].data[R].PHI,   nn, llp->LL[lp].Side,     pole);
            				pp2  = pp - nn*Para->phi.Value + 2*M_PI*Z*Para->z.Value;
                    		/* Phase Residual Calculation */
            				dtheta = fabs(fmod(refp - pp2, 2*M_PI));
							dtheta = fabs(MIN(2*M_PI-dtheta, dtheta));

                    		Sum     += F*ctfWeight*weight;
                    		Para->R +=   ctfWeight*weight
								*sqrt(SQR(llref->LL[lref].data[R].F*cos(refp) - llp->LL[lp].data[R].F*cos(pp2))
                                     +SQR(llref->LL[lref].data[R].F*sin(refp) - llp->LL[lp].data[R].F*sin(pp2)));
						}
					}
    			}
	    	}	
        }
    }
    if(Sum>0) {
    	Para->R = Para->R/Sum/2.0;
    } else {
        Para->R = 1.0;
    }
}

