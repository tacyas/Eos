/*
# lFETOrientationSearchByFeatureAlignmentSphere : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : lFETOrientationSearchByFeatureAlignmentSphere 
# Attention
#   $Loccker$
#  	$State$ 
#
*/
/* $Log$ */


#include "lFETOrientationSearchByFeatureAlignment.h"
#define PI1 3.141592654

//void lFETFAvectorProduct1(double* a, double* b, double* ans);
//double lFETFAcalcCoordDistance(lFETFeatureAlignmentCoord a, lFETFeatureAlignmentCoord b);
//lFETFeatureAlignmentCoord lFETFAcalcCoordSum(lFETFeatureAlignmentCoord a, lFETFeatureAlignmentCoord b, lFETFeatureAlignmentCoord c, lFETFeatureAlignmentCoord d);
//void lFETFAcoordcpy1(lFETFeatureAlignmentCoord* b, double* a, int mode);
//void lFATFAcoordcpy2(lFETFeatureAlignmentCoord* a, double* b, int mode);
//void lFETFAfeaturecpy1(lFETFeatureAlignmentFeature* b, double* a);
//void lFETFAfeatureAdd(lFETFeatureAlignmentFeature* b, lFETFeatureAlignmentFeature* a);

lFETFeatureAlignmentSpherePointInfo __calcStickPointSum(lFETFeatureAlignmentSpherePointInfo p1, lFETFeatureAlignmentSpherePointInfo p2, lFETFeatureAlignmentSpherePointInfo p3, lFETFeatureAlignmentSpherePointInfo p4);
void __sphereSquareMalloc(lFETFeatureAlignmentSphereInfo* sph, int size, int malloct);
void __sphereSquareFree(lFETFeatureAlignmentSphereInfo* sph, int freet);
lFETFeatureAlignmentSpherePointInfo* __sphereSearchPoint(lFETFeatureAlignmentSphereInfo* sph, lFETFeatureAlignmentCoord in);
void __spherePointLink2(lFETFeatureAlignmentSpherePointInfo* a,lFETFeatureAlignmentSpherePointInfo* b);
void __spherePointLink3(lFETFeatureAlignmentSpherePointInfo* a,lFETFeatureAlignmentSpherePointInfo* b, lFETFeatureAlignmentSpherePointInfo* c);
					
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

double
lFETFAcalcCoordDistance(lFETFeatureAlignmentCoord a, lFETFeatureAlignmentCoord b)
{
	double dis;
	dis = pow((a.x-b.x),2) + pow((a.y-b.y),2) + pow((a.z-b.z),2);
	dis = pow(dis,0.5);
	return dis;
}

lFETFeatureAlignmentCoord 
lFETFAcalcCoordSum(lFETFeatureAlignmentCoord a, lFETFeatureAlignmentCoord b, lFETFeatureAlignmentCoord c, lFETFeatureAlignmentCoord d)
{
	lFETFeatureAlignmentCoord ans;
	double len;
	ans.x = a.x + b.x + c.x + d.x;
	ans.y = a.y + b.y + c.y + d.y;
	ans.z = a.z + b.z + c.z + d.z;
	len = pow(ans.x,2) + pow(ans.y,2) + pow(ans.z,2);
	len = pow(len,0.5);
	if(len > 0.00001){ ans.x /= len;  ans.y /= len;  ans.z /= len; }
	return ans;
}

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

void
lFETFAfeaturecpy1(lFETFeatureAlignmentFeature* b, double* a)
{
	b->w = a[0]; b->a = a[1]; b->k = a[2];
}

void
lFETFAfeatureAdd(lFETFeatureAlignmentFeature* b, lFETFeatureAlignmentFeature* a)
{
	b->w += a->w; b->a += a->a; b->k += a->k;
}
*/
void
lFETFeatureAlignmentSphereInit(lFETFeatureAlignmentSphereInfo* sph, int mode)
{   
	int i, j, k, i2;
	int size=3, ce=1;
	int cur, count;
	double value1, value2, value;
	double v0[3];
	lFETFeatureAlignmentSphereSquareInfo* curr;
	
	if(mode){
		__sphereSquareFree(sph,sph->curSwitch);
	}
	__sphereSquareMalloc(sph,size,0);
	cur = sph->curSwitch = 0;
	curr = sph->sq6[cur];

	value1 = cos(PI1/4);
	value2 = 1/pow(3.0,0.5);
	count = 0;

	for(i=0;i<3;i++) v0[i]=0.0;
	
	for(i=0; i<6; i++){
		if(i<3) i2 = 1;
		else i2 = -1;
		for(j=-1; j<=1; j++){
		for(k=-1; k<=1; k++){
			if(j*k != 0)    value = value2;
			else if(j+k != 0) value = value1;
			else value = 1.0;
			if(i%3 == 0){
				curr[i].sq[ce-j][ce-k].self.x = i2*value;
				curr[i].sq[ce-j][ce-k].self.y = j*value;
				curr[i].sq[ce-j][ce-k].self.z = k*value;
			}else if(i%3 == 1){
				curr[i].sq[ce-j][ce-k].self.y = i2*value;
				curr[i].sq[ce-j][ce-k].self.z = j*value;
				curr[i].sq[ce-j][ce-k].self.x = k*value;
			}else{
				curr[i].sq[ce-j][ce-k].self.z = i2*value;
				curr[i].sq[ce-j][ce-k].self.x = j*value;
				curr[i].sq[ce-j][ce-k].self.y = k*value;
			}
			lFETFAfeaturecpy1(&(curr[i].sq[ce+j][ce+k].fets),v0);
			lFETFAfeaturecpy1(&(curr[i].sq[ce+j][ce+k].nfets),v0);
			curr[i].sq[ce+j][ce+k].nnum = 0;
		}
		}
		
	}
}

void
__sphereSquareMalloc(lFETFeatureAlignmentSphereInfo* sph, int size, int malloct)
{
	int i,j;
	for(i=0; i<6; i++){
		sph->sq6[malloct][i].sq = 
			(lFETFeatureAlignmentSpherePointInfo**)memoryAllocate(sizeof(lFETFeatureAlignmentSpherePointInfo*)*size,
																   "in lFETFeatureAlignmentSphereInit");
		for(j=0; j<size; j++){
			sph->sq6[malloct][i].sq[j] = 
				(lFETFeatureAlignmentSpherePointInfo*)memoryAllocate(sizeof(lFETFeatureAlignmentSpherePointInfo)*size,
																	  "in lFETFeatureAlignmentSphereInit");
		}
		sph->sq6[malloct][i].center = (size-1)/2;
	}
}

void
__sphereSquareFree(lFETFeatureAlignmentSphereInfo* sph, int freet)
{
	int i, j, size;

	size = sph->sq6[freet][0].center;
	if(size!=0){
	size = 1+(size*2);
	for(i=0;i<6;i++){
		for(j=0;j<size;j++){
			free(sph->sq6[freet][i].sq[j]);
		}
		free(sph->sq6[freet][i].sq);
		sph->sq6[freet][i].center = 0;
	}
	}
	
}

void 
lFETFeatureAlignmentSphereDegenerate(lFETFeatureAlignmentSphereInfo* sph)
{   
	int i, j, k;
	int new, cur, nsize, csize;
	double v0[3];
	lFETFeatureAlignmentSpherePointInfo dummy;
	
	dummy.fets.w = -10000.0;
	for(i=0;i<3;i++) v0[i]=0.0;
	cur = sph->curSwitch;
	csize = sph->sq6[cur][0].center;
	csize = (csize*2)+1;
	nsize = ((csize-1)/2) + 1;
	if(cur==0) new=1;
	else new=0;
	sph->curSwitch = new;
	fprintf(stdout,"before spmalloc\n");
	__sphereSquareMalloc(sph,nsize,new);
	fprintf(stdout,"after spmalloc\n");
	
	for(i=0; i<6; i++){
		for(j=0; j<nsize; j++){
		for(k=0; k<nsize; k++){ 
			sph->sq6[new][i].sq[j][k] = sph->sq6[cur][i].sq[j*2][k*2];
		}}
	}
	fprintf(stdout,"before spfree\n");
	__sphereSquareFree(sph,cur);
}
	
void 
lFETFeatureAlignmentSphereDevide(lFETFeatureAlignmentSphereInfo* sph)
{
	int i, j, k;
	int new, cur, nsize, csize;
	double v0[3];
	lFETFeatureAlignmentSpherePointInfo dummy;

	dummy.fets.w = -10000.0;
	for(i=0;i<3;i++) v0[i]=0.0;

	cur = sph->curSwitch;
	csize = sph->sq6[cur][0].center;
	csize = (csize*2)+1;
	nsize = ((csize-1)*2) + 1;
	if(cur==0) new=1;
	else new=0;
	sph->curSwitch = new;
	
	__sphereSquareMalloc(sph,nsize,new);
	
	for(i=0; i<6; i++){
		for(j=0; j<csize; j++){
		for(k=0; k<csize; k++){	
			sph->sq6[new][i].sq[j*2][k*2] = sph->sq6[cur][i].sq[j][k];
		}		}
		for(j=1; j<nsize; j=j+2){
		for(k=1; k<nsize; k=k+2){
			sph->sq6[new][i].sq[j][k] = __calcStickPointSum(sph->sq6[new][i].sq[j-1][k-1],
					sph->sq6[new][i].sq[j-1][k+1],
					sph->sq6[new][i].sq[j+1][k-1],
					sph->sq6[new][i].sq[j+1][k+1]);
		}		}
		for(j=0; j<nsize; j=j+2){
		for(k=1; k<nsize; k=k+2){
			sph->sq6[new][i].sq[j][k] = __calcStickPointSum(sph->sq6[new][i].sq[j][k-1],
					sph->sq6[new][i].sq[j][k+1],dummy,dummy);
		}		}
		for(j=1; j<nsize; j=j+2){
		for(k=0; k<nsize; k=k+2){
			sph->sq6[new][i].sq[j][k] = __calcStickPointSum(sph->sq6[new][i].sq[j-1][k],
					sph->sq6[new][i].sq[j+1][k],dummy,dummy);
		}		}
	}
	for(i=0; i<6; i++){
		for(j=0; j<nsize; j++){
		for(k=0; k<nsize; k++){  
			sph->sq6[new][i].sq[j][k].nnum = 0;
			lFETFAfeaturecpy1(&(sph->sq6[new][i].sq[j][k].nfets), v0);
		}}
	}
	__sphereSquareFree(sph,cur);
}

void 
lFETFeatureAlignmentSphereRandDisturb(lFETFeatureAlignmentSphereInfo* sph)
{
	int i;
	lFETFeatureAlignmentCoord temp;
	lFETFeatureAlignmentSpherePointInfo* cur;
	double len;
	
	temp.x = 10.0;
	temp.y = 7.0;
	temp.z = 5.0;
	len = pow(temp.x,2) + pow(temp.y,2) + pow(temp.z,2);
	len = pow(len,0.5);
	temp.x /= len; temp.y /= len; temp.z /= len;
	cur = __sphereSearchPoint(sph, temp);
	i = sph->sq6[sph->curSwitch][0].center;
	cur->fets = sph->sq6[sph->curSwitch][0].sq[i][i].fets;
}

lFETFeatureAlignmentSpherePointInfo*
__sphereSearchPoint(lFETFeatureAlignmentSphereInfo* sph, lFETFeatureAlignmentCoord in)
{
	int i,j,k,mapn;
	int mnum, min2, max2, min3, max3;
	double dis,mindis=10.0;
	int mini, minj;
	
	mnum = (sph->sq6[sph->curSwitch][0].center * 2) + 1;
	if(fabs(in.x) >= fabs(in.y) && fabs(in.x) >= fabs(in.z)){
		if(in.x > 0.0)	mapn=0;	else mapn=3;
		if(in.y >= 0.0){ min2 = 0; max2 = sph->sq6[sph->curSwitch][0].center+1; }
		else{ min2 = sph->sq6[sph->curSwitch][0].center; max2 = mnum; }
		if(in.z >= 0.0){ min3 = 0; max3 = sph->sq6[sph->curSwitch][0].center+1; }
		else{ min3 = sph->sq6[sph->curSwitch][0].center; max3 = mnum; }
	}else if(fabs(in.y) >= fabs(in.z) && fabs(in.y) >= fabs(in.x)){
		if(in.y > 0.0)	mapn=1; else mapn=4;
		if(in.z >= 0.0){ min2 = 0; max2 = sph->sq6[sph->curSwitch][0].center+1; }
	    else{ min2 = sph->sq6[sph->curSwitch][0].center; max2 = mnum; }
	    if(in.x >= 0.0){ min3 = 0; max3 = sph->sq6[sph->curSwitch][0].center+1; }
	    else{ min3 = sph->sq6[sph->curSwitch][0].center; max3 = mnum; }
	}else if(fabs(in.z) >= fabs(in.x) && fabs(in.z) >= fabs(in.y)){
		if(in.z > 0.0)	mapn=2; else mapn=5;
		if(in.x >= 0.0){ min2 = 0; max2 = sph->sq6[sph->curSwitch][0].center+1; }
        else{ min2 = sph->sq6[sph->curSwitch][0].center; max2 = mnum; }
        if(in.y >= 0.0){ min3 = 0; max3 = sph->sq6[sph->curSwitch][0].center+1; }
        else{ min3 = sph->sq6[sph->curSwitch][0].center; max3 = mnum; }
	}
	for(i=min2;i<max2;i++){
	for(j=min3;j<max3;j++){
		dis = lFETFAcalcCoordDistance(sph->sq6[sph->curSwitch][mapn].sq[i][j].self,in);
		if(dis < mindis){
			mini = i; minj = j; mindis = dis;
		}
	}}
	//fprintf(stdout,"%d %d %d\n",mapn,mini,minj);
	return &(sph->sq6[sph->curSwitch][mapn].sq[mini][minj]);
}

void
__spherePointLink2(lFETFeatureAlignmentSpherePointInfo* a,lFETFeatureAlignmentSpherePointInfo* b)
{
	int num;
	num = a->nnum + b->nnum;
	lFETFAfeatureAdd(&(a->nfets), &(b->nfets));
	b->nfets = a->nfets;
	a->nnum = num; b->nnum = num;
}

void 
__spherePointLink3(lFETFeatureAlignmentSpherePointInfo* a,lFETFeatureAlignmentSpherePointInfo* b, lFETFeatureAlignmentSpherePointInfo* c)
{
	int num;
	num = a->nnum + b->nnum + c->nnum;
	lFETFAfeatureAdd(&(a->nfets), &(b->nfets));
	lFETFAfeatureAdd(&(a->nfets), &(c->nfets));
	b->nfets = c->nfets = a->nfets;
	a->nnum = num; b->nnum = num; c->nnum = num;
}

void
lFETFeatureAlignmentSphereFeatureSet(lFETFeatureAlignmentInfo* info)
{
	int i,j,k,l;
	double dr, theta;
	int mapni, mapnj,mapnk,mnum;
	lFETFeatureAlignmentSpherePointInfo* cur; 
	lFETFeatureAlignmentCoord curc;
	double tnorm[3], tpoint[3], tans[3], v0[3];

	mnum = (info->sph.sq6[info->sph.curSwitch][0].center)*2;
	for(i=0;i<6;i++){
		for(j=0;j<mnum+1;j++){
		for(k=0;k<mnum+1;k++){
			info->sph.sq6[info->sph.curSwitch][i].sq[j][k].nnum = 0;
		}}
	}
	dr = 360.0/info->imagey;
	for(i=0;i<info->imagenum;i++){	if((info->images[i].norm.x <= 1.0)&&(info->images[i].interAngle>=info->srl)){
		lFATFAcoordcpy2(&(info->images[i].norm),tnorm,1);
		lFATFAcoordcpy2(&(info->images[i].base),tpoint,1);
		for(j=0;j<info->imagey;j++){
			theta = j*dr;
			lFETpointRotation(tnorm,tpoint,theta,tans,0);
			lFETFAcoordcpy1(&curc,tans,1);
			cur = __sphereSearchPoint(&(info->sph),curc);
			lFETFAfeatureAdd(&(cur->nfets),&(info->images[i].fets[j]));
			cur->nnum++;
			/*if(info->images[i].interAngle<0.4){
				lFETFAfeatureAdd(&(cur->nfets),&(info->images[i].fets[j]));
				lFETFAfeatureAdd(&(cur->nfets),&(info->images[i].fets[j]));
				lFETFAfeatureAdd(&(cur->nfets),&(info->images[i].fets[j]));
				lFETFAfeatureAdd(&(cur->nfets),&(info->images[i].fets[j]));
				lFETFAfeatureAdd(&(cur->nfets),&(info->images[i].fets[j]));
				lFETFAfeatureAdd(&(cur->nfets),&(info->images[i].fets[j]));
				lFETFAfeatureAdd(&(cur->nfets),&(info->images[i].fets[j]));
				lFETFAfeatureAdd(&(cur->nfets),&(info->images[i].fets[j]));
				lFETFAfeatureAdd(&(cur->nfets),&(info->images[i].fets[j]));
				lFETFAfeatureAdd(&(cur->nfets),&(info->images[i].fets[j]));
				cur->nnum += 10;
			}else if(info->images[i].interAngle<0.5){
				lFETFAfeatureAdd(&(cur->nfets),&(info->images[i].fets[j]));
				lFETFAfeatureAdd(&(cur->nfets),&(info->images[i].fets[j]));
				lFETFAfeatureAdd(&(cur->nfets),&(info->images[i].fets[j]));
				lFETFAfeatureAdd(&(cur->nfets),&(info->images[i].fets[j]));
				lFETFAfeatureAdd(&(cur->nfets),&(info->images[i].fets[j]));
				lFETFAfeatureAdd(&(cur->nfets),&(info->images[i].fets[j]));
				cur->nnum += 6;
			}else if(info->images[i].interAngle<0.7){
				lFETFAfeatureAdd(&(cur->nfets),&(info->images[i].fets[j]));
				lFETFAfeatureAdd(&(cur->nfets),&(info->images[i].fets[j]));
				cur->nnum+=2;
			}*/
			
		}
	}}
	// sphere square edge processing
	for(i=0;i<=1;i++){ 	if(i==0) mapni=0; else mapni=3;
	for(j=0;j<=1;j++){	if(j==0) mapnj=1; else mapnj=4;
	for(k=0;k<=1;k++){	if(k==0) mapnk=2; else mapnk=5;
		__spherePointLink3(&(info->sph.sq6[info->sph.curSwitch][mapni].sq[j*mnum][k*mnum]),
				&(info->sph.sq6[info->sph.curSwitch][mapnj].sq[k*mnum][i*mnum]),
				&(info->sph.sq6[info->sph.curSwitch][mapnk].sq[i*mnum][j*mnum]));
	}}}
	for(i=0;i<3;i++){
		for(j=0;j<=1;j++){ mapnj=i+1; if((j==0)&&(mapnj>=3)) mapnj-=3;	else if((j==1)&&(mapnj<3)) mapnj+=3;	
		for(k=0;k<=1;k++){ mapnk=i+2; if((k==0)&&(mapnk>=3)) mapnk-=3;  else if((k==1)&&(mapnk<3)) mapnk+=3;
			for(l=1;l<mnum;l++){
				__spherePointLink2(&(info->sph.sq6[info->sph.curSwitch][mapnj].sq[j*mnum][l]),
						&(info->sph.sq6[info->sph.curSwitch][mapnk].sq[l][j*mnum]));
			}
		}}
	}
	
	// sphere points fets average processing
	for(i=0;i<3;i++) v0[i] = 0.0; 
	for(i=0;i<6;i++){
		for(j=0;j<mnum+1;j++){
		for(k=0;k<mnum+1;k++){
			l = info->sph.sq6[info->sph.curSwitch][i].sq[j][k].nnum;
			if(l>0){
				info->sph.sq6[info->sph.curSwitch][i].sq[j][k].nfets.w /= (double)l;
				info->sph.sq6[info->sph.curSwitch][i].sq[j][k].nfets.a /= (double)l;
				info->sph.sq6[info->sph.curSwitch][i].sq[j][k].nfets.k /= (double)l;
				info->sph.sq6[info->sph.curSwitch][i].sq[j][k].nnum = 0;
				info->sph.sq6[info->sph.curSwitch][i].sq[j][k].fets = info->sph.sq6[info->sph.curSwitch][i].sq[j][k].nfets;
				lFETFAfeaturecpy1(&(info->sph.sq6[info->sph.curSwitch][i].sq[j][k].nfets),v0);
			}
			/*lFETFAfeatureAdd(&(info->sph.sq6[info->sph.curSwitch][i].sq[j][k].fets),
					&(info->sph.sq6[info->sph.curSwitch][i].sq[j][k].nfets));
			dr = (double)info->sph.sq6[info->sph.curSwitch][i].sq[j][k].nnum + 1;
			info->sph.sq6[info->sph.curSwitch][i].sq[j][k].fets.w /= dr;
			info->sph.sq6[info->sph.curSwitch][i].sq[j][k].fets.a /= dr;
			info->sph.sq6[info->sph.curSwitch][i].sq[j][k].fets.k /= dr;
			info->sph.sq6[info->sph.curSwitch][i].sq[j][k].nnum = 0;
			lFETFAfeaturecpy1(&(info->sph.sq6[info->sph.curSwitch][i].sq[j][k].nfets),v0);
			*/
		}}
	}
}

int
lFETFeatureAlignmentSphereRefGenerate(lFETFeatureAlignmentInfo* in, lFETFeatureAlignmentImageInfo* out)
{
	int i,j,k,l,m, cen;
	int mnum, refnum;
	int imagey;
	double axis[3][3], point[3], ans[3], caxis[3];
	double theta, dr;
	lFETFeatureAlignmentSpherePointInfo* sppt;
	lFETFeatureAlignmentCoord tcoord;

	for(i=0;i<3;i++) for(j=0;j<3;j++) axis[i][j] = 0.0; 
	for(i=0;i<3;i++){
		j=i+1; if(j>2) j-=3;
		axis[i][j] = 1.0;
	}
	mnum = (in->sph.sq6[in->sph.curSwitch][0].center * 2) + 1;
	imagey = in->imagey;
	dr = 360/imagey;
	refnum = 0; cen = in->sph.sq6[in->sph.curSwitch][0].center; cen = cen*2;
	for(i=0;i<6;i++){
		for(j=0;j<mnum;j++){
		for(k=0;k<mnum;k++){
			out[refnum].norm = in->sph.sq6[in->sph.curSwitch][i].sq[j][k].self;
			out[refnum].spt[0] = &(in->sph.sq6[in->sph.curSwitch][i].sq[j][k]);
			out[refnum].spt[1] = &(in->sph.sq6[in->sph.curSwitch][(i+3)%6].sq[cen-j][cen-k]);
			lFATFAcoordcpy2(&(out[refnum].norm),caxis,1);
			lFETFAvectorProduct1(caxis,axis[i%3],point);
			lFETFAcoordcpy1(&(out[refnum].base),point,1);
			out[refnum].fets = (lFETFeatureAlignmentFeature*)memoryAllocate(sizeof(lFETFeatureAlignmentFeature)*imagey,"in lFETFeatureAlignmentSphereRefGenerate");
			for(l=0;l<imagey;l++){
				theta = l*dr;
				lFETpointRotation(caxis,point,theta,ans,0);
				lFETFAcoordcpy1(&tcoord,ans,1);
				sppt = __sphereSearchPoint(&(in->sph),tcoord);
				out[refnum].fets[l] = sppt->fets;
			}
			out[refnum].next = ++refnum;
			//refnum++;
		}}
	}
	out[refnum].next = -2;
	return refnum;
}

lFETFeatureAlignmentSpherePointInfo
__calcStickPointSum(lFETFeatureAlignmentSpherePointInfo p1, lFETFeatureAlignmentSpherePointInfo p2, lFETFeatureAlignmentSpherePointInfo p3, lFETFeatureAlignmentSpherePointInfo p4)
{
	int ave=2;
	double len;
	lFETFeatureAlignmentSpherePointInfo ans;

	ans.self.x = p1.self.x + p2.self.x; 
	ans.self.y = p1.self.y + p2.self.y; 
	ans.self.z = p1.self.z + p2.self.z;
	ans.fets.w = p1.fets.w + p2.fets.w;
	ans.fets.a = p1.fets.a + p2.fets.a;
	ans.fets.k = p1.fets.k + p2.fets.k;
	if(p3.fets.w > -9999.0){
		ans.self.x += p3.self.x + p4.self.x;
	    ans.self.y += p3.self.y + p4.self.y; 
	    ans.self.z += p3.self.z + p4.self.z;
	    ans.fets.w += p3.fets.w + p4.fets.w;
		ans.fets.a += p3.fets.a + p4.fets.a;
	    ans.fets.k += p3.fets.k + p4.fets.k;
		ave += 2;
	}
	ans.fets.w /= ave;    ans.fets.a /= ave;    ans.fets.k /= ave;
	len = pow(ans.self.x,2) + pow(ans.self.y,2) + pow(ans.self.z,2); 	len = pow(len,0.5);
	ans.self.x /= len; 	ans.self.y /= len;	ans.self.z /= len;

	return ans;
}



