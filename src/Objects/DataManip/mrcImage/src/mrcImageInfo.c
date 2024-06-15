/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% mrcImageInfo ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : mrcImageInfo 
#%Z% Attention
#%Z%
*/

static char __sccs_id[] = "%Z%mrcImageInfo ver%I%; Date:%D% %Z%";

#define DEBUG
#undef UNDEBUG2
#include "genUtil.h"
#include <math.h>
#include <stdlib.h>
#include "../inc/mrcImage.h"
#include "Memory.h"

void
lmrcImageYSection(mrcImage* sec, mrcImage* img, double Y)
{
	mrcImageParaTypeInteger ix, iz;
	double data;

	DEBUGPRINT1("%f in lmrcImageYSection", Y);
	if(IsImage(img, "lmrcImageYSection", mrcStatusMask_ExitFailure)) {
    	sec->Header    = img->Header;
    	sec->HeaderN.y = 1;
    	mrcInit(sec, NULL);
    	for(ix=0; ix<img->HeaderN.x; ix++) {
    		for(iz=0; iz<img->HeaderN.z; iz++) {
        		mrcPixelDataGet(img, 
                               (mrcImageParaTypeReal)ix, 
                               (mrcImageParaTypeReal)Y, 
                               (mrcImageParaTypeReal)iz, 
                               &data, mrcPixelRePart, mrcPixelHowNearest);
        		mrcPixelDataSet(sec, 
								(mrcImageParaTypeReal)ix, 
								0.0, 
								iz, 
                        		data, mrcPixelRePart); 
				DEBUGPRINT4("%d %d %d : %f\n", ix, (int)Y, iz, data);
			}
    	}
	} else if(IsFT(img, "lmrcImageYSection", mrcStatusMask_ExitFailure)) {
    	sec->Header     = img->Header;
		sec->HeaderMode = mrcFloatImage;
    	sec->HeaderN.y  = 1;
    	mrcInit(sec, NULL);
    	for(ix=-img->HeaderN.x/2.0; ix<img->HeaderN.x/2.0; ix++) {
    		for(iz=-img->HeaderN.z/2.0; iz<img->HeaderN.z/2.0; iz++) {
        		mrcPixelDataGet(img, 
                               (mrcImageParaTypeReal)ix, 
                               (mrcImageParaTypeReal)Y, 
                               (mrcImageParaTypeReal)iz, 
                               &data, mrcPixelMag, mrcPixelHowNearest);
        		mrcPixelDataSet(sec, 
								(mrcImageParaTypeReal)ix+img->HeaderN.x/2.0, 
								0.0, 
								(mrcImageParaTypeReal)iz+img->HeaderN.z/2.0, 
                        		data, mrcPixelRePart); 
			}
    	}
	} else {
		fprintf(stderr, "Not Supported Mode: %d\n", img->HeaderMode);
	}	
	mrcStatDataSet(sec, 0);
}

void
lmrcImageXSection(mrcImage* sec, mrcImage* img, double X)
{
	mrcImageParaTypeInteger iy, iz;
	double data;

	if(IsImage(img, "lmrcImageYSection", mrcStatusMask_ExitFailure)) {
		sec->Header = img->Header;
		sec->HeaderN.x = 1;
		mrcInit(sec, NULL);
		for(iy=0; iy<img->HeaderN.y; iy++) {
			for(iz=0; iz<img->HeaderN.z; iz++) {
				mrcPixelDataGet(img, 
					(mrcImageParaTypeReal)X, 
					(mrcImageParaTypeReal)iy, 
					(mrcImageParaTypeReal)iz, 
					&data, mrcPixelRePart, mrcPixelHowNearest);
				mrcPixelDataSet(sec, 
					0.0, 
					(mrcImageParaTypeReal)iy, 
					(mrcImageParaTypeReal)iz, 
					data, mrcPixelRePart); 
			}
		}
	} else if(IsFT(img, "lmrcImageXSection", mrcStatusMask_ExitFailure)) {
		sec->Header    = img->Header;
		sec->HeaderN.x = 1;
		sec->HeaderMode = mrcFloatImage;
		mrcInit(sec, NULL);
		for(iy=-img->HeaderN.y/2; iy<img->HeaderN.y/2; iy++) {
			for(iz=-img->HeaderN.z/2.0; iz<img->HeaderN.z/2.0; iz++) {
				mrcPixelDataGet(img, 
					(mrcImageParaTypeReal)X, 
					(mrcImageParaTypeReal)iy, 
					(mrcImageParaTypeReal)iz, 
					&data, mrcPixelMag, mrcPixelHowNearest);
				mrcPixelDataSet(sec, 
					0.0, 
					(mrcImageParaTypeReal)iy+img->HeaderN.y/2.0,
					(mrcImageParaTypeReal)iz+img->HeaderN.z/2.0,
					data, mrcPixelRePart); 
			}
		}
	} else {
		fprintf(stderr, "Not Supported Mode: %d\n", img->HeaderMode);
	}
	mrcStatDataSet(sec, 0);
}

void
lmrcImageXProjection(mrcImage* proj, mrcImage* img)
{
    mrcImageParaTypeInteger ix, iy, iz;
    double data, sum;

	if(IsImage(img, "lmrcImageXProjection", mrcStatusMask_ExitFailure)) {
		proj->Header = img->Header;
		proj->HeaderN.y = proj->HeaderN.z = 1;
		mrcInit(proj, NULL);
		for(ix=0; ix<img->HeaderN.x; ix++) {
				sum = 0.0;
				for(iy=0; iy<img->HeaderN.y; iy++) {
						for(iz=0; iz<img->HeaderN.z; iz++) {
								mrcPixelDataGet(img, 
														   (mrcImageParaTypeReal)ix, 
														   (mrcImageParaTypeReal)iy, 
														   (mrcImageParaTypeReal)iz, 
														   &data, mrcPixelRePart, mrcPixelHowNearest);
								sum += data;
						}
				}
				mrcPixelDataSet(proj, (mrcImageParaTypeReal)ix, 0.0, 0.0, 
												sum, mrcPixelRePart); 
		}
	} else if(IsFT(img, "lmrcImageYProjection", mrcStatusMask_ExitFailure)) {
		proj->Header = img->Header;
		proj->HeaderN.y = proj->HeaderN.z = 1;
		proj->HeaderMode = mrcFloatImage;
		mrcInit(proj, NULL);
		for(ix=-img->HeaderN.x/2.0; ix<img->HeaderN.x/2.0; ix++) {
				sum = 0.0;
				for(iy=-img->HeaderN.y/2.0; iy<img->HeaderN.y/2.0; iy++) {
						for(iz=-img->HeaderN.z/2.0; iz<img->HeaderN.z/2.0; iz++) {
								mrcPixelDataGet(img, 
														   (mrcImageParaTypeReal)ix, 
														   (mrcImageParaTypeReal)iy, 
														   (mrcImageParaTypeReal)iz, 
														   &data, mrcPixelMag, mrcPixelHowNearest);
								sum += data;
						}
				}
				mrcPixelDataSet(proj, (mrcImageParaTypeReal)ix+img->HeaderN.x/2.0, 0.0, 0.0, 
												sum, mrcPixelRePart); 
		}
	}
	mrcStatDataSet(proj, 0);
}

void
lmrcImageYProjection(mrcImage* proj, mrcImage* img)
{
    mrcImageParaTypeInteger ix, iy, iz;
    double data, sum;

	if(IsImage(img, "lmrcImageYProjection", mrcStatusMask_ExitFailure)) {
    	proj->Header = img->Header;
    	proj->HeaderN.z = proj->HeaderN.x = 1;
    	mrcInit(proj, NULL);
    	for(iy=0; iy<img->HeaderN.y; iy++) {
       		sum = 0.0;
        	for(iz=0; iz<img->HeaderN.z; iz++) { 
           		for(ix=0; ix<img->HeaderN.x; ix++) {
                	mrcPixelDataGet(img, 
                               (mrcImageParaTypeReal)ix, 
                               (mrcImageParaTypeReal)iy, 
                               (mrcImageParaTypeReal)iz, 
                               &data, mrcPixelRePart, mrcPixelHowNearest);
                	sum += data;
            	}
        	}
        	mrcPixelDataSet(proj, 0.0, (mrcImageParaTypeReal)iy, 0.0, 
                        sum, mrcPixelRePart); 
		}
	} else if(IsFT(img, "lmrcImageYProjection", mrcStatusMask_ExitFailure)) {
		DEBUGPRINT("FT\n");		
    	proj->Header = img->Header;
    	proj->HeaderN.z = proj->HeaderN.x = 1;
		proj->HeaderMode = mrcFloatImage;
    	mrcInit(proj, NULL);
    	for(iy=-img->HeaderN.y/2; iy<img->HeaderN.y/2; iy++) {
       		sum = 0.0;
        	for(iz=-img->HeaderN.z/2; iz<MAX(img->HeaderN.z/2,1) ; iz++) { 
           		for(ix=0; ix<=img->HeaderN.x/2; ix++) {
                	mrcPixelDataGet(img, 
                               (mrcImageParaTypeReal)ix, 
                               (mrcImageParaTypeReal)iy, 
                               (mrcImageParaTypeReal)iz, 
                               &data, mrcPixelMag, mrcPixelHowNearest);
                	sum += data;
            	}
        	}
        	mrcPixelDataSet(proj, 0.0, (mrcImageParaTypeReal)(iy+img->HeaderN.y/2), 0.0, 
                        sum, mrcPixelRePart); 
		}

	} else {
		fprintf(stderr, "Not supported mode: %d in lmrcImageYProjection\n", img->HeaderMode);
		exit(EXIT_FAILURE);
	}
	mrcStatDataSet(proj, 0);
}

void
lmrcImageZProjection(mrcImage* proj, mrcImage* img)
{
    mrcImageParaTypeInteger ix, iy, iz;
    double data, sum;

	IsImage(img, "lmrcImageZProjection", mrcStatusMask_ExitFailure);
    proj->Header = img->Header;
    proj->HeaderN.x = proj->HeaderN.y = 1;
    mrcInit(proj, NULL);
    for(iz=0; iz<img->HeaderN.z; iz++) {
		sum = 0.0;
        for(ix=0; ix<img->HeaderN.x; ix++) { 
            for(iy=0; iy<img->HeaderN.y; iy++) {
                mrcPixelDataGet(img, 
                               (mrcImageParaTypeReal)ix, 
                               (mrcImageParaTypeReal)iy, 
                               (mrcImageParaTypeReal)iz, 
                               &data, mrcPixelRePart, mrcPixelHowNearest);
                sum += data;
            }
        }
        mrcPixelDataSet(proj, 0.0, 0.0, (mrcImageParaTypeReal)iz,
                        sum, mrcPixelRePart); 
    }
	mrcStatDataSet(proj, 0);
}

void
lmrcImageXYProjection(mrcImage* proj, mrcImage* img)
{
	mrcImageParaTypeInteger ix, iy, iz;
	double data, sum;


	IsImage(img, "lmrcImageXYProjection", mrcStatusMask_ExitFailure);
    proj->Header = img->Header;
    proj->HeaderN.z = 1;
    mrcInit(proj, NULL);
    for(ix=0; ix<img->HeaderN.x; ix++) {
        for(iy=0; iy<img->HeaderN.y; iy++) {
			sum = 0.0;
            for(iz=0; iz<img->HeaderN.z; iz++) {
                mrcPixelDataGet(img, 
                               (mrcImageParaTypeReal)ix, 
                               (mrcImageParaTypeReal)iy, 
                               (mrcImageParaTypeReal)iz, 
                               &data, mrcPixelRePart, mrcPixelHowNearest);
                sum += data;
            }
        	mrcPixelDataSet(proj, (mrcImageParaTypeReal)ix, (mrcImageParaTypeReal)iy, 0.0, 
           		             sum, mrcPixelRePart); 
		}
    }
}

void
lmrcImageYZProjection(mrcImage* proj, mrcImage* img)
{
	mrcImageParaTypeInteger ix, iy, iz;
	double data, sum;


	IsImage(img, "lmrcImageXYProjection", mrcStatusMask_ExitFailure);
    proj->Header = img->Header;
    proj->HeaderN.z = 1;
    mrcInit(proj, NULL);
    for(iy=0; iy<img->HeaderN.y; iy++) {
        for(iz=0; iz<img->HeaderN.z; iz++) {
			sum = 0.0;
            for(ix=0; ix<img->HeaderN.x; ix++) {
                mrcPixelDataGet(img, 
                               (mrcImageParaTypeReal)ix, 
                               (mrcImageParaTypeReal)iy, 
                               (mrcImageParaTypeReal)iz, 
                               &data, mrcPixelRePart, mrcPixelHowNearest);
                sum += data;
            }
        	mrcPixelDataSet(proj, (mrcImageParaTypeReal)iy, (mrcImageParaTypeReal)iz, 0.0,
           		             sum, mrcPixelRePart); 
		}
    }
}

void
lmrcImageZXProjection(mrcImage* proj, mrcImage* img)
{
	mrcImageParaTypeInteger ix, iy, iz;
	double data, sum;


	IsImage(img, "lmrcImageXYProjection", mrcStatusMask_ExitFailure);
    proj->Header = img->Header;
    proj->HeaderN.z = 1;
    mrcInit(proj, NULL);
    for(iz=0; iz<img->HeaderN.z; iz++) {
        for(ix=0; ix<img->HeaderN.x; ix++) {
			sum = 0.0;
            for(iy=0; iy<img->HeaderN.y; iy++) {
                mrcPixelDataGet(img, 
                               (mrcImageParaTypeReal)ix, 
                               (mrcImageParaTypeReal)iy, 
                               (mrcImageParaTypeReal)iz, 
                               &data, mrcPixelRePart, mrcPixelHowNearest);
                sum += data;
            }
        	mrcPixelDataSet(proj, (mrcImageParaTypeReal)iz, (mrcImageParaTypeReal)ix, 0.0,
           		             sum, mrcPixelRePart); 
		}
    }
}

/*
	Weight 
*/

void
lmrcImageHistgram5(double** hist, unsigned long nlevel, double Low, double High, mrcImage* img)
{
	mrcImage tmp;

	tmp = *img;
	tmp.HeaderAMin = Low;
	tmp.HeaderAMax = High;
	lmrcImageHistgram(hist, nlevel, &tmp);
}

void
lmrcImageHistgram2(double** hist, double delta, mrcImage* img)
{
	unsigned long n;
	n = (unsigned long)((img->HeaderAMax - img->HeaderAMin)/delta + 0.5 + 1);
	lmrcImageHistgram(hist, n, img);	
}

void
lmrcImageHistgram(double** hist, unsigned long nlevel, mrcImage* img)
{
    long i;
    mrcImageParaTypeInteger ix, iy, iz;
    double data;
    double max;
    unsigned long* lhist;
	int index;

	lhist = (unsigned long*)memoryAllocate(sizeof(unsigned long)*nlevel, "in lmrcImageHistgram");	
	*hist = (double*)memoryAllocate(sizeof(double)*nlevel, "in lmrcImageHistgram");	

    for(i=0; i<nlevel; i++) {
        lhist[i] = 0;
        (*hist)[i] = 0;
    }

	if(IsImage(img, "in lmrcImageHistgram", 0)) {
    	for(ix=0; ix<img->HeaderN.x; ix++) {
       		for(iy=0; iy<img->HeaderN.y; iy++) {
            	for(iz=0; iz<img->HeaderN.z; iz++) {
                	mrcPixelDataGet(img, (mrcImageParaTypeReal)ix, (mrcImageParaTypeReal)iy, (mrcImageParaTypeReal)iz, 
						&data, mrcPixelMag, mrcPixelHowNearest);
					index = (unsigned long)((data-img->HeaderAMin)/(img->HeaderAMax-img->HeaderAMin)*(nlevel-1)+0.5);
					if(index<0) {
						index = 0;
					} else if(nlevel<=index) {
						index = nlevel - 1;
					}
                	lhist[index]++;
           		}
			}
        }
    } else if(IsFT(img, "in lmrcImageHistgram", 0)) {
    	for(ix=0; ix<=img->HeaderN.x/2.0; ix++) {
       		for(iy=-img->HeaderN.y/2.0; iy<img->HeaderN.y/2.0; iy++) {
       			for(iz=-img->HeaderN.z/2.0; iz<img->HeaderN.z/2.0; iz++) {
                	mrcPixelDataGet(img, (mrcImageParaTypeReal)ix, (mrcImageParaTypeReal)iy, (mrcImageParaTypeReal)iz, 
						&data, mrcPixelMag, mrcPixelHowNearest);
					index = (unsigned long)((data-img->HeaderAMin)/(img->HeaderAMax-img->HeaderAMin)*(nlevel-1)+0.5);
					if(index<0) {
						index = 0;
					} else if(nlevel<=index) {
						index = nlevel - 1;
					}
                	lhist[index]++;
           		}
			}
        }
	}

    max = lhist[1];
    for(i=1; i<nlevel-1; i++) {
        if(max<lhist[i]) {
            max = lhist[i];
        }
    }
	if(0.0==max) {
		max = MAX(lhist[0], lhist[nlevel-1]);	
	}
	if(0.0==max) {
    	for(i=0; i<nlevel; i++) {
       		(*hist)[i] = lhist[i];
    	}
	} else {
    	for(i=0; i<nlevel; i++) {
       		(*hist)[i] = lhist[i]/max;
    	}
	}
    free(lhist);
}

/*
	Count
*/

void
lmrcImageHistgram6(double** hist, double delta, double Low, double High, mrcImage* img)
{
	mrcImage tmp;
    unsigned int nLevel;
	tmp = *img;
	tmp.HeaderAMin = Low;
	tmp.HeaderAMax = High;
    nLevel = (int)((High-Low)/delta + 1);
    DEBUGPRINT3("%f %f %d\n", High, Low, nLevel);
	lmrcImageHistgram3(hist, nLevel, &tmp);	
}

void
lmrcImageHistgram4(double** hist, double delta, mrcImage* img)
{
	unsigned long n;
	n = (unsigned long)((img->HeaderAMax - img->HeaderAMin)/delta + 0.5 + 1);
	lmrcImageHistgram3(hist, n, img);
}

void
lmrcImageHistgram3(double** hist, unsigned long nlevel, mrcImage* img)
{
    long i;
    mrcImageParaTypeInteger ix, iy, iz;
    double data;
    double max;
    unsigned long* lhist;
	int index;

	lhist = (unsigned long*)memoryAllocate(sizeof(unsigned long)*nlevel, "in lmrcImageHistgram");	
	*hist = (double*)memoryAllocate(sizeof(double)*nlevel, "in lmrcImageHistgram");	

    for(i=0; i<nlevel; i++) {
        lhist[i] = 0;
        (*hist)[i] = 0;
    }

	if(IsImage(img, "in lmrcImageHistgram", 0)) {
    	for(ix=0; ix<img->HeaderN.x; ix++) {
       		for(iy=0; iy<img->HeaderN.y; iy++) {
            	for(iz=0; iz<img->HeaderN.z; iz++) {
                	mrcPixelDataGet(img, (mrcImageParaTypeReal)ix, (mrcImageParaTypeReal)iy, (mrcImageParaTypeReal)iz, 
						&data, mrcPixelMag, mrcPixelHowNearest);
					index = (unsigned long)((data-img->HeaderAMin)/(img->HeaderAMax-img->HeaderAMin)*(nlevel-1)+0.5);
					if(index<0) {
						index = 0;
					} else if(nlevel<=index) {
						index = nlevel - 1;
					}
                	lhist[index]++;
           		}
			}
        }
    } else if(IsFT(img, "in lmrcImageHistgram", 0)) {
    	for(ix=0; ix<=img->HeaderN.x/2.0; ix++) {
       		for(iy=-img->HeaderN.y/2.0; iy<img->HeaderN.y/2.0; iy++) {
       			for(iz=-img->HeaderN.z/2.0; iz<img->HeaderN.z/2.0; iz++) {
                	mrcPixelDataGet(img, (mrcImageParaTypeReal)ix, (mrcImageParaTypeReal)iy, (mrcImageParaTypeReal)iz, 
						&data, mrcPixelMag, mrcPixelHowNearest);
					index = (unsigned long)((data-img->HeaderAMin)/(img->HeaderAMax-img->HeaderAMin)*(nlevel-1)+0.5);
					if(index<0) {
						index = 0;
					} else if(nlevel<=index) {
						index = nlevel - 1;
					}
                	lhist[index]++;
           		}
			}
        }
	}

    max = lhist[0];
    for(i=0; i<nlevel; i++) {
        if(max<lhist[i]) {
            max = lhist[i];
        }
    }
    for(i=0; i<nlevel; i++) {
        (*hist)[i] = lhist[i];
    }
    free(lhist);
}

void
lmrcImageInformation(mrcImageInformation* info, mrcImage* img)
{
    mrcImageParaTypeInteger ix, iy, iz;
    double data;
	double sumForMean, sumForSd, sum;
	double sumForSphereSurface, sdForSphereSurface;
	double sumForCylinderSurface, sdForCylinderSurface;
	double max, min;
	float phi, theta; 
	float rmax; 
	double count;
	mrcImageParaTypeReal offsetx, offsety, offsetz; 
	mrcImageParaTypeReal sftx, sfty, sftz; 
	mrcImageParaTypeReal dstx, dsty, dstz; 

	switch(info->mode){
		case meanOfAll:{
			DEBUGPRINT("meanOfAll\n");

    		mrcPixelDataGet(img, (mrcImageParaTypeReal)0, (mrcImageParaTypeReal)0, (mrcImageParaTypeReal)0, 
											&data, mrcPixelMag, mrcPixelHowNearest);
			min = max = data;
			info->minCoord.x = info->minCoord.y = info->minCoord.z = 0;
			info->maxCoord.x = info->maxCoord.y = info->maxCoord.z = 0;
  			sumForMean = sumForSd = 0;
   			for(iz=0; iz<img->HeaderN.z; iz++) {
       		for(iy=0; iy<img->HeaderN.y; iy++) {
          	for(ix=0; ix<img->HeaderN.x; ix++) {
            	mrcPixelDataGet(img, (mrcImageParaTypeReal)ix, (mrcImageParaTypeReal)iy, (mrcImageParaTypeReal)iz, 
									&data, mrcPixelMag, mrcPixelHowNearest);
               	if(min>data)  {
					min=data;
					info->minCoord.x = ix;
					info->minCoord.y = iy;
					info->minCoord.z = iz;
				}
           		if(max<data) {
					max=data;
					info->maxCoord.x = ix;
					info->maxCoord.y = iy;
					info->maxCoord.z = iz;
				}
           		sumForMean += data;
             	sumForSd   += (data*data);
           	}
       		}
   			}
 			info->min = min;
			info->max = max;
			info->mean = sumForMean/(img->HeaderN.x*img->HeaderN.y*img->HeaderN.z);
			info->rootMeanSquare = sqrt(sumForSd/(img->HeaderN.x*img->HeaderN.y*img->HeaderN.z)); 
			info->sd   = sqrt(sumForSd/(img->HeaderN.x*img->HeaderN.y*img->HeaderN.z) - info->mean*info->mean);
			info->se   = info->sd/sqrt((double)img->HeaderN.x*img->HeaderN.y*img->HeaderN.z);
			DEBUGPRINT4("Max: %g at (%d, %d, %d)\n", info->max, 
						(int)info->maxCoord.x, (int)info->maxCoord.y, (int)info->maxCoord.z);
			DEBUGPRINT4("Min: %g at (%d, %d, %d)\n", info->min, 
						(int)info->minCoord.x, (int)info->minCoord.y, (int)info->minCoord.z);
			break;
		}
		case meanOfCentre: {
			int cx;
			int cy;
			int cz;
			int count;
			int xmin, ymin, zmin;
			int xmax, ymax, zmax;
			DEBUGPRINT("meanOfAll\n");
	
			if(info->flagCentre) {
				cx = info->CentreX;
				cy = info->CentreY;
				cz = info->CentreZ;
			} else {
				cx = img->HeaderN.x/2;
				cy = img->HeaderN.y/2;
				cz = img->HeaderN.z/2;
			}
    		mrcPixelDataGet(img, 
				(mrcImageParaTypeReal)cx, 
				(mrcImageParaTypeReal)cy, 
				(mrcImageParaTypeReal)cz, 
				&data, mrcPixelMag, mrcPixelHowNearest);
			min = max = data;
			info->minCoord.x = cx;
			info->minCoord.y = cy;
			info->minCoord.z = cz;
			info->maxCoord.x = cx;
			info->maxCoord.y = cy;
			info->maxCoord.z = cz;
  			sumForMean = sumForSd = 0;

			if(info->flagXrange) {
				xmin = info->XrangeMin;	
				xmax = info->XrangeMax;	
			} else {
				xmin = -32;
				xmax = +32;
			}

			if(info->flagYrange) {
				ymin = info->YrangeMin;	
				ymax = info->YrangeMax;	
			} else {
				ymin = -32;
				ymax = +32;
			}

			if(info->flagZrange) {
				zmin = info->ZrangeMin;
				zmax = info->ZrangeMax;
			} else {
				zmin = -32;
				zmax = +32;
			}

			count=0;
   			for(iz=cz+zmin; iz<cz+zmax; iz++) {
   			for(iy=cy+ymin; iy<cy+ymax; iy++) {
   			for(ix=cx+xmin; ix<cx+xmax; ix++) {
				count++;
            	mrcPixelDataGet(img, (mrcImageParaTypeReal)ix, (mrcImageParaTypeReal)iy, (mrcImageParaTypeReal)iz, 
											&data, mrcPixelMag, mrcPixelHowNearest);
               	if(min>data)  {
					min=data;
					info->minCoord.x = ix;
					info->minCoord.y = iy;
					info->minCoord.z = iz;
				}
           		if(max<data) {
					max=data;
					info->maxCoord.x = ix;
					info->maxCoord.y = iy;
					info->maxCoord.z = iz;
				}
           		sumForMean += data;
             	sumForSd   += (data*data);
           	}
       		}
   			}
 			info->min = min;
			info->max = max;
			info->mean = sumForMean/count;
			info->rootMeanSquare = sqrt(sumForSd/count); 
			info->sd   = sqrt(sumForSd/count - info->mean*info->mean);
			info->se   = info->sd/sqrt(count);
			DEBUGPRINT4("Max: %g at (%d, %d, %d)\n", info->max, 
						(int)info->maxCoord.x, (int)info->maxCoord.y, (int)info->maxCoord.z);
			DEBUGPRINT4("Min: %g at (%d, %d, %d)\n", info->min, 
						(int)info->minCoord.x, (int)info->minCoord.y, (int)info->minCoord.z);
			break;
		}
		case meanOfSparse: {
			int dx;
			int dy;
			int dz;
			int count;
			DEBUGPRINT("meanOfSparse\n");
		
			dx = MAX(1,img->HeaderN.x/64);
			dy = MAX(1,img->HeaderN.y/64);
			dz = MAX(1,img->HeaderN.z/64);
    		mrcPixelDataGet(img, 
				(mrcImageParaTypeReal)0, 
				(mrcImageParaTypeReal)0, 
				(mrcImageParaTypeReal)0, 
				&data, mrcPixelMag, mrcPixelHowNearest);
			min = max = data;
			info->minCoord.x = 0;
			info->minCoord.y = 0;
			info->minCoord.z = 0;
			info->maxCoord.x = 0;
			info->maxCoord.y = 0;
			info->maxCoord.z = 0;
  			sumForMean = sumForSd = 0;
			count=0;
   			for(ix=0; ix<img->HeaderN.x; ix+=dx) {
   			for(iy=0; iy<img->HeaderN.y; iy+=dy) {
   			for(iz=0; iz<img->HeaderN.z; iz+=dz) {
				count++;
            	mrcPixelDataGet(img, (mrcImageParaTypeReal)ix, (mrcImageParaTypeReal)iy, (mrcImageParaTypeReal)iz, 
											&data, mrcPixelMag, mrcPixelHowNearest);
               	if(min>data)  {
					min=data;
					info->minCoord.x = ix;
					info->minCoord.y = iy;
					info->minCoord.z = iz;
				}
           		if(max<data) {
					max=data;
					info->maxCoord.x = ix;
					info->maxCoord.y = iy;
					info->maxCoord.z = iz;
				}
           		sumForMean += data;
             	sumForSd   += (data*data);
           	}
       		}
   			}
 			info->min = min;
			info->max = max;
			info->mean = sumForMean/count;
			info->rootMeanSquare = sqrt(sumForSd/count); 
			info->sd   = sqrt(sumForSd/count - info->mean*info->mean);
			info->se   = info->sd/sqrt(count);
			DEBUGPRINT4("Max: %g at (%d, %d, %d)\n", info->max, 
						(int)info->maxCoord.x, (int)info->maxCoord.y, (int)info->maxCoord.z);
			DEBUGPRINT4("Min: %g at (%d, %d, %d)\n", info->min, 
						(int)info->minCoord.x, (int)info->minCoord.y, (int)info->minCoord.z);
			break;
		}
		case meanOfCylinderSurface:{
			DEBUGPRINT("meanOfCylinderSurface\n");
			offsetx = floor ((img->HeaderN.x-1)/2); /* PIXEL */
			offsety = floor ((img->HeaderN.y-1)/2); /* PIXEL */ 
			offsetz = floor ((img->HeaderN.z-1)/2); /* PIXEL */
			count = 0;
	   		sumForCylinderSurface = 0;
	   		sdForCylinderSurface  = 0;
	
			rmax = MIN(offsetx*img->HeaderLength.x, offsety*img->HeaderLength.y);
			if (info->flagrmax){
				if(info->rmax<rmax){
					fprintf(stderr,"rmax from option:%f\n",info->rmax);
				}else{
					info->rmax = rmax;	/* A */
					fprintf(stderr,"Your selected rmax is beyond range.  The rmax changes to caliculated rmax:%f\n"
							,info->rmax);
				}
			}else{
				info->rmax = rmax;
				fprintf(stderr,"rmax from caliculate:%f\n",info->rmax);
			}
			if(IsEven(img->HeaderN.x)){
				fprintf(stderr, "HeaderNx should be odd\n");
			}
			if(IsEven(img->HeaderN.y)){
				fprintf(stderr, "HeaderNy should be odd\n");
			}
	
   		 	for(iz=0; iz<img->HeaderN.z; iz++) {
   		 		for(phi=0; phi<2*M_PI; phi+=M_PI/360) {
					sftx = info->rmax * cos (phi) / img->HeaderLength.x; /* PIXEL */
					sfty = info->rmax * sin (phi) / img->HeaderLength.y;
					sftz = iz;
					dstx = offsetx + sftx; /* PIXEL */
					dsty = offsety + sfty;
					dstz = offsetz + sftz;
   		         	mrcPixelDataGet(img, (mrcImageParaTypeReal)dstx, 
										 (mrcImageParaTypeReal)dsty, 
										 (mrcImageParaTypeReal)dstz, 
										 &data, mrcPixelRePart, mrcPixelHowCubicConv);
					DEBUG2PRINT4("(x,y,z)=(%15.6f, %15.6f, %15.6f) data:%15.6f\n",
									   	 (mrcImageParaTypeReal)dstx, 
										 (mrcImageParaTypeReal)dsty, 
										 (mrcImageParaTypeReal)dstz,
										 data);
  					sumForCylinderSurface += data;
  					sdForCylinderSurface  += SQR(data);
					count++;
				}
			}
			DEBUGPRINT2("sumForCylinderSurface: %15.6f cout: %15.6f\n", sumForCylinderSurface, count);
			info->meanOfCylinderSurface = sumForCylinderSurface/count;
			info->sdOfCylinderSurface   = sqrt(sdForCylinderSurface/count - SQR(info->meanOfCylinderSurface));
			info->seOfCylinderSurface   = info->sdOfCylinderSurface/ sqrt(count);
			fprintf(stderr, "meanOfCylinderSurface %g at rmax %g[A]\n", 
						info->meanOfCylinderSurface, info->rmax);
			break;
		}
		case meanOfSphereSurface:{
			DEBUGPRINT("meanOfSphereSurface\n");
			count = 0;	
 		   	sumForSphereSurface = 0;

			offsetx = floor ((img->HeaderN.x-1)/2); /* PIXEL */
			offsety = floor ((img->HeaderN.y-1)/2); /* PIXEL */ 
			
			if(1<img->HeaderN.z) {
				offsetz = floor ((img->HeaderN.z-1)/2); /* PIXEL */
				rmax = MIN3(offsetx*img->HeaderLength.x,
							offsety*img->HeaderLength.y,
							offsetz*img->HeaderLength.z);
			} else {
				offsetz = 0;
				rmax = MIN(offsetx*img->HeaderLength.x, 
						offsety*img->HeaderLength.y);
			}
			if (info->flagrmax){
				if(info->rmax<rmax){
					fprintf(stderr,"rmax from option:%f\n",info->rmax);
				}else{
					info->rmax = rmax;	/* A */
					fprintf(stderr,"Your selected rmax is beyond range.  The rmax changes to caliculated rmax:%f\n"
							,info->rmax);
				}
			}else{
				info->rmax = rmax;
				fprintf(stderr,"rmax from caliculate:%f\n",info->rmax);
			}
			if(IsEven(img->HeaderN.x)){
				fprintf(stderr, "HeaderNx should be odd\n");
			}
			if(IsEven(img->HeaderN.y)){
				fprintf(stderr, "HeaderNy should be odd\n");
			}
			if(IsEven(img->HeaderN.z)){
				fprintf(stderr, "HeaderNz should be odd\n");
			}
	
   		 	for(theta=0; theta<M_PI; theta+=M_PI/360) {
   		 		for(phi=0; phi<2*M_PI; phi+=M_PI/360) {
					sftx = info->rmax * sin (theta) * cos (phi) / img->HeaderLength.x; /* PIXEL */
					sfty = info->rmax * sin (theta) * sin (phi) / img->HeaderLength.y;
					sftz = info->rmax * cos (theta) / img->HeaderLength.z;
					dstx = offsetx + sftx; /* PIXEL */
					dsty = offsety + sfty;
					dstz = offsetz + sftz;
   		         	mrcPixelDataGet(img, (mrcImageParaTypeReal)dstx, 
										 (mrcImageParaTypeReal)dsty, 
										 (mrcImageParaTypeReal)dstz, 
										 &data, mrcPixelRePart, mrcPixelHowCubicConv);
					DEBUG2PRINT4("(x,y,z)=(%15.6f, %15.6f, %15.6f) data:%15.6f\n",
									   	 (mrcImageParaTypeReal)dstx, 
										 (mrcImageParaTypeReal)dsty, 
										 (mrcImageParaTypeReal)dstz,
										 data);
  					sumForSphereSurface += data;
  					sdForSphereSurface  += SQR(data);
					count++;
				}
			}
			info->meanOfSphereSurface = sumForSphereSurface / count;
			info->sdOfSphereSurface   = sqrt(sdForSphereSurface/count - SQR(info->meanOfSphereSurface));
			info->seOfSphereSurface   = info->sdOfSphereSurface/sqrt(count);
			fprintf(stderr, "meanOfSphereSurface %g at rmax %g[A]\n", 
						info->meanOfSphereSurface, info->rmax);

			break;
		}		
		case meanOfEdge: {
			DEBUGPRINT("meanOfEdge\n");
			sumForMean = sumForSd = 0;
			count = 0;
          	for(iz=0; iz<img->HeaderN.z; iz++) {
       		for(iy=0; iy<img->HeaderN.y; iy++) {
   			for(ix=0; ix<img->HeaderN.x; ix++) {
				if((img->HeaderN.x!=1 && (ix==0 || ix==img->HeaderN.x-1))
				|| (img->HeaderN.y!=1 && (iy==0 || iy==img->HeaderN.y-1))
				|| (img->HeaderN.z!=1 && (iz==0 || iz==img->HeaderN.z-1))) {
             		mrcPixelDataGet(img, 
						(mrcImageParaTypeReal)ix, 
						(mrcImageParaTypeReal)iy, 
						(mrcImageParaTypeReal)iz, 
						&data, mrcPixelRePart, mrcPixelHowNearest);
           			sumForMean += data;
             		sumForSd   += (data*data);
					count++;
				}
           	}
       		}
   			}
			if(0<count) {
				info->meanOfEdge = sumForMean/count;
				info->sdOfEdge   = sqrt(sumForSd/count - SQR(info->meanOfEdge));
				info->seOfEdge   = info->sdOfEdge/sqrt(count);
			} else {
				fprintf(stderr, "pixel number %f for edge\n", count); 
				exit(EXIT_FAILURE);
			}
			break;
		}		
		case meanOf2DEdgeY: {
			DEBUGPRINT("meanOf2DEdgeY\n");
			sumForMean = sumForSd = 0;
			count = 0;
       		for(iy=0; iy<img->HeaderN.y; iy++) {
   			for(ix=0; ix<img->HeaderN.x; ix+=(img->HeaderN.x-1)) {
             	mrcPixelDataGet(img, 
					(mrcImageParaTypeReal)ix, 
					(mrcImageParaTypeReal)iy, 
					(mrcImageParaTypeReal)0, 
					&data, mrcPixelRePart, mrcPixelHowNearest);
           		sumForMean += data;
             	sumForSd   += (data*data);
				count++;
           	}
       		}
			if(0<count) {
				info->meanOfEdge = sumForMean/count;
				info->sdOfEdge   = sqrt(sumForSd/count - SQR(info->meanOfEdge));
				info->seOfEdge   = info->sdOfEdge/sqrt(count);
			} else {
				fprintf(stderr, "pixel number %f for edge\n", count); 
				exit(EXIT_FAILURE);
			}
			break;
		}		
		case RMSofAllPixels: {
			DEBUGPRINT("RMSofAllPixels\n");
			info->RMS = 0;
			count = 0;
			sum = 0;
          	for(iz=0; iz<img->HeaderN.z; iz++) {
       		for(iy=0; iy<img->HeaderN.y; iy++) {
   			for(ix=0; ix<img->HeaderN.x; ix++) {
             	mrcPixelDataGet(img, 
					(mrcImageParaTypeReal)ix, 
					(mrcImageParaTypeReal)iy, 
					(mrcImageParaTypeReal)iz, 
					&data, mrcPixelRePart, mrcPixelHowNearest);
           		sum += data*data;
				count++;
           	}
       		}
   			}
			info->RMS = sqrt(sum/count);

			break;
		}
		case sdOfAllAxis: {
			DEBUGPRINT("SDofAllAxis\n");
			double weight, weight2;
			double sumx, sumy, sumz;	
			double avex, avey, avez;	
			double dat2;

			sumx = 0;
			sumy = 0;
			sumz = 0;
			weight = 0;
			count = img->HeaderN.x*img->HeaderN.y*img->HeaderN.z;
          	for(iz=0; iz<img->HeaderN.z; iz++) {
       		for(iy=0; iy<img->HeaderN.y; iy++) {
   			for(ix=0; ix<img->HeaderN.x; ix++) {
             	mrcPixelDataGet(img, 
					(mrcImageParaTypeReal)ix, 
					(mrcImageParaTypeReal)iy, 
					(mrcImageParaTypeReal)iz, 
					&data, mrcPixelRePart, mrcPixelHowNearest);
				sumx += ix*data;
				sumy += iy*data;
				sumz += iz*data;
				weight += data;
           	}
       		}
   			}

			avex = sumx/weight;
			avey = sumy/weight;
			avez = sumz/weight;

			sumx = 0;
			sumy = 0;
			sumz = 0;
			weight2 = 0;
          	for(iz=0; iz<img->HeaderN.z; iz++) {
       		for(iy=0; iy<img->HeaderN.y; iy++) {
   			for(ix=0; ix<img->HeaderN.x; ix++) {
             	mrcPixelDataGet(img, 
					(mrcImageParaTypeReal)ix, 
					(mrcImageParaTypeReal)iy, 
					(mrcImageParaTypeReal)iz, 
					&data, mrcPixelRePart, mrcPixelHowNearest);
				sumx += SQR((ix - avex)*data);
				sumy += SQR((iy - avey)*data);
				sumz += SQR((iz - avez)*data);
           	}
       		}
   			}

			info->sdOfAllAxis.x = sqrt(sumx/weight);
			info->sdOfAllAxis.y = sqrt(sumy/weight);
			info->sdOfAllAxis.z = sqrt(sumz/weight);
			info->aveOfAllAxis.x = avex; 
			info->aveOfAllAxis.y = avey; 
			info->aveOfAllAxis.z = avez; 
			break;
		}
        case meanOfHighValueArea: {
            int N, i, thres, med;
            double* sort;
            double sum, n;

            N = img->HeaderN.x*img->HeaderN.y*img->HeaderN.z;
            thres = N*(double)info->thresHigh;
            med   = (N-1 + thres)/2.0;
            //DEBUGPRINT3("N %d thres %d med %d\n", N, thres, med);
            sort = (double*)memoryAllocate(sizeof(double)*N, "in mrcImageInfo");
            lmrcImagePixelValueSort(sort, img, 0);
            info->thresOfHighValueArea = sort[thres];
            info->maxOfHighValueArea = sort[N-1];
            info->minOfHighValueArea = sort[thres];
            info->medianOfHighValueArea = sort[med];
            //DEBUGPRINT5("thres %d thresHigh %f thresVal %f max %f min %f\n", thres, info->thresHigh, sort[thres], info->maxOfHighValueArea, info->minOfHighValueArea);
            //DEBUGPRINT6("N %d thres %d med %d value value  %f %f %f \n", N, thres, med, sort[thres], sort[med], sort[N-1]); 
            n = 0;
            sum = 0;
            for(i=thres; i<N; i++) {
                sum += sort[i]; 
                n++;
            }
            info->meanOfHighValueArea = sum/n;

            sum = 0;
            for(i=thres; i<N; i++) {
                sum += SQR( sort[i] - info->meanOfHighValueArea); 
            }
            info->sdOfHighValueArea = sqrt(sum/n);
            info->seOfHighValueArea = sqrt(sum/n)/sqrt(n);
            break;
        }
        case meanOfLowValueArea: {
            int N, i, thres, med;
            double* sort;
            double sum, n;

            N = img->HeaderN.x*img->HeaderN.y*img->HeaderN.z;
            thres = N*info->thresLow;
            med   = thres/2.0;
            sort = (double*)memoryAllocate(sizeof(double)*N, "in mrcImageInfo");
            lmrcImagePixelValueSort(sort, img, 0);
            info->thresOfLowValueArea = sort[thres];
            info->maxOfLowValueArea = sort[thres];
            info->minOfLowValueArea = sort[0];
            info->medianOfLowValueArea = sort[med];
            n = 0;
            //DEBUGPRINT2("thresLow %f %f\n", info->thresLow, sort[thres]); 
            //DEBUGPRINT6("N %d thres %d med %d  %f %f %f \n", N, thres, med, sort[thres], sort[med], sort[N-1]); 
            sum = 0;
            for(i=0; i<thres; i++) {
                sum += sort[i]; 
                n++;
            }
            info->meanOfLowValueArea = sum/n;

            sum = 0;
            for(i=0; i<thres; i++) {
                sum += SQR( sort[i] - info->meanOfLowValueArea); 
            }
            info->sdOfLowValueArea = sqrt(sum/n);
            info->seOfLowValueArea = sqrt(sum/n)/sqrt(n);
            break;
        }
        case meanOfLowValueAreaAndHighValueArea: {
            int N, i, thres, med;
            double* sort;
            double sum, n;

            // 
            N = img->HeaderN.x*img->HeaderN.y*img->HeaderN.z;
            sort = (double*)memoryAllocate(sizeof(double)*N, "in mrcImageInfo");
            lmrcImagePixelValueSort(sort, img, 0);

            // Low 
            thres = N*info->thresLow;
            med   = thres/2.0;
            info->thresOfLowValueArea = sort[thres];
            info->maxOfLowValueArea = sort[thres];
            info->minOfLowValueArea = sort[0];
            info->medianOfLowValueArea = sort[med];
            n = 0;
            DEBUGPRINT2("thresLow %f value %f\n", info->thresLow, sort[thres]); 
            DEBUGPRINT6("N %d thres %d med %d  %f %f %f \n", N, thres, med, sort[thres], sort[med], sort[0]); 
            sum = 0;
            for(i=0; i<thres; i++) {
                sum += sort[i]; 
                n++;
            }
            info->meanOfLowValueArea = sum/n;

            sum = 0;
            for(i=0; i<thres; i++) {
                sum += SQR( sort[i] - info->meanOfLowValueArea); 
            }
            info->sdOfLowValueArea = sqrt(sum/n);
            info->seOfLowValueArea = sqrt(sum/n)/sqrt(n);

            
            // High
            thres = N*info->thresHigh;
            med   = (N-1 + thres)/2.0;
            info->thresOfHighValueArea = sort[thres];
            info->minOfHighValueArea = sort[thres];
            info->maxOfHighValueArea = sort[N-1];
            info->medianOfHighValueArea = sort[med];
            n = 0;
            DEBUGPRINT2("thresHigh %f %f\n", info->thresHigh, sort[thres]); 
            DEBUGPRINT6("N %d thres %d med %d  %f %f %f \n", N, thres, med, sort[thres], sort[med], sort[N-1]); 
            sum = 0;
            for(i=thres; i<N; i++) {
                sum += sort[i]; 
                n++;
            }
            info->meanOfHighValueArea = sum/n;

            sum = 0;
            for(i=thres; i<N; i++) {
                sum += SQR( sort[i] - info->meanOfHighValueArea); 
            }
            info->sdOfHighValueArea = sqrt(sum/n);
            info->seOfHighValueArea = sqrt(sum/n)/sqrt(n);

            break;
        }
		default:{
			fprintf(stderr, "Not supported mode :%d", info->mode);
			exit(EXIT_FAILURE);
		}
	}
}

