/*
# lFETOrientationSearchByFeatureAlignmentInitSet : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : lFETOrientationSearchByFeatureAlignmentInitSet 
# Attention
#   $Loccker$
#  	$State$ 
#
*/
/* $Log$ */


#include "lFETOrientationSearchByFeatureAlignment.h"
#define PI1 3.141592654
#include "Random.h"
#include <time.h>
#include "Memory.h"

double __searchCommonLinePoint(lFETFeatureAlignmentFeature* in1, lFETFeatureAlignmentFeature* in2, int y, int* outi, int* outj);
int __searchMatchSet(int* in, int* out, int num, lFETFeatureAlignment_i1LssInitInfo* ref);
double __calcImageCor11(lFETFeatureAlignmentImageInfo i1, lFETFeatureAlignmentImageInfo i2, int y, int rev);
int __calc90pos(lFETFeatureAlignmentFeature in, lFETFeatureAlignmentFeature* ref, int y);
double __calcScore(lFETFeatureAlignment_i11LMLXsInitInfo* info, int* pos, int y);
//void lFETFAcoordcpy1(lFETFeatureAlignmentCoord* b, double* a, int mode);
//void lFATFAcoordcpy2(lFETFeatureAlignmentCoord* a, double* b, int mode);
//void lFETFAvectorProduct1(double* a, double* b, double* ans);
void __unitalize(double* a, double* ans);

void lFETFeatureAlignmentInitSet_i2PCA(lFETFeatureAlignmentInfo* info);
void __alignLXgroup0(lFETFeatureAlignmentImageQSInfo* in);
int __alignLXgroupPCA(lFETFeatureAlignmentImageQSInfo* in, int* ts, int tnum, int l, int r, double* dec, double* lmd, int mode);
void __alignLXgroupSetPara(lFETFeatureAlignmentImageQSInfo* qs, lFETFeatureAlignmentInfo* info);
lFETFeatureAlignmentFeature __calcImageCor(lFETFeatureAlignmentImageInfo i1, lFETFeatureAlignmentImageInfo i2, int y, int* a);

void 
lFETFeatureAlignmentInitSet_random(lFETFeatureAlignmentInfo* info)
{	
	int i,j,k,n;
	double* rands;
	double t1[6], ans[3], tans1[3], tans2[3];
	double* tp;
	time_t t;

	n = info->imagenum;
	rands = (double*)memoryAllocate(sizeof(double)*(n*6), "in lFETFeatureAlignmentInitSet_random");
	srandomByTime();
	for(i=0; i<n*6; i++){
		rands[i] = randomUniformGet(0.0, 2.0, 0);
		rands[i] = rands[i]-1.0;
	}
	
	tp = &t1[3];
	for(i=0; i<n; i++){
		k = i*6;
		for(j=0;j<6;j++) t1[j] = rands[k+j];
		__unitalize(t1,tans1);
		__unitalize(tp,tans2);
		lFETFAvectorProduct1(tans1, tans2, ans);

		lFETFAcoordcpy1(&(info->images[i].norm),tans1,1);
		lFETFAcoordcpy1(&(info->images[i].base),ans,1);
		info->images[i].interAngle = 1.0;
	}
}

void
__unitalize(double* a, double* ans)
{
	int i,j;
	double len = 0.0;

	for(i=0;i<3;i++) len += pow(a[i],2);
	len = pow(len,0.5);
	for(i=0;i<3;i++) ans[i] = a[i]/len;
}
/*
void
lFETFAvectorProduct1(double* a, double* b, double* ans)
{
	int i,j,k;
	double len=0.0;

	for(i=0;i<3;i++){
		if(i==0){ j=1; k=2; }else if(i==1){ j=2; k=0; }else{ j=0; k=1; }
		ans[i] = (a[j]*b[k]) - (a[k]*b[j]);
		len += pow(ans[i],2);
	}
	len = pow(len,0.5);
	for(i=0;i<3;i++) ans[i] /= len;
}
*/
void 
lFETFeatureAlignmentInitSet_i2LM(lFETFeatureAlignmentInfo* info)
{ 
	; 
}

void 
lFETFeatureAlignmentInitSet_i21LMLX(lFETFeatureAlignmentInfo* info)
{ 
	; 
}

void
lFETFeatureAlignmentInitPreSet_i1Lss(lFETFeatureAlignmentInfo* info,
        lFETFeatureAlignment_i1LssInitInfo* out, int target)
{
	int i,j;
	double data;
	out->images[target] = (lFETFeatureAlignmentImageInfo*)memoryAllocate(sizeof(lFETFeatureAlignmentImageInfo)*info->imagenum, "in lFETFeatureAlignmentInitPreSet_i1Lss");
	out->angle[target] = (int**)memoryAllocate(sizeof(int*)*info->imagenum, "in lFETFeatureAlignmentInitPreSet_i1Lss");
	out->nums[target] = (int**)memoryAllocate(sizeof(int*)*info->imagenum, "in lFETFeatureAlignmentInitPreSet_i1Lss");
	if(target==0) out->max = (int**)memoryAllocate(sizeof(int*)*info->imagenum, "in lFETFeatureAlignmentInitPreSet_i1Lss");
	for(j=0;j<info->imagenum;j++){
		out->angle[target][j] = (int*)memoryAllocate(sizeof(int)*info->imagenum, "in lFETFeatureAlignmentInitPreSet_i1Lss");
		out->nums[target][j] = (int*)memoryAllocate(sizeof(int)*info->imagenum, "in lFETFeatureAlignmentInitPreSet_i1Lss");
		if(target==0) out->max[j] = (int*)memoryAllocate(sizeof(int)*info->imagenum, "in lFETFeatureAlignmentInitPreSet_i1Lss");
	}
	for(i=0;i<info->imagenum;i++){
		out->images[target][i] = info->images[i];
	}
	for(i=0;i<info->imagenum-1;i++){
		for(j=i+1;j<info->imagenum;j++){
			data = info->images[i].norm.x * info->images[j].norm.x;
			data += info->images[i].norm.y * info->images[j].norm.y;
			data += info->images[i].norm.z * info->images[j].norm.z;
			data = acos(data);
			data = 180*data/PI1;
			out->angle[target][i][j] = out->angle[target][j][i] = (int)(data+0.5);
		}
	}
}

void
lFETFeatureAlignmentInitSet_i1Lss(lFETFeatureAlignmentInfo* info,
		lFETFeatureAlignment_i1LssInitInfo* out, int mode)
{
	int i, j, k, l, count, flag;
	int setcount[10];
	int maxset, depth, num;
	int theta, dt;
	int* series;
	int* recept;
fprintf(stderr,"in lFETFeatureAlignmentInitSet_i1Lss\n");	
	series = (int*)memoryAllocate(sizeof(int)*info->imagenum, "in lFETFeatureAlignmentInitSet_i1Lss");
	recept = (int*)memoryAllocate(sizeof(int)*info->imagenum, "in lFETFeatureAlignmentInitSet_i1Lss");
fprintf(stderr,"after malloc\n");
	for(i=0;i<10;i++){
		setcount[i] = 0;
		//fprintf(stderr,"in i loop\n");
		for(j=0;j<info->imagenum-1;j++){
		for(k=j+1;k<info->imagenum;k++){
			//fprintf(stderr,"in jk loop\n");
			count = 0;
			theta = out->angle[i][j][k];
			for(l=0;l<10;l++){
				//fprintf(stderr,"in l loop ");
				if(i!=l){
					//fprintf(stderr,"if ");
					dt = abs(theta - out->angle[l][j][k]);
					if(dt < 15) count++;
				}
			}
			out->nums[i][j][k] = out->nums[i][k][j] = count;
			if(count>5) setcount[i]++;
		}}
	}
	fprintf(stderr,"after anglematch counting\n");
	count=-1; maxset=0;
	for(i=0;i<10;i++){
		fprintf(info->OutLOG,"set%d: %d\n",i,setcount[i]);
		if(setcount[i]>count){
			maxset=i;
			count=setcount[i];
		}
	}
	fprintf(stderr,"after maxset find %d %d\n",maxset,count);
	for(j=0;j<info->imagenum-1;j++){
	for(k=j+1;k<info->imagenum;k++){
		if(out->nums[maxset][j][k]>5) out->max[j][k] = out->max[k][j] = 1;
		else out->max[j][k] = out->max[k][j] = 0;
	}}
	fprintf(stderr,"after maxset set into struct\n");
//
	for(i=0;i<info->imagenum;i++){ 
		out->nums[maxset][i][i] = 0;
		out->angle[maxset][i][i] = 0;
		out->max[i][i] = 0;
	}
		
	for(i=0;i<info->imagenum;i++){	for(j=0;j<info->imagenum;j++){	fprintf(stderr,"%d ",out->angle[maxset][i][j]);
	}fprintf(stderr,"\n");}fprintf(stderr,"\n");
	for(i=0;i<info->imagenum;i++){  for(j=0;j<info->imagenum;j++){  fprintf(stderr,"%d ",out->nums[maxset][i][j]);
	}fprintf(stderr,"\n");}fprintf(stderr,"\n");
	for(i=0;i<info->imagenum;i++){  for(j=0;j<info->imagenum;j++){  fprintf(stderr,"%d ",out->max[i][j]);
	 }fprintf(stderr,"\n");}fprintf(stderr,"\n");	
	
//
	num=0;
	for(i=0;i<info->imagenum;i++){
		flag = 1;
		for(j=0; j<info->imagenum&&flag; j++){
			if(i!=j) if(out->max[i][j]) flag=0;
		}
		if(flag==0){
			series[num]=i; num++;
		}
	}
	fprintf(stderr,"before depth calc\n");
	depth = __searchMatchSet(series,recept,num,out);
	//
	fprintf(stderr,"finel depth = %d\n",depth);
	for(i=0;i<depth;i++) fprintf(stderr,"%d ",recept[i]);
	fprintf(stderr,"\n");
	//
	for(i=0;i<info->imagenum;i++){
		info->images[i] = out->images[maxset][i];
		info->images[i].interAngle = -10.0;
	}
	for(i=0;i<depth;i++)
		info->images[recept[i]].interAngle = 1.0;
}

int
__searchMatchSet(int* in, int* out, int num, lFETFeatureAlignment_i1LssInitInfo* ref)
{
	int i,j,nnum,depth,maxdepth=0;
	int* next;
	int* ser;
	int* temp;
fprintf(stderr,"in depth calc num=%d\t",num);
for(i=0;i<num;i++) fprintf(stderr,"%d ",in[i]);
fprintf(stderr,"\n");

	next = (int*)memoryAllocate(sizeof(int)*num, "in lFETFeatureAlignmentInitSet_i1Lss");
	if(num==1){
		out[0] = in[0]; maxdepth = 1;
	}else{
		temp = (int*)memoryAllocate(sizeof(int)*num, "in lFETFeatureAlignmentInitSet_i1Lss");
		ser = (int*)memoryAllocate(sizeof(int)*num, "in lFETFeatureAlignmentInitSet_i1Lss");
		for(i=0;i<num;i++) temp[i]=1;
		for(i=0;i<num-1;i++){ if(temp[i]){
			nnum=0;
			for(j=i+1;j<num;j++){
				if(ref->max[in[i]][in[j]]){
					ser[nnum] = in[j];
					temp[j]=0;
					nnum++;
				}
			}
			if(nnum != 0){
				depth = __searchMatchSet(ser,next,nnum,ref);
				if(depth > maxdepth){
					maxdepth = depth;
					out[0]=in[i];
					for(j=0; j<depth; j++){
						out[j+1] = next[j];
					}
				}
			}
		}}
		if(maxdepth == 0){
			out[0] = in[0];
		}
		maxdepth++;
	}
	fprintf(stderr,"ret maxdepth=%d\n",maxdepth);
	return maxdepth;
}

void
lFETFeatureAlignmentInitPreSet_i11LMLXs(lFETFeatureAlignmentInfo* info, 
		lFETFeatureAlignment_i11LMLXsInitInfo* out)
{
	int i, j, k, l, ii, jj, lmlimit;
	int pos90, pos90t;
	int lxseries[10], lmseries[30], lxpos[10];
	double theta;
	double data;
	double score[30];
	lFETFeatureAlignmentFeature lxfets[10];

//	fprintf(stderr,"in preset\n");
	lmlimit = info->imagenum - 30;

	for(i=0,j=0,k=0;i<info->imagenum;i++){
		if(info->images[i].flagLX < 10){
			lxseries[j] = i;
			j++;
		}else if(info->images[i].flagLX > lmlimit){
			lmseries[k] = i;
			k++;
		}
	}
	
	for(i=0; i<9; i++){	
	for(j=i+1; j<10; j++){
		data = __calcImageCor11(info->images[lxseries[i]], info->images[lxseries[j]],info->imagey,0);
		out->cor[i][j][0] = out->cor[j][i][0] = data;
		data = __calcImageCor11(info->images[lxseries[i]], info->images[lxseries[j]],info->imagey,1);
		out->cor[i][j][1] = out->cor[j][i][1] = data;
	}}
//fprintf(stderr,"after corset\n");

	for(i=0;i<10;i++){
		fprintf(stderr,"%d  ",lxseries[i]);
		pos90 = info->images[lxseries[i]].posmax + info->imagey/4;
		if(pos90 >= info->imagey) pos90 -= info->imagey;
		lxfets[i].w=0.0; lxfets[i].a=0.0; lxfets[i].k=0.0;
		for(j=-5;j<=5;j++){
			pos90t = pos90 + j;
			if(pos90t >= info->imagey) pos90t -= info->imagey;
			else if(pos90t <= -1) pos90t += info->imagey;
			lFETFAfeatureAdd(&lxfets[i], &(info->images[lxseries[i]].fets[pos90t]));
		}
		lxfets[i].w/=11.0; lxfets[i].a/=11.0; lxfets[i].k/=11.0;
	}

	for(i=0;i<30;i++){
		for(j=0;j<10;j++){
			lxpos[j] = __calc90pos(lxfets[j],info->images[lmseries[i]].fets, info->imagey);
		}
		score[i] = __calcScore(out,lxpos,info->imagey);
		fprintf(stderr,"\n%d  %f\n",lmseries[i],score[i]);
	}
//fprintf(stderr,"after calc90pos and calcscore\n");

	for(i=0;i<10;i++){
		data = score[0];
		for(j=0;j<30;j++){
			if(score[j]>data){
				data = score[j];
				k=j;
			}
		}
		out->lmList[i] = lmseries[k];
		out->cvalue[i] = score[k]; 
		score[k]=-100;
		out->lxList[i] = lxseries[i];
	}
	for(i=0;i<10;i++){
		for(j=0;j<10;j++){
			out->pos[i][j] = __calc90pos(lxfets[j],info->images[lmseries[i]].fets, info->imagey);
		}
	}
}

double
__calcScore(lFETFeatureAlignment_i11LMLXsInitInfo* info, int* pos, int y)
{
	int i,j,tpos,rflag,yl,num;
	double ans=0.0, tans;
	double iscore[10];

	yl=y/12;
	
	for(i=0;i<10;i++){
		num=0;
		iscore[i] = 0.0;
		for(j=0;j<10;j++){
			if(i!=j){
				tpos = abs(pos[i] - pos[j]);
				if(tpos>11*yl || tpos<yl){ 
					rflag = 0; num++;
					iscore[i] += info->cor[i][j][rflag];
				}else if(tpos>5*yl && tpos<7*yl){ 
					rflag = 1; num++;
					iscore[i] += info->cor[i][j][rflag];
				}
			}
		}
		if(num!=0)iscore[i] /= (double)num;
		ans += iscore[i];
		fprintf(stderr,"%d  %f  ",pos[i],iscore[i]);
	}
	return ans;
}

int
__calc90pos(lFETFeatureAlignmentFeature in, lFETFeatureAlignmentFeature* ref, int y)
{
	int i,j,k;
	int ans;
	double* cor;
	double* mad; 
	double temp,tmax=-20;
	lFETFeatureAlignmentFeature fett;

	cor = (double*)memoryAllocate(sizeof(double)*y,"in __calc90pos"); 
	mad = (double*)memoryAllocate(sizeof(double)*y,"in __calc90pos");
	for(i=0;i<y;i++){
		fett.w = in.w * ref[i].w; fett.a = in.a * ref[i].a; fett.k = in.k * ref[i].k;
		cor[i] = fett.w * fett.a * fett.k;
		if(fett.w<0.0 || fett.a<0.0 || fett.k<0.0) cor[i] = fabs(cor[i]) * -1;
	}
	for(i=0;i<y;i++){
		temp=0.0;
		for(j=-1;j<=1;j++){
			k=i+j;
			if(k>=y) k-=y;
			else if(k<0) k+=y;
			temp += cor[k];
		}
		mad[i] = temp/3;
		if(mad[i]>tmax){
			tmax = mad[i];
			ans = i;
		}
	}
	//fprintf(stderr,"%d  ",ans);
	return ans;
}

double
__calcImageCor11(lFETFeatureAlignmentImageInfo i1, lFETFeatureAlignmentImageInfo i2, int y, int rev)
{
	int i;
	int p1, p2;
	lFETFeatureAlignmentFeature ans[4];
	double answer;

	p1 = i1.posmax; p2 = i2.posmax; 
	for(i=0;i<4;i++){ ans[i].w=0.0; ans[i].a=0.0; ans[i].k=0.0; }
	for(i=0; i<y; i++){
		ans[1].w += pow(i1.fets[p1].w,2);  ans[2].w += pow(i2.fets[p2].w,2);
		ans[1].a += pow(i1.fets[p1].a,2);  ans[2].a += pow(i2.fets[p2].a,2);
		ans[1].k += pow(i1.fets[p1].k,2);  ans[2].k += pow(i2.fets[p2].k,2);
		ans[3].w += i1.fets[p1].w * i2.fets[p2].w; 
		ans[3].a += i1.fets[p1].a * i2.fets[p2].a;
		ans[3].k += i1.fets[p1].k * i2.fets[p2].k;
		p1++; if(rev==0) p2++; else p2--;
		if(p1 == y) p1 -= y;
		if(p2 == y) p2 -= y;
		if(p2 == -1) p2 += y;
	}
	ans[1].w = ans[1].w * ans[2].w;  ans[1].w = pow(ans[1].w,0.5);
	ans[1].a = ans[1].a * ans[2].a;  ans[1].a = pow(ans[1].a,0.5);
	ans[1].k = ans[1].k * ans[2].k;  ans[1].k = pow(ans[1].k,0.5);
	
	ans[0].w = ans[3].w / ans[1].w;
	ans[0].a = ans[3].a / ans[1].a;
	ans[0].k = ans[3].k / ans[1].k;

	answer = ans[0].w * ans[0].a * ans[0].k;
	if((ans[0].w<0.0) || (ans[0].a<0.0) || (ans[0].k<0.0)) answer = fabs(answer) * -1;
	
	return answer;
}

void
lFETFeatureAlignmentInitSet_i11LMLXs(lFETFeatureAlignmentInfo* info, 
		lFETFeatureAlignment_i11LMLXsInitInfo* initInfo, int target)
{
	int i,j,k;
	int tar,cur,curp;
	double an[]={0.0,0.0,1.0};
	double b[]={1.0,0.0,0.0};
	double bn[]={0.0,1.0,0.0};
	double ab[3],bb[3];
	double theta, dcurp;

	for(i=0;i<info->imagenum;i++) info->images[i].interAngle = -10.0;
	tar = initInfo->lmList[target];
	lFETFAcoordcpy1(&(info->images[tar].norm),b,1);
	lFETFAcoordcpy1(&(info->images[tar].base),bn,1);
	info->images[tar].interAngle = 1.0;
	for(i=0;i<10;i++){
		cur = initInfo->lxList[i];
		dcurp = (double)(initInfo->pos[target][i] + info->imagey/4);
		lFETpointRotation(b,bn,dcurp,ab,0);
		lFETFAcoordcpy1(&(info->images[cur].norm),ab,1);
		theta = (double)info->images[cur].posmax * -1;
		lFETpointRotation(ab,b,theta,bb,0);
		lFETFAcoordcpy1(&(info->images[cur].base),bb,1);
		info->images[cur].interAngle = 1.0;
	}
}

void
lFETFeatureAlignmentInitPreSet_i2LMsLXs(lFETFeatureAlignmentInfo* info,
		 lFETFeatureAlignment_i2LMsLXsInitInfo* initInfo)
{
	int i,j,k,l,m,curmax,temp;
	int num, cnum;
	int selnum;
	int* series;
	int* sorts;
	//int** 
	double max, maxr, cur;
	double** cor;
	
fprintf(stdout,"in lFETFeatureAlignmentInitPreSet_i2LMsLXs\n");
	selnum=info->imagenum/5;
	selnum++;
	series = (int*)memoryAllocate(sizeof(int)*selnum, "in lFETFeatureAlignmentInitPreSet_i2LMsLXs");
	sorts = (int*)memoryAllocate(sizeof(int)*info->imagenum, "in lFETFeatureAlignmentInitPreSet_i2LMsLXs");
	cor = (double**)memoryAllocate(sizeof(double*)*selnum, "in lFETFeatureAlignmentInitPreSet_i2LMsLXs");
	for(i=0;i<selnum;i++) cor[i] = (double*)memoryAllocate(sizeof(double)*selnum, "in lFETFeatureAlignmentInitPreSet_i2LMsLXs");
fprintf(stdout,"in lFETFeatureAlignmentInitPreSet_i2LMsLXs %d\n",selnum);	
	for(m=0;m<2;m++){
		//fprintf(stdout,"in m loop\n");
		for(i=0;i<info->imagenum;i++) sorts[i]=i;
		for(i=0;i<selnum;i++){
			//fprintf(stdout,"in i loop\n");
			curmax=i; 
			if(m==0) max=info->images[sorts[i]].lenmax;
			else max=info->images[sorts[i]].lenmax;
			for(j=i+1;j<info->imagenum;j++){
				//fprintf(stdout,"in j loop ");
				if((info->images[sorts[j]].lenmax > max)&&m==0){
					max = info->images[sorts[j]].lenmax;
					curmax = j;
				}else if((info->images[sorts[j]].lenmax < max)&&m==1){
					max = info->images[sorts[j]].lenmax;
					curmax = j;
				}
			}
			//fprintf(stdout," j loop out\n");
			temp = sorts[i];
			sorts[i] = sorts[curmax];
			sorts[curmax] = temp;
			series[i] = sorts[i];
		}
		fprintf(stdout,"after sort selnum=%d\n",selnum);
		for(i=0;i<selnum-1;i++){ for(j=i+1;j<selnum;j++){
			max = __calcImageCor11(info->images[series[i]], info->images[series[j]],info->imagey,0);
			maxr = __calcImageCor11(info->images[series[i]], info->images[series[j]],info->imagey,1);
			if(max>maxr) cor[i][j] = cor[j][i] = max;
			else cor[i][j] = cor[j][i] = maxr;
		}}
		fprintf(stdout,"after calcImageCor %f\n",max);
		for(i=0;i<selnum;i++) sorts[i]=1;
		num = 0; 
		for(i=0; i<selnum && num<5; i++){ if(sorts[i]){
			initInfo->ser[m][num][0]=series[i];
			cnum=1;
			for(j=i+1;j<selnum && cnum<10; j++){ 
				if(cor[i][j]>0.6){
					sorts[j]=0;
					initInfo->ser[m][num][cnum]=series[j];
					cnum++;
				}
			}
			initInfo->ser[m][num][cnum]=-1;
			sorts[i]=0;
			num++;
		}}
		for(i=0;i<selnum;i++)
			fprintf(stdout,"%d: %d: %s\n",i,series[i],info->images[series[i]].imagename);
		for(i=0;i<selnum;i++){ for(j=0;j<selnum;j++){
			fprintf(stdout,"%4.3f\t",cor[i][j]);
		}fprintf(stdout,"\n");}
		fprintf(stdout,"num=%d\n",num);
		for(j=0;j<num;j++){
			for(i=0;initInfo->ser[m][j][i]!=-1;i++){
				fprintf(stdout,"%d\t",initInfo->ser[m][j][i]);
			}fprintf(stdout,"\n");}

		initInfo->num[m] = num;
		
	}
	
	
}

void
lFETFeatureAlignmentInitSet_i2LMsLXs(lFETFeatureAlignmentInfo* info,
		lFETFeatureAlignment_i2LMsLXsInitInfo* initInfo, int targetM, int targetS)
{
	int i,j,k,flag;
	int pti,ptj;
	int mser[10],sser[10],mnum,snum;
	int mserr[10],sserr[10];
	double max,maxr;
	lFETFeatureAlignmentFeature* mfets;
	lFETFeatureAlignmentFeature* sfets;
	//int tar,cur,curp;
	double an[]={0.0,0.0,1.0};
	double anr[]={0.0,0.0,-1.0};
	double b[]={1.0,0.0,0.0};
	double bn[]={0.0,1.0,0.0};
	double ab[3],bb[3],cb[3];
	double theta, dcurp;
	int matchi,matchj;
	
	for(i=0,mnum=0;initInfo->ser[0][targetM][i]!=-1;i++){
		mser[i]=initInfo->ser[0][targetM][i];
		mnum++;
	}
	for(i=0,snum=0;initInfo->ser[1][targetS][i]!=-1;i++){
		sser[i]=initInfo->ser[1][targetS][i];
		snum++;
	}
	fprintf(stderr,"cpt1  ");
	mfets = (lFETFeatureAlignmentFeature*)memoryAllocate(sizeof(lFETFeatureAlignmentFeature)*info->imagey,
			"in lFETFeatureAlignmentInitSet_i2LMsLXs");
	sfets = (lFETFeatureAlignmentFeature*)memoryAllocate(sizeof(lFETFeatureAlignmentFeature)*info->imagey,
			"in lFETFeatureAlignmentInitSet_i2LMsLXs");
	for(i=0;i<info->imagey;i++){
		mfets[i] = info->images[mser[0]].fets[i];
		sfets[i] = info->images[sser[0]].fets[i];
	}
	fprintf(stderr,"cpt2  ");
	mserr[0]=1; sserr[0]=1;
	if(mnum>1){ 
		for(j=1;j<mnum;j++){
			max = __calcImageCor11(info->images[mser[0]], info->images[mser[j]],info->imagey,0);
			maxr = __calcImageCor11(info->images[mser[0]], info->images[mser[j]],info->imagey,1);
			if(max>maxr) flag=1; else flag=-1;	mserr[j] = flag;
			pti = info->images[mser[0]].posmax; ptj = info->images[mser[j]].posmax;
			for(i=0;i<info->imagey;i++){
				lFETFAfeatureAdd(&(mfets[pti]),&(info->images[mser[j]].fets[ptj]));
				pti++; ptj+=flag;
				if(pti>=info->imagey) pti-=info->imagey;
				if(ptj>=info->imagey) ptj-=info->imagey; else if(ptj<0) ptj+=info->imagey;
			}
		}
		for(i=0;i<info->imagey;i++){
			mfets[i].w /= (double)mnum; mfets[i].k /= (double)mnum; mfets[i].k /= (double)mnum;
		}
	}
	fprintf(stderr,"cpt3  ");
	if(snum>1){ 
		for(j=1;j<snum;j++){
			max = __calcImageCor11(info->images[sser[0]], info->images[sser[j]],info->imagey,0);
			maxr = __calcImageCor11(info->images[sser[0]], info->images[sser[j]],info->imagey,1);
			if(max>maxr) flag=1; else flag=-1;	sserr[j]=flag;
			pti = info->images[sser[0]].posmax; ptj = info->images[sser[j]].posmax;
			for(i=0;i<info->imagey;i++){
				lFETFAfeatureAdd(&(sfets[pti]),&(info->images[sser[j]].fets[ptj]));
				pti++; ptj+=flag;
				if(pti>=info->imagey) pti-=info->imagey;
				if(ptj>=info->imagey) ptj-=info->imagey; else if(ptj<0) ptj+=info->imagey;
			}
		}
		for(i=0;i<info->imagey;i++){
			sfets[i].w /= (double)snum; sfets[i].k /= (double)snum; sfets[i].k /= (double)snum;
		}
	}
	fprintf(stderr,"cpt4  ");
	for(i=0;i<info->imagenum;i++) info->images[i].interAngle = -10.0;
	for(i=0;i<mnum;i++){
		lFETFAcoordcpy1(&(info->images[mser[i]].norm),an,mserr[i]);
		info->images[mser[i]].interAngle = 1.0;
		theta = (double)info->images[mser[i]].posmax*360/info->imagey * -1 * mserr[i];
		lFETpointRotation(an,b,theta,ab,0);
		lFETFAcoordcpy1(&(info->images[mser[i]].base),ab,1);
	}
	fprintf(stderr,"cpt5  ");
	max = __searchCommonLinePoint(mfets,sfets,info->imagey,&matchi,&matchj);
	fprintf(stdout,"mindis %f\tmatchi %d\t matchj %d\n  ",max,matchi,matchj);
	theta = (double)matchi - (double)info->images[mser[0]].posmax;
	theta = theta*360.0/info->imagey;
	lFETpointRotation(an,b,theta,bb,0);
	theta -= 90.0;
	lFETpointRotation(an,b,theta,ab,0);
	fprintf(stderr,"cpt6  ");
	for(i=0;i<snum;i++){
		lFETFAcoordcpy1(&(info->images[sser[i]].norm),ab,sserr[i]);
		info->images[sser[i]].interAngle = 1.0;
		theta = (double)matchj*360.0/info->imagey * -1 * sserr[i];
		lFETpointRotation(ab,bb,theta,cb,0);
		lFETFAcoordcpy1(&(info->images[sser[i]].base),cb,1);
	}
	fprintf(stdout,"maxnorm\t%f\t%f\t%f\n",info->images[mser[0]].norm.x,info->images[mser[0]].norm.y,info->images[mser[0]].norm.z);
	fprintf(stdout,"maxbase\t%f\t%f\t%f\n",info->images[mser[0]].base.x,info->images[mser[0]].base.y,info->images[mser[0]].base.z);
	fprintf(stdout,"minnorm\t%f\t%f\t%f\n",info->images[sser[0]].norm.x,info->images[sser[0]].norm.y,info->images[sser[0]].norm.z);
	fprintf(stdout,"minbase\t%f\t%f\t%f\n",info->images[sser[0]].base.x,info->images[sser[0]].base.y,info->images[mser[0]].base.z);
	
	fprintf(stderr,"cpt7  ");
	
}

double
__searchCommonLinePoint(lFETFeatureAlignmentFeature* in1, lFETFeatureAlignmentFeature* in2, int y, int* outi, int* outj)
{
	int i,j,maxi,maxj;
	double ans=150.0,cur;
	lFETFeatureAlignmentFeature temp;
	for(i=0;i<y;i++){ for(j=0;j<y/2;j++){
		temp.w = pow((in1[i].w-in2[j].w),2); temp.k = pow((in1[i].k-in2[j].k),2); temp.k = pow((in1[i].k-in2[j].k),2);
		cur = temp.w*4 + temp.a + temp.k; cur = pow(cur,0.5);
		if(cur<ans){ ans=cur; maxi=i; maxj=j; } 
	}}
	*outi = maxi; *outj = maxj;
	return ans;
}

void 
lFETFeatureAlignmentInitSet_i1L(lFETFeatureAlignmentInfo* info)
{ 
	int i;
	int seed;
	double an[]={0.0,0.0,1.0};
	double b[]={1.0,0.0,0.0};
	double ab[3];
	double theta;

	seed = info->seedImage;
	for(i=0;i<info->imagenum;i++) info->images[i].interAngle = -10.0;
	
	lFETFAcoordcpy1(&(info->images[seed].norm),an,1);
	info->images[seed].interAngle = 1.0;
	theta = (double)info->images[seed].posmax * -1;
	lFETpointRotation(an,b,theta,ab,0);
	lFETFAcoordcpy1(&(info->images[seed].base),ab,1);
}

void
lFETFeatureAlignmentInitSet_i1Ls(lFETFeatureAlignmentInfo* info, int target)
{
	int i,j,k;
	int seed;
	double an[]={0.0,0.0,1.0};
	double b[]={1.0,0.0,0.0};
	double ab[3];
	double theta;
	
	for(i=0;i<info->imagenum;i++) info->images[i].interAngle = -10.0;
	for(i=0;i<info->imagenum;i++)	if(info->images[i].flagLX == target)	seed = i;

	lFETFAcoordcpy1(&(info->images[seed].norm),an,1);
	info->images[seed].interAngle = 1.0;
	theta = (double)info->images[seed].posmax * -1;
	lFETpointRotation(an,b,theta,ab,0);
	lFETFAcoordcpy1(&(info->images[seed].base),ab,1);
}

void
lFETFeatureAlignmentInitSet_i2LXs(lFETFeatureAlignmentInfo* info, int target)
{
	int i,j,k;
	int num,seed,tar;
	int* lxseries;
	double an[]={0.0,0.0,1.0};
	double b[]={1.0,0.0,0.0};
	double bn[]={0.0,1.0,0.0};
	double ab[3],bb[3];
	double theta;
	
	for(i=0,num=0;i<info->imagenum;i++)	if(info->images[i].flagLX < 20) num++;
	lxseries = (int*)memoryAllocate(sizeof(int)*num-1,"in alignLXgroup");
	for(i=0,num=0;i<info->imagenum;i++){
		if((info->images[i].flagLX < 20) && (i != info->seedImage)){
			lxseries[num] = i;
			num++;
		}
	}
	seed = info->seedImage; tar = lxseries[target];
	for(i=0;i<info->imagenum;i++) info->images[i].interAngle = -10.0;

	lFETFAcoordcpy1(&(info->images[seed].norm),an,1);
	lFETFAcoordcpy1(&(info->images[tar].norm),bn,1);
	info->images[seed].interAngle = 1.0;
	info->images[tar].interAngle = 1.0;
	theta = (double)info->images[seed].posmax * -1;
	lFETpointRotation(an,b,theta,ab,0);
	theta = (double)info->images[tar].posmax * -1;
	lFETpointRotation(bn,b,theta,bb,0);
	lFETFAcoordcpy1(&(info->images[seed].base),ab,1);
	lFETFAcoordcpy1(&(info->images[tar].base),bb,1);
}

void
lFETFeatureAlignmentInitSet_i2PCA(lFETFeatureAlignmentInfo* info)
{
	int i,j,k,ci,cj,y,cim;
	int num, seed;
	int* seedseries;
	int te1, te2;
	lFETFeatureAlignmentImageQSInfo qs;

	for(i=0,num=0;i<info->imagenum;i++){
		if(info->images[i].flagLX < 20){
			num++;
		}
	}
	if(num < 3){
		fprintf(stderr,"few LX images are not suitable for this process\n");
		exit(0);
	}
	qs.lxseries = (int*)memoryAllocate(sizeof(int)*num,"in alignLXgroup");
	for(i=0,num=0;i<info->imagenum;i++){
		if(info->images[i].flagLX < 20){
			qs.lxseries[num] = i;
			num++;
		}
	}
	
	seedseries = (int*)memoryAllocate(sizeof(int)*num,"in alignLXgroup");
	qs.corset = (lFETFeatureAlignmentFeature**)memoryAllocate(sizeof(lFETFeatureAlignmentFeature*)*num,
			"in alignLXgroup");
	qs.cset = (int**)memoryAllocate(sizeof(int*)*num,"in alignLXgroup");
	for(i=0;i<num;i++){ 
		qs.corset[i] = (lFETFeatureAlignmentFeature*)memoryAllocate(sizeof(lFETFeatureAlignmentFeature)*num,
				"in alignLXgroup");
		qs.cset[i] = (int*)memoryAllocate(sizeof(int)*num,"in alignLXgroup");
	}
	
	y = info->imagey;
	for(i=0;i<num-1;i++){
	for(j=i;j<num;j++){
		qs.corset[i][j] = qs.corset[j][i] = __calcImageCor(info->images[qs.lxseries[i]],info->images[qs.lxseries[j]],y,&(qs.cset[i][j]));
		qs.cset[j][i] = qs.cset[i][j];
		qs.corset[i][j].t = fabs(qs.corset[i][j].w) * fabs(qs.corset[i][j].a) * fabs(qs.corset[i][j].k);
		if((qs.corset[i][j].w<0.0)||(qs.corset[i][j].a<0.0)||(qs.corset[i][j].k<0.0))
			qs.corset[i][j].t = qs.corset[j][i].t = qs.corset[i][j].t * -1; 
	}}
	//fprintf(stdout,"after corset calc, before alignLXgroup0\n");
	qs.num = num; qs.seed = seed;
	__alignLXgroup0(&qs);
	//fprintf(stdout,"before __alignLXgroupSetPara\n");
	__alignLXgroupSetPara(&qs, info);
	//fprintf(stdout,"out of __alignLXgroup\n");
}

void
__alignLXgroupSetPara(lFETFeatureAlignmentImageQSInfo* qs, lFETFeatureAlignmentInfo* info)
{
	int i,j,k,nflag,bflag;
	int cflag=-1,dflag;
	int cenima,cennum;
	int seeds[4];
	double value1, theta;
	double norm[4][3], base[3], ans[3], axis[3];

	for(i=0; i<info->imagenum; i++)
		info->images[i].interAngle = -1.0;

	//fprintf(stdout,"in __alignLXgroupSetPara\n");
	j=0;
	for(i=0;i<qs->num+4 && j<4;i++){
		if(qs->nseries[i] == -1){
			seeds[j] = qs->nseries[i+1];
			j++;
		}
	}
	if(qs->cset[seeds[1]][seeds[2]] == 1) j=1;
	else j=-1;
	if(qs->cset[seeds[1]][seeds[3]] == 1) k=1;
	else k=-1;
	
	fprintf(stderr,"seeds read %d %d %d %d\n",seeds[0],seeds[1],seeds[2],seeds[3]);
	
	value1 = 1.0/pow(2,0.5);
	norm[0][0] = 0.0; norm[0][1] = 0.0; norm[0][2] = 1.0;
	norm[1][0] = 0.0; norm[1][1] = 1.0; norm[1][2] = 0.0;
	norm[2][0] = 0.0; norm[2][1] = j*value1; norm[2][2] = -1*j*value1;
	norm[3][0] = 0.0; norm[3][1] = k*value1; norm[3][2] = k*value1;
	base[0] = 1.0; base[1] = 0.0; base[2] = 0.0;
	
	//fprintf(stdout,"values set %f \n",value1);
	
	for(i=0;i<info->imagenum;i++){
		info->images[i].norm.x = 10.0;
	}

	//fprintf(stdout,"norm set 10.0\n");
	//for(i=0;i<qs->num+4;i++) fprintf(stdout,"%d\n",qs->nseries[i]);
	
	cenima=qs->nseries[0]; nflag=1;//cennum = 0; 
	for(i=0;(i<qs->num+4)&&(cflag<4);i++){
		if(qs->nseries[i]==-1){ 
			cflag++; 
			cenima=qs->nseries[++i];
			nflag=6;
			//cennum = i;
		}	
		if(cflag < 4){
			if(nflag==6) nflag = 1;
			else nflag = qs->cset[cenima][qs->nseries[i]];
		
			lFETFAcoordcpy1(&(info->images[qs->lxseries[qs->nseries[i]]].norm),norm[cflag],nflag);
			lFATFAcoordcpy2(&(info->images[qs->lxseries[qs->nseries[i]]].norm),axis,1);
			theta = (double)info->images[qs->lxseries[qs->nseries[i]]].posmax * -1;
			lFETpointRotation(axis,base,theta,ans,0);
			lFETFAcoordcpy1(&(info->images[qs->lxseries[qs->nseries[i]]].base),ans,1);
			info->images[qs->lxseries[qs->nseries[i]]].interAngle = 1.0;
		}}
	//fprintf(stdout,"out __alignLXgroupSetPara\n");
}
/*
void
lFETFAcoordcpy1(lFETFeatureAlignmentCoord* b, double* a, int mode)
{
	b->x = a[0]*mode; b->y = a[1]*mode; b->z = a[2]*mode;
}

void
lFATFAcoordcpy2(lFETFeatureAlignmentCoord* a, double* b, int mode)
{
	b[0] = a->x*mode; b[1] = a->y*mode; b[2] = a->z*mode;
}
*/
void
__alignLXgroup0(lFETFeatureAlignmentImageQSInfo* in)
{
	int i,ii,j,jj,k,counter,counter2;
	int tnum, ttnum, ttnum2, ttnumex, ttnume, ttnumc;
	int edge1, edge2, edgc1, edgc2, flag1, flag2;
	int* temps;
	//int* exlist;
	int* tempsE;
	int* tempsC;
	//int* temps4[4], ttnum4[4], stone4[4][2];
	int seed, equa=-1, cenA=-1, cenB=-1;
	double data, data2, lam, maxl, maxlt;
	double** pcaset[3], pcaset4[4][3]; 
	//Array X, X2, C, lambda, u;
	

	temps = (int*)memoryAllocate(sizeof(int)*in->num+1,"X in __alignLXgroup0"); 
	//exlist = (int*)memoryAllocate(sizeof(int)*in->num,"X in __alignLXgroup0");
	tempsE = (int*)memoryAllocate(sizeof(int)*in->num+1,"X in __alignLXgroup0");
	tempsC = (int*)memoryAllocate(sizeof(int)*in->num+1,"X in __alignLXgroup0");
	in->nseries = (int*)memoryAllocate(sizeof(int)*in->num+4,"X in __alignLXgroup0");
	for(i=0;i<3;i++){
		 pcaset[i] = (double**)memoryAllocate(sizeof(double*)*in->num,"X in __alignLXgroup0");
		 for(j=0;j<in->num;j++){
			 pcaset[i][j] = (double*)memoryAllocate(sizeof(double)*in->num,"X in __alignLXgroup0");
		}
	}
	/*for(i=0;i<4;i++){
		temps4[i] = (int*)memoryAllocate(sizeof(int)*in->num,"X in __alignLXgroup0");
		ttnum4[i] = 0;
	}*/
	// whole pcaset create
	for(i=0;i<in->num-1;i++){
	for(j=i+1;j<in->num;j++){
		tnum=0;
		for(k=0;k<in->num;k++){	if((k!=i)&&(k!=j)){
				temps[tnum] = k;
				tnum++;
		}}
		//fprintf(stdout,"in ijloop of pca\n");
		pcaset[2][i][j] = (double)__alignLXgroupPCA(in,temps,tnum,i,j,&data,&lam,4);
		pcaset[0][j][i] = pcaset[0][i][j] = data;
		pcaset[1][j][i] = pcaset[1][i][j] = lam;
		pcaset[2][j][i] = pcaset[2][i][j];
	}}
	// seed-equa pair detect
	fprintf(stderr,"before 1st pair detection\n"); 
	maxl = -1.0; 
	seed = 0; equa = 1; 
	for(i=0;i<in->num-1;i++){
	for(j=i+1;j<in->num;j++){
		if(fabs(pcaset[0][i][j])<0.5){
			if(pcaset[1][i][j] > maxl){ maxl = pcaset[1][i][j]; seed=i; equa=j;
				fprintf(stderr,"det "); }
		}
	}}
	fprintf(stdout,"after equasearch loop, equa = %d\tseed=%d \n",equa,seed);
	// image align to seed-equa axis with mode 6
	tnum = 0;
	for(j=0; j<in->num; j++){ if((j != seed) && (j != equa)){
		tempsE[tnum] = j; tnum++;
	}}	
	ttnume = __alignLXgroupPCA(in,tempsE,tnum,seed,equa,&data,&lam,6);
	fprintf(stdout,"%d :: dec=%f\tlmd=%f\texcp=%d\n",equa,data,lam,tnum-ttnume);
	// exlist generate
	/*for(i=in->num-2, ttnum=0;i>=ttnume;i--,ttnum++){
		exlist[ttnum] = tempsE[i]; 
	}*/
	// cenA-cenB pair detect
	edge1 = (ttnume+2) / 6;  edge2 = ((ttnume+2)*5) / 6;
	cenA = 2; cenB = 3;
	maxl = -10.0; 
	for(i=edge1;i<edge2;i++){
	for(j=i+1;j<=edge2;j++){
		if(fabs(pcaset[0][tempsE[i]][tempsE[j]]) < 0.5){
			if(pcaset[1][tempsE[i]][tempsE[j]] > maxl){ 
				maxl = pcaset[1][tempsE[i]][tempsE[j]]; cenA = tempsE[i]; cenB = tempsE[j]; 
			}
		}
	}}
	fprintf(stdout,"after cen search loop, cenA = %d\tcenB = %d\n",cenA,cenB);
	fprintf(stdout,"%d-%d :: dec=%f\tlmd=%f\texcp=%d\n",cenA,cenB,pcaset[0][cenA][cenB],maxl,tnum-(int)pcaset[2][cenA][cenB]);
	temps[0]=seed; temps[1]=equa; temps[2]=cenA; temps[3]=cenB;
	tnum=0;
	for(i=0;i<4;i++){
		in->nseries[tnum] = -1; tnum++;
		in->nseries[tnum] = temps[i]; tnum++;
		for(j=0;j<in->num;j++){ if(j!=temps[i]){
			if((pcaset[0][temps[i]][j]>1.2) && (pcaset[1][temps[i]][j]>15.0)){
				in->nseries[tnum] = j; tnum++;
			}
		}}
	}
	in->nseries[tnum] = -1; tnum++;
	//fprintf(stdout,"alignLXgroup0 out\n");
		
	
	/*tnum = 0;
	for(j=0; j<in->num; j++){ if((j != cenA) && (j != cenB)){
		tempsC[tnum] = j; tnum++;
	}}
	ttnumc = __alignLXgroupPCA(in,tempsC,tnum,cenA,cenB,&data,&lam,6);
	fprintf(stdout,"%d-%d :: dec=%f\tlmd=%f\texcp=%d\n",cenA,cenB,data,lam,tnum-ttnumc);
	*/
	/*edge1 = (ttnume+2) / 3;  edge2 = ((ttnume+2)*2) / 3;
	edgc1 = (ttnumc+2) / 3;  edgc2 = ((ttnumc+2)*2) / 3;
	
	stone4[0][0]=stone4[1][0]=seed;
	stone4[2][0]=stone4[3][0]=equa;
	stone4[0][1]=stone4[2][1]=cenA;
	stone4[1][1]=stone4[3][1]=cenB;
	for(i=edge2;i>=0;i--){
		flag1=flag2=0;
		for(j=edgc2;j>=0;j--){
			if(tempsE[i]==tempsC[j]){	flag1=1; break;	}
		}
		for(j=edgc1;j<=ttnumc;j++){
			if(tempsE[i]==tempsC[j]){	flag2=1; break;	}
		}
		if(flag1){ temps4[0][ttnum4[0]] = tempsE[i]; ttnum4[0]++; }
		if(flag2){ temps4[1][ttnum4[1]] = tempsE[i]; ttnum4[1]++; }
	}
	for(i=edge1;i<=ttnume;i++){
		flag1=flag2=0;
		for(j=edgc2;j>=0;j--){
			if(tempsE[i]==tempsC[j]){   flag1=1; break; }
		}
		for(j=edgc1;j<=ttnumc;j++){
			if(tempsE[i]==tempsC[j]){   flag2=1; break; }
		}
		if(flag1){ temps4[2][ttnum4[2]] = tempsE[i]; ttnum4[2]++; }
		if(flag2){ temps4[3][ttnum4[3]] = tempsE[i]; ttnum4[3]++; }
	}
	for(i=0;i<4;i++){
		pcaset4[i][2] = (double)__alignLXgroupPCA(in,temps4[i],ttnum4[i],stone4[i][0],stone4[i][1],&data,&lam,6);
		pcaset4[i][0] = data; pcaset4[i][1] = lam;
		fprintf(stdout,"excenum = %d\n",ttnum4[i]-(int)pcaset4[i][2]);
	}*/

	
	// exlist generate 2
	/*for(i=in->num-2;i>=ttnumc;i--,ttnum++){
		ttnum2=0;
		for(j=0;j<ttnum;j++) if(exlist[j]==tempsC[i]) ttnum2=1;
		if(ttnum2==0) exlist[ttnum] = tempsC[i];
	}
	ttnumex = ttnum;*/
	//fprintf(stdout,"ttnumex = %d\n",ttnumex);

	// image mapping to seed-equa axis and cenA-B axis with mode 7
	/*tnum = 0;
	for(j=0; j<in->num; j++){ if((j != cenA) && (j != cenB)){
		tempsC[tnum] = j; tnum++;
	}}  
	ttnumc = __alignLXgroupPCA(in,tempsC,tnum,cenA,cenB,&data,&lam,7);
	fprintf(stdout,"%d-%d :: dec=%f\tlmd=%f\texcp=%d\n",cenA,cenB,data,lam,tnum-ttnumc);
	
	tnum = 0;
	for(j=0; j<in->num; j++){ if((j != in->seed) && (j != equa)){
		tempsE[tnum] = j; tnum++;
	}}
	ttnume = __alignLXgroupPCA(in,tempsE,tnum,seed,equa,&data,&lam,7);
	
	for(i=0; i<in->num; i++){
		fprintf(stdout,"%f\t%f\n",(double)tempsE[i],(double)tempsC[i]);
	}*/


	
	
/*	counter = 0;
	for(j=0; j<in->num; j++){if((j != in->seed) && (j != equa)){
		arrayDataSet2(X, 0, counter, (float)in->corset[in->seed][j].t);
		arrayDataSet2(X, 1, counter, (float)in->corset[equa][j].t);
		counter++;
	}}*/
	//arrayWriteToFile(stdout, &X, "in main");
	
	
}

int
__alignLXgroupPCA(lFETFeatureAlignmentImageQSInfo* in, int* ts, int tnum, int l, int r, double* dec, double* lmd, int mode)
{
	int i,j,k,counter,excep,lrcount;
	int maxi, temp;
	double data, data2, lam;
	Array X, X2, C, lambda, u, ave;
	
	X.dim = 2; X.n[0] = 2; X.n[1] = tnum; arrayInit(&X, "X in __alignLXgroup0");
	counter = 0;
	for(i=0; i<tnum; i++){ if((ts[i]!=l)&&(ts[i]!=r)){
		arrayDataSet2(X, 0, counter, (float)in->corset[l][ts[i]].t);
		arrayDataSet2(X, 1, counter, (float)in->corset[r][ts[i]].t);
		counter++;
	}}
	//fprintf(stdout,"%d %d %d %d\n",mode,mode&0x04,mode&0x02,mode&0x01);
	//if((mode&0x02) == 2) arrayWriteToFile(stdout, &X, "in main");
	if((mode&0x08)==8){
		//maxi=pow(2,0.5); maxi=1.0/maxi;
		arrayDataSet2(u, 0, 0, 1.0/pow(2,0.5));
		arrayDataSet2(u, 1, 0, -1.0/pow(2,0.5));
		arrayDataSet2(u, 0, 1, -1.0/pow(2,0.5));
		arrayDataSet2(u, 1, 1, 1.0/pow(2,0.5));
	}else{
		arrayPCA(&u, &C, &lambda, &X, &ave, 0);
	}
	//fprintf(stdout,"%d-%d::\t",l,r);
	if((mode&0x04) == 4){
		data = arrayDataGet2(u, 0, 0) + arrayDataGet2(u, 1, 0);
		if((fabs(data) < 0.3) || (fabs(data) > 1.114)){
			counter = 0;
			//lrcount=0;
			for(i=0; i<tnum; i++){ if((ts[i]!=l)&&(ts[i]!=r)){
				data2 = in->corset[l][ts[i]].t * arrayDataGet2(u, 0, 1)
					+ in->corset[r][ts[i]].t * arrayDataGet2(u, 1, 1);
				arrayDataSet2(X, 1, i, (float)data2);
				/*if((mode&0x08)==8){ if(fabs(data2) < 0.4) counter++; }
				else{ if(fabs(data2) < 0.3) counter++; }
				*/
				if(fabs(data2) < 0.3) counter++;
				if((mode&0x02) == 2){
					data2 = in->corset[l][ts[i]].t * arrayDataGet2(u, 0, 0)
						+ in->corset[r][ts[i]].t * arrayDataGet2(u, 1, 0);
					arrayDataSet2(X, 0, i, (float)data2);
				}
				//lrcount++;
			}}
			//excep = counter;
			//fprintf(stdout,"low 2ndPC image num = %d\n",counter);
			X2.dim = 2; X2.n[0] = 2; X2.n[1] = counter; arrayInit(&X2, "X in __alignLXgroup0");
			counter = 0;
			//lrcount=0;
			for(i=0; i<tnum; i++){ if((ts[i]!=l)&&(ts[i]!=r)){
				if(fabs(arrayDataGet2(X,1,i)) < 0.3){
					arrayDataSet2(X2, 0, counter, (float)in->corset[l][ts[i]].t);
					arrayDataSet2(X2, 1, counter, (float)in->corset[r][ts[i]].t);
					counter++;
				}
				//lrcount++;
			}}
			excep = counter;
			//fprintf(stdout,"%d-%d::\n",l,r);
			arrayPCA(&u, &C, &lambda, &X2, &ave, 0);
			//fprintf(stdout,"%d-%d::\n",l,r);
		}else{ 
			//fprintf(stdout,"else \n");
			excep = tnum; 
		}
	}
	//fprintf(stdout,"after 1st loop \n");
	
	if((mode&0x02) == 2){
		counter=tnum-1;
		for(i=tnum-1;i>=0;i--){
			if(fabs(arrayDataGet2(X,1,i))>0.3){
				temp = ts[counter]; ts[counter] = ts[i]; ts[i] = temp;
				counter--; 
			}
		}
		counter++;
		
		if(arrayDataGet2(u, 0, 0) > 0.0) k = 1; 	else k = -1;
		for(i=0; i<counter-1; i++){
			maxi = i;
			for(j=0; j<counter; j++){
				if((arrayDataGet2(X,0,j))*k > (arrayDataGet2(X,0,maxi))*k) maxi=j;
			}
			temp=ts[i];	ts[i]=ts[maxi];	ts[maxi]=temp; 
		}
	}else if((mode&0x03) == 3){
		if(arrayDataGet2(u, 0, 0) > 0.0) k = 10000;     else k = -10000;
		counter = 0;
		if(l>r){ temp = l; l=r; r=temp; temp=-1;}
		else temp=1;
		for(i=0;i<tnum;i++){
			if(counter==l){
				ts[counter] = (int)10000.0*temp;
				counter++;
			}if(counter==r){
				ts[counter] = (int)-10000.0*temp;
				counter++;
			}
			ts[counter] = (int)(arrayDataGet2(X,0,i)*k);
			counter++;
		}
	}
	//fprintf(stdout,"after 2nd if \n");
	if((mode&0x04) == 0) excep = tnum;
    *lmd = arrayDataGet1(lambda, 0) / arrayDataGet1(lambda, 1);
	*dec = arrayDataGet2(u, 0, 0) + arrayDataGet2(u, 1, 0);
	//fprintf(stdout,"dec=%f\tlmd=%f\n",*dec,*lmd);
	//if(mode&0x04 == 0) excep = tnum;
	return excep;
}

lFETFeatureAlignmentFeature
__calcImageCor(lFETFeatureAlignmentImageInfo i1, lFETFeatureAlignmentImageInfo i2, int y, int* a)
{
	int i,j,p1,p2a,p2b;
	int si1, si2;
	lFETFeatureAlignmentFeature ans[5];

	p1 = i1.posmax; p2a = i2.posmax; p2b = i2.posmax;
	for(i=0;i<5;i++){ ans[i].w=0.0; ans[i].a=0.0; ans[i].k=0.0; }
	for(i=0; i<y; i++){
		ans[1].w += pow(i1.fets[p1].w,2);  ans[2].w += pow(i2.fets[p2a].w,2);
		ans[1].a += pow(i1.fets[p1].a,2);  ans[2].a += pow(i2.fets[p2a].a,2);
		ans[1].k += pow(i1.fets[p1].k,2);  ans[2].k += pow(i2.fets[p2a].k,2);
		ans[3].w += i1.fets[p1].w * i2.fets[p2a].w;  ans[4].w += i1.fets[p1].w * i2.fets[p2b].w;
		ans[3].a += i1.fets[p1].a * i2.fets[p2a].a;  ans[4].a += i1.fets[p1].a * i2.fets[p2b].a;
		ans[3].k += i1.fets[p1].k * i2.fets[p2a].k;  ans[4].k += i1.fets[p1].k * i2.fets[p2b].k;
		p1++; p2a++; p2b--;
		if(p1 == y) p1 -= y;
		if(p2a == y) p2a -= y;
		if(p2b == -1) p2b += y;
	}
	ans[1].w = ans[1].w * ans[2].w;  ans[1].w = pow(ans[1].w,0.5);
	ans[1].a = ans[1].a * ans[2].a;  ans[1].a = pow(ans[1].a,0.5);
	ans[1].k = ans[1].k * ans[2].k;  ans[1].k = pow(ans[1].k,0.5);
	
	if(ans[3].w >= ans[4].w){ j=3; *a = 1; }
	else{ j=4; *a = -1; }
	ans[0].w = ans[j].w / ans[1].w;
	ans[0].a = ans[j].a / ans[1].a;
	ans[0].k = ans[j].k / ans[1].k;

	return ans[0];
}









