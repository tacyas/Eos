#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>       
#undef DEBUG
#include "genUtil.h"
#include "../inc/mrcImage.h"

void
lmrcImageConvolution(mrcImage* out, mrcImage* in, mrcImage* kernel, int mode)
{
	int srcx, srcy, srcz;
	int minx, miny, minz;
	int maxx, maxy, maxz;
	int minxx, minyy, minzz;
	int maxxx, maxyy, maxzz;

	int kx, ky, kz;
	int x, y, z;
	double src;
	double dst;
	double weight;

	out->Header = in->Header;
	mrcInit(out, NULL);
	minz = -kernel->HeaderN.z/2; maxz=minz+kernel->HeaderN.z;
	miny = -kernel->HeaderN.y/2; maxy=miny+kernel->HeaderN.y;
	minx = -kernel->HeaderN.x/2; maxx=minx+kernel->HeaderN.x;
	for(z=0; z<out->HeaderN.z; z++) {
	for(y=0; y<out->HeaderN.y; y++) {
	for(x=0; x<out->HeaderN.x; x++) {
		dst = 0;
		minxx = MAX(0, minx+x);
		minyy = MAX(0, miny+y);
		minzz = MAX(0, minz+z);
		maxxx = MIN(maxx+x, in->HeaderN.x);
		maxyy = MIN(maxy+y, in->HeaderN.y);
		maxzz = MIN(maxz+z, in->HeaderN.z);

		DEBUGPRINT3("min %d %d %d \n", minxx, minyy, minzz);
		DEBUGPRINT3("max %d %d %d \n", maxxx, maxyy, maxzz);
		for(srcz=minzz; srcz<maxzz; srcz++) {	
			kz = srcz - minz - z; 
		for(srcy=minyy; srcy<maxyy; srcy++) {	
			ky = srcy - miny - y; 
		for(srcx=minxx; srcx<maxxx; srcx++) {	
			kx = srcx - minx - x; 
			mrcPixelDataGet(in,     srcx, srcy, srcz, &src,    mrcPixelRePart, mrcPixelHowNearest); 
			mrcPixelDataGet(kernel,   kx,   ky,   kz, &weight, mrcPixelRePart, mrcPixelHowNearest); 
			DEBUGPRINT4("w %d %d %d %f\n", kx, ky, kz, weight);
			dst += weight*src;
		}
		}
		}
		DEBUGPRINT4("d %d %d %d %f\n", x, y, z, dst);
		mrcPixelDataSet(out, x, y, z, dst, mrcPixelRePart); 
	}
	}
	}	
}

void 
lmrcImageDividedByImage(mrcImage* img, mrcImage* i1, mrcImage* i2)
{
    long ix, iy, iz;
    double ftmp1, ftmp2;

	if(    i1->HeaderN.x!=i2->HeaderN.x
	    || i1->HeaderN.y!=i2->HeaderN.y
	    || i1->HeaderN.z!=i2->HeaderN.z ) {
		fprintf(stderr, "ImageSize is different in lmrcImageDividedByImage\n");
		exit(EXIT_FAILURE);
	}
    img->Header = i1->Header;
    mrcInit(img, 0);
    switch(img->HeaderMode) {
        case MRC_char_image:
        case MRC_short_image:
        case MRC_float_image:
        case MRC_long_image:
        case MRC_double_image: {
            for(ix=0; ix<img->HeaderN.x; ix++) {
                for(iy=0; iy<img->HeaderN.y; iy++) {
                    for(iz=0; iz<img->HeaderN.z; iz++) {
                        mrcPixelDataGet(i1, (mrcImageParaTypeReal)ix, (mrcImageParaTypeReal)iy, (mrcImageParaTypeReal)iz,
    			               &ftmp1, mrcPixelRePart, mrcPixelHowNearest);
                        mrcPixelDataGet(i2, (mrcImageParaTypeReal)ix, (mrcImageParaTypeReal)iy, (mrcImageParaTypeReal)iz,
    			               &ftmp2, mrcPixelRePart, mrcPixelHowNearest);
                        if(ftmp2!=0) {
                            mrcPixelDataSet(img, (mrcImageParaTypeReal)ix, (mrcImageParaTypeReal)iy, (mrcImageParaTypeReal)iz,
        			               ftmp1/ftmp2, mrcPixelRePart);
                        } else if(ftmp1==0&&ftmp2==0){
                            mrcPixelDataSet(img, (mrcImageParaTypeReal)ix, (mrcImageParaTypeReal)iy, (mrcImageParaTypeReal)iz,
        			               0.0, mrcPixelRePart);
                        } else {
                            mrcPixelDataSet(img, (mrcImageParaTypeReal)ix, (mrcImageParaTypeReal)iy, (mrcImageParaTypeReal)iz,
        			               0.0, mrcPixelRePart);
                        }
                    }
                }
            }
            break;
        }
        default: {
            fprintf(stderr, "Not Supported mrcImageMode %d in lfft\n", img->HeaderMode);
            break;
        }
    }
}

void 
lmrcImagetMapForZero(mrcImage* t, mrcImage* avg, mrcImage* se)
{
	lmrcImageDividedByImage(t, avg, se);
}

void 
lmrcImageSN(mrcImage* sn, mrcImage* avg, mrcImage* sig)
{
	lmrcImageDividedByImage(sn, avg, sig);
}

void 
lmrcImageDividedByReal(mrcImage* img, double d)
{
    long ix, iy, iz;
    double ftmp;

    switch(img->HeaderMode) {
        case MRC_char_image:
        case MRC_short_image:
        case MRC_float_image:
        case MRC_long_image:
        case MRC_double_image: {
            for(ix=0; ix<img->HeaderN.x; ix++) {
                for(iy=0; iy<img->HeaderN.y; iy++) {
                    for(iz=0; iz<img->HeaderN.z; iz++) {
                        mrcPixelDataGet(img, (mrcImageParaTypeReal)ix, (mrcImageParaTypeReal)iy, (mrcImageParaTypeReal)iz,
    			               &ftmp, mrcPixelRePart, mrcPixelHowNearest);
                        mrcPixelDataSet(img, (mrcImageParaTypeReal)ix, (mrcImageParaTypeReal)iy, (mrcImageParaTypeReal)iz,
    			               ftmp/d, mrcPixelRePart);
                    }
                }
            }
            break;
        }
        default: {
            fprintf(stderr, "Not Supported mrcImageMode %d in lfft\n", img->HeaderMode);
            break;
        }
    }
}

void 
lmrcImageDividedByRealForOnlyPositive(mrcImage* img, double d)
{
    long ix, iy, iz;
    double ftmp;

    switch(img->HeaderMode) {
        case MRC_char_image:
        case MRC_short_image:
        case MRC_float_image:
        case MRC_long_image:
        case MRC_double_image: {
            for(ix=0; ix<img->HeaderN.x; ix++) {
                for(iy=0; iy<img->HeaderN.y; iy++) {
                    for(iz=0; iz<img->HeaderN.z; iz++) {
                        mrcPixelDataGet(img, (mrcImageParaTypeReal)ix, (mrcImageParaTypeReal)iy, (mrcImageParaTypeReal)iz,
    			               &ftmp, mrcPixelRePart, mrcPixelHowNearest);
						if(ftmp>=0) {
							ftmp /= d;
						}
                        mrcPixelDataSet(img, (mrcImageParaTypeReal)ix, (mrcImageParaTypeReal)iy, (mrcImageParaTypeReal)iz,
    			               ftmp, mrcPixelRePart);
                    }
                }
            }
            break;
        }
        default: {
            fprintf(stderr, "Not Supported mrcImageMode %d in lfft\n", img->HeaderMode);
            break;
        }
    }
}

void 
lmrcImageAddedByReal(mrcImage* img, double d)
{
    long ix, iy, iz;
    double ftmp;

    switch(img->HeaderMode) {
        case MRC_char_image:
        case MRC_short_image:
        case MRC_float_image:
        case MRC_long_image:
        case MRC_double_image: {
            for(ix=0; ix<img->HeaderN.x; ix++) {
                for(iy=0; iy<img->HeaderN.y; iy++) {
                    for(iz=0; iz<img->HeaderN.z; iz++) {
                        mrcPixelDataGet(img, (mrcImageParaTypeReal)ix, (mrcImageParaTypeReal)iy, (mrcImageParaTypeReal)iz,
    			               &ftmp, mrcPixelRePart, mrcPixelHowNearest);
                        mrcPixelDataSet(img, (mrcImageParaTypeReal)ix, (mrcImageParaTypeReal)iy, (mrcImageParaTypeReal)iz,
    			               ftmp+d, mrcPixelRePart);
                    }
                }
            }
            break;
        }
        default: {
            fprintf(stderr, "Not Supported mrcImageMode %d in lfft\n", img->HeaderMode);
            break;
        }
    }
}

void 
lmrcImageStdDev(mrcImage* sig, mrcImage* avg, mrcImage* avg2, long number)
{
    long ix, iy, iz;
    double ftmp1, ftmp2;

    sig->Header = avg->Header;
    mrcInit(sig, 0);
    switch(sig->HeaderMode) {
        case MRC_char_image:
        case MRC_short_image:
        case MRC_float_image:
        case MRC_long_image:
        case MRC_double_image: {
            for(ix=0; ix<sig->HeaderN.x; ix++) {
                for(iy=0; iy<sig->HeaderN.y; iy++) {
                    for(iz=0; iz<sig->HeaderN.z; iz++) {
                        mrcPixelDataGet(avg,  (mrcImageParaTypeReal)ix, (mrcImageParaTypeReal)iy, (mrcImageParaTypeReal)iz,
    			               &ftmp1, mrcPixelRePart, mrcPixelHowNearest);
                        mrcPixelDataGet(avg2, (mrcImageParaTypeReal)ix, (mrcImageParaTypeReal)iy, (mrcImageParaTypeReal)iz,
    			               &ftmp2, mrcPixelRePart, mrcPixelHowNearest);
                        mrcPixelDataSet(sig,  (mrcImageParaTypeReal)ix, (mrcImageParaTypeReal)iy, (mrcImageParaTypeReal)iz,
    			               sqrt(ftmp2-ftmp1*ftmp1), mrcPixelRePart);
                    }
                }
            }
            break;
        }
        default: {
            fprintf(stderr, "Not Supported mrcImageMode %d in lmrcImageStdDev\n", sig->HeaderMode);
            break;
        }
    }
}

void 
lmrcImageStdErr(mrcImage* se, mrcImage* avg, mrcImage* avg2, long number)
{
	lmrcImageStdDev(se, avg, avg2, number);
	lmrcImageDividedByReal(se, number);
}

void
lmrcImageAdd(mrcImage* img2, mrcImage* img1, long* number)
{
    int ix, iy, iz;
    double ftmp1, ftmp2, data;

    if((*number)==0) {
        img2->Header = img1->Header;
        mrcInit(img2, 0);
    } else {
        if(img2->HeaderN.x!=img1->HeaderN.x
         ||img2->HeaderN.y!=img1->HeaderN.y
         ||img2->HeaderN.z!=img1->HeaderN.z) {
            fprintf(stderr, "Image Size is different in lmrcImageAdd !!\n");
        }
    }
    (*number)++;

    switch(img2->HeaderMode) {
        case mrcCharImage:
        case mrcShortImage:
        case mrcFloatImage:
        case mrcLongImage:
        case mrcDoubleImage: {
			DEBUGPRINT("Image\n");	
            for(iz=0; iz<img1->HeaderN.z; iz++) {
            for(iy=0; iy<img1->HeaderN.y; iy++) {
            for(ix=0; ix<img1->HeaderN.x; ix++) {
            	mrcPixelDataGet(img1, (mrcImageParaTypeReal)ix, (mrcImageParaTypeReal)iy, (mrcImageParaTypeReal)iz,
    			               &ftmp1, mrcPixelRePart, mrcPixelHowNearest);
                mrcPixelDataGet(img2, (mrcImageParaTypeReal)ix, (mrcImageParaTypeReal)iy, (mrcImageParaTypeReal)iz,
    			               &ftmp2, mrcPixelRePart, mrcPixelHowNearest);
                data = ftmp2 + ftmp1;
                mrcPixelDataSet(img2, (mrcImageParaTypeReal)ix, (mrcImageParaTypeReal)iy, (mrcImageParaTypeReal)iz,
    			data, mrcPixelRePart);
            }
            }
            }
            break;
        }
        case mrcComplexShortFT:
        case mrcComplexFloatFT:
        case mrcComplexLongFT:
        case mrcComplexDoubleFT: {
			DEBUGPRINT3("FT: %d %d %d\n", img1->HeaderN.x, img1->HeaderN.y, img1->HeaderN.z);	
			DEBUGPRINT3("FT: %d %d %d\n", img1->HeaderN.x/2, (img1->HeaderN.y+1)/2, (img1->HeaderN.z+1)/2);	
            for(iz= -(img1->HeaderN.z/2); iz<(img1->HeaderN.z+1)/2; iz++) {
            for(iy= -(img1->HeaderN.y/2); iy<(img1->HeaderN.y+1)/2; iy++) {
            for(ix=0;                  ix<=img1->HeaderN.x/2;    ix++) {
				DEBUGPRINT3("%d %d %d in lmrcImageAdd\n", ix, iy, iz);
                mrcPixelDataGet(img1, (mrcImageParaTypeReal)ix, (mrcImageParaTypeReal)iy, (mrcImageParaTypeReal)iz,
    			               &ftmp1, mrcPixelRePart, mrcPixelHowNearest);
                mrcPixelDataGet(img2, (mrcImageParaTypeReal)ix, (mrcImageParaTypeReal)iy, (mrcImageParaTypeReal)iz,
    			               &ftmp2, mrcPixelRePart, mrcPixelHowNearest);
                data = ftmp2 + ftmp1;
                mrcPixelDataSet(img2, (mrcImageParaTypeReal)ix, (mrcImageParaTypeReal)iy, (mrcImageParaTypeReal)iz,
    			               data, mrcPixelRePart);

                mrcPixelDataGet(img1, (mrcImageParaTypeReal)ix, (mrcImageParaTypeReal)iy, (mrcImageParaTypeReal)iz,
    			               &ftmp1, mrcPixelImPart, mrcPixelHowNearest);
                mrcPixelDataGet(img2, (mrcImageParaTypeReal)ix, (mrcImageParaTypeReal)iy, (mrcImageParaTypeReal)iz,
    			               &ftmp2, mrcPixelImPart, mrcPixelHowNearest);
                data = ftmp2 + ftmp1;
                mrcPixelDataSet(img2, (mrcImageParaTypeReal)ix, (mrcImageParaTypeReal)iy, (mrcImageParaTypeReal)iz,
    			               data, mrcPixelImPart);
            }
            }
            }
			DEBUGPRINT3("%d %d %d in lmrcImageAdd\n", ix, iy, iz);
            break;
        }
        default: {
            fprintf(stderr, "Not Supported mrcImageMode %d in lfft\n", img2->HeaderMode);
			exit(EXIT_FAILURE);
            break;
        }
    }
}

void
lmrcSQRImageAdd(mrcImage* img2, mrcImage* img1, long* number)
{
    unsigned long ix, iy, iz;
    double ftmp1, ftmp2, data;

    if((*number)==0) {
        img2->Header = img1->Header;
        mrcInit(img2, 0);
        switch(img2->HeaderMode) {
            case MRC_char_image:
            case MRC_short_image:
            case MRC_float_image:
            case MRC_long_image:
            case MRC_double_image: {
                for(ix=0; ix<img1->HeaderN.x; ix++) {
                    for(iy=0; iy<img1->HeaderN.y; iy++) {
                        for(iz=0; iz<img1->HeaderN.z; iz++) {
                            mrcPixelDataSet(img2, (mrcImageParaTypeReal)ix, (mrcImageParaTypeReal)iy, (mrcImageParaTypeReal)iz,
        			               0.0, mrcPixelRePart);
                        }
                    }
                }
                break;
            }
            default: {
                fprintf(stderr, "Not Supported mrcImageMode %d in lfft\n", img2->HeaderMode);
                break;
            }
        }
    } else {
        if(img2->HeaderN.x!=img1->HeaderN.x
         ||img2->HeaderN.y!=img1->HeaderN.y
         ||img2->HeaderN.z!=img1->HeaderN.z) {
            fprintf(stderr, "Image Size is Wrong!!\n");
            exit(EXIT_FAILURE);
        }
    }
    (*number)++;


    switch(img2->HeaderMode) {
        case MRC_char_image:
        case MRC_short_image:
        case MRC_float_image:
        case MRC_long_image:
        case MRC_double_image: {
            for(ix=0; ix<img1->HeaderN.x; ix++) {
                for(iy=0; iy<img1->HeaderN.y; iy++) {
                    for(iz=0; iz<img1->HeaderN.z; iz++) {
                        mrcPixelDataGet(img1, (mrcImageParaTypeReal)ix, (mrcImageParaTypeReal)iy, (mrcImageParaTypeReal)iz,
    			               &ftmp1, mrcPixelRePart, mrcPixelHowNearest);
                        mrcPixelDataGet(img2, (mrcImageParaTypeReal)ix, (mrcImageParaTypeReal)iy, (mrcImageParaTypeReal)iz,
    			               &ftmp2, mrcPixelRePart, mrcPixelHowNearest);
                        data = ftmp2 + ftmp1*ftmp1;
                        mrcPixelDataSet(img2, (mrcImageParaTypeReal)ix, (mrcImageParaTypeReal)iy, (mrcImageParaTypeReal)iz,
    			               data, mrcPixelRePart);
                    }
                }
            }
            break;
        }
        default: {
            fprintf(stderr, "Not Supported mrcImageMode %d in lfft\n", img2->HeaderMode);
            break;
        }
    }
}


void lmrcImageSquare(mrcImage* in) 
{
/* variables */
  int x,y,z;
  double data,datao;
  
/* begin */
  for (z=0 ;z<in->HeaderN.z ;z++){
    for (y=0 ;y<in->HeaderN.y ;y++){
      for (x=0 ;x<in->HeaderN.x ;x++){
    mrcPixelDataGet(in,x,y,z,&data,mrcPixelRePart ,mrcPixelHowNearest); 
    datao = data*data;
    mrcPixelDataSet(in,x,y,z,datao ,mrcPixelRePart);
      }   
    }   
  }
  mrcStatDataSet(in,0);  
}


void lmrcImageRoot(mrcImage* in ,double eps)
{
/* variables */
  int x,y,z;
  double data,datao;

/* begin */
  for (z=0 ;z<in->HeaderN.z ;z++){
    for (y=0 ;y<in->HeaderN.y ;y++){
      for (x=0 ;x<in->HeaderN.x ;x++){
    mrcPixelDataGet(in,x,y,z,&data,mrcPixelRePart ,mrcPixelHowNearest);
        if (data > eps){
      datao = sqrt(data);
    }else {
      datao = 0;
      if (data < 0){
        fprintf(stderr,"Data is negative! (x,y,z)=(%d,%d,%d) \n",x,y,z);
      }
    }
    mrcPixelDataSet(in,x,y,z,datao ,mrcPixelRePart);
      }
    }
  }
  mrcStatDataSet(in,0);
}

void
lmrcImageAbs(mrcImage* out ,mrcImage* in) 
{
/* variables */
  int x,y,z;
  double data;
  
  out->Header = in->Header;
  mrcInit(out,NULL);


/* begin */
  for (z=0 ;z<in->HeaderN.z ;z++){
    for (y=0 ;y<in->HeaderN.y ;y++){
      for (x=0 ;x<in->HeaderN.x ;x++){
    mrcPixelDataGet(in,x,y,z,&data,mrcPixelRePart ,mrcPixelHowNearest); 
    data = fabs(data);
    mrcPixelDataSet(out ,x,y,z,data ,mrcPixelRePart);
      }   
    }   
  }
  mrcStatDataSet(out,0);  
}

