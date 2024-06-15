#include <math.h>
#include <stdlib.h>
#include "../inc/llData.h"
#include "lllDataFit.h"
#include "genUtil.h"
#include "nr2.h"

#define VALUE_MASK (0x10)
#define PARAM_NUM        (2)
#define phiPara (1)
#define zPara   (2)

/* Static Data */
static llData Ref;
static llData Tes;
static llDataParaTypeReal Resolution;

extern void __lllDataFit20(llData* ref, llData* tes, llDataParamToFit* P, llDataParamToFit* R, long mode);
extern void __lllDataFitdPValue2(float* p, float* xi);
extern float __lllDataFitPValue2(float* p);
extern void __lllDataFitdQValue2(float* p, float* xi);
extern float __lllDataFitQValue2(float* p);
extern void __lllDataFitdRValue2(float* p, float* xi);
extern float __lllDataFitRValue2(float* p);

/*
    lllDataFit2(
        llData* llref,   LayerLineData Pointer to be treated
        llData* llp,     LayerLineData Pointer to be treated
        llDataFittedParam* p);  
*/
void
lllDataFit2(llData* llref, llData* llp, llDataFittedParam* p, long mode)
{
    /* Search */
    if(mode&PVALUE_MODE) {
        __lllDataFit20(llref, llp, &(p->Para), &(p->PPara), mode&(PVALUE_MODE|VALUE_MASK));
    }

    if(mode&QVALUE_MODE) {
        __lllDataFit20(llref, llp, &(p->Para), &(p->QPara), mode&(QVALUE_MODE|VALUE_MASK));
    }

    if(mode&RVALUE_MODE) {
        __lllDataFit20(llref, llp, &(p->Para), &(p->RPara), mode&(RVALUE_MODE|VALUE_MASK));
    }
}

void
__lllDataFit20(llData* ref, llData* tes, llDataParamToFit* P, llDataParamToFit* R, long mode)
{
    llDataParamToFit tmp;
    float p[PARAM_NUM+1]; /* Starting Point: Attention Index is from 1.  */
    float ftol, fret;
    int n, iter;                     /* Parameter Number */

    /* Initialization */
    p[phiPara] = (P->phi.Max + P->phi.Min)/2.0;
    p[zPara]   = (P->z.Max   + P->z.Min  )/2.0;
    n    = PARAM_NUM;
    ftol = 1.0e-6;
    *R = *P;
    
    Ref = *ref;
    Tes = *tes;
    
    if(mode&PVALUE_MODE) {
        frprmn(p, n, ftol, &iter, &fret, __lllDataFitPValue2, __lllDataFitdPValue2);
    }
    if(mode&QVALUE_MODE) {
        frprmn(p, n, ftol, &iter, &fret, __lllDataFitQValue2, __lllDataFitdQValue2);      
    }
    if(mode&RVALUE_MODE) {
        frprmn(p, n, ftol, &iter, &fret, __lllDataFitRValue2, __lllDataFitdRValue2);      
    }
    R->R = fret;
    R->phi.Value = p[phiPara];
    R->z.Value   = p[zPara];    
    if(!(R->phi.Min<=R->phi.Value&&R->phi.Value<=R->phi.Max)) {
        fprintf(stderr, "Minimum Point(phi) is out of range\n");
    }
    if(!(R->z.Min<=R->z.Value&&R->z.Value<=R->z.Max)) {
        fprintf(stderr, "Minimum Point(z) is out of range\n");
    }
    fprintf(stdout, "phi:%g z:%g iter:%d Res:%g\n", p[phiPara], p[zPara], iter, fret);
}

/* 
   P       = sqrt[Sigma{Fi*SQR(refpi - (tespi - nn*phi + 2*PI*Zi*z))}/Sigma{Fi}]
   dP/dphi = Sigma{2*Fi*nn       *(refpi - (tespi - nn*phi + 2*PI*Zi*z))}/{2*P*Sigma(Fi)}
   dP/dz   = Sigma{2*Fi*(-2*PI*Z)*(refpi - (tespi - nn*phi + 2*PI*Zi*z))}/{2*P*Sigma(Fi)}

   Q       = Sigma{Fi*(refpi - (tespi - nn*phi + 2*PI*Zi*z))}/Sigma{Fi}
   dQ/dphi = Sigma(Fi*nn       )/Sigma{Fi}
   dQ/dz   = Sigma(Fi*(-2*PI*Z))/Sigma{Fi}

   R       = Sigma[|Fi*exp(i*refpi) - Fi*exp{i*(tespi - nn*phi + 2*PI*Zi*z)}|]/Sigma{Fi}
   dR/dphi = Sigma[2*(rr*pF*sin(pp)*nn-ri*pF*cos(pp)*nn)+2*()/{2*()}]/Sigma{Fi}
*/


void
__lllDataFitdPValue2(float* p, float* xi)
{
    long lp, lr, R;
    llDataParaTypeReal dtheta, Res, Sum, refp, pp, pp2, F, Z, weight;
    llDataParaTypeReal x;
    llDataParaTypeInteger nn;

    Res = Sum   = 0.0;
    xi[phiPara] = 0.0;
    xi[zPara]   = 0.0;
    for(lr=0; lr<Ref.llMax; lr++) {
        for(lp=0; lp<Tes.llMax; lp++) {
            if(  Ref.LL[lr].nl==Tes.LL[lp].nl 
           &&Ref.LL[lr].nn==Tes.LL[lp].nn 
           &&Ref.LL[lr].Weight!=0.0) { /* Reference Layer Number = Layer Number */
                Ref.LL[lr].Z = Ref.LL[lr].nl/Ref.truePitch;
                Tes.LL[lp].Z = Tes.LL[lp].nl/Tes.truePitch;
                Z  = Ref.LL[lr].Z;
                nn = Ref.LL[lr].nn;
                for(R=0; R<Ref.LL[lr].nR; R++) {
                    /* Phase Transform */ 
                    refp = nearSidePhaseGet(Ref.LL[lr].data[R].PHI, nn, Ref.LL[lr].Side, Ref.Pole);
                    pp   = nearSidePhaseGet(Tes.LL[lp].data[R].PHI, nn, Tes.LL[lp].Side, Tes.Pole);
                    pp2  = pp - nn*p[phiPara] + 2*PI*Z*p[zPara];
                    /* Phase Residual Calculation */
                    dtheta = fmod(refp - pp2, 2*PI);
                    dtheta = fabs(MIN(2*PI-dtheta, dtheta));
                    weight = Ref.LL[lr].Weight;
                    F      = fabs((Ref.LL[lr].data[R].F+Tes.LL[lp].data[R].F)/2.0*weight);
                    Sum += F;
                    x = F*dtheta;
                    xi[phiPara] += 2*x*nn;
                    xi[zPara]   += 2*x*(-2*PI*Z);
                    Res         += x*dtheta;
                }
            }    
        }
    }
    Res = sqrt(Res/Sum);
    xi[phiPara] = xi[phiPara]/(2*Res*Sum);
    xi[zPara]   = xi[zPara]/(2*Res*Sum);
      
}

float
__lllDataFitPValue2(float* p)
{
    long lp, lr, R;
    llDataParaTypeReal dtheta, Res, Sum, refp, pp, pp2, F, Z, weight;
    llDataParaTypeInteger nn;

    Res = Sum = 0;
    for(lr=0; lr<Ref.llMax; lr++) {
        for(lp=0; lp<Tes.llMax; lp++) {
            if(  Ref.LL[lr].nl==Tes.LL[lp].nl 
               &&Ref.LL[lr].nn==Tes.LL[lp].nn 
               &&Ref.LL[lr].Weight!=0.0) { /* Reference Layer Number = Layer Number */
                Ref.LL[lr].Z = Ref.LL[lr].nl/Ref.truePitch;
                Tes.LL[lp].Z = Tes.LL[lp].nl/Tes.truePitch;
                Z  = Ref.LL[lr].Z;
                nn = Ref.LL[lr].nn;
                for(R=0; R<Ref.LL[lr].nR; R++) {
                    /* Phase Transform */ 
                    refp = nearSidePhaseGet(Ref.LL[lr].data[R].PHI, nn, Ref.LL[lr].Side, Ref.Pole);
                    pp   = nearSidePhaseGet(Tes.LL[lp].data[R].PHI, nn, Tes.LL[lp].Side, Tes.Pole);
                    pp2  = pp - nn*p[phiPara] + 2*PI*Z*p[zPara];
                    /* Phase Residual Calculation */
                    dtheta = fmod(refp - pp2, 2*PI);
                    dtheta = fabs(MIN(2*PI-dtheta, dtheta));
                    weight = Ref.LL[lr].Weight;
                    F      = fabs((Ref.LL[lr].data[R].F+Tes.LL[lp].data[R].F)/2.0*weight);
                    Sum += F;
                    Res += F*dtheta*dtheta;
                }
            }    
        }
    }
    Res = sqrt(Res/Sum);
    return Res;
}


void
__lllDataFitdQValue2(float* p, float* xi)
{
    long lp, lr, R;
    llDataParaTypeReal dtheta, Res, Sum, refp, pp, pp2, F, Z, weight;
    llDataParaTypeInteger nn;

    Res = Sum   = 0.0;
    xi[phiPara] = 0.0;
    xi[zPara]   = 0.0;
    for(lr=0; lr<Ref.llMax; lr++) {
        for(lp=0; lp<Tes.llMax; lp++) {
            if(  Ref.LL[lr].nl==Tes.LL[lp].nl 
               &&Ref.LL[lr].nn==Tes.LL[lp].nn 
               &&Ref.LL[lr].Weight!=0.0) { /* Reference Layer Number = Layer Number */
                Ref.LL[lr].Z = Ref.LL[lr].nl/Ref.truePitch;
                Tes.LL[lp].Z = Tes.LL[lp].nl/Tes.truePitch;
                Z  = Ref.LL[lr].Z;
                nn = Ref.LL[lr].nn;
                for(R=0; R<Ref.LL[lr].nR; R++) {
                    weight = Ref.LL[lr].Weight;
                    F      = fabs((Ref.LL[lr].data[R].F+Tes.LL[lp].data[R].F)/2.0*weight);
                    Sum += F;
                    xi[phiPara] += (F*nn);
                    xi[zPara]   += (F*(-2*PI*Z));
                }
            }
        }
    }
    xi[phiPara] = xi[phiPara]/Sum;
    xi[zPara]   = xi[zPara]  /Sum;
}

float
__lllDataFitQValue2(float* p)
{
    long lp, lr, R;
    llDataParaTypeReal dtheta, Res, Sum, refp, pp, pp2, F, Z, weight;
    llDataParaTypeInteger nn;

    Res = Sum = 0;
    for(lr=0; lr<Ref.llMax; lr++) {
        for(lp=0; lp<Tes.llMax; lp++) {
            if(  Ref.LL[lr].nl==Tes.LL[lp].nl 
           &&Ref.LL[lr].nn==Tes.LL[lp].nn 
           &&Ref.LL[lr].Weight!=0.0) { /* Reference Layer Number = Layer Number */
                Ref.LL[lr].Z = Ref.LL[lr].nl/Ref.truePitch;
                Tes.LL[lp].Z = Tes.LL[lp].nl/Tes.truePitch;
                Z  = Ref.LL[lr].Z;
                nn = Ref.LL[lr].nn;
                for(R=0; R<Ref.LL[lr].nR; R++) {
                    /* Phase Transform */ 
                    refp = nearSidePhaseGet(Ref.LL[lr].data[R].PHI, nn, Ref.LL[lr].Side, Ref.Pole);
                    pp   = nearSidePhaseGet(Tes.LL[lp].data[R].PHI, nn, Tes.LL[lp].Side, Tes.Pole);
                    pp2  = pp - nn*p[phiPara] + 2*PI*Z*p[zPara];
                    /* Phase Residual Calculation */
                    dtheta = fmod(refp - pp2, 2*PI);
                    dtheta = fabs(MIN(2*PI-dtheta, dtheta));
                    weight = Ref.LL[lr].Weight;
                    F      = fabs((Ref.LL[lr].data[R].F+Tes.LL[lp].data[R].F)/2.0*weight);
                    Sum += F;
                    Res += F*dtheta;
                }
            }    
        }
    }
    Res = Res/Sum;
    return Res;
}

void
__lllDataFitdRValue2(float* p, float* xi)
{
    long lp, lr, R;
    llDataParaTypeReal dtheta, res, Res, Sum, rp, pp, rF, pF, pp2, F, Z, weight;
    llDataParaTypeReal r, i, rr, ri, pr, pi, x;
    llDataParaTypeInteger nn;

    Res = Sum = 0;
    for(lr=0; lr<Ref.llMax; lr++) {
        for(lp=0; lp<Tes.llMax; lp++) {
            if(  Ref.LL[lr].nl==Tes.LL[lp].nl 
           &&Ref.LL[lr].nn==Tes.LL[lp].nn 
           &&Ref.LL[lr].Weight!=0.0) { /* Reference Layer Number = Layer Number */
                Ref.LL[lr].Z = Ref.LL[lr].nl/Ref.truePitch;
                Tes.LL[lp].Z = Tes.LL[lp].nl/Tes.truePitch;
                Z  = Ref.LL[lr].Z;
                nn = Ref.LL[lr].nn;
                for(R=0; R<Ref.LL[lr].nR; R++) {
                    /* Phase Transform */ 
                    rp = nearSidePhaseGet(Ref.LL[lr].data[R].PHI, nn, Ref.LL[lr].Side, Ref.Pole);
                    pp = nearSidePhaseGet(Tes.LL[lp].data[R].PHI, nn, Tes.LL[lp].Side, Tes.Pole);
                    pp2= pp - nn*p[phiPara] + 2*PI*Z*p[zPara];
                    /* Phase Residual Calculation */
                    rF = Ref.LL[lr].data[R].F;
                    pF = Tes.LL[lp].data[R].F;
                    weight = Ref.LL[lr].Weight;
                    F  = (rF + pF);
                    rr = rF*cos(rp);
                    ri = rF*sin(rp);
                    pr = pF*cos(pp2);
                    pi = pF*sin(pp2);
                    r  =  rr*pr + ri*pi;
                    i  = -rr*pi + ri*pr;
                    res = sqrt(SQR(r)+SQR(i))*weight;
                    Sum += F*weight;
                    Res += res;
                    x = ((rr*pF*(-sin(pp2))+ri*pF*cos(pp2))*r + (-rr*pF*cos(pp2)+ri*pF*(-sin(pp2)))*i)/res;
                    xi[phiPara] += x*(-nn);
                    xi[zPara]   += x*(2*PI*Z);
                }
            }    
        }
    }
    Res         /= Sum;
    xi[phiPara] /= Sum;
    xi[zPara]   /= Sum;    
}

float
__lllDataFitRValue2(float* p)
{
    long lp, lr, R;
    llDataParaTypeReal dtheta, Res, Sum, rp, pp, rF, pF, pp2, F, Z, weight;
    llDataParaTypeReal rr, ri, pr, pi;
    llDataParaTypeInteger nn;

    Res = Sum = 0;
    for(lr=0; lr<Ref.llMax; lr++) {
        for(lp=0; lp<Tes.llMax; lp++) {
            if(  Ref.LL[lr].nl==Tes.LL[lp].nl 
           &&Ref.LL[lr].nn==Tes.LL[lp].nn 
           &&Ref.LL[lr].Weight!=0.0) { /* Reference Layer Number = Layer Number */
                Ref.LL[lr].Z = Ref.LL[lr].nl/Ref.truePitch;
                Tes.LL[lp].Z = Tes.LL[lp].nl/Tes.truePitch;
                Z  = Ref.LL[lr].Z;
                nn = Ref.LL[lr].nn;
                for(R=0; R<Ref.LL[lr].nR; R++) {
                    /* Phase Transform */ 
                    rp = nearSidePhaseGet(Ref.LL[lr].data[R].PHI, nn, Ref.LL[lr].Side, Ref.Pole);
                    pp = nearSidePhaseGet(Tes.LL[lp].data[R].PHI, nn, Tes.LL[lp].Side, Tes.Pole);
                    pp2= pp - nn*p[phiPara] + 2*PI*Z*p[zPara];
                    /* Phase Residual Calculation */
                    rF = Ref.LL[lr].data[R].F;
                    pF = Tes.LL[lp].data[R].F;
                    weight = Ref.LL[lr].Weight;
                    F  = (rF + pF)*weight;
                    rr = rF*cos(rp);
                    ri = rF*sin(rp);
                    pr = pF*cos(pp2);
                    pi = pF*sin(pp2);
                    Sum += F;
                    Res += sqrt(SQR(rr*pr+ri*pi)+SQR(rr*pi-ri*pr))*weight;
                }
            }    
        }
    }
    Res = Res/Sum;
    return Res;
}
