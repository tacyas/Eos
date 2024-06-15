/*
# lmrcImageFourierShellCorrelation : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : lmrcImageFourierShellCorrelation 
# Attention
#   $Loccker$
#  	$State$ 
#
*/
/* $Log$ */

#undef DEBUG
#include "genUtil.h"
#include "Memory.h"
#include "./lmrcImageFourierShellCorrelation.h"
#include "./mrcRefUtil.h"

void
lmrcImageFourierShellCorrelation(lmrcImageFourierShellCorrelationResult* res, mrcImage* in1, mrcImage* in2, lmrcImageFourierShellCorrelationInfo linfo, int mode, int mode2)
{
/* variables */
    mrcImage ft1;
    mrcImage ft2;
    mrcImage tmpimg;
    int X,Y,Z,R,max,tempmode;
	double* data; 
	double* RR;
    int *N;
    double *tmp1,*tmp2,*tmp3;
    double rdata1,idata1,rdata2,idata2,XX,YY,ZZ,f1,f2,nr1,nr2,ni1,ni2,dr,di,d,dp,tmpR;
    mrcImageParaTypeRealCoord shift;
	double minW;

	double H      = linfo.High;
	double L      = linfo.Low;
	double delta = linfo.Delta;

	
/* begin */
    if ((mode2&2)==2){
        lmrcImageCenterGet(&tmpimg ,in1 , in2->HeaderN.x, in2->HeaderN.y, in2->HeaderN.z,
               (in1->HeaderN.x - 1.0) /2.0, (in1->HeaderN.y - 1.0) /2.0, (in1->HeaderN.z - 1.0) /2.0, 2);
        shift.x = shift.y = shift.z =0;
        mrcImageFree(in1,"");
        in1->Header=in2->Header;
        mrcInit(in1,NULL);
        lmrcImageCopy(in1,&tmpimg,shift);
        mrcImageFree(&tmpimg,"");
    }
    if ((mode&2)==2){
        max = 2;
    } else {
        max=floor(sqrt(SQR(1/in1->HeaderLength.x)+SQR(1/in1->HeaderLength.y)+SQR(1/in1->HeaderLength.z) ) /delta /2  +0.5)+1;
    }
    DEBUGPRINT1("max=%d\n",max);

    tmp1 = (double *)memoryAllocate(sizeof(double)*max, "in lmrcImageFourierShellCorrelation");
    tmp2 = (double *)memoryAllocate(sizeof(double)*max, "in lmrcImageFourierShellCorrelation");
    tmp3 = (double *)memoryAllocate(sizeof(double)*max, "in lmrcImageFourierShellCorrelation");
    N    = (int*)memoryAllocate(sizeof(int)*max, "in lmrcImageFourierShellCorrelation");
    data = (double*)memoryAllocate(sizeof(double)*max, "in lmrcImageFourierShellCorrelation");
    RR   = (double*)memoryAllocate(sizeof(double)*max, "in lmrcImageFourierShellCorrelation");

	for (R = 0; R < max; R++) {
        tmp1[R]=tmp2[R]=tmp3[R]=0;
        N[R]=0;
        DEBUGPRINT1("%d ",R);
    }
    lmrcImageFFT(&ft1 ,in1 ,0);
    lmrcImageFFT(&ft2 ,in2 ,0);

    for(Z=-ft1.HeaderN.z/2.0; Z<ft1.HeaderN.z/2.0; Z++) {
        DEBUGPRINT1("%d ",Z);
    for(Y=-ft1.HeaderN.y/2.0; Y<ft1.HeaderN.y/2.0; Y++) {
    for(X=0; X<=ft1.HeaderN.x/2.0; X++) {
        mrcPixelDataGet(&ft1, X, Y, Z, &rdata1, mrcPixelRePart, mrcPixelHowNearest);
        mrcPixelDataGet(&ft1, X, Y, Z, &idata1, mrcPixelImPart, mrcPixelHowNearest);
        mrcPixelDataGet(&ft2, X, Y, Z, &rdata2, mrcPixelRePart, mrcPixelHowNearest);
        mrcPixelDataGet(&ft2, X, Y, Z, &idata2, mrcPixelImPart, mrcPixelHowNearest);
        XX = X/(ft1.HeaderLength.x*ft1.HeaderN.x);
        YY = Y/(ft1.HeaderLength.y*ft1.HeaderN.y);
        ZZ = Z/(ft1.HeaderLength.z*ft1.HeaderN.z);
        tmpR=XX*XX+YY*YY+ZZ*ZZ;
        tempmode=mode;
        if ((tempmode&4)==4){
            if (in1->HeaderN.z==1) {
                if (Y==0) {
                    continue ;
                }
            } else {
                if (Z==0) continue ;
            }
            tempmode -= 4;
         }
         if ((tempmode&2)==2){
             if (L*L< tmpR && tmpR < H*H) {
                 R=0;
             } else {
                 R=1;
             }
         } else {
             R=floor(sqrt(tmpR)/delta +0.5);
         }
         switch (tempmode&0x1) {
             case 0: {
                 tmp1[R] += rdata1*rdata2 + idata1*idata2;
                 tmp2[R] += rdata1*rdata1 + idata1*idata1;
                 tmp3[R] += rdata2*rdata2 + idata2*idata2;
                 break;
		     }
             case 1: {
                f1 = rdata1*rdata1 + idata1*idata1;
                f2 = rdata2*rdata2 + idata2*idata2;
                if (f1 != 0 && f2 != 0 ) {
                	f1=sqrt(f1);
                	f2=sqrt(f2);
                	tmp2[R] += f1*f2;
                	nr1=rdata1/f1;
                	ni1=idata1/f1;
                	nr2=rdata2/f2;
                	ni2=idata2/f2;
                	dr=nr1-nr2;
                	di=ni1-ni2;
                  	if (dr != 0.0 ) {
                    	d=sqrt(dr*dr+di*di);
                    	if (d>2) d=2 ;
                    	dp=2*asin(d/2);
                    	tmp1[R] += f1*f2*dp;
                  	}
                 }
                 break;
		     }
        }
        N[R]++;
    }
    }
    }

    tempmode=mode;
    if ((mode&4)==4){
        tempmode -= 4;
    }
    for (R=0 ;R<max ;R++) {
        switch (tempmode&0x1) {
            case 0: {
                if (tmp2[R]!=0 && tmp3[R]!=0){
                    data[R]=tmp1[R]/sqrt(tmp2[R]*tmp3[R]);
                } else {
                    data[R]=0.0;
                }
                break;
		    }
            case 1: {
                if (tmp2[R]!=0){
                    data[R]=tmp1[R]/tmp2[R];
                } else {
                    data[R]=0.0;
                }
                break;
			}
        }
		RR[R] = R*delta;
		/*
        if ((tempmode&2) != 2) {
            fprintf(stdout,"%f %f %d \n", RR[R], data[R], N[R]);
        }
		*/
    }
    if ((tempmode&2) == 2){
		RR[0] = H;
		RR[1] = L;
		/*
        fprintf(stdout,"%f %f %f \n", H, L, data[0]);
		*/
    }

	res->data = data;
	res->N    = N;
	res->R    = RR;
	res->nR   = max;

	if(res->flagSNR) {
		res->SNR =  (double*)memoryAllocate(sizeof(double)*max, "in lmrcImageFourierShellCorrelation");
    	for (R=0 ;R<max ;R++) {
			if(res->data[R] == 1) {
				res->SNR[R] = MAXFLOAT;
			} else {
				res->SNR[R] = 2*res->data[R]/(1 - res->data[R]);
			}
		}
	}
	if(res->flagFSCfull) {
		res->FSCfull = (double*)memoryAllocate(sizeof(double)*max, "in lmrcImageFourierShellCorrelation");
    	for (R=0 ;R<max ;R++) {
			res->FSCfull[R] = 2*res->data[R]/(1 + res->data[R]);
		}
	}
	if(res->flagCref || res->flagNoiseWeighted) {
		res->Cref = (double*)memoryAllocate(sizeof(double)*max, "in lmrcImageFourierShellCorrelation");
    	for (R=0 ;R<max ;R++) {
			if(res->data[R] <= 0 ) {
				res->Cref[R] = 0;
			} else {
				res->Cref[R] = sqrt(2*res->data[R]/(1 + res->data[R]));
			}
		}
	}

	minW = 1;
	if(res->flagNoiseWeighted) {
		res->NoiseWeighted = (double*)memoryAllocate(sizeof(double)*max, "in lmrcImageFourierShellCorrelation");
    	for (R=0 ;R<max ;R++) {
			if(res->Cref[R]<=0) {
				minW = 0;
			}
			res->NoiseWeighted[R] = minW*res->Cref[R]*exp(-res->Brestore/4.0*SQR(res->R[R]));
		}
	}

    mrcImageFree(&ft1,"");
    mrcImageFree(&ft2,"");
    free(tmp1);
    free(tmp2);
    free(tmp3);
    //free(N);
}


void
lmrcImageFourierShellCorrelationPrint(FILE* fpt, lmrcImageFourierShellCorrelationResult* res, lmrcImageFourierShellCorrelationInfo linfo, int mode, int mode2)
{
	int R;
    for (R=0 ;R<res->nR; R++) {
        if ((mode&2) != 2) {
            fprintf(fpt, "%f % 10.6f %10d ", res->R[R], res->data[R], res->N[R]);
        }
		if(res->flagSNR) {
			fprintf(fpt, "SNR % 15.6e ", res->SNR[R]);
		}
		if(res->flagFSCfull) {
			fprintf(fpt, "FSCfull % 10.6f ", res->FSCfull[R]);
		}
		if(res->flagCref) {
			fprintf(fpt, "Cref %10.6f ", res->Cref[R]);
		}
		if(res->flagNoiseWeighted) {
			fprintf(fpt, "NoiseWeighted % 15.6e ", res->NoiseWeighted[R]);
		}
		fprintf(fpt, "\n");
	}
    if ((mode&2) == 2){
        fprintf(stdout,"%f %f %f %d %f %d \n", res->R[0], res->R[1], res->data[0], res->N[0], res->data[1], res->N[1]);
	}
}
