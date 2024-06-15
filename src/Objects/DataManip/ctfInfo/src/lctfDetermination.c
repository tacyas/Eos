/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% lctfDetermination ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : lctfDetermination 
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%lctfDetermination ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include "./lctfDetermination.h"
#include "./powerspectraTangentLine.h"
#include "./ctfInfoWrite2.h"
#include "./lmrcFSInfoScatteringAngularDistributionAverageSection.h"
#define DEBUG
#include "genUtil.h"
#include "Vector.h"
#include "nr2.h"
#include "Memory.h"
/*
    Henderson-like Min-Max Method
		0.9<CTF*CTF: +Scattering : Score 
		CTF*CTF<0.1: -Scattering : Penalty
*/
static double __DefocusMaxDetermine(ctfInfo* ini, floatVector* spacing)
{
	ctfInfo tmp;
	int     i;
	int     flagDefocusMax = 0;
	double  ctfValue[3] = {0.0, 0.0, 0.0};
	double  tmpCutLow = 0.0;
	
	tmp = *ini;

	for(tmp.defocus = 0.0 ; tmp.defocus < ini->defocus*2 ; tmp.defocus += ini->defocus/1000.0){
		ctfValue[0] = ctfValue[1] = ctfValue[2] = 0.0;
		for(i=0 ; i <spacing->size ; i++){
			if( i <= 2){
				ctfValue[i] = pow(ctfFunction(&tmp, spacing->data[i],0),2);
			}
			else{
				ctfValue[0] = ctfValue[1];
				ctfValue[1] = ctfValue[2];
				ctfValue[2] = pow(ctfFunction(&tmp, spacing->data[i],0),2);
			}
			if((ctfValue[0] > ctfValue[1]) && (ctfValue[2] > ctfValue[1])){
				tmpCutLow = spacing->data[i];
				break;
			}
			//fprintf(stdout,"spacing:%lf ctfValue:%lf CutLow%lf\n",spacing->data[i],ctfValue[2],tmpCutLow);
		}
		//fprintf(stdout,"%lf %lf\n",ini->CutLow, tmpCutLow);
		if(ini->CutLow > tmpCutLow){
			flagDefocusMax = 1;
			return tmp.defocus;
			break;
		}
	}
	if( 0 == flagDefocusMax ){
		return ini->defocus*2;
	}
}

void
lctfDeterminationbyMinMaxMethods(ctfInfo* res, mrcImage* mrc, ctfInfo* ini, long mode)
{
    floatVector* scatter;
    floatVector* spacing;
    floatVector* ctf;
    long         i;
    float        E;
	float	     maxE;
    ctfInfo      tmp;

    scatter = lmrcFSInfoScatteringAngularDistributionAverage(mrc);
    spacing = lmrcFSInfoSpacing(mrc);
	DEBUGPRINT2("%f %f\n", scatter->data[1], spacing->data[1]);
    ctf     = floatVectorInit(NULL, spacing->size);
    tmp     = *ini;
    *res    = *ini;

    maxE = 0;

    for(tmp.defocus=0; tmp.defocus<2*ini->defocus; tmp.defocus+=ini->defocus/100.0) {
        for(i=0; i<spacing->size; i++) {
            ctf->data[i] = ctfFunction(&tmp, spacing->data[i], mode);
        }
		DEBUGPRINT1("%f\n", ctf->data[1]);
        E = 0.0;
        for(i=0; i<spacing->size; i++) {
            if(tmp.CutLow < spacing->data[i]
             &&spacing->data[i] < tmp.CutHigh ) {
                if(SQR(ctf->data[i])>0.9) {
                    E += scatter->data[i];
                } else if(SQR(ctf->data[i])<0.1) {
                    E -= scatter->data[i];
                }
            }
        }
        if(maxE<E) {
			fprintf(stdout, "Max: %f %f %f\n", tmp.defocus, E, maxE);
			maxE = E;
            res->defocus = tmp.defocus;
        }
        fprintf(stdout, "%10.6e %10.6e\n", tmp.defocus, E);
    }
}

/* 
	Fitting Method:

    F(R) = S(R)*S(R) + N(R)*N(R) + N2(R)*N2(R)
	, where
		S(R)  = I0*|CTF(R)|*Env(R)*ME(R)*Vib(R)*MTF(R) ,
		N(R)  = I0*White*MTF(R) and
		N2(R) = I0*White2

	Fitted to F(R)
        A   : Normalization Factor 
        CTF :   -sin(Kai)-a*cos(Kai)
                Kai = M_PI*dF*lambda*R*R - 0.5*M_PI*Cs*lambda*lambda*lambda*R*R*R*R
		ENV(Cs) : exp(-SQR(M_PI*Cs*lambda*lambda*R*R*R-M_PI*dF*R)*SQR(Ain)/log(2))
		ENV(Cc) : exp(-SQR(M_PI*lambda*R*R*Cc*dE/E*((1+E/E0)/(1+E/E0/2))/4/sqrt(log(2))))
        Me  : Table
        SN  : constant (White Noise)
        B   : constant (MTF) SingleExp/Lorenzian/Both 

    a[1]  : I0  : normarizing factor
    a[2]  : dF : defocus (underfocus is positive)
    a[3]  : Cs : Cs 
    a[4]  : a  : the ratio of amplitude contrast to phase contrast
    a[5]  : Ai : Illumination angle 
    a[6]  : Cc : Cc 
    a[7]  : dE : dE
    a[8]  : V  : Vibration : exp(-V*V*R*R/2)
    a[9]  : White  : signal to noise ratio
    a[10] : White2 : signal to noise ratio
    a[11] : B  : Dumping Factor of MTF: exp(-B*R)
    a[12] : E  : Energy : fixed
    a[13] : E0 : Energy : fixed
    a[14] : lambda  : Wave Length : fixed
    a[15] : Me : Scattering Factor : fixed

*/
static ctfInfo __lctfDetermineCTF;


void
angularDistributionFunctionOfSignalAndNoise(float x, float p[], float* y, float dyda[], int na)
{
    float R, I0, dF, Cs, a, Ai, Cc, dE, V, White, White2, B,  E, E0, lambda, Me;
	float chi, dchidR, dchi, spread, dspread, CTF, dCTF, Env1, Env2, Env, Vib, MTF;
	float S;
	float N;
	float N2;
	float F;
	float Mag;
	
	Mag = p[16];
    R  = x*Mag;
    I0 = p[1];
    dF = p[2];
    Cs = p[3];
    a  = p[4];
    Ai = p[5];
    Cc = p[6];
    dE = p[7];
    V  = p[8];
    White  = p[9];
    White2 = p[10];
    B  = p[11];
	/* */  
	if(__lctfDetermineCTF.flagMolecEnvTable) {
		Me = lmolecularEnvelopeDataGet(&(__lctfDetermineCTF.MolecEnvTable), R*1e-10, 0);
	} else {
		Me = exp(-p[12]*p[12]*R*R/2.0);
	}
	/* fixed */
    E  = p[13];
    E0 = p[14];
    lambda = p[15];

	/* Wave Length */
    chi    = M_PI*(dF*lambda - 0.5*Cs*lambda*lambda*lambda*R*R)*R*R;
    dchidR = 2*M_PI*(dF*lambda - Cs*lambda*lambda*lambda*R*R)*R;
	dchi   = M_PI*(Cs*lambda*lambda*R*R - dF)*R;
	spread = M_PI*lambda*R*R*Cc*dE/E*((1+E/E0)/(1+E/E0/2))/4/sqrt(log(2));
    CTF = -sin(chi) - a*cos(chi);
	Env1 = exp(-SQR(dchi)*SQR(Ai)/log(2));
	Env2 = exp(-SQR(spread));
	Env  = Env1*Env2;
	Vib  = exp(-V*V*R*R/2.0);
	MTF  = exp(-B*R);

	S  = I0*Me*CTF*Env*Vib*MTF;
	N  = I0*White*MTF;
	N2 = I0*White2;

    F  = SQR(S) + SQR(N) + SQR(N2);
	*y = F;


    dyda[1] = 2*F/I0;
    dyda[2] = 2*S*I0*Me*(-cos(chi)+a*sin(chi))*(M_PI*lambda*R*R)*Env*Vib*MTF
	         +2*S*S*(-2)*dchi*(-M_PI*R)*SQR(Ai)/log(2); 
    dyda[3] = 2*S*I0*Me*(-cos(chi)+a*sin(chi))*(M_PI*(-0.5)*lambda*lambda*lambda*R*R*R*R)*Env*Vib*MTF
	         +2*S*S*(-2)*dchi*(M_PI*lambda*lambda*R*R*R)*SQR(Ai)/log(2);
    dyda[4] = 2*S*I0*Me*(-cos(chi))*Env*Vib*MTF;
    dyda[5] = 2*S*S*(-2)*SQR(dchi)*Ai/log(2);
    dyda[6] = 2*S*S*(-2)*spread*M_PI*lambda*R*R*   dE/E*((1+E/E0)/(1+E/E0/2))/4/sqrt(log(2));
    dyda[7] = 2*S*S*(-2)*spread*M_PI*lambda*R*R*Cc   /E*((1+E/E0)/(1+E/E0/2))/4/sqrt(log(2));
    dyda[8] =   S*S*(-1)*V*R*R;
    dyda[9] = 2*N *N /White;
    dyda[10]= 2*N2*N2/White2;
    dyda[11]= 2*(S*S+N*N)*(-R);
	/* fixed */
	if(__lctfDetermineCTF.flagMolecEnvTable) {
    	dyda[12] = 0;
	} else {
		dyda[12] = 2*S*S*(-p[12]*R*R); 
	}
	DEBUGPRINT6("%e %e %e %e %e %e ", dyda[1], dyda[2], dyda[3], dyda[4], dyda[5], dyda[6]);
	DEBUGPRINT6("%e %e %e %e %e %e \n", dyda[7], dyda[8], dyda[9], dyda[10], dyda[11], dyda[12]);
    dyda[13]= 0.0;
    dyda[14]= 0.0;
    dyda[15]= 0.0;

	if(__lctfDetermineCTF.flagMolecEnvTable) {
		dyda[16]= x*
				  (2*S*
				  (I0*Me*((-cos(chi)+a*sin(chi))*dchidR)*Env*Vib*MTF 
				 + I0*Me*CTF*((-2)*dchi*SQR(Ai)/log(2)*M_PI*(3*Cs*lambda*lambda*R - dF)*Env1)*Vib*MTF 
				 + I0*Me*CTF*((-2)*spread*2*M_PI*lambda*R*Cc*dE/E*((1+E/E0)/(1+E/E0/2))/4/sqrt(log(2))*Env2)*Vib*MTF 
				 + I0*Me*CTF*Env*(-V*V*R*Vib)*MTF 
				 + I0*Me*CTF*Env*Vib*(-B*MTF)) 
				 +(2*N*(-B*N)));
	} else {
		dyda[16]= x*
				  (2*S*
				  (I0*(-V*V*R*Me)*CTF*Env*Vib*MTF 
				 + I0*Me*((-cos(chi)+a*sin(chi))*dchidR)*Env*Vib*MTF 
				 + I0*Me*CTF*((-2)*dchi*SQR(Ai)/log(2)*M_PI*(3*Cs*lambda*lambda*R*R - dF)*Env1)*Env2*Vib*MTF 
				 + I0*Me*CTF*Env1*((-2)*spread*2*M_PI*lambda*R*Cc*dE/E*((1+E/E0)/(1+E/E0/2))/4/sqrt(log(2))*Env2)*Vib*MTF 
				 + I0*Me*CTF*Env*(-V*V*R*Vib)*MTF 
				 + I0*Me*CTF*Env*Vib*(-B*MTF)) 
				 +(2*N*(-B*N)));
	}
}

void
lctfDeterminationbyFittingMethods(ctfInfo* res, ctfInfo* var, mrcImage* mrc, ctfInfo* ini, long mode)
{

    floatVector* scatter;
    floatVector* spacing;
    floatVector*  ctf;
    floatVector*  sig;
    long i, j, imin, imax, n, flag;
    float E, maxE;
    ctfInfo tmp;
	int count;
    float* a;
    int* ia;
    int ma;
    float** covar;
    float** alpha;
    float chisq;
    float alambda, oldalambda;

    scatter = lmrcFSInfoScatteringAngularDistributionAverage(mrc);
    sig     = lmrcFSInfoScatteringAngularDistributionSD(mrc);
    spacing = lmrcFSInfoSpacing(mrc);
    ctf     = floatVectorInit(NULL, spacing->size);
    imin = 0; imax = spacing->size - 1; n = 0;
    for(i=0; i<spacing->size; i++) {
        if(ini->CutLow  <= spacing->data[i]
         &&ini->CutHigh >= spacing->data[i]) {
            if(0==n) {
                imin = i;
            }
            n++;
        }
        spacing->data[i] = spacing->data[i]*1e10 ;
        DEBUGPRINT4("%d: %g %g %g\n", i, spacing->data[i], scatter->data[i], sig->data[i]);
    }
	if(n<3) {
		fprintf(stderr, "mrcImage is too small : %d!!\n", n);
		exit(EXIT_FAILURE);
	}
    DEBUGPRINT4("Low: %g High: %g ::: n: %d, imin: %d\n", ini->CutLow, ini->CutHigh, n, imin);
    tmp  = *ini;
    *res = *ini;

    ma = 16;
    a  = vector(1, ma);
    ia = ivector(1, ma);
    covar = matrix(1, ma, 1, ma);
    alpha = matrix(1, ma, 1, ma);

	for(i=1; i<=ma; i++) {	
		a[i]  = 0;
		ia[i] = 0;
		for(j=1; j<=ma; j++) {	
			covar[i][j] = 0;
			alpha[i][j] = 0;
		}
	}
	/* Parameter */
    a[1] = ini->I0;                 ia[1] = 1;
    a[2] = ini->defocus*1e-10;      ia[2] = 1;
    a[3] = ini->Cs*1e-3;            ia[3] = 1;
    a[4] = ini->ratioOfAmpToPhase;  ia[4] = 1;
    a[5] = ini->Ain*1e-3;           ia[5] = 1;
    a[6] = ini->Cc*1e-3;            ia[6] = 1;
    a[7] = ini->dE;                 ia[7] = 1;
    a[8] = ini->BofVibration*1e-10; ia[8] = 1;
    a[9] = ini->WhiteNoise;         ia[9] = 1;
    a[10]= ini->WhiteNoise2;        ia[10] = 1;
    a[11]= ini->BofMTF*1e-10;       ia[11] = 1;
	if(ini->flagMolecEnvTable) {
    	a[12]= 0;   ia[12] = 0;
	} else {
    	a[12]= ini->MolecEnv*1e-10; ia[12] = 1;
	}
	/* fixed */
    a[13] = ini->kV*1e3;                 ia[13] = 0;
    a[14] = 511*1e3;                     ia[14] = 0;
    a[15] = wavelengthOfElectron(ini->kV*1e3); ia[15] = 0;
	fprintf(stderr, "lambda: %g\n", a[15]); 
	/* Parameter */	
	a[16] = ini->Magnification;     ia[16] = 1;

	__lctfDetermineCTF = *ini;

    alambda = -1;
	oldalambda = 1e-6;
	for(count=0; count<20; count++) {
		fprintf(stdout, "count: %d\n", count); fflush(stdout);
    	mrqmin(spacing->data+imin-1, scatter->data+imin-1, sig->data+imin-1, n, a, ia, ma, covar, alpha, &chisq, angularDistributionFunctionOfSignalAndNoise, &alambda);
		fprintf(stdout, "chisq: %15.6g\n", chisq);
		fprintf(stdout, "alambda: %15.6g\n", alambda);
		for(i=1; i<=ma; i++) {
			fprintf(stdout, "a[%d]: %15.6g\n", i, a[i]); 
		}
		if(alambda<1e-6) {
			break;
		} else if(oldalambda<alambda) {
			count--; 
		}
		oldalambda = alambda;
		fflush(stdout);
	}
	fprintf(stdout, "Fitting End: %15.6g\n", chisq);
    res->I0                = a[1];
    res->defocus           = a[2]*1e10;
    res->Cs                = a[3]*1e+3;
    res->ratioOfAmpToPhase = a[4];
    res->Ain               = a[5]*1e+3;
    res->Cc                = a[6]*1e+3;
    res->dE                = a[7];
    res->BofVibration      = a[8]*1e10;
    res->WhiteNoise        = a[9];
    res->WhiteNoise2       = a[10];
    res->BofMTF            = a[11]*1e10;
	if(ini->flagMolecEnvTable) {
	} else {
    	res->MolecEnv      = a[12]*1e10;
	}
	res->Magnification     = a[16];  

	alambda = 0;
    mrqmin(spacing->data+imin-1, scatter->data+imin-1, sig->data+imin-1, n, a, ia, ma, covar, alpha, &chisq, angularDistributionFunctionOfSignalAndNoise, &alambda);
	fprintf(stdout, "chisq: %15.6g\n", chisq);
	fprintf(stdout, "alambda: %15.6g\n", alambda);
	for(i=1; i<=ma; i++) {
		fprintf(stdout, "a[%d]: %15.6g\n", i, a[i]); 
	}
    var->I0                = sqrt(covar[1][1]);
    var->defocus           = sqrt(covar[2][2])*1e10;
    var->Cs                = sqrt(covar[3][3])*1e+3;
    var->ratioOfAmpToPhase = sqrt(covar[4][4]);
    var->Ain               = sqrt(covar[5][5])*1e+3;
    var->Cc                = sqrt(covar[6][6])*1e+3;
    var->dE                = sqrt(covar[7][7]);
    var->BofVibration      = sqrt(covar[8][8])*1e10;
    var->WhiteNoise        = sqrt(covar[9][9]);
    var->WhiteNoise2       = sqrt(covar[10][10]);
    var->BofMTF            = sqrt(covar[11][11])*1e10;
	if(ini->flagMolecEnvTable) {
	} else {
    	res->MolecEnv      = sqrt(covar[12][12])*1e10;
	}
	var->Magnification     = sqrt(covar[16][16]);
}

/*
	Differential Method
		ThonRing Point:	ScatteringDifferential	:0	score+
							:+or-	score-
*/
/*
	LimitValue
		determination	   MaximumValue		:return 	+1
				or minimumValue		:return		-1
				   NotLimitValue	:return		 0
*/

static float __power(float x,long a)
{
	long i;
	float y = 1.0;
	for(i=0 ; i<a ; i++){
		y *= x;
	}
	return(y);	
}


static int  __LimitValue(floatVector* function,long i,long around)
{
	float	before = 0.0,after = 0.0;
	long    j;
	int	flag;
	
	j = i-around;
	//while(before == 0.0){
		before	=function->data[i]-function->data[j];
	//	j -= 1;
	//}

	j = i+around;
	//while(after == 0.0){
		after	=function->data[j]-function->data[i];
	//	j += 1;
	//}

	if(before > 0.0){
		if(after <= 0){
			flag = 1;
		}
		else{
			flag = 0;
		}
	}
	else if(before < 0.0){
		if(after >= 0){
			flag = -1;
		}
		else{
			flag = 0;
		}
	}
	else{
		if(after > 0.0){
			flag = -1;
		}
		else{
			flag = +1;
		}
	}
	return(flag);
}

static int  __SquareLimitValue(floatVector* function,long i,long around)
{
	float	before = 0.0,after = 0.0;
	long    j;
	int	flag;
	
	j = i-around;
	//while(before == 0.0){
		before	= SQR(function->data[i])-SQR(function->data[j]);
	//	j -= 1;
	//}

	j = i+around;
	//while(after == 0.0){
		after	= SQR(function->data[j])-SQR(function->data[i]);
	//	j += 1;
	//}
	//fprintf(stdout,"%ld %f %f ",i,before,after);
	
	
	if(before > 0.0){
		if(after <= 0){
			flag = 1;
		}
		else{
			flag = 0;
		}
	}
	else if(before < 0.0){
		if(after >= 0){
			flag = -1;
		}
		else{
			flag = 0;
		}
	}
	else{
		
		if(after > 0.0){
			flag = -1;
		}
		else{
			flag = +1;
		}
	}
	//fprintf(stdout,"%ld\n",flag);
	return(flag);
}


static float __Median(floatVector* function, long i, long around){
	
	float sequence[around*2 + 1];
	float tmp;
	long  j,k;

	k = 0;
	for(j=i-around;j<=i+around;j++){
		sequence[k] = function->data[j];
		k++;
	}
	
	for(j=0;j<around*2+1;j++){
		for(k=j+1;k<around*2+1;k++){
			if(sequence[j]>sequence[k]){
				tmp = sequence[j];
				sequence[j] = sequence[k];
				sequence[k] = tmp;
			}
		}
	}
	return(sequence[around]);
}

static float __Average(floatVector* function,long i,long around){
	
	long  j;
	float sum = 0.0;

	for(j=i-around;j<=i+around;j++){
		sum += function->data[j];
	}

	return(sum/(around*2+1));
}


static long __LongAbs(long x){
	
	if(x <=  0){
		return(-x);
	}
	else{
		return(x);
	}
}
static float __AverageWithWeight(floatVector* function,long i,long around){
	
	long  j;
	float sum = 0.0;
	float n = 0.0;

	for(j=i-around;j<=i+around;j++){
		sum += function->data[j]/(__LongAbs(i-j)+1);
		n   += (float)1/( __LongAbs(i-j) + 1);
	}
	return( sum/n );

}


/*Smoothing is CurveSmoothing
	mode 1:	for MedianMethod
	mode 2:	for AverageMethod
	mode 3: for AverageMethod with Weight
*/
void __Smoothing(floatVector* function,floatVector* SmoothCurve ,long around,long mode){
	
	long i;
	long aroundtmp;
	
	aroundtmp = around;
	
	for(i=0;i<function->size;i++){
		aroundtmp = around;
		if(i!=0 && i!=function->size-1){
			if(i<around){
				aroundtmp = i;
			}
			else if(i>function->size-1-around){
				aroundtmp = function->size-1-i;
			}
			
			switch(mode){
				case 1:{
					SmoothCurve->data[i] = __Median(function,i,aroundtmp);
					break;
				}
				case 2:{
					SmoothCurve->data[i] = __Average(function,i,aroundtmp);
					break;
				}
				case 3:{
					SmoothCurve->data[i] = __AverageWithWeight(function,i,aroundtmp);
					break;
				}
			}
		}
			
		else{
			SmoothCurve->data[i] = function->data[i];
		}
	}
		
}


void
lctfDeterminationbyDifferentialMethods(ctfInfo* res, mrcImage* mrc, ctfInfo* ini,long* MaxThonRing, long mode)
{
	floatVector* scatter;
	floatVector* spacing;
	floatVector* ctf;
	floatVector* MedianCurve;
	long         i;
	long         Differentialaround;
	long         Smootharound;
	long         Smoothmode;
	long         ThonRing;
	float        E;
	float	     maxE=0;
	float        ME;			/*M......with MedianCurve*/
	float        MmaxE=0;
	ctfInfo      tmp;
	ctfInfo      Mres;
	//float        Mres;
	
	Differentialaround = 1;
	Smootharound       = 2;
	Smoothmode         = 1;
	
	scatter = lmrcFSInfoScatteringAngularDistributionAverage(mrc);
	spacing = lmrcFSInfoSpacing(mrc);
	DEBUGPRINT2("%f %f\n", scatter->data[1], spacing->data[1]);
	ctf     = floatVectorInit(NULL, spacing->size);
	tmp     = *ini;
	*res    = *ini;
	Mres   = *ini;
	
	fprintf(stdout,"\nDifferentialMethod\n");
	MedianCurve = floatVectorInit(NULL,spacing->size);
	for(tmp.defocus = 0.0; tmp.defocus<2*ini->defocus; tmp.defocus+=ini->defocus/1000.0) {
		for(i=0;i<spacing->size;i++){
			ctf->data[i] = ctfFunction(&tmp, spacing->data[i],mode);
		}
		__Smoothing(scatter,MedianCurve,Smootharound,Smoothmode);
		DEBUGPRINT1("%f\n", ctf->data[1]);
		E = 0.0;
		ME= 0.0;
		ThonRing = 0;
		for(i=(0+Differentialaround); i<(spacing->size-Differentialaround); i++) {
			if(tmp.CutLow < spacing->data[i]
			&&spacing->data[i] < tmp.CutHigh ) {
				/*DifferentialMethod*/
				if(__SquareLimitValue(ctf,i,Differentialaround) == -1){
					ThonRing += 1;
					if(__LimitValue(scatter,i,Differentialaround) == -1){
						E+=1.0;
					}
					else{
						E-=1.0;
					}

					if(__LimitValue(MedianCurve,i,Differentialaround) == -1){
						ME+=1.0;
					}
					else{
						ME-=1.0;
					}
					
				}
                	}
            	}
        	if(maxE<E) {
			fprintf(stdout, "Max: %10.6e %f %f\n", tmp.defocus, E, maxE);
			maxE = E;
			res->defocus = tmp.defocus;
		}

		if(MmaxE<ME){
			//fprintf(stdout, "MMAX: %f %f %f\n", tmp.defocus,ME,MmaxE);
			MmaxE = ME;
			Mres.defocus         = tmp.defocus;
			*MaxThonRing = ThonRing;
		}
        	//fprintf(stdout, "%10.6e %3ld  %3.0f %3.0f\n", tmp.defocus,ThonRing, E,ME);
	}
	fprintf(stdout,"defocus(not median)= %10.6f (median)= %10.6f\n",res->defocus,Mres.defocus);
	
	res->defocus = Mres.defocus;
	/*for smooth test*/
	/*for(i=0;i<spacing->size;i++){
		ctf->data[i]  = ctfFunction(&Mres, spacing->data[i],mode);
	}
	fprintf(stdout,"\n\ndefocus:%f\n",Mres.defocus);
	fprintf(stdout,"    spacing:    SQR(ctf):     scatter:\n");
	for(i=0;i<spacing->size;i++){
		
		if(tmp.CutLow < spacing->data[i]
		&&spacing->data[i] < tmp.CutHigh ) {
			fprintf(stdout,"%10.6e %10.6e %10.6e ",spacing->data[i],SQR(ctf->data[i]),scatter->data[i]);
			if(__SquareLimitValue(ctf,i,Differentialaround) == -1){
				fprintf(stdout,"ring\n");
			}
			else{
				fprintf(stdout,"\n");
			}
		}
	}*/
}

void __MinSquare(floatVector* functionX,floatVector* functionY,floatVector* MinSquare,long around){
	long i;
	long j;
	long tmpAround;
	float x;
	float y;
	float xy;
	float xx;
	long n;

	tmpAround = around;
	n = around*2+1;
	for(i=around;i<functionX->size-around;i++){
		tmpAround = around;
		
		if(i<around){
			tmpAround = i;
		}
		else if(functionX->size-1-i<around){
			tmpAround = functionX->size-1-i;
		}
		
		if(i!=0 || i!=functionX->size-1){
			x = 0.0;
			y = 0.0;
			xx = 0.0;
			xy = 0.0;
			for(j=i-around;j<=i+around;j++){
				x += functionX->data[j];
				y += functionY->data[j];
				xy += functionX->data[j]*functionY->data[j];
				xx += functionX->data[j]*functionX->data[j];
			}
			MinSquare->data[i] = (n*xy-x*y)/(n*xx-x*x);
		}
		else{
			MinSquare->data[i] = 0.0;
		}
	}
}

void __MinimumByMinSquare(floatVector* functionX,floatVector* functionY,floatVector* Minimum,long around)
{	
	floatVector* MinSquare;
	floatVector* MinimumBaf;
	long i;
	long j;
	long k;
	long l;
	long CountSame = 1;

	MinimumBaf = floatVectorInit(NULL,functionX->size);
	MinSquare = floatVectorInit(NULL,functionX->size);
	__MinSquare(functionX,functionY,MinSquare,around);

	for(i=0;i<functionX->size;i++){
		if(MinSquare->data[i] > 0.0){
			MinSquare->data[i] = 1.0;
		}
		else if(MinSquare->data[i] < 0.0){
			MinSquare->data[i] = -1.0;
		}
	}
	
	for(i=1;i<functionX->size;i++){
		/*for minimum lotation*/
		if(functionY->data[i] == functionY->data[i-1]){
			CountSame     += 1;
		}
		else{
			CountSame     = 1;
		}
		
		switch ((int)MinSquare -> data[i-1]){
			case (int)-1:{
				switch ((int)MinSquare->data[i]){
					case (int)1:{
						Minimum->data[i] = 1.0;
						break;
					}
					case (int)-1:{
						Minimum->data[i] = 0.0;
						break;
					}
					case (int)0:{
						j = 1;
						while(MinSquare->data[i+j] == 0.0 ){
							if(i+j == functionX->size){
								break;
							}
							j++;
						}
						
						if(MinSquare->data[i+j] > 0){
							Minimum->data[i] == 1.0;
						}
						else if(MinSquare->data[i+j] < 0){
							Minimum->data[i] == 0.0;
						}
						break;
					}
				}
			}


			case (int)1:{
				Minimum->data[i] == 0.0;	
				break;
			}

			case (int)0:{
				j = -1;
				while(MinSquare->data[i+j] == 0.0){
					if(i+j == 0){
						break;
					}
					j--;
				}

				if(MinSquare->data[i+j] > 0.0){
					Minimum->data[i] == 0.0;
				}
				else if(MinSquare->data[i+j] <= 0.0){
					k = 1;
					while(MinSquare->data[i+k] == 0.0){
						if(i+k == functionX->size){
							break;
						}
						k++;
					}
					
					if(MinSquare->data[i+k] >= 0.0){
						Minimum->data[i] = 1.0;
					}
					else{
						Minimum->data[i] = 0.0;
					}
				}
				break;
			}	
		}
		/**/
		if(Minimum->data[i] == 1){
			Minimum->data[i] = 0;
			for(l = 0 ; l < CountSame ; l++){
				Minimum->data[i-l] += (1.0 / CountSame);
			}
		}
		/**/
	}
}


void __MaximumByMinSquare(floatVector* functionX,floatVector* functionY,floatVector* Maximum,long around)
{	
	floatVector* MinSquare;
	floatVector* MaximumBaf;
	long i;
	long j;
	long k;
	long l;
	long CountSame = 1;

	MaximumBaf = floatVectorInit(NULL,functionX->size);
	MinSquare = floatVectorInit(NULL,functionX->size);
	__MinSquare(functionX,functionY,MinSquare,around);

	for(i=0;i<functionX->size;i++){
		if(MinSquare->data[i] > 0.0){
			MinSquare->data[i] = 1.0;
		}
		else if(MinSquare->data[i] < 0.0){
			MinSquare->data[i] = -1.0;
		}
	}
	
	for(i=1;i<functionX->size;i++){
		/*for Maximum lotation*/
		if(functionY->data[i] == functionY->data[i-1]){
			CountSame     += 1;
		}
		else{
			CountSame     = 1;
		}
		
		switch ((int)MinSquare -> data[i-1]){
			case (int)1:{
				switch ((int)MinSquare->data[i]){
					case (int)-1:{
						Maximum->data[i] = 1.0;
						break;
					}
					case (int)1:{
						Maximum->data[i] = 0.0;
						break;
					}
					case (int)0:{
						j = -1;
						while(MinSquare->data[i+j] == 0.0 ){
							if(i+j == functionX->size){
								break;
							}
							j++;
						}
						
						if(MinSquare->data[i+j] < 0){
							Maximum->data[i] == 1.0;
						}
						else if(MinSquare->data[i+j] > 0){
							Maximum->data[i] == 0.0;
						}
						break;
					}
				}
			}


			case (int)-1:{
				Maximum->data[i] == 0.0;	
				break;
			}

			case (int)0:{
				j = -1;
				while(MinSquare->data[i+j] == 0.0){
					if(i+j == 0){
						break;
					}
					j--;
				}

				if(MinSquare->data[i+j] < 0.0){
					Maximum->data[i] == 0.0;
				}
				else if(MinSquare->data[i+j] >= 0.0){
					k = 1;
					while(MinSquare->data[i+k] == 0.0){
						if(i+k == functionX->size){
							break;
						}
						k++;
					}
					
					if(MinSquare->data[i+k] <= 0.0){
						Maximum->data[i] = 1.0;
					}
					else{
						Maximum->data[i] = 0.0;
					}
				}
				break;
			}	
		}
		/**/
		if(Maximum->data[i] == 1){
			Maximum->data[i] = 0;
			for(l = 0 ; l < CountSame ; l++){
				Maximum->data[i-l] += (1.0 / CountSame);
			}
		}
		/**/
	}
}


void
lctfDeterminationbyMinSquareMethods(ctfInfo* res, mrcImage* mrc, ctfInfo* ini,long* MaxThonRing, lctfDetermineInfo* linfo, floatVector* defocus, floatVector* Eres, long mode)
{
	floatVector* scatter;
	floatVector* spacing;
	floatVector* ctf;
	floatVector* ctfSQR;
	floatVector* MedianCurve3;
	floatVector* MedianCurve5;
	floatVector* MedianCurve7;
	floatVector* MinSquare;
	
	floatVector* Minimum;
	floatVector* Minimum33;
	floatVector* Minimum35;
	floatVector* Minimum37;
	floatVector* Minimum53;
	floatVector* Minimum55;
	floatVector* Minimum57;
	floatVector* Minimum73;
	floatVector* Minimum75;
	floatVector* Minimum77;

	
	floatVector* Maximum;
	floatVector* Maximum33;
	floatVector* Maximum35;
	floatVector* Maximum37;
	floatVector* Maximum53;
	floatVector* Maximum55;
	floatVector* Maximum57;
	floatVector* Maximum73;
	floatVector* Maximum75;
	floatVector* Maximum77;
	
	floatVector* ThonRing; 
	floatVector* ctfMinSquare;
	floatVector* Noise;
	long         i,j,k;
	long         l = 0;
	long         Differentialaround;
	long         Smootharound;
	long         Smoothmode;
	long         ThonRingSize;
	float	     maxE=0;
	float        E;			/*M......with MedianCurve*/
	float        MmaxE=0;
	double       defocusMax = 0.0;
	ctfInfo      tmp;
	ctfInfo      Mres;

	float**     aboveCoefficient;	/*without Noise*/
	float**     belowCoefficient;

	belowCoefficient = MemoryAllocate(float*, linfo->degree+1, "in lctfDeterminationByTangent");
	for(i=0 ; i<linfo->degree+1  ; i++){
		belowCoefficient[i] = MemoryAllocate(float, i+1, "in lctfDeterminationByTangent");
	}
	aboveCoefficient = MemoryAllocate(float*, linfo->degree+1, "in lctfDeterminationByTangent");
	for(i=0 ; i<linfo->degree+1 ; i++){
		aboveCoefficient[i] = MemoryAllocate(float, i+1, "in lctfDeterminationByTangent");
	}
	
	Differentialaround = 1;
	Smoothmode         = 1;
	
	scatter = lmrcFSInfoScatteringAngularDistributionAverage(mrc);
	//scatter = lmrcFSInfoScatteringAngularDistributionAverageSection(mrc,4);
	spacing = lmrcFSInfoSpacing(mrc);
	DEBUGPRINT2("%f %f\n", scatter->data[1], spacing->data[1]);
	ctf     = floatVectorInit(NULL, spacing->size);
	ctfSQR  = floatVectorInit(NULL, spacing->size);
	ThonRing= floatVectorInit(NULL, spacing->size);
	ctfMinSquare = floatVectorInit(NULL,spacing->size);
	Noise        = floatVectorInit(NULL,spacing->size);
	tmp     = *ini;
	*res    = *ini;
	Mres   = *ini;

	//fprintf(stdout,"\nDifferentialMethod\n");
	MedianCurve3 = floatVectorInit(NULL,spacing->size);
	MedianCurve5 = floatVectorInit(NULL,spacing->size);
	MedianCurve7 = floatVectorInit(NULL,spacing->size);
	MinSquare    = floatVectorInit(NULL,spacing->size);
	
	Minimum      = floatVectorInit(NULL,spacing->size);
	Minimum33    = floatVectorInit(NULL,spacing->size);
	Minimum35    = floatVectorInit(NULL,spacing->size);	
	Minimum37    = floatVectorInit(NULL,spacing->size);
	Minimum53    = floatVectorInit(NULL,spacing->size);
	Minimum55    = floatVectorInit(NULL,spacing->size);
	Minimum57    = floatVectorInit(NULL,spacing->size);
	Minimum73    = floatVectorInit(NULL,spacing->size);
	Minimum75    = floatVectorInit(NULL,spacing->size);
	Minimum77    = floatVectorInit(NULL,spacing->size);

	Maximum      = floatVectorInit(NULL,spacing->size);
	Maximum33    = floatVectorInit(NULL,spacing->size);
	Maximum35    = floatVectorInit(NULL,spacing->size);	
	Maximum37    = floatVectorInit(NULL,spacing->size);
	Maximum53    = floatVectorInit(NULL,spacing->size);
	Maximum55    = floatVectorInit(NULL,spacing->size);
	Maximum57    = floatVectorInit(NULL,spacing->size);
	Maximum73    = floatVectorInit(NULL,spacing->size);
	Maximum75    = floatVectorInit(NULL,spacing->size);
	Maximum77    = floatVectorInit(NULL,spacing->size);
	
	if(1 == mode){/*Noise Estimation*/
		TangentLine(spacing, scatter, belowCoefficient, aboveCoefficient, ini, linfo,-1);
		for(i=(0+Differentialaround); i<(spacing->size-Differentialaround); i++){
			Noise->data[i] = belowCoefficient[linfo->degree][0];
			for(j=1 ; j<=linfo->degree ; j++){
				Noise->data[i] += belowCoefficient[linfo->degree][j]*__power(spacing->data[i],j);
			}
			scatter->data[i] = scatter->data[i] - pow(10,Noise->data[i]);
		}
		mode = 0;
	}

	
	__Smoothing(scatter,MedianCurve3,1,1);
	__Smoothing(scatter,MedianCurve5,2,1);
	__Smoothing(scatter,MedianCurve7,3,1);

	__MinimumByMinSquare(spacing,MedianCurve3,Minimum33,1);
	__MinimumByMinSquare(spacing,MedianCurve3,Minimum35,2);
	__MinimumByMinSquare(spacing,MedianCurve3,Minimum37,3);
	__MinimumByMinSquare(spacing,MedianCurve5,Minimum53,1);
	__MinimumByMinSquare(spacing,MedianCurve5,Minimum55,2);
	__MinimumByMinSquare(spacing,MedianCurve5,Minimum57,3);
	__MinimumByMinSquare(spacing,MedianCurve7,Minimum73,1);
	__MinimumByMinSquare(spacing,MedianCurve7,Minimum75,2);
	__MinimumByMinSquare(spacing,MedianCurve7,Minimum77,3);

	__MaximumByMinSquare(spacing,MedianCurve3,Maximum33,1);
	__MaximumByMinSquare(spacing,MedianCurve3,Maximum35,2);
	__MaximumByMinSquare(spacing,MedianCurve3,Maximum37,3);
	__MaximumByMinSquare(spacing,MedianCurve5,Maximum53,1);
	__MaximumByMinSquare(spacing,MedianCurve5,Maximum55,2);
	__MaximumByMinSquare(spacing,MedianCurve5,Maximum57,3);
	__MaximumByMinSquare(spacing,MedianCurve7,Maximum73,1);
	__MaximumByMinSquare(spacing,MedianCurve7,Maximum75,2);
	__MaximumByMinSquare(spacing,MedianCurve7,Maximum77,3);
	
	__MinSquare(spacing,MedianCurve5,MinSquare,2);

	defocusMax = __DefocusMaxDetermine(ini, spacing);
	for(tmp.defocus = 0.0; tmp.defocus< 2*ini->defocus; tmp.defocus+=ini->defocus/1000.0) {
		defocus->data[l] = tmp.defocus;
		for(i=0;i<spacing->size;i++){
			ctf->data[i] = ctfFunction(&tmp, spacing->data[i],mode);
		}
		DEBUGPRINT1("%f\n", ctf->data[1]);
		E = 0.0;
		ThonRingSize = 0;
		for(i=(0+Differentialaround); i<(spacing->size-Differentialaround); i++) {
			ThonRing->data[i] = 0;
			if(tmp.CutLow < spacing->data[i] && spacing->data[i] < tmp.CutHigh ) {				
				/*DifferentialMethod*/
				if(__SquareLimitValue(ctf,i,Differentialaround) == -1){
					ThonRing->data[i] = 1;
					ThonRingSize += 1;
				}
                	}
			
            	}
		j = 0;
		k = 0;
		for(i=(0+Differentialaround); i<(spacing->size-Differentialaround); i++) {
			
			E += 2*Minimum33->data[i]*(0.5-SQR(ctf->data[i]))+2*Minimum35->data[i]*(0.5-SQR(ctf->data[i]))+2*Minimum37->data[i]*(0.5-SQR(ctf->data[i]))+
			     2*Minimum53->data[i]*(0.5-SQR(ctf->data[i]))+2*Minimum55->data[i]*(0.5-SQR(ctf->data[i]))+2*Minimum57->data[i]*(0.5-SQR(ctf->data[i]))+
			     2*Minimum73->data[i]*(0.5-SQR(ctf->data[i]))+2*Minimum75->data[i]*(0.5-SQR(ctf->data[i]))+2*Minimum77->data[i]*(0.5-SQR(ctf->data[i])); 

			E += 2*Maximum33->data[i]*(-0.5+SQR(ctf->data[i]))+2*Maximum35->data[i]*(-0.5+SQR(ctf->data[i]))+2*Maximum37->data[i]*(-0.5+SQR(ctf->data[i]))+
			     2*Maximum53->data[i]*(-0.5+SQR(ctf->data[i]))+2*Maximum55->data[i]*(-0.5+SQR(ctf->data[i]))+2*Maximum57->data[i]*(-0.5+SQR(ctf->data[i]))+
			     2*Maximum73->data[i]*(-0.5+SQR(ctf->data[i]))+2*Maximum75->data[i]*(-0.5+SQR(ctf->data[i]))+2*Maximum77->data[i]*(-0.5+SQR(ctf->data[i])); 
		
		}
		E = E/9;

		if((ThonRingSize <= E )|| (tmp.defocus > defocusMax) ){
			E = 0;
		}
		
		if(MmaxE<=E && ThonRingSize >= E/*&& k == j*/){
			//fprintf(stdout, "MMAX: %6.0f %f %f\n", tmp.defocus,E,MmaxE);
			MmaxE = E;
			res->defocus = tmp.defocus;
			*MaxThonRing = ThonRingSize;
		}
		
		/*if((ThonRingSize <= E )|| (tmp.defocus > defocusMax) ){
			E = 0;
		}*/
		Eres->data[l] = E;
       	//fprintf(stdout, "defocus %6f ring %3ld res %f MaxE %lf E %lf\n", defocus->data[l],ThonRingSize,Eres->data[l],MmaxE,E);
		l++;
	}
	fprintf(stdout,"defocus: %f\n",res->defocus);
	/*for smooth test*/
	/*Minimum = Minimum33;
	for(i=0;i<spacing->size;i++){
		ctf->data[i]  = ctfFunction(res, spacing->data[i],mode);
		ctfSQR->data[i] = SQR(ctf->data[i]);
	}
	__MinimumByMinSquare(spacing,ctfSQR,ThonRing,1);

	__MinSquare(spacing,ctfSQR,ctfMinSquare,1);
	fprintf(stdout,"    spacing:    SQR(ctf):     scatter:     Median:   | Minimum(33,35,37,53,55,57,73,75,77):\n");
	for(i=0;i<spacing->size;i++){
		
		if(tmp.CutLow < spacing->data[i]
		&&spacing->data[i] < tmp.CutHigh ) {
			fprintf(stdout,"%10.6e %10.6e %10.6e %10.6e | %4.2f %4.2f %4.2f | %4.2f %4.2f %4.2f | %4.2f %4.2f %4.2f || %4.2f %4.2f %4.2f | %4.2f %4.2f %4.2f | %4.2f %4.2f %4.2f "\
					,spacing->data[i],SQR(ctf->data[i]),scatter->data[i],MedianCurve5->data[i],Minimum33->data[i],Minimum35->data[i],Minimum37->data[i],Minimum53->data[i],Minimum55->data[i],Minimum57->data[i],Minimum73->data[i],Minimum75->data[i],Minimum77->data[i],Maximum33->data[i],Maximum35->data[i],Maximum37->data[i],Maximum53->data[i],Maximum55->data[i],Maximum57->data[i],Maximum73->data[i],Maximum75->data[i],Maximum77->data[i]);
			if(__SquareLimitValue(ctf,i,Differentialaround) == -1){
				fprintf(stdout,"Ring\n");
			}
			else{
				fprintf(stdout,"\n");
			}
		}
	}
*/
}


void
lctfDeterminationbyMinSquareMethodsWithAcomp(ctfInfo* res, mrcImage* mrc, ctfInfo* ini,long* MaxThonRing,lctfDetermineInfo* linfo,floatVector* defocus,floatVector* Eres, long mode)
{
	floatVector* scatter;
	floatVector* spacing;
	floatVector* ctf;
	floatVector* ctfSQR;
	floatVector* MedianCurve3;
	floatVector* MedianCurve5;
	floatVector* MedianCurve7;
	floatVector* MinSquare;
	
	floatVector* Minimum;
	floatVector* Minimum33;
	floatVector* Minimum35;
	floatVector* Minimum37;
	floatVector* Minimum53;
	floatVector* Minimum55;
	floatVector* Minimum57;
	floatVector* Minimum73;
	floatVector* Minimum75;
	floatVector* Minimum77;

	
	floatVector* Maximum;
	floatVector* Maximum33;
	floatVector* Maximum35;
	floatVector* Maximum37;
	floatVector* Maximum53;
	floatVector* Maximum55;
	floatVector* Maximum57;
	floatVector* Maximum73;
	floatVector* Maximum75;
	floatVector* Maximum77;
	
	floatVector* ThonRing; 
	floatVector* ctfMinSquare;
	floatVector* Noise;
	long         i,j,k;
	long         l = 0;
	long         Differentialaround;
	long         Smootharound;
	long         Smoothmode;
	long         ThonRingSize;
	float	     maxE=0;
	float        E;			/*M......with MedianCurve*/
	float        MmaxE=0;
	float        ctfMax = 0;
	ctfInfo      tmp;
	ctfInfo      Mres;

	float**     aboveCoefficient;	/*without Noise*/
	float**     belowCoefficient;

	belowCoefficient = MemoryAllocate(float*, linfo->degree+1, "in lctfDeterminationByTangent");
	for(i=0 ; i<linfo->degree+1  ; i++){
		belowCoefficient[i] = MemoryAllocate(float, i+1, "in lctfDeterminationByTangent");
	}
	aboveCoefficient = MemoryAllocate(float*, linfo->degree+1, "in lctfDeterminationByTangent");
	for(i=0 ; i<linfo->degree+1 ; i++){
		aboveCoefficient[i] = MemoryAllocate(float, i+1, "in lctfDeterminationByTangent");
	}
	
	Differentialaround = 1;
	Smoothmode         = 1;
	
	scatter = lmrcFSInfoScatteringAngularDistributionAverage(mrc);
	//scatter = lmrcFSInfoScatteringAngularDistributionAverageSection(mrc,4);
	spacing = lmrcFSInfoSpacing(mrc);
	DEBUGPRINT2("%f %f\n", scatter->data[1], spacing->data[1]);
	ctf     = floatVectorInit(NULL, spacing->size);
	ctfSQR  = floatVectorInit(NULL, spacing->size);
	ThonRing= floatVectorInit(NULL, spacing->size);
	ctfMinSquare = floatVectorInit(NULL,spacing->size);
	Noise        = floatVectorInit(NULL,spacing->size);
	tmp     = *ini;
	*res    = *ini;
	Mres   = *ini;

	//fprintf(stdout,"\nDifferentialMethod\n");
	MedianCurve3 = floatVectorInit(NULL,spacing->size);
	MedianCurve5 = floatVectorInit(NULL,spacing->size);
	MedianCurve7 = floatVectorInit(NULL,spacing->size);
	MinSquare    = floatVectorInit(NULL,spacing->size);
	
	Minimum      = floatVectorInit(NULL,spacing->size);
	Minimum33    = floatVectorInit(NULL,spacing->size);
	Minimum35    = floatVectorInit(NULL,spacing->size);	
	Minimum37    = floatVectorInit(NULL,spacing->size);
	Minimum53    = floatVectorInit(NULL,spacing->size);
	Minimum55    = floatVectorInit(NULL,spacing->size);
	Minimum57    = floatVectorInit(NULL,spacing->size);
	Minimum73    = floatVectorInit(NULL,spacing->size);
	Minimum75    = floatVectorInit(NULL,spacing->size);
	Minimum77    = floatVectorInit(NULL,spacing->size);

	Maximum      = floatVectorInit(NULL,spacing->size);
	Maximum33    = floatVectorInit(NULL,spacing->size);
	Maximum35    = floatVectorInit(NULL,spacing->size);	
	Maximum37    = floatVectorInit(NULL,spacing->size);
	Maximum53    = floatVectorInit(NULL,spacing->size);
	Maximum55    = floatVectorInit(NULL,spacing->size);
	Maximum57    = floatVectorInit(NULL,spacing->size);
	Maximum73    = floatVectorInit(NULL,spacing->size);
	Maximum75    = floatVectorInit(NULL,spacing->size);
	Maximum77    = floatVectorInit(NULL,spacing->size);
	
	if(1 == mode){ /*Noise Estimation*/
		TangentLine(spacing, scatter, belowCoefficient, aboveCoefficient, ini, linfo,-1);
		for(i=(0+Differentialaround); i<(spacing->size-Differentialaround); i++){
			Noise->data[i] = belowCoefficient[linfo->degree][0];
			for(j=1 ; j<=linfo->degree ; j++){
				Noise->data[i] += belowCoefficient[linfo->degree][j]*__power(spacing->data[i],j);
			}
			scatter->data[i] = scatter->data[i] - pow(10,Noise->data[i]);
		}
		mode = 0;
	}

	
	__Smoothing(scatter,MedianCurve3,1,1);
	__Smoothing(scatter,MedianCurve5,2,1);
	__Smoothing(scatter,MedianCurve7,3,1);

	__MinimumByMinSquare(spacing,MedianCurve3,Minimum33,1);
	__MinimumByMinSquare(spacing,MedianCurve3,Minimum35,2);
	__MinimumByMinSquare(spacing,MedianCurve3,Minimum37,3);
	__MinimumByMinSquare(spacing,MedianCurve5,Minimum53,1);
	__MinimumByMinSquare(spacing,MedianCurve5,Minimum55,2);
	__MinimumByMinSquare(spacing,MedianCurve5,Minimum57,3);
	__MinimumByMinSquare(spacing,MedianCurve7,Minimum73,1);
	__MinimumByMinSquare(spacing,MedianCurve7,Minimum75,2);
	__MinimumByMinSquare(spacing,MedianCurve7,Minimum77,3);

	__MaximumByMinSquare(spacing,MedianCurve3,Maximum33,1);
	__MaximumByMinSquare(spacing,MedianCurve3,Maximum35,2);
	__MaximumByMinSquare(spacing,MedianCurve3,Maximum37,3);
	__MaximumByMinSquare(spacing,MedianCurve5,Maximum53,1);
	__MaximumByMinSquare(spacing,MedianCurve5,Maximum55,2);
	__MaximumByMinSquare(spacing,MedianCurve5,Maximum57,3);
	__MaximumByMinSquare(spacing,MedianCurve7,Maximum73,1);
	__MaximumByMinSquare(spacing,MedianCurve7,Maximum75,2);
	__MaximumByMinSquare(spacing,MedianCurve7,Maximum77,3);
	
	__MinSquare(spacing,MedianCurve5,MinSquare,2);

	for(tmp.ratioOfAmpToPhase = 0.05 ; tmp.ratioOfAmpToPhase <= 1.00 ; tmp.ratioOfAmpToPhase += 0.01){
		for(tmp.defocus = 0.0; tmp.defocus<2*ini->defocus; tmp.defocus+=ini->defocus/1000.0) {
			ctfMax = sqrt(SQR(ctfFunction(&tmp, spacing->data[0],mode)));
			defocus->data[l] = tmp.defocus;
			for(i=0;i<spacing->size;i++){
				ctf->data[i] = ctfFunction(&tmp, spacing->data[i],mode);
				if(ctfMax < sqrt(SQR(ctfFunction(&tmp, spacing->data[i],mode)))){
					ctfMax = sqrt(SQR(ctfFunction(&tmp, spacing->data[i],mode)));
				}
			}
			for(i=0;i<spacing->size;i++){
				ctf->data[i] /= ctfMax;
			}
			DEBUGPRINT1("%f\n", ctf->data[1]);
			E = 0.0;
			ThonRingSize = 0;
			for(i=(0+Differentialaround); i<(spacing->size-Differentialaround); i++) {
				ThonRing->data[i] = 0;
				if(tmp.CutLow < spacing->data[i] && spacing->data[i] < tmp.CutHigh ) {				
					/*DifferentialMethod*/
					if(__SquareLimitValue(ctf,i,Differentialaround) == -1){
						ThonRing->data[i] = 1;
						ThonRingSize += 1;
					}
				}
			
            }
			j = 0;
			k = 0;
			for(i=(0+Differentialaround); i<(spacing->size-Differentialaround); i++) {
				
				E += 2*Minimum33->data[i]*(0.5-SQR(ctf->data[i]))+2*Minimum35->data[i]*(0.5-SQR(ctf->data[i]))+2*Minimum37->data[i]*(0.5-SQR(ctf->data[i]))+
				     2*Minimum53->data[i]*(0.5-SQR(ctf->data[i]))+2*Minimum55->data[i]*(0.5-SQR(ctf->data[i]))+2*Minimum57->data[i]*(0.5-SQR(ctf->data[i]))+
				     2*Minimum73->data[i]*(0.5-SQR(ctf->data[i]))+2*Minimum75->data[i]*(0.5-SQR(ctf->data[i]))+2*Minimum77->data[i]*(0.5-SQR(ctf->data[i])); 
	
				E += 2*Maximum33->data[i]*(-0.5+SQR(ctf->data[i]))+2*Maximum35->data[i]*(-0.5+SQR(ctf->data[i]))+2*Maximum37->data[i]*(-0.5+SQR(ctf->data[i]))+
				     2*Maximum53->data[i]*(-0.5+SQR(ctf->data[i]))+2*Maximum55->data[i]*(-0.5+SQR(ctf->data[i]))+2*Maximum57->data[i]*(-0.5+SQR(ctf->data[i]))+
				     2*Maximum73->data[i]*(-0.5+SQR(ctf->data[i]))+2*Maximum75->data[i]*(-0.5+SQR(ctf->data[i]))+2*Maximum77->data[i]*(-0.5+SQR(ctf->data[i])); 
			
			}
			E = E/9;
			if(MmaxE<=E && ThonRingSize >= E/*&& k == j*/){
				//fprintf(stdout, "MMAX: %6.0f %f %f %f\n", tmp.defocus,tmp.ratioOfAmpToPhase,E,MmaxE);
				MmaxE = E;
				res->defocus = tmp.defocus;
				res->ratioOfAmpToPhase = tmp.ratioOfAmpToPhase;
				*MaxThonRing = ThonRingSize;
			}
			
			if(ThonRingSize <= E){
				E = 0;
			}
			//Eres->data[l] = E;
   	    	//fprintf(stdout, "%6f %3ld %f\n", defocus->data[l],ThonRingSize,Eres->data[l]);
			//l++;
			//fprintf(stdout, "Acomp:%6f defocus:%f E:%f ctfMax:%f\n", tmp.ratioOfAmpToPhase,tmp.defocus,E,ctfMax);
			/*3D*//*if( (10000 <= tmp.defocus) && (tmp.defocus <= 20000)){
				fprintf(stdout,"%f ",E); 
			}*/
		}
		fprintf(stdout,"Acomp %f %f %f\n", tmp.ratioOfAmpToPhase,res->defocus,MmaxE);
		/*fprintf(stdout,"\n");*//*3D*/
		MmaxE = 0.0;
	}
	fprintf(stdout,"defocus:%f Acomp:%f\n",res->defocus,res->ratioOfAmpToPhase);
	/*for smooth test*/
	/*Minimum = Minimum77;
	for(i=0;i<spacing->size;i++){
		ctf->data[i]  = ctfFunction(res, spacing->data[i],mode);
		ctfSQR->data[i] = SQR(ctf->data[i]);
	}
	__MinimumByMinSquare(spacing,ctfSQR,ThonRing,1);

	__MinSquare(spacing,ctfSQR,ctfMinSquare,1);
	fprintf(stdout,"    spacing:    SQR(ctf):     scatter:     Median:   | Minimum(33,35,37,53,55,57,73,75,77):\n");
	for(i=0;i<spacing->size;i++){
		
		if(tmp.CutLow < spacing->data[i]
		&&spacing->data[i] < tmp.CutHigh ) {
			fprintf(stdout,"%10.6e %10.6e %10.6e %10.6e | %4.2f %4.2f %4.2f | %4.2f %4.2f %4.2f | %4.2f %4.2f %4.2f || %4.2f %4.2f %4.2f | %4.2f %4.2f %4.2f | %4.2f %4.2f %4.2f "\
					,spacing->data[i],SQR(ctf->data[i]),scatter->data[i],MedianCurve5->data[i],Minimum33->data[i],Minimum35->data[i],Minimum37->data[i],Minimum53->data[i],Minimum55->data[i],Minimum57->data[i],Minimum73->data[i],Minimum75->data[i],Minimum77->data[i],Maximum33->data[i],Maximum35->data[i],Maximum37->data[i],Maximum53->data[i],Maximum55->data[i],Maximum57->data[i],Maximum73->data[i],Maximum75->data[i],Maximum77->data[i]);
			if(__SquareLimitValue(ctf,i,Differentialaround) == -1){
				fprintf(stdout,"Ring\n");
			}
			else{
				fprintf(stdout,"\n");
			}
		}
	}*/

}



/*ctfDeterminationbyCovarianceMethod*/

static float __Covariance(floatVector* function,floatVector* MedianCurve,long i,long around){
	
	long j;
	float tmp;
	
	tmp = 0.0;
	for(j=(i-around);j<=(i+around);j++){
		tmp += SQR(MedianCurve->data[j] - function->data[j]);
	}

	return(tmp);
}


void __CovarianceEstimation(floatVector* function,floatVector* MedianCurve,floatVector* Covariance,long around){
	
	long i;
	long aroundtmp;
	
	aroundtmp = around;
	
	for(i=0;i<function->size;i++){
		aroundtmp = around;
		if(i!=0 && i!=function->size-1){
			if(i<around){
				aroundtmp = i;
			}
			else if(i>function->size-1-around){
				aroundtmp = function->size-1-i;
			}

			Covariance->data[i]  = __Covariance(function,MedianCurve,i,aroundtmp);
			
		}
			
		else{
			Covariance->data[i] = 0.0;
		}
	}
	
}


void
lctfDeterminationbyCovarianceMethods(ctfInfo* res, mrcImage* mrc, ctfInfo* ini,long* MaxThonRing, long mode)
{
	floatVector* scatter;
	floatVector* spacing;
	floatVector* ctf;
	floatVector* MedianCurve;
	floatVector* Covariance;
	long         i;
	long         Differentialaround;
	long         Smootharound;
	long         CovarianceAround;
	long         ThonRing;
	float        E;
	float        minE = 0.0;
	ctfInfo      tmp;
	
	Differentialaround = 1;
	Smootharound       = 2;
	CovarianceAround   = 2;
	
	scatter = lmrcFSInfoScatteringAngularDistributionAverage(mrc);
	spacing = lmrcFSInfoSpacing(mrc);
	DEBUGPRINT2("%f %f\n", scatter->data[1], spacing->data[1]);
	ctf     = floatVectorInit(NULL, spacing->size);
	tmp     = *ini;
	*res    = *ini;
	
	MedianCurve = floatVectorInit(NULL,spacing->size);
	Covariance  = floatVectorInit(NULL,spacing->size);
	
	fprintf(stdout,"\nCovarianceMethod\n");
	if(*MaxThonRing == -1){
		fprintf(stdout,"all ThonRing search\n");
	}
	else{
		fprintf(stdout,"only ThonRing = %3ld\n",*MaxThonRing);
	}
	
	for(tmp.defocus = 0.0; tmp.defocus<2*ini->defocus; tmp.defocus+=ini->defocus/1000.0) {
		for(i=0;i<spacing->size;i++){
			ctf->data[i] = ctfFunction(&tmp, spacing->data[i],mode);
		}
		__Smoothing(scatter,MedianCurve,Smootharound,1);
		__CovarianceEstimation(scatter,MedianCurve,Covariance,CovarianceAround);
		DEBUGPRINT1("%f\n", ctf->data[1]);
		E= 0.0;
		ThonRing = 0;
		for(i=(0+Differentialaround); i<(spacing->size-Differentialaround); i++) {
			if(tmp.CutLow < spacing->data[i]
			&&spacing->data[i] < tmp.CutHigh ) {
				if(__SquareLimitValue(ctf,i,Differentialaround) == -1){
					ThonRing += 1;
					if(ThonRing <= 3){
						E += log10(Covariance->data[i] + 1.0);
					}
				}
                	}
            	}

		if(ThonRing != 0){
			//E = E/(float)ThonRing;
			if((minE > E || minE == 0.0) && (*MaxThonRing == ThonRing || *MaxThonRing == -1) ){
				fprintf(stdout, "minE: %10.6e  %10.6e %10.6e\n", tmp.defocus,E,minE);
				minE = E;
				res->defocus         = tmp.defocus;
			}
		}
        	fprintf(stdout, "%10.6e %3ld  %10.6e \n", tmp.defocus,ThonRing, E);
	}
	fprintf(stdout,"defocus= %10.6f\n",res->defocus);
	
	/*for smooth test*/
	for(i=0;i<spacing->size;i++){
		ctf->data[i]  = ctfFunction(res, spacing->data[i],mode);
	}
	fprintf(stdout,"\n\ndefocus:%f\n",res->defocus);
	fprintf(stdout,"    spacing:    SQR(ctf):     scatter:      Median:  Estimation:\n");
	for(i=0;i<spacing->size;i++){
		
		if(tmp.CutLow < spacing->data[i]
		&&spacing->data[i] < tmp.CutHigh ) {
			fprintf(stdout," %10.6e %10.6e %10.6e %10.6e %10.6e ",spacing->data[i],SQR(ctf->data[i]),scatter->data[i],MedianCurve->data[i],Covariance->data[i]);
			if(__SquareLimitValue(ctf,i,Differentialaround) == -1){
				fprintf(stdout,"ring\n");
			}
			else{
				fprintf(stdout,"\n");
			}
		}
	}

}


void
lctfDeterminationbyMixMethods(ctfInfo* res, mrcImage* mrc, ctfInfo* ini,long* ThonRing, long mode){
	
	fprintf(stdout,"\nDifferential & Covariance Method");
	lctfDeterminationbyDifferentialMethods(res, mrc, ini,ThonRing, mode);
	
	lctfDeterminationbyCovarianceMethods(res,mrc,ini,ThonRing,mode);	
}

double 
lctfDeterminationByTangent(ctfInfo* res, mrcImage* mrc, ctfInfo* ini, lctfDetermineInfo* linfo,floatVector* defocus, floatVector* Eres, long mode){
	
	floatVector*	scatter;
	floatVector*	spacing;
	floatVector*	ctf;
	floatVector*    belowTangent;
	floatVector*    aboveTangent;
	floatVector*    PSwithoutNoise;
	floatVector*    envelope;
	long		i,j,k;
	long        l = 0;
	float       E;
	float       Emax = 0;
	float       Emix = 0;
	float       defocusByTangent;
	float       defocusByMix;
	float       defocusByMinSq;
	float       sumPSwithoutNoise;
	float       sumCTFwithEnvelope;
	float**     aboveCoefficient;
	float**     belowCoefficient;
	ctfInfo		tmp;
	
	belowCoefficient = MemoryAllocate(float*, linfo->degree+1, "in lctfDeterminationByTangent");
	for(i=0 ; i<linfo->degree+1  ; i++){
		belowCoefficient[i] = MemoryAllocate(float, i+1, "in lctfDeterminationByTangent");
	}
	aboveCoefficient = MemoryAllocate(float*, linfo->degree+1, "in lctfDeterminationByTangent");
	for(i=0 ; i<linfo->degree+1 ; i++){
		aboveCoefficient[i] = MemoryAllocate(float, i+1, "in lctfDeterminationByTangent");
	}
	//linfo->noise = MemoryAllocate(float, linfo->degree+1, "in lctfDeterminationByTangent");
	for(i=0 ; i<linfo->degree+1 ; i++){
		for(j=0 ; j<i+1 ; j++){
			belowCoefficient[i][j] = 0.0;
			aboveCoefficient[i][j] = 0.0;
		}
	}
	
	scatter = lmrcFSInfoScatteringAngularDistributionAverage(mrc);
	spacing = lmrcFSInfoSpacing(mrc);
	DEBUGPRINT2("%f %f\n",scatter->data[1],spacing->data[1]);
	belowTangent   = floatVectorInit(NULL,spacing->size);
	aboveTangent   = floatVectorInit(NULL,spacing->size);
	PSwithoutNoise = floatVectorInit(NULL,spacing->size);
	envelope       = floatVectorInit(NULL,spacing->size);
	ctf            = floatVectorInit(NULL,spacing->size);
	tmp = *res;
	defocusByMinSq = res->defocus;
	TangentLine(spacing, scatter, belowCoefficient, aboveCoefficient, ini, linfo,0);
	
	//fprintf(stdout,"    spacing     scatter       below       above      Signal    Envelope\n");
	sumPSwithoutNoise = 0;
	for(i=0 ; i<spacing->size ; i++){
		if((ini->CutLow < spacing->data[i]) && (spacing->data[i] < ini->CutHigh)){
			belowTangent->data[i] = belowCoefficient[linfo->degree][0];
			aboveTangent->data[i] = aboveCoefficient[linfo->degree][0];
			for(k=1 ; k<=linfo->degree ; k++){
				belowTangent->data[i] += belowCoefficient[linfo->degree][k] * __power(spacing->data[i],k);
				aboveTangent->data[i] += aboveCoefficient[linfo->degree][k] * __power(spacing->data[i],k);
			}
			PSwithoutNoise->data[i] = scatter->data[i] - pow(10,belowTangent->data[i]);
			sumPSwithoutNoise += pow(PSwithoutNoise->data[i],2);
			envelope->data[i]       = pow(10,aboveTangent->data[i]) - pow(10,belowTangent->data[i]);
			//fprintf(stdout," %10.6f %11.6f %11.6f %11.6f %11.6f %11.6f\n",spacing->data[i],scatter->data[i],pow(10,belowTangent->data[i]),pow(10,aboveTangent->data[i]),PSwithoutNoise->data[i],envelope->data[i]);
		}
	}
	
	//fprintf(stdout,"\n defocus       Eminsq         Etan         Emix\n");
	for(tmp.defocus = 0.0 ; tmp.defocus < ini->defocus*2 ; tmp.defocus += ini->defocus/1000.0){
		E=0;
		sumCTFwithEnvelope = 0;
		for(i=0 ; i<spacing->size ; i++){
			if((ini->CutLow < spacing->data[i]) && (spacing->data[i] < ini->CutHigh)){
				ctf->data[i] = ctfFunction(&tmp, spacing->data[i],mode);
				sumCTFwithEnvelope += pow(pow(ctf->data[i],2) * envelope->data[i],2);
				E += PSwithoutNoise->data[i] * pow(ctf->data[i],2) * envelope->data[i];
				//fprintf(stdout," %f",pow(ctf->data[i],2)*envelope->data[i]);
			}
		}
		E = E / sqrt(sumCTFwithEnvelope * sumPSwithoutNoise);


		if(E >= Emax){
			Emax = E;
			defocusByTangent = tmp.defocus;
		}

		//fprintf(stdout,"  %6.0f %+11.5e %+11.5e",tmp.defocus,Eres->data[l],E);
		Eres->data[l] = Eres->data[l] * E;
		//fprintf(stdout," %+11.5e\n",Eres->data[l]);

		if(Eres->data[l] >= Emix){
			Emix = Eres->data[l];
			defocusByMix = tmp.defocus;
		}
		l++;
	}
	
	res->defocus = defocusByMix;
	linfo->IntensityMin = pow(10, belowCoefficient[0][0]);
	linfo->IntensityMax = pow(10, aboveCoefficient[0][0]);
	for(i=0 ; i<linfo->degree+1 ; i++){
		linfo->noise[i] = belowCoefficient[linfo->degree][i];
	}
	
	fprintf(stdout,"defocusByMinSq= %5.0f defocusByTangent= %5.0f ByMix= %5.0f\n",defocusByMinSq,defocusByTangent,defocusByMix);
	if( 1 == mode ){
		return defocusByMinSq;
	}
	if( 2 == mode ){
		return defocusByTangent;
	}
	else{
		return defocusByMix;
	}
}


void 
EnvelopeDetermine(ctfInfo* res, mrcImage* mrc, ctfInfo* ini, lctfDetermineInfo* linfo,floatVector* defocus, floatVector* Eres, long mode){
	
	floatVector*	scatter;
	floatVector*	spacing;
	floatVector*	ctf;
	floatVector*    belowTangent;
	floatVector*    aboveTangent;
	floatVector*    PSwithoutNoise;	
	floatVector*    envelope;
	
	floatVector*    Median;
	floatVector*    Maximum;
	floatVector*    SpacingMaxLocation;
	floatVector*    ScatterMaxLocation;
	int         MaxLocationSize = 0;
	long		i,j,k;
	long        l = 0;
	float       E;
	float       Emax = 0;
	float       Emix = 0;
	float       defocusByTangent;
	float       defocusByMix;
	float       defocusByMinSq;
	float       sumPSwithoutNoise;
	float       sumCTFwithEnvelope;
	float**     aboveCoefficient;
	float**     belowCoefficient;
	int         degreeBuf = 0;
	ctfInfo		tmp;
	
	belowCoefficient = MemoryAllocate(float*, linfo->degree+1, "in lctfDeterminationByTangent");
	for(i=0 ; i<linfo->degree+1  ; i++){
		belowCoefficient[i] = MemoryAllocate(float, i+1, "in lctfDeterminationByTangent");
	}
	aboveCoefficient = MemoryAllocate(float*, linfo->degree+1, "in lctfDeterminationByTangent");
	for(i=0 ; i<linfo->degree+1 ; i++){
		aboveCoefficient[i] = MemoryAllocate(float, i+1, "in lctfDeterminationByTangent");
	}
	//linfo->noise = MemoryAllocate(float, linfo->degree+1, "in lctfDeterminationByTangent");
	for(i=0 ; i<linfo->degree+1 ; i++){
		for(j=0 ; j<i+1 ; j++){
			belowCoefficient[i][j] = 0.0;
			aboveCoefficient[i][j] = 0.0;
		}
	}
	
	
	scatter = lmrcFSInfoScatteringAngularDistributionAverage(mrc);
	spacing = lmrcFSInfoSpacing(mrc);
	DEBUGPRINT2("%f %f\n",scatter->data[1],spacing->data[1]);
	belowTangent   = floatVectorInit(NULL,spacing->size);
	aboveTangent   = floatVectorInit(NULL,spacing->size);
	PSwithoutNoise = floatVectorInit(NULL,spacing->size);
	envelope       = floatVectorInit(NULL,spacing->size);
	ctf            = floatVectorInit(NULL,spacing->size);
	Median         = floatVectorInit(NULL,spacing->size);
	Maximum        = floatVectorInit(NULL,spacing->size);
	SpacingMaxLocation  = floatVectorInit(NULL,spacing->size);
	ScatterMaxLocation  = floatVectorInit(NULL,spacing->size);
	tmp = *res;
	defocusByMinSq = res->defocus;
	
	TangentLine(spacing, scatter, belowCoefficient, aboveCoefficient, ini, linfo,-1);
	degreeBuf = linfo->degree;
	
	linfo->degree = 0;//for IntensityMax
	TangentLine(spacing, scatter, belowCoefficient, aboveCoefficient, ini, linfo,1);//
	linfo->degree = degreeBuf;//
	
	linfo->IntensityMax = pow(10, aboveCoefficient[0][0]) * 1.5;
	sumPSwithoutNoise = 0;
	for(i=0; i<spacing->size; i++){
		belowTangent->data[i] = belowCoefficient[linfo->degree][0];
		for(j=1 ; j<=linfo->degree ; j++){
			belowTangent->data[i] += belowCoefficient[linfo->degree][j]*__power(spacing->data[i],j);
		}
		PSwithoutNoise->data[i] = scatter->data[i] - pow(10,belowTangent->data[i]);
		sumPSwithoutNoise += pow(PSwithoutNoise->data[i],2);
	}
	__Smoothing(PSwithoutNoise,Median,1,1);	
	__MaximumByMinSquare(spacing,Median,Maximum,1);

	for(i=0 ; i<spacing->size ; i++){
		if((ini->CutLow < spacing->data[i]) && (spacing->data[i] < ini->CutHigh)){
			if((1 == Maximum->data[i]) || (0 == MaxLocationSize)){
				SpacingMaxLocation->data[MaxLocationSize] = spacing->data[i];
				ScatterMaxLocation->data[MaxLocationSize] = PSwithoutNoise->data[i];
				MaxLocationSize++;
			}
		}
	}
	SpacingMaxLocation->size = MaxLocationSize;
	ScatterMaxLocation->size = MaxLocationSize;
/*	for(i = 0 ; i <= MaxLocationSize ; i++){
		fprintf(stdout,"%f %f\n",SpacingMaxLocation->data[i],ScatterMaxLocation->data[i]);
	}
*/
	TangentLine(SpacingMaxLocation, ScatterMaxLocation, belowCoefficient, aboveCoefficient, ini, linfo,1);

	//fprintf(stdout,"    spacing     scatter       below       above      Signal    Envelope\n");
	for(i=0 ; i<spacing->size ; i++){
		if((ini->CutLow < spacing->data[i]) && (spacing->data[i] < ini->CutHigh)){
			aboveTangent->data[i] = aboveCoefficient[linfo->degree][0];
			for(k=1 ; k<=linfo->degree ; k++){
				aboveTangent->data[i] += aboveCoefficient[linfo->degree][k] * __power(spacing->data[i],k);
			}
			envelope->data[i]       = pow(10,aboveTangent->data[i]);
			//fprintf(stdout," %10.6f %11.6f %11.6f %11.6f %11.6f %11.6f\n",spacing->data[i],scatter->data[i],pow(10,belowTangent->data[i]),pow(10,aboveTangent->data[i]),PSwithoutNoise->data[i],envelope->data[i]);
		}
	}
	
	//fprintf(stdout,"\n defocus       Eminsq         Etan         Emix\n");
	for(tmp.defocus = 0.0 ; tmp.defocus < ini->defocus*2 ; tmp.defocus += ini->defocus/1000.0){
		E=0;
		sumCTFwithEnvelope = 0;
		for(i=0 ; i<spacing->size ; i++){
			if((ini->CutLow < spacing->data[i]) && (spacing->data[i] < ini->CutHigh)){
				ctf->data[i] = ctfFunction(&tmp, spacing->data[i],mode);
				sumCTFwithEnvelope += pow(pow(ctf->data[i],2) * envelope->data[i],2);
				E += PSwithoutNoise->data[i] * pow(ctf->data[i],2) * envelope->data[i];
				//fprintf(stdout," %f",pow(ctf->data[i],2)*envelope->data[i]);
			}
		}
		E = E / sqrt(sumCTFwithEnvelope * sumPSwithoutNoise);


		if(E >= Emax){
			Emax = E;
			defocusByTangent = tmp.defocus;
		}

		//fprintf(stdout,"  %6.0f %+11.5e %+11.5e",tmp.defocus,Eres->data[l],E);
		Eres->data[l] = Eres->data[l] * E;
		//fprintf(stdout," %+11.5e\n",Eres->data[l]);

		if(Eres->data[l] >= Emix){
			Emix = Eres->data[l];
			defocusByMix = tmp.defocus;
		}
		l++;
	}
	
	res->defocus = defocusByMix;
	linfo->IntensityMin = pow(10, belowCoefficient[0][0])*0.5;
	//linfo->IntensityMax = pow(10, aboveCoefficient[0][0]);
	for(i=0 ; i<linfo->degree+1 ; i++){
		linfo->noise[i] = belowCoefficient[linfo->degree][i];
	}
	fprintf(stdout,"defocusByMinSq= %5.0f defocusByTangent= %5.0f ByMix= %5.0f\n",defocusByMinSq,defocusByTangent,defocusByMix);
}

