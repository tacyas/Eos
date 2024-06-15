/* # %M% %Y% %I% # The latest update : %G% at %U% #%Z% lmrcImageNormalizing ver %I% #%Z% Created by tacyas #%Z% #%Z% Usage : lmrcImageNormalizing #%Z% Attention #%Z% */
#include <stdlib.h>
#include <stdio.h>
static char __sccs_id[] = "%Z%lmrcImageNormalizing ver%I%; Date:%D% %Z%";

#define DEBUG
#include "genUtil.h"
#include "mrcImage.h"
#include "nr2.h"
#include "lmrcImageNormalizing.h"

void
__lmrcImageNormalizingfgauss(float x, float a[], float* y, float dyda[], int na)
{
	int i;
	float fac, ex, arg;

	*y = 0.0;

	for(i=1; i<=na-1; i+=3) {
		arg   = (x-a[i+1])/a[i+2];
		ex    = exp(-arg*arg);
		fac   = a[i]*ex*2.0*arg;
		*y   += a[i]*ex;
		dyda[i]   = ex;
		dyda[i+1] = fac/a[i+2];
		dyda[i+2] = fac*arg/a[i+2];
	}
}

void
lmrcImageNormalizingModePrint(FILE* fpt, int mode)
{
	fprintf(fpt, "----- Mode for lmrcImageNormalizing -----\n");
	fprintf(fpt, "%3d: Double Exponential: Solvent and Object\n", lmrcImageNormalizingModeDoubleExponential);
	fprintf(fpt, "         Fitting histgram to double exponentials as Solvent and Object  \n");
	fprintf(fpt, "		   data = A*(data-MeanOfSolvent)/(MeanOfObject-MeanOfSolvent) + B \n");
	fprintf(fpt, "%3d: Min-Max: Background and Object\n", lmrcImageNormalizingModeMinMax);
	fprintf(fpt, "		   data = A*(data-Min)/(Max-Min) + B \n");
	fprintf(fpt, "%3d: Contour\n", lmrcImageNormalizingModeUsingContour);
	fprintf(fpt, "		   data = A*(data-ContourMin)/(ContourMax-ContourMin) + B \n");
	fprintf(fpt, "%3d: Contour and Solvent\n", lmrcImageNormalizingModeUsingContourWithSolventFlattening);
	fprintf(fpt, "		   if data < ContourSolvent, data = ContourSolvent.  After this, calculate the below. \n");
	fprintf(fpt, "		   data = A*(data-ContourMin)/(ContourMax-ContourMin) + B \n");
	fprintf(fpt, "%3d: No Estimation\n", lmrcImageNormalizingModeNoEstimation);
	fprintf(fpt, "		   data = A*data + B \n");
	fprintf(fpt, "%3d: Assume the density as gaussion.\n", lmrcImageNormalizingModeAssumeGaussian);
	fprintf(fpt, "		   data = A*Normalized(data) + B , where normalized means (average=0, SD=1)\n");
	fprintf(fpt, "%3d: Min-75percent: Background and Object(75)\n", lmrcImageNormalizingModeMin75percent);
	fprintf(fpt, "		   data = A*(data-Min)/(75percent-Min)x0.75 + B \n");
	fprintf(fpt, "%3d: LowValueArea to HighValueArea: \n", lmrcImageNormalizingModeUsingLowValueAreaToHighValueArea);
	fprintf(fpt, "		   data = A*(data-MeanOfLowValueArea)/(meanOfHighValue-meanOfLowValueArea) + B, using LowValueArea and HighValueArea\n");
}

void 
lmrcImageNormalizing(mrcImage* out, mrcImage* in, lmrcImageNormalizingInfo* linfo, int mode)
{
	double data;
	mrcImageParaTypeReal x, y, z;

	double* hist;
	float* fhist;
	float* fdens;
	float* fsig;
	float* a;
	int* ia;
	float** covar;
	float** alpha;
	float chisq;
	float oldchisq;
	float alambda;

	unsigned long lhist;
	int nexp, ma;
	int i, iter;

	out->Header = in->Header;
	mrcInit(out, NULL);

	switch(linfo->Mode) {
		case lmrcImageNormalizingModeDoubleExponential: {
            fprintf(linfo->paramOut, "NormalizingMode: DoubleExp\n");
			lhist = 100;
			nexp  = 2;
			lmrcImageHistgram(&hist, lhist, in);
			fhist = vector(1, (int)lhist);
			fdens = vector(1, (int)lhist);
			fsig  = vector(1, (int)lhist);
			for(i=1; i<=lhist; i++) {
				fhist[i] = hist[i-1];
				fdens[i] = (in->HeaderAMax - in->HeaderAMin)/(lhist-1)*(i+0.5)+in->HeaderAMin;
				fsig[i]  = 1.0;
			}
			ma = nexp*3; 
			a     = vector(1, ma);
			ia    =ivector(1, ma);
			covar = matrix(1, ma, 1, ma);
			alpha = matrix(1, ma, 1, ma);
			for(i=1; i<=ma; i++) {
				ia[i] = 1;
			}
			/* Protein */	
			a[1] = 0.5; 											/* Ratio */
			a[2] = 0.75*in->HeaderAMax + 0.25*in->HeaderAMin;       /* Mean  */
			a[3] = 0.25*(in->HeaderAMax - in->HeaderAMin);          /* SD    */
			/* Solvent */
			a[4] = 0.5;                                             /* Ratio */
			a[5] = 0.25*in->HeaderAMax + 0.75*in->HeaderAMin;       /* Mean  */
			a[6] = 0.25*(in->HeaderAMax - in->HeaderAMin);          /* SD    */ 
			alambda = -1;
			iter = 0;
			oldchisq = 1e30;
			DEBUGPRINT6(" %15s  %15s  %15s  %15s  %15s  %15s\n", "pa", "pm", "ps", "sa", "sm", "ss");
			do {
				chisq = oldchisq;
				mrqmin(fdens, fhist, fsig, (int)lhist, a, ia, ma, covar, alpha, &chisq, __lmrcImageNormalizingfgauss, &alambda);
				DEBUGPRINT6(" %15s  %15s  %15s  %15s  %15s  %15s\n", "pa", "pm", "ps", "sa", "sm", "ss");
				DEBUGPRINT6(" %15.6e  %15.6e  %15.6e  %15.6e  %15.6e  %15.6e\n", a[1], a[2], a[3], a[4], a[5], a[6]);
				DEBUGPRINT6("+%15.6e +%15.6e +%15.6e +%15.6e +%15.6e +%15.6e\n", 
					sqrt(alpha[1][1]),sqrt(alpha[2][2]),sqrt(alpha[3][3]),
					sqrt(alpha[4][4]),sqrt(alpha[5][5]),sqrt(alpha[6][6]));
				DEBUGPRINT3(" %15d  %15.6e  %15.6e \n", iter, chisq, alambda);
				if(oldchisq-chisq<1e-6) {
					alambda*=10;
				}
				iter++;
			} while(iter<100 && alambda<1e6);
			for(x=0; x<in->HeaderN.x; x++) {
				for(y=0; y<in->HeaderN.y; y++) {
					for(z=0; z<in->HeaderN.z; z++) {
						mrcPixelDataGet(in, x, y, z, &data, mrcPixelRePart, mrcPixelHowNearest);
						/* 
							data = A*(data-MeanOfSolvent)/(MeanOfObject-MeanOfSolvent) + B
						*/
						data = linfo->A*(data - a[5])/(a[2] - a[5]) + linfo->B;
						mrcPixelDataSet(out, x, y, z, data, mrcPixelRePart);
					}
				}
			}
            fprintf(linfo->paramOut, "(min,max): %f %f\n", a[5], a[2]);
			break;
		}
		case lmrcImageNormalizingModeMinMax: {
            fprintf(linfo->paramOut, "NormalizingMode: MinMax\n");
			for(x=0; x<in->HeaderN.x; x++) {
				for(y=0; y<in->HeaderN.y; y++) {
					for(z=0; z<in->HeaderN.z; z++) {
						mrcPixelDataGet(in, x, y, z, &data, mrcPixelRePart, mrcPixelHowNearest);
						data = linfo->A*(data - in->HeaderAMin)/(in->HeaderAMax - in->HeaderAMax) + linfo->B;
						mrcPixelDataSet(out, x, y, z, data, mrcPixelRePart);
					}
				}
			}
            fprintf(linfo->paramOut, "(min,max): %f %f\n", in->HeaderAMin, in->HeaderAMax);
			break;
		}
		case lmrcImageNormalizingModeMin75percent: {
            fprintf(linfo->paramOut, "NormalizingMode: MinMax-A*0.75+B\n");
			for(x=0; x<in->HeaderN.x; x++) {
				for(y=0; y<in->HeaderN.y; y++) {
					for(z=0; z<in->HeaderN.z; z++) {
						mrcPixelDataGet(in, x, y, z, &data, mrcPixelRePart, mrcPixelHowNearest);
						data = linfo->A*(data - in->HeaderAMin)/(in->HeaderAMax - in->HeaderAMax)*0.75 + linfo->B;
						mrcPixelDataSet(out, x, y, z, data, mrcPixelRePart);
					}
				}
			}
            fprintf(linfo->paramOut, "(min,max): %f %f\n", in->HeaderAMin, in->HeaderAMax);
			break;
		}
		case lmrcImageNormalizingModeUsingContour: {
            fprintf(linfo->paramOut, "NormalizingMode: ContourMinMax\n");
			for(x=0; x<in->HeaderN.x; x++) {
				for(y=0; y<in->HeaderN.y; y++) {
					for(z=0; z<in->HeaderN.z; z++) {
						mrcPixelDataGet(in, x, y, z, &data, mrcPixelRePart, mrcPixelHowNearest);
						data = linfo->A*(data - linfo->ContourMin)/(linfo->ContourMax - linfo->ContourMin) + linfo->B;
						mrcPixelDataSet(out, x, y, z, data, mrcPixelRePart);
					}
				}
			}
            fprintf(linfo->paramOut, "(min,max): %f %f\n", linfo->ContourMin, linfo->ContourMax);
			break;
		}
		case lmrcImageNormalizingModeUsingContourWithSolventFlattening: {
            fprintf(linfo->paramOut, "NormalizingMode: ContourMinMaxWithSoventFlattenng\n");
			for(x=0; x<in->HeaderN.x; x++) {
				for(y=0; y<in->HeaderN.y; y++) {
					for(z=0; z<in->HeaderN.z; z++) {
						mrcPixelDataGet(in, x, y, z, &data, mrcPixelRePart, mrcPixelHowNearest);
						if(data<linfo->ContourSolvent) {
							data = linfo->ContourSolvent;
						}
						data = linfo->A*(data - linfo->ContourMin)/(linfo->ContourMax - linfo->ContourMin) + linfo->B;
						mrcPixelDataSet(out, x, y, z, data, mrcPixelRePart);
					}
				}
			}
            fprintf(linfo->paramOut, "(min,max): %f %f\n", linfo->ContourMin, linfo->ContourMax);
            fprintf(linfo->paramOut, "Solavent:  %f\n", linfo->ContourSolvent);
			break;
		}
		case lmrcImageNormalizingModeNoEstimation: {
            fprintf(linfo->paramOut, "NormalizingMode: A*data+B\n");
			for(x=0; x<in->HeaderN.x; x++) {
				for(y=0; y<in->HeaderN.y; y++) {
					for(z=0; z<in->HeaderN.z; z++) {
						mrcPixelDataGet(in, x, y, z, &data, mrcPixelRePart, mrcPixelHowNearest);
						data = linfo->A*data + linfo->B;
						mrcPixelDataSet(out, x, y, z, data, mrcPixelRePart);
					}
				}
			}
			break;
		}
		case lmrcImageNormalizingModeAssumeGaussian: {
            fprintf(linfo->paramOut, "NormalizingMode: AssumeGaussian\n");
			mrcImageInformation imageInfo;
			imageInfo.mode = meanOfAll;
			lmrcImageInformation(&imageInfo, in);
			for(x=0; x<in->HeaderN.x; x++) {
				for(y=0; y<in->HeaderN.y; y++) {
					for(z=0; z<in->HeaderN.z; z++) {
						mrcPixelDataGet(in, x, y, z, &data, mrcPixelRePart, mrcPixelHowNearest);
						data = linfo->A*((data-imageInfo.mean)/imageInfo.sd) + linfo->B;
						mrcPixelDataSet(out, x, y, z, data, mrcPixelRePart);
					}
				}
			}
            fprintf(linfo->paramOut, "(mean,sd): %f %f\n", imageInfo.mean, imageInfo.sd);
			break;
		}
		case lmrcImageNormalizingModeUsingLowValueAreaToHighValueArea: {
            fprintf(linfo->paramOut, "NormalizingMode: LowValueAreaToHighValueArea\n");
			mrcImageInformation imageInfo;
			imageInfo.mode = meanOfLowValueAreaAndHighValueArea;
            imageInfo.thresHigh = linfo->thresOfHighValueArea;
            imageInfo.thresLow  = linfo->thresOfLowValueArea;
			lmrcImageInformation(&imageInfo, in);
            DEBUGPRINT2("LowArea %f HighArea %f\n", imageInfo.meanOfLowValueArea, imageInfo.meanOfHighValueArea); 
			for(x=0; x<in->HeaderN.x; x++) {
				for(y=0; y<in->HeaderN.y; y++) {
					for(z=0; z<in->HeaderN.z; z++) {
						mrcPixelDataGet(in, x, y, z, &data, mrcPixelRePart, mrcPixelHowNearest);
						data = linfo->A*(data-imageInfo.meanOfLowValueArea)/(imageInfo.meanOfHighValueArea - imageInfo.meanOfLowValueArea) + linfo->B;
						mrcPixelDataSet(out, x, y, z, data, mrcPixelRePart);
					}
				}
			}
            fprintf(linfo->paramOut, "thresRate(min,max):  %f %f\n", imageInfo.thresLow, imageInfo.thresHigh);
            fprintf(linfo->paramOut, "thresValue(min,max): %f %f\n", imageInfo.thresOfLowValueArea, imageInfo.thresOfHighValueArea);
            fprintf(linfo->paramOut, "value(min,max):      %f %f\n", imageInfo.meanOfLowValueArea, imageInfo.meanOfHighValueArea);
			break;
		}
		default: {
			fprintf(stderr, "Not supported Mode: %d\n", linfo->Mode);
			exit(EXIT_FAILURE);
			break;
		}
	}
    fprintf(linfo->paramOut, "(A,B):  %f %f\n", linfo->A, linfo->B);
}
