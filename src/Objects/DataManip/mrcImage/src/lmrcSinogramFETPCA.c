/*
# lmrcSinogramFETPCA : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : lmrcSinogramFETPCA 
# Attention
#   $Loccker$
#  	$State$ 
#
*/
/* $Log$ */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "genUtil.h"
#include "Memory.h"
#include "File.h"
#include "eosString.h"
#include "../inc/mrcImage.h"
#include "Array.h"
#include "lmrcSinogramFET.h"
#define ONELINEMAX 20

void __FETpcadWrite(FILE* out, Array* in, int lambdaRank);

void
lmrcSinogramFETPCA(lmrcSinogramFETPCAInfo in, int mode){
	int i,j,k,l,count,n,y;
	double data, data1, data2;
	char s[256];
	mrcImage temp;
	
	y = in.inImage->HeaderN.y;
	in.X.dim = 2;
	in.X.n[0] = in.inImage->HeaderN.x;
	in.X.n[1] = y * in.inImage->HeaderN.z;
	arrayInit(&(in.X), "X in lmrcSinogramFETPCA");
	in.Ave.dim = 2;
	in.Ave.n[0] = in.inImage->HeaderN.x;
	in.Ave.n[1] = y * in.inImage->HeaderN.z;
	arrayInit(&(in.Ave), "Ave in lmrcSinogramFETPCA");
	
	for(k=0; k<in.inImage->HeaderN.z; k++){
		for(j=0; j<in.inImage->HeaderN.y; j++){
			for(i=0; i<in.inImage->HeaderN.x; i++){
				mrcPixelDataGet(in.inImage,i,j,k,&data, mrcPixelRePart, mrcPixelHowNearest);
				arrayDataSet2(in.X, i, (k*y)+j, (float)data);
			}
		}
	}
	//fprintf(stderr,"before arrayPCA\n");
	arrayPCA(&(in.u), &(in.C), &(in.lambda), &(in.X), &(in.Ave), 0);
	//fprintf(stderr,"after arrayPCA\n");

	//arrayWriteToFile(in.Out, &(in.X), "in main");
	fprintf(in.Out, "Result\n");
	fprintf(in.Out, "lambda^2: lambda^2\n");
	arrayWriteToFile(in.Out, &(in.lambda), "in main");
	fprintf(in.Out, "u: unit vector\n");
	arrayWriteToFile(in.Out, &(in.u), "in main");
	fprintf(in.Out, "C: covariance matrix\n");
	arrayWriteToFile(in.Out, &(in.C), "in main");

	in.fetpcad.dim = 3;
	in.fetpcad.n[0] = in.inImage->HeaderN.x;
	in.fetpcad.n[1] = y;
	in.fetpcad.n[2] = in.inImage->HeaderN.z;
	arrayInit(&(in.fetpcad), "fetpcad in lmrcSinogramFETPCA");

	for(k=0; k<in.inImage->HeaderN.z; k++){
		for(j=0; j<in.inImage->HeaderN.y; j++){
			for(i=0; i<in.inImage->HeaderN.x; i++){
				data = 0;
				for(l=0; l<in.inImage->HeaderN.x; l++) {
					data += arrayDataGet2(in.X, l, (k*y)+j) * arrayDataGet2(in.u, l, i);
				}
				arrayDataSet3(in.fetpcad, i, j, k, (float)data);
			}
		}
	}
	arrayWriteToFile(in.Out, &(in.fetpcad), "in main");
	__FETpcadWrite(stdout, &(in.fetpcad), 4);
}						  

void 
__FETpcadWrite(FILE* out, Array* in, int lambdaRank)
{
	int i,j,k,l,cur;
	float data;
	int oneLine;

	oneLine = ONELINEMAX/lambdaRank;
	fprintf(out,"fetpcad start\n");
	for(l=0; l<in->n[2]; l+=oneLine){
		for(j=0; j<in->n[1]; j++){
			for(k=0; k<oneLine; k++){
				cur =  l+k;
				for(i=0; i<lambdaRank; i++){
					data = arrayDataGet3(*in,i,j,cur);
					fprintf(out,"%f\t",data);
				}
				fprintf(out,"\t");
			}
			fprintf(out,"\n");
		}
		fprintf(out,"\n");
	}
}
	
