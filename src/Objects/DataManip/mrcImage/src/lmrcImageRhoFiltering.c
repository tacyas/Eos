/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% lmrcImageRhoFiltering ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : lmrcImageRhoFiltering 
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%lmrcImageRhoFiltering ver%I%; Date:%D% %Z%";
#include <math.h>
#include <stdlib.h>
#undef DEBUG
#include "genUtil.h"
#include "eosFunc.h"
#include "../inc/mrcImage.h"
#include "Matrix3D.h"
#include "./lmrcImageRhoFiltering.h"

/*
	lmrcImageRhoFiltering2
		Rho-Filtering for double-tilting
*/

void
lmrcImageRhoFiltering2(mrcImage* out, mrcImage* counter, int index, Matrix3D M, lmrcImageRhoFilteringInfo* linfo, long mode)
{
	mrcImage counterFFT; 
	mrcImage counterReal;
	mrcImage fft;
	mrcImageParaTypeReal X, Y, Z;
	mrcImageParaTypeReal x, y, z;
	mrcImageParaTypeReal prjX, prjY, prjZ;
	mrcImageParaTypeReal prjx, prjy, prjz;
	double re;
	//double im;
	double re2,im2;
	double redst, imdst;
	//double R;
	//double norm, normN;
	double F000;
	//mrcImageParaTypeReal XX, YY, ZZ; 
	mrcImageParaTypeReal g3x, g3y, g3z; 
	floatVector v;	
	//mrcImageParaTypeReal lX, lY, lZ;
	//mrcImageParaTypeReal nX, nY, nZ;
	//mrcImageParaTypeReal aX, aY, aZ;
	double data;
	double lenX, lenY, lenZ;
	double startX, startY, startZ;
	double endX, endY, endZ;
	double weight, zweight, normz, weightThres;
	double delta;

	DEBUGPRINT("Start lmrcImageRhoFiltering2\n");
	floatVectorInit(&v, 4);
    v.data[3] = 1.0;

	if(out->HeaderN.x%2==0) {
		lenX = (out->HeaderN.x  )/2.0;
	} else {
		lenX = (out->HeaderN.x-1)/2.0;
	}
	endX = lenX;
	startX = 0; 

	if(out->HeaderN.y%2==0) {
		lenY = (out->HeaderN.y    )/2.0;
		startY = -lenY;
		endY   =  lenY-1;
	} else {
		lenY = (out->HeaderN.y - 1)/2.0;
		startY = -lenY;
		endY   =  lenY;
	}

	if(out->HeaderN.z%2==0) {
		lenZ = (out->HeaderN.z    )/2.0;
		startZ = -lenZ;
		endZ   =  lenZ-1;
	} else {
		lenZ = (out->HeaderN.z - 1)/2.0;
		startZ = -lenZ;
		endZ   =  lenZ;
	}
	DEBUGPRINT3("%f %f %f\n", startX, endX, lenX);
	DEBUGPRINT3("%f %f %f\n", startY, endY, lenY);
	DEBUGPRINT3("%f %f %f\n", startZ, endZ, lenZ);
	delta = 1.0/linfo->SubSampling;
	
	switch(mode) {
		case 0: { /* Preparing */
			/* Initialization */
			if(0==index) { 
				counter->Header.Cont = out->Header.Cont;
				counter->HeaderMode  = mrcComplexDoubleFT;
				mrcInit(counter, NULL);
			}
			switch(linfo->weightMode) {
				case 0:
				case 1:
				case 2: 
				case 3: {
					counterReal.Header.Cont = out->Header.Cont; 
					mrcInit(&counterReal, NULL);
					DEBUGPRINT1("WeightMode: %d\n", linfo->weightMode);
					/* Counter Set */
					g3x = (out->HeaderN.x-1.0)/2.0;
					g3y = (out->HeaderN.y-1.0)/2.0;
					g3z = (out->HeaderN.z-1.0)/2.0;
					zweight = 1;		
    				for(z=0; z<out->HeaderN.z; z+=delta) {
    				for(y=0; y<out->HeaderN.y; y+=delta) {
    				for(x=0; x<out->HeaderN.x; x+=delta) {
    					v.data[0] = x-g3x;
    					v.data[1] = y-g3y;
    					v.data[2] = z-g3z;
    					v.data[3] = 1;
						weight = 1;

    					matrix3DMultiplyVector(&v, M); /* 3D Space into Projection Space */ 
						prjx = v.data[0];			
						prjy = v.data[1];			
						prjz = v.data[2];  
						if(linfo->flagThicknessWeight) {
							normz = fabs(prjz/g3z);	 
							if(normz<0.9) {
								zweight = 1; 
							} else if(1<normz){
								zweight = 0;
							} else {
								zweight = (cos((normz-0.9)/0.1*M_PI) + 1.0)/2.0;
							}	
						}
						if(-0.5 <= prjz + g3z && prjz + g3z < out->HeaderN.z-0.5) {	
							switch(linfo->weightMode)  {
								case 0: {	
    								if( -1<prjx && prjx<1
    		  		  	  	  		&&-1<prjy && prjy<1) {
										data = MAX(0,1-sqrt(SQR(prjx) + SQR(prjy)));
    									mrcPixelDataSet(&counterReal, x, y, z, weight*data*zweight, mrcPixelRePart);
    								}
									break;
								}
								case 1: {	
    								if( -1<prjx && prjx<1
    			  		  	  	      &&-1<prjy && prjy<1) {
										data = (1-fabs(prjx))*(1-fabs(prjy));
    									mrcPixelDataSet(&counterReal, x, y, z, weight*data*zweight, mrcPixelRePart);
    								}
									break;
								}
								case 2: {	
    								if( -1<=prjx && prjx<1.0
    			  		  	  	  	  &&-1<=prjy && prjy<1.0) {
										//fprintf(stderr, "prj %f %f %f org %f %f %f\n", prjx, prjy, prjz, x, y, z);
										data = 0.25;
    									mrcPixelDataSet(&counterReal, x, y, z, weight*data*zweight, mrcPixelRePart);
    								}
									break;
								}
								case 3: {	
    								if( -1<=prjx && prjx<1.0
    			  		  	  		  &&-1<=prjy && prjy<1.0) {
										//fprintf(stderr, "prj %f %f %f org %f %f %f\n", prjx, prjy, prjz, x, y, z);
    									mrcPixelDataGet(&counterReal, x, y, z, &data, mrcPixelRePart, mrcPixelHowNearest);
										data += weight*0.25/delta/delta*zweight; 
    									mrcPixelDataSet(&counterReal, x, y, z, data, mrcPixelRePart);
    								}
									break;
								}
								default: {
									fprintf(stderr, "weightMode Not Supported: %d:\n", linfo->weightMode);
									exit(EXIT_FAILURE);
									break;
								}
							}	
						}	
					//fprintf(stderr, "weight %f data %f \n", weight, data);
    				}
    				}	
    				}	

					DEBUGPRINT("FFT Start\n")
					lmrcImageFFT(&counterFFT, &counterReal, 0);
					DEBUGPRINT("FFT End\n")
					mrcPixelDataGet(&counterFFT, 0, 0, 0, &F000, mrcPixelMag, mrcPixelHowNearest);
					if(0==F000) fprintf(stderr, "F000 = %f\n", F000);
#undef DEBUG
#ifdef  DEBUG
					DEBUGPRINT1("F000:%g\n", F000);
    				mrcPixelDataGet(counter, 0, 0, 0, &re, mrcPixelMag, mrcPixelHowNearest);
					DEBUGPRINT1("F000:%g counter\n", re);
				    mrcPixelDataGet(&counterFFT, 1, 0, 0, &re, mrcPixelMag, mrcPixelHowNearest);
					DEBUGPRINT1("F100:%g\n", re);
				    mrcPixelDataGet(counter, 1, 0, 0, &re, mrcPixelMag, mrcPixelHowNearest);
					DEBUGPRINT1("F100:%g counter\n", re);
				    mrcPixelDataGet(&counterFFT, counter->HeaderN.x/2.0, 0, 0, &re, mrcPixelMag, mrcPixelHowNearest);
					DEBUGPRINT1("Nyquest X:%g \n", re);
				    mrcPixelDataGet(counter, counter->HeaderN.x/2.0, 0, 0, &re, mrcPixelMag, mrcPixelHowNearest);
					DEBUGPRINT1("Nyquest X:%g counter\n", re);
				    mrcPixelDataGet(&counterFFT, 0.0, counter->HeaderN.y/2.0, 0, &re, mrcPixelMag, mrcPixelHowNearest);
					DEBUGPRINT1("Nyquest Y:%g \n", re);
				    mrcPixelDataGet(counter, 0.0, counter->HeaderN.y/2.0, 0, &re, mrcPixelMag, mrcPixelHowNearest);
					DEBUGPRINT1("Nyquest Y:%g counter\n", re);
#endif
					for(Z=startZ; Z <= endZ; Z++) {
					for(Y=startY; Y <= endY; Y++) {
					for(X=startX; X <= endX; X++) {
						weight = SQR(X/lenX)
								+SQR(Y/lenY)
								+SQR(Z/lenZ);
						if(0<weight) {
							weight = sqrt(weight); 
							if(weight<0.9) {
								weight = 1;
							} else if(weight<1) {
								weight = (cos(M_PI*(weight-0.9)/0.1)+1)/2.0; 
							} else {
								weight = 0;
							}	
						} else {
							weight = 1;
						}
    					mrcPixelDataGet(&counterFFT, X, Y, Z, &re,  mrcPixelMag, mrcPixelHowNearest);
    					mrcPixelDataGet(counter,     X, Y, Z, &re2, mrcPixelRePart, mrcPixelHowNearest);
    					mrcPixelDataSet(counter,     X, Y, Z, re2+weight*re/F000, mrcPixelRePart);
    					mrcPixelDataSet(counter,     X, Y, Z, 0.0, mrcPixelImPart);
						//fprintf(stderr, "re2 %f re %f weight %f F000 %f \n", re2, re, weight, F000);	
					}
					}
					}
					mrcImageFree(&counterFFT, 0);
					mrcImageFree(&counterReal, 0);
					break;
				}
				case 4: 
				case 5: 
				case 6: {
					DEBUGPRINT("Plane Weight\n")
					for(Z=startZ; Z <= endZ; Z++) {
					for(Y=startY; Y <= endY; Y++) {
					for(X=startX; X <= endX; X++) {
    					v.data[0] = X;
    					v.data[1] = Y;
    					v.data[2] = Z;
    					v.data[3] = 1;
    					matrix3DMultiplyVector(&v, M); /* 3D Space into Projection Space */ 
						prjX = v.data[0];			
						prjY = v.data[1];			
						prjZ = v.data[2];  
						switch(linfo->weightMode) {
							case 4: {
								if(-counter->HeaderN.x/2.0 < prjX && prjX < counter->HeaderN.x/2.0-0.5
								 &&-counter->HeaderN.y/2.0 < prjY && prjY < counter->HeaderN.y/2.0-0.5 
								 &&                 -0.5 <= prjZ && prjZ < 0.5 ) {
									weight = 1.0; 		
								} else {
									weight = 0;
								}
#ifdef DEBUG
								if(weight!=0) {	
								DEBUGPRINT3("%f %f %f \n", prjX, prjY, prjZ);
								DEBUGPRINT4("%f %f %f => weight %f \n", X, Y, Z, weight);
								}
#endif
								break;
							}
							case 5: {   
								if(-counter->HeaderN.x/2.0<prjX && prjX < counter->HeaderN.x/2.0
								 &&-counter->HeaderN.y/2.0<prjY && prjY < counter->HeaderN.y/2.0
								 &&                 -1 <= prjZ && prjZ <= 1.0 ) {
									weight = (prjZ<0)?(1+prjZ):(1-prjZ); 		
								} else {
									weight = 0;
								}
								break;
							}
							case 6: {   
								if(-counter->HeaderN.x/2.0<prjX && prjX < counter->HeaderN.x/2.0
								 &&-counter->HeaderN.y/2.0<prjY && prjY < counter->HeaderN.y/2.0
								 &&                  -1 < prjZ && prjZ <= 1.0 ) {
									weight = (cos(prjZ*M_PI)+1.0)/2.0; 		
								} else {
									weight = 0;
								}
								break;
							}
							default: {
								weight = 0;
								break;
							}
						}
    					mrcPixelDataGet(counter,    X, Y, Z, &data,       mrcPixelRePart, mrcPixelHowNearest);
    					mrcPixelDataSet(counter,    X, Y, Z, 0.0,         mrcPixelImPart);
    					mrcPixelDataSet(counter,    X, Y, Z, data+weight, mrcPixelRePart);
					}
					}	
					}
					break;	
				}
				default: {
					break;
				}
			}           
			break;
		}
		case 1: { /* Performing */ 
			lmrcImageFFT(&fft, out, 0); 
#ifdef DEBUG
    		mrcPixelDataGet(counter, 0, 0, 0, &re, mrcPixelRePart, mrcPixelHowNearest);
			DEBUGPRINT1("Final F000:%g counter\n", re);
		    mrcPixelDataGet(counter, 1, 0, 0, &re, mrcPixelRePart, mrcPixelHowNearest);
			DEBUGPRINT1("Final F100:%g counter\n", re);
		    mrcPixelDataGet(counter, counter->HeaderN.x/2.0, 0, 0, &re, mrcPixelRePart, mrcPixelHowNearest);
			DEBUGPRINT1("Final Nyqust X:%g counter\n", re);
		    mrcPixelDataGet(counter, 0.0,  counter->HeaderN.y/2.0, 0, &re, mrcPixelRePart, mrcPixelHowNearest);
			DEBUGPRINT1("Final Nyqust Y:%g counter\n", re);
#endif
			for(Z=startZ; Z<=endZ; Z++) {
			for(Y=startY; Y<=endY; Y++) {
			for(X=startX; X<=endX; X++) {
				weight = SQR(X/lenX) + SQR(Y/lenY) + SQR(Z/lenZ); 
				if(weight<0.9) {
					weight = 1;
				} else if(1<=weight) {
					weight = 0;
				} else {
					//weight = 0;
					//weight = (1-weight)/0.1;
					weight = (cos(M_PI*(weight-0.9)/0.1)+1)/2.0; 
				}
				if(             Y == startY || Z == startZ ||
				   X==endX   || Y == endY   || Z == endZ) {
				   weight = 0;
				}
				mrcPixelDataGet(counter, X, Y, Z, &re,  mrcPixelRePart, mrcPixelHowNearest);

				mrcPixelDataGet(&fft,     X, Y, Z, &re2, mrcPixelRePart, mrcPixelHowNearest);
				mrcPixelDataGet(&fft,     X, Y, Z, &im2, mrcPixelImPart, mrcPixelHowNearest);

				//fprintf(stderr, "counter %f fft %f %f\n", re, re2, im2 );
				//if(X==0) fprintf(stderr, "counter %f fft %f %f thres %f\n", re, re2, im2, linfo->counterThreshold);
				if(re==0) { 
					weightThres=0;
				} else {
					switch(linfo->counterThresholdMode)	{
						case 0:
							if(linfo->counterThreshold<re) {
								/* re is not exactly zero because of calculation errors : 
									1e-2/1e-6 give the same result : by tacyas 2005/02/04  */ 
								weightThres = 1.0/re;
							} else {
								weightThres = 0;
							}
							break;
						 case 1:
							//weightThres = 1.0/re*(1/(1+SQR(linfo->counterThreshold/re)));
							weightThres = 1.0/(re + SQR(linfo->counterThreshold)/re);
							break;
						 default: 
							if(linfo->counterThreshold<re) {
								weightThres = 1.0/re;
							} else {
								weightThres = 0;
							}
							break;
					}
				}	
				redst = re2*weightThres*weight;
				imdst = im2*weightThres*weight;
				mrcPixelDataSet(&fft, X, Y, Z, redst, mrcPixelRePart);
				mrcPixelDataSet(&fft, X, Y, Z, imdst, mrcPixelImPart);
				//if(X==0) { fprintf(stderr, "counter %f fft %f %f thres %f weight %f weightTres %f\n", re, re2, im2, linfo->counterThreshold, weight, weightThres); fflush(stderr); }
				//if(Y==startY || Z == startZ) { fprintf(stderr, "counter %f fft %f %f thres %f weight %f weightTres %f at %f %f %f dst %f %f\n", re, re2, im2, linfo->counterThreshold, weight, weightThres, X, Y, Z, redst, imdst); fflush(stderr); }
			}	
			}
			}
#ifdef DEBUG
			mrcFileWrite(&fft, "/tmp/test.fft", "in main", 0);
#endif
			lmrcImageFFT(out, &fft, 0);	
			mrcImageFree(&fft, 0);
			break;
		}
		default: {
			fprintf(stderr, "Not supported mode in lmrcImageRhoFiltering2: %ld\n", mode);
			exit(EXIT_FAILURE);
			break;
		}
	}
	//fprintf(stderr, "%x counter pointer\n", &counter);
	DEBUGPRINT("End lmrcImageRhoFiltering\n")
	return;
}

void
lmrcImageRhoFiltering(mrcImage* out, mrcImage* in, Matrix3D M, lmrcImageRhoFiltering1Info linfo, long mode)
{
	mrcImage fft;
	mrcImageParaTypeReal X, Y;
	double re, im;
	double R;
	double norm, normN;
	mrcImageParaTypeReal XX, YY; 
	double weight;
	mrcImageParaTypeReal lX, lY, lZ;
	mrcImageParaTypeReal nX, nY, nZ;
	mrcImageParaTypeReal aX, aY, aZ;

	nX = M[2][0];
	nY = M[2][1];
	nZ = M[2][2];
	DEBUGPRINT3("n(%f %f %f)\n", nX, nY, nZ);
	if(nX!=0.0 || nY!=0.0) {
		normN = sqrt(SQR(nX) + SQR(nY));
		aX =  nY/normN;
		aY = -nX/normN;
		aZ =  0.0;
	} else {
	    DEBUGPRINT1("mode :%ld\n",mode);
		switch(mode) {
			case 0: { /* x */
			    aX = 1.0;
			    aY = 0.0;
			    aZ = 0.0;
				break;
			}
			case 1: { /* y */
			    aX = 0.0;
			    aY = 1.0;
			    aZ = 0.0;
				break;
			}
			default: {
				fprintf(stderr, "Not supported : %ld \n", mode);
				exit(EXIT_FAILURE);
			}
		}
	}
	DEBUGPRINT3("a(%f %f %f)\n", aX, aY, aZ);
	lmrcImageFFT(&fft, in, 0);

	for(X=0; X<=fft.HeaderN.x/2.0; X++) {
		for(Y=-fft.HeaderN.y/2.0; Y<fft.HeaderN.y/2.0; Y++) {
			XX = X/(fft.HeaderLength.x*fft.HeaderN.x);
			YY = Y/(fft.HeaderLength.y*fft.HeaderN.y);
			lX = M[0][0]*XX + M[1][0]*YY; 
			lY = M[0][1]*XX + M[1][1]*YY; 
			lZ = M[0][2]*XX + M[1][2]*YY; 
			norm = lX*aX + lY*aY + lZ*aZ; 
			R = sqrt(SQR(lX - norm*aX) 
				   + SQR(lY - norm*aY) +SQR(lZ -norm*aZ) );
			switch(linfo.filterMode) {
				case lmrcImageRhoFilter1ModeRhoFilter: { // Original Rho-Filter
					weight = 1;
					break;
				}	
				case lmrcImageRhoFilter1ModeRamLak: { // Ram-Lak Filter 
					weight = eosRect(R,linfo.Rmax);
					break;
				}
				case lmrcImageRhoFilter1ModeSheppLogan: { // Shepp-Logan Filter 
					weight = eosSinc(R/linfo.Rmax/2.0)*eosRect(R,linfo.Rmax);
					break;
				}
				case lmrcImageRhoFilter1ModeCosine: { // cosine
					weight = cos(R/linfo.Rmax*M_PI/2.0)*eosRect(R,linfo.Rmax);
					break;
				}
				default: {
					weight = 1;
					fprintf(stderr, "Not supported RhoFilter Mode: %d\n", linfo.filterMode);
					break;
				}
			}
			mrcPixelDataGet(&fft, X, Y, 0.0, &re, mrcPixelRePart, mrcPixelHowNearest);
			mrcPixelDataGet(&fft, X, Y, 0.0, &im, mrcPixelImPart, mrcPixelHowNearest);
			mrcPixelDataSet(&fft, X, Y, 0.0, re*R*weight, mrcPixelRePart);
			mrcPixelDataSet(&fft, X, Y, 0.0, im*R*weight, mrcPixelImPart);
		}
	}
	mrcImageFree( out, "in lmrcImageRhoFiltering");
	lmrcImageFFT(out, &fft, 0);
	mrcImageFree(&fft, "in lmrcImageRhoFiltering");
}
