/*
# powerspectraTangentLine : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : powerspectraTangentLine 
# Attention
#   $Loccker$
#  	$State$ 
#
*/
/* $Log$ */
static char __sccs_id[] = "%Z%lctfDetermination ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "./powerspectraTangentLine.h"
#include "./ctfInfoWrite2.h"
#define DEBUG
#define DEBUG2
#include "genUtil.h"
#include "Vector.h"
#include "nr2.h"
#include "Memory.h"

typedef struct stepInfo{
	float min;
	float max;
	float step;
	long  Number;
}stepInfo;

typedef struct iterationInfo{
	long  degree;
	long  CutLowSize;
	long  CutHighSize;
	float CutLine;
	float Emin;
	float Emax;
}iterationInfo;
	

double __power(double x,int a)
{
	int i;
	double y = 1.0;
	
	for(i=0 ; i<a ; i++){
		y *= x;
	}
	return(y);
}

void __stepNumberCulc(stepInfo *sInfo, long degree)
{
	long i;
	for(i=0 ; i<= degree ; i++){
		sInfo[i].Number =  (long) ((sInfo[i].max - sInfo[i].min )/ sInfo[i].step);
		if(sInfo[i].Number < 1){
			sInfo[i].Number = 1;
		}
	}
}

/*
mode = 1  belowLine
     = -1 aboveLine
*/
void	
__CoefficientDetermine(floatVector* spacing ,floatVector* Plog ,floatVector* tmpcoefficient ,stepInfo* sInfo,iterationInfo* iInfo, float mode)
{
	long i,j,k,l;
	long AdvanceRatio = 1;
	long Number[iInfo->degree+1];
	unsigned long long int  belowN;
	unsigned long long int fewerN;
	unsigned long n;
	unsigned long long int  sum = 1;
	float coefficient[iInfo->degree+1];
	float E;
	float minTangent;
	floatVector* Tangent;

#ifdef DEBUG
	if(mode == 1.0){
		DEBUGPRINT("BelowLineEstimation ");
	} else if(mode == -1.0){
		DEBUGPRINT("AboveLineEstimation ");
	} else{
		DEBUGPRINT("CoefficientDetermine don't support this mode\nprogram stop");
		exit(1);
	}
	DEBUGPRINT1("degree:%2ld\n",iInfo->degree);
#endif
	Tangent = floatVectorInit(NULL,spacing->size);

	//iInfo->Emax;
	for(j=0 ; j<=iInfo->degree ; j++){
		sum *= sInfo[j].Number;
		DEBUGPRINT5("StepCondition[%2ld] Min: %+8.3lf Max: %+8.3lf StepSize: %6.3f StepNumber: %4ld\n",j,sInfo[j].min,sInfo[j].max,sInfo[j].step,sInfo[j].Number);
	}
	DEBUGPRINT1("sum:%llu\n",sum);
	
	for(n=0 ; n< sum; n++){	
		E = 0.0;
		minTangent = 0.0;
		for(j=0 ; j<=iInfo->degree; j++){
			fewerN = 1;
			for(k=0 ; k<j ; k++){
				fewerN *= sInfo[k].Number; 
			}
			belowN = fewerN * sInfo[j].Number;
			coefficient[j] = (long)((n % belowN)/fewerN)* sInfo[j].step + sInfo[j].min;
			minTangent += coefficient[j]*__power(spacing->data[iInfo->CutHighSize],j); 
		}

		if(minTangent < iInfo->CutLine){
			E = iInfo->Emax;
		}
		
		for(i=iInfo->CutLowSize ; i<=iInfo->CutHighSize ; i++){
			Tangent->data[i] = coefficient[0];
			for(j=1 ; j<=iInfo->degree ; j++){
				Tangent->data[i] += coefficient[j]*__power(spacing->data[i],j);
			}
			E += fabs(Tangent->data[i] - Plog->data[i]);
			
			if((Tangent->data[i] - Plog->data[i])*mode > 0 || Tangent->data[i] < iInfo->CutLine || E>iInfo->Emin){
				E = iInfo->Emax;
				break;
			}
		}
		

		if(E <= iInfo->Emin){
			for(j=0 ; j<=iInfo->degree ; j++){
				tmpcoefficient->data[j] = coefficient[j];
				DEBUGPRINT2("%2ld:%+10.3e ",j,tmpcoefficient->data[j]);
			}
			DEBUGPRINT2("E=%10.3e Emin=%10.3e \n",E,iInfo->Emin);
			iInfo->Emin = E;
		}
	}
	DEBUGPRINT("result: ");
#ifdef DEBUG
	for(j=0 ; j<=iInfo->degree ; j++){
		DEBUGPRINT2("%2ld: %+10.3e ",j,tmpcoefficient->data[j]);
	}
#endif
	DEBUGPRINT1("Emin= %10.3e\n",iInfo->Emin);
}

/*mode 0  above & below
	  -1  below
	   1  above*/
void
TangentLine(floatVector* spacing, floatVector* scatter, float** belowCoefficient, float** aboveCoefficient, ctfInfo* ini, lctfDetermineInfo* linfo, int mode)
{	
	long i,j;
	floatVector* tmpcoefficient;
	float E;
	float Pmax = 0.0;
	float tmp;
	float tmpEmin;
	long CutLowSize = 0;
	long CutHighSize = 0;
	floatVector* Plog;
	stepInfo sInfo[linfo->degree+1];
	iterationInfo iInfo;

	DEBUGPRINT("TangentLine Start\n");
	Plog = floatVectorInit(NULL,spacing->size);
	iInfo.CutLine = 0.0;
	iInfo.degree = linfo->degree;
	
	for(i=0;i<=linfo->degree;i++){
		sInfo[i].step = linfo->step;
		sInfo[i].min = linfo->min;
		sInfo[i].max = linfo->max;
	}
	__stepNumberCulc(sInfo,linfo->degree);
	
	iInfo.CutLowSize = 0;
	iInfo.CutHighSize =0;
	iInfo.Emax = 0.0;

	tmpcoefficient = floatVectorInit(NULL,linfo->degree);
	
	for(i=0;i<spacing->size;i++){
		Plog->data[i] = log10(scatter->data[i]);

		if(Pmax < Plog->data[i]){
			Pmax = Plog->data[i];
		}
		
		if(spacing->data[i] < ini->CutLow){
			iInfo.CutLowSize = i+1;
		}
		if(spacing->data[i] < ini->CutHigh){
			iInfo.CutHighSize = i;
		}

		if((spacing->data[i] > ini->CutLow) && (spacing->data[i] < ini->CutHigh)){
			iInfo.Emax += Plog->data[i];
		}
	}
	iInfo.Emin = iInfo.Emax;
	tmpEmin = iInfo.Emin;


/*below*/
	if(0 == mode || -1 == mode){
		DEBUGPRINT("below\n");
		iInfo.degree = 0;
		sInfo[0].step = 0.01;
		__stepNumberCulc(sInfo,linfo->degree);
		__CoefficientDetermine(spacing,Plog,tmpcoefficient,sInfo,&iInfo,1.0);
		belowCoefficient[0][0] = tmpcoefficient->data[0];
		sInfo[0].step = linfo->step;
		iInfo.CutLine = tmpcoefficient->data[0] -0.1;
		DEBUGPRINT2("%2d: %10.3e  \n", 0, tmpcoefficient->data[0]);
		
		if(linfo->degree > 0){
			iInfo.degree = 1;
			__stepNumberCulc(sInfo,linfo->degree);
			__CoefficientDetermine(spacing,Plog,tmpcoefficient,sInfo,&iInfo,1.0);
			for(j=0 ; j<=iInfo.degree ; j++){
				belowCoefficient[1][j] = tmpcoefficient->data[j];
				DEBUGPRINT2("%2ld: %10.3e  ",j,tmpcoefficient->data[j]);
			}
			DEBUGPRINT("\n");
		}
		for(i=2 ; i<linfo->degree+1 ; i++){
			iInfo.degree = i;
			sInfo[i-1].step = sInfo[i-1].step * 100;
			sInfo[i].step = sInfo[i].step * 100;
		 	__stepNumberCulc(sInfo,linfo->degree);
			__CoefficientDetermine(spacing,Plog,tmpcoefficient,sInfo,&iInfo,1.0);
			
		 	sInfo[i-2].min = tmpcoefficient->data[i-2];
		 	sInfo[i-2].max = tmpcoefficient->data[i-2];
		 	sInfo[i-1].step = sInfo[i-1].step/100;
		 	sInfo[i].step = sInfo[i].step/100;
	
			sInfo[i-1].min = tmpcoefficient->data[i-1] - 100*sInfo[i-1].step;
			sInfo[i-1].max = tmpcoefficient->data[i-1] + 100*sInfo[i-1].step;
			sInfo[i].min = tmpcoefficient->data[i] - 100*sInfo[i].step;
			sInfo[i].max = tmpcoefficient->data[i] + 100*sInfo[i].step;
			
			__stepNumberCulc(sInfo,linfo->degree);
			__CoefficientDetermine(spacing,Plog,tmpcoefficient,sInfo,&iInfo,1.0);
			sInfo[i-1].min = linfo->min;
			sInfo[i-1].max = linfo->max;
			sInfo[i].min = linfo->min;
			sInfo[i].max = linfo->max;
			for(j=0 ; j<=i ; j++){
				 belowCoefficient[i][j] = tmpcoefficient->data[j];
				 DEBUGPRINT2("%2d: %10.3e  ", j, tmpcoefficient->data[j]);
			}
			DEBUGPRINT("\n");
		}
		iInfo.CutLine = 0.0;
	}
/*below end*/
/*above initial*/
	if(0 == mode || 1 == mode){
		for(i=0 ; i<=linfo->degree ; i++){
			sInfo[i].step =linfo->step * 10;
			sInfo[i].min = linfo->min * 10;
			sInfo[i].max = linfo->max * 10;
		}
		tmpcoefficient = floatVectorInit(NULL,linfo->degree+1);
		iInfo.Emin = tmpEmin;
		
	/*subtract noise*/
	/*	for(i=iInfo.CutLowSize ; i<=iInfo.CutHighSize ; i++){
			fprintf(stdout,"%10.3f %10.3f",spacing->data[i],Plog->data[i]);
			for(j=0 ; j<=linfo->degree ; j++){
				Plog->data[i] -= belowCoefficient[linfo->degree][j]*__power(spacing->data[i] ,j);
			}
			fprintf(stdout,"%10.3f\n",Plog->data[i]);
		}
	*/
	/*above start*/
		/*above*/
		fprintf(stdout,"above\n");
		iInfo.degree = 0;
		__stepNumberCulc(sInfo,linfo->degree);
		__CoefficientDetermine(spacing,Plog,tmpcoefficient,sInfo,&iInfo,-1.0);
		aboveCoefficient[0][0] = tmpcoefficient->data[0];
		DEBUGPRINT2("%2d: %10.3e  \n", 0, tmpcoefficient->data[0]);
	
		if(linfo->degree > 0){
			iInfo.degree = 1;
			__stepNumberCulc(sInfo,linfo->degree);
			__CoefficientDetermine(spacing,Plog,tmpcoefficient,sInfo,&iInfo,-1.0);
			aboveCoefficient[1][0] = tmpcoefficient->data[0];
			aboveCoefficient[1][1] = tmpcoefficient->data[1];
			for(i=0 ; i<iInfo.degree+1 ; i++){
				fprintf(stdout,"%2ld: %10.3e  ",i,tmpcoefficient->data[i]);
			}
			fprintf(stdout,"\n");
		}
		
		for(j= 2 ; j<=linfo->degree ; j++){
			iInfo.degree = j;
			sInfo[j].step = sInfo[j].step * 100;
			sInfo[j-1].step = sInfo[j-1].step * 100;
			__stepNumberCulc(sInfo,linfo->degree);
			__CoefficientDetermine(spacing,Plog,tmpcoefficient,sInfo,&iInfo,-1.0);
		
			sInfo[j-2].step = sInfo[j-2].step / 10;
			sInfo[j-2].min = tmpcoefficient->data[j-2] - 1000*sInfo[j-2].step;
			sInfo[j-2].max = tmpcoefficient->data[j-2] + 1000*sInfo[j-2].step;
		
			sInfo[j-1].step = sInfo[j-1].step /10;
			sInfo[j-1].min = tmpcoefficient->data[j-1] - 10*sInfo[j-1].step;
			sInfo[j-1].max = tmpcoefficient->data[j-1] + 10*sInfo[j-1].step;
		
			sInfo[j].step = sInfo[j].step /10;
			sInfo[j].min = tmpcoefficient->data[j] - 10*sInfo[j].step;
			sInfo[j].max = tmpcoefficient->data[j] + 10*sInfo[j].step;
		
			__stepNumberCulc(sInfo,linfo->degree);
			__CoefficientDetermine(spacing,Plog,tmpcoefficient,sInfo,&iInfo,-1.0);
			sInfo[j-2].min = tmpcoefficient->data[j-2];
			sInfo[j-2].max = tmpcoefficient->data[j-2];
			
			sInfo[j-1].step = linfo->step;
			sInfo[j-1].min = tmpcoefficient->data[j-1] - 100*sInfo[j-1].step;
			sInfo[j-1].max = tmpcoefficient->data[j-1] + 100*sInfo[j-1].step;
		
			sInfo[j].step = linfo->step;
			sInfo[j].min = tmpcoefficient->data[j] - 100*sInfo[j].step;
			sInfo[j].max = tmpcoefficient->data[j] + 100*sInfo[j].step;
	
			__stepNumberCulc(sInfo,linfo->degree);
			__CoefficientDetermine(spacing,Plog,tmpcoefficient,sInfo,&iInfo,-1.0);
	
			sInfo[j-1].min = linfo->min;
			sInfo[j-1].max = linfo->max;
			sInfo[j-1].step = linfo->step;
			sInfo[j].min = linfo->min;
			sInfo[j].max = linfo->max;
			sInfo[j].step = linfo->step;
	
			for(i=0 ; i<=j ; i++){
				aboveCoefficient[j][i] = tmpcoefficient->data[i];
				DEBUGPRINT2("%2ld: %10.3e  ",i,tmpcoefficient->data[i]);
			}
			DEBUGPRINT("\n");
		}
	}
/*above end*/	
#ifdef DEBUG2
	TangentLinePrint(stderr, spacing, scatter, belowCoefficient, aboveCoefficient, linfo, mode);
#endif
}

void
TangentLinePrint(FILE* fpt, floatVector* spacing, floatVector* scatter, float** belowCoefficient, float** aboveCoefficient, lctfDetermineInfo* linfo, int mode)
{	
	int i, j;

	fprintf(fpt,"degree  : ");
	for(i=0 ; i<=linfo->degree ; i++){
		fprintf(fpt,"%8d",i);
	}
	fprintf(fpt,"\n");

	fprintf(fpt,"above\n");
	for(i=0 ; i<=linfo->degree ; i++){
		fprintf(fpt,"%6d   ",i);
		for(j=0 ; j<=i ; j++){
			fprintf(fpt,"%+7.3g ",aboveCoefficient[i][j]);
		}
		fprintf(fpt,"\n");
	}

	fprintf(fpt,"below\n");
	for(i=0 ; i<=linfo->degree ; i++){
		fprintf(fpt,"%6d   ",i);
		for(j=0 ; j<=i ; j++){
			fprintf(fpt,"%+7.3g ",belowCoefficient[i][j]);
		}
		fprintf(fpt,"\n");
	}
	fprintf(fpt,"\n");
}
