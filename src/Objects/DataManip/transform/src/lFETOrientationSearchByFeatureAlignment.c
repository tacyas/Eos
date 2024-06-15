/*
# lFETOrientationSearchByFeatureAlignment : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : lFETOrientationSearchByFeatureAlignment 
# Attention
#   $Loccker$
#  	$State$ 
#
*/
/* $Log$ */

#include <string.h>

#include "lFETOrientationSearchByFeatureAlignment.h"
#define PI1 3.141592654

void __inRead(FILE* in, lFETFeatureAlignmentInfo* out, int mode);
double __inReadA(FILE* in, lFETFeatureAlignmentInfo* out, int mode);
void __calcMAXMIN(lFETFeatureAlignmentInfo* info);
//void __generateInitialState(lFETFeatureAlignmentInfo* info);
void __FeatureAlignmentIter(lFETFeatureAlignmentInfo* info, int itmax, int devmax, int mode);
void __FeatureAlignmentPrint(lFETFeatureAlignmentInfo* info, FILE* out, FILE* outA, FILE* out2D, int mode);
	
/*	
double lFETFAcalcCoordDistance(lFETFeatureAlignmentCoord a, lFETFeatureAlignmentCoord b);
lFETFeatureAlignmentCoord lFETFAcalcCoordSum(lFETFeatureAlignmentCoord a, lFETFeatureAlignmentCoord b, lFETFeatureAlignmentCoord c, lFETFeatureAlignmentCoord d);
void lFETFAcoordcpy1(lFETFeatureAlignmentCoord* b, double* a, int mode);
void lFATFAcoordcpy2(lFETFeatureAlignmentCoord* a, double* b, int mode);
void lFETFAfeaturecpy1(lFETFeatureAlignmentFeature* b, double* a);
void lFETFAfeatureAdd(lFETFeatureAlignmentFeature* b, lFETFeatureAlignmentFeature* a);
*/

void __arrayNorm(Array* in);
//void lFETFAvectorProduct1(double* a, double* b, double* ans);

void __convCoordYOYS(lFETFeatureAlignmentImageInfo* in);
void __spherePrint(lFETFeatureAlignmentInfo* in, int a, int b);
//void __printAllProfile(lFETFeatureAlignmentInfo* info, FILE* out);
void __printAllProfile02(lFETFeatureAlignmentInfo* info, FILE* out);
void __printOutA(lFETFeatureAlignmentInfo* info, FILE* out);
void __printOut2D(lFETFeatureAlignmentInfo* info, FILE* out);

void __imagesFitToRef(lFETFeatureAlignmentImageInfo* images, lFETFeatureAlignmentImageInfo* ref, int imagenum, int refnum, int imagey, FILE* Out, double* corave, int mode);
lFETFeatureAlignmentFeature __calcImageCor(lFETFeatureAlignmentImageInfo i1, lFETFeatureAlignmentImageInfo i2, int y, int* a);
lFETFeatureAlignmentFeature __calcImageCor0(lFETFeatureAlignmentImageInfo i1, lFETFeatureAlignmentImageInfo i2, int i1n, int i2n, int y, int mode);
int __initmSelecter(lFETFeatureAlignment_initmSelecterInfo* in, int count, int timing);

void 
lFETOrientationSearchByFeatureAlignment(lFETOrientationSearchByFeatureAlignmentInfo in, int mode)
{
	int i,j,fmax,dust;
	int itmax,devmax,pmode;
	int outm, butm, initm;
	//char s[256];
	lFETFeatureAlignmentInfo faInfo;
	lFETFeatureAlignmentInfo faInfo1;
	lFETFeatureAlignmentInfo faInfo2;
	lFETFeatureAlignment_initmSelecterInfo initms;

	pmode = in.flagOutA*2 + in.flagOut2D;
	faInfo.OutLOG = in.OutLOG;
	__inRead(in.In, &faInfo, in.flagInType);  // SinogramList to featureArrays
	faInfo.ldn = in.ldn;
	faInfo.srl = in.srl;
	__calcMAXMIN(&faInfo);
	
	lFETFeatureAlignmentSphereInit(&(faInfo.sph),0);

	if(in.flagInA){
		outm = butm = 0; initm = initms.mode = 10;
		initms.InA = in.InA;
	}else{
		outm = in.mode/100;
		butm = (in.mode - outm*100)/10;
		initm = initms.mode = in.mode - outm*100 - butm*10;
	}
	initms.itmax = in.itmax; initms.mitmax = in.mitmax;
	initms.devmax = in.devmax; initms.mdevmax = in.mdevmax;
	initms.faInfo = &faInfo;
	if(outm != 0){
		fmax = __initmSelecter(&initms,0,1);
		for(i=0;i<fmax;i++){
			dust = __initmSelecter(&initms,i,2);
			__FeatureAlignmentIter(&faInfo,initms.mitmax,initms.mdevmax,butm);
            if(outm == 1) __FeatureAlignmentPrint(&faInfo,in.Out,in.OutA,in.Out2D,pmode);
            fprintf(in.OutLOG,"\n");
			if(outm == 2){
				if(i==0){ 
					initms.multi.max = faInfo.corave;
					for(j=0;j<faInfo.imagenum;j++) initms.multi.images[j] = faInfo.images[j];
				}else if(initms.multi.max < faInfo.corave){
					initms.multi.max = faInfo.corave;
					for(j=0;j<faInfo.imagenum;j++) initms.multi.images[j] = faInfo.images[j];
				}
			}
			lFETFeatureAlignmentSphereInit(&(faInfo.sph),1);
		}
	}
	if(outm != 1){
		dust = __initmSelecter(&initms,0,outm+3);
		__FeatureAlignmentIter(&faInfo,initms.itmax,initms.devmax,butm);
		__FeatureAlignmentPrint(&faInfo,in.Out,in.OutA,in.Out2D,pmode);
	}
		 
			
	
/*
	
fprintf(stderr,"before 1st if");	
	if((in.flagInA && in.mode<64) || in.mode < 32){
		if(in.flagInA){
			faInfo.srl = __inReadA(in.InA, &faInfo, 0);
			faInfo.srl *= 1.02;
			lFETFeatureAlignmentSphereFeatureSet(&faInfo);
			lFETFeatureAlignmentSphereDevide(&(faInfo.sph));
			lFETFeatureAlignmentSphereFeatureSet(&faInfo);
			lFETFeatureAlignmentSphereDevide(&(faInfo.sph));
			lFETFeatureAlignmentSphereFeatureSet(&faInfo);
			lFETFeatureAlignmentSphereDevide(&(faInfo.sph));
			faInfo.srl = in.srl;

			itmax = 5; devmax = 0;

			if(in.flagIn2){
				faInfo1 = faInfo;
				__inRead(in.In2, &faInfo2, in.flagInType);
				i=faInfo1.imagenum+faInfo2.imagenum;
				free(faInfo.images);
				faInfo.images = (lFETFeatureAlignmentImageInfo*)memoryAllocate((sizeof(lFETFeatureAlignmentImageInfo))*i,"in lFETOriSearchByFA__inRead");
				faInfo.imagenum = i;
				for(i=0;i<faInfo1.imagenum;i++){
					faInfo.images[i] = faInfo1.images[i];
				}for(j=0;j<faInfo2.imagenum;j++,i++){
					faInfo.images[i] = faInfo2.images[i];
					faInfo.images[i].interAngle = -10.0;
				}
			}
			//lFETFeatureAlignmentInitSet_IA(&faInfo);
		}else{
			if(in.mode == 0){
				lFETFeatureAlignmentInitSet_i2PCA(&faInfo);	
				itmax = 6; devmax = 2;
			}else if(in.mode == 1){
				lFETFeatureAlignmentInitSet_i1L(&faInfo);
				itmax = 8; devmax = 3;
			}else if(in.mode == 3){
				lFETFeatureAlignmentInitSet_i2LM(&faInfo);

			}else if(in.mode == 4){
				lFETFeatureAlignmentInitSet_i21LMLX(&faInfo);
				
			}else if(in.mode == 16){
				lFETFeatureAlignmentInitSet_random(&faInfo);
				lFETFeatureAlignmentSphereDevide(&(faInfo.sph));
				lFETFeatureAlignmentSphereDevide(&(faInfo.sph));
				itmax = 10; devmax = 0;
			}else{
				fprintf(stderr,"mode %d is not supported, default setting excecute\n",in.mode);
				lFETFeatureAlignmentInitSet_i2PCA(&faInfo);
				itmax = 4; devmax = 3;
			}
		}
		__FeatureAlignmentIter(&faInfo,itmax,devmax,0);
		__FeatureAlignmentPrint(&faInfo,in.Out,in.OutA,in.Out2D,pmode);
	}
	else if(in.mode < 64){
		fprintf(stdout,"before 2nd if\n");
		if(in.mode == 32){
			for(i=0;i<19;i++){
				lFETFeatureAlignmentInitSet_i2LXs(&faInfo,i);
				itmax = 3; devmax = 3;
				__FeatureAlignmentIter(&faInfo,itmax,devmax,0);
				__FeatureAlignmentPrint(&faInfo,in.Out,in.OutA,in.Out2D,pmode);
				lFETFeatureAlignmentSphereInit(&(faInfo.sph),1);
				fprintf(in.OutLOG,"\n");
			}
		}else if(in.mode == 33){
			itmax = 8; devmax = 3;
			for(i=0;i<10;i++){
				lFETFeatureAlignmentInitSet_i1Ls(&faInfo,i);
				__FeatureAlignmentIter(&faInfo,itmax,devmax,0);
				__FeatureAlignmentPrint(&faInfo,in.Out,in.OutA,in.Out2D,pmode);
				lFETFeatureAlignmentSphereInit(&(faInfo.sph),1);
				fprintf(in.OutLOG,"\n");
			}
		}else if(in.mode == 36){
			fprintf(stderr,"in if36\n");
			lFETFeatureAlignmentInitPreSet_i11LMLXs(&faInfo,&initInfoi11);
			itmax = 8; devmax = 2;
			for(i=0;i<10;i++){
				lFETFeatureAlignmentInitSet_i11LMLXs(&faInfo,&initInfoi11,i);
				__FeatureAlignmentIter(&faInfo,itmax,devmax,0);
				__FeatureAlignmentPrint(&faInfo,in.Out,in.OutA,in.Out2D,pmode);
				lFETFeatureAlignmentSphereInit(&(faInfo.sph),1);
				fprintf(in.OutLOG,"\n");
			}
		}else if(in.mode == 37){
			lFETFeatureAlignmentInitPreSet_i2LMsLXs(&faInfo,&initInfoi2LMsLXs);
			itmax = 3; devmax = 3;
			for(i=0;i<initInfoi2LMsLXs.num[0];i++){
				for(j=0;j<initInfoi2LMsLXs.num[1];j++){
					lFETFeatureAlignmentInitSet_i2LMsLXs(&faInfo,&initInfoi2LMsLXs,i,j);
					__FeatureAlignmentIter(&faInfo,itmax,devmax,0);
					__FeatureAlignmentPrint(&faInfo,in.Out,in.OutA,in.Out2D,pmode);
					lFETFeatureAlignmentSphereInit(&(faInfo.sph),1);
					fprintf(in.OutLOG,"\n");
				}
			}
		}
	}else{
		if(in.mode == 65){
			fprintf(stderr," in if65\n");
			if(in.flagInA){
				for(i=0;i<10;i++){
					faInfo.srl = __inReadA(in.InA, &faInfo, i);
					fprintf(stderr,"before preset\n");
					lFETFeatureAlignmentInitPreSet_i1Lss(&faInfo,&initInfoi1Lss,i);
				}
			}else{
				itmax = 8; devmax = 3;
				for(i=0;i<10;i++){
					lFETFeatureAlignmentInitSet_i1Ls(&faInfo,i);
					__FeatureAlignmentIter(&faInfo,itmax,devmax,0);
					lFETFeatureAlignmentInitPreSet_i1Lss(&faInfo,&initInfoi1Lss,i);
				}
			}
			fprintf(stderr,"before initset\n");
			lFETFeatureAlignmentInitSet_i1Lss(&faInfo,&initInfoi1Lss,0);
			itmax = 5; devmax = 3;
			__FeatureAlignmentIter(&faInfo,itmax,devmax,0);
			__FeatureAlignmentPrint(&faInfo,in.Out,in.OutA,in.Out2D,pmode);
		}
	}
	*/
}

int 
__initmSelecter(lFETFeatureAlignment_initmSelecterInfo* in, int count, int timing)
{
	int out,i,j,k;
	if(in->mode == 10){
		in->faInfo->srl = __inReadA(in->InA, in->faInfo, 0);
        in->faInfo->srl = 2;
        lFETFeatureAlignmentSphereFeatureSet(in->faInfo);
        lFETFeatureAlignmentSphereDevide(&(in->faInfo->sph));
        lFETFeatureAlignmentSphereFeatureSet(in->faInfo);
        lFETFeatureAlignmentSphereDevide(&(in->faInfo->sph));
        lFETFeatureAlignmentSphereFeatureSet(in->faInfo);
        lFETFeatureAlignmentSphereDevide(&(in->faInfo->sph));
		in->devmax -= 3; 
	}else if(in->mode == 0){
		if(timing != 3){
			fprintf(stderr,"mode error\n");
			exit(1);
		}else{
			lFETFeatureAlignmentInitSet_i2PCA(in->faInfo);
		}
	}else if(in->mode == 1){
		if(timing == 2 || timing == 3){
			lFETFeatureAlignmentInitSet_i1Ls(in->faInfo,count);
		}
	}else if(in->mode == 2){
		if(timing == 3){
            fprintf(stderr,"mode error\n");
			exit(1);
		}else if(timing == 2){
			lFETFeatureAlignmentInitSet_i2LXs(in->faInfo,count);
		}
	}else if(in->mode == 3){
		if(timing == 2 || timing == 3){
			lFETFeatureAlignmentInitSet_random(in->faInfo);
            lFETFeatureAlignmentSphereDevide(&(in->faInfo->sph));
            lFETFeatureAlignmentSphereDevide(&(in->faInfo->sph));
			if(count == 0 && timing == 3){
				in->devmax -= 2;
			}else if(count == 0 && timing == 2){
				in->mdevmax -= 2;
			}
		}
	}
	if(timing == 1){	
		in->multi.images = (lFETFeatureAlignmentImageInfo*)memoryAllocate(sizeof(lFETFeatureAlignmentImageInfo)*in->faInfo->imagenum,"in __initmSelecter");
	}else if(timing == 5){
		for(i=0; i<in->faInfo->imagenum; i++){
			in->faInfo->images[i] = in->multi.images[i];
		}
		for(i=0; i<in->devmax; i++){
			lFETFeatureAlignmentSphereFeatureSet(in->faInfo);
			lFETFeatureAlignmentSphereDevide(&(in->faInfo->sph));
		}
		in->devmax = 0;
		in->itmax -= in->mitmax;
	}

	
	out = 0;
	if(in->mode == 1) out=10;
	else if(in->mode == 2) out = 19;
	else if(in->mode == 3) out = 10;
	return out;
}

void
__FeatureAlignmentIter(lFETFeatureAlignmentInfo* info, int itmax, int devmax, int mode)
{
	int i,j;
	int refnum;
	lFETFeatureAlignmentImageInfo ref[SphereDevNum];
	for(i=0;i<itmax;i++){
		lFETFeatureAlignmentSphereFeatureSet(info);
		//__spherePrint(&faInfo,i,0);
		if(i<devmax) lFETFeatureAlignmentSphereDevide(&(info->sph));
		refnum = lFETFeatureAlignmentSphereRefGenerate(info,ref);
		__imagesFitToRef(info->images,ref,info->imagenum,refnum,info->imagey,info->OutLOG,&info->corave,0);
		__spherePrint(info,i,1);
		fprintf(stderr,"after %dth __imagesFitToRef\n",i);
		fprintf(stdout,"after %dth __imagesFitToRef\n",i);
	}
}

void
__FeatureAlignmentPrint(lFETFeatureAlignmentInfo* info, FILE* out, FILE* outA, FILE* out2D, int mode)
{
	int i;
	
	for(i=0;i<info->imagenum;i++)  __convCoordYOYS(&(info->images[i]));
	__printAllProfile02(info,out);
	if((mode&0x02)==2) __printOutA(info, outA);
	if((mode&0x01)==1) __printOut2D(info, out2D);
	
}

void
__convCoordYOYS(lFETFeatureAlignmentImageInfo* in)
{
	int i,j;
	Matrix3D ma;
	matrix3DParaTypeReal rot1,rot2,rot3;
	double norm[3], base[3], t[3];

	lFATFAcoordcpy2(&(in->norm),norm,1);
	lFATFAcoordcpy2(&(in->base),base,1);
	lFETFAvectorProduct1(norm,base,t);
	for(i=0;i<3;i++){
		ma[i][0] = base[i]; ma[i][1] = t[i]; ma[i][2] = norm[i]; ma[i][3] = 0.0;
	}
	matrix3DEulerAngleGetFromMatrix3D(ma,"YOYS",&rot1,&rot2,&rot3,0);

	in->yoys.x = ((double)rot1*180.0)/PI1; 
	in->yoys.y = ((double)rot2*180.0)/PI1; 
	in->yoys.z = ((double)rot3*180.0)/PI1;
}

void
__spherePrint(lFETFeatureAlignmentInfo* in, int a, int b)
{
	mrcImage out, temp;
	int i,ii,j,jj,k;
	int mnum,hmnum;
	double data;
	char s[32]="smap", ss[]="spheremap.mrc";
	lFETFeatureAlignmentSphereSquareInfo* sq;
	
	mrcFileRead(&temp,in->images[0].imagename,"",0);
	out.Header = temp.Header;
	out.HeaderN.x = out.HeaderN.y = 65;
	out.HeaderN.z = 4;
	mrcInit(&out,NULL);
	hmnum=in->sph.sq6[in->sph.curSwitch][0].center; mnum=hmnum*2+1;
	sq = in->sph.sq6[in->sph.curSwitch];
	for(k=0;k<4;k++){
	for(i=0;i<65;i++){ for(j=0;j<65;j++){
		mrcPixelDataSet(&out,i,j,k,-10.0, mrcPixelRePart);
	}}}
	for(k=0;k<4;k++){
		jj=0;
	for(i=hmnum;i>0;i--){
		ii=hmnum; 
		for(j=0;j<mnum;j++){
			if(k==0) data=sq[1].sq[j][i].fets.w;
			else if(k==1) data=sq[1].sq[j][i].fets.a;
			else if(k==2) data=sq[1].sq[j][i].fets.k;
			else data = (double)sq[1].sq[j][i].nnum;
			mrcPixelDataSet(&out,ii,jj,k,data, mrcPixelRePart);
			ii++;
		}
		jj++;
	}
	for(i=0;i<mnum;i++){ for(j=0;j<mnum;j++){
		if(k==0) data=sq[0].sq[j][i].fets.w;
		else if(k==1) data=sq[0].sq[j][i].fets.a;
		else if(k==2) data=sq[0].sq[j][i].fets.k;
		else data = (double)sq[0].sq[j][i].nnum;
		mrcPixelDataSet(&out,i+hmnum,j+hmnum,k,data, mrcPixelRePart);
	}}
	ii=0;
	for(i=hmnum;i>0;i--){ jj = hmnum; 
		for(j=0;j<mnum;j++){ 
			if(k==0) data=sq[2].sq[i][j].fets.w;
			else if(k==1) data=sq[2].sq[i][j].fets.a;
			else if(k==2) data=sq[2].sq[i][j].fets.k;
			else data = (double)sq[2].sq[i][j].nnum;
			mrcPixelDataSet(&out,ii,jj,k,data, mrcPixelRePart);
			jj++;
		}
		ii++;
	}
	ii = hmnum + mnum;
	for(i=1;i<=hmnum;i++){ jj = hmnum;
		for(j=0;j<mnum;j++){
			if(k==0) data=sq[5].sq[i][j].fets.w;
			else if(k==1) data=sq[5].sq[i][j].fets.a;
			else if(k==2) data=sq[5].sq[i][j].fets.k;
			else data = (double)sq[5].sq[i][j].nnum;
			mrcPixelDataSet(&out,ii,jj,k,data, mrcPixelRePart);
			jj++;
		}
		ii++;
	}
	jj = hmnum + mnum;
	for(i=1;i<=hmnum;i++){
		ii=hmnum; 
		for(j=0;j<mnum;j++){
			if(k==0) data=sq[4].sq[j][i].fets.w;
			else if(k==1) data=sq[4].sq[j][i].fets.a;
			else if(k==2) data=sq[4].sq[j][i].fets.k;
			else data = (double)sq[4].sq[j][i].nnum;
			mrcPixelDataSet(&out,ii,jj,k,data, mrcPixelRePart);
			ii++;
		}
		jj++;
	}
	}
	mrcStatDataSet(&out,0);
	if(a==0) s[4]='0'; else if(a==1) s[4]='1'; else if(a==2) s[4]='2'; else if(a==3) s[4]='3'; 
	else if(a==4) s[4]='4'; else if(a==5) s[4]='5'; else if(a==6) s[4]='6';
	else if(a==7) s[4]='7'; else if(a==8) s[4]='8'; else s[4]='9';
	if(b==0) s[6]='0'; else if(b==1) s[6]='1'; else if(b==2) s[6]='2'; else if(b==3) s[6]='3';
    else if(b==4) s[6]='4'; else if(b==5) s[6]='5'; else if(b==6) s[6]='6'; else s[6]='7';
	s[5]='-'; s[7]='\0';
	strcat(s,ss);
	mrcFileWrite(&out,s,"",0);
}

void
__imagesFitToRef(lFETFeatureAlignmentImageInfo* images, lFETFeatureAlignmentImageInfo* ref, int imagenum, int refnum, int imagey, FILE* Out, double* corave, int mode)
{
	int i,j,k;
	int tmaxref, tmaxn;
	double tmax, dr;
	lFETFeatureAlignmentFeature tans;
	double axis[3], point[3], ans[3];
	double tmaxave=0.0;
	//lFETFeatureAlignmentSpherePointInfo* cur;
	//lFETFeatureAlignmentCoord coo;
fprintf(stderr,"in fit");
	dr = -360.0/imagey;
	tmax = -10.0;
	for(i=0;i<imagenum;i++){
		fprintf(stderr,"in fit\n");
		for(j=0;j<refnum;j++){
			for(k=0;k<imagey;k++){
				tans = __calcImageCor0(images[i], ref[j], k, 0, imagey,2);
				tans.t = fabs(tans.w) * fabs(tans.a) * fabs(tans.k);
				if((tans.w<0.0)||(tans.a<0.0)||(tans.k<0.0)) tans.t *= -1;
				if(tans.t > tmax){
					tmax = tans.t;
					tmaxn = k;
					tmaxref = j;
				}
			}
		}
		fprintf(stdout,"%dth :refnum %d-%d\t%f\n",i,tmaxref,tmaxn,tmax);
		
		images[i].interAngle = tmax;
		images[i].norm = ref[tmaxref].norm;
		lFATFAcoordcpy2(&(ref[tmaxref].norm),axis,1);
		lFATFAcoordcpy2(&(ref[tmaxref].base),point,1);
		lFETpointRotation(axis,point,(double)tmaxn*dr,ans,0);
		lFETFAcoordcpy1(&(images[i].base),ans,1);
		ref[tmaxref].spt[0]->nnum++;
		ref[tmaxref].spt[1]->nnum++;
		/*
		coo = ref[tmaxref].norm;
		cur = __sphereSearchPoint(sph,coo);	cur->nnum++;
		coo.x *= -1; coo.y *= -1; coo.z *= -1;
		cur = __sphereSearchPoint(sph,coo); cur->nnum++;
		*/
		tmaxave += tmax;
		tmax = -10.0;
	}
	tmaxave /= (double)imagenum;
	//images[].lensum = tmaxave;
	fprintf(stdout,"tmax average = %f\n",tmaxave);
	*corave = tmaxave;
	fprintf(Out,"%f\t",tmaxave); 
}

lFETFeatureAlignmentFeature
__calcImageCor0(lFETFeatureAlignmentImageInfo i1, lFETFeatureAlignmentImageInfo i2, int i1n, int i2n, int y, int mode)
{
	int i,i1c,i2c;
	double data;
	lFETFeatureAlignmentFeature tmp[3];
	
	for(i=0;i<3;i++){ tmp[i].w = 0.0; tmp[i].a = 0.0; tmp[i].k = 0.0; }
	i1c = i1n; i2c = i2n;
	for(i=0;i<y;i++){
		
		tmp[0].w += i1.fets[i1c].w * i2.fets[i2c].w;
		tmp[0].a += i1.fets[i1c].a * i2.fets[i2c].a;
		tmp[0].k += i1.fets[i1c].k * i2.fets[i2c].k;
		
		tmp[1].w += pow(i1.fets[i1c].w,2); tmp[1].a += pow(i1.fets[i1c].a,2); tmp[1].k += pow(i1.fets[i1c].k,2);
		tmp[2].w += pow(i2.fets[i2c].w,2); tmp[2].a += pow(i2.fets[i2c].a,2); tmp[2].k += pow(i2.fets[i2c].k,2);
		
		/*data = i1.fets[i1c].w * i2.fets[i2c].w;
		tmp[0].w += pow(data,mode); 
		data = i1.fets[i1c].a * i2.fets[i2c].a;
		tmp[0].a += pow(data,mode); 
		data = i1.fets[i1c].k * i2.fets[i2c].k;
		tmp[0].k += pow(data,mode);
		
		tmp[1].w += pow(i1.fets[i1c].w,2*mode); 
		tmp[1].a += pow(i1.fets[i1c].a,2*mode); 
		tmp[1].k += pow(i1.fets[i1c].k,2*mode);
		tmp[2].w += pow(i2.fets[i2c].w,2*mode); 
		tmp[2].a += pow(i2.fets[i2c].a,2*mode); 
		tmp[2].k += pow(i2.fets[i2c].k,2*mode);
		*/
		i1c++; i2c++;
		if(i1c >= y) i1c -= y;
		if(i2c >= y) i2c -= y;
	}
	tmp[0].w /= pow((tmp[1].w * tmp[2].w),0.5);
	tmp[0].a /= pow((tmp[1].a * tmp[2].a),0.5);
	tmp[0].k /= pow((tmp[1].k * tmp[2].k),0.5);

	return tmp[0];	
}

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

double
lFETFAcalcCoordDistance(lFETFeatureAlignmentCoord a, lFETFeatureAlignmentCoord b)
{
	double dis;
	dis = pow((a.x-b.x),2) + pow((a.y-b.y),2) + pow((a.z-b.z),2);
	dis = pow(dis,0.5);
	return dis;
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

void 
__calcMAXMIN(lFETFeatureAlignmentInfo* info)
{
	int i,j,k,l;
	int n,y;
	int curmaxp, curminp;
	double curmax, curmin, cursum, llong, lshort, lmiddle, lmiddles, lsummin;
	double data;
	double lstep, sstep;
	double llim, mlim, slim, mlims;
	int curr[9];
	int* series; 
	

	n = info->imagenum; y = info->imagey;

	for(k=0; k<n; k++){
		curmax = curmin = info->images[k].fets[0].w;
		curmaxp = curminp = 0;
		for(j=1; j<(y/2); j++){
			data = info->images[k].fets[j].w;
			if(data > curmax){ curmax = data; curmaxp = j; }
			else if(data < curmin){ curmin = data; curminp = j; }
		}
		cursum = curmax + curmin;
		if(k==0){ llong = lmiddle = curmax;	lshort = lmiddles = curmin; lsummin = cursum; }
		if(curmax > llong) llong = curmax;
		else if(curmax < lmiddle) lmiddle = curmax;
		if(curmin < lshort) lshort = curmin;
		else if(curmin > lmiddles) lmiddles = curmin;
		if(cursum < lsummin) lsummin = cursum;
		
		data = info->images[k].fets[curmaxp].a;
		if(data < 0.0)	curmaxp += (y/2);
		if(abs(curmaxp-curminp) > y/4 && abs(curmaxp-curminp) < 3*y/4)	curminp += (y/2);
		data = (double)(curmaxp-curminp)*(360.0/y);
		if(data > 180.0) data -= 360;
		else if(data < -180.0) data += 360;
		
		info->images[k].interAngle = data;
		info->images[k].lenmax = curmax;
		info->images[k].lenmin = curmin;
		info->images[k].lensum = cursum;
		info->images[k].posmax = curmaxp;
		info->images[k].posmin = curminp;
		fprintf(stdout,"%s\t%f\n",info->images[k].imagename,curmax);
	}
	info->llong = llong;
	info->lshort = lshort;
	info->lmiddle = lmiddle;
	info->lmiddles = lmiddles;

	series=(int*)memoryAllocate(sizeof(int)*info->imagenum,"__calcMAXMIN");
	for(i=0;i<info->imagenum;i++) series[i]=i;
	for(i=0;i<info->imagenum-1;i++){
		data=info->images[i].lenmax; k=i;
		for(j=i+1;j<info->imagenum;j++){
			if(info->images[series[j]].lenmax > data){
				data = info->images[series[j]].lenmax;
				k=j;
			}
		}
		j=series[i];
		series[i]=series[k];
		series[k]=j;
	}
	for(i=0; i<info->imagenum;i++) info->images[series[i]].flagLX = i;

	// classification
	//llim = info->images[series[20]].lenmax; 
	for(k=0; k<n; k++){
		if(lsummin == info->images[k].lensum) info->smallImage = k;
		if(llong == info->images[k].lenmax) info->seedImage = k;
		/*if(info->images[k].lenmax > llim) info->images[k].flagLX = 1;
		else info->images[k].flagLX = 0;*/
	}
	
}

double
__inReadA(FILE* in, lFETFeatureAlignmentInfo* out, int mode)
{
	int i,j,k;
	char s[512];
	double ave=0.0,max;
	double* ser;
	fseek(in, 0L, SEEK_SET);
	i=0;
	ser=(double*)memoryAllocate(sizeof(double)*out->imagenum,"in __inReadA");
	if(mode > 0){
		for(i=0; i < (mode * out->imagenum); i++) stringGetFromFile(s,"",in,stdout,1);
	}
	for(i=0;i<out->imagenum;i++){
	//while(NULL!=stringGetFromFile(s,"",in,stdout,1)){
		stringGetFromFile(s,"",in,stdout,1);
		out->images[i].norm.x = (double)stringGetNthRealData(s, 1, " ,\t");
		out->images[i].norm.y = (double)stringGetNthRealData(s, 2, " ,\t");
		out->images[i].norm.z = (double)stringGetNthRealData(s, 3, " ,\t");
		out->images[i].base.x = (double)stringGetNthRealData(s, 4, " ,\t");
		out->images[i].base.y = (double)stringGetNthRealData(s, 5, " ,\t");
		out->images[i].base.z = (double)stringGetNthRealData(s, 6, " ,\t");
		if(mode == -1) out->images[i].interAngle = (double)stringGetNthRealData(s, 7, " ,\t");
		else out->images[i].interAngle = 0.8;
		ave += out->images[i].interAngle;
		ser[i]=out->images[i].interAngle;
	}
	for(i=0;i<5;i++){
		max = ser[i]; k = i;
		for(j=i+1;j<out->imagenum;j++){
			if(ser[j]>max){
				max=ser[j];
				k=j;
			}
		}
		max = ser[i];
		ser[i] = ser[k];
		ser[k] = max;
	}
	ave /= (double)i;
	return ser[4];
}

void
__inRead(FILE* in, lFETFeatureAlignmentInfo* out, int mode)
{
	int i,j,k,count;
	int y;
	char s[256];
	double data;
	mrcImage fetin,fetout;
	Array fetall;
	lmrcSinogramFETInfo fetinfo;

	count = 0;
	fseek(in, 0L, SEEK_SET);
	while(NULL!=stringGetFromFile(s,"",in,stdout,1)) count++;
	fseek(in, 0L, SEEK_SET);
	stringGetFromFile(s,"",in,stdout,1);
	//fprintf(stdout,"before 1st mrcRead\n");
	mrcFileRead(&fetin, s, "in lFETOriSearchByFA__inRead",0);
	//fprintf(stdout,"after 1st mrcRead\n");
	y = out->imagey = fetin.HeaderN.y;
	out->imagenum = count;
	fprintf(stdout,"count = %d\tsizeofStruct %d\n",count,sizeof(lFETFeatureAlignmentImageInfo));
	out->images = (lFETFeatureAlignmentImageInfo*)memoryAllocate((sizeof(lFETFeatureAlignmentImageInfo))*count,"in lFETOriSearchByFA__inRead");

	if(mode==0){ fetinfo.flagsm=1; fetinfo.sm=17; /*fetinfo.outmode = 0;*/ }
	
	fetall.dim = 2;
	fetall.n[0] = NumOfFeature;
	fetall.n[1] = out->imagey * out->imagenum;
	arrayInit(&fetall,"fetall in lFETOriSearchByFA__inRead");
	
	count = 0;
	fseek(in, 0L, SEEK_SET);
	while(NULL!=stringGetFromFile(s,"",in,stdout,1)){
		mrcFileRead(&fetin, s, "in lFETOriSearchByFA__inRead",0);
		strcpy(out->images[count].imagename, s);
		if(mode==0){
			//fprintf(stdout,"before sinogramFET");
			lmrcSinogramFET(&fetin,&fetout,fetinfo,0);
		}
		for(j=0; j<y; j++){
			for(i=0; i<NumOfFeature; i++){
				if(mode) mrcPixelDataGet(&fetin,i,j,0,&data, mrcPixelRePart, mrcPixelHowNearest);
				else mrcPixelDataGet(&fetout,i,j,0,&data, mrcPixelRePart, mrcPixelHowNearest);
				arrayDataSet2(fetall, i, j+count*y, (float)data);
			}
		}
		if(mode==0) mrcImageFree(&fetout,"in __mapchker");
		count++;
	}
	fprintf(stdout,"before arrayNorm\n");
	__arrayNorm(&fetall);
	fprintf(stdout,"after arrayNorm\n");

	count = 0;
	for(k=0; k<out->imagenum; k++){
		//fprintf(stdout,"before %d th paraset  ",k);
		//out->images[k].fets.dim = 2;
		//out->images[k].fets.n[0] = FET3num;
		//out->images[k].fets.n[1] = y;
		//fprintf(stdout,"before arrayInit  ");
		//arrayInit(&(out->images[k].fets), "in lFETOriSearchByFA__inRead");
		//fprintf(stdout,"after arrayInit  ");
		out->images[k].fets = (lFETFeatureAlignmentFeature*)memoryAllocate(sizeof(lFETFeatureAlignmentFeature)*y,"in lFETOriSearchByFA__inRead");
		for(j=0; j<y; j++){
			out->images[k].fets[j].a = arrayDataGet2(fetall, FETasymmetry, j+k*y);
			out->images[k].fets[j].k = arrayDataGet2(fetall, FETkur, j+k*y);
			//arrayDataSet2(out->images[k].fets, FET3asymmetry, j, arrayDataGet2(fetall, FETskewness, j+k*y));
			//arrayDataSet2(out->images[k].fets, FET3kur, j, arrayDataGet2(fetall, FETkurtosis, j+k*y));
			data = (double)arrayDataGet2(fetall, FETwidth, j+k*y);
			//data -= (double)arrayDataGet2(fetall, FETACFkurtosis, j+k*y);
			//data += (double)arrayDataGet2(fetall, FETACFaverage, j+k*y);
			//data += (double)arrayDataGet2(fetall, FETvariance, j+k*y);
			//data = (double)arrayDataGet2(fetall, FETlength, j+k*y);
			//data /= 4.0;
			out->images[count].fets[j].w = data*-1;
			//arrayDataSet2(out->images[count].fets, FET3width, j, (float)data);
		}
		//fprintf(stdout,"after arrayCopy  \n");
		count++;
		//fprintf(stdout,"after arrayCopy  \n");
	}	
	fprintf(stdout,"function __inRead finished\n");

}

void 
__arrayNorm(Array* in)
{
	int i,j,k;
	double data,ave,sd;

	for(i=0; i<in->n[0]; i++){
		ave = sd = 0;
		for(j=0; j<in->n[1]; j++){
			ave += arrayDataGet2(*in, i, j);
		}
		ave /= in->n[1];
		for(j=0; j<in->n[1]; j++){
			data = (double)arrayDataGet2(*in, i, j);
			sd += pow((data-ave),2);
		}
		sd /= in->n[1];
		sd = pow(sd,0.5);
		for(j=0; j<in->n[1]; j++){
			data = (double)arrayDataGet2(*in, i, j);
			data -= ave;
			if(sd > 0.00001) data /= sd;
			arrayDataSet2(*in, i, j, (float)data);
		}
	}
}

/*void
__printAllProfile01(lFETFeatureAlignmentInfo* in, FILE* out)
{
	int i,j,k;
	int curr[9];
	int max, min;

	for(i=0; i<9; i++){ // groups loop
		curr[i] = in->groups[i];
		max = in->images[curr[i]].group.max; min = in->images[curr[i]].group.min;
		fprintf(out,"\n\ngroup %d :\tmax %d\tmin %d\n",i,max,min);
		for(;curr[i] != -1;){
			fprintf(out,"%s\n",in->images[curr[i]].imagename);
			fprintf(out,"posmax %d\tlenmax %f\tposmin %d\tlenmin %f\tangle %f\n",in->images[curr[i]].posmax,in->images[curr[i]].lenmax,in->images[curr[i]].posmin,in->images[curr[i]].lenmin,in->images[curr[i]].interAngle);
			curr[i] = in->images[curr[i]].next;
		}
	}
}*/

void
__printOutA(lFETFeatureAlignmentInfo* in, FILE* out)
{
	int i;
	for(i=0;i<in->imagenum;i++){
		fprintf(out,"%5.2f\t%5.2f\t%5.2f\t%5.2f\t%5.2f\t%5.2f\n",
				in->images[i].norm.x,in->images[i].norm.y,in->images[i].norm.z,
				in->images[i].base.x,in->images[i].base.y,in->images[i].base.z);
	}
}

void
__printOut2D(lFETFeatureAlignmentInfo* in, FILE* out)
{
	int i;
	for(i=0;i<in->imagenum;i++){
		fprintf(out,"-EulerMode YOYS -Rot1 %4.1f %4.1f 1 -Rot2 %4.1f %4.1f 1 -Rot3 %4.1f %4.1f 1\n",
				in->images[i].yoys.x,in->images[i].yoys.x,
				in->images[i].yoys.y,in->images[i].yoys.y,
				in->images[i].yoys.z,in->images[i].yoys.z);
	}			
}

void
__printAllProfile02(lFETFeatureAlignmentInfo* in, FILE* out)
{
	int i,j;
	for(i=0;i<in->imagenum;i++){
		fprintf(out,"%s\tYOYS\t%f\t%f\t%f\t%f\n",
				in->images[i].imagename,
				in->images[i].yoys.x, in->images[i].yoys.y, in->images[i].yoys.z,
				in->images[i].interAngle);
	}
}
