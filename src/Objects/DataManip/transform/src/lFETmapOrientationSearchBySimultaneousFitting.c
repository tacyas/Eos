/*
# lFETmapOrientationSearchBySimultaneousFitting : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : lFETmapOrientationSearchBySimultaneousFitting 
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
#include "../../mrcImage/inc/mrcImage.h"
#include "lEvaluateCorrelationMapwithCommonLine.h"
#include "lFETmapOrientationSearchBySimultaneousFitting.h"

#define PI1 3.1415
#define INUM1 0
#define INUM2 1
#define INUM3 2
#define NORMAL 1
#define ZEROLINE 0
#define COMPX 0
#define COMPY 1
#define COMPZ 2

void __paraSet1(lFETmapOrientationSearchBySimultaneousFittingInfo* info, lFETmapPeakDetectAndTableMakeInfo* TMinfo);
void __randomER(RadonSpaceSimultaneousFittingParameters* paras);
int __calcTriadAngles(FETCoreTriad* , int );
		
void
lFETmapOrientationSearchBySimultaneousFitting(lFETmapOrientationSearchBySimultaneousFittingInfo info, int mode)
{
	int i,j,k;
	lFETmapPeakDetectAndTableMakeInfo TMinfo;
	FETmapPeakTable pTable;
	lFETmapCoreTriadGenerateInfo CTGinfo;
	lRadonSpaceSimultaneousFittingInfo RSinfo;
	RadonSpaceSimultaneousFittingParameters paraTable;
	
	__paraSet1(&info,&TMinfo); //copy parameter
	TMinfo.tableP=&pTable;
	lFETmapPeakDetectAndTableMake(&TMinfo,0);
	
	for(i=0;i<info.PN;i++){
		fprintf(stdout,"0-9 %d  %d\n",pTable.table[0][9][i],pTable.table[9][0][i]);
	}
	
	/*RSinfo.tableP=&pTable;
	RSinfo.paras=&paraTable;
	RSinfo.cycleMaxR = 10;
	RSinfo.cycleMax = 10;
	RSinfo.cycleMaxS = 5;
	lRadonSpaceSimultaneousFitting(&RSinfo,0);*/

	CTGinfo.InCL = info.InCL;
	CTGinfo.filesN = TMinfo.filesN;
	lFETmapCoreTriadGenerate(TMinfo.tableP,&CTGinfo,TMinfo.PN);
	/*for(i=0;i<10;i++){ 	
	fprintf(stdout,"%d o %d o %d\n",CTGinfo.CList[i].triad[0],CTGinfo.CList[i].triad[1],CTGinfo.CList[i].triad[2]);}*/

	
	
}

void lFETmapCoreTriadGenerate(FETmapPeakTable* Table, lFETmapCoreTriadGenerateInfo* info, int mode)
{
	int i,j,count,hits;
	char s[256];
	FETCoreTriad coretemp;

	fseek(info->InCL, 0L, SEEK_SET);
    i = 0;
    while(NULL!=stringGetFromFile(s,"",info->InCL,stdout,1)) i++;
	info->CList=(FETCoreTriad*)memoryAllocate(sizeof(FETCoreTriad)*i,"in lFETmapCoreTriadGenerate");
	
	fseek(info->InCL, 0L, SEEK_SET);
	i=0;
	while(NULL!=stringGetFromFile(s,"",info->InCL,stdout,1)){
		coretemp.triad[0] = (int)stringGetNthRealData(s,1," ,\t");
		coretemp.triad[1] = (int)stringGetNthRealData(s,2," ,\t");
		coretemp.triad[2] = (int)stringGetNthRealData(s,3," ,\t");
		fprintf(stdout,"%d %d %d\n",coretemp.triad[0],coretemp.triad[1],coretemp.triad[2]);
		coretemp.filesN = info->filesN;
		hits = lFETBestCoreSearch(Table, &coretemp, mode, 0);
		fprintf(stdout,"get %d triangles in %d	%f\n",coretemp.matchFlag,i,coretemp.angles[0][1][2]);
		info->CList[i] = coretemp;
		i++;
	}
	
}

int lFETBestCoreSearch(FETmapPeakTable* Table, FETCoreTriad* coreT, int PN, int mode)
{
	int i,j,k,l,m,count,hits=0;
	int flag1, cflag[3], cFlag, retflag;
	int coreset[3], para[6], maxnum[3];
	double coreTr[3], coreTrM[3];
	double radian1, coreTr1, coreTr2, var1, var2;
	FETCoreTriad coreTemp;
	//int*** triadTable;

	/*triadTable = (int***)memoryAllocate(sizeof(int)*PN,"in lFETBestCoreSearch");
	for(i=0;i<PN;i++){
		triadTable[i] = (int**)memoryAllocate(sizeof(int)*PN,"in lFETBestCoreSearch");
		for(j=0;j<PN;j++){
			triadTable[i][j] = (int*)memoryAllocate(sizeof(int)*PN,"in lFETBestCoreSearch");
		}}*/

	coreTemp = *coreT;
	for(i=0;i<3;i++) coreset[i] = coreT->triad[i];
	fprintf(stdout,"%d %d %d\n",coreset[0],coreset[1],coreset[2]);
	radian1 = 180/PI1;
	var1 = 0.0;
	for(i=0;i<PN;i++){
	for(j=0;j<PN;j++){
	for(k=0;k<PN;k++){
		para[0] = Table->table[coreset[0]][coreset[1]][i]; 
		coreT->matchPosi[0][0] = para[0];
		para[1] = Table->table[coreset[1]][coreset[0]][i];
		coreT->matchPosi[0][1] = para[1];
		para[4] = Table->table[coreset[1]][coreset[2]][j];
		coreT->matchPosi[1][0] = para[4];
        para[2] = Table->table[coreset[2]][coreset[1]][j];
		coreT->matchPosi[1][1] = para[2];
		para[5] = Table->table[coreset[2]][coreset[0]][k];
		coreT->matchPosi[2][0] = para[5];
        para[3] = Table->table[coreset[0]][coreset[2]][k];
		coreT->matchPosi[2][1] = para[3];
		
		if(para[0]==500 || para[2]==500 || para[3]==500){
			fprintf(stdout,"500");  
			//*triadTable[i][j][k]=0;
			fflush;
		}
		else{
			/*for(l=0;l<6;l++){
				if(para[l]>180) para[l]-=180;
			}*/
			for(l=0;l<3;l++) cflag[l]=0;
			for(l=0;l<3;l++){
				coreTr[l] = (double)abs(para[l]-para[l+3]);
				if(coreTr[l]>180){
					coreTr[l] = 360-coreTr[l];
				}
				if(coreTr[l]>90){
					coreTrM[l] = 180-coreTr[l];
					cflag[l] = 1;
				}
				else coreTrM[l] = coreTr[l];
			}
			if(coreTr[0]<30.0  || coreTr[1]<30.0  || coreTr[2]<30.0  || 
		  	   coreTrM[0]<30.0 || coreTrM[1]<30.0 || coreTrM[2]<30.0 ||
			   coreTr[0]>150.0 || coreTr[1]>150.0 || coreTr[2]>150.0){
				;
			}
			else{
				//if(i==0) fprintf(stdout,"psd1  %3.1f %3.1f %3.1f\n",coreTr[0],coreTr[1],coreTr[2]);
				for(cFlag=0,l=0;l<3;l++) cFlag += cflag[l];
				if(cFlag==0||cFlag==1){
					for(l=0;l<3;l++) coreTr[l] = 2.0*radian1*(cos((180.0-coreTr[l])/radian1/2.0));
				}else if(cFlag==3){
 					for(l=0;l<2;l++) coreTr[l] = 2.0*radian1*(cos((180.0-coreTrM[l])/radian1/2.0));
					coreTr[2] = 2.0*radian1*(cos((180.0-coreTr[l])/radian1/2.0));
				}else{
					for(l=0;l<3;l++){
						if(cflag[l]==1) coreTr[l] = 2.0*radian1*(cos((180.0-coreTrM[l])/radian1/2.0));
						else  coreTr[l] = 2.0*radian1*(cos((180.0-coreTr[l])/radian1/2.0));
					}
				}
				for(coreTr1=0.0,coreTr2=0.0,l=0;l<3;l++){
					if(coreTr[l]>coreTr1) coreTr1=coreTr[l];
					coreTr2+=coreTr[l];
				}
				if(coreTr2-coreTr1 < coreTr1+30.0){ 
					//triadTable[i][j][k]=0;
					//if(i==0) fprintf(stdout,"not psd  %3.1f %3.1f %3.1f\n",coreTr[0],coreTr[1],coreTr[2]);
					//;
					;
				}
				else{
					//triadTable[i][j][k]=1;
					var2 = 0.0;
					coreT->triad[3]=i; coreT->triad[4]=j; coreT->triad[5]=k;
					retflag = __calcTriadAngles(coreT,0);
					if(retflag==0){
						hits++;
						for(l=0; l < coreT->filesN ;l++){
							if(l==coreset[0] || l==coreset[1] || l==coreset[2]) ;
							else{
								var2 += lFET4thMatching(Table,coreT,i,j,k,l,0);
							}
						}
						if(var1 < var2){
							var1 = var2;
							//for(m=0;m<18;m++) coreTemp.angles[m] = coreT->angles[m];
							maxnum[0]=i; maxnum[1]=j; maxnum[2]=k;
						}
					}else ;
				}
			}
		}
	}}}

	fprintf(stdout,"var1 : %5.2f i : %d  j: %d  k : %d\n",var1,maxnum[0],maxnum[1],maxnum[2]); 

	if(hits==0) coreT->matchFlag = 0;
	else{
		coreT->matchFlag = hits;
		for(i=0;i<3;i++){
			coreT->triad[i+3] = maxnum[i];
		}
		coreT->matchingLevel = var1;
	}
	//for(i=0;i<18;i++) coreT->angles[i] = coreTemp.angles[i];
	
	return hits;
}

int __calcTriadAngles(FETCoreTriad* coreT, int mode)
{
	int i,j,k,t1,t2,t3;
	int flag;
	double x,y,z;
	double px, py, pz, qx, qy, qz, rx, ry, rz, alpha, beta, gamma;
	double angle1, length1, comp[3], point[3];

	px=1.0; py=0.0; pz=0.0;
	coreT->angles[INUM1][ZEROLINE][COMPZ] = 0.0;
	coreT->angles[INUM1][NORMAL][COMPX] = coreT->angles[INUM1][NORMAL][COMPY] = 0.0;
	coreT->angles[INUM1][NORMAL][COMPZ] = 1.0;
	px=1.0; py=0.0; pz=0.0;
	angle1 = -1*PI1*(double)coreT->matchPosi[0][0]/180.0;
	coreT->angles[INUM1][ZEROLINE][COMPX] = cos(angle1);
	coreT->angles[INUM1][ZEROLINE][COMPY] = sin(angle1);
	t1 = coreT->matchPosi[0][0] - coreT->matchPosi[2][1];
	if(abs(t1)>90 && abs(t1)<270){
		//if(t1 > 0) t1 = 180-t1; if(t1 < 0) t1+=180;
		//fprintf(stdout,"%d   %d, %d    ",coreT->matchPosi[0][0],coreT->matchPosi[2][0],coreT->matchPosi[2][1]);  
		coreT->matchPosi[2][0] += 180;
		coreT->matchPosi[2][1] += 180;
		if(coreT->matchPosi[2][0] > 360) coreT->matchPosi[2][0] -= 360;
		if(coreT->matchPosi[2][1] > 360) coreT->matchPosi[2][1] -= 360;
		//fprintf(stdout,"%d, %d  ",coreT->matchPosi[2][0],coreT->matchPosi[2][1]);
	}
	alpha = (double)(coreT->matchPosi[2][1] - coreT->matchPosi[0][0]);
	if(fabs(alpha)>180.0){
		if(alpha>0) alpha -= 360.0;
		else alpha += 360.0;
	}
	
	qz = 0.0;  qy = sin(PI1*alpha/180.0);  qx = cos(PI1*alpha/180.0);
	t1 = coreT->matchPosi[0][1] - coreT->matchPosi[1][0];
	if(abs(t1)>90 && abs(t1)<270){
        coreT->matchPosi[1][0] += 180;
        coreT->matchPosi[1][1] += 180;
        if(coreT->matchPosi[1][0] > 360) coreT->matchPosi[1][0] -= 360;
        if(coreT->matchPosi[1][1] > 360) coreT->matchPosi[1][1] -= 360;
    }
	beta = (double)(coreT->matchPosi[1][0] - coreT->matchPosi[0][1]);
	if(fabs(beta)>180.0){
		if(beta>0) beta -= 360.0;
        else beta += 360.0;
    }
	gamma = (double)(coreT->matchPosi[1][1] - coreT->matchPosi[2][0]);
	if(fabs(gamma)>180.0){
        if(gamma>0) gamma -= 360.0;
        else gamma += 360.0;
    }
	rx = cos(PI1*fabs(beta)/180.0);	
	ry = (cos(PI1*fabs(gamma)/180.0)-qx*ry)/qy;
	if(rx*rx+ry*ry>1.0){ //exception
		flag=1;
	}else{
		flag=0;	
		rz = sqrt(1-rx*rx-ry*ry);
		//fprintf(stdout,"rx=%3.2f ry=%3.2f rx=%3.2f\n",rx,ry,rz);
		comp[0] = py*rz-ry*pz; comp[1] = pz*rx-rz*px; comp[2] = px*ry-rx*py;
		length1 = sqrt(pow(comp[0],2) + pow(comp[1],2) + pow(comp[2],2));
		if(beta<0.0) for(i=0;i<3;i++) comp[i] *= -1; 
		coreT->angles[INUM2][NORMAL][COMPX] = comp[0]/length1;
		coreT->angles[INUM2][NORMAL][COMPY] = comp[1]/length1;
		coreT->angles[INUM2][NORMAL][COMPZ] = comp[2]/length1;
		comp[0] = qy*rz-ry*qz; comp[1] = qz*rx-rz*qx; comp[2] = qx*ry-rx*qy;
        length1 = sqrt(pow(comp[0],2) + pow(comp[1],2) + pow(comp[2],2));
		if(gamma<0.0) for(i=0;i<3;i++) comp[i] *= -1;
        coreT->angles[INUM3][NORMAL][COMPX] = comp[0]/length1;
        coreT->angles[INUM3][NORMAL][COMPY] = comp[1]/length1;
        coreT->angles[INUM3][NORMAL][COMPZ] = comp[2]/length1;

		point[0]=px; point[1]=py; point[2]=pz;
		lFETpointRotation(coreT->angles[INUM2][NORMAL],point,-1.0*(double)coreT->matchPosi[0][1],comp,0);
		coreT->angles[INUM2][ZEROLINE][COMPX] = comp[0];
        coreT->angles[INUM2][ZEROLINE][COMPY] = comp[1];
        coreT->angles[INUM2][ZEROLINE][COMPZ] = comp[2];
		point[0]=qx; point[1]=qy; point[2]=qz;
        lFETpointRotation(coreT->angles[INUM3][NORMAL],point,-1.0*(double)coreT->matchPosi[2][0],comp,0);
        coreT->angles[INUM3][ZEROLINE][COMPX] = comp[0];
        coreT->angles[INUM3][ZEROLINE][COMPY] = comp[1];
        coreT->angles[INUM3][ZEROLINE][COMPZ] = comp[2];
		fprintf(stdout,"  %3.2f ",coreT->angles[INUM3][ZEROLINE][COMPZ]);				


		
	}
	
	return flag;
	
}

void lFETpointRotation(double axis[3], double point[3], double theta, double* ans, int mode)
{
	int i,j,k;
	double thetarad, cost, sint, costr, rot[3][3];

	thetarad = PI1*theta/180.0;
	cost = cos(thetarad);  costr = 1-cost;  sint = sin(thetarad);

	for(i=0;i<3;i++){
		for(j=0;j<3;j++){
			rot[i][j] = axis[i]*axis[j]*costr;
			if(i==j) rot[i][j] += cost;
			else{
				k = (j-i)%2 + -1*(j-i)/2;
				rot[i][j] += k*axis[3-i-j]*sint;
			}
		}
	}
	/*rot[0][0] = pow(axis[0],2)*costr+cost;
	rot[0][1] = axis[0]*axis[1]*costr+axis[2]*sint;
	rot[0][2] = axis[0]*axis[2]*costr-axis[1]*sint;
	rot[1][0] = axis[0]*axis[1]*costr-axis[2]*sint;
	rot[1][1] = pow(axis[1],2)*costr+cost;
	rot[1][2] = axis[1]*axis[2]*costr+axis[0]*sint;
    rot[2][0] = axis[0]*axis[2]*costr+axis[1]*sint;
    rot[2][1] = axis[1]*axis[2]*costr-axis[0]*sint;
	rot[2][2] = pow(axis[2],2)*costr+cost;
*/
	for(i=0;i<3;i++){
		ans[i]=0;
		for(j=0;j<3;j++){
			ans[i] += rot[j][i]*point[j];
		}
	}
}

double lFET4thMatching(FETmapPeakTable* Table, FETCoreTriad* coreT, int a, int b, int c, int d, int main)
{
	int i,j,k;
	double point;

	//for(i=0;i<18;i++) coreT->angles[i]=i;
	point = 0.3;

	
	return point;
}

void lRadonSpaceSimultaneousFitting(lRadonSpaceSimultaneousFittingInfo* info, int mode)
{
	int i,j,k,l,m;
	int flagCORE=0;
	int* sortN; 
	int* rigidSubset[10];
	
	info->paras->table=(double**)memoryAllocate(sizeof(double)*info->tableP->filesN, "in lRadonSpaceSimultaneousFitting");
	for(i=0;i<info->tableP->filesN;i++){
		info->paras->table[i]=(double*)memoryAllocate(sizeof(double)*3, "in lRadonSpaceSimultaneousFitting");
	}
	sortN = (int*)memoryAllocate(sizeof(int)*info->tableP->filesN, "in lRadonSpaceSimultaneousFitting");
	for(i=0;i<10;i++) rigidSubset[i]=(int*)memoryAllocate(sizeof(int)*info->tableP->filesN, "in lRadonSpaceSimultaneousFitting");
	
	for(i=0;flagCORE!=0||info->cycleMaxR;i++){
		__randomER(info->paras);
		lRadonSpaceSimultaneousFittingC(info->tableP,info->paras,sortN,0);
		flagCORE = lRadonSpaceSimultaneousFittingCoreSearch(info->tableP,info->paras,rigidSubset,0);
	}
	


	
}

int
lRadonSpaceSimultaneousFittingCoreSearch(FETmapPeakTable* tableP,RadonSpaceSimultaneousFittingParameters* paras, int* rS[10], int mode){
	return 0;
}

void
lRadonSpaceSimultaneousFittingC(FETmapPeakTable* tableP,RadonSpaceSimultaneousFittingParameters* paras, int* sortN, int mode)
{
	int i;
}

void __randomER(RadonSpaceSimultaneousFittingParameters* paras){
	int i;
}

void
lFETmapPeakDetectAndTableMake(lFETmapPeakDetectAndTableMakeInfo* info, int mode)
{
	int i,j,k,count;
	char s[256];
	mrcImage in, out;
	mrcImageInformation linfo;
	lmrcSCMEpeakDetectInfo pDinfo;
	
	fseek(info->InNL, 0L, SEEK_SET);
	i = 0;
	while(NULL!=stringGetFromFile(s,"",info->InNL,stdout,1)) i++;
	info->filesN = i;
	fseek(info->InML, 0L, SEEK_SET);
	j = 0;
	while(NULL!=stringGetFromFile(s,"",info->InML,stdout,1)) j++;
	if(j != i*(i-1)/2){
		fprintf(stderr,"your input MapList %dlines and NameList %dlines are not match.\n",j,i);
		exit(1);
	}
	else info->filesM = j;

	info->tableP->table=(int***)memoryAllocate(sizeof(int)*info->filesN, "in lFETmapPeakDetectAndTableMake");
	for(i=0;i<info->filesN;i++){
		info->tableP->table[i]=(int**)memoryAllocate(sizeof(int)*info->filesN, "in lFETmapPeakDetectAndTableMake");
		for(j=0;j<info->filesN;j++){
			info->tableP->table[i][j]=(int*)memoryAllocate(sizeof(int)*info->PN, "in lFETmapPeakDetectAndTableMake");
		}
	}

	pDinfo.flagOut=0; pDinfo.Out=&out;
	pDinfo.flagThreshold=1;
	pDinfo.Threshold=info->PDT;
	pDinfo.flagCount=1;
	pDinfo.PA=info->PM;
	count=1;
	i=0;j=1;
	fprintf(stdout,"N = %d\n",info->filesN);
	
	fseek(info->InML, 0L, SEEK_SET);
	while(NULL!=stringGetFromFile(s,"",info->InML,stdout,1)){
		mrcFileRead(&in, s, "in lFETmapPeakDetectAndTableMake", 0);
		linfo.mode = meanOfAll;
		lmrcImageInformation(&linfo, &in);
		pDinfo.MaxI = linfo.max;

		lmrcSCMEpeakDetect(&in, &pDinfo, 1);
			
		for(k=0;k<info->PN;k++){
			if(k>pDinfo.Count){
				info->tableP->table[i][j][k] = 500;
				info->tableP->table[j][i][k] = 500;
			}else{
				info->tableP->table[i][j][k] = pDinfo.highestPeak[k].x;
				info->tableP->table[j][i][k] = pDinfo.highestPeak[k].y;
			}
		}
		j++;
		if(j==info->filesN){
			i++;
			j=i+1;
		}
		count++;
	}
	
	for(i=0;i<info->filesN;i++){
		for(j=0;j<info->PN;j++){
			info->tableP->table[i][i][j] = 0;
		}
	}
	info->tableP->filesN = info->filesN;
	info->tableP->filesM = info->filesM;
	info->tableP->PM = info->PM;
	info->tableP->PN = info->PN;
}

void
__paraSet1(lFETmapOrientationSearchBySimultaneousFittingInfo* info, lFETmapPeakDetectAndTableMakeInfo* TMinfo)
{
	TMinfo->InML=info->InML;
	TMinfo->InNL=info->InNL;
	TMinfo->PM=info->PM;
	TMinfo->PN=info->PN;
	TMinfo->PDT=info->PDT;
}









