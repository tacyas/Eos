/*
	%A%
	%Z%: lmrcImageSmoothing(mrcImage* dst, mrcImage* src, lmrcImageSmoothingInfo* info, long mode)
	%Z%: Created newly by tacyas, 1996/02/29
	%Z%: Add Mean Filter by Isao, 1996/04/23
	%Z%: Add Surface Fit Filter by Isao, 1996/04/24 - 25
*/
#include <stdio.h>
#include <stdlib.h>

#undef DEBUG
#include "genUtil.h"
#include "Memory.h"
#include "../inc/mrcImage.h"

static void __lmrcImageSmoothingMedianFilter(mrcImage* dst, mrcImage* src, lmrcImageSmoothingInfo* info, long mode);
static void __lmrcImageSmoothingMeanFilter(mrcImage *dst, mrcImage *src, lmrcImageSmoothingInfo *info, long mode);
static void __lmrcImageSmoothingSurfaceFitFilter(mrcImage *dst, mrcImage *src, lmrcImageSmoothingInfo *info, long mode);
static void __lmrcImageSmoothingLeeSigmaFilter(mrcImage *dst, mrcImage *src, lmrcImageSmoothingInfo *info, long mode);
static void __lmrcImageSmoothingLocalWeightedMeanFilter(mrcImage *dst, mrcImage *src, lmrcImageSmoothingInfo *info, long mode);
static void __lmrcImageSmoothingEdgeAndLineWeightsSmoothingFilter(mrcImage *dst, mrcImage *src, lmrcImageSmoothingInfo *info, long mode);
static void __lmrcImageSmoothingContrastSensitiveWeightsSmoothingFilter(mrcImage *dst, mrcImage *src, lmrcImageSmoothingInfo *info, long mode);
static void __lmrcImageSmoothingGradientInverseWeightedSmoothingFilter(mrcImage *dst, mrcImage *src, lmrcImageSmoothingInfo *info, long mode);

static float _D[12][9] = {
   {
	0,     0,     0,
	1.0/6, 1.0/6, 1.0/6,
	1.0/6, 1.0/6, 1.0/6
   }, {
	0,     0,     1.0/6,
	0,     1.0/6, 1.0/6,
	1.0/6, 1.0/6, 1.0/6
   }, {
	0,     1.0/6, 1.0/6,
	0,     1.0/6, 1.0/6,
	0,     1.0/6, 1.0/6
   }, {
	1.0/6, 1.0/6, 1.0/6,
	0,     1.0/6, 1.0/6,
	0,     0,     1.0/6
   }, {
	1.0/6, 1.0/6, 1.0/6,
	1.0/6, 1.0/6, 1.0/6,
	0,     0,     0
   }, {
	1.0/6, 1.0/6, 1.0/6,
	1.0/6, 1.0/6,     0,
	1.0/6,     0,     0
   }, {
	1.0/6, 1.0/6,     0,
	1.0/6, 1.0/6,     0,
	1.0/6, 1.0/6,     0
   }, {
	1.0/6, 0,         0,
	1.0/6, 1.0/6,     0,
	1.0/6, 1.0/6, 1.0/6
   }, {
	0,     0,         0,
	1.0/6, 1.0/3, 1.0/3,
	0,     0,         0
   }, {
	0,     0,     1.0/3,
	0,     1.0/3,     0,
	1.0/6, 0,         0
   }, {
	0,     1.0/3,     0,
	0,     1.0/3,     0,
	0,     1.0/6,     0
   }, {
	1.0/3, 0,         0,
	0,     1.0/3,     0,
	0,     0,     1.0/3
   }
};


void 
lmrcImageSmoothingModeInfo(FILE* fpt) 
{
    fprintf(fpt, "    1: Median filter\n");
    fprintf(fpt, "    2: Mean filter \n");
    fprintf(fpt, "    3: Surface Fit filter\n");
    fprintf(fpt, "    4: Lee-Sigma filter(Use sigma)\n");
    fprintf(fpt, "    5: Local weighted mean filter\n");
    fprintf(fpt, "    6: Edge and line weights smoothing filter(3x3)\n");
    fprintf(fpt, "    7: Contrast-sensitiveline weights smoothing filter(3x3:Use sigma)\n");
    fprintf(fpt, "    8: Gradient inverse weighted smoothing filter(3x3)\n");
    fprintf(fpt, ">>> Mode2 <<<< \n");
    fprintf(fpt, "    0: Kernel is cube. : required argumnent: -sx, -sy, [-sz]\n");
    fprintf(fpt, "    1: Kernel is sphere.(Only mode 1 supported) : required argumnent: -r \n");
}

void
lmrcImageSmoothing(mrcImage* dst, mrcImage* src, lmrcImageSmoothingInfo* info, long mode)
{
	DEBUGPRINT1("mode: %d\n", info->mode);
	switch(info->mode) {
		case 1: /* Median Filtering */ {
			__lmrcImageSmoothingMedianFilter(dst, src, info, mode);
			break;
		}
		case 2: /* Mean Filtering */
		    __lmrcImageSmoothingMeanFilter(dst, src, info, mode);
			break;
		case 3:
		    __lmrcImageSmoothingSurfaceFitFilter(dst, src, info, mode);
		    break;
		case 4: /* Lee-Sigma Filtering */
			DEBUGPRINT("__lmrcImageSmoothingLeeSigmaFilter\n");
		    __lmrcImageSmoothingLeeSigmaFilter(dst, src, info, mode);
		    break;
		case 5: /* Local Weighted Mean Filtering */
			DEBUGPRINT("__lmrcImageSmoothingLocalWeightedMeanFilter\n");
		    __lmrcImageSmoothingLocalWeightedMeanFilter(dst, src, info, mode);
		    break;
		case 6: /* Edge and Line Weights Smoothing Filtering */
			DEBUGPRINT("__lmrcImageSmoothingEdgeAndLineWeightsSmoothingFilter\n");
		    __lmrcImageSmoothingEdgeAndLineWeightsSmoothingFilter(dst, src, info, mode);
		    break;
		case 7: /* Contrast Sensitive Weights Smoothing Filtering */
			DEBUGPRINT("__lmrcImageSmoothingConstrastSensitiveWeightsSmoothingFilter\n");
		    __lmrcImageSmoothingContrastSensitiveWeightsSmoothingFilter(dst, src, info, mode);
		    break;
		case 8: /* Gradient Inverse Weighted Smoothing Filtering */
			DEBUGPRINT("__lmrcImageSmoothingGradientInverseWeightedSmoothingFilter\n");
		    __lmrcImageSmoothingGradientInverseWeightedSmoothingFilter(dst, src, info, mode);
		    break;
		default:  {
			fprintf(stderr, "Not supported mode in lmrcImageSmoothing: %ld\n", info->mode);
			lmrcImageSmoothingModeInfo(stderr);
			break;
		}
	}
}


void 
__lmrcImageSmoothingLeeSigmaFilter(mrcImage* dst, mrcImage* src, lmrcImageSmoothingInfo* info,long mode)
{
	long n, i, index, center ,lsx ,lsy ,lsz;
	float x, y, z ,r2, rr;
	float tmpx, tmpy, tmpz;
	int offsetx, offsety, offsetz;
	double data;
	float* kernel; 
	float* kernel2; 
	double sum, avg, sigma;

	DEBUGPRINT("__lmrcImageSmoothingLeeSigmaFilter\n");
	if (mode==0){
	  lsx=floor(info->sx+0.5);
	  lsy=floor(info->sy+0.5);
	  lsz=floor(info->sz+0.5);
	  if(IsOdd(lsx)) {
	    offsetx = (lsx - 1)/2;
	  } else {
	    fprintf(stderr, "Not supported kernel size: sx = %ld\n", lsx);
	    exit(EXIT_FAILURE);
	  }
	  if(IsOdd(lsy)) {
	    offsety = (lsy - 1)/2;
	  } else {
	    fprintf(stderr, "Not supported kernel size: sy = %ld\n", lsy);
	    exit(EXIT_FAILURE);
 	  }
	  if(IsOdd(lsz)) {
	    offsetz = (lsz - 1)/2;
	  } else {
	  fprintf(stderr, "Not supported kernel size: sz = %ld\n", lsz);
	  }
	  n = lsx*lsy*lsz;
	}else{
	  offsetx=offsety=offsetz=floor(info->sx); 
	  if (src->HeaderN.z==1 ){
	    offsetz=0;
	  }
	  r2 = SQR(info->sx) ;
	  DEBUGPRINT4("%d %d %d %f\n",offsetx,offsety,offsetz,r2);
	  n=(offsetx*2+1)*(offsety*2+1)*(offsetz*2+1);
	}

	center = (n-1)/2;
	DEBUGPRINT5("x: %d %d y: %d %d center: %d\n", offsetx, info->sx, offsety, info->sy, center);
	kernel  = (float*)memoryAllocate(sizeof(float)*n, "in __lmrcImageSmoothingMedianFilter");
	kernel2 = (float*)memoryAllocate(sizeof(float)*n, "in __lmrcImageSmoothingMedianFilter");
	dst->Header = src->Header;
	mrcInit(dst, NULL);	
	for(z = 0; z < src->HeaderN.z; z++) {
	for(y = 0; y < src->HeaderN.y; y++) {
	for(x = 0; x < src->HeaderN.x; x++) {
		index = 0;	
		switch(mode%2){
			case 0: {
		  		for(tmpz=MAX(0,z-offsetz); tmpz<=MIN(z+offsetz, src->HeaderN.z-1); tmpz++) {
		   		for(tmpy=MAX(0,y-offsety); tmpy<=MIN(y+offsety, src->HeaderN.y-1); tmpy++) {
		    	for(tmpx=MAX(0,x-offsetx); tmpx<=MIN(x+offsetx, src->HeaderN.x-1); tmpx++) {
					rr = fabs(z-tmpz)+fabs(y-tmpy)+fabs(z-tmpz);
					if(0==rr) {
						center = index;
					}
					mrcPixelDataGet(src, tmpx, tmpy, tmpz, &data, mrcPixelMag, mrcPixelHowNearest);
					kernel[index] = data;
			  		//DEBUGPRINT5("%f %f %f %f %d \n",tmpx,tmpy,tmpz,data ,index);
					index++;
		      	}
		    	}
		  		}
		  		break;
			}
			case 1: {
		  		for(tmpz=z-offsetz; tmpz<=z+offsetz; tmpz++) {
		      	for(tmpy=y-offsety; tmpy<=y+offsety; tmpy++) {
		    	for(tmpx=x-offsetx; tmpx<=x+offsetx; tmpx++) {
					rr = SQR(z-tmpz)+SQR(y-tmpy)+SQR(x-tmpx);
					if(0==rr) {
						center = index;
					}
					if(rr <= r2 ) {
						mrcPixelDataGet(src, tmpx, tmpy, tmpz, &data, mrcPixelMag, mrcPixelHowNearest);
			  			kernel[index] = data;
			  			//DEBUGPRINT5("%f %f %f %f %d \n",tmpx,tmpy,tmpz,data ,index);
			  			index++;		
					}	
		      	}
		    	}
		  		}
				break;
			}
			default: {
				fprintf(stderr, "Not supported mode: %ld\n", mode);
				exit(EXIT_FAILURE);
				break;
			}
		}

		n = index;
		DEBUGPRINT6("(%f, %f, %f) center %d  n %d %d\n", x, y, z, center, n, index);
		sum = 0;
		avg = kernel[center];
		for(i=0; i<n; i++) {
			sum += SQR(kernel[i] - avg);
		}
		if(0<n) {
			sigma = sqrt(sum/n);
		} else {
			sigma = 0;
		}
		DEBUGPRINT3("avg %f sigma %f n %d \n",avg, sigma, n);

		index = 0;
		sum = 0;
		for(i=0; i<n; i++) {
			if(fabs(kernel[i]-avg)<info->sigma*sigma) {
				sum += kernel[i];
				index++;
			}
		}
		n = index;
		if(0<n) {
			avg = sum/n;
			DEBUGPRINT4("avg %f sigma %f n %d info->sigma: %f\n",avg,sigma,n, info->sigma);
		} 
		mrcPixelDataSet(dst, x, y, z, avg, mrcPixelMag);
	}
	}
	}
	memoryFree(kernel);
	memoryFree(kernel2);
}

void 
__lmrcImageSmoothingMedianFilter(mrcImage* dst, mrcImage* src, lmrcImageSmoothingInfo* info,long mode)
{
	long n, index, center ,lsx ,lsy ,lsz;
	float x, y, z ,r2;
	float tmpx, tmpy, tmpz;
	long offsetx, offsety, offsetz;
	double data;
	float* kernel; 
	extern int __lmrcImageSmoothingMedianFilterCompare(const void* a, const void* b);

	if (mode==0){
	  lsx=floor(info->sx+0.5);
	  lsy=floor(info->sy+0.5);
	  lsz=floor(info->sz+0.5);
	  if(IsOdd(lsx)) {
	    offsetx = (lsx - 1)/2;
	  } else {
	    fprintf(stderr, "Not supported kernel size: sx = %ld\n", lsx);
	    exit(EXIT_FAILURE);
	  }
	  if(IsOdd(lsy)) {
	    offsety = (lsy - 1)/2;
	  } else {
	    fprintf(stderr, "Not supported kernel size: sy = %ld\n", lsy);
	    exit(EXIT_FAILURE);
 	  }
	  if(IsOdd(lsz)) {
	    offsetz = (lsz - 1)/2;
	  } else {
	  fprintf(stderr, "Not supported kernel size: sz = %ld\n", lsz);
	  }
	  n = lsx*lsy*lsz;
	}else{
	  offsetx=offsety=offsetz=floor(info->sx); 
	  if (src->HeaderN.z==1 ){
	    offsetz=0;
	  }
	  r2 = SQR(info->sx) ;
	  fprintf(stderr,"%ld %ld %ld %f\n",offsetx,offsety,offsetz,r2);
	  n=(offsetx*2+1)*(offsety*2+1)*(offsetz*2+1);
	}

	center = (n-1)/2;
	DEBUGPRINT5("x: %ld %ld y: %ld %ld center: %ld\n", offsetx, info->sx, offsety, info->sy, center);
	kernel = (float*)memoryAllocate(sizeof(float)*n, "in __lmrcImageSmoothingMedianFilter");
	dst->Header = src->Header;
	mrcInit(dst, NULL);	
	for(z = 0; z < src->HeaderN.z; z++) {
      if(__verbose__) {
          fprintf(stderr, "%d/%d\n", z, src->HeaderN.z); 
      }
	  for(y = 0; y < src->HeaderN.y; y++) {
	    for(x = 0; x < src->HeaderN.x; x++) {
	      	      
	      if( (x<offsetx 
		   || y < offsety 
		   || z < offsetz
		   || src->HeaderN.x-1-offsetx<x
		   || src->HeaderN.y-1-offsety<y
		   || src->HeaderN.z-1-offsetz<z ) 
		  && !(mode & 2) ) {				 
	      
		mrcPixelDataGet(src, x, y, z, &data, mrcPixelMag, mrcPixelHowNearest);
		mrcPixelDataSet(dst, x, y, z, data, mrcPixelMag);
	      } else {
	      
		index = 0;	
		switch(mode%2){
		case 0:
		  for(tmpz=z-offsetz; tmpz<=z+offsetz; tmpz++) {
		    for(tmpy=y-offsety; tmpy<=y+offsety; tmpy++) {
		      for(tmpx=x-offsetx; tmpx<=x+offsetx; tmpx++) {
			mrcPixelDataGet(src, tmpx, tmpy, tmpz, &data, mrcPixelMag, mrcPixelHowNearest);
			kernel[index] = data;
			index++;
		      }
		    }
		  }
		  break;
		case 1:
		  for(tmpz=z-offsetz; tmpz<=z+offsetz; tmpz++) {
		    for(tmpy=y-offsety; tmpy<=y+offsety; tmpy++) {
		      for(tmpx=x-offsetx; tmpx<=x+offsetx; tmpx++) {
			if (SQR(z-tmpz)+SQR(y-tmpy)+SQR(x-tmpx) <= r2 ){
			  mrcPixelDataGet(src, tmpx, tmpy, tmpz, &data, mrcPixelMag, mrcPixelHowNearest);
			  kernel[index] = data;
			  index++;		
			  DEBUGPRINT5("%f %f %f %f %d \n",tmpx,tmpy,tmpz,data ,index);
			}	
		      }
		    }
		  }
		  center = (index-1)/2;
		  n=index;
		}
		qsort(kernel, n, sizeof(float), __lmrcImageSmoothingMedianFilterCompare);
#ifdef DEBUG
		if(data==kernel[center]) fprintf(stderr, "%f %f\n", x, y);
#endif
		data = kernel[center];
		mrcPixelDataSet(dst, x, y, z, data, mrcPixelMag);
		
	      }
		
	    }
	  }
	}
	memoryFree(kernel);
}

int
__lmrcImageSmoothingMedianFilterCompare(const void* a, const void* b)
{
	DEBUGPRINT2("in __mrcImageSmoothingMedianFilterCompare:%f %f\n", *(float*)a, *(float*)b);
	if(*(float*)a<*(float*)b) {
		return -1;
	} else if(*(float*)a==*(float*)b) {
		return 0;
	} else {
		return 1;
	}
}

void 
__lmrcImageSmoothingMeanFilter(mrcImage* dst, mrcImage* src, lmrcImageSmoothingInfo* info, long mode)
{
	long n, index;
	float x, y;
	float tmpx, tmpy;
	long offsetx, offsety, offsetz ,lsx ,lsy ,lsz;
	double data, sum; 

	if (mode==0){
	  lsx=floor(info->sx+0.5);
	  lsy=floor(info->sy+0.5);
	  lsz=floor(info->sz+0.5);
	  if(IsOdd(lsx)) {
	    offsetx = (lsx - 1)/2;
	  } else {
	    fprintf(stderr, "Not supported kernel size: sx = %ld\n", lsx);
	    exit(EXIT_FAILURE);
	  }
	  if(IsOdd(lsy)) {
	    offsety = (lsy - 1)/2;
	  } else {
	    fprintf(stderr, "Not supported kernel size: sy = %ld\n", lsy);
	    exit(EXIT_FAILURE);
	  }
	  if(IsOdd(lsz)) {
	    offsetz = (lsz - 1)/2;
	  } else {
	  fprintf(stderr, "Not supported kernel size: sz = %ld\n", lsz);
	  }
	  n = lsx*lsy*lsz;
	}
	if(src->HeaderN.z!=1) {
		if(IsOdd(lsz)) {
			offsetz = (lsz - 1)/2;
		} else {
			fprintf(stderr, "Not supported kernel size: sz = %ld\n", lsz);
		}
		n = n*lsz;
	}
	DEBUGPRINT5("x: %ld %ld y: %ld %ld datapoints: %ld\n", offsetx, lsx, offsety, lsy, n);
	dst->Header = src->Header;
	mrcInit(dst, NULL);	
	for(x = 0; x < src->HeaderN.x; x++) {
		for(y = 0; y < src->HeaderN.y; y++) {
			if(1!=src->HeaderN.z) {
				fprintf(stderr, "Not yet supported: z-dimension\n");
				exit(EXIT_FAILURE);
			} else {
				if(x<offsetx 
					|| y < offsety 
					|| src->HeaderN.x-1-offsetx<x
					|| src->HeaderN.y-1-offsety<y ) {				
					mrcPixelDataGet(src, x, y, 0.0, &data, mrcPixelMag, mrcPixelHowNearest);
					mrcPixelDataSet(dst, x, y, 0.0, data, mrcPixelMag);
				} else {
					index = 0;	
					for(sum = 0.0, tmpx=x-offsetx; tmpx<=x+offsetx; tmpx++) {
						for(tmpy=y-offsety; tmpy<=y+offsety; tmpy++) {
							mrcPixelDataGet(src, tmpx, tmpy, 0.0, &data, mrcPixelMag, mrcPixelHowNearest);
					sum += data;
							index++;
						}
					}
					data = sum / n;
					mrcPixelDataSet(dst, x, y, 0.0, data, mrcPixelMag);
				}
			}
		}
	}
}

void 
__lmrcImageSmoothingLocalWeightedMeanFilter(mrcImage* dst, mrcImage* src, lmrcImageSmoothingInfo* info, long mode)
{
	long n, index;
	float x, y, z;
	float tmpx, tmpy, tmpz;
	long offsetx, offsety, offsetz ,lsx ,lsy ,lsz;
	double data, sum, sumW, W; 

	if (mode==0){
	  lsx=floor(info->sx+0.5);
	  lsy=floor(info->sy+0.5);
	  lsz=floor(info->sz+0.5);
	  if(IsOdd(lsx)) {
	    offsetx = (lsx - 1)/2;
	  } else {
	    fprintf(stderr, "Not supported kernel size: sx = %ld\n", lsx);
	    exit(EXIT_FAILURE);
	  }
	  if(IsOdd(lsy)) {
	    offsety = (lsy - 1)/2;
	  } else {
	    fprintf(stderr, "Not supported kernel size: sy = %ld\n", lsy);
	    exit(EXIT_FAILURE);
	  }
	  if(IsOdd(lsz)) {
	    offsetz = (lsz - 1)/2;
	  } else {
	  fprintf(stderr, "Not supported kernel size: sz = %ld\n", lsz);
	  }
	  n = lsx*lsy*lsz;
	}
	if(src->HeaderN.z!=1) {
		if(IsOdd(lsz)) {
			offsetz = (lsz - 1)/2;
		} else {
			fprintf(stderr, "Not supported kernel size: sz = %ld\n", lsz);
		}
		n = n*lsz;
	}
	DEBUGPRINT5("x: %ld %ld y: %ld %ld datapoints: %ld\n", offsetx, lsx, offsety, lsy, n);
	dst->Header = src->Header;
	mrcInit(dst, NULL);	
	for(z = 0; z < src->HeaderN.z; z++) {
	for(y = 0; y < src->HeaderN.y; y++) {
	for(x = 0; x < src->HeaderN.x; x++) {
		if(x < offsetx 
		|| y < offsety 
		|| z < offsetz 
		|| src->HeaderN.x-1-offsetx<x
		|| src->HeaderN.y-1-offsety<y 
		|| src->HeaderN.z-1-offsetz<z ) {				
			mrcPixelDataGet(src, x, y, 0.0, &data, mrcPixelRePart, mrcPixelHowNearest);
			mrcPixelDataSet(dst, x, y, 0.0,  data, mrcPixelRePart);
		} else {
			index = 0;	
			sum  = 0.0;
			sumW = 0.0;
			for(tmpz=z-offsetz; tmpz<=z+offsetz; tmpz++) {
			for(tmpy=y-offsety; tmpy<=y+offsety; tmpy++) {
			for(tmpx=x-offsetx; tmpx<=x+offsetx; tmpx++) {
				W = (offsetx - fabs(tmpx - x) + 1)
				   *(offsety - fabs(tmpy - y) + 1)
				   *(offsetz - fabs(tmpz - z) + 1); 
				mrcPixelDataGet(src, tmpx, tmpy, tmpz, &data, mrcPixelRePart, mrcPixelHowNearest);
				sum  += data*W;
				sumW += W;
			}
			}
			}
			data = sum / sumW;
			mrcPixelDataSet(dst, x, y, tmpz, data, mrcPixelRePart);
		}
	}
	}
	}
}


void 
__lmrcImageSmoothingEdgeAndLineWeightsSmoothingFilter(mrcImage* dst, mrcImage* src, lmrcImageSmoothingInfo* info, long mode)
{
	long n, index;
	float x, y, z;
	float tmpx, tmpy, tmpz;
	long offsetx, offsety, offsetz ,lsx ,lsy ,lsz;
	double data, sum, sumW; 
	double D[9];
	double Wu[12];
	double Ov[12];
	double Sv[12];
	double S, SumWu;
	int u, v;
	double maxOv;
	double signMaxOv;

	if(src->HeaderN.z!=1) {
		fprintf(stderr, "Not supported 3D data: lmrcImageSmoothingEdgeAndLineWeightsSmoothingFilter\n");
		exit(EXIT_FAILURE);
	}

	dst->Header = src->Header;
	mrcInit(dst, NULL);	
	for(y = 0; y < src->HeaderN.y; y++) {
	for(x = 0; x < src->HeaderN.x; x++) {
		if(x < 1 
		|| y < 1 
		|| src->HeaderN.x-1-1<x
		|| src->HeaderN.y-1-1<y ) {				
			mrcPixelDataGet(src, x, y, 0.0, &data, mrcPixelRePart, mrcPixelHowNearest);
			mrcPixelDataSet(dst, x, y, 0.0,  data, mrcPixelRePart);
		} else {
			S = 0;
			for(tmpy=y-1; tmpy<=y+1; tmpy++) {
			for(tmpx=x-1; tmpx<=x+1; tmpx++) {
				mrcPixelDataGet(src, tmpx, tmpy, 0, &data, mrcPixelRePart, mrcPixelHowNearest);
				S += data;
				
			}
			}
			maxOv = 0;
			signMaxOv = 1;
			for(v=0; v<12; v++) {
				Sv[v] = 0;
				index = 0; 
				for(tmpy=y-1; tmpy<=y+1; tmpy++) {
				for(tmpx=x-1; tmpx<=x+1; tmpx++) {
					if(v< 8 && _D[v][index] == 0
					&& 8<=v && _D[v][index] != 0) {
						mrcPixelDataGet(src, tmpx, tmpy, 0, &data, mrcPixelRePart, mrcPixelHowNearest);
						Sv[v] += data;
					}
					index++;
				}
				}
				Ov[v] = S - 3*Sv[v];
				if(maxOv < fabs(Ov[v])) {
					maxOv = fabs(Ov[v]);
					signMaxOv = Ov[v]/maxOv;
				}
			}
			if(signMaxOv<0) {
				for(v=0; v<12; v++) {
					Ov[v] *= (-1);
					if(Ov[v]<0) {
						Ov[v] = 0;	
					}
				}
			} else {
				for(v=0; v<12; v++) {
					if(Ov[v]<0) {
						Ov[v] = 0;	
					}
				}
			}	
			SumWu = 0;	
			for(u=0; u<12; u++) {
				SumWu += Ov[u];
			}
			for(u=0; u<12; u++) {
				Wu[u] = Ov[u]/SumWu;
			}
			
			for(index=0; index<9; index++) {
				D[index] = 0;
				for(u=0; u<12; u++) {
					D[index] += Wu[u]*_D[u][index];
				}
			}

			sum = 0;
			index = 0;
			for(tmpy=y-1; tmpy<=y+1; tmpy++) {
			for(tmpx=x-1; tmpx<=x+1; tmpx++) {
				mrcPixelDataGet(src, tmpx, tmpy, 0, &data, mrcPixelRePart, mrcPixelHowNearest);
				sum += data*D[index]; 
				index++;
			}
			}
			mrcPixelDataSet(dst, x, y, 0, sum, mrcPixelRePart);
		}
	}
	}
}


void 
__lmrcImageSmoothingContrastSensitiveWeightsSmoothingFilter(mrcImage* dst, mrcImage* src, lmrcImageSmoothingInfo* info, long mode)
{
	long n, index;
	float x, y, z;
	float tmpx, tmpy, tmpz;
	long offsetx, offsety, offsetz ,lsx ,lsy ,lsz;
	double data, sum, sumW; 
	double D[3][3];
	double a, b, c, d, e, f, g, h, i;
	double A[8];
	if(src->HeaderN.z!=1) {
		fprintf(stderr, "Not supported 3D data: lmrcImageSmoothingEdgeAndLineWeightsSmoothingFilter\n");
		exit(EXIT_FAILURE);
	}

	dst->Header = src->Header;
	mrcInit(dst, NULL);	
	for(y = 0; y < src->HeaderN.y; y++) {
	for(x = 0; x < src->HeaderN.x; x++) {
		if(x < 1 
		|| y < 1 
		|| src->HeaderN.x-1-1<x
		|| src->HeaderN.y-1-1<y ) {				
			mrcPixelDataGet(src, x, y, 0.0, &data, mrcPixelRePart, mrcPixelHowNearest);
			mrcPixelDataSet(dst, x, y, 0.0,  data, mrcPixelRePart);
		} else {
			mrcPixelDataGet(src, x-1, y-1, 0, &g, mrcPixelRePart, mrcPixelHowNearest);
			mrcPixelDataGet(src, x,   y-1, 0, &h, mrcPixelRePart, mrcPixelHowNearest);
			mrcPixelDataGet(src, x+1, y-1, 0, &i, mrcPixelRePart, mrcPixelHowNearest);
			mrcPixelDataGet(src, x-1, y  , 0, &d, mrcPixelRePart, mrcPixelHowNearest);
			mrcPixelDataGet(src, x,   y  , 0, &e, mrcPixelRePart, mrcPixelHowNearest);
			mrcPixelDataGet(src, x+1, y  , 0, &f, mrcPixelRePart, mrcPixelHowNearest);
			mrcPixelDataGet(src, x-1, y+1, 0, &a, mrcPixelRePart, mrcPixelHowNearest);
			mrcPixelDataGet(src, x,   y+1, 0, &b, mrcPixelRePart, mrcPixelHowNearest);
			mrcPixelDataGet(src, x+1, y+1, 0, &c, mrcPixelRePart, mrcPixelHowNearest);

			A[0] = exp(-fabs((a+b+c)-(d+e+f))/info->sigma);
			A[1] = exp(-fabs((g+h+d)-(d+e+f))/info->sigma);
			A[2] = exp(-fabs((a+b+d)-(c+e+g))/info->sigma);
			A[3] = exp(-fabs((f+h+i)-(c+e+g))/info->sigma);
			A[4] = exp(-fabs((a+d+g)-(b+e+h))/info->sigma);
			A[5] = exp(-fabs((c+f+i)-(b+e+h))/info->sigma);
			A[6] = exp(-fabs((b+c+f)-(a+e+i))/info->sigma);
			A[7] = exp(-fabs((d+g+h)-(a+e+i))/info->sigma);

			D[0][0]=A[1]*A[4]*A[7];
			D[1][0]=A[1]*A[3]*A[7];
			D[2][0]=A[1]*A[3]*A[5];

			D[0][1]=A[2]*A[4]*A[7];
			D[1][1]=1;
			D[2][1]=          A[6];

			D[0][2]=A[0]*A[2]*A[4];
			D[1][2]=A[0]*A[2]*A[6];
			D[2][2]=A[0]*A[5]*A[6];

			sum  = D[0][0]*g + D[1][0]*h + D[2][0]*i 
			     + D[0][1]*d + D[1][1]*e + D[2][1]*f
			     + D[0][2]*a + D[1][2]*b + D[2][2]*c;
			sumW = D[0][0]   + D[1][0]   + D[2][0] 
			     + D[0][1]   + D[1][1]   + D[2][1]
			     + D[0][2]   + D[1][2]   + D[2][2];
			DEBUGPRINT3("%f %f %f\n", D[0][2], D[1][2], D[2][2]);
			DEBUGPRINT3("%f %f %f\n", D[0][1], D[1][1], D[2][1]);
			DEBUGPRINT3("%f %f %f\n", D[0][0], D[1][0], D[2][0]);
			DEBUGPRINT3("sum: %f sumW: %f centre: %f\n", sum, sumW, e);
			mrcPixelDataSet(dst, x, y, 0, sum/sumW, mrcPixelRePart);
		}
	}
	}
}


void 
__lmrcImageSmoothingGradientInverseWeightedSmoothingFilter(mrcImage* dst, mrcImage* src, lmrcImageSmoothingInfo* info, long mode)
{
	long n, index;
	float x, y, z;
	float tmpx, tmpy, tmpz;
	long offsetx, offsety, offsetz ,lsx ,lsy ,lsz;
	double data, sum, sumW; 
	double D[3][3];
	double a, b, c, d, e, f, g, h, i;
	if(src->HeaderN.z!=1) {
		fprintf(stderr, "Not supported 3D data: lmrcImageSmoothingEdgeAndLineWeightsSmoothingFilter\n");
		exit(EXIT_FAILURE);
	}

	dst->Header = src->Header;
	mrcInit(dst, NULL);	
	for(y = 0; y < src->HeaderN.y; y++) {
	for(x = 0; x < src->HeaderN.x; x++) {
		if(x < 1 
		|| y < 1 
		|| src->HeaderN.x-1-1<x
		|| src->HeaderN.y-1-1<y ) {				
			mrcPixelDataGet(src, x, y, 0.0, &data, mrcPixelRePart, mrcPixelHowNearest);
			mrcPixelDataSet(dst, x, y, 0.0,  data, mrcPixelRePart);
		} else {
			mrcPixelDataGet(src, x-1, y-1, 0, &g, mrcPixelRePart, mrcPixelHowNearest);
			mrcPixelDataGet(src, x,   y-1, 0, &h, mrcPixelRePart, mrcPixelHowNearest);
			mrcPixelDataGet(src, x+1, y-1, 0, &i, mrcPixelRePart, mrcPixelHowNearest);
			mrcPixelDataGet(src, x-1, y  , 0, &d, mrcPixelRePart, mrcPixelHowNearest);
			mrcPixelDataGet(src, x,   y  , 0, &e, mrcPixelRePart, mrcPixelHowNearest);
			mrcPixelDataGet(src, x+1, y  , 0, &f, mrcPixelRePart, mrcPixelHowNearest);
			mrcPixelDataGet(src, x-1, y+1, 0, &a, mrcPixelRePart, mrcPixelHowNearest);
			mrcPixelDataGet(src, x,   y+1, 0, &b, mrcPixelRePart, mrcPixelHowNearest);
			mrcPixelDataGet(src, x+1, y+1, 0, &c, mrcPixelRePart, mrcPixelHowNearest);

			D[0][0]=(0<fabs(g-e))?(1.0/fabs(g-e)):(2);
			D[1][0]=(0<fabs(h-e))?(1.0/fabs(h-e)):(2);
			D[2][0]=(0<fabs(i-e))?(1.0/fabs(i-e)):(2);

			D[0][1]=(0<fabs(d-e))?(1.0/fabs(d-e)):(2);
			D[1][1]=1.0/2;
			D[2][1]=(0<fabs(f-e))?(1.0/fabs(f-e)):(2);

			D[0][2]=(0<fabs(a-e))?(1.0/fabs(a-e)):(2);
			D[1][2]=(0<fabs(b-e))?(1.0/fabs(b-e)):(2);
			D[2][2]=(0<fabs(c-e))?(1.0/fabs(c-e)):(2);

			sum  = D[0][0]*g + D[1][0]*h + D[2][0]*i 
			     + D[0][1]*d + D[1][1]*e + D[2][1]*f
			     + D[0][2]*a + D[1][2]*b + D[2][2]*c;
			sumW = D[0][0]   + D[1][0]   + D[2][0] 
			     + D[0][1]   + D[1][1]   + D[2][1]
			     + D[0][2]   + D[1][2]   + D[2][2];

			DEBUGPRINT3("%f %f %f\n", D[0][2], D[1][2], D[2][2]);
			DEBUGPRINT3("%f %f %f\n", D[0][1], D[1][1], D[2][1]);
			DEBUGPRINT3("%f %f %f\n", D[0][0], D[1][0], D[2][0]);
			DEBUGPRINT3("sum: %f sumW: %f centre: %f\n", sum, sumW, e);
			mrcPixelDataSet(dst, x, y, 0, sum/sumW, mrcPixelRePart);
		}
	}
	}
}



static long int __SumOfSquare(long int);
static long int __SumOfSquareSquare(long int n, long int m);
static long int __SumOf4(long int n);
static void __setKernel(double *kernel, lmrcImageSmoothingInfo* info, long n, long offsetx, long offsety);

void __lmrcImageSmoothingSurfaceFitFilter(mrcImage* dst, mrcImage* src, lmrcImageSmoothingInfo* info, long mode)
{
    long n, index ,lsx ,lsy ,lsz;
    float x, y, tmpx, tmpy;
    long offsetx, offsety, offsetz;
    /* g = axx + byy + cxy + dx + ey + f */
    double data, g;
    double *kernel;
    
    /* This function allows odd sx, sy and sz only. */
    if (mode==0){
      lsx=floor(info->sx+0.5);
      lsy=floor(info->sy+0.5);
      lsz=floor(info->sz+0.5);
      if(IsOdd(lsx)) {
	offsetx = (lsx - 1)/2;
      } else {
	fprintf(stderr, "Not supported kernel size: sx = %ld\n", lsx);
	exit(EXIT_FAILURE);
      }
      if(IsOdd(lsy)) {
	offsety = (lsy - 1)/2;
      } else {
	fprintf(stderr, "Not supported kernel size: sy = %ld\n", lsy);
	exit(EXIT_FAILURE);
      }
      if(IsOdd(lsz)) {
	offsetz = (lsz - 1)/2;
      } else {
	fprintf(stderr, "Not supported kernel size: sz = %ld\n", lsz);
      }
      n = lsx*lsy*lsz;
    }
    /* Number of data points in the region.*/
    if(n < 6) {
	fprintf(stderr, "Too few data number to caluculate surface.\nTry with more large sx and sy.\n");
	exit(EXIT_FAILURE);
    }
    kernel = (double *)memoryAllocate(sizeof(double) * n, "in __lmrcImageSmoothingSurfaceFitFilter");
    __setKernel(kernel, info, n, offsetx, offsety);

    dst->Header = src->Header;
    mrcInit(dst, NULL);
    for(x = 0; x < src->HeaderN.x; x++) {
	for(y = 0; y < src->HeaderN.y; y++) {
	    {
		if(x<offsetx || y < offsety ||
		   src->HeaderN.x - offsetx <= x ||
		   src->HeaderN.y - offsety <= y)
		{				
		    mrcPixelDataGet(src, x, y, 0.0, &data, mrcPixelMag, mrcPixelHowNearest);
		    mrcPixelDataSet(dst, x, y, 0.0, data, mrcPixelMag);
		} 
		else 
		{
		    index = 0, g = 0.0;
		    for(tmpx=-offsetx; tmpx<=offsetx; tmpx++)
		    {
			for(tmpy=-offsety; tmpy<=offsety; tmpy++) 
			{
			    mrcPixelDataGet(src, x + tmpx, y + tmpy, 0.0, &data, mrcPixelMag, mrcPixelHowNearest);
			    g += kernel[index++] * data;
			}
		    }
		    mrcPixelDataSet(dst, x, y, 0.0, g, mrcPixelMag);
		}
	    }
	}
    }
    memoryFree(kernel);
}

static inline long int __SumOfSquare(long int n)
{
    return n * (n + 1) * (n * 2 + 1) / 6;
}

static long __SumOfSquareSquare(long n, long m)
{
    long i, j, ret = 0;;
    for(i = 1; i <= n; i++)
	for(j = 1; j <= m; j++)
	    ret += i * i * j * j;
    return ret;
}

static long int __SumOf4(long int n)
{
    long int i, ret = 0;
    for(i = 1; i <= n; i++) ret += i * i * i * i;
    return ret;
}

static void __setKernel(double *kernel, lmrcImageSmoothingInfo* info, long n, long offsetx, long offsety)
{
    long index, x, y;
    double det, a13, a23, a33, x4, y4, x2y2, x2, y2;

    x2 = __SumOfSquare(offsetx) * 2 * info->sy;
    y2 = __SumOfSquare(offsety) * 2 * info->sx;
    /* Get Sum of n^2 from -offsetx to offsetx */
    x2y2 = __SumOfSquareSquare(offsetx, offsety) * 4;
    x4 = __SumOf4(offsetx) * 2 * info->sy;
    y4 = __SumOf4(offsety) * 2 * info->sx;
    det = x4 * y4 * n + 2 * x2y2 * x2 * y2 
	- x2 * x2 * y4 - x2y2 * x2y2 * n - x4 * y2 * y2;
    a13 = (x2y2 * y2 - x2 * y4) / det;
    a23 = - (x4 * y2 - x2 * x2y2) / det;
    a33 = (x4 * y4 - x2y2 * x2y2) / det;    
    for(index = 0, x=-offsetx; x<=offsetx; x++)
    {
	for(y=-offsety; y<=offsety; y++) 
	{
	    kernel[index] = a13 * x * x + a23 * y * y + a33;
#ifdef DEBUG
	    DEBUGPRINT1("%0.3e ", kernel[index]);
#endif
	    index++;
	}
#ifdef DEBUG
	DEBUGPRINT("\n");
#endif
    }
}
