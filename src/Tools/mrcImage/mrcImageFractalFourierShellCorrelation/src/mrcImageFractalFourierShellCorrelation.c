/*
# mrcImageFractalFourierShellCorrelation : $Revision$ $Date$ Created
# by $Author$ Usage : mrcImageFractalFourierShellCorrelation Attention
# $Loccker$ $State$ #
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"

#define DEBUG
/*#define DEBUG2*/
#include "genUtil.h"
#include "mrcImage.h"
#include "lmrcImageFourierShellCorrelation.h"
#include "Memory.h"

typedef struct lmrcImageFractalFourierShellCorrelationInfo {
  double Threshold;
  double stepx;
  double stepy;
  double stepz;
  double scaling;
  double maxN;
  int getMode;
  char* Log;
  double xmin;
  double ymin;
  double zmin;
  double xmax;
  double ymax;
  double zmax;
  double densityThreshold;
} lmrcImageFractalFourierShellCorrelationInfo;

typedef struct coordinate{
    int x;
    int y;
    int z;
}coordinate;

typedef struct coordinate2{
    double x;
    double y;
    double z;
}coordinate2;

typedef struct range{
  coordinate from;
  coordinate to;
} range;


/*
typedef enum lmrcImageFractalFourierShellCorrelationMode {
  a=0,
  b=1
} lmrcImageFractalFourierShellCorrelationMode;
*/


extern void lmrcImageFractalFourierShellCorrelation(mrcImage* out, mrcImage* in, mrcImage* ref, lmrcImageFractalFourierShellCorrelationInfo linfo, int mode);

void initLinfo(lmrcImageFractalFourierShellCorrelationInfo* linfo,mrcImageFractalFourierShellCorrelationInfo info);
void lcorrelationGet(double** correlation,int* max,mrcImage* in,mrcImage* ref,lmrcImageFourierShellCorrelationInfo* llinfo);
void linitialResolutionGet(double* initialResolution, double* correlation, mrcImage* in, mrcImage* ref, int max, lmrcImageFractalFourierShellCorrelationInfo linfo, lmrcImageFourierShellCorrelationInfo llinfo);
void linitialPartHeaderNGet(mrcImage* partIn, mrcImage* partRef, double initialResolution);
void lpartOffset(mrcImage* partIn, mrcImage* partRef, mrcImage* in, mrcImage* ref);
void lpartOffset2(mrcImage* partIn,mrcImage* partRef,mrcImage* in,mrcImage* ref,lmrcImageFractalFourierShellCorrelationInfo linfo,coordinate2* ratioPartInHeaderNtomaxN,coordinate2* ratioPartRefHeaderNtomaxN,coordinate* ratioPartInHeaderNtomaxNFlag,coordinate* ratioPartRefHeaderNtomaxNFlag);
void lWeightGet(double* Weight,mrcImage* partIn,mrcImageParaTypeReal dstx,mrcImageParaTypeReal dsty,mrcImageParaTypeReal dstz);
void lpartReset(mrcImage* partIn,mrcImage* partRef,mrcImage* in, mrcImage* ref,coordinate2 ratioPartInHeaderNtomaxN,coordinate2 ratioPartRefHeaderNtomaxN,coordinate ratioPartInHeaderNtomaxNFlag,coordinate ratioPartREfHeaderNtomaxFlag);
int lcorrelationCheck(range* searchRange,double correlation2,double correlation3,mrcImage* partIn,mrcImage* partRef,mrcImage* in,lmrcImageFractalFourierShellCorrelationInfo linfo,int* extractFlag);
void loutHeaderSet(mrcImage* out,mrcImage* in,lmrcImageFractalFourierShellCorrelationInfo linfo);

int
main(int argc, char* argv[]) 
{
  mrcImageFractalFourierShellCorrelationInfo info;
  lmrcImageFractalFourierShellCorrelationInfo linfo;
  mrcImage in;
  mrcImage ref;
  mrcImage out;

  init0(&info);
  argCheck(&info, argc, argv);
  init1(&info);

  DEBUGPRINT("Program Start\n");

  initLinfo(&linfo,info);
  
  mrcFileRead(&in, info.In, "in main", 0);
  mrcFileRead(&ref, info.Ref, "in main", 0);
  lmrcImageFractalFourierShellCorrelation(&out, &in, &ref, linfo, info.mode);

  mrcFileWrite(&out, info.Out, "in main", 0); 
  exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
  fprintf(stderr, "----- Additional Usage -----\n");
}

void
lmrcImageFractalFourierShellCorrelation(mrcImage* out, mrcImage* in, mrcImage* ref, lmrcImageFractalFourierShellCorrelationInfo linfo, int mode)
{
  mrcImageParaTypeReal srcx, srcy, srcz;
  mrcImageParaTypeReal dstx, dsty, dstz;
  mrcImageParaTypeReal x, y, z;
  double* correlation=NULL;
  int max,extractFlag,breakFlag,criterionFlag; 
  lmrcImageFourierShellCorrelationInfo llinfo;
  mrcImage partIn,partRef;
  double resolution,Weight,dataIn,dataRef;
  range searchRange;
  double initialResolution;
  coordinate ratioPartInHeaderNtomaxNFlag,ratioPartRefHeaderNtomaxNFlag;
  coordinate2 ratioPartInHeaderNtomaxN,ratioPartRefHeaderNtomaxN;
  FILE* fp;

  
  out->Header = in->Header;
  mrcInit(out, NULL);

  partIn.Header=in->Header;
  mrcInit(&partIn,NULL);
  
  partRef.Header=ref->Header;
  mrcInit(&partRef,NULL);

  if(1==linfo.stepx && 1==linfo.stepy && 1==linfo.stepz){
    
  }else{
    loutHeaderSet(out,in,linfo);
  }
  
  /*initial resolution*/
  lcorrelationGet(&correlation,&max,in,ref,&llinfo);
  linitialResolutionGet(&initialResolution,correlation,in,ref,max,linfo,llinfo);
  DEBUGPRINT3("initial resolution=%f\n correlation[2]=%f correlation[3]=%f",initialResolution,correlation[2],correlation[3]);
    
  /*initial partHeaderN*/DEBUGPRINT("2");
  linitialPartHeaderNGet(&partIn,&partRef,initialResolution);
  DEBUGPRINT("3");

  if(NULL!=linfo.Log){
    if(NULL == (fp=fopen(linfo.Log,"w"))){
      fprintf(stderr,"Can't open the file.\n");
    }
  } else {
    fp = NULL; 
  } 
  
  if(0==linfo.xmax)linfo.xmax=in->HeaderN.x;
  if(0==linfo.ymax)linfo.ymax=in->HeaderN.y;
  if(0==linfo.zmax)linfo.zmax=in->HeaderN.z;
  
  /* Fractal Fourier Shell Correlation at (x, y, z) */
  for(x=0; x<in->HeaderN.x; x += linfo.stepx) {
  for(y=0; y<in->HeaderN.y; y += linfo.stepy) {
  for(z=0; z<in->HeaderN.z; z += linfo.stepz) {
	searchRange.from.x=0;
	searchRange.from.y=0;
	searchRange.from.z=0;
	extractFlag=0;
	while(1) {
	  if(x<linfo.xmin || linfo.xmax<x || y<linfo.ymin || linfo.ymax<y || z<linfo.zmin || linfo.zmax<z){
	    criterionFlag=1;
	    break;
	  } else {
	    criterionFlag=0;
	  }
	 
	  lpartOffset(&partIn, &partRef, in, ref);
	  	  
	  DEBUGPRINT3("partIn.HeaderN.x=%d partIn.HeaderN.y=%d partIn.HeaderN.z=%d\n", \
	  	partIn.HeaderN.x,partIn.HeaderN.y,partIn.HeaderN.z);
	  DEBUGPRINT3("partIn.HeaderLength.x=%f partIn.HeaderLength.y=%f partIn.HeaderLength.z=%f\n", \
	  	partIn.HeaderLength.x,partIn.HeaderLength.y,partIn.HeaderLength.z);
	  
	  lpartOffset2(&partIn,&partRef,in,ref,linfo,&ratioPartInHeaderNtomaxN,&ratioPartRefHeaderNtomaxN,\
		       &ratioPartInHeaderNtomaxNFlag,&ratioPartRefHeaderNtomaxNFlag);

	  for(dstx=0; dstx<partIn.HeaderN.x; dstx++) {
	  for(dsty=0; dsty<partIn.HeaderN.y; dsty++) {
	  for(dstz=0; dstz<partIn.HeaderN.z; dstz++) {
	 
	    DEBUG2PRINT3("partIn.HeaderN.x=%d partIn.HeaderN.y=%d partIn.HeaderN.z=%d\n", \
				partIn.HeaderN.x,partIn.HeaderN.y,partIn.HeaderN.z);
				
	    srcx = x + (dstx-partIn.HeaderN.x/2)*ratioPartInHeaderNtomaxN.x;
	    srcy = y + (dsty-partIn.HeaderN.y/2)*ratioPartInHeaderNtomaxN.y;
	    srcz = z + (dstz-partIn.HeaderN.z/2)*ratioPartInHeaderNtomaxN.z;
	    /*if(1==flag2.x){
	      DEBUGPRINT3("srcx=%f srcy=%f srcz=%f\n",srcx,srcy,srcz);
	      getchar();
	      }*/
		
	    mrcPixelDataGet(in,  srcx, srcy, srcz, &dataIn,  mrcPixelRePart, linfo.getMode);
	    mrcPixelDataGet(ref, srcx, srcy, srcz, &dataRef, mrcPixelRePart, linfo.getMode);
	    

	    if(0!=linfo.densityThreshold){
	      if(0==(int)(dstx-partIn.HeaderN.x/2+0.5) && 0==(int)(dsty-partIn.HeaderN.y/2+0.5)\
		 && 0==(int)(dstz-partIn.HeaderN.z/2+0.5)){
		DEBUGPRINT3("dstx=%f dsty=%f dstz=%f\n",dstx,dsty,dstz);
		DEBUGPRINT3("dataIn=%f dataRef=%f (dataIn+dataRef)/2=%f\n",dataIn,dataRef,(dataIn+dataRef)/2);
		if((dataIn+dataRef)/2<linfo.densityThreshold){
		  criterionFlag=1;
		  break;
		}
	      }
	    }
	    DEBUG2PRINT3("dstx=%f dsty=%f dstz=%f\n",dstx,dsty,dstz);     
	    
	    lWeightGet(&Weight,&partIn,dstx,dsty,dstz);
	    
	    DEBUG2PRINT1("Weight=%f\n",Weight);
	    
	    mrcPixelDataSet(&partIn,  dstx, dsty, dstz, Weight*dataIn, mrcPixelRePart);
	    mrcPixelDataSet(&partRef, dstx, dsty, dstz, Weight*dataRef, mrcPixelRePart);
	  }
	  if(1==criterionFlag)break;
	  }
	  if(1==criterionFlag)break;
	  }
	  
	  /*getchar();*/
	  /* Fourier Shell Correlation */
	  if(0==criterionFlag){
	    free(correlation);
	    lcorrelationGet(&correlation,&max,&partIn,&partRef,&llinfo);
	    /*if(1==flag2.x)getchar();*/
	    DEBUGPRINT3("x=%f y=%f z=%f\n",x,y,z);
	    DEBUGPRINT3("partIn.HeaderN.x=%d partIn.HeaderN.y=%d partIn.HeaderN.z=%d\n",partIn.HeaderN.x,partIn.HeaderN.y,partIn.HeaderN.z);
	    DEBUGPRINT3("partIn.HeaderLength.x=%f partIn.HeaderLength.y=%f partIn.HeaderLength.z=%f\n",partIn.HeaderLength.x,partIn.HeaderLength.y,partIn.HeaderLength.z);
	    DEBUGPRINT3("max=%d,correlation[2]=%f,correlation[3]=%f\n",max,correlation[2],correlation[3]);
	    DEBUGPRINT("---------------------------------\n");
	  }

	  lpartReset(&partIn, &partRef,in,ref,ratioPartInHeaderNtomaxN, ratioPartRefHeaderNtomaxN, ratioPartInHeaderNtomaxNFlag,ratioPartRefHeaderNtomaxNFlag);
	  
	  DEBUGPRINT3("partIn.HeaderN.x=%d partIn.HeaderN.y=%d partIn.HeaderN.z=%d\n",partIn.HeaderN.x,partIn.HeaderN.y,partIn.HeaderN.z);
	  DEBUGPRINT3("partIn.HeaderLength.x=%f partIn.HeaderLength.y=%f partIn.HeaderLength.z=%f\n",partIn.HeaderLength.x,partIn.HeaderLength.y,partIn.HeaderLength.z);
	  DEBUGPRINT("---------------------------------\n");
	  if(1==criterionFlag)break;
	  breakFlag=lcorrelationCheck(&searchRange,correlation[2],correlation[3],&partIn,&partRef,in,linfo,&extractFlag);
	  if(1==breakFlag)break;
	  
	  /*if(1==flag2.x)getchar();*/
	}
	
	if(1==criterionFlag)resolution=0;
	if(0==criterionFlag)resolution=2*llinfo.Delta;

	mrcPixelDataSet(out, x/linfo.stepx, y/linfo.stepy, z/linfo.stepz, resolution, mrcPixelRePart);
	DEBUGPRINT1("%d",out->HeaderN.x);/*getchar();*/
	if(NULL!=fp && 0==criterionFlag){
	  fprintf(fp,"x=%f y=%f z=%f correlation[2]=%f correlation[3]=%f resolution=%f 1/resolution=%f\n" \
		  ,x,y,z,correlation[2],correlation[3],resolution,1/resolution);
	  fflush(fp);
	}
	if(NULL!=fp && 1==criterionFlag){
	  fprintf(fp,"x=%f y=%f z=%f correlation[2]=nothing correlation[3]=nothing resolution=%f 1/resolution=nothing\n" \
		  ,x,y,z,resolution);
	  fflush(fp);
	}

	if(0==criterionFlag){
	  DEBUGPRINT6("x=%f y=%f z=%f correlation[2]=%f correlation[3]=%f resolution=%f\n",x,y,z,correlation[2],correlation[3],resolution);
	}	
	
	if(1==criterionFlag){
	  DEBUGPRINT4("x=%f y=%f z=%f correlation[2]=nothing correlation[3]=nothing resolution=%f 1/resolution=nothing\n" \
		  ,x,y,z,resolution);
	}
	DEBUGPRINT("---------------------------------------------\n");
	/*getchar();*/
	
	if(4==partIn.HeaderN.x && 4==partIn.HeaderN.y && 4==partIn.HeaderN.z){
	  linitialPartHeaderNGet(&partIn,&partRef,initialResolution);
	}

      }
    } 
  }
  if(NULL!=fp)fclose(fp);
}

void initLinfo(lmrcImageFractalFourierShellCorrelationInfo* linfo,  mrcImageFractalFourierShellCorrelationInfo info)
{
  linfo->Threshold = info.Threshold;
  linfo->stepx = info.stepx;
  linfo->stepy = info.stepy;
  linfo->stepz = info.stepz;
  linfo->scaling = info.scaling;
  linfo->maxN = info.maxN;
  linfo->getMode = info.getMode;
  linfo->Log = info.Log;
  linfo->xmin = info.xmin;
  linfo->ymin = info.ymin;
  linfo->zmin = info.zmin;
  linfo->xmax = info.xmax;
  linfo->ymax = info.ymax;
  linfo->zmax = info.zmax;
  linfo->densityThreshold = info.densityThreshold;
}

void lcorrelationGet(double** correlation,int* max,mrcImage* in,mrcImage* ref,lmrcImageFourierShellCorrelationInfo* llinfo)
{
  
  llinfo->Delta=1/(in->HeaderLength.x*in->HeaderN.x);
  *max=floor(sqrt(SQR(1/in->HeaderLength.x)+SQR(1/in->HeaderLength.y)+SQR(1/in->HeaderLength.z))/llinfo->Delta/2+0.5)+1;
  *correlation=(double*)memoryAllocate(sizeof(double)*(*max),"in linitialResolutionGet");
  lmrcImageFourierShellCorrelation(*correlation,in,ref,*llinfo,0,0);
}
 
void linitialResolutionGet(double* initialResolution, double* correlation, mrcImage* in, mrcImage* ref, int max, lmrcImageFractalFourierShellCorrelationInfo linfo, lmrcImageFourierShellCorrelationInfo llinfo)
{
  int i;

  for(i=2;i<max;i++){
    if(correlation[i]<linfo.Threshold){
      *initialResolution=1/((i-1)*llinfo.Delta);
      break;
    }
  }
  if(i==max)*initialResolution=1/((i-1)*llinfo.Delta);
 
}
     
void linitialPartHeaderNGet(mrcImage* partIn, mrcImage* partRef, double initialResolution){
  partIn->HeaderN.x = (int)(2*initialResolution/partIn->HeaderLength.x);
  partIn->HeaderN.y = (int)(2*initialResolution/partIn->HeaderLength.y);
  partIn->HeaderN.z = (int)(2*initialResolution/partIn->HeaderLength.z);
  
  partRef->HeaderN.x = (int)(2*initialResolution/partRef->HeaderLength.x);
  partRef->HeaderN.y = (int)(2*initialResolution/partRef->HeaderLength.y);
  partRef->HeaderN.z = (int)(2*initialResolution/partRef->HeaderLength.z);
}

void lpartOffset(mrcImage* partIn, mrcImage* partRef, mrcImage* in, mrcImage* ref){

  
  int partInHeaderNmax;

  /*if partN>inN then partN=inN*/
  if(partIn->HeaderN.x>in->HeaderN.x){
    partIn->HeaderN.x=in->HeaderN.x;
    partRef->HeaderN.x=ref->HeaderN.x;
  }
  
  if(partIn->HeaderN.y>in->HeaderN.y){
    partIn->HeaderN.y=in->HeaderN.y;
    partRef->HeaderN.y=ref->HeaderN.y;
  }

  if(partIn->HeaderN.z>in->HeaderN.z){
    partIn->HeaderN.z=in->HeaderN.z;
    partRef->HeaderN.z=ref->HeaderN.z;
  }
  
  /*partInHeaderNmax Seach*/
  partInHeaderNmax=partIn->HeaderN.x;
  if(partInHeaderNmax<partIn->HeaderN.y)partInHeaderNmax=partIn->HeaderN.y;
  if(partInHeaderNmax<partIn->HeaderN.z)partInHeaderNmax=partIn->HeaderN.z;
  
  if(partInHeaderNmax <= in->HeaderN.x  && partInHeaderNmax <= in->HeaderN.y && partInHeaderNmax <= in->HeaderN.z){
    partIn->HeaderN.x = partInHeaderNmax;
    partIn->HeaderN.y = partInHeaderNmax;
    partIn->HeaderN.z = partInHeaderNmax;
    partRef->HeaderN.x= partIn->HeaderN.x;
    partRef->HeaderN.y= partIn->HeaderN.y;
    partRef->HeaderN.z= partIn->HeaderN.z;
  }  
  
  if(partIn->HeaderN.x<4)partIn->HeaderN.x=4;
  if(partIn->HeaderN.y<4)partIn->HeaderN.y=4;
  if(partIn->HeaderN.z<4)partIn->HeaderN.z=4;
}

void lpartOffset2(mrcImage* partIn,mrcImage* partRef,mrcImage* in,mrcImage* ref,lmrcImageFractalFourierShellCorrelationInfo linfo,coordinate2* ratioPartInHeaderNtomaxN,coordinate2* ratioPartRefHeaderNtomaxN,coordinate* ratioPartInHeaderNtomaxNFlag,coordinate* ratioPartRefHeaderNtomaxNFlag){
  
  if(linfo.maxN<partIn->HeaderN.x){
    ratioPartInHeaderNtomaxN->x  = partIn->HeaderN.x/linfo.maxN;
    partIn->HeaderLength.x = in->HeaderLength.x*ratioPartInHeaderNtomaxN->x;
    partIn->HeaderN.x      = (int)linfo.maxN;
    ratioPartInHeaderNtomaxNFlag->x=1;
  } else {
    ratioPartInHeaderNtomaxN->x=1;
    ratioPartInHeaderNtomaxNFlag->x=0;
  }
	 
  if(linfo.maxN<partRef->HeaderN.x){
    ratioPartRefHeaderNtomaxN->x  = partRef->HeaderN.x/linfo.maxN;
    partRef->HeaderLength.x = ref->HeaderLength.x*ratioPartRefHeaderNtomaxN->x;
    partRef->HeaderN.x      = (int)linfo.maxN;
    ratioPartRefHeaderNtomaxNFlag->x=1;
  } else {
    ratioPartRefHeaderNtomaxN->x=1;
    ratioPartRefHeaderNtomaxNFlag->x=0;
  }
	  
  if(linfo.maxN<partIn->HeaderN.y){
    ratioPartInHeaderNtomaxN->y  = partIn->HeaderN.y/linfo.maxN;
    partIn->HeaderLength.y = in->HeaderLength.y*ratioPartInHeaderNtomaxN->y;
    partIn->HeaderN.y      = (int)linfo.maxN;
    ratioPartInHeaderNtomaxNFlag->y=1;
  } else {
    ratioPartInHeaderNtomaxN->y=1;
    ratioPartInHeaderNtomaxNFlag->y=0;
  }
  if(linfo.maxN<partRef->HeaderN.y){
    ratioPartRefHeaderNtomaxN->y  = partRef->HeaderN.y/linfo.maxN;
    partRef->HeaderLength.y = ref->HeaderLength.y*ratioPartRefHeaderNtomaxN->y;
    partRef->HeaderN.y      = (int)linfo.maxN;
    ratioPartRefHeaderNtomaxNFlag->y=1;
  } else {
    ratioPartRefHeaderNtomaxN->y=1;
    ratioPartRefHeaderNtomaxNFlag->y=0;
  }
  
  if(linfo.maxN<partIn->HeaderN.z){
    ratioPartInHeaderNtomaxN->z  = partIn->HeaderN.z/linfo.maxN;
    partIn->HeaderLength.z = in->HeaderLength.z*ratioPartInHeaderNtomaxN->z;
    partIn->HeaderN.z      = (int)linfo.maxN;
    ratioPartInHeaderNtomaxNFlag->z = 1;
  } else {
    ratioPartInHeaderNtomaxN->z=1;
    ratioPartInHeaderNtomaxNFlag->z = 0;
  }
	  
  if(linfo.maxN<partRef->HeaderN.z){
    ratioPartRefHeaderNtomaxN->z  = partRef->HeaderN.z/linfo.maxN;
    partRef->HeaderLength.z = ref->HeaderLength.z*ratioPartRefHeaderNtomaxN->z;
    partRef->HeaderN.z      = (int)linfo.maxN;
    ratioPartRefHeaderNtomaxNFlag->z = 1;
  } else {
    ratioPartRefHeaderNtomaxN->z=1;
    ratioPartRefHeaderNtomaxNFlag->z = 0;
  }
}

void lWeightGet(double* Weight,mrcImage* partIn,mrcImageParaTypeReal dstx,mrcImageParaTypeReal dsty,mrcImageParaTypeReal dstz){
  /* Weight */
  *Weight = 1.0;
  if(dstx/(partIn->HeaderN.x) < 0.2) {
    *Weight *= (1-cos((M_PI*dstx)/(0.2*partIn->HeaderN.x)))/2;
  }
  if(0.8 < dstx/partIn->HeaderN.x){
    *Weight *= (1-cos((M_PI*(partIn->HeaderN.x-dstx))/(0.2*partIn->HeaderN.x)))/2;
  }
  if(dsty/(partIn->HeaderN.y) < 0.2){
    *Weight *= (1-cos((M_PI*dsty)/(0.2*partIn->HeaderN.y)))/2;
  }
  if(0.8 < dsty/(partIn->HeaderN.y)){
    *Weight *= (1-cos((M_PI*(partIn->HeaderN.y-dsty))/(0.2*partIn->HeaderN.y)))/2;
  }
  if(dstz/(partIn->HeaderN.z) < 0.2){
    *Weight *= (1-cos((M_PI*dstz)/(0.2*partIn->HeaderN.z)))/2;
  }
  if(0.8 < dstz/(partIn->HeaderN.z)){
    *Weight *= (1-cos((M_PI*(partIn->HeaderN.z-dstz))/(0.2*partIn->HeaderN.z)))/2;
  }
}

void lpartReset(mrcImage* partIn,mrcImage* partRef,mrcImage* in, mrcImage* ref,coordinate2 ratioPartInHeaderNtomaxN,coordinate2 ratioPartRefHeaderNtomaxN,coordinate ratioPartInHeaderNtomaxNFlag,coordinate ratioPartRefHeaderNtomaxNFlag){
  if(1==ratioPartInHeaderNtomaxNFlag.x){
    partIn->HeaderLength.x=in->HeaderLength.x;
    partIn->HeaderN.x=(int)(partIn->HeaderN.x*ratioPartInHeaderNtomaxN.x+0.5);
    /*getchar();*/
  }
	  
  if(1==ratioPartRefHeaderNtomaxNFlag.x){
    partRef->HeaderLength.x=ref->HeaderLength.x;
    partRef->HeaderN.x=(int)(partRef->HeaderN.x*ratioPartRefHeaderNtomaxN.x+0.5);
  }
  
  if(1==ratioPartInHeaderNtomaxNFlag.y){
    partIn->HeaderLength.y=in->HeaderLength.y;
    partIn->HeaderN.y=(int)(partIn->HeaderN.y*ratioPartInHeaderNtomaxN.y+0.5);
  }
  if(1==ratioPartRefHeaderNtomaxNFlag.y){
    partRef->HeaderLength.y=ref->HeaderLength.y;
    partRef->HeaderN.y=(int)(partRef->HeaderN.y*ratioPartRefHeaderNtomaxN.y+0.5);
  }
  if(1==ratioPartInHeaderNtomaxNFlag.z){
    partIn->HeaderLength.z=in->HeaderLength.z;
    partIn->HeaderN.z=(int)(partIn->HeaderN.z*ratioPartInHeaderNtomaxN.z+0.5);
  }
  if(1==ratioPartRefHeaderNtomaxNFlag.z){
    partRef->HeaderLength.z=ref->HeaderLength.z;
    partRef->HeaderN.z=(int)(partRef->HeaderN.z*ratioPartRefHeaderNtomaxN.z+0.5);
  }
}

int lcorrelationCheck(range* searchRange,double correlation2,double correlation3,mrcImage* partIn,mrcImage* partRef,mrcImage* in,lmrcImageFractalFourierShellCorrelationInfo linfo,int* extractFlag){
  
  int breakFlag;
  static coordinate prePartInHeaderN={0,0,0};
  
  if(4==partIn->HeaderN.x && 4==partIn->HeaderN.y && 4==partIn->HeaderN.z)return breakFlag=1;

  if(correlation2<linfo.Threshold) {
    if(in->HeaderN.x==partIn->HeaderN.x && in->HeaderN.y==partIn->HeaderN.y && in->HeaderN.z==partIn->HeaderN.z)return breakFlag=1;
    searchRange->from.x=partIn->HeaderN.x;
    searchRange->from.y=partIn->HeaderN.y;
    searchRange->from.z=partIn->HeaderN.z;

    if(0==*extractFlag){
      partIn->HeaderN.x *= linfo.scaling;
      partIn->HeaderN.y *= linfo.scaling;
      partIn->HeaderN.z *= linfo.scaling;
    }

    if(1==*extractFlag){
      partIn->HeaderN.x = (searchRange->from.x+searchRange->to.x)/2;
      partIn->HeaderN.y = (searchRange->from.y+searchRange->to.y)/2;
      partIn->HeaderN.z = (searchRange->from.z+searchRange->to.z)/2;
    }
    partRef->HeaderN.x = partIn->HeaderN.x;
    partRef->HeaderN.y = partIn->HeaderN.y;
    partRef->HeaderN.z = partIn->HeaderN.z;

    if(partIn->HeaderN.x==prePartInHeaderN.x && partIn->HeaderN.y==prePartInHeaderN.y && partIn->HeaderN.z==prePartInHeaderN.z)return breakFlag=1;
    
    prePartInHeaderN.x=partIn->HeaderN.x;
    prePartInHeaderN.y=partIn->HeaderN.y;
    prePartInHeaderN.z=partIn->HeaderN.z;
    
    return breakFlag=0;
  }
  
  else if(correlation3>linfo.Threshold){
    searchRange->to.x=partIn->HeaderN.x;
    searchRange->to.y=partIn->HeaderN.y;
    searchRange->to.z=partIn->HeaderN.z;
    
    partIn->HeaderN.x = (searchRange->from.x+searchRange->to.x)/2;
    partIn->HeaderN.y = (searchRange->from.y+searchRange->to.y)/2;
    partIn->HeaderN.z = (searchRange->from.z+searchRange->to.z)/2;
    partRef->HeaderN.x = partIn->HeaderN.x;
    partRef->HeaderN.y = partIn->HeaderN.y;
    partRef->HeaderN.z = partIn->HeaderN.z;
    *extractFlag=1;

    if(partIn->HeaderN.x==prePartInHeaderN.x && partIn->HeaderN.y==prePartInHeaderN.y && partIn->HeaderN.z==prePartInHeaderN.z)return breakFlag=1;

    prePartInHeaderN.x=partIn->HeaderN.x;
    prePartInHeaderN.y=partIn->HeaderN.y;
    prePartInHeaderN.z=partIn->HeaderN.z;
    return breakFlag=0;
  }
  else return breakFlag=1;
  
}

void loutHeaderSet(mrcImage* out,mrcImage* in,lmrcImageFractalFourierShellCorrelationInfo linfo){
  out->HeaderN.x=(int)(in->HeaderN.x/linfo.stepx+1);
  out->HeaderN.y=(int)(in->HeaderN.y/linfo.stepy+1);
  out->HeaderN.z=(int)(in->HeaderN.z/linfo.stepz+1);
  out->HeaderLength.x=in->HeaderLength.x*linfo.stepx;
  out->HeaderLength.y=in->HeaderLength.y*linfo.stepy;
  out->HeaderLength.z=in->HeaderLength.z*linfo.stepz;
}
