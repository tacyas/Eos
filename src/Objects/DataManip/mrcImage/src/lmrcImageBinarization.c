/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% lmrcImageBinarization ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : mrcImageBinarization
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%lmrcImageBinarization ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  

#undef DEBUG
#include "genUtil.h"
#include "Memory.h"
#include "../inc/mrcImage.h"
#include "lmrcImageBinarization.h"

float
lmrcImageBinarization(mrcImage* out, mrcImage*  in, lmrcImageBinarizationInfo linfo, int mode)
{
	double thres;

	DEBUGPRINT1("mode in lmrcImageBinarization: %d\n", mode&0xf0)
	switch(mode&0xf0) {
		case 16: {
			linfo.thresHold = lmrcImageDeterminationOfThresholdForBinarizationByKittlerMethod(in, linfo.nLevel, mode);
			break;
		}
		case 32: {
			linfo.thresHold = lmrcImageDeterminationOfThresholdForBinarizationByOhtsuMethod(in, linfo.nLevel, mode);
			break;
		}
		case 48: {
			DEBUGPRINT("48: in lmrcImageBinarization\n");
			linfo.thresHold = lmrcImageDeterminationOfThresholdForBinarizationByptileMethod(in, linfo.nLevel, linfo.p, mode&0x0f);
			break;
		}
		case 64: {
		    linfo.thresHold = lmrcImageDeterminationOfThresholdForBinarizationByDifferentialHistogramMethod(in, linfo.nLevel, mode);
            break;
        }
		case 80: {
            linfo.thresHold = lmrcImageDeterminationOfThresholdForBinarizationByLaplacianHistogramMethod(in, linfo.nLevel, mode);
            break;
        }
		case 0: {
			break;
		}
		default: {
			fprintf(stderr, "Not supported mode %d, so the fixed threshold was used  \n", mode&0xf0);
			break;
		}
	}

	if(linfo.flagDeltaThreshold) {
		linfo.thresHold += linfo.deltaThreshold;
	}
	lmrcImageBinarization0(out, in, linfo, mode&0x0f); 

	return linfo.thresHold;
}

void 
lmrcImageBinarization0(mrcImage* out, mrcImage* in, lmrcImageBinarizationInfo linfo, int mode)
{
	/* variables */
  	mrcImageParaTypeReal x,y,z;
	int n;
	int flagNear = 0;
  	mrcImageParaTypeReal x0,y0,z0;
  	double data;
	double data0;

	double t; /* thresHold */
	double v; /* value */
	
	out->Header = in->Header;
	mrcInit(out, NULL);
	if(0 < in->numTailer) {
		mrcTailerCopy(out, in, 1);
	}
	DEBUGPRINT1("Binarization0 mode %d\n", mode);
  	t = linfo.thresHold;
  	v = linfo.value;
  	n=0;
	for(z=0 ;z < in->HeaderN.z ;z++) {
  	for(y=0 ;y < in->HeaderN.y ;y++) {
  	for(x=0 ;x < in->HeaderN.x ;x++) {
  		mrcPixelDataGet(in, x, y, z, &data, mrcPixelRePart,mrcPixelHowNearest);
		flagNear = 0;
		//DEBUGPRINT6("(%f,%f,%f): %f %d %d\n", x, y, z, data, linfo.flagNear, flagNear);
		if(linfo.flagNear) {
			DEBUGPRINT1("in linfo.flagNear %f\n", linfo.near);
			for(x0=MAX(0,x-linfo.near); x0<=MIN(x+linfo.near,in->HeaderN.x-1); x0++) {	
			for(y0=MAX(0,y-linfo.near); y0<=MIN(y+linfo.near,in->HeaderN.y-1); y0++) {	
			for(z0=MAX(0,z-linfo.near); z0<=MIN(z+linfo.near,in->HeaderN.z-1); z0++) {	
				if(SQR(x-x0)+SQR(y-y0)+SQR(z-z0)<=SQR(linfo.near)) {
  					mrcPixelDataGet(in, x0, y0, z0, &data0, mrcPixelRePart,mrcPixelHowNearest);
					DEBUGPRINT4("All(%f,%f,%f), %g\n", x0,y0,z0, data0);
					switch(mode) {
						case 0:
						case 2: {
							if(t<=data0) { /* Near */
								flagNear = 1;
  								mrcPixelDataGet(in, x0, y0, z0, &data0, mrcPixelRePart,mrcPixelHowNearest);
							}
							break;
						}
						case 1:
						case 3: {
							if(data0<t) { /* Near */
								flagNear = 1;
							}
							break;
						}
						case 4: 
						case 6: {
							if(t - linfo.sigmaThreshold <= data0  && data0 <= t + linfo.sigmaThreshold ) { /* Near */
								flagNear = 1;
							}
							break;
						}
						case 5: 
						case 7: {
							if(data0 < t - linfo.sigmaThreshold || t + linfo.sigmaThreshold < data0 ) { /* Near */
								flagNear = 1;
							}
							break;
						}
						default: {
							fprintf(stderr, "Not supported mode in lmrcImageBinarization : %d", mode);
							break;
						}
					}
				}
				if(0<flagNear) {
					break;
				}
			}
				if(0<flagNear) {
					break;
				}
			}
				if(0<flagNear) {
					break;
				}
			}
		}	
		switch(mode) {
       		case 0: {
	 			if(data < t) {
					if(0<linfo.flagNear && 0<flagNear) {
						data = 1;
					} else {
						data = 0;
					}
					//DEBUGPRINT6("(%f,%f,%f): %f %d %d\n", x, y, z, data, linfo.flagNear, flagNear);
	 			} else {
	  			 	data = 1;
	   				n++;
	 			}
	 			break;
			}
      		case 1: {
	 			if(data > t){
					if(0<linfo.flagNear && 0<flagNear) {
						data = 1;
					} else {
						data = 0;
					}
	 			} else {
	   				data = 1;
	   				n++;
	 			}	 
	 			break;
			}
       		case 2: {
	 			if(data < t){
					if(0<linfo.flagNear && 0<flagNear) {
						data = data;
					} else {
	   					data = v;
					}
	 			} else {
					data = data;
	   				n++;
	 			}
	 			break;
			}
       		case 3: {
	 			if(data > t) {
					if(0<linfo.flagNear && 0<flagNear) {
						data = data;
					} else {
	   					data = v;
					}
	 			} else {
					data = data;
	   				n++;
	 			}
				break;
			}
      		case 4: {
	 			if(data < t - linfo.sigmaThreshold || t + linfo.sigmaThreshold < data){
					if(0<linfo.flagNear && 0<flagNear) {
						data = 1;
					} else {
						data = 0;
					}
	 			} else {
	   				data = 1;
	   				n++;
	 			}	 
	 			break;
			}
      		case 5: {
	 			if(t - linfo.sigmaThreshold <= data && data <= t + linfo.sigmaThreshold){
					if(0<linfo.flagNear && 0<flagNear) {
						data = 1;
					} else {
						data = 0;
					}
	 			} else {
	   				data = 1;
	   				n++;
	 			}	 
	 			break;
			}
      		case 6: {
	 			if(data < t - linfo.sigmaThreshold || t + linfo.sigmaThreshold < data){
					if(0<linfo.flagNear && 0<flagNear) {
						data = data;
					} else {
						data = v;
					}
	 			} else {
	   				data = data;
	   				n++;
	 			}	 
	 			break;
			}
      		case 7: {
	 			if(t - linfo.sigmaThreshold <= data && data <= t + linfo.sigmaThreshold){
					if(0<linfo.flagNear && 0<flagNear) {
						data = data;
					} else {
						data = v;
					}
	 			} else {
	   				data = data;
	   				n++;
	 			}	 
	 			break;
			}
			default: {
				fprintf(stderr, "Not supported mode in lmrcImageBinarization : %d", mode);
				break;
			}
      	} 
       	mrcPixelDataSet(out, x, y, z, data, mrcPixelRePart);
		flagNear = 0;
    }
   	}
	}
  	mrcStatDataSet(out, 0);
  	//fprintf(stdout ,"N= %d\n",n);
}    

void
lmrcImageBinarizationUsage(FILE* fpt)
{
	fprintf(fpt, "----- Additional Usage -----\n");
	fprintf(fpt, "mode 0: Under thresHold, 0.     Above thresHold, 1.\n");
	fprintf(fpt, "     1: Above thresHold, 0.     Under thresHold, 1.\n");
	fprintf(fpt, "     2: Under thresHold, value. Above thresHold, unchanged.\n");
	fprintf(fpt, "     3: Above thresHold, value. Under thresHold, unchanged.\n");
	fprintf(fpt, "     4: thresHold +- sigma, 1.     Others 0.\n");
	fprintf(fpt, "     5: thresHold +- sigma, 0.     Others 1.\n");
	fprintf(fpt, "     6: thresHold +- sigma, unchanged. Others value.\n");
	fprintf(fpt, "     7: thresHold +- sigma, value.     Others unchanged.\n");
	fprintf(fpt, "     +16: Automatically Determine threshold by Kittler Method\n");
	fprintf(fpt, "     +32: Automatically Determine threshold by Ohtsu Method\n");
	fprintf(fpt, "     +48: Automatically Determine threshold by p-tile Method\n");
	fprintf(fpt, "          p range: 0.0 - 1.0\n"); 
	fprintf(fpt, "     +64: Automatically Determine threshold by Differential-Histogram Method\n");
	fprintf(fpt, "     +80: Automatically Determine threshold by Laplacian-Histogram Method\n");
}

double
lmrcImageDeterminationOfThresholdForBinarizationByKittlerMethod(mrcImage* mrc, int L, int mode)
{
	double  Emin; 
	double  E;
	int     kmin;
	double* hist ;
	int index;
	mrcImageInformation linfo;
	float x, y, z;
	double data;
	int k;
	double omega0, omega1;
	double sigma0, sigma1;
	double mean0, mean1;
	int    count0, count1;
	int N;

	linfo.mode = meanOfAll;
	lmrcImageInformation(&linfo, mrc);
	hist = (double*)memoryAllocate(sizeof(double)*L, "in lmrcImageDetermination");

	N=mrc->HeaderN.x*mrc->HeaderN.y*mrc->HeaderN.z;

	for(index=0; index<L; index++) { 
		hist[index] = (linfo.max-linfo.min)*((double)index)/(double)L+linfo.min; 
		DEBUGPRINT2("hist %4d %15.6g\n", index, hist[index]);
	}

	Emin = 1e30; 
	DEBUGPRINT1("start E: %15.6g\n", Emin)
	kmin = 0;
	for(k=1; k<L; k++) {
		omega0 = omega1 = 0;
		mean0  = mean1  = 0;
		count0 = count1 = 0;
		for(z=0; z<mrc->HeaderN.z; z++) {
		for(y=0; y<mrc->HeaderN.y; y++) {
		for(x=0; x<mrc->HeaderN.x; x++) {
			mrcPixelDataGet(mrc, x, y, z, &data, mrcPixelRePart, mrcPixelHowNearest);
			if(data<hist[k]) {
				omega0++;
				mean0 += data;
				count0++;	
			} else {
				omega1++;
				mean1 += data;
				count1++;
			}
		}
		}
		}
		omega0 /= N;
		omega1 /= N;
		mean0  /= count0;
		mean1  /= count1;
	
		sigma0 = sigma1 = 0;
		for(z=0; z<mrc->HeaderN.z; z++) {
		for(y=0; y<mrc->HeaderN.y; y++) {
		for(x=0; x<mrc->HeaderN.x; x++) {
			mrcPixelDataGet(mrc, x, y, z, &data, mrcPixelRePart, mrcPixelHowNearest);
			if(data<hist[k]) {
				sigma0 += SQR(data-mean0); 
			} else {
				sigma1 += SQR(data-mean1); 
			}
		}
		}
		}

		sigma0=sqrt(sigma0/count0);
		sigma1=sqrt(sigma1/count1);
		E = omega0*log10(sigma0/omega0) + omega1*log10(sigma1/omega1); 
		DEBUGPRINT5("count below %6d above %6d hist %15.6g mean %15.6g %15.6g\n", count0, count1, hist[k], mean0, mean1);
		DEBUGPRINT6("E: k %4d E %15.6g below %15.6g %15.6g above %15.6g %15.6g\n", k, E, omega0, sigma0, omega1, sigma1);
		if(E<Emin)  {
			DEBUGPRINT("MINIMUM\n");
			Emin = E;
			kmin = k; 
		}
	}
	DEBUGPRINT3("minimum kmin %6d Emin %15.6g hist %15.6g\n", kmin, Emin, hist[kmin]);
	return hist[kmin];
}

double
lmrcImageDeterminationOfThresholdForBinarizationByOhtsuMethod(mrcImage* mrc, int L, int mode)
{
	double  Emax; 
	double  E;
	int     kmax;
	double* hist ;
	int index;
	mrcImageInformation linfo;
	float x, y, z;
	double data;
	int k;
	double omega0, omega1;
	double sigma0, sigma1, sigmaT, sigmaW, sigmaB;
	double mean0, mean1, mean;
	int    count0, count1;
	int N;

	linfo.mode = meanOfAll;
	lmrcImageInformation(&linfo, mrc);
	mean = linfo.mean;
	hist = (double*)memoryAllocate(sizeof(double)*L, "in lmrcImageDetermination");

	N=mrc->HeaderN.x*mrc->HeaderN.y*mrc->HeaderN.z;

	for(index=0; index<L; index++) { 
		hist[index] = (linfo.max-linfo.min)*((double)index)/(double)L+linfo.min; 
		DEBUGPRINT2("hist %4d %15.6g\n", index, hist[index]);
	}

	Emax = 0; 
	DEBUGPRINT1("start E: %15.6g\n", Emax)
	kmax = 0;
	for(k=1; k<L; k++) {
		omega0 = omega1 = 0;
		mean0  = mean1  = 0;
		sigma0 = sigma1 = 0;
		count0 = count1 = 0;
		for(z=0; z<mrc->HeaderN.z; z++) {
		for(y=0; y<mrc->HeaderN.y; y++) {
		for(x=0; x<mrc->HeaderN.x; x++) {
			mrcPixelDataGet(mrc, x, y, z, &data, mrcPixelRePart, mrcPixelHowNearest);
			if(data<hist[k]) {
				omega0++;
				mean0 += data;
				sigma0 += SQR(data);
				count0++;	
			} else {
				omega1++;
				mean1 += data;
				sigma1 += SQR(data);
				count1++;
			}
		}
		}
		}
		omega0 /= N;
		omega1 /= N;
		mean0  /= count0;
		mean1  /= count1;
		sigma0 = (sigma0/count0 - SQR(mean0));   	
		sigma1 = (sigma1/count1 - SQR(mean1));   	

		//
		sigmaB = omega0*SQR(mean0-mean) + omega1*SQR(mean1-mean); 
		sigmaW = omega0*sigma0 + omega1*sigma1; 
		sigmaT = sigmaB + sigmaW;
		E = sigmaB/sigmaT; 
		DEBUGPRINT5("count below %6d above %6d hist %15.6g mean %15.6g %15.6g\n", count0, count1, hist[k], mean0, mean1);
		DEBUGPRINT2("E: k %4d E %15.6g \n", k, E);
		if(Emax<E)  {
			DEBUGPRINT("MAXIMUM\n");
			Emax = E;
			kmax = k; 
		}
	}
	DEBUGPRINT3("minimum kmin %6d Emax %15.6g hist %15.6g\n", kmax, Emax, hist[kmax]);
	return hist[kmax];
	free(hist);
}

double 
lmrcImageDeterminationOfThresholdForBinarizationByptileMethod(mrcImage* mrc, int L, double p, int mode)
{
	int x,y,z;
	int* tile;
	double data;
	int count, total=0;
	double oneLevel, current, wholeintensity, threshold;
	mrcImageInformation linfo;

	DEBUGPRINT("p-tile start\n");
	linfo.mode = meanOfAll;
	lmrcImageInformation(&linfo, mrc);
	wholeintensity = linfo.max-linfo.min;
	
	oneLevel = wholeintensity/L;
	
    tile = (int*)memoryAllocate(sizeof(int)*(L+1), "in lmrcImageDetermination");
	for(count=0 ; count<=L ; count++)
		tile[count] = 0;
	count = 0;
				
	for(x=0; x<mrc->HeaderN.x; x++) {
    for(y=0; y<mrc->HeaderN.y; y++) {
    for(z=0; z<mrc->HeaderN.z; z++) {
        mrcPixelDataGet(mrc, x, y, z, &data, mrcPixelRePart, mrcPixelHowNearest);
		current = (data-linfo.min)/oneLevel;
		tile[(int)current] ++;
		count ++;
	}
	}
	}
	p *= count;
	for(count=L ; total<=(int)p ;count--)
		total += tile[count];
	threshold = count*oneLevel + linfo.min;
	
	return threshold;
	free(tile);
}

double
lmrcImageDeterminationOfThresholdForBinarizationByDifferentialHistogramMethod(mrcImage* mrc, int L, int mode)
{
	double* hist;
	double data, dataminus, dataplus, difference=0;
	double oneLevel, current, wholeintensity, threshold;
    mrcImageInformation linfo;
	int x,y,z,count,ismax_d=L;
		
	linfo.mode = meanOfAll;
    lmrcImageInformation(&linfo, mrc);
    wholeintensity = linfo.max-linfo.min;
    oneLevel = wholeintensity/L;
				
    hist = (double*)memoryAllocate(sizeof(double)*(L+1), "in lmrcImageDetermination");
	for(count=0 ; count<=L ; count++)
        hist[count] = 0;
    count = 0;
	
	for(x=0; x<mrc->HeaderN.x; x++) {
    for(y=0; y<mrc->HeaderN.y; y++) {
	for(z=0; z<mrc->HeaderN.z; z++) {
		if(mrc->HeaderN.z!=1 && (z==0 || z==mrc->HeaderN.z-1));// these 3 "if"sentences is to omit the edge of image 
		else if(mrc->HeaderN.y!=1 && (y==0 || y==mrc->HeaderN.y-1));
		else if(mrc->HeaderN.x!=1 && (x==0 || x==mrc->HeaderN.x-1)); else{
		difference = 0;
		if(mrc->HeaderN.x!=1){
			mrcPixelDataGet(mrc, x-1, y, z, &dataminus, mrcPixelRePart, mrcPixelHowNearest);
			mrcPixelDataGet(mrc, x+1, y, z, &dataplus, mrcPixelRePart, mrcPixelHowNearest);
			difference += pow((dataplus-dataminus),2); }
		if(mrc->HeaderN.y!=1){
            mrcPixelDataGet(mrc, x, y-1, z, &dataminus, mrcPixelRePart, mrcPixelHowNearest);
            mrcPixelDataGet(mrc, x, y+1, z, &dataplus, mrcPixelRePart, mrcPixelHowNearest);
            difference += pow((dataplus-dataminus),2); }
		if(mrc->HeaderN.z!=1){
            mrcPixelDataGet(mrc, x, y, z-1, &dataminus, mrcPixelRePart, mrcPixelHowNearest);
            mrcPixelDataGet(mrc, x, y, z+1, &dataplus, mrcPixelRePart, mrcPixelHowNearest);
            difference += pow((dataplus-dataminus),2); }

		difference = pow(difference,0.5);
        mrcPixelDataGet(mrc, x, y, z, &data, mrcPixelRePart, mrcPixelHowNearest);
        current = (data-linfo.min)/oneLevel;
        hist[(int)current] += difference;
		} //end of omitting
    }
    }
    }
	DEBUGPRINT("in differentialhist 1");
	for(count=0 ; count<L ; count++)
	{
		if( hist[ismax_d] < hist[count] )
			ismax_d = count;
	}			
	free(hist);
	threshold = ismax_d*oneLevel + linfo.min;
	
	return threshold;
}

double
lmrcImageDeterminationOfThresholdForBinarizationByLaplacianHistogramMethod(mrcImage* mrc, int L, int mode)
{	
	double* pixelLaplas;
	double* databox;
	int* tile;
	double data, dataminus, dataplus, laplas=0, maxlaplas=0, oneLevellaplas;
	double wholeintensity, current, oneLevel, threshold, thresholdLaplas;
	int x,y,z,count,total=0;
	int wholepixel;
	mrcImageInformation linfo;

	linfo.mode = meanOfAll;
    lmrcImageInformation(&linfo, mrc);
    wholeintensity = linfo.max-linfo.min;
    oneLevel = wholeintensity/L;
	
	wholepixel = mrc->HeaderN.x * mrc->HeaderN.y * mrc->HeaderN.z;
	pixelLaplas = (double*)memoryAllocate(sizeof(double)*wholepixel, "in lmrcImageDetermination");
	databox = (double*)memoryAllocate(sizeof(double)*wholepixel, "in lmrcImageDetermination");
	for(count=0 ; count<wholepixel ; count++){
		pixelLaplas[count] = 0;
		databox[count] = 0;
	}	
	
	for(x=0; x<mrc->HeaderN.x; x++) {
    for(y=0; y<mrc->HeaderN.y; y++) {
    for(z=0; z<mrc->HeaderN.z; z++) {
        if(mrc->HeaderN.z!=1 && (z==0 || z==mrc->HeaderN.z-1));// these 3 "if"sentences is to omit the edge of image
        else if(mrc->HeaderN.y!=1 && (y==0 || y==mrc->HeaderN.y-1));
        else if(mrc->HeaderN.x!=1 && (x==0 || x==mrc->HeaderN.x-1)); else{
		laplas = 0;
		mrcPixelDataGet(mrc, x, y, z, &data, mrcPixelRePart, mrcPixelHowNearest);
        if(mrc->HeaderN.x!=1){
            mrcPixelDataGet(mrc, x-1, y, z, &dataminus, mrcPixelRePart, mrcPixelHowNearest);
            mrcPixelDataGet(mrc, x+1, y, z, &dataplus, mrcPixelRePart, mrcPixelHowNearest);
            laplas += pow((pow((dataplus+dataminus-data*2),2)),0.5); }
        if(mrc->HeaderN.y!=1){
            mrcPixelDataGet(mrc, x, y-1, z, &dataminus, mrcPixelRePart, mrcPixelHowNearest);
            mrcPixelDataGet(mrc, x, y+1, z, &dataplus, mrcPixelRePart, mrcPixelHowNearest);
			laplas += pow((pow((dataplus+dataminus-data*2),2)),0.5); }
        if(mrc->HeaderN.z!=1){
            mrcPixelDataGet(mrc, x, y, z-1, &dataminus, mrcPixelRePart, mrcPixelHowNearest);
            mrcPixelDataGet(mrc, x, y, z+1, &dataplus, mrcPixelRePart, mrcPixelHowNearest);
			laplas += pow((pow((dataplus+dataminus-data*2),2)),0.5); }
			
        pixelLaplas[(int)x+y*mrc->HeaderN.x+z*mrc->HeaderN.x*mrc->HeaderN.y] = laplas;
		databox[(int)x+y*mrc->HeaderN.x+z*mrc->HeaderN.x*mrc->HeaderN.y] = data;
		if( maxlaplas < laplas ) maxlaplas=laplas;
        } //end of omitting
    }
    }
    }
	tile = (int*)memoryAllocate(sizeof(int)*L, "in lmrcImageDetermination");
	for(count=0 ; count<L ; count++)
		tile[count] = 0;
	fprintf(stdout, "wholeintensity : %f     oneLevel : %f\n",wholeintensity,oneLevel);	
	fprintf(stdout, "maxLaplas : %f  \n",maxlaplas);
	
	oneLevellaplas = maxlaplas/L;
	
	for(count=0 ; count<wholepixel ; count++)
		tile[(int)(pixelLaplas[count]/oneLevellaplas)]++;
	
	for(count=L-1 ; total<(int)((double)wholepixel/10) ; count--)
		total += tile[count];
	free(tile);	
	thresholdLaplas = (double)count * oneLevellaplas;
	fprintf(stdout, " Laplas threshold : %f\n",thresholdLaplas); 	
	
	tile = (int*)memoryAllocate(sizeof(int)*L, "in lmrcImageDetermination");
	for(count=0 ; count<L ; count++)
		tile[count] = 0;
	for(count=0 ; count<wholepixel ; count++){
		if(pixelLaplas[count] > thresholdLaplas){
			current = (databox[count]-linfo.min)/oneLevel;
			tile[(int)current]++;
		}
	}
	free(pixelLaplas);
	free(databox);

	threshold = determinationThresholdFromGraylevelHistogramByOhtsuMethod(tile, L);
	free(tile);
	threshold = threshold*oneLevel + linfo.min;
	
	return threshold;																		
}

double
determinationThresholdFromGraylevelHistogramByOhtsuMethod(int* tile, int L)
{
	int count, count2;
	int* hist2;
	double threshold=0;
	int total=0, n1, n2;
	double mew1, mew2, mewtotal, minimum;
	double sigma1, sigma2, sigmaW, sigmaB;
	double* hist;
	
	hist2 = (int*)memoryAllocate(sizeof(int)*L, "in lmrcImageDetermination");
	hist = (double*)memoryAllocate(sizeof(double)*L, "in lmrcImageDetermination");
	for(count=0 ; count<L ; count++)
	{	
		if(count==0)	hist2[count] = 0;
		else	hist2[count] = hist2[count-1]+tile[count];
		total += tile[count];
	}
	for(count=0 ; count<L ; count++)
	{
		mew1 = 0;
		mew2 = 0;
		sigma1 = 0;
		sigma2 = 0;
		if(hist2[count] < total/5) ;
		else if(hist2[count] > (total*4)/5) ;
		else{
			n1 = hist2[count];
			n2 = total - n1;
			for(count2=0 ; count2<count ; count2++){
				sigma1 += pow(count2,2)*hist2[count2];
				mew1 += hist2[count2]*count2;
			}	
			for(count2=count ; count2<L ; count2++){
				sigma2 += pow(count2,2)*hist2[count2];
				mew2 += hist2[count2]*count2;
			}	
			mewtotal = mew1+mew2;
			mew1 /= n1;
			mew2 /= n2;
			sigma1 /= n1;
			sigma2 /= n2;
			sigma1 -= pow(mew1,2);
			sigma2 -= pow(mew2,2);
			sigmaW = (sigma1*n1+sigma2*n2)/total;
			sigmaB = (n1*SQR(mew1-mewtotal)+n2*SQR(mew2-mewtotal))/total;
			
			hist[count] = sigmaB/sigmaW;
fprintf(stdout,"%d : n1=%d n2=%d eeta=%f\n",count,n1,n2,hist[count]); 			
		}	
	}
	
	minimum = (double)L;
	
	for(count=0 ; count<L ; count++)
	{
		if(hist2[count] < total/5) ;
        else if(hist2[count] > (total*4)/5) ;
        else{
				
			if(hist[count] < minimum){
				minimum = hist[count];
				count2 = count;
			}
		}	
	}	
	threshold = (double)count2;	
fprintf(stdout,"threshold=%f\n",threshold);	
	free(hist2);
	free(hist);
	
	return threshold;
}
