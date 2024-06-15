/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% lmrcImageHoughTransform ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : lmrcImageHoughTransform 
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%lmrcImageHoughTransform ver%I%; Date:%D% %Z%";

#undef DEBUG
#include "genUtil.h"
#include "./lmrcImageHoughTransform.h"

void
lmrcImageHoughTransformSpaceModePrint(FILE* fpt)
{
	fprintf(stderr, "%d: Lines\n", lmrcImageHoughTransformModeLines);
	fprintf(stderr, "    0: Nearest\n");
	fprintf(stderr, "    1: Linear\n");
 	fprintf(stderr, "%d: TwoLines\n", lmrcImageHoughTransformModeTwoLines);
	fprintf(stderr, "    0: Nearest(centre) + InterpolationMode\n");
	fprintf(stderr, "    1: Linear(centre)  + InterpolationMode\n");
    fprintf(stderr, "%d: Rectangles (not yet)\n", lmrcImageHoughTransformModeRectangles);
    fprintf(stderr, "%d: FilledRectangles (not yet)\n", lmrcImageHoughTransformModeFilledRectangles);
    fprintf(stderr, "%d: Circles (not yet)\n", lmrcImageHoughTransformModeCircles);
    fprintf(stderr, "%d: FilledCircles (not yet)\n", lmrcImageHoughTransformModeFilledCircles);
    fprintf(stderr, "%d: GivenStructure (not yet)\n", lmrcImageHoughTransformModeGivenStructure);
}

void 
lmrcImageHoughTransformInverse(mrcImage* out, mrcImage* in, lmrcImageHoughTransformInfo* linfo, int mode)
{
	switch(linfo->HoughSpaceMode) {
		case lmrcImageHoughTransformModeLines: {
			lmrcImageHoughTransformInverseLines(out, in, linfo, mode);
			break;
		}
		default: {
			fprintf(stderr, "Not yet supported HoughTransformMode: %d\n", linfo->HoughSpaceMode);
			exit(EXIT_FAILURE);
		}
	}
}

void 
lmrcImageHoughTransform(mrcImage* out, mrcImage* in, lmrcImageHoughTransformInfo* linfo, int mode)
{
	switch(linfo->HoughSpaceMode) {
		case lmrcImageHoughTransformModeLines: {
			lmrcImageHoughTransformLines(out, in, linfo, mode);
			break;
		}
		case lmrcImageHoughTransformModeTwoLines: {
			lmrcImageHoughTransformTwoLines(out, in, linfo, mode);
			break;
		}
		case lmrcImageHoughTransformModeFilledRectangles: {
			lmrcImageHoughTransformFilledRectangles(out, in, linfo, mode);
			break;
		}
		default: {
			fprintf(stderr, "Not supported HoughTransformMode: %d\n", linfo->HoughSpaceMode);
			exit(EXIT_FAILURE);
		}
	}
}

void 
lmrcImageHoughTransformInit(mrcImage* out, mrcImage* in, lmrcImageHoughTransformInfo* linfo, int mode)
{
    mrcDefaultHeaderValueSet(out);
    out->HeaderN.x = (int)(M_PI/linfo->deltaTheta); 
    out->HeaderN.y = 2*(int)(sqrt(SQR(in->HeaderN.x)+SQR(in->HeaderN.y))/linfo->deltaRho)+1; 
    out->HeaderN.z = (int)((linfo->widthMax - linfo->widthMin)/linfo->deltaRho) + 1;
    out->HeaderMode = mrcFloatImage;
	out->HeaderLength.x = linfo->deltaTheta*DEGREE;
	out->HeaderLength.y = linfo->deltaRho*in->HeaderLength.x;
	out->HeaderLength.z = linfo->deltaRho*in->HeaderLength.y;
	out->HeaderStartN.x = 0;
	out->HeaderStartN.y = -(out->HeaderN.y - 1)/2;
	out->HeaderStartN.z = 0;
    mrcInit(out, NULL); 
}

void 
lmrcImageHoughTransformInverseInit(mrcImage* out, mrcImage* in, lmrcImageHoughTransformInfo* linfo, int mode)
{
	mrcDefaultHeaderValueSet(out);
	out->HeaderN.x = linfo->Nx;
	out->HeaderN.y = linfo->Ny;
	out->HeaderN.z = 1;
	out->HeaderMode = mrcFloatImage;
	out->HeaderLength.x = linfo->dx;
	out->HeaderLength.y = linfo->dy;
	out->HeaderLength.z = linfo->dy;
	out->HeaderStartN.x = 0;
	out->HeaderStartN.y = 0;
	out->HeaderStartN.z = 0;
	mrcInit(out, NULL);
}

void 
lmrcImageHoughTransformLines(mrcImage* out, mrcImage* in, lmrcImageHoughTransformInfo* linfo, int mode)
{
    int iTheta, iRho, iRho0, iRho1, iRhoIndex, index, index2;
    double theta, rho;
    mrcImageParaTypeInteger x, y;
    double data, data2, weight, weight0, weight1, Rho;
    

	lmrcImageHoughTransformInit(out, in, linfo, mode);

    for(y=0; y<in->HeaderN.y; y++) {
    for(x=0; x<in->HeaderN.x; x++) {
        //mrcPixelDataGet(in, x, y, 0, &data, mrcPixelRePart, mrcPixelHowNearest);
		if(in->HeaderMode==mrcFloatImage) {
			index2 = x + in->HeaderN.x*y;
			data = in->ImageFloatImage[index2];  
		} else {
        	mrcPixelDataGet(in, x, y, 0, &data, mrcPixelRePart, mrcPixelHowNearest);
		}
		data/=out->HeaderN.x;

        for(iTheta=0; iTheta<out->HeaderN.x; iTheta++) {
            theta = iTheta*linfo->deltaTheta; 
            rho = x*cos(theta) + y*sin(theta);  
			switch(mode) {
				case 0: {
					if(rho>=0) {
            			iRho = (int)(rho/linfo->deltaRho + 0.5); 
					} else {
            			iRho = (int)(rho/linfo->deltaRho - 0.5); 
					}
					iRho -= out->HeaderStartN.y;
					index = iTheta+iRho*out->HeaderN.x;
					out->ImageFloatImage[index] += data;
					break;
				}
				case 1: {
					Rho = rho/linfo->deltaRho; 
					if(Rho>=0) {
            			iRho0 = (int)Rho; 
            			iRho1 = (int)Rho + 1; 
					} else {
            			iRho0 = (int)Rho - 1; 
            			iRho1 = (int)Rho; 
					}
					weight0 = iRho1 - Rho;
					weight1 = Rho - iRho0;

					iRho0 -= out->HeaderStartN.y;
					index = iTheta+iRho0*out->HeaderN.x;
					out->ImageFloatImage[index] += (data*weight0);
					iRho1 -= out->HeaderStartN.y;
					index = iTheta+iRho1*out->HeaderN.x;
					out->ImageFloatImage[index] += (data*weight1);
					//DEBUGPRINT5("%f %d %d weight: %f %f\n", Rho-out->HeaderStartN.y, iRho0, iRho1, weight0, weight1);
					break;
				}	
				dafault: {
					fprintf(stderr, "Not supported Mode: %d\n", mode);
					exit(EXIT_FAILURE);
					break;
				}
			}
			/*
            mrcPixelDataGet(out, iTheta, iRho, 0, &data2, mrcPixelRePart, mrcPixelHowNearest); 
            mrcPixelDataSet(out, iTheta, iRho, 0, data2+data, mrcPixelRePart);
			*/
        } 
    }
    }  
}

void 
lmrcImageHoughTransformInverseLines(mrcImage* out, mrcImage* in, lmrcImageHoughTransformInfo* linfo, int mode)
{
	int iTheta, iRho, index, index2; 
	mrcImageParaTypeReal theta, rho;
    mrcImageParaTypeReal x, y;
    double data, data2, dx, dy, del, delta, thres;
    
	lmrcImageHoughTransformInverseInit(out, in, linfo, mode);

	delta = sqrt(SQR(out->HeaderLength.x) + SQR(out->HeaderLength.y))/2.0*in->HeaderLength.x*RADIAN;
	thres = 1.0/sqrt(2);
    for(iRho=0;   iRho  <in->HeaderN.y;   iRho++) {
    	rho   = (iRho + in->HeaderStartN.y)*in->HeaderLength.y; 
		DEBUGPRINT3("%f %d/%d\n", rho, iRho, in->HeaderN.y);
    for(iTheta=0; iTheta<in->HeaderN.x; iTheta++) {
    	theta = iTheta*in->HeaderLength.x*RADIAN; 

		index = iTheta + iRho*in->HeaderN.x;
		data = in->ImageFloatImage[index];
        //mrcPixelDataGet(in, iTheta, iRho, 0, &data, mrcPixelRePart, mrcPixelHowNearest); 

		// rho = y*sin(theta)*out->HeaderLength.y + x*cos(theta)*out->HeaderLength.x	
		// y = rho/(sin(theta)*out->HeaderLength.y) - x*cos(theta)*out->HeaderLength.x/(sin(theta)*out->HeaderLength.y)
		// x = rho/(cos(theta)*out->HeaderLength.x) - y*sin(theta)*out->HeaderLength.y/(cos(theta)*out->HeaderLength.x)

		if(thres<fabs(sin(theta))) {
    		for(x=0; x<out->HeaderN.x; x++) {
				y = rho/(sin(theta)*out->HeaderLength.y) - x*cos(theta)*out->HeaderLength.x/(sin(theta)*out->HeaderLength.y);
				if(-0.5<=y && y<out->HeaderN.y-0.5) {
					y = (int)(y+0.5);
					index2 = (int)(x+out->HeaderN.x*y);
					out->ImageFloatImage[index2]+=data;
				}
			}
		} else { 
    		for(y=0; y<out->HeaderN.y; y++) {
				x = rho/(cos(theta)*out->HeaderLength.x) - y*sin(theta)*out->HeaderLength.y/(cos(theta)*out->HeaderLength.x);
				if(-0.5<=x && x<out->HeaderN.x-0.5) {
					x = (int)(x+0.5);
					index2 = (int)(x+out->HeaderN.x*y);
					out->ImageFloatImage[index2]+=data;
				}
			}
		}
    }
    }
}

void
lmrcImageHoughTransformTwoLines(mrcImage* out, mrcImage* in, lmrcImageHoughTransformInfo* linfo, int mode)
{
    int iTheta, iRho, iWidth, index, iRho0, iRho1;
    mrcImageParaTypeReal theta, rho, rho0, rho1, rhoCentre, Rho, width;
    mrcImageParaTypeReal x, y, srcx1, srcy1, srcx2, srcy2;
    double data0, data1, data2, weight0, weight1;


	lmrcImageHoughTransformInit(out, in, linfo, mode);

	for(iWidth=0; iWidth<out->HeaderN.z; iWidth++) {
		width = (iWidth*linfo->deltaRho + linfo->widthMin)/2.0;		
		
    	for(y=0; y<in->HeaderN.y; y++) {
    	for(x=0; x<in->HeaderN.x; x++) {
        	for(iTheta=0; iTheta<out->HeaderN.x; iTheta++) {
            	theta     = iTheta*linfo->deltaTheta; 
				rhoCentre = x*cos(theta) + y*sin(theta); 

				switch(mode) {
					case 0: {
						if(0<=rhoCentre) {
							iRho      = (int)(rhoCentre/linfo->deltaRho+0.5);
						} else {
							iRho      = (int)(rhoCentre/linfo->deltaRho-0.5);
						}
						iRho -= out->HeaderStartN.y; 

						if(0<=iRho && iRho <out->HeaderN.y) {
							srcx1 = +width*cos(theta) + x;
							srcy1 = +width*sin(theta) + y;
							srcx2 = -width*cos(theta) + x;
							srcy2 = -width*sin(theta) + y;

       			 			mrcPixelDataGet(in, srcx1, srcy1, 0, &data1, mrcPixelRePart, linfo->InterpolationMode);
        					mrcPixelDataGet(in, srcx2, srcy2, 0, &data2, mrcPixelRePart, linfo->InterpolationMode);

							index = iTheta + iRho*out->HeaderN.x + iWidth*out->HeaderN.x*out->HeaderN.y;
							out->ImageFloatImage[index] += ((data1+data2)/2.0/out->HeaderN.x);
            				//mrcPixelDataGet(out, iTheta, iRho, iWidth, &data0, mrcPixelRePart, mrcPixelHowNearest); 
            				//mrcPixelDataSet(out, iTheta, iRho, iWidth, data0+data1+data2, mrcPixelRePart);
						}
						break;
					}
					case 1: {
						Rho  = rhoCentre/linfo->deltaRho;
						iRho = (int)Rho;
						if(0<=rhoCentre) {
							iRho0      = iRho;
							iRho1      = iRho + 1;
						} else {
							iRho0      = iRho - 1;
							iRho1      = iRho;
						}
						weight0 = iRho1 - Rho;
						weight1 = Rho - iRho0;
	
						//iRho -= out->HeaderStartN.y; 
						iRho0 -= out->HeaderStartN.y; 
						iRho1 -= out->HeaderStartN.y; 

						if(0<=iRho0 && iRho1 <out->HeaderN.y) {
							srcx1 = +width*cos(theta) + x;
							srcy1 = +width*sin(theta) + y;
							srcx2 = -width*cos(theta) + x;
							srcy2 = -width*sin(theta) + y;

       			 			mrcPixelDataGet(in, srcx1, srcy1, 0, &data1, mrcPixelRePart, linfo->InterpolationMode);
        					mrcPixelDataGet(in, srcx2, srcy2, 0, &data2, mrcPixelRePart, linfo->InterpolationMode);

							//iRho0
							index = iTheta + iRho0*out->HeaderN.x + iWidth*out->HeaderN.x*out->HeaderN.y;
							out->ImageFloatImage[index] += ((data1+data2)/2.0/out->HeaderN.x*weight0);
							//iRho1
							index = iTheta + iRho1*out->HeaderN.x + iWidth*out->HeaderN.x*out->HeaderN.y;
							out->ImageFloatImage[index] += ((data1+data2)/2.0/out->HeaderN.x*weight1);


            				//mrcPixelDataGet(out, iTheta, iRho, iWidth, &data0, mrcPixelRePart, mrcPixelHowNearest); 
            				//mrcPixelDataSet(out, iTheta, iRho, iWidth, data0+data1+data2, mrcPixelRePart);
						}
						break;
					}
					dafault: {
						fprintf(stderr, "Not supported Mode: %d\n", mode);
						exit(EXIT_FAILURE);
						break;
					}
				}
			}
        }  
    }  
    }  
}

void 
lmrcImageHoughTransformInverseTwoLines(mrcImage* out, mrcImage* in, lmrcImageHoughTransformInfo* linfo, int mode)
{
    int iTheta, iRho, index, index2;
    mrcImageParaTypeReal theta, rho;
    mrcImageParaTypeReal x, y;
    double data, data2, dx, dy, del, delta, thres;
    

	lmrcImageHoughTransformInverseInit(out, in, linfo, mode);

	thres = 1.0/sqrt(2.0);
	delta = in->HeaderLength.y*out->HeaderLength.x*RADIAN;
    for(iRho=0;   iRho  <in->HeaderN.y;   iRho++) {
    	rho   = (iRho + in->HeaderStartN.y)*in->HeaderLength.y; 
		DEBUGPRINT2("%f %d\n", rho, iRho);
    for(iTheta=0; iTheta<in->HeaderN.x; iTheta++) {
    	theta = iTheta*in->HeaderLength.x*RADIAN; 
	
		index = iTheta + iRho*in->HeaderN.x;
		data = in->ImageFloatImage[index];

		if(thres<fabs(sin(theta))) {
    		for(x=0; x<out->HeaderN.x; x++) {
				y = rho/(sin(theta)*out->HeaderLength.y) - x*cos(theta)*out->HeaderLength.x/(sin(theta)*out->HeaderLength.y);
				if(-0.5<=y && y<out->HeaderN.y-0.5) {
					y = (int)(y+0.5);
					index2 = (int)(x+out->HeaderN.x*y);
					out->ImageFloatImage[index2]+=data;
				}
			}
		} else { 
    		for(y=0; y<out->HeaderN.y; y++) {
				x = rho/(cos(theta)*out->HeaderLength.x) - y*sin(theta)*out->HeaderLength.y/(cos(theta)*out->HeaderLength.x);
				if(-0.5<=x && x<out->HeaderN.x-0.5) {
					x = (int)(x+0.5);
					index2 = (int)(x+out->HeaderN.x*y);
					out->ImageFloatImage[index2]+=data;
				}
			}
		}
    }   
    }   
}



void
lmrcImageHoughTransformFilledRectangles(mrcImage* out, mrcImage* in, lmrcImageHoughTransformInfo* linfo, int mode)
{
    int iTheta, iRho, iWidth, index, iRho0, iRho1;
    double theta, rho, rho0, rho1, rhoCentre, Rho, width, w, widthOut;
    mrcImageParaTypeReal x, y, srcx1, srcy1, srcx2, srcy2, srcx, srcy;
    double data0, data1, data2, weight0, weight1, data, norm;


	lmrcImageHoughTransformInit(out, in, linfo, mode);

	for(iWidth=0; iWidth<out->HeaderN.z; iWidth++) {
		width = (iWidth*linfo->deltaRho + linfo->widthMin)/2.0;	
		widthOut = linfo->widthOut+width;
		norm = 1.0/out->HeaderN.x/(2.0*widthOut);
		//DEBUGPRINT2("width: %f %f\n", width, widthOut);
    	for(y=0; y<in->HeaderN.y; y++) {
    	for(x=0; x<in->HeaderN.x; x++) {
        	for(iTheta=0; iTheta<out->HeaderN.x; iTheta++) {
            	theta     = iTheta*linfo->deltaTheta; 
				rhoCentre = x*cos(theta) + y*sin(theta); 

				switch(mode) {
					case 0: {
						if(0<=rhoCentre) {
							iRho      = (int)(rhoCentre/linfo->deltaRho+0.5);
						} else {
							iRho      = (int)(rhoCentre/linfo->deltaRho-0.5);
						}
						iRho -= out->HeaderStartN.y; 

						if(0<=iRho && iRho <out->HeaderN.y) {
							for(w=-width; w<=width; w+=linfo->deltaRho) {
								srcx = +w*cos(theta) + x;
								srcy = +w*sin(theta) + y;
       			 				mrcPixelDataGet(in, srcx, srcy, 0, &data, mrcPixelRePart, linfo->InterpolationMode);
								index = iTheta + iRho*out->HeaderN.x + iWidth*out->HeaderN.x*out->HeaderN.y;
								out->ImageFloatImage[index] += (data*norm);
							}
							for(w=-widthOut; w<-width; w+=linfo->deltaRho) {
								srcx = +w*cos(theta) + x;
								srcy = +w*sin(theta) + y;
       			 				mrcPixelDataGet(in, srcx, srcy, 0, &data, mrcPixelRePart, linfo->InterpolationMode);
								index = iTheta + iRho*out->HeaderN.x + iWidth*out->HeaderN.x*out->HeaderN.y;
								out->ImageFloatImage[index] -= (data*norm);
							}
							for(w= widthOut; width<w; w-=linfo->deltaRho) {
								srcx = +w*cos(theta) + x;
								srcy = +w*sin(theta) + y;
       			 				mrcPixelDataGet(in, srcx, srcy, 0, &data, mrcPixelRePart, linfo->InterpolationMode);
								index = iTheta + iRho*out->HeaderN.x + iWidth*out->HeaderN.x*out->HeaderN.y;
								out->ImageFloatImage[index] -= (data*norm);
							}
						}
						break;
					}
					case 1: {
						Rho  = rhoCentre/linfo->deltaRho;
						iRho = (int)Rho;
						if(0<=rhoCentre) {
							iRho0      = iRho;
							iRho1      = iRho + 1;
						} else {
							iRho0      = iRho - 1;
							iRho1      = iRho;
						}
						weight0 = iRho1 - Rho;
						weight1 = Rho - iRho0;
	
						//iRho -= out->HeaderStartN.y; 
						iRho0 -= out->HeaderStartN.y; 
						iRho1 -= out->HeaderStartN.y; 

						if(0<=iRho0 && iRho1 <out->HeaderN.y) {
							for(w= -width; w<=width; w+=linfo->deltaRho) {
								srcx = +w*cos(theta) + x;
								srcy = +w*sin(theta) + y;
       			 				mrcPixelDataGet(in, srcx, srcy, 0, &data, mrcPixelRePart, linfo->InterpolationMode);
								index = iTheta + iRho0*out->HeaderN.x + iWidth*out->HeaderN.x*out->HeaderN.y;
								out->ImageFloatImage[index] += (data*norm*weight0);
								index = iTheta + iRho1*out->HeaderN.x + iWidth*out->HeaderN.x*out->HeaderN.y;
								out->ImageFloatImage[index] += (data*norm*weight1);
							}
							for(w= -widthOut; w < -width; w+=linfo->deltaRho) {
								srcx = +w*cos(theta) + x;
								srcy = +w*sin(theta) + y;
       			 				mrcPixelDataGet(in, srcx, srcy, 0, &data, mrcPixelRePart, linfo->InterpolationMode);
								index = iTheta + iRho0*out->HeaderN.x + iWidth*out->HeaderN.x*out->HeaderN.y;
								out->ImageFloatImage[index] -= (data*norm*weight0);
								index = iTheta + iRho1*out->HeaderN.x + iWidth*out->HeaderN.x*out->HeaderN.y;
								out->ImageFloatImage[index] -= (data*norm*weight1);
							}
							for(w= widthOut; width < w; w-=linfo->deltaRho) {
								srcx = +w*cos(theta) + x;
								srcy = +w*sin(theta) + y;
       			 				mrcPixelDataGet(in, srcx, srcy, 0, &data, mrcPixelRePart, linfo->InterpolationMode);
								index = iTheta + iRho0*out->HeaderN.x + iWidth*out->HeaderN.x*out->HeaderN.y;
								out->ImageFloatImage[index] -= (data*norm*weight0);
								index = iTheta + iRho1*out->HeaderN.x + iWidth*out->HeaderN.x*out->HeaderN.y;
								out->ImageFloatImage[index] -= (data*norm*weight1);
							}
						}
						break;
					}
					dafault: {
						fprintf(stderr, "Not supported Mode: %d\n", mode);
						exit(EXIT_FAILURE);
						break;
					}
				}
			}
        }  
    }  
    }  
}
