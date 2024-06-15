/*
	llDataAxisSearch(
		llData* nea,     LayerLineData Pointer to be treated
		llData* far,     LayerLineData Pointer to be treated
    	llDataFittedParam* p,
    	long               mode);

*/

#include <stdlib.h>
#include <math.h>
#include "genUtil.h"
#include "nr2.h"
#include "../inc/llData.h"
#include "lllDataFit.h"

#define VALUE_MASK (0x10)
#define PI M_PI
#define CUTOFF (0.5)
#define STEP   (20.0)
#define STEP2  (STEP/2.0)
#define L_LLDATA_AXIS_SEARCH_PARA_NUMBER (2)
#define xPara     (1)
#define OmegaPara (2)

extern void __lllDataAxisSearch21(llData* nea, llData* far, llDataParamToFit* P, llDataParamToFit* R, long mode);
extern float __lllDataAxisSearchQValue2(float* p);
extern void  __lllDataAxisSearchdQValue2(float* p, float* xi);

/* Static Data */
static llData Nea;
static llData Far;
static llDataParaTypeReal Resolution;

void
lllDataAxisSearch2(llData* nea, llData* far, llDataFittedParam* p, long mode)
{
	if(mode&QVALUE_MODE) {
        __lllDataAxisSearch21(nea, far, &(p->Para), &(p->QPara), mode&(QVALUE_MODE|VALUE_MASK));
    }
}

void 
__lllDataAxisSearch21(llData* nea, llData* far, llDataParamToFit* P, llDataParamToFit* R, long mode)
{
    float p[L_LLDATA_AXIS_SEARCH_PARA_NUMBER+1]; /* Parameter Starting Point: n+1 */
                                                 /* p[1] = deltax */
                                                 /* p[2] = deltaOmega */
    int   n;                                     /* Parameter Number */
    int   iter;                                  /* The Number of Performed Iterations */
    float fret;                                  /* The Minimum Value of Function  */
    float ftol;                                  /* Convergence Toleance */
    /* Parameter Set */
    p[xPara] = (P->x.Max     + P->x.Min    )/2.0; /* Starting Point of x*/
    p[OmegaPara] = (P->Omega.Max + P->Omega.Min)/2.0; /* Starting Point of Omega */
    n = L_LLDATA_AXIS_SEARCH_PARA_NUMBER;     /* Parameter Number */
    ftol = 1.0e-6;
    *R = *P;

    /* llData Set */
    Nea = *nea;
    Far = *far;
    Resolution = P->Resolution;

    /* Minimization */
    frprmn(p, n, ftol, &iter, &fret, __lllDataAxisSearchQValue2, __lllDataAxisSearchdQValue2);

    /* Fitted Parameter Set */
    R->R = fret;
    R->x.Value     = p[1];
    R->Omega.Value = p[2];
    if(!(R->x.Min<=R->x.Value&&R->x.Value<=R->x.Max)) {
        fprintf(stderr, "Minimum Point(x) is Out of Range. Range (%g - %g) <-> Value (%g)\n", R->x.Min, R->x.Max, R->x.Value);
    }
    if(!(R->Omega.Min<=R->Omega.Value&&R->Omega.Value<=R->Omega.Max)) {
        fprintf(stderr, "Minimum Point(Omega) is Out of Range. Range (%g - %g) <-> Value (%g)\n", R->Omega.Min, R->Omega.Max, R->Omega.Value);
    }
    fprintf(stdout, "x:%g O:%g iter:%d Res:%g\n", p[xPara], p[OmegaPara], iter, fret);
}

/*
Without Omega Angle
    Q     = Sigma[F*{(nea - 2*PI*x*R) - (far + 2*PI*x*R + n*PI)}]/Sigma[F]
    dQ/dx = Sigma(-4*PI*R*F)/Sigma[F]
    dQ/dO = 0
With Omega Angle
    Q = Sigma[F*{(nea - 2*PI*x*R - n*PI*Arcsin(Z*tan(Omega)/R)/(PI/2)/2) - (far + 2*PI*x*R + n*PI*Arcsin(Z*tan(Omega)/R)/(PI/2)/2 + n*PI)}]/Sigma[F]
    dQ/dx = Sigma(-4*PI*R*F)/Sigma[F]
    dQ/dO = Sigma[-2*F*n/sqrt(1-(Z*tan(Omega)/R)^2)*Z/R*(1-tan(Omega)^2)]/Sigma[F]
*/

void  
__lllDataAxisSearchdQValue2(float* p, float* xi)
{
    long lnea, lfar, R, sig;
    llDataParaTypeInteger nn;
    llDataParaTypeReal dtheta, Sum, neap, neap2, farp, farp2, F, Z, weight, RR, Res;

    Res = Sum = 0;
    xi[xPara]     = 0.0;
    xi[OmegaPara] = 0.0;
    for(lnea=0; lnea<Nea.llMax; lnea++) {
        for(lfar=0; lfar<Far.llMax; lfar++) {
            if(Nea.LL[lnea].nl==Far.LL[lfar].nl 
             &&Nea.LL[lnea].nn==Far.LL[lfar].nn 
             &&Nea.LL[lnea].Weight!=0.0) { /* Reference Layer Number = Layer Number */
		        Z  = Far.LL[lfar].Z = Nea.LL[lnea].Z = Nea.LL[lnea].nl/Nea.truePitch;
				nn = Nea.LL[lnea].nn;
                if(   (nn>=0&&Nea.LL[lnea].Side==NearSide)
                    ||(nn< 0&&Nea.LL[lnea].Side==FarSide)) {
                    sig = -1.0;
                } else {
                    sig = 1.0;
                }
		    	for(R=0; R<Nea.LL[lnea].nR; R++) {
                    RR   = Nea.LL[lnea].data[R].RR;
                    if(SQR(Resolution)>SQR(RR)+SQR(Z)) {

        		        F = (fabs(Nea.LL[lnea].data[R].F)+fabs(Far.LL[lfar].data[R].F))/2.0;
                        weight = Nea.LL[lnea].Weight;
                        xi[xPara]     += (-sig*4*PI*RR*F*weight);
                        xi[OmegaPara] += 0;
/*
                        xi[OmegaPara] += (-2*F*weight*nn/sqrt(1-SQR(Z*tan(p[OmegaPara])/RR))*Z/RR*(1-SQR(tan(p[OmegaPara]))));
*/
                        Sum += F*weight;
                    }
    			}
	    	}	
        }
    }
    xi[xPara]     /= Sum;
    xi[OmegaPara] /= Sum;
}


float
__lllDataAxisSearchQValue2(float* p)
{
    long lnea, lfar, R, sig;
    llDataParaTypeInteger nn;
    llDataParaTypeReal dtheta, Sum, neap, neap2, farp, farp2, F, Z, weight, RR, Res;

    Res = Sum = 0;
    for(lnea=0; lnea<Nea.llMax; lnea++) {
        for(lfar=0; lfar<Far.llMax; lfar++) {
            if(Nea.LL[lnea].nl==Far.LL[lfar].nl 
             &&Nea.LL[lnea].nn==Far.LL[lfar].nn 
             &&Nea.LL[lnea].Weight!=0.0) { /* Reference Layer Number = Layer Number */
		        Z  = Far.LL[lfar].Z = Nea.LL[lnea].Z = Nea.LL[lnea].nl/Nea.truePitch;
				nn = Nea.LL[lnea].nn;
                if(   (nn>=0&&Nea.LL[lnea].Side==NearSide)
                    ||(nn< 0&&Nea.LL[lnea].Side==FarSide)) {
                    sig = -1.0;
                } else {
                    sig = 1.0;
                }
		    	for(R=0; R<Nea.LL[lnea].nR; R++) {
                    RR   = Nea.LL[lnea].data[R].RR;
                    if(SQR(Resolution)>SQR(RR)+SQR(Z)) {
        		        F = (fabs(Nea.LL[lnea].data[R].F)+fabs(Far.LL[lfar].data[R].F))/2.0;
                        /* Phase Transform */
                        neap = Nea.LL[lnea].data[R].PHI;
                        farp = Far.LL[lfar].data[R].PHI;
                        neap2 = NORMAL_PHASE(neap - sig*2*PI*p[xPara]*RR        );
                        farp2 = NORMAL_PHASE(farp + sig*2*PI*p[xPara]*RR + nn*PI);
/*
                        neap2 = NORMAL_PHASE(neap - 2*PI*p[xPara]*RR - nn*PI*asin(Z*tan(p[OmegaPara])/RR)/(PI/2.0)/2.0        );
                        farp2 = NORMAL_PHASE(farp + 2*PI*p[xPara]*RR + nn*PI*asin(Z*tan(p[OmegaPara])/RR)/(PI/2.0)/2.0 + nn*PI);
*/
                        /* Phase Residual Calculation */
                		dtheta = fmod(fabs(neap2-farp2), 2*PI);
    					dtheta = MIN(2*PI-dtheta, dtheta);
                        weight = Nea.LL[lnea].Weight;
                        Sum += F*weight;
    	            	Res += F*weight*dtheta;
                    }
    			}
	    	}	
        }
    }
    return Res/Sum;
}


