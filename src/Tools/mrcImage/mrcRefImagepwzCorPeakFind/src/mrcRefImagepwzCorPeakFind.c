/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% mrcRefImagepwzCorPeakFind ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : mrcRefImagepwzCorPeakFind
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%mrcRefImagepwzCorPeakFind ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"
#undef DEBUG
#include "genUtil.h"
#include "mrcImage.h"
#include "mrcRefUtil.h"
#include "mrcImagefuncmin.h"

/* typedef */
typedef struct {
  mrcImage image;
  double sy;
  double ey;
  double ysize;
} lmrcpwzCorrelation;

/* prototype */
void lmrcpwzTemplateCorrelation(lmrcpwzCorrelation* out,mrcImage* in2 ,mrcImage* in,lmrcpwzCorrelation* template ,int sy, int ey ,int mode);
void lmrcRefImagepwzCorPeakFind(mrcImage* out ,double* maxx ,double* maxy ,double* maxdata ,mrcImage* in ,int N ,int dN ,double dp ,double dz ,int length ,int div ,int mode );
void lmrcMakepwzCortemplate(lmrcpwzCorrelation* out ,int N ,double dp ,double dz ,mrcpwzCorHeader* header ,mrcImage* in ,int mode);
void lmrcImageMaxFind(mrcImageParaTypeRealCoord* maxpos,double* maxdata,mrcImage* in);
void  lmrcRefImagepwzRefPeakMake(double* refmaxx ,double* refmaxy ,mrcImage* template , mrcImageParaTypeRealCoord maxpos ,int N);
double llmrcRefImagepwzCorPeakFind(double* maxx ,double* maxy ,double* maxdata ,mrcImage* in ,double* refmaxx ,double* refmaxy ,int N ,int mode);
void lmrcRefImagepwzCorPeakDisp(mrcImage* out ,double* maxx ,double* maxy ,double* maxdata ,int N ,mrcImage* in);
void lmrcRefImagepwzCorPeak2to1(double* maxx,double* maxy,double *maxdata,double** refmaxx,double** refmaxy,double** refmaxdata,int dN,int N ,int tN ,int mode);
void lmrcRefImagepwzCorPeak2to1MaxFind(double* maxx,double* maxy,double* maxdata,double** refmaxx,double** refmaxy,double** refmaxdata,int dN,int N,int tN ,int n,int m, int mode);
void lmrcRefImagepwzCorSmoothing(mrcImage* out ,mrcImage* in ,int N ,double dp ,double dz ,int mode);
void lmrcRefImagepwzCorPeakDistance(double* maxdx, double* maxdy, double* maxx, double* maxy,int N,int tN ,mrcImage* template ,double* maxxorg ,double* maxyorg);

void
main(int argc, char* argv[]) 
{
	long status;
	mrcRefImagepwzCorPeakFindInfo info;
/* variables */
	mrcImage in;
	mrcImage out;
	double* maxx;
	double* maxy;
	double* maxdata;

/* input patameters ,file open */
	init0(&info);
	argCheck(&info, argc, argv);
	init1(&info);

/* begin */
	mrcFileRead(&in ,info.In ,"in main" ,0);
	DEBUGPRINT("Read \n");
	if (info.mode2==1){
	  lmrcRefImagepwzCorSmoothing(&out,&in,info.N,info.dp,info.dz,info.mode);
	} else {
	  lmrcRefImagepwzCorPeakFind(&out ,maxx ,maxy ,maxdata ,&in ,info.N ,info.dN ,info.dp ,info.dz ,info.length ,info.div ,info.mode);
	}
	mrcFileWrite(&out ,info.Out ,"in main" ,0);
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
fprintf(stdout,"------ mode ------\n");
fprintf(stdout,"1:Use full length template and middle length template. Requires N and dN option\n");
fprintf(stdout,"------ Mode 2 -----\n");
fprintf(stdout,"0:peak find\n");
fprintf(stdout,"1:Smoothing pwzcorrelation file using template.\n");
}

void lmrcRefImagepwzCorSmoothing(mrcImage* out ,mrcImage* in ,int N ,double dp ,double dz ,int mode)
{
/* variables */
  lmrcpwzCorrelation template,tmp;
  mrcImage in2;
  mrcpwzCorHeader header;
/* begin */
  lmrcpwzCorHeaderGet(&header ,in);
  lmrcMakepwzCortemplate(&template ,N ,dp ,dz ,&header ,in ,mode);
  lmrcpwzTemplateCorrelation(&tmp,&in2,in,&template,header.sy ,header.ey,1);
  printf("ey:%f %f\n",header.ey,N * dz / in->HeaderLength.y); 
  header.ey -= N * dz / in->HeaderLength.y;
  out->Header=in->Header;
  mrcInit(out,NULL);
  lmrcpwzCorHeaderSet(out ,&header);
  lmrc3DZ1ImgPut(out,&tmp.image,1);
  mrcStatDataSet(out,0);

}

void lmrcRefImagepwzCorPeakFind(mrcImage* out ,double* maxx ,double* maxy ,double* maxdata ,mrcImage* in ,int N ,int dN ,double dp ,double dz ,int length ,int div ,int mode)
{
/* variables */
  int tN,n,i;
  double lmaxdata;
  mrcpwzCorHeader header;
  lmrcpwzCorrelation template,template2,tmp,tmp2;
  mrcImageParaTypeRealCoord lmaxpos;
  mrcImage in2,dum;
  double* refmaxx;
  double* refmaxy;
  double** refmaxx2;
  double** refmaxy2;
  double** refmaxdata;

/* begin */
  lmrcpwzCorHeaderGet(&header ,in);
  tN=floor( (header.ey -header.sy) *in->HeaderLength.y /dz +0.1) -1 ;
  if ( ( refmaxx = (double *)malloc(sizeof(double)*tN) ) == NULL ){
    fprintf(stderr ,"Enough memoly is not available.");
    exit(EXIT_FAILURE);
  }
  if ( ( refmaxy = (double *)malloc(sizeof(double)*tN) ) == NULL ){
    fprintf(stderr ,"Enough memoly is not available.");
    exit(EXIT_FAILURE);
  }
  if ( ( maxx = (double *)malloc(sizeof(double)*tN) ) == NULL ){
    fprintf(stderr ,"Enough memoly is not available.");
    exit(EXIT_FAILURE);
  }
  if ( ( maxy = (double *)malloc(sizeof(double)*tN) ) == NULL ){
    fprintf(stderr ,"Enough memoly is not available.");
    exit(EXIT_FAILURE);
  }
  if ( ( maxdata = (double *)malloc(sizeof(double)*tN) ) == NULL ){
    fprintf(stderr ,"Enough memoly is not available.");
    exit(EXIT_FAILURE);
  }
  
  if ( (refmaxx2 = (double **)malloc(sizeof(double*)*tN*div ) )== NULL ){
    fprintf(stderr ,"Enough memoly is not available.");
    exit(EXIT_FAILURE);
  }
  if ( (refmaxy2 = (double **)malloc(sizeof(double*)*tN*div ) )== NULL ){
    fprintf(stderr ,"Enough memoly is not available.");
    exit(EXIT_FAILURE);
  }
  if ( (refmaxdata = (double **)malloc(sizeof(double*)*tN*div ) )== NULL ){
    fprintf(stderr ,"Enough memoly is not available.");
    exit(EXIT_FAILURE);
  }
  for(n=0;n<tN*div;n++){
    if ( (refmaxx2[n] = (double *)malloc(sizeof(double)*N ) )== NULL ){
      fprintf(stderr ,"Enough memoly is not available.");
      exit(EXIT_FAILURE);
    }
    if ( (refmaxy2[n] = (double *)malloc(sizeof(double)*N ) )== NULL ){
      fprintf(stderr ,"Enough memoly is not available.");
      exit(EXIT_FAILURE);
    }
    if ( (refmaxdata[n] = (double *)malloc(sizeof(double)*N ) )== NULL ){
      fprintf(stderr ,"Enough memoly is not available.");
      exit(EXIT_FAILURE);
    }
  }
  lmrcMakepwzCortemplate(&template2 ,N/div ,dp ,dz ,&header ,in ,0);
  lmrcpwzTemplateCorrelation(&tmp,&in2,in,&template2,header.sy ,header.ey,1);
  lmrcMakepwzCortemplate(&template ,tN-N/div ,dp ,dz ,&header ,in ,0);
  lmrcpwzTemplateCorrelation(&tmp2,&dum,&tmp.image,&template,tmp.sy ,tmp.ey,2);
  lmrcImageMaxFind(&lmaxpos,&lmaxdata,&tmp2.image);     
  lmrcRefImagepwzRefPeakMake(refmaxx ,refmaxy ,&template.image ,lmaxpos ,tN-N/div);
  llmrcRefImagepwzCorPeakFind(maxx ,maxy ,maxdata ,&tmp.image ,refmaxx ,refmaxy ,tN-N/div ,0);      
  n=0;
  i=0;
  while(n<tN-N){
    lmaxpos.x=maxx[n];
    lmaxpos.y=maxy[n];
    lmaxpos.z=0;
    lmrcRefImagepwzRefPeakMake(refmaxx ,refmaxy,&template2.image ,lmaxpos ,N);
    llmrcRefImagepwzCorPeakFind(refmaxx2[i] ,refmaxy2[i] ,refmaxdata[i] ,&in2 ,refmaxx ,refmaxy ,N ,0);
    n += dN;
      i++;
  }
  lmrcRefImagepwzCorPeak2to1(maxx,maxy,maxdata,refmaxx2,refmaxy2,refmaxdata,dN,N,tN,0);
  lmrcRefImagepwzCorPeakDisp(out,maxx ,maxy ,maxdata,tN,&in2);     
}




void lmrcMakepwzCortemplate(lmrcpwzCorrelation* out ,int N ,double dp ,double dz ,mrcpwzCorHeader* header ,mrcImage* in ,int mode)
{
/* variables */
  double z,p,sp,sz;
  int oz,op,n;
  
  union uniheader{
    mrcRefHeader ref;
    mrcpwzCorHeader cor;
  };   
  union uniheader tmpheader;

/* initialization */
  out->image.Header = in->Header;
  out->image.HeaderN.z = 1;
  out->image.HeaderN.x = in->HeaderN.x -1 ;
  mrcInit(&out->image ,NULL);
  tmpheader.cor = *header;
  p=0;
  z=dz/2;
  n=0;
  out->sy = 0;
  out->ey = floor(N*dz / in->HeaderLength.y+0.5);
  DEBUGPRINT1("%f ",out->ey);
/* begin */
  if (mode==0){
    while (n < N){
      p=NormalDegree(p);
      op=lmrcRefGetzCordinate(p,header->iw ,header->ia,&(tmpheader.ref) ) - 1; 
      oz=floor(z / in->HeaderLength.y +0.5);
      mrcPixelDataSet(&out->image ,op ,oz ,0 ,1 ,mrcPixelRePart);
      n ++ ;
      z += dz ;
      p += dp ;
    } 
  } else {
    out->ey = 0;
    if (N%2) { 
      sp=0; sz=0; 
    } else { 
      sp=dp/2; sz=dz/2; 
    }
    for (n = -N/2 ;n <= (N-1)/2 ;n++) {
      DEBUGPRINT1("%n ",n);
      p = sp + dp*n;
      p = NormalDegree(p);
      z = sz + dz*n;
      op=lmrcRefGetzCordinate(p,header->iw ,header->ia,&(tmpheader.ref) ) - 1; 
      oz=floor(z / in->HeaderLength.y +0.5);
      mrcPixelDataSet(&out->image ,op ,oz ,0 ,1 ,mrcPixelRePart);
    }
  }
  mrcStatDataSet(&out->image,0);
}


void lmrcpwzTemplateCorrelation(lmrcpwzCorrelation* out,mrcImage* in2 ,mrcImage* in,lmrcpwzCorrelation* template ,int sy, int ey ,int mode)
{
/* variables */
  mrcImage tmp;
  mrcpwzCorHeader header;
  int x,y;
/* begin */
  if (mode/2){
    lmrcImageCorrelation(&out->image,in,&template->image,0);
    for (x=0;x<in->HeaderN.x ;x++){
      for (y=0 ;y<sy-(int)template->sy ;y++){
	mrcPixelDataSet(&out->image,x,y,0,in->HeaderAMin,mrcPixelRePart);
      }
      for (y=ey-(int)template->ey+1 ;y<in->HeaderN.y ;y++){
	mrcPixelDataSet(&out->image,x,y,0,in->HeaderAMin,mrcPixelRePart);
      }
    }	
    DEBUGPRINT4("mode2:%d %d %g %g \n",sy-(int)template->sy,ey-(int)template->ey+1,sy-(int)template->sy ,ey-(template->ey-template->ey) );
    DEBUGPRINT4("%d %g %d %g \n",sy,template->sy,ey,template->ey );

  }else{
    lmrc3DZ1ImgGet(&tmp ,in ,1);
    lmrcImageRectangleGet(in2 ,&tmp ,0 ,0 ,in->HeaderN.x-2 ,in->HeaderN.y-1 );
    if (mode){
      lmrcImageCorrelation(&out->image ,in2 ,&template->image ,0);
      for (x=0;x<in->HeaderN.x ;x++){
	for (y=0 ;y<sy-(int)template->sy ;y++){
	  mrcPixelDataSet(&out->image,x,y,0,in2->HeaderAMin,mrcPixelRePart);
	}
	for (y=ey-(int)template->ey+1 ;y <in->HeaderN.y ;y++){
	  mrcPixelDataSet(&out->image,x,y,0,in2->HeaderAMin,mrcPixelRePart);
	}
      }	
    } else {
      lmrcpwzCorHeaderGet(&header ,in);
      lmrcImageCorrelation(&tmp ,in2 ,&template->image ,0);
      for (x=0;x<in->HeaderN.x ;x++){
	for (y=0 ;y<sy-(int)template->sy ;y++){
	  mrcPixelDataSet(&tmp,x,y,0,in2->HeaderAMin,mrcPixelRePart);
	}
	for (y=ey-(int)template->ey+1 ;y <in->HeaderN.y ;y++){
	  mrcPixelDataSet(&tmp,x,y,0,in2->HeaderAMin,mrcPixelRePart);
	}
      }	
      out->image.Header = in->Header;
      out->image.HeaderN.x = in->HeaderN.x-1;
      mrcInit(&out->image,NULL);
      lmrc3DZ1ImgPut(&out->image,&tmp ,1);
      lmrcpwzCorHeaderSet(&out->image,&header);
    }
  }
  out->ey=ey-(template->ey-template->sy);
  out->sy=sy-(int)template->sy;
  mrcStatDataSet(&out->image,0);
}

void lmrcImageMaxFind(mrcImageParaTypeRealCoord* maxpos,double* maxdata,mrcImage* in)
{
/* variables */
  int x,y,z;
  double data;

/* begin */
  mrcPixelDataGet(in ,0 ,0 ,0 ,maxdata ,mrcPixelRePart , mrcPixelHowNearest);
  maxpos->x=maxpos->y=maxpos->z=0;
  for (x=0 ;x<in->HeaderN.x ;x++){
    for (y=0 ;y<in->HeaderN.y ;y++){
      for (z=0 ;z<in->HeaderN.z ;z++){
	mrcPixelDataGet(in ,x ,y ,z ,&data ,mrcPixelRePart , mrcPixelHowNearest);
	if (data > *maxdata ){
	  *maxdata = data;
	  maxpos->x=x;
	  maxpos->y=y;
	  maxpos->z=z;
	}
      }
    }
  }
}
	

void  lmrcRefImagepwzRefPeakMake(double* refmaxx ,double* refmaxy ,mrcImage* template , mrcImageParaTypeRealCoord maxpos ,int N)
{
  int x,y,z,n;
  double data;
  mrcImage tmp;

  n=0;
  lmrcImageShift(&tmp ,template ,maxpos ,mrcPixelHowNearest);
  for (z=0 ;z<tmp.HeaderN.z ;z++){
    for (y=0 ;y<tmp.HeaderN.y ;y++){
      for (x=0 ;x<tmp.HeaderN.x ;x++){
	mrcPixelDataGet(&tmp ,x ,y ,z ,&data ,mrcPixelRePart , mrcPixelHowNearest);
	if (data != 0.0 && n<N){
	  refmaxx[n]=x;
	  refmaxy[n]=y;
	  n++;
	}
      }
    }
  }
  mrcImageFree(&tmp,"");
}
 

double llmrcRefImagepwzCorPeakFind(double* maxx ,double* maxy ,double* maxdata ,mrcImage* in ,double* refmaxx ,double* refmaxy ,int N ,int mode)
{
/* variables */
  int n;

/* begin */
  for (n=0 ;n<N ;n++){
    mrcImagePeakFind(&maxx[n] ,&maxy[n] ,&maxdata[n] ,in ,refmaxx[n] ,refmaxy[n] ,0);
  }
  return(0);
}

void lmrcRefImagepwzCorPeakDisp(mrcImage* out ,double* maxx ,double* maxy ,double* maxdata ,int N ,mrcImage* in)
{
  int n;
  out->Header=in->Header;
  mrcInit(out,NULL);
  for (n=0 ;n<N ;n++){
    mrcPixelDataSet(out ,maxx[n] ,maxy[n] ,0 ,1 ,mrcPixelRePart);
    DEBUGPRINT2("%f %f   ",maxx[n] ,maxy[n]);
  }
  DEBUGPRINT("\n");
  mrcStatDataSet(out,0);
}



void lmrcRefImagepwzCorPeak2to1(double* maxx,double* maxy,double *maxdata,double** refmaxx,double** refmaxy,double** refmaxdata,int dN,int N ,int tN ,int mode)
{
  int n,m,on;
  
  if (mode==0){
    m=0;
    on=0;
    for(m=0;m<N;m++){
      lmrcRefImagepwzCorPeak2to1MaxFind(&maxx[on],&maxy[on],&maxdata[on],refmaxx,refmaxy,refmaxdata,dN,N,tN,0,m,mode);
      on++;
    }
    n=1;
    while(n<(tN-N)/dN){
      for(m=N-dN;m<N;m++){
	lmrcRefImagepwzCorPeak2to1MaxFind(&maxx[on],&maxy[on],&maxdata[on],refmaxx,refmaxy,refmaxdata,dN,N,(tN-N)/dN,n,m,mode);    
	on++;
      }
      n++;
    }
  } else if (mode==1){
    for(on=0; on<N/2; on++){
      maxx[on]=refmaxx[0][on];
      maxy[on]=refmaxy[0][on];
      maxdata[on]=refmaxdata[0][on];
    }
    for (n=0 ; n <tN-N  ;n++){
      on++;
      maxx[on]=refmaxx[n][on-n];
      maxy[on]=refmaxy[n][on-n];
      maxdata[on]=refmaxdata[n][on-n];
    }
    for (on=tN-N+N/2 ;on<tN-1 ;on++){
      maxx[on]=refmaxx[tN-N-1][on-(tN-N)];
      maxy[on]=refmaxy[tN-N-1][on-(tN-N)];
      maxdata[on]=refmaxdata[tN-N-1][on-(tN-N)];      
    }
    for (n=0 ;n <tN-1 ;n++){
      fprintf(stdout, "%f %f %f\n",maxx[n],maxy[n],maxdata[n]);
    }
    for (n=0 ;n< tN-N ;n++){
      for (m=0 ;m<N ;m++){
	fprintf(stdout,"%d %d %f \t", n,m,refmaxx[n][m]);
      }
    }
  }
}

void lmrcRefImagepwzCorPeak2to1MaxFind(double* maxx,double* maxy,double* maxdata,double** refmaxx,double** refmaxy,double** refmaxdata,int dN,int N,int tN ,int n,int m, int mode)
{
  int tmpn,tmpm,tmpmaxn,tmpmaxm;
  double tmpmax;
  tmpmaxn=n;
  tmpmaxm=m;
  tmpmax=refmaxdata[n][m];
  tmpn=n+1;
  tmpm=m-dN;
  DEBUGPRINT3("%d %d %g\n",n,m,refmaxdata[n][m]);
  while(tmpn<tN && tmpm>=0 ){
    if (refmaxdata[tmpn][tmpm] >tmpmax){
      tmpmax=refmaxdata[tmpn][tmpm];
      tmpmaxn=tmpn;
      tmpmaxm=tmpm;
    }
    tmpn++;
    tmpm -= dN;
  }
  *maxx=refmaxx[tmpmaxn][tmpmaxm];
  *maxy=refmaxy[tmpmaxn][tmpmaxm];
  *maxdata=tmpmax;
}

void lmrcRefImagepwzCorPeakDistance(double* maxdx, double* maxdy, double* maxx, double* maxy,int N,int tN ,mrcImage* template, double* maxxorg, double* maxyorg)
{
  double** refmaxx;
  double** refmaxy;
  int n,m;
  mrcImageParaTypeRealCoord lmaxpos;

  if ( (refmaxx = (double **)malloc(sizeof(double*)*tN ) )== NULL ){
    fprintf(stderr ,"Enough memoly is not available.");
    exit(EXIT_FAILURE);
  }
  if ( (refmaxy = (double **)malloc(sizeof(double*)*tN ) )== NULL ){
    fprintf(stderr ,"Enough memoly is not available.");
    exit(EXIT_FAILURE);
  }
  
  for(n=0; n<tN; n++){
    if ( (refmaxx[n] = (double *)malloc(sizeof(double)*N ) )== NULL ){
	fprintf(stderr ,"Enough memoly is not available.");
	exit(EXIT_FAILURE);
    }
    if ( (refmaxy[n] = (double *)malloc(sizeof(double)*N ) )== NULL ){
	fprintf(stderr ,"Enough memoly is not available.");
	exit(EXIT_FAILURE);
    }
  }
  
  fprintf(stderr,"allocate ");
  for (n=0;n<tN-N;n++){
    lmaxpos.x=maxxorg[n];
    lmaxpos.y=maxyorg[n];
    lmaxpos.z=0;
    lmrcRefImagepwzRefPeakMake(refmaxx[n] ,refmaxy[n] ,template, lmaxpos ,N);   
  }
  
  for (n=0 ;n<N/2 ;n++){
    maxdx[n]=maxx[n]-refmaxx[0][n];
    maxdy[n]=maxy[n]-refmaxy[0][n];
    fprintf(stdout,"%f %f %f %f %f %f \n",maxx[n],maxy[n],maxdx[n],maxdy[n],refmaxx[0][n],refmaxy[0][n]);
  }
  
  for (m=0 ;m<tN-N ;m++){
    n++;
    maxdx[n]=maxx[n]-refmaxx[m][n-m];
    maxdy[n]=maxy[n]-refmaxy[m][n-m];
    fprintf(stdout,"%f %f %f %f %f %f \n",maxx[n],maxy[n],maxdx[n],maxdy[n],refmaxx[m][n-m],refmaxy[m][n-m]);
  }
  
  for (n=tN-N+N/2+1 ;n<tN-1 ;n++){
    maxdx[n]=maxx[n]-refmaxx[tN-N-1][n-(tN-N-1)];
    maxdy[n]=maxy[n]-refmaxy[tN-N-1][n-(tN-N-1)];
    fprintf(stdout,"%f %f %f %f %f %f \n",maxx[n],maxy[n],maxdx[n],maxdy[n],refmaxx[tN-N-1][n-(tN-N-1)],refmaxy[tN-N-1][n-(tN-N-1)]);
  }
  
  
}





