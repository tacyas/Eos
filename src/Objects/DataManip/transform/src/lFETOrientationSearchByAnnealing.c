/*
# lFETOrientationSearchByAnnealing : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : lFETOrientationSearchByAnnealing 
# Attention
#   $Loccker$
#  	$State$ 
#
*/
/* $Log$ */

#include <string.h>
#include "genUtil.h"
#include "Memory.h"
#include "eosString.h"
#include "File.h"
#include "Random.h"
#include <time.h>

#include "../../mrcImage/inc/mrcImage.h"
#include "lFETOrientationSearchByAnnealing.h"
#define ROTMODE "YOYS"
#define SETP 5
#define RANKP 3
#define IMRANK 10
#define DEFX 0
#define DEFY 1
#define DEFZ 2


static int __countFileLines(FILE* in);
//void __randomParaSet(lFETsimultaneousMinimizationDataSet* in, int mode);
//double __deltaLcalcANDrenewTable(lFETOrientationSearchByAnnealingDataSet* in, int changed, int mode);
//double __Lcalculation(lFETOrientationSearchByAnnealingDataSet* in, int mode);
//void __DataSetOverWrite(lFETOrientationSearchByAnnealingDataSet* in, int mode);
//void __inFileRead(lFETOrientationSearchByAnnealingInfo* info, mrcImage* inFL, mrcImage* inML);
static void __annealingProcess(lFETOrientationSearchByAnnealingInfo* info, lFETOrientationSearchByAnnealingDataSet* in, int mode);
static void __testcalc(lFETsimultaneousMinimizationDataSet* in, int ss); 


void
lFETOrientationSearchByAnnealing(lFETOrientationSearchByAnnealingInfo info, int mode)
{
	int i,j,k,n,x,y,z;
	int ss;
	mrcImage in;
	mrcImage inFL;
	mrcImage inML;
	double cU,dU,deltaL;
	lFETsimultaneousMinimizationDataSet ds;
	lCommonLineCalculationInfo clc;
	//mrcImageInformation mrcInfo;
	time_t t;
	unsigned tt=01234;
	
	srand(tt);
	//srand((unsigned) time(NULL));
	
	ss = 360/info.InMS->HeaderN.x;
	x = info.InMS->HeaderN.x;
	y = info.InMS->HeaderN.y;
	z = info.InMS->HeaderN.z;
	n = (pow((1+8*z),0.5)+1)/2;
	ds.map = info.InMS;
	ds.clc = &clc;
	lFETsimultaneousMinimizationDataSetMemoryAllocate(&ds,n,0);
	lFETsimultaneousMinimizationRandomParaSet(&ds,0);
/*for(i=0;i<n;i++){
	fprintf(stdout,"im%d)\t%s",i,ROTMODE);
	for(j=0;j<3;j++){
		fprintf(stdout,"\t%4.1f",ds.cAngle[j][i]);
	}
	fprintf(stdout,"\n");
}	*/
/*for(i=1;i<n;i++){
	fprintf(stdout,"%d\t%d\n",ds.cPos[0][0][i],ds.cPos[1][0][i]);
}*/
	for(i=0;i<10;i++){
		for(j=0;j<100;j++){
			lFETsimultaneousMinimizationRandomParaSet(&ds,1);
			lFETsimultaneousMinimizationLcalculate(&ds,1);
			if(ds.dU<0.0)   lFETsimultaneousMinimizationOverWrite(&ds,0);
		}
		//fprintf(stdout,"%f\t%f\n",ds.cU,ds.dU);
	}
	
	__testcalc(&ds,ss); 

/*	for(i=0;i<n-1;i++){
		for(j=i+1;j<n;j++){
			fprintf(stdout,"%d\t%d\n",ds.cPos[0][i][j]*5,ds.cPos[1][i][j]*5);
		}
	}*/
	fprintf(stderr,"Complete!\n");

	
}

void
lFETOrientationSearchByRigidSubsetCore(lFETOrientationSearchByAnnealingInfo info, int mode)
{
	int i,j,k,n,x,y,z;
    int ss;
    mrcImage in;
    mrcImage inFL;
    mrcImage inML;
    double cU,dU,deltaL;
    lFETsimultaneousMinimizationDataSet ds[SETP];
    lCommonLineCalculationInfo clc;
    time_t t;
    unsigned tt=01234;
	
	//srand(tt);
	srand((unsigned) time(NULL));
	ss = 360/info.InMS->HeaderN.x;
    x = info.InMS->HeaderN.x;
    y = info.InMS->HeaderN.y;
    z = info.InMS->HeaderN.z;
    n = (pow((1+8*z),0.5)+1)/2;
	for(i=0; i<SETP; i++){
		ds[i].map = info.InMS;
		ds[i].clc = &clc;
		lFETsimultaneousMinimizationDataSetMemoryAllocate(&ds[i],n,0);
	}

	for(k=0; k<15; k++){
		for(i=0; i<SETP; i++){
			lFETsimultaneousMinimizationRandomParaSet(&ds[i],0);
			for(j=0;j<1000;j++){
	            lFETsimultaneousMinimizationRandomParaSet(&ds[i],1);
    	        lFETsimultaneousMinimizationLcalculate(&ds[i],1);
        	    if(ds[i].dU<0.0)   lFETsimultaneousMinimizationOverWrite(&ds[i],0);
       		}
			if(i==1){ __testcalc(&ds[i],ss);
				for(j=0; j<n; j++){
					fprintf(stdout,"%d ",ds[i].sflag[j]);
				}
			}
		}
		lFETOrientationSearchByRigidSubsetCore_Search(ds,0);
	}
	
	//__testcalc(&ds[3],ss);

	
}

void
lFETOrientationSearchByRigidSubsetCore_Search(lFETsimultaneousMinimizationDataSet* ds, int mode)
{
	int i,j,k,l,o,p,counter;
	int n, step;
	int rank[SETP][RANKP];
	unsigned nodeDS[SETP][RANKP][RANKP];
	double data, datar=0.0;
	int temp[RANKP];

	n = ds[0].n;
	step = 1080/ds[0].map->HeaderN.x;
 	for(i=0; i<SETP; i++){
		for(j=0; j<n; j++){
			for(k=0; k<n; k++){
				if(j==k) ;
				else if(k>j){
	                 ds[i].cUt[j] += ds[i].cUs[j][k];
    	        }else{
        	         ds[i].cUt[j] += ds[i].cUs[k][j];
            	}
			}
		}
		for(j=0; j<RANKP && j<n; j++){
			data=10000.0;
			for(k=0; k<n; k++){
				if(ds[i].cUt[k]<data && ds[i].cUt[k]>datar){
					data = ds[i].cUt[k];
					l=k;
				}
			}
			datar=data;
			rank[i][j] = l;
			//ds[i].sflag[l] = 1;
		}
	}
	for(i=0; i<SETP; i++){
		for(l=0; l<SETP; l++){
			if(i==l) ;
			else{
				for(j=0; j<RANKP-1 && j<n-1; j++){
				for(k=j+1; k<RANKP && k<n; k++){	
					if(rank[i][j] < rank[i][k]){
						data = pow((ds[i].cPos[DEFX][rank[i][j]][rank[i][k]] - ds[l].cPos[DEFX][rank[i][j]][rank[i][k]]),2);
						datar = pow((ds[i].cPos[DEFY][rank[i][j]][rank[i][k]] - ds[l].cPos[DEFY][rank[i][j]][rank[i][k]]),2);
					}else{
						data = pow((ds[i].cPos[DEFX][rank[i][k]][rank[i][j]] - ds[l].cPos[DEFX][rank[i][k]][rank[i][j]]),2);
                        datar = pow((ds[i].cPos[DEFY][rank[i][k]][rank[i][j]] - ds[l].cPos[DEFY][rank[i][k]][rank[i][j]]),2);
					}
					data = pow((data+datar),0.5);
					//fprintf(stdout,"%f ",data);
					if(data<step) nodeDS[l][j][k] = 1;
					else nodeDS[l][j][k] = 0;
					//fprintf(stdout,"%d  ",nodeDS[l][j][k]);
				}
				}
			}
		}
		//fprintf(stdout,"\n\n\n");
		
		for(l=0; l<SETP; l++){
            if(i==l) ;
			else{
				for(j=0; j<RANKP; j++){
					counter = 0;
					for(k=0; k<RANKP; k++){
						if(j==k) ;
						else if(j<k){
							if(nodeDS[l][j][k]==1){ temp[counter]=k; counter++; }
						}else{
							if(nodeDS[l][k][j]==1){ temp[counter]=k; counter++; }
						}
					}
					for(k=0; k<counter-1; k++){
						for(o=k+1; o<counter; o++){
							if(temp[k]>temp[o]){
								p=o; o=k; k=p;
							}
							if(nodeDS[l][temp[k]][temp[o]]==1){
								ds[i].sflag[rank[i][j]]++; 
								ds[i].sflag[rank[i][k]]++;
								ds[i].sflag[rank[i][o]]++; 
							}
						}
					}
				}
			}
		}
	}	

	
}

void __testcalc(lFETsimultaneousMinimizationDataSet* in, int ss){
	int i,j,k;
	double rankd[46], ranks[46], data, datar=0.0;
	int rank[46];

	for(i=0;i<46;i++) { rankd[i]=0.0; rank[i]=0; }
	for(i=0;i<in->n;i++){
		for(j=0;j<in->n;j++){
			if(j==i) ;
			else if(j>i){
				rankd[i] += in->cUs[i][j];
			}else{
				rankd[i] += in->cUs[j][i];
			}
		}
	}
	for(i=0;i<46;i++){
		data=10000.0;
		for(j=0;j<46;j++){
			if(rankd[j]<data&&rankd[j]>datar){
				data=rankd[j];
				k=j;
			}
			
		}
		datar=data;
		rank[i]=k;
	}
	for(i=0;i<46;i++){
		fprintf(stdout,"%f\t",rankd[rank[i]]);
	}
	fprintf(stdout,"\n");
	for(i=0;i<46;i++) fprintf(stdout,"%d\t",rank[i]);
	fprintf(stdout,"\n\n");

	for(i=0;i<4;i++){
		for(j=i+1;j<5;j++){
//	for(i=41;i<45;i++){
//		for(j=i+1;j<46;j++){
			if(rank[i]<rank[j]){
				fprintf(stdout,"%d-%d\t%d-%d\t",i,rank[i],j,rank[j]);
				fprintf(stdout,"%d\t%d\t%d\t%f\n",in->cPos[2][rank[i]][rank[j]],in->cPos[0][rank[i]][rank[j]]*ss,in->cPos[1][rank[i]][rank[j]]*ss,in->cUs[rank[i]][rank[j]]);
			}else{
				fprintf(stdout,"%d-%d\t%d-%d\t",j,rank[j],i,rank[i]);
                fprintf(stdout,"%d\t%d\t%d\t%f\n",in->cPos[2][rank[j]][rank[i]],in->cPos[0][rank[j]][rank[i]]*ss,in->cPos[1][rank[j]][rank[i]]*ss,in->cUs[rank[j]][rank[i]]);
				
			}
		}
	}

}

void 
lFETsimultaneousMinimizationOverWrite(lFETsimultaneousMinimizationDataSet* in, int mode)
{
	int i,j;
	
	for(i=0 ; i<3 ; i++) in->cAngle[i][in->dImage] = in->dAngle[i];
	for(i=0 ; i<in->dImage ;i++){
		for(j=0 ; j<2 ; j++){
			in->cPos[j][i][in->dImage] = in->dPos[j][i];
		}
		in->cUs[i][in->dImage] = in->dUs[i];
	}
	for(i=in->dImage+1 ; i<in->n ; i++){
        for(j=0 ; j<2 ; j++){
            in->cPos[j][in->dImage][i] = in->dPos[j][i];
        }   
        in->cUs[in->dImage][i] = in->dUs[i];
	}
		
	
	
}


void 
lFETsimultaneousMinimizationDataSetMemoryAllocate(lFETsimultaneousMinimizationDataSet* in, int n, int mode)
{
	int i,j,c,m;
	
	in->n = n;
	in->sflag = (unsigned*)memoryAllocate(sizeof(unsigned)*n,"in lFETOrientationSearchByAnnealing");
	in->cUt = (double*)memoryAllocate(sizeof(double)*n,"in lFETOrientationSearchByAnnealing");
	for(i=0; i<n; i++) in->sflag[i] = 0;
	for(i=0; i<3; i++){
		in->cAngle[i] = (double*)memoryAllocate(sizeof(double)*n,"in lFETOrientationSearchByAnnealing");
		in->dPos[i] = (int*)memoryAllocate(sizeof(int)*n,"in lFETOrientationSearchByAnnealing");
		in->cPos[i] = (int**)memoryAllocate(sizeof(int*)*n,"in lFETOrientationSearchByAnnealing");
		for(j=0; j<n; j++){
			in->cPos[i][j] = (int*)memoryAllocate(sizeof(int)*n,"in lFETOrientationSearchByAnnealing");
		}
	}
	in->cUs = (double**)memoryAllocate(sizeof(double*)*n,"in lFETOrientationSearchByAnnealing");
	for(j=0; j<n; j++){
		in->cUs[j] = (double*)memoryAllocate(sizeof(double)*n,"in lFETOrientationSearchByAnnealing");
	}
	in->dUs = (double*)memoryAllocate(sizeof(double)*n,"in lFETOrientationSearchByAnnealing");

	c=0;
	for(i=0; i<n-1; i++){
		for(j=i+1; j<n; j++){
			in->cPos[2][i][j] = c; 
			c++;
		}
	}

	in->z = (n*(n-1))/2;
	m = in->z;
	in->clc->num = m;
	in->clc->I1RotationalMode = MemoryAllocate(char*, m, "in lFETOrientationSearchByAnnealing");
	in->clc->I2RotationalMode = MemoryAllocate(char*, m, "in lFETOrientationSearchByAnnealing");
    for(i=0; i<m; i++){
        in->clc->I1RotationalMode[i] = MemoryAllocate(char, 16, "in lFETOrientationSearchByAnnealing");
        in->clc->I2RotationalMode[i] = MemoryAllocate(char, 16, "in lFETOrientationSearchByAnnealing");
    }
	in->clc->I1Angle1 = MemoryAllocate(float, m, "in lFETOrientationSearchByAnnealing");
    in->clc->I1Angle2 = MemoryAllocate(float, m, "in lFETOrientationSearchByAnnealing");
    in->clc->I1Angle3 = MemoryAllocate(float, m, "in lFETOrientationSearchByAnnealing");
    in->clc->I2Angle1 = MemoryAllocate(float, m, "in lFETOrientationSearchByAnnealing");
    in->clc->I2Angle2 = MemoryAllocate(float, m, "in lFETOrientationSearchByAnnealing");
    in->clc->I2Angle3 = MemoryAllocate(float, m, "in lFETOrientationSearchByAnnealing");
    in->clc->CLAngleOnI1AgainstI2  = MemoryAllocate(float, m, "in lFETOrientationSearchByAnnealing");
    in->clc->CLAngleOnI2AgainstI1  = MemoryAllocate(float, m, "in lFETOrientationSearchByAnnealing");
    in->clc->flag     = MemoryAllocate(int  , m, "in lFETOrientationSearchByAnnealing");
	
}

void __annealingProcess(lFETOrientationSearchByAnnealingInfo* info, lFETOrientationSearchByAnnealingDataSet* in, int mode)
{
	int i,j;
	double T;

	T = info->ITemp;
	for(i=0;i<info->as3;i++){
		for(j=0;j<(info->as1*info->fnum);i++){

			;
		}	
		T *= info->as2;
	}

}

void
lFETsimultaneousMinimizationLcalculate(lFETsimultaneousMinimizationDataSet* in, int mode)
{
	int i,j,k;
	double data=0, data1=0, data2=0;

	if(mode==0){
		for(i=0 ; i<in->n-1 ; i++){
			for(j=i+1 ; j<in->n ; j++){
                data += in->cUs[i][j];
            }
		}
		in->cU = data;
		
	}else if(mode==1){
		for(i=0 ; i<in->n-1 ; i++){
			for(j=i+1 ; j<in->n ; j++){
				data += in->cUs[i][j];
			}
			data1 += in->dUs[i];
		}
		for(i=0 ; i<in->dImage ; i++) data2 += in->cUs[i][in->dImage];
		for(i=in->dImage+1 ; i<in->n ; i++) data2 += in->cUs[in->dImage][i];
		
		in->cU = data;
		in->dU = data1-data2;
		
	}else ;

}

void
lFETsimultaneousMinimizationRandomParaSet(lFETsimultaneousMinimizationDataSet* in, int mode)
{
	int i,j,k,ss;
	int pair;
	double data;
	
	ss = 360/in->map->HeaderN.x;
	if(mode==0){  // mode0  : initial parameter setting
		for(i=0;i<in->n;i++){ // initial randamize
			if(in->sflag[i]==0){
				in->cAngle[0][i] = (double)((rand()/(double)RAND_MAX)*360)*-1.0;
				in->cAngle[1][i] = (double)((rand()/(double)RAND_MAX)*180)-90.0;
				if(in->cAngle[1][i]<0.0) in->cAngle[1][i]+=360;
				in->cAngle[2][i] = (double)((rand()/(double)RAND_MAX)*360);
			}else ;
		}
		pair=0;  // copy random data for commonlineCalculation
		for(i=0;i<in->n-1;i++){
			for(j=i+1;j<in->n;j++){
				stringCopy(in->clc->I1RotationalMode[pair], ROTMODE, 4);
				stringCopy(in->clc->I2RotationalMode[pair], ROTMODE, 4);
				in->clc->I1Angle1[pair] = (float)in->cAngle[0][i]*RADIAN;
				in->clc->I1Angle2[pair] = (float)in->cAngle[1][i]*RADIAN;
				in->clc->I1Angle3[pair] = (float)in->cAngle[2][i]*RADIAN;
				in->clc->I2Angle1[pair] = (float)in->cAngle[0][j]*RADIAN;
				in->clc->I2Angle2[pair] = (float)in->cAngle[1][j]*RADIAN;
				in->clc->I2Angle3[pair] = (float)in->cAngle[2][j]*RADIAN;
				lCommonLineCalculation1(in->clc, pair, 0);
				
				in->cPos[0][i][j] = (int)(in->clc->CLAngleOnI1AgainstI2[pair]*DEGREE/ss);
				in->cPos[1][i][j] = (int)(in->clc->CLAngleOnI2AgainstI1[pair]*DEGREE/ss);
				if(in->cPos[1][i][j]>180/ss){
					in->cPos[1][i][j] -= 180/ss;
					in->cPos[0][i][j] -= 180/ss;
				}

				mrcPixelDataGet(in->map,in->cPos[0][i][j],in->cPos[1][i][j],in->cPos[2][i][j],&data, mrcPixelRePart, mrcPixelHowNearest);
				in->cUs[i][j] = data;
				pair++;
			}
		}
		
	}else{  // mode!=0 : generate difference on minimization process
		if(mode==1){ // mode1 : completely random  
			in->dImage = (int)((rand()/(double)RAND_MAX)*in->n);
			if(in->sflag[in->dImage]==0){
				in->dAngle[0] = (double)((rand()/(double)RAND_MAX)*360)*-1.0;
				in->dAngle[1] = (double)((rand()/(double)RAND_MAX)*180)-90.0;
				if(in->dAngle[1]<0.0) in->dAngle[1]+=360;
				in->dAngle[2] = (double)((rand()/(double)RAND_MAX)*360);
			}else{
				in->dAngle[0] = in->cAngle[0][in->dImage];
				in->dAngle[1] = in->cAngle[1][in->dImage];
				in->dAngle[2] = in->cAngle[2][in->dImage];	
			}
		}else ;
		
		pair=0;
		for(i=0;i<in->dImage;i++){
			stringCopy(in->clc->I1RotationalMode[pair], ROTMODE, 4);
			stringCopy(in->clc->I2RotationalMode[pair], ROTMODE, 4);
			in->clc->I1Angle1[pair] = (float)in->cAngle[0][i]*RADIAN;
			in->clc->I1Angle2[pair] = (float)in->cAngle[1][i]*RADIAN;
            in->clc->I1Angle3[pair] = (float)in->cAngle[2][i]*RADIAN;
			in->clc->I2Angle1[pair] = (float)in->dAngle[0]*RADIAN;
            in->clc->I2Angle2[pair] = (float)in->dAngle[1]*RADIAN;
            in->clc->I2Angle3[pair] = (float)in->dAngle[2]*RADIAN;
			lCommonLineCalculation1(in->clc, i, 0);

			in->dPos[0][i] = (int)(in->clc->CLAngleOnI1AgainstI2[i]*DEGREE/ss);
			in->dPos[1][i] = (int)(in->clc->CLAngleOnI2AgainstI1[i]*DEGREE/ss);
			in->dPos[2][i] = in->cPos[2][i][in->dImage];
			if(in->dPos[1][i]>180/ss){
                 in->dPos[1][i] -= 180/ss;
                 in->dPos[0][i] -= 180/ss;
            }

			mrcPixelDataGet(in->map,in->dPos[0][i],in->dPos[1][i],in->dPos[2][i],&data, mrcPixelRePart, mrcPixelHowNearest);
			in->dUs[i] = data;
			
			pair++;
		}
		in->dUs[pair] = 0.0;
		pair++;
		for(i=in->dImage+1;i<in->n;i++){
			stringCopy(in->clc->I1RotationalMode[pair], ROTMODE, 4);
            stringCopy(in->clc->I2RotationalMode[pair], ROTMODE, 4);
            in->clc->I1Angle1[pair] = (float)in->dAngle[0]*RADIAN;
            in->clc->I1Angle2[pair] = (float)in->dAngle[1]*RADIAN;
            in->clc->I1Angle3[pair] = (float)in->dAngle[2]*RADIAN;
            in->clc->I2Angle1[pair] = (float)in->cAngle[0][i]*RADIAN;
            in->clc->I2Angle2[pair] = (float)in->cAngle[1][i]*RADIAN;
            in->clc->I2Angle3[pair] = (float)in->cAngle[2][i]*RADIAN;
			lCommonLineCalculation1(in->clc, i, 0);

			in->dPos[0][i] = (int)(in->clc->CLAngleOnI1AgainstI2[i]*DEGREE/ss);
            in->dPos[1][i] = (int)(in->clc->CLAngleOnI2AgainstI1[i]*DEGREE/ss);
			in->dPos[2][i] = in->cPos[2][in->dImage][i];
			if(in->dPos[1][i]>180/ss){
                 in->dPos[1][i] -= 180/ss;
                 in->dPos[0][i] -= 180/ss;
            }
			
			mrcPixelDataGet(in->map,in->dPos[0][i],in->dPos[1][i],in->dPos[2][i],&data, mrcPixelRePart, mrcPixelHowNearest);
			in->dUs[i] = data;
			pair++;
		}

		
	}
}
/*
void __inFileRead(lFETOrientationSearchByAnnealingInfo* info, mrcImage* inFL, mrcImage* inML)
{
	int i,j,k,z;
	char s[256];
	double data;
	mrcImage in;
	
	if(info->flagInML==0){
		fseek(info->InFL, 0L, SEEK_SET);
		stringGetFromFile(s,"",info->InFL,stdout,1);
		mrcFileRead(&in, s, "in lmrcSinogramFETcalcWeight",0);
		inFL->Header = in.Header;
		inFL->HeaderN.z = info->fnum;
		mrcInit(inFL,NULL);
		
		fseek(info->InFL, 0L, SEEK_SET);
		k=0;
		while(NULL!=stringGetFromFile(s,"",info->InFL,stdout,1)){
			mrcFileRead(&in, s, "in lmrcSinogramFETcalcWeight",0);
			for(i=0;i<in.HeaderN.x;i++){
				for(j=0;j<in.HeaderN.y;j++){
					mrcPixelDataGet(&in,i,j,0,&data, mrcPixelRePart, mrcPixelHowNearest);
					mrcPixelDataSet(inFL,i,j,k,data, mrcPixelRePart);
				}}
			k++;
		}
		mrcStatDataSet(inFL,0); 
	}
	else{
	    z = (info->fnum*(info->fnum-1))/2;
    	fseek(info->InML, 0L, SEEK_SET);
	    stringGetFromFile(s,"",info->InML,stdout,1);
    	mrcFileRead(&in, s, "in lmrcSinogramFETcalcWeight",0);
	    inML->Header = in.Header;
    	inML->HeaderN.z = z;
	    mrcInit(inML,NULL);
	
		fseek(info->InML, 0L, SEEK_SET);
	    k=0;
    	while(NULL!=stringGetFromFile(s,"",info->InML,stdout,1)){
        	mrcFileRead(&in, s, "in lmrcSinogramFETcalcWeight",0);
	        for(i=0;i<in.HeaderN.x;i++){
    	        for(j=0;j<in.HeaderN.y;j++){
        	        mrcPixelDataGet(&in,i,j,0,&data, mrcPixelRePart, mrcPixelHowNearest);
            	    mrcPixelDataSet(inML,i,j,k,data, mrcPixelRePart);
	            }}
    	    k++;
    	}
		mrcStatDataSet(inML,0);
	}
}
*/								   
int __countFileLines(FILE* in)
{
	int i;
	char s[256];

	fseek(in, 0L, SEEK_SET);
	i=0;
	while(NULL!=stringGetFromFile(s,"",in,stdout,1)) i++;
	
	return i;
}













