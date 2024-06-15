/*
# mrcImageInverseRadonTransform : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : mrcImageInverseRadonTransform
# Attention
#   $Loccker$
#  	$State$ 
#
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"

#define DEBUG
#include "genUtil.h"
#include "Memory.h"
#include "mrcImage.h"


typedef enum lmrcImageInverseRadonTransformMode {
	SimpleBackProjection                 = 1,
	WeightedBackProjection               = 2,
	RWeightedBackProjection              = 3,
	NearestCountRWeightedBackProjection  = 4,
	WeightedCountRWeightedBackProjection = 5,
	SimpleBackProjectionRWeight          = 6
} lmrcImageInverseRadonTransformMode;

typedef struct lmrcImageInverseRadonTransformInfo {
	lmrcImageInverseRadonTransformMode BackProjectionMode;
} lmrcImageInverseRadonTransformInfo;

typedef struct lmrcImageRadonTransformRhoFilterInfo {
	double Rmin;
    double Rmax;
	int    T;
} lmrcImageRadonTransformRhoFilterInfo;

extern void lmrcImageInverseRadonTransform(mrcImage* out, mrcImage* in, lmrcImageInverseRadonTransformInfo* linfo1, lmrcImageRadonTransformRhoFilterInfo* linfo2, int mode);
extern void lmrcImageRadonTransfromInverseFourierTransform(mrcImage* out, mrcImage* in, int mode);
extern void lmrcImageRadonTransformRhoFilter(mrcImage* out, mrcImage* in, lmrcImageRadonTransformRhoFilterInfo* linfo, int mode);
extern void lmrcImageRadonTransformFourierTransform(mrcImage* out, mrcImage* in, int mode);
extern void lmrcImageRadonTransformOneLineGet(mrcImage* out, mrcImage* in, int theta, int phi, int mode);
extern void lmrcImageRadonTransformFourierTransformOneLineGet(mrcImage* out, mrcImage* in, int theta, int phi, int mode);
extern void lmrcImageRadonTransformCountRhoFilter(mrcImage* out, mrcImage* in, lmrcImageRadonTransformRhoFilterInfo* linfo, int mode);
extern void lmrcImageRadonTransformNearestCountRWeightedBackProjectionWeightCalculation(mrcImage* out, mrcImage* in, mrcImage* radon, int mode);
extern void lmrcImageRadonTransformWeightedCountRWeightedBackProjectionWeightCalculation(mrcImage* out, mrcImage* in, mrcImage* radon, lmrcImageRadonTransformRhoFilterInfo* linfo2, int mode);

extern void lmrcImageRadonTransformSimpleBackProjectionRWeightFiltering(mrcImage* out, mrcImage* in, lmrcImageRadonTransformRhoFilterInfo* linfo, int mode);

int
main(int argc, char* argv[]) 
{
    mrcImageInverseRadonTransformInfo info;
	lmrcImageInverseRadonTransformInfo linfo1;
	lmrcImageRadonTransformRhoFilterInfo linfo2; 
	mrcImage in;
	mrcImage out;

	init0(&info);
	argCheck(&info, argc, argv);
	init1(&info);

	DEBUGPRINT("Program Start\n");

	mrcFileRead(&in, info.In, "Read In", 0);

	linfo2.Rmin               = info.Rmin;
	linfo2.Rmax               = info.Rmax;
	linfo2.T                  = info.T;
	linfo1.BackProjectionMode = info.BackProjectionMode;

	lmrcImageInverseRadonTransform(&out, &in, &linfo1, &linfo2, info.mode);  

	mrcFileWrite(&out, info.Out, "Write Out", 0);

	DEBUGPRINT("Program End\n");

	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "\n");
	fprintf(stderr, "----- BackProjectionMode -----\n");
	fprintf(stderr, " 1 = SimpleBackProjection\n");
	fprintf(stderr, " 2 = WeightedBackProjection\n");
	fprintf(stderr, " 3 = RWeightedBackProjectioni             (-Rmax, -Rmin)\n");
	fprintf(stderr, " 4 = CountRWeightedBackProjection         (-Rmax, -Rmin)\n");
	fprintf(stderr, " 5 = WeightedCountRWeightedBackProjection (-Rmax, -Rmin, -T)\n");
	fprintf(stderr, " 6 = SimpleBackProjectionRWeight          (-Rmax, -Rmin)\n");
}

void
lmrcImageInverseRadonTransform(mrcImage* out, mrcImage* in,lmrcImageInverseRadonTransformInfo* linfo1, lmrcImageRadonTransformRhoFilterInfo* linfo2, int mode)
{
	int                  srcx, srcy, srcz;	
	double               x, y, z;
	int                  count;
	int                  theta, phi;
	double               p;
	double               costheta, sintheta, cosphi, sinphi;
	double               Radondata1, Radondata2, Radondata3, data;
	mrcImage             tmpFT;
	mrcImage             tmpFTRho;
	mrcImage             tmpImg;
	mrcImage             SimpleImg;

    out->Header    = in->Header;
	out->HeaderN.x = out->HeaderN.y = out->HeaderN.z = in->HeaderN.x;
	out->HeaderLength.x = out->HeaderLength.y = out->HeaderLength.z = in->HeaderLength.x;
	out->HeaderMode = mrcFloatImage;
	mrcInit(out, NULL);

    SimpleImg.Header = out->Header;
    mrcInit(&SimpleImg,NULL);
	
	switch(linfo1->BackProjectionMode){
	case NearestCountRWeightedBackProjection:
	case WeightedCountRWeightedBackProjection:
	  lmrcImageRadonTransformFourierTransform(&tmpFT, in, mode);
	  	DEBUGPRINT("Finished to Fourier Transform\n");
	  lmrcImageRadonTransformCountRhoFilter(&tmpFTRho, &tmpFT, linfo2, mode);
	  	DEBUGPRINT("Finished to Count Rho Filtering\n");
	  lmrcImageRadonTransfromInverseFourierTransform(&tmpImg, &tmpFTRho, mode);
	  	DEBUGPRINT("Finished to Inverse Fourier Transform\n");
	  mrcImageFree(&tmpFT, 0);
	  mrcImageFree(&tmpFTRho, 0);
	  break;
	case RWeightedBackProjection:
	  lmrcImageRadonTransformFourierTransform(&tmpFT, in, mode);
	  	DEBUGPRINT("Finished to Fourier Transform\n");
	  lmrcImageRadonTransformRhoFilter(&tmpFTRho, &tmpFT, linfo2, mode);
	  	DEBUGPRINT("Finished to Rho Filtering\n");
	  lmrcImageRadonTransfromInverseFourierTransform(&tmpImg, &tmpFTRho, mode);
	  	DEBUGPRINT("Finished to Inverse Fourier Transform\n");
	  mrcImageFree(&tmpFT, 0);
	  mrcImageFree(&tmpFTRho, 0);
      break;
	case SimpleBackProjectionRWeight:
	case SimpleBackProjection:
	case WeightedBackProjection:
	  tmpImg = *in;
	  tmpImg.HeaderMode = mrcFloatRadonImage;
	  break;
	}
	
	switch(linfo1->BackProjectionMode){
		case RWeightedBackProjection:
			for(srcx=0; srcx<out->HeaderN.x; srcx++){
	    		if(fmod(srcx, out->HeaderN.x/10)==0){	
		   			count = srcx/(out->HeaderN.x/10);
		   			DEBUGPRINT1(">%d",count);
				} 
			for(srcy=0; srcy<out->HeaderN.y; srcy++){
			for(srcz=0; srcz<out->HeaderN.z; srcz++){
	  			x = out->HeaderLength.x*(srcx-(out->HeaderN.x-1)/2);
	  			y = out->HeaderLength.y*(srcy-(out->HeaderN.y-1)/2);
	  			z = out->HeaderLength.z*(srcz-(out->HeaderN.z-1)/2);
	
	  			data = 0;
	  			for(theta=0; theta<tmpImg.HeaderN.y; theta++){
					costheta = cos(theta*tmpImg.HeaderLength.y*RADIAN);
	    			sintheta = sin(theta*tmpImg.HeaderLength.y*RADIAN);
	  			for(phi=0;   phi<tmpImg.HeaderN.z;   phi++){
	    			cosphi = cos(phi*tmpImg.HeaderLength.z*RADIAN);
	    			sinphi = sin(phi*tmpImg.HeaderLength.z*RADIAN);
	    
	    			p = x*costheta*cosphi-y*sinphi+z*sintheta*cosphi;

	    			p = p/tmpImg.HeaderLength.x+(tmpImg.HeaderN.x-1)/2;
		
					if(p<-0.5 && tmpImg.HeaderN.x-0.5<p) Radondata2 = 0;
					else mrcPixelDataGet(&tmpImg, p, theta, phi, &Radondata2, mrcPixelRePart, mrcPixelHowCubicConv);
		
	      			data += Radondata2;
	  			}
	  			}
				mrcPixelDataSet(out, srcx, srcy, srcz, data, mrcPixelRePart);
			}
			}
			}
		break;
		default :
			for(srcx=0; srcx<out->HeaderN.x; srcx++){
	    		if(fmod(srcx, out->HeaderN.x/10)==0){	
		   			count = srcx/(out->HeaderN.x/10);
		   			DEBUGPRINT1(">%d",count);
				} 
			for(srcy=0; srcy<out->HeaderN.y; srcy++){
			for(srcz=0; srcz<out->HeaderN.z; srcz++){
	  			x = out->HeaderLength.x*(srcx-(out->HeaderN.x-1)/2);
	  			y = out->HeaderLength.y*(srcy-(out->HeaderN.y-1)/2);
	  			z = out->HeaderLength.z*(srcz-(out->HeaderN.z-1)/2);
	
	  			data = 0;
	  			for(theta=0; theta<tmpImg.HeaderN.y; theta++){
					costheta = cos(theta*tmpImg.HeaderLength.y*RADIAN);
	    			sintheta = sin(theta*tmpImg.HeaderLength.y*RADIAN);
	  			for(phi=0;   phi<tmpImg.HeaderN.z;   phi++){
	    			cosphi = cos(phi*tmpImg.HeaderLength.z*RADIAN);
	    			sinphi = sin(phi*tmpImg.HeaderLength.z*RADIAN);
	    
	    			p = x*costheta*cosphi-y*sinphi+z*sintheta*cosphi;

	    			p = p/tmpImg.HeaderLength.x+(tmpImg.HeaderN.x-1)/2;
		
					if(p<-0.5 && tmpImg.HeaderN.x-0.5<p) Radondata2 = 0;
					else mrcPixelDataGet(&tmpImg, p, theta, phi, &Radondata2, mrcPixelRePart, mrcPixelHowCubicConv);
		
	    			switch(linfo1->BackProjectionMode){
	    				case SimpleBackProjectionRWeight:
						case NearestCountRWeightedBackProjection:
	    				case WeightedCountRWeightedBackProjection:
						case SimpleBackProjection:
	      					data += Radondata2;
	      					break;
	    				case WeightedBackProjection:
	      					if(p-1<0.5 && p-1>tmpImg.HeaderN.x-0.5) Radondata1 = 0;
							else mrcPixelDataGet(&tmpImg, p-1, theta, phi, &Radondata1, mrcPixelRePart, mrcPixelHowCubicConv);

							if(p+1<0.5 && p+1>tmpImg.HeaderN.x-0.5) Radondata3 = 0;
							else mrcPixelDataGet(&tmpImg, p+1, theta, phi, &Radondata3, mrcPixelRePart, mrcPixelHowCubicConv);
				
							data += Radondata2*0.25-Radondata1*0.125-Radondata3*0.125;
	      					break;
	    			}
	  			}
	  			}
				switch(linfo1->BackProjectionMode){
					case SimpleBackProjectionRWeight:
					case NearestCountRWeightedBackProjection:
					case WeightedCountRWeightedBackProjection:
						mrcPixelDataSet(&SimpleImg, srcx, srcy, srcz, data, mrcPixelRePart);
					break;
					case SimpleBackProjection:
					case WeightedBackProjection:
						mrcPixelDataSet(out, srcx, srcy, srcz, data, mrcPixelRePart);
	      			break;
	  			}
			}
			}
			}
		break;
	}
	
	switch(linfo1->BackProjectionMode){
	  case SimpleBackProjectionRWeight:
	    	DEBUGPRINT("\nlmrcImageRadonTransformSimpleBackProjectionRWeightFiltering start\n");
        lmrcImageRadonTransformSimpleBackProjectionRWeightFiltering(out, &SimpleImg, linfo2, mode);
	    	DEBUGPRINT("lmrcImageRadonTransformSimpleBackProjectionRWeightFiltering end\n");
	    mrcImageFree(&SimpleImg, 0);
	    break;
	  case NearestCountRWeightedBackProjection:
	    	DEBUGPRINT("\nlmrcImageRadonTransformNearestCountRWeightBackProjectionWeightCalculation start\n");
   	    lmrcImageRadonTransformNearestCountRWeightedBackProjectionWeightCalculation(out, &SimpleImg, in, mode);
	    	DEBUGPRINT("lmrcImageRadonTransformNearestCountRWeightBackProjectionWeightCalculation end\n");
        mrcImageFree(&SimpleImg, 0);
		break;
	  case WeightedCountRWeightedBackProjection:
	    	DEBUGPRINT("\nlmrcImageRadonTransformWeightedCountRWeightBackProjectionWeightCalculation start\n");
   	    lmrcImageRadonTransformWeightedCountRWeightedBackProjectionWeightCalculation(out, &SimpleImg, in, linfo2, mode);
	    	DEBUGPRINT("lmrcImageRadonTransformWeightedCountRWeightBackProjectionWeightCalculation end\n");
        mrcImageFree(&SimpleImg, 0);
		break;
	  case SimpleBackProjection:
	  case WeightedBackProjection:
	  case RWeightedBackProjection:
	    break;
	}
	DEBUGPRINT("\n");
}

void
lmrcImageRadonTransformSimpleBackProjectionRWeightFiltering(mrcImage* out, mrcImage* in, lmrcImageRadonTransformRhoFilterInfo* linfo, int mode)
{
	int      FTx, FTy, FTz;
	int      i;
	double   FTLength;
	double   x, y, z;	
	double   distance;
	double   Sumweight;
	double   Redata, Imdata, weight;
	double*  Weight;
	mrcImage tmpFT;

	lmrcImageFFT(&tmpFT, in, 0);
	
	Weight = (double*)memoryAllocate(sizeof(double)*(in->HeaderN.x/2+1)*in->HeaderN.y*in->HeaderN.z, "in lmrcImageRadonTransformSimpleBackProjectionRWeightFiltering");

	FTLength = 1/(in->HeaderN.x*in->HeaderLength.x);
	
	i = 0;
	Sumweight = 0;
	for(FTx=0                  ; FTx<=tmpFT.HeaderN.x/2; FTx++){
		x = FTx*FTLength;
	for(FTy=-tmpFT.HeaderN.y/2; FTy< tmpFT.HeaderN.y/2; FTy++){
		y = FTy*FTLength;
	for(FTz=-tmpFT.HeaderN.z/2; FTz< tmpFT.HeaderN.z/2; FTz++){
		z = FTz*FTLength;
		distance = sqrt(SQR(x)+SQR(y)+SQR(z));
		if(distance <= linfo->Rmin){
			weight = distance;
		}
		else if(linfo->Rmin < distance && distance < linfo->Rmax){
			weight = distance*(cos(M_PI*(distance-linfo->Rmin)/(linfo->Rmax-linfo->Rmin))+1)/2;
		}
		else{
			weight = 0;
		}
		Sumweight += weight;
		Weight[i] = weight;
		i++;
	}
	}
	}
/*
	for(i=0; i<(in->HeaderN.x/2+1)*in->HeaderN.y*in->HeaderN.z; i++){
		Weight[i] /= Sumweight;
	}
*/
	i = 0;
	for(FTx=0                  ; FTx<=tmpFT.HeaderN.x/2; FTx++){
	for(FTy=-tmpFT.HeaderN.y/2; FTy< tmpFT.HeaderN.y/2; FTy++){
	for(FTz=-tmpFT.HeaderN.z/2; FTz< tmpFT.HeaderN.z/2; FTz++){
		mrcPixelDataGet(&tmpFT , FTx, FTy, FTz, &Redata, mrcPixelRePart, mrcPixelHowNearest);
		mrcPixelDataGet(&tmpFT , FTx, FTy, FTz, &Imdata, mrcPixelImPart, mrcPixelHowNearest);
		Redata *= Weight[i];
		Imdata *= Weight[i];
		mrcPixelDataSet(&tmpFT , FTx, FTy, FTz, Redata, mrcPixelRePart);
		mrcPixelDataSet(&tmpFT , FTx, FTy, FTz, Imdata, mrcPixelImPart);
		i++;	
	}
	}
	}
	
	lmrcImageFFT(out, &tmpFT, 0);
	mrcImageFree(&tmpFT, 0);
}

void
lmrcImageRadonTransformNearestCountRWeightedBackProjectionWeightCalculation(mrcImage* out, mrcImage* in, mrcImage* radon, int mode)
{
	mrcImage weight;
	mrcImage tmpFT;
	int      x, y, z;
	int      theta, phi;
	int      i;
	double   thetaRad, phiRad;
	double   Px, Py, Pz;
	double   Pxi, Pyi, Pzi;
	double   ReData, ImData, count;
	
	lmrcImageFFT(&tmpFT, in, 0);

	weight.Header = tmpFT.Header;
	mrcInit(&weight,NULL);

	for(theta=0; theta<radon->HeaderN.y; theta++){
	for(phi  =0; phi  <radon->HeaderN.z; phi++){
		thetaRad = theta*radon->HeaderLength.y*RADIAN;
		phiRad   = phi*radon->HeaderLength.z*RADIAN;
		Px = cos(thetaRad)*cos(phiRad);
		Py = -sin(phiRad);
		Pz = sin(thetaRad)*cos(phiRad);
		if(Px<0) {
			Px *= -1;
			Py *= -1;
			Pz *= -1;
		}
		i=0;
		while(1) {
			Pxi = (int)(Px*i+0.5); Pyi = (int)(Py*i+0.5); Pzi = (int)(Pz*i+0.5);	
			if(Pxi<=weight.HeaderN.x/2
			 &&-weight.HeaderN.y/2 <= Pyi && Pyi < weight.HeaderN.y/2
			 &&-weight.HeaderN.z/2 <= Pzi && Pzi < weight.HeaderN.z/2) {
				mrcPixelDataGet(&weight, Pxi, Pyi, Pzi, &count, mrcPixelRePart, mrcPixelHowNearest);
				count += 1;
				mrcPixelDataSet(&weight, Pxi, Pyi, Pzi, count, mrcPixelRePart);
				i++;
			} else {
				break;
			}
		}
	}
	}
	for(x = 0                   ;  x <=tmpFT.HeaderN.x/2; x++){
	for(y = -(tmpFT.HeaderN.y/2);  y < tmpFT.HeaderN.y/2; y++){
	for(z = -(tmpFT.HeaderN.z/2);  z < tmpFT.HeaderN.z/2; z++){
		mrcPixelDataGet(&tmpFT , x, y, z, &ReData, mrcPixelRePart, mrcPixelHowNearest);
		mrcPixelDataGet(&tmpFT , x, y, z, &ImData, mrcPixelImPart, mrcPixelHowNearest);
		mrcPixelDataGet(&weight, x, y, z, &count , mrcPixelRePart, mrcPixelHowNearest);
		if(count != 0){
			ReData /= count;
			ImData /= count;
		}
		mrcPixelDataSet(&tmpFT, x, y, z, ReData, mrcPixelRePart);
		mrcPixelDataSet(&tmpFT, x, y, z, ImData, mrcPixelImPart);
	}
	}
	}
	lmrcImageFFT(out, &tmpFT, 0);
	mrcImageFree(&weight, 0);
	mrcImageFree(&tmpFT, 0);
}

void
lmrcImageRadonTransformWeightedCountRWeightedBackProjectionWeightCalculation(mrcImage* out, mrcImage* in, mrcImage* radon, lmrcImageRadonTransformRhoFilterInfo* linfo2, int mode)
{
	mrcImage weight;
	mrcImage tmpFT;
	int      x, y, z;
	int      theta, phi;
	int      i,j,k,l;
	int*     pxi;
	int*     pyi;
	int*     pzi;
	int      number;
	double   thetaRad, phiRad;
	double   Px, Py, Pz;
	double   Pxi, Pyi, Pzi;
	double   ReData, ImData, count;
	double*  RatioX;
	double*  RatioY;
	double*  RatioZ;
    double   SumX;
    double   SumY;
    double   SumZ;
 
	lmrcImageFFT(&tmpFT, in, 0);

	weight.Header = tmpFT.Header;
	mrcInit(&weight,NULL);

    number = 2*linfo2->T;

	pxi = (int*)memoryAllocate(sizeof(int)*number, "in lmrcRadonTransformWeightedCountRWeightedBackProjectionWeightCalculation");
	pyi = (int*)memoryAllocate(sizeof(int)*number, "in lmrcRadonTransformWeightedCountRWeightedBackProjectionWeightCalculation");
	pzi = (int*)memoryAllocate(sizeof(int)*number, "in lmrcRadonTransformWeightedCountRWeightedBackProjectionWeightCalculation");

	RatioX = (double*)memoryAllocate(sizeof(double)*number, "in lmrcRadonTransformWeightedCountRWeightedBackProjeciotnWeightCalculation");
	RatioY = (double*)memoryAllocate(sizeof(double)*number, "in lmrcRadonTransformWeightedCountRWeightedBackProjeciotnWeightCalculation");
	RatioZ = (double*)memoryAllocate(sizeof(double)*number, "in lmrcRadonTransformWeightedCountRWeightedBackProjeciotnWeightCalculation");

    for(theta=0; theta<radon->HeaderN.y; theta++){
	for(phi  =0; phi  <radon->HeaderN.z; phi++){
		thetaRad = theta*radon->HeaderLength.y*RADIAN;
		phiRad   = phi*radon->HeaderLength.z*RADIAN;
		Px = cos(thetaRad)*cos(phiRad);
		Py = -sin(phiRad);
		Pz = sin(thetaRad)*cos(phiRad);
		if(Px<0) {
			Px *= -1;
			Py *= -1;
			Pz *= -1;
		}
		i=0;
		while(1) {
			Pxi = Px*i;
			Pyi = Py*i;
			Pzi = Pz*i;
			if(Pxi<weight.HeaderN.x/2-1e-15
			 &&-weight.HeaderN.y/2+1e-15 < Pyi && Pyi < weight.HeaderN.y/2-1-1e-15
			 &&-weight.HeaderN.z/2+1e-15 < Pzi && Pzi < weight.HeaderN.z/2-1-1e-15) {
				if(Pxi < 0){
					pxi[0] = (int)Pxi-linfo2->T;
				}
				else{
					pxi[0] = (int)Pxi-linfo2->T+1;
				}
				if(Pyi < 0){
					pyi[0] = (int)Pyi-linfo2->T;
				}
				else{
					pyi[0] = (int)Pyi-linfo2->T+1;
				}
				if(Pzi < 0){
					pzi[0] = (int)Pzi-linfo2->T;
				}
				else{
					pzi[0] = (int)Pzi-linfo2->T+1;
				}
				for(j=1; j<number; j++){
					pxi[j] = pxi[j-1]+1;
					pyi[j] = pyi[j-1]+1;
					pzi[j] = pzi[j-1]+1;
				}
				SumX = 0;
				SumY = 0;
				SumZ = 0;
				for(j=0; j<number; j++){
					RatioX[j] = linfo2->T-fabs(Pxi-pxi[j]);
					RatioY[j] = linfo2->T-fabs(Pyi-pyi[j]);
					RatioZ[j] = linfo2->T-fabs(Pzi-pzi[j]);
					SumX +=RatioX[j];
					SumY +=RatioY[j];
					SumZ +=RatioZ[j];
				}
				for(j=0; j<number; j++){
					RatioX[j] /=SumX;
					RatioY[j] /=SumY;
					RatioZ[j] /=SumZ;
				}
				for(j=0; j<number; j++){
				for(k=0; k<number; k++){
				for(l=0; l<number; l++){
					if(0                   <= pxi[j] && pxi[j] <= weight.HeaderN.x/2
					 &&-weight.HeaderN.y/2 <= pyi[k] && pyi[k] <= weight.HeaderN.y/2-1
					 &&-weight.HeaderN.z/2 <= pzi[l] && pzi[l] <= weight.HeaderN.z/2-1){
						mrcPixelDataGet(&weight, pxi[j], pyi[k], pzi[l], &count, mrcPixelRePart, mrcPixelHowNearest);
						count += RatioX[j]*RatioY[k]*RatioZ[l];
						mrcPixelDataSet(&weight, pxi[j], pyi[k], pzi[l], count, mrcPixelRePart);
					}
				}
				}
				}
				i++;
			} else {
				break;
			}
		}
	}
	}
	for(x = 0                   ;  x <=tmpFT.HeaderN.x/2; x++){
	for(y = -(tmpFT.HeaderN.y/2);  y < tmpFT.HeaderN.y/2; y++){
	for(z = -(tmpFT.HeaderN.z/2);  z < tmpFT.HeaderN.z/2; z++){
		mrcPixelDataGet(&tmpFT , x, y, z, &ReData, mrcPixelRePart, mrcPixelHowNearest);
		mrcPixelDataGet(&tmpFT , x, y, z, &ImData, mrcPixelImPart, mrcPixelHowNearest);
		mrcPixelDataGet(&weight, x, y, z, &count , mrcPixelRePart, mrcPixelHowNearest);
		if(1 <= count){
			ReData /= count;
			ImData /= count;
		}
		mrcPixelDataSet(&tmpFT, x, y, z, ReData, mrcPixelRePart);
		mrcPixelDataSet(&tmpFT, x, y, z, ImData, mrcPixelImPart);
	}
	}
	}
	lmrcImageFFT(out, &tmpFT, 0);
	mrcImageFree(&weight, 0);
	mrcImageFree(&tmpFT, 0);
}

void
lmrcImageRadonTransformFourierTransform(mrcImage* out, mrcImage* in, int mode) 
{
  mrcImage tmpImg;
  mrcImage tmpFT;
  int      theta, phi, P;
  double   re,im;

  out->Header = in->Header;
  out->HeaderMode = mrcFloatRadonFT;
  mrcInit(out, NULL);

  for(theta=0; theta < out->HeaderN.y; theta++){
  for(phi=0;   phi   < out->HeaderN.z;   phi++){
    lmrcImageRadonTransformOneLineGet(&tmpImg, in, theta, phi, 0);
    lmrcImageFFT(&tmpFT, &tmpImg, 0);
    for(P=0; P<=tmpFT.HeaderN.x/2; P++) {/*real data:Fourier data = 2:1*/
      mrcPixelDataGet(&tmpFT, P, 0, 0, &re, mrcPixelRePart, mrcPixelHowNearest);
      mrcPixelDataGet(&tmpFT, P, 0, 0, &im, mrcPixelImPart, mrcPixelHowNearest);
      mrcPixelDataSet(out, P, theta, phi, re, mrcPixelRePart);  
      mrcPixelDataSet(out, P, theta, phi, im, mrcPixelImPart);  
    }
	mrcImageFree(&tmpImg, 0);
	mrcImageFree(&tmpFT, 0);
  }
  }
}

void
lmrcImageRadonTransformOneLineGet(mrcImage* out, mrcImage* in, int theta, int phi, int mode)
{
  double data;
  int    p;

  out->Header = in->Header;
  out->HeaderN.y = out->HeaderN.z = 1;
  mrcInit(out, NULL);

  for(p=0; p < out->HeaderN.x; p++) {
    mrcPixelDataGet(in, p, theta, phi, &data, mrcPixelRePart, mrcPixelHowNearest);
    mrcPixelDataSet(out, p, 0, 0, data, mrcPixelRePart);
  }
}

void
lmrcImageRadonTransformCountRhoFilter(mrcImage* out, mrcImage* in, lmrcImageRadonTransformRhoFilterInfo* linfo, int mode)
{
  int     P, theta, phi;
  double  re, im;
  double  PP;
  double* W;

  W = (double*)memoryAllocate(sizeof(double)*(in->HeaderN.x/2+1), "in lmrcImageRadonTransformRhoFilter");

  out->Header = in->Header;
  mrcInit(out, NULL);
  
  for(P=0; P<=out->HeaderN.x/2; P++){
	PP = P/(in->HeaderN.x*in->HeaderLength.x);
    if(linfo->Rmin < PP && PP < linfo->Rmax){
       W[P] = (cos(M_PI*(PP-linfo->Rmin)/(linfo->Rmax-linfo->Rmin))+1)/2;
    }else{
       W[P] = 1;    
    }
  }

  for(P=0; P<=out->HeaderN.x/2; P++){
  for(theta=0; theta < out->HeaderN.y; theta++) {
  for(phi  =0; phi   < out->HeaderN.z; phi++) {
    mrcPixelDataGet(in, P, theta, phi, &re, mrcPixelRePart, mrcPixelHowNearest);
    mrcPixelDataGet(in, P, theta, phi, &im, mrcPixelImPart, mrcPixelHowNearest);
    re *= W[P];
    im *= W[P];
    mrcPixelDataSet(out, P, theta, phi, re, mrcPixelRePart);
    mrcPixelDataSet(out, P, theta, phi, im, mrcPixelImPart);
  }
  }
  }
  free(W);
}

void
lmrcImageRadonTransformRhoFilter(mrcImage* out, mrcImage* in, lmrcImageRadonTransformRhoFilterInfo* linfo, int mode)
{
  int     P, theta, phi;
  double  re, im;
  double  PP;
  double* W;
  double  SumW=0;

  W = (double*)memoryAllocate(sizeof(double)*(in->HeaderN.x/2+1), "in lmrcImageRadonTransformRhoFilter");

  out->Header = in->Header;
  mrcInit(out, NULL);
 
  for(P=0; P<=out->HeaderN.x/2; P++){
	PP = P/(in->HeaderN.x*in->HeaderLength.x);
	if(0 < PP && PP<= linfo->Rmin){
       W[P] = SQR(PP);
    } else if(linfo->Rmin < PP && PP < linfo->Rmax){
       W[P] = SQR(PP)*(cos(M_PI*(PP-linfo->Rmin)/(linfo->Rmax-linfo->Rmin))+1)/2;
    } else if(linfo->Rmax <= PP && PP <= 0){
       W[P] = 0;    
    }
	SumW += W[P];
  }

  for(P=0; P<=out->HeaderN.x/2; P++){
	W[P] /=SumW;
  for(theta=0; theta < out->HeaderN.y; theta++) {
  for(phi  =0; phi   < out->HeaderN.z; phi++) {
    mrcPixelDataGet(in, P, theta, phi, &re, mrcPixelRePart, mrcPixelHowNearest);
    mrcPixelDataGet(in, P, theta, phi, &im, mrcPixelImPart, mrcPixelHowNearest);
    re *= W[P];
    im *= W[P];
    mrcPixelDataSet(out, P, theta, phi, re, mrcPixelRePart);
    mrcPixelDataSet(out, P, theta, phi, im, mrcPixelImPart);
  }
  }
  }
  free(W);
}

void/*OneLine inverseFourierTransform*/
lmrcImageRadonTransfromInverseFourierTransform(mrcImage* out, mrcImage* in, int mode)
{
  double   data;
  mrcImage tmpImg;
  mrcImage tmpFT;
  int      p, theta, phi;

  out->Header = in->Header;
  out->HeaderMode = mrcFloatRadonImage;
  mrcInit(out, NULL);

  for(theta=0; theta<in->HeaderN.y; theta++) {
  for(phi=0;   phi<in->HeaderN.z;   phi++){
    lmrcImageRadonTransformFourierTransformOneLineGet(&tmpFT, in, theta, phi, 0);
    lmrcImageFFT(&tmpImg, &tmpFT, 0);
    for(p=0; p<tmpImg.HeaderN.x; p++) {
      mrcPixelDataGet(&tmpImg, p, 0, 0, &data, mrcPixelRePart, mrcPixelHowNearest);
      mrcPixelDataSet(out, p, theta, phi, data, mrcPixelRePart);    
    }
	mrcImageFree(&tmpFT, 0);
	mrcImageFree(&tmpImg, 0);
  }
  }

}

void
lmrcImageRadonTransformFourierTransformOneLineGet(mrcImage* out, mrcImage* in, int theta, int phi, int mode)
{
  double re, im;
  int    P;

  out->Header = in->Header;
  out->HeaderN.y = out->HeaderN.z = 1;
  mrcInit(out, NULL);

  for(P=0; P<=out->HeaderN.x/2 ;P++){
    mrcPixelDataGet(in, P, theta, phi, &re, mrcPixelRePart, mrcPixelHowNearest);
    mrcPixelDataGet(in, P, theta, phi, &im, mrcPixelImPart, mrcPixelHowNearest);
    mrcPixelDataSet(out, P, 0, 0, re, mrcPixelRePart);
    mrcPixelDataSet(out, P, 0, 0, im, mrcPixelImPart);
  }
}
