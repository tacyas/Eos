/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% lmrcMultiFFTCentralSectionsCompare ver %I%
#%Z% Created by
#%Z%
#%Z% Usage : lmrcMultiFFTCentralSectionsCompare
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%lmrcMultiFFTCentralSectionsCompare ver%I%; Date:%D% %Z%";

#define DEBUG
#include "genUtil.h"
#include "Memory.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "./lmrcFFTCentralSection.h"
#include "../inc/mrcImage.h"

void
lmrcMultiFFTCentralSectionsCompare(lmrcMultiFFTCentralSectionsCompareInfoOut* Out, mrcImage* in, mrcImage* volume, lmrcMultiFFTCentralSectionsCompareInfo* linfo, int mode, int nummode){
    mrcImageParaTypeReal x, y;
    double likelihood, prelikelihood;
    double likelihoodxre, likelihoodyre, likelihoodxyre;
    double likelihoodxim, likelihoodyim, likelihoodxyim;
    double rein, imin;
    double inOrigin, inlim;
    double revol, imvol;
    int i,j, flag;
    clock_t start,end;
    int sig_x,sig_y;
    double sigma, sigMax=0, sigMin=100;;
    double sum2d, sum3d;
    int count;

    DEBUGPRINT("lmrcMultiFFTCentralSectionsCompare start\n");

    if(mode != 1){
        lmrcMultiFFTCentralSectionsCompareSigma(in, linfo, 0);//0:sigma=1 1:sigmaCalcu
    }

    for(i=0; i < linfo->OutSize; i++){
        flag =0;
        for(j=0; j< linfo->PriorSize; j++){
            if(Out[i].OriginNum == linfo->Prior[j].OriginNum){
            if(mode == 1){
                likelihoodxre = 0.0;
                 likelihoodyre = 0.0;
                likelihoodxyre = 0.0;
                likelihoodxim = 0.0;
                likelihoodyim = 0.0;
                likelihoodxyim = 0.0;
                for(x=0; x <= in->HeaderN.x/2.0 ; x++){
                for(y=-in->HeaderN.y/2.0; y < in -> HeaderN.y/2.0 ; y++){
                    mrcPixelDataGet(in, x, y, 0, &rein, mrcPixelRePart, linfo->llinfo.llinfo.InterpMode);
                    //if(rein > 0){
                    mrcPixelDataGet(in, x, y, 0, &imin, mrcPixelImPart, linfo->llinfo.llinfo.InterpMode);
                    mrcPixelDataGet(&Out[i].out, x, y, 0, &revol, mrcPixelRePart, linfo->llinfo.llinfo.InterpMode);
                    mrcPixelDataGet(&Out[i].out, x, y, 0, &imvol, mrcPixelImPart, linfo->llinfo.llinfo.InterpMode);

                    likelihoodxre = likelihoodxre + rein*rein;
                    likelihoodxim = likelihoodxim + imin*imin;
                    likelihoodyre = likelihoodyre + revol*revol;
                    likelihoodyim = likelihoodyim + imvol*imvol;
                    likelihoodxyre = likelihoodxyre + rein*revol;
                    likelihoodxyim = likelihoodxyim + imin*imvol;
                    //}
                }
                }
                Out[i].Likelihood = likelihoodxyre/sqrt(likelihoodxre*likelihoodyre) + likelihoodxyim/sqrt(likelihoodxim*likelihoodyim);
            }else{
                likelihood = 1;
                prelikelihood = 0;
                sigma = 1;
                sig_x =0;
	              sum2d = 0.0;
		            sum3d = 0.0;

		            count = 0;
                for(x= 0; x <=0 ; x++){
                for(y= 0; y <=0 ; y++){
                   mrcPixelDataGet(in, x, y, 0, &rein, mrcPixelRePart, linfo->llinfo.llinfo.InterpMode);
                   mrcPixelDataGet(in, x, y, 0, &imin, mrcPixelImPart, linfo->llinfo.llinfo.InterpMode);
                   mrcPixelDataGet(&Out[i].out, x, y, 0, &revol, mrcPixelRePart, linfo->llinfo.llinfo.InterpMode);
                   mrcPixelDataGet(&Out[i].out, x, y, 0, &imvol, mrcPixelImPart, linfo->llinfo.llinfo.InterpMode);
		               count++;
                   sum2d += rein*rein + imin*imin;
                   sum3d += revol*revol + imvol*imvol;
                }
                }
		            sum2d = sqrt(sum2d/count);
		            sum3d = sqrt(sum3d/count);

                for(x= 0; x <= in -> HeaderN.x/2.0 ; x++){
                    sig_y=0;
                for(y= -in->HeaderN.y/2.0; y < in -> HeaderN.y/2.0 ; y++){
                   mrcPixelDataGet(in, x, y, 0, &rein, mrcPixelRePart, linfo->llinfo.llinfo.InterpMode);
                   //if(rein > 0 && linfo->Sigma[sig_x][sig_y] > 0.0){
                   mrcPixelDataGet(in, x, y, 0, &imin, mrcPixelImPart, linfo->llinfo.llinfo.InterpMode);
                   mrcPixelDataGet(&Out[i].out, x, y, 0, &revol, mrcPixelRePart, linfo->llinfo.llinfo.InterpMode);
                   mrcPixelDataGet(&Out[i].out, x, y, 0, &imvol, mrcPixelImPart, linfo->llinfo.llinfo.InterpMode);

		               rein /= sum2d;
		               imin /= sum2d;
		               revol /= sum3d;
		               imvol /= sum3d;

                   //prelikelihood =  prelikelihood + (((rein - revol)*(rein - revol) + (imin - imvol)*(imin - imvol))/((-2)));
                   prelikelihood =  prelikelihood + (((rein - revol)*(rein - revol) + (imin - imvol)*(imin - imvol))/((-2)*linfo->Sigma[sig_x][sig_y]));
                   // DEBUGPRINT5(" preLikelihood likelihood, Sigma %d    %e  %e   %e  %e \n", i, prelikelihood, sigma, likelihood, linfo->Sigma[sig_x][sig_y]);
                   //}
                   sig_y ++;
                }
                sig_x ++;
                }
 //               DEBUGPRINT3("sigma likelihood %f %f %f\n", linfo->Sigma[sig_x-1][sig_y-1], prelikelihood, likelihood);
                  Out[i].Likelihood = exp(prelikelihood)/(2*M_PI);
            }
            flag = 1;
            }
        }
        if(flag == 0){
            Out[i].Likelihood = 0;
        }
 //  DEBUGPRINT3("Likelihood  %d     %f   %e\n", i, prelikelihood, Out[i].Likelihood);
    }
    DEBUGPRINT("lmrcMultiFFTCentralSectionsCompare end\n");
}

void
lmrcMultiFFTCentralSectionsCompareNormalization(lmrcMultiFFTCentralSectionsCompareInfoOut* Out, lmrcMultiFFTCentralSectionsCompareInfo* linfo, int mode){

    int i;
    double sum=0.0;
    double min;
    double max;
    double delta = 0.0;
    double weight = 0.0;
    double* preProb;

    min = Out[0].Post;
    max = Out[0].Post;

    if(mode ==1){
        preProb = (double*)malloc(sizeof(double)*linfo->OutSize);
        for(i=0; i < linfo->OutSize; i++){
            if(min > Out[i].Post){
                min = Out[i].Post;
            }else if(max < Out[i].Post){
                max = Out[i].Post;
            }
            sum = sum + Out[i].Post;
        }
 //       DEBUGPRINT1("lmrcMultiFFTCentralSectionsComapreNormalization sum: %f\n",sum);
        delta = max - min;
        for(i=0; i<linfo->OutSize; i++){
            preProb[i] = (exp((Out[i].Post - min)/delta) - 1)/(exp(1)-1);
            weight = weight + exp(preProb[i]);
        }

        for(i=0; i<linfo->OutSize; i++){
            if(Out[i].Post > 0){
                Out[i].Prob = exp(preProb[i])/weight;
                Out[i].Post = exp(preProb[i])/weight;
            }else{
                Out[i].Prob = 0;
                Out[i].Post = 0;
            }
        }
    }else{
        for(i=0; i<linfo->OutSize; i++){
            sum = sum + Out[i].Post;
        }
 //       DEBUGPRINT1("lmrcMultiFFTCentralSectionsComapreNormalization sum: %f\n",sum);
        for(i=0; i<linfo->OutSize; i++){
            if(sum != 0){
            Out[i].Prob = Out[i].Post / sum;
            Out[i].Post = Out[i].Post / sum;
            }else{
                Out[i].Prob = 1/(double)(linfo->OutSize);
            }

        }
    }
}

void
lmrcMultiFFTCentralSectionsCompareInfoWrite(FILE* fpt, char* filename, lmrcMultiFFTCentralSectionsCompareInfoOut* Out, lmrcMultiFFTCentralSectionsCompareInfo* linfo, float mode1, float mode2){
    int i;


    DEBUGPRINT1("lmrcMultiFFTCentralSectionsCompareInfoWrite: %d\n", linfo->OutSize);
    for(i=0; i< linfo->OutSize; i++){
        if(Out[i].Prob == 0){
        }else{
            fprintf(fpt,"%s %s %15.4f %15.4f %15.4f %s %15d %15.6e\n", filename, linfo->Out[i].EulerMode, Out[i].Rot[0]*DEGREE, Out[i].Rot[1]*DEGREE, Out[i].Rot[2]*DEGREE, Out[i].volume, Out[i].OriginNum, Out[i].Prob);
        }
    }
}

void
lmrcMultiFFTCentralSectionsCompareInfoWriteLikelihood(FILE* fpt, char* filename, lmrcMultiFFTCentralSectionsCompareInfoOut* Out, lmrcMultiFFTCentralSectionsCompareInfo* linfo, float mode1, float mode2){
    int i;

    for(i=0; i< linfo->OutSize; i++){
        if(Out[i].Prob == 0){
        }else{
            fprintf(fpt,"%s %s %15.4f %15.4f %15.4f %s %15d %15.6e\n", filename, linfo->Out[i].EulerMode, Out[i].Rot[0]*DEGREE, Out[i].Rot[1]*DEGREE, Out[i].Rot[2]*DEGREE, Out[i].volume, Out[i].OriginNum, Out[i].Likelihood);
        }
    }
}

void
lmrcMultiFFTCentralSectionsCompareInfoLimit(lmrcMultiFFTCentralSectionsCompareInfoOut* Out, lmrcMultiFFTCentralSectionsCompareInfo* linfo, float mode1, float mode2){
    int i,j;
    double sum=0;

    for(i=0; i< linfo->OutSize; i++){
        if(Out[i].Prob < mode1){
            Out[i].Prob = 0;
            Out[i].Post = 0;
        }else if(mode2 != 0){
            if(Out[0].Prob>mode2){
                Out[0].Prob = 1.0;
                sum = 1.0;
            }else if(sum <= mode2){
                sum = sum + Out[i].Prob;
            }else{
                Out[i].Prob = 0;
                Out[i].Post = 0;
            }
        }
    }
}

void
lmrcMultiFFTCentralSectionsCompareInfoSort(lmrcMultiFFTCentralSectionsCompareInfoOut Out[], int left, int right){

    int pl=left;
    int pr=right;
    int middle=(left+right)/2;
    lmrcMultiFFTCentralSectionsCompareInfoOut temp;
    double pivot;

    pivot = Out[middle].Prob;

    do{
        while(Out[pl].Prob > pivot) pl++;
        while(Out[pr].Prob < pivot) pr--;

        if(pl <= pr){
            temp = Out[pl];
            Out[pl] = Out[pr];
            Out[pr] = temp;
            pl++;
            pr--;
        }
    }while(pl <= pr);

    if(left < pr) lmrcMultiFFTCentralSectionsCompareInfoSort(Out, left, pr);
    if(pl < right) lmrcMultiFFTCentralSectionsCompareInfoSort(Out, pl, right);
}

void
lmrcMultiFFTCentralSectionsCompareInfoUpdate(lmrcMultiFFTCentralSectionsCompareInfoOut* Out, lmrcMultiFFTCentralSectionsCompareInfo* linfo){
    int i;

    for(i=0; i<linfo->PriorSize; i++){
                linfo->Out[linfo->Prior[i].OriginNum].Post = linfo->Prior[i].Prior * linfo->Out[linfo->Prior[i].OriginNum].Likelihood;
    }
}

void
lmrcMultiFFTCentralSectionsCompareInfoProbSet(lmrcMultiFFTCentralSectionsCompareInfo* linfo ,int mode){
    int i;
    for(i=0; i<linfo->PriorSize; i++){
        if(mode == 0){
            linfo->Prior[i].Prior = 1/(double)(linfo->PriorSize);
        }else if(mode == 1){
         //   linfo->Out[i].Post = linfo->Prior[i].Prior * linfo->Out[Prior[i].OriginNum].Likelihood;
        }
    }
}

void
lmrcMultiFFTCentralSectionsCompareInfoVariation(lmrcMultiFFTCentralSectionsCompareInfoOut* Out, lmrcMultiFFTCentralSectionsCompareInfo* linfo){
    int i,j;
    double var=0,temp=0;

    for(i=0; i< linfo->PriorSize; i++){
        for(j=0; j< linfo->OutSize; j++){
            if(linfo->Prior[i].OriginNum == Out[j].OriginNum){
                var = var + sqrt((Out[j].Prob - linfo->Prior[i].Prior)*(Out[j].Prob - linfo->Prior[i].Prior));
 /*       temp = Out[linfo->Prior[i].OriginNum].Prob - linfo->Prior[i].Prior;
        if(temp < 0){
            temp = temp * (-1);
        }
        var = var + temp;
    */
            }
        }
    }
    linfo->Variat = var;
    printf("Variation: %f\n",linfo->Variat);
}

void
lmrcMultiFFTCentralSectionsCompareSigma(mrcImage* in, lmrcMultiFFTCentralSectionsCompareInfo* linfo, int mode){

    mrcImageParaTypeReal x, y;
    double rein, imin;
    double revol, imvol;
    int i,j;
    int sig_x, sig_y;
    double sigma, sigMax=0, sigMin=100, delta;
    double inOrigin, inlim;

    linfo->Sigma = malloc(sizeof(double*)*(in->HeaderN.x));
    if(linfo->Sigma ==NULL){
        DEBUGPRINT("malloc error\n");
    }
    sig_x = 0;
    for(x=-in->HeaderN.x/2.0; x< in->HeaderN.x/2.0; x++){
        linfo->Sigma[sig_x] = malloc(sizeof(double)*in->HeaderN.y);
        if(linfo->Sigma[sig_x]==NULL){
            DEBUGPRINT("malloc error\n");
        }
        sig_x ++;
    }
    if(mode == 1){
        mrcPixelDataGet(in, 0, 0, 0, &inOrigin, mrcPixelRePart, linfo->llinfo.llinfo.InterpMode);
        inlim = inOrigin / 1000;

        sig_x=0;
        for(x = -in->HeaderN.x/2.0 ; x < in->HeaderN.x/2.0; x++){
        sig_y=0;
        for(y = -in->HeaderN.y/2.0 ; y < in->HeaderN.y/2.0; y++){
            sigma=0;
            mrcPixelDataGet(in, x, y, 0, &rein, mrcPixelRePart, linfo->llinfo.llinfo.InterpMode);
 //           mrcPixelDataGet(in, (x/(in->HeaderN.x/2.0))*(x/(in->HeaderN.x/2.0)), (y/(in->HeaderN.y/2.0))*(y/(in->HeaderN.y/2.0)), 0, &rein, mrcPixelRePart, linfo->llinfo.llinfo.InterpMode);
            if(rein > 0.0){
                for(i=0; i < linfo->PriorSize; i++){
                   mrcPixelDataGet(in , x, y, 0, &imin, mrcPixelImPart, linfo->llinfo.llinfo.InterpMode);
                   mrcPixelDataGet(&linfo->Out[i].out, x, y, 0, &revol, mrcPixelRePart, linfo->llinfo.llinfo.InterpMode);
                   mrcPixelDataGet(&linfo->Out[i].out, x, y, 0, &imvol, mrcPixelImPart, linfo->llinfo.llinfo.InterpMode);
                //    mrcPixelDataGet(in, (x/(in->HeaderN.x/2.0))*(x/(in->HeaderN.x/2.0)), (y/(in->HeaderN.y/2.0))*(y/(in->HeaderN.y/2.0)), 0, &rein, mrcPixelRePart, linfo->llinfo.llinfo.InterpMode);
                //    mrcPixelDataGet(in, (x/(in->HeaderN.x/2.0))*(x/(in->HeaderN.x/2.0)), (y/(in->HeaderN.y/2.0))*(y/(in->HeaderN.y/2.0)), 0, &imin, mrcPixelImPart, linfo->llinfo.llinfo.InterpMode);
                //    mrcPixelDataGet(&linfo->Out[linfo->Prior[i].OriginNum].out, (x/(in->HeaderN.x/2.0))*(x/(in->HeaderN.x/2.0)), (y/(in->HeaderN.y/2.0))*(y/(in->HeaderN.y/2.0)), 0, &revol, mrcPixelRePart, linfo->llinfo.llinfo.InterpMode);
                    mrcPixelDataGet(&linfo->Out[linfo->Prior[i].OriginNum].out, (x/(in->HeaderN.x/2.0))*(x/(in->HeaderN.x/2.0)), (y/(in->HeaderN.y/2.0))*(y/(in->HeaderN.y/2.0)), 0, &imvol, mrcPixelImPart, linfo->llinfo.llinfo.InterpMode);
                    sigma = sigma + linfo->Prior[i].Prior*((rein - revol)*(rein - revol) + (imin - imvol)*(imin - imvol));
                }
                linfo->Sigma[sig_x][sig_y] = sigma/2;

                if(sigMax < linfo->Sigma[sig_x][sig_y]){
                    sigMax = linfo->Sigma[sig_x][sig_y];
                }else if(sigMin > linfo->Sigma[sig_x][sig_y] && linfo->Sigma[sig_x][sig_y] > 0.0 ){
                //}else if(sigMin > linfo->Sigma[sig_x][sig_y] && linfo->Sigma[sig_x][sig_y] > 0.000001 ){
                    sigMin = linfo->Sigma[sig_x][sig_y];
                }//else if(linfo->Sigma[sig_x][sig_y] < 0.000001){
                 //   linfo->Sigma[sig_x][sig_y] = 0.0;
               // }

            }
            else{
                linfo->Sigma[sig_x][sig_y] = 0.0;
            }
 //       DEBUGPRINT3("sigma %d %d %f\n",sig_x, sig_y, linfo->Sigma[sig_x][sig_y]);
            sig_y++;
        }
        sig_x++;
        }
        DEBUGPRINT2("sigMax sigMin %e %e\n",sigMax, sigMin);
      linfo->SigMin = sigMin;
       // delta = sqrt((sigMax-sigMin)*(sigMax-sigMin));
 /*       for(sig_x =0; sig_x < (int)in->HeaderN.x; sig_x++){
        for(sig_y =0; sig_y < (int)in->HeaderN.y; sig_y++){
               linfo->Sigma[sig_x][sig_y] = linfo->Sigma[sig_x][sig_y]/(sigMin*2*M_PI);
           //    linfo->Sigma[sig_x][sig_y] = linfo->Sigma[sig_x][sig_y] /(sigMin*M_PI);

        }
        }*/
    }else{
        for(sig_x =0; sig_x < (int)in->HeaderN.x; sig_x++){
        for(sig_y =0; sig_y < (int)in->HeaderN.y; sig_y++){
            linfo->Sigma[sig_x][sig_y] = 1.0;
        }
        }
    }

}
