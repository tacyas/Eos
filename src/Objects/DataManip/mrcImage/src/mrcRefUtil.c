#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#undef DEBUG
#include "genUtil.h"
#include "mrcImage.h"
#include "mrcRefUtil.h"
#include "time.h"
#include "Random.h"

#define lmrcPixelGet(in ,x ,y ,z ,data ,type ,how) (lmrcPixelLiGet( (in),(x),(y),(z),(data),(type), (how) ))


/*--------------------------- For General ----------------------------------*/
void lRandShuffle()
{
/* variables */
  time_t jikoku;
  struct tm *lt;
  int it,i;

/* begin */
  time(&jikoku);
  lt = localtime(&jikoku);
  it = lt->tm_mday*(lt->tm_hour+1)*(lt->tm_min+1)*(lt->tm_sec+1);
  DEBUGPRINT1("%d ",it);
  for (i=0 ;i<it ;i++){
    random();
  }
  DEBUGPRINT("\n");
}
 
void lestimateradian(mrcRefDegCoordinate* lradian)
{
  if (*lradian > PI){
    for( ;*lradian > PI ;*lradian -= 2 * PI );
  }else{
    if (*lradian < -PI){
      for( ;*lradian < -PI ;*lradian += 2 * PI );
    }
  }
}


/*--------------------------- For mrcImage Operation  ----------------------*/

double lmrcImageZ1Normalization(mrcImage* in ,int z)
{
/* variables */
  int x,y;
  double sum,data,suma,var,avr;

/* begin */
  sum = 0.0;
  suma = 0.0;
  for (y = 0 ;y < in->HeaderN.y ;y++ ){
    for (x = 0 ;x < in->HeaderN.x ;x++){
      mrcPixelDataGet(in ,x ,y ,z ,&data ,mrcPixelRePart ,mrcPixelHowNearest);
      sum += data*data;
      suma += data;
    }
  }
  avr = suma /(in->HeaderN.y * in->HeaderN.x );
  var = sqrt ( sum - avr*avr*in->HeaderN.x*in->HeaderN.y );
  DEBUGPRINT2("%f %f ",avr,var );
  if (var < 1e-7) var = 1e-7;
  for (y = 0 ;y < in->HeaderN.y ;y++ ){
    for (x = 0 ;x < in->HeaderN.x ;x++){
      mrcPixelDataGet(in ,x ,y ,z ,&data ,mrcPixelRePart ,mrcPixelHowNearest);
      data = (data - avr) / var;
      mrcPixelDataSet(in ,x ,y ,z ,data  ,mrcPixelRePart);
    }
  }
  mrcStatDataSet(in ,0);
  return(var);
}

double lmrcImageNormalization(mrcImage* in ,int mode)
{
/* variables */
  int x,y,z;
  double sum,data,suma,var,avr;

/* begin */
  sum = 0.0;
  suma = 0.0;
  for (z = 0 ;z < in->HeaderN.z ;z++){
    for (y = 0 ;y < in->HeaderN.y ;y++ ){
      for (x = 0 ;x < in->HeaderN.x ;x++){
	mrcPixelDataGet(in ,x ,y ,z ,&data ,mrcPixelRePart ,mrcPixelHowNearest);
	sum += data*data;
	suma += data;
      }
    }
  }
  avr = suma /(in->HeaderN.y * in->HeaderN.x * in->HeaderN.z  );
  var = sqrt ( sum - avr*avr*in->HeaderN.x*in->HeaderN.y*in->HeaderN.z );
  DEBUGPRINT2("%f %f ",avr,var );
  if (var < 1e-7) var = 1e-7;
  for (z = 0 ;z < in->HeaderN.z ;z++ ){
    for (y = 0 ;y < in->HeaderN.y ;y++ ){
      for (x = 0 ;x < in->HeaderN.x ;x++){
	mrcPixelDataGet(in ,x ,y ,z ,&data ,mrcPixelRePart ,mrcPixelHowNearest);
	data = (data - avr) / var;
	mrcPixelDataSet(in ,x ,y ,z ,data  ,mrcPixelRePart);
      }
    }
  }
  mrcStatDataSet(in ,0);
  return(var);
}

void lmrcImageRectangleGet(mrcImage* out ,mrcImage* in ,int blx ,int bly ,int trx ,int try )
{
/* variables */
  int x,y;
  double data;

/* initialization */
  out->Header = in->Header;
  out->HeaderN.x = trx - blx + 1;
  out->HeaderN.y = try - bly + 1;
  mrcInit(out,NULL);

/* begin */
  for (x = blx ;x <= trx ;x++){
    for (y = bly ;y <=try ;y++){
      mrcPixelDataGet(in ,x ,y ,0 ,&data ,mrcPixelRePart ,mrcPixelHowNearest);
      mrcPixelDataSet(out ,x-blx ,y-bly ,0 ,data, mrcPixelRePart);
    }
  }
  mrcStatDataSet(out,0);
}


void llmrcImageAdd(mrcImage* in1 ,mrcImage* in2)
{
/* variables */
  int x,y,z;
  double data1,data2,datao;

/* begin */
  for (z=0 ;z<in1->HeaderN.z ;z++){
    for (y=0 ;y<in1->HeaderN.y ;y++){
      for (x=0 ;x<in1->HeaderN.x ;x++){
	mrcPixelDataGet(in1,x,y,z,&data1,mrcPixelRePart ,mrcPixelHowNearest); 
	mrcPixelDataGet(in2,x,y,z,&data2,mrcPixelRePart ,mrcPixelHowNearest); 
	datao = data1+data2;
	mrcPixelDataSet(in1,x,y,z,datao ,mrcPixelRePart);
      }
    }
  }
  mrcStatDataSet(in1,0);  
}

void llmrcImageSub(mrcImage*out ,mrcImage* in1 ,mrcImage* in2)
{
/* variables */
  int x,y,z;
  double data1,data2,datao;

  out->Header = in1->Header;
  mrcInit(out,NULL);

/* begin */
  for (z=0 ;z<in1->HeaderN.z ;z++){
    for (y=0 ;y<in1->HeaderN.y ;y++){
      for (x=0 ;x<in1->HeaderN.x ;x++){
	mrcPixelDataGet(in1,x,y,z,&data1,mrcPixelRePart ,mrcPixelHowNearest); 
	mrcPixelDataGet(in2,x,y,z,&data2,mrcPixelRePart ,mrcPixelHowNearest); 
	datao = data1-data2;
	DEBUGPRINT4("%d %f %f %f ",x,data1,data2,datao); 
	mrcPixelDataSet(out,x,y,z,datao ,mrcPixelRePart);
      }
    }
  }
  mrcStatDataSet(out,0);  
}

void lmrcPixelLiGet(mrcImage* mrc,
		    mrcImageParaTypeReal x,
		    mrcImageParaTypeReal y,
		    mrcImageParaTypeReal z,
		    double* data,
		    mrcPixelDataType mode,
		    mrcPixelDataHowToGet how)
{
/* variables */
  double tmp;
  int xi,yi,zi;

/* initialization */
  xi = (int)x;
  yi = (int)y;
  zi = (int)z;

/* begin */
  *data = 0.0;
  mrcPixelDataGet(mrc ,xi   ,yi   ,zi   ,&tmp, mode, mrcPixelHowNearest);
  *data += (1-(x-xi))*(1-(y-yi))*(1-(z-zi))*tmp;
  mrcPixelDataGet(mrc ,xi   ,yi   ,zi+1 ,&tmp, mode, mrcPixelHowNearest);
  *data += (1-(x-xi))*(1-(y-yi))*( z - zi )*tmp;
  mrcPixelDataGet(mrc ,xi   ,yi+1 ,zi   ,&tmp, mode, mrcPixelHowNearest);
  *data += (1-(x-xi))*( y - yi )*(1-(z-zi))*tmp;
  mrcPixelDataGet(mrc ,xi   ,yi+1 ,zi+1 ,&tmp, mode, mrcPixelHowNearest);
  *data += (1-(x-xi))*( y - yi )*( z - zi )*tmp;
  mrcPixelDataGet(mrc ,xi+1 ,yi   ,zi   ,&tmp, mode, mrcPixelHowNearest);
  *data += ( x - xi )*(1-(y-yi))*(1-(z-zi))*tmp;
  mrcPixelDataGet(mrc ,xi+1 ,yi   ,zi+1 ,&tmp, mode, mrcPixelHowNearest);
  *data += ( x - xi )*(1-(y-yi))*( z - zi )*tmp;
  mrcPixelDataGet(mrc ,xi+1 ,yi+1 ,zi   ,&tmp, mode, mrcPixelHowNearest);
  *data += ( x - xi )*( y - yi )*(1-(z-zi))*tmp;
  mrcPixelDataGet(mrc ,xi+1 ,yi+1 ,zi+1 ,&tmp, mode, mrcPixelHowNearest);
  *data += ( x - xi )*( y - yi )*( z - zi )*tmp;
}
   

double
mrcImagecubicConvolutionInterpolation(mrcImage* in, double x, double y)
{
    double dat,imagedata;
    long int xl, yl;
    long int xmin, xmax, ymin, ymax;
    double dx, dy;
    long nx,ny;

    nx=in->HeaderN.x;
    ny=in->HeaderN.y;

    if((int)(x-3.0)<0) {
        xmin = 0;
    } else {
        xmin = (int)(x-3.0);
    }
    if((int)(x+3.0)>nx-1) {
        xmax = nx-1;
    } else {
        xmax = (int)(x+3.0);
    }

    if((int)(y-3.0)<0) {
        ymin = 0;
    } else {
        ymin = (int)(y-3.0);
    }
    if((int)(y+3.0)>ny-1) {
        ymax = ny-1;
    } else {
        ymax = (int)(y+3.0);
    }

    dat = 0.0;
    for(xl=xmin; xl<=xmax; xl++) {
        for(yl=ymin; yl<=ymax; yl++) {
            dx = fabs(x-xl);
            dy = fabs(y-yl);
            if(dx>=2.0||dy>=2.0) {
                dat += 0.0;
            } else if(dx>=1.0&&dy>=1.0) {
	        mrcPixelDataGet(in ,xl,yl,0,&imagedata,mrcPixelRePart ,mrcPixelHowNearest);
                dat += ((4.0-8.0*dx+5.0*dx*dx-dx*dx*dx)
                       *(4.0-8.0*dy+5.0*dy*dy-dy*dy*dy)
                       *imagedata);
            } else if(dx>=1.0&&dy<1.0) {
	        mrcPixelDataGet(in ,xl,yl,0,&imagedata,mrcPixelRePart ,mrcPixelHowNearest);
                dat += ((4.0-8.0*dx+5.0*dx*dx-dx*dx*dx)
                       *(1.0-2.0*dy*dy+dy*dy*dy)
                       *imagedata);
            } else if(dx<1.0&&dy>=1.0) {
	        mrcPixelDataGet(in ,xl,yl,0,&imagedata,mrcPixelRePart ,mrcPixelHowNearest);
                dat += ((4.0-8.0*dy+5.0*dy*dy-dy*dy*dy)
                       *(1.0-2.0*dx*dx+dx*dx*dx)
                       *imagedata);
            } else if(dx<1.0&&dy<1.0) {
	        mrcPixelDataGet(in ,xl,yl,0,&imagedata,mrcPixelRePart ,mrcPixelHowNearest);              
		dat += ((1.0-2.0*dx*dx+dx*dx*dx)
                       *(1.0-2.0*dy*dy+dy*dy*dy)
                       *imagedata);
            } else {
                fprintf(stderr, "That's stupid!\n!");
            }
        }
    }
    return(dat);
}

void lmrcImageMultiplyingbyMrc(mrcImage* out ,mrcImage* in1 ,mrcImage* in2)
{

  /* variables */
  int x,y,z,X,Y,Z,Zmax;
  double data1,data2,datao,data1r,data2r,data1i,data2i,dataor,dataoi;

  /* begin */
  out->Header = in1->Header;
  mrcInit(out ,0);

  if (in1->HeaderMode != in2->HeaderMode){
    fprintf(stderr,"in lmrcImageMultiplyingbyMrc: Image mode is diffrent between two images."); 
    exit(EXIT_FAILURE);

  } else if (in1->HeaderMode == mrcFloatImage){
    for (z=0 ;z<in1->HeaderN.z ;z++){
      for (y=0 ;y<in1->HeaderN.y ;y++){
	for (x=0 ;x<in1->HeaderN.x ;x++){
	  mrcPixelDataGet(in1,x,y,z,&data1,mrcPixelRePart ,mrcPixelHowNearest); 
	   mrcPixelDataGet(in2,x,y,z,&data2,mrcPixelRePart ,mrcPixelHowNearest); 
	   datao = data1*data2;
	   mrcPixelDataSet(out,x,y,z,datao ,mrcPixelRePart);
	}
      }
    }
  } else if (in1->HeaderMode == mrcComplexFloatFT){
    (in1->HeaderN.z == 1)?(Zmax=1):(Zmax=in1->HeaderN.z /2);
    for (Z = - in1->HeaderN.z / 2; Z < Zmax  ;Z++){
      for (Y = - in1->HeaderN.y / 2; Y < in1->HeaderN.y/ 2 ;Y++){
	for (X = 0; X <= in1->HeaderN.x / 2 ;X++){
	  mrcPixelDataGet(in1 ,X ,Y ,Z ,&data1r ,mrcPixelRePart ,mrcPixelHowNearest);
	  mrcPixelDataGet(in2 ,X ,Y ,Z ,&data2r ,mrcPixelRePart ,mrcPixelHowNearest);
	  mrcPixelDataGet(in1 ,X ,Y ,Z ,&data1i ,mrcPixelImPart ,mrcPixelHowNearest);
	  mrcPixelDataGet(in2 ,X ,Y ,Z ,&data2i ,mrcPixelImPart ,mrcPixelHowNearest);
	  dataor = data1r*data2r + data1i*data2i;
	  dataoi = -data1r*data2i + data1i*data2r;
	  mrcPixelDataSet(out ,X ,Y ,Z ,dataor ,mrcPixelRePart);
	  mrcPixelDataSet(out ,X ,Y ,Z ,dataoi ,mrcPixelImPart);      
	}
      }
    }

  } else {
    fprintf(stderr,"in lmrcImageMultiplyingbyMrc: Image mode %d is not supported!",in1->HeaderMode);
    exit(EXIT_FAILURE);
  }
  
  mrcStatDataSet(out,0);
}

void lmrcImageFTSetbyRArray(mrcImage* infft ,double** filterval ,int mode)
{
/* variables */
  int X,Y,Z;
  double e,Lx,Ly,Lz,Fx,Fy,Fz;
 
/* begin */
  Lx = infft->HeaderLength.x * infft->HeaderN.x;
  Ly = infft->HeaderLength.y * infft->HeaderN.y;
  Lz = infft->HeaderLength.z * infft->HeaderN.z;
  Fx = 1 / Lx;
  Fy = 1 / Ly;
  Fz = 1 / Lz;
  for(Z = -infft->HeaderN.z / 2.0; Z < infft->HeaderN.z / 2.0; Z += 1){
    for(Y = -infft->HeaderN.y / 2.0; Y < infft->HeaderN.y / 2.0; Y += 1){
      for(X = 0; X <= infft->HeaderN.x / 2.0; X += 1){
	if (mode){
	  e = lmrcImageFTDataSetByRArray(Fx*X ,0 ,0 ,filterval ,mode);
	} else {
	  e = lmrcImageFTDataSetByRArray(Fx*X ,Fy*Y ,Fz*Z ,filterval ,mode);
	}
	mrcPixelDataSet(infft, X, Y, Z, e , mrcPixelRePart);
	mrcPixelDataSet(infft, X, Y, Z, 0 , mrcPixelImPart);
      }
    }
  }
  mrcStatDataSet(infft,0);
}


double lmrcImageFTDataSetByRArray(double X ,double Y ,double Z ,double** filterval ,int mode)
{
/* variables */
  double R,data,d;
  int i;

/* begin */  
  R=X*X+Y*Y+Z*Z;
  if (R > 1e-10){
    R=sqrt(R);
  }
  i=0;
  data=0;
  while (R>=filterval[i][0] && filterval[i][0] != -1 ){
    i++;
  }
  if (filterval[i][0] == -1){
    fprintf(stderr ,"Data range of R is too short! Data for R=%g does not exist!" ,R);
    exit(1);
  }
  d=filterval[i][0]-filterval[i-1][0];
  data = (filterval[i][0]-R)/d*filterval[i-1][1];
  data += (R-filterval[i-1][0])/d*filterval[i][1];
  return(data);	
}

void lmrcImageMagnificationChange(mrcImage* out, mrcImage* in, double ratio)
{
  /* variables */
  double ix,iy,iz,data;
  double d,inx,iny,inz;
  int n2x,n2y,n2z,x,y,z;

  /* initialization */
  out->Header = in->Header ;
  out->HeaderN.x = floor( (float)in->HeaderN.x *ratio +0.5) ;
  out->HeaderN.y = floor( (float)in->HeaderN.y *ratio +0.5) ;
 
  ix = ((float)in->HeaderN.x - 1.0 ) *0.5;
  iy = ((float)in->HeaderN.y - 1.0 ) *0.5;
 
  d = 1.0 / ratio;
  
  n2x=out->HeaderN.x / 2 ;
  n2y=out->HeaderN.y / 2 ;
  (out->HeaderN.x % 2 ) ? (inx = -n2x):(inx = -n2x+0.5);
  (out->HeaderN.y % 2 ) ? (iny = -n2y):(iny = -n2y+0.5);

  if (in->HeaderN.z == 1){
    out->HeaderN.z = 1;
    iz=0;
    n2z=0;
    inz=0;
  } else {
    out->HeaderN.z = floor( (float)in->HeaderN.z *ratio +0.5) ;
    iz = ((float)in->HeaderN.z - 1.0 ) *0.5;
    n2z=out->HeaderN.z / 2 ;
    (out->HeaderN.z % 2 ) ? (inz = -n2z):(inz = -n2z+0.5);
  }

  mrcInit(out,NULL);

  DEBUGPRINT3("%f %d %f\n",ix,n2x,inx);
  for ( x=0 ;x<out->HeaderN.x ;x++ ){
    for ( y=0 ;y<out->HeaderN.y  ;y++ ){
      for ( z=0 ;z<out->HeaderN.z  ;z++ ){
	mrcPixelDataGet(in , (x+inx)*d + ix , (y+iny)*d + iy ,(z+inz)*d +iz ,&data ,mrcPixelRePart,  mrcPixelHowCubicConv);	
	mrcPixelDataSet(out ,x ,y  , z,  data, mrcPixelRePart);      
      }
    }
  }
  mrcStatDataSet(out,0);  
}

void lmrcImageMultiplysingbyFile(mrcImage* in1 ,mrcImage* in2)
{
/* variables */
  int x,y,z;
  double data1,data2,datao;

/* begin */
  for (z=0 ;z<in1->HeaderN.z ;z++){
    for (y=0 ;y<in1->HeaderN.y ;y++){
      for (x=0 ;x<in1->HeaderN.x ;x++){
	mrcPixelDataGet(in1,x,y,z,&data1,mrcPixelRePart ,mrcPixelHowNearest); 
	mrcPixelDataGet(in2,x,y,z,&data2,mrcPixelRePart ,mrcPixelHowNearest); 
	datao = data1*data2;
	mrcPixelDataSet(in1,x,y,z,datao ,mrcPixelRePart);
      }
    }
  }
  mrcStatDataSet(in1,0);  
}
  


/*--------------------------- For mrcImage Statics -------------------------*/

double lmrcImageStandardDeviation(mrcImage* in)
{
/* variables */
	int z;
	double sum;

/* begin */
	sum = 0;
	for (z = 0 ;z < in->HeaderN.z ;z++){
		sum += lmrcRefVariationZ1(in ,z);
	}
	DEBUGPRINT1("1 %f ",sum);
 	sum /= in->HeaderN.z;
	sum = sqrt(sum); 
	DEBUGPRINT1("2 %f ",sum);
	return (sum);
}


/*--------------------------- For Projection -------------------------------*/


void lmrcRefFilamentProjction(mrcImage* out, mrcImage* in, mrcRefDegCoordinate phi ,mrcRefDegCoordinate omega ,mrcRefDegCoordinate alpha ,int sizex ,int sizey )
{

/* variables */

  double data,sum,aphi,itxd,x,y,z,itx,ity,itz,xc;
  /*  int x,y,z,itx,ity,itz,flagz,flagy,xc;
   */
  double e1[3],e2[3],e3[3],rp[3],rs[3],rsy[3],tmp1[3];


/* intialization */
  out->Header = in->Header;
  out->HeaderN.z = 1;
  out->HeaderN.x = sizex ;
  out->HeaderN.y = sizey ;
  mrcInit(out,NULL);

  lestimateradian(&phi);
  aphi = abs(phi) - PI/2 ;
  xc = (floor)( sqrt ((in->HeaderN.x / cos(omega)) * (in->HeaderN.x / cos(omega))
	      +( in->HeaderN.y / cos(omega) ) * (in->HeaderN.y / cos(omega)) ) /2 ) + 1.0 ;
  e1[0] = cos(phi) * cos(omega);
  e1[1] = sin(phi) * cos(omega);
  e1[2] = sin(omega);
  e2[0] = -sin(phi)*cos(alpha) - cos(phi)*sin(omega)*sin(alpha);
  e2[1] =  cos(phi)*cos(alpha) - sin(phi)*sin(omega)*sin(alpha);
  e2[2] =  cos(omega)*sin(alpha);
  e3[0] =  sin(phi)*sin(alpha) - cos(phi)*sin(omega)*cos(alpha);
  e3[1] = -cos(phi)*sin(alpha) - sin(phi)*sin(omega)*cos(alpha);
  e3[2] =  cos(omega)*cos(alpha);
  rs[0] = (double)(in->HeaderN.x - 1.0) / 2.0;
  rs[1] = (double)(in->HeaderN.y - 1.0) / 2.0;
  rs[2] = (double)(in->HeaderN.z - 1.0) / 2.0;
  itz = (double)(out->HeaderN.y -1.0) / 2.0;
  ity = (double)(out->HeaderN.x -1.0) / 2.0; 
  fprintf(stderr ,"itz= %g ,ity= %g \n",itz,ity);

/* begin */
  lvec3mul(tmp1 ,(double)(-itz-1), e3);  /* rs = rs - (itz+1) * e3 */
  lvec3add(rs,rs,tmp1);    
  for (z = -itz ;z <= itz ;z++){
    lvec3add(rs,rs,e3);        /* rs += e3 */    
    lvec3mul(tmp1 ,(double)(-ity-1) ,e2 );  /* rsy = rs - (ity+1) * e2 */
    lvec3add(rsy ,rs ,tmp1);    
    for (y = -ity ;y <= ity ;y++){
      lvec3add(rsy,rsy,e2);    /* rsy += e2 */     
      sum = 0.0;
      itxd = z * tan(omega) / cos(alpha) - xc;
      itx = floor(itxd + 0.5);
      lvec3mul(tmp1 ,(double)itx ,e1 );
      lvec3add(rp ,rsy ,tmp1);

      for ( x = itx ;x <= itx + 2*xc + 1 ;x++){ 
	if (rp[0] < in->HeaderN.x  && rp[0] >= 0 &&
	    rp[1] < in->HeaderN.y  && rp[1] >= 0 &&
	    rp[2] < in->HeaderN.z  && rp[2] >= 0  ){
	  mrcPixelDataGet(in ,rp[0] ,rp[1] ,rp[2] ,&data ,mrcPixelRePart,  mrcPixelHowCubicConv); 
	  /*  	printf("%f %f %f %f \n",rp[0],rp[1],rp[2],data); */  
	  sum += data ;
	}
	lvec3add(rp,rp,e1);
      }
      mrcPixelDataSet(out ,y+ity ,z+itz  , 0,  sum, mrcPixelRePart);      
    }
  }
  mrcStatDataSet(out,0);  
}


void lvec3mul(double* out ,double x ,double* in )
{
  int i;
  for (i=0 ;i<3 ;i++){
    out[i] = x * in[i] ;
  }
}

void lvec3add(double* out ,double* in1 ,double* in2)
{
  int i;
  for (i=0 ;i<3 ;i++){
    out[i] = in1[i] + in2[i];
  }
}

void lvec3sub(double* out ,double* in1 ,double* in2)
{
  int i;
  for (i=0 ;i<3 ;i++){
    out[i] = in1[i] - in2[i];
  }
}

                
 



/*-------------------- For Reference file Operation -----------------------*/


void lmrc3DZ1Clear(mrcImage* in ,int z)
{
  int x,y;
  
  switch(in->HeaderMode){
  case mrcFloatImage:
    DEBUGPRINT("start ");
    for (y = 0 ;y < in->HeaderN.y ;y++){
      for (x = 0 ;x < in->HeaderN.x ;x++){
	DEBUGPRINT2("%d %d  ",x,y );
	mrcPixelDataSet(in ,x ,y ,z  ,0.0 ,mrcPixelRePart); 
      }
    }
    break;
  case mrcComplexFloatFT:
    for (y = 0 ;y < in->HeaderN.y ;y++){
      for (x = 0 ;x < in->HeaderN.x ;x++){
	mrcPixelDataSet(in ,x ,y ,z  ,0.0 ,mrcPixelRePart); 
	mrcPixelDataSet(in ,x ,y ,z  ,0.0 ,mrcPixelImPart); 
      }
    }
  }
}


void lmrcRefHeaderSet(mrcImage* out ,mrcRefHeader* in)
{
  DEBUGPRINT("0 ");
  lmrc3DZ1Clear(out ,0); 
  DEBUGPRINT("1 ");
  mrcPixelDataSet(out ,0 ,0 ,0 ,in->ip ,mrcPixelRePart);
  mrcPixelDataSet(out ,(1%out->HeaderN.x) ,floor(1/out->HeaderN.x) ,0 ,in->iw 
,mrcPixelRePart);
  DEBUGPRINT("0 ");
  mrcPixelDataSet(out ,(2%out->HeaderN.x) ,floor(2/out->HeaderN.x) ,0 ,in->ia 
,mrcPixelRePart);
  mrcPixelDataSet(out ,(3%out->HeaderN.x) ,floor(3/out->HeaderN.x) ,0 ,in->dp 
,mrcPixelRePart);
  mrcPixelDataSet(out ,(4%out->HeaderN.x) ,floor(4/out->HeaderN.x) ,0 ,in->dw 
,mrcPixelRePart);
  DEBUGPRINT("0 ");
  mrcPixelDataSet(out ,(5%out->HeaderN.x) ,floor(5/out->HeaderN.x) ,0 ,in->da 
,mrcPixelRePart);
  mrcPixelDataSet(out ,(6%out->HeaderN.x) ,floor(6/out->HeaderN.x) ,0 ,in->wp 
,mrcPixelRePart);
  mrcPixelDataSet(out ,(7%out->HeaderN.x) ,floor(7/out->HeaderN.x) ,0 ,in->ww 
,mrcPixelRePart);
  mrcPixelDataSet(out ,(8%out->HeaderN.x) ,floor(8/out->HeaderN.x) ,0 ,in->wa 
,mrcPixelRePart);
  DEBUGPRINT("0 ");

}

void lmrcRefHeaderGet(mrcRefHeader* out ,mrcImage* in)
{
  double data;
  mrcPixelDataGet(in ,0                 ,0                      ,0 ,&data 
,mrcPixelRePart ,mrcPixelHowNearest); 
  out->ip = data;
  mrcPixelDataGet(in ,(1%in->HeaderN.x) ,floor(1/in->HeaderN.x) ,0 ,&data 
,mrcPixelRePart ,mrcPixelHowNearest); 
  out->iw = data;
  mrcPixelDataGet(in ,(2%in->HeaderN.x) ,floor(2/in->HeaderN.x) ,0 ,&data 
,mrcPixelRePart ,mrcPixelHowNearest); 
  out->ia = data;
  mrcPixelDataGet(in ,(3%in->HeaderN.x) ,floor(3/in->HeaderN.x) ,0 ,&data 
,mrcPixelRePart ,mrcPixelHowNearest); 
  out->dp = data;
  mrcPixelDataGet(in ,(4%in->HeaderN.x) ,floor(4/in->HeaderN.x) ,0 ,&data 
,mrcPixelRePart ,mrcPixelHowNearest); 
  out->dw = data;
  mrcPixelDataGet(in ,(5%in->HeaderN.x) ,floor(5/in->HeaderN.x) ,0 ,&data 
,mrcPixelRePart ,mrcPixelHowNearest); 
  out->da = data;
  mrcPixelDataGet(in ,(6%in->HeaderN.x) ,floor(6/in->HeaderN.x) ,0 ,&data 
,mrcPixelRePart ,mrcPixelHowNearest); 
  out->wp = data;
  mrcPixelDataGet(in ,(7%in->HeaderN.x) ,floor(7/in->HeaderN.x) ,0 ,&data 
,mrcPixelRePart ,mrcPixelHowNearest); 
  out->ww = data;
  mrcPixelDataGet(in ,(8%in->HeaderN.x) ,floor(8/in->HeaderN.x) ,0 ,&data 
,mrcPixelRePart ,mrcPixelHowNearest); 
  out->wa = data;
}


void lmrc3DZ1ImgPut(mrcImage* out ,mrcImage* in ,int z)
{

/* variables */
  int    x,y;
  double data;
  
/* begin */
  for (y = 0; y < out->HeaderN.y ;y++){
    for (x = 0; x < out->HeaderN.x ;x++){
      mrcPixelDataGet(in ,x ,y ,0 ,&data ,mrcPixelRePart ,mrcPixelHowNearest);
/*    printf("%d %d %d %f ",x,y,z,data); */
      mrcPixelDataSet(out ,x ,y ,z ,data, mrcPixelRePart);      
    }
  }
  mrcStatDataSet(out,0);  
}


void lmrc3DZ1ImgGet(mrcImage* out ,mrcImage* in ,int z)
{

/* variables */
  int    x,y;
  double data;

/* Initialization */
  out->Header = in->Header;
  out->HeaderN.z = 1;
  mrcInit(out,NULL);
  
/* begin */
  for (y = 0; y < out->HeaderN.y ;y++){
    for (x = 0; x < out->HeaderN.x ;x++){
      mrcPixelDataGet(in ,x ,y ,z ,&data ,mrcPixelRePart ,mrcPixelHowNearest);
      mrcPixelDataSet(out ,x ,y ,0 ,data, mrcPixelRePart);      
    }
  }
  mrcStatDataSet(out,0);  
}


void lmrc3DZ1FtGet(mrcImage* out ,mrcImage* in ,int Z)
{

/* variables */
  int    X,Y;
  double data;

/* Initialization */
  out->Header = in->Header;
  out->HeaderN.z = 1;
  mrcInit(out,NULL);
  
/* begin */
  for (Y = - out->HeaderN.y / 2; Y < out->HeaderN.y/ 2 ;Y++){
    for (X = 0; X <= out->HeaderN.x / 2 ;X++){
      mrcPixelDataGet(in ,X ,Y ,Z ,&data ,mrcPixelRePart ,mrcPixelHowNearest);
      mrcPixelDataSet(out ,X ,Y ,0 ,data, mrcPixelRePart);      
      mrcPixelDataGet(in ,X ,Y ,Z ,&data ,mrcPixelImPart ,mrcPixelHowNearest);
      mrcPixelDataSet(out ,X ,Y ,0 ,data, mrcPixelImPart);      
    }
  }
  mrcStatDataSet(out,0);  
}


void lmrc3DZ1FtPut(mrcImage* out ,mrcImage* in ,int Z)
{

/* variables */
  int    X,Y;
  double data;
  
/* begin */
  for (Y = - out->HeaderN.y / 2; Y < out->HeaderN.y / 2  ;Y++){
    for (X = 0; X <= out->HeaderN.x / 2 ;X++){
      mrcPixelDataGet(in  ,X ,Y ,0 ,&data ,mrcPixelRePart ,mrcPixelHowNearest);
      mrcPixelDataSet(out ,X ,Y ,Z - out->HeaderN.z / 2  ,data  
,mrcPixelRePart);      
      mrcPixelDataGet(in  ,X ,Y ,0 ,&data ,mrcPixelImPart ,mrcPixelHowNearest);
      mrcPixelDataSet(out ,X ,Y ,Z - out->HeaderN.z / 2  ,data  
,mrcPixelImPart);      
    }
  }
}


double lmrcRef2DImgCorrelation(mrcImage* in1 ,mrcImage* in2 )
{
/* variables */
  int x,y;
  double c,data1,data2;

/* begin */
  c = 0.0;
  for (y = 0 ;y < in1->HeaderN.y ;y++){
    for (x = 0 ;x < in1->HeaderN.x ;x++){
      mrcPixelDataGet(in1 ,x ,y ,0 ,&data1 ,mrcPixelRePart 
,mrcPixelHowNearest);
      mrcPixelDataGet(in2 ,x ,y ,0 ,&data2 ,mrcPixelRePart 
,mrcPixelHowNearest);
/*      DEBUGPRINT4("%d %d %f %f \n",x,y,data1,data2);  */
      c += data1*data2;
    }
  }
/*  DEBUGPRINT1("%f " ,c);  */
  return(c);
} 


void lmrcRefNormalization(mrcImage* in)
{
/* variables */
  int z;

/* begin */
  for (z = 1 ;z < in->HeaderN.z ;z++ ){
    lmrcImageZ1Normalization(in ,z);
  }
  mrcStatDataSet(in ,0);
}


int lmrcRefGetzCordinate(mrcRefDegCoordinate phi ,mrcRefDegCoordinate omega ,mrcRefDegCoordinate alpha ,mrcRefHeader* header)
{
  int z;

  phi = (phi - header->ip + header->wp)/header->dp;
  omega = (omega - header->iw + header->ww)/header->dw;
  alpha = (alpha - header->ia + header->wa)/header->da;
 
  z =floor((header->wp / header->dp *2 +1)*(header->wa / header->da * 2 + 1)*omega + (header->wa / header->da * 2 + 1)*phi + alpha + 1 +0.5);

  return (z);
}

void lmrcRefGetdegreeCoordinate(mrcRefDegCoordinate* phi ,mrcRefDegCoordinate* omega ,mrcRefDegCoordinate* alpha ,int z ,mrcRefHeader* header)
{
/* variables */
  int np,na,flag;

/* initialization */
  z -= 1;

/* begin */
  np = floor(header->wp / header->dp +0.5)* 2 + 1;
  na = floor(header->wa / header->da +0.5)* 2 + 1;
  flag = 0;
  *omega = z / (np*na) ;
  *omega = header->iw -header->ww +header->dw * (*omega); 
  *phi = ( z%(np*na) )/na;
  *phi = header->ip -header->wp +header->dp * (*phi) ;
  *alpha = z%na;
  *alpha = header->ia -header->wa +header->da * (*alpha);
} 


/*------------------------ For Reference statics ------------------------*/


double lmrcRefSqrAverage(mrcImage* in)
{
/* variables */
	int z;
	double sum;

/* begin */
	DEBUGPRINT("start \n");
	z = 0;
	for (z=1 ;z < in->HeaderN.z ;z++) {
		sum += lmrcRefSqrAverageZ1(in ,z);
		DEBUGPRINT1("%f ",sum);
	}
	sum /= (in->HeaderN.z - 1);
	DEBUGPRINT1("%f \n" ,sum); 
	return(sum);
}


double lmrcRefSqrAverageZ1(mrcImage* in ,int z)
{
/* variables */
	int x,y;
	double sum,data;

/* begin */
	sum = 0.0;
	for(x=0 ;x < in->HeaderN.x ;x++) {
		for(y=0 ;y < in->HeaderN.y ;y++){
			mrcPixelDataGet(in ,x ,y ,z ,&data ,mrcPixelRePart ,mrcPixelHowNearest);
			sum += data * data;
		}
	}
	sum /= (in->HeaderN.x * in->HeaderN.y);
	return(sum);
} 	


double lmrcRefStandardDeviation(mrcImage* in)
{
/* variables */
	int z;
	double sum;

/* begin */

	for (z = 1 ;z < in->HeaderN.z ;z++){
		sum += lmrcRefVariationZ1(in ,z);
	}
 	sum /= (in->HeaderN.z -1);
	sum = sqrt(sum); 
	return (sum);
}


double lmrcRefVariationZ1(mrcImage* in ,int z)
{
/* variables */
	int x,y;
	double sum2,sum,data;

/* begin */
	sum2 = 0.0;
	sum = 0.0;
	for(x=0 ;x < in->HeaderN.x ;x++) {
		for(y=0 ;y < in->HeaderN.y ;y++){
			mrcPixelDataGet(in ,x ,y ,z ,&data ,mrcPixelRePart ,mrcPixelHowNearest);
			sum2 += data*data;
			sum += data;
		      }
	}
	DEBUGPRINT3("%f %f %f ",sum2,sum,sum*sum);
	sum /= (in->HeaderN.x * in->HeaderN.y);
	sum2 /= (in->HeaderN.x * in->HeaderN.y);
	sum2 -= sum*sum;
	return(sum2);
}


/*-------------- For Reference Correlation File Operation -----------*/


void lmrcRefCorHeaderSet(mrcImage* out ,mrcRefCorHeader* in)
{
  lmrc3DZ1Clear(out ,0); 
  mrcPixelDataSet(out ,0 ,0 ,0 ,in->ip ,mrcPixelRePart);
  mrcPixelDataSet(out ,(1%out->HeaderN.x) ,floor(1/out->HeaderN.x) ,0 ,in->iw 
,mrcPixelRePart);
  mrcPixelDataSet(out ,(2%out->HeaderN.x) ,floor(2/out->HeaderN.x) ,0 ,in->ia 
,mrcPixelRePart);
  mrcPixelDataSet(out ,(3%out->HeaderN.x) ,floor(3/out->HeaderN.x) ,0 ,in->dp 
,mrcPixelRePart);
  mrcPixelDataSet(out ,(4%out->HeaderN.x) ,floor(4/out->HeaderN.x) ,0 ,in->dw 
,mrcPixelRePart);
  mrcPixelDataSet(out ,(5%out->HeaderN.x) ,floor(5/out->HeaderN.x) ,0 ,in->da 
,mrcPixelRePart);
  mrcPixelDataSet(out ,(6%out->HeaderN.x) ,floor(6/out->HeaderN.x) ,0 ,in->wp 
,mrcPixelRePart);
  mrcPixelDataSet(out ,(7%out->HeaderN.x) ,floor(7/out->HeaderN.x) ,0 ,in->ww 
,mrcPixelRePart);
  mrcPixelDataSet(out ,(8%out->HeaderN.x) ,floor(8/out->HeaderN.x) ,0 ,in->wa 
,mrcPixelRePart);
  mrcPixelDataSet(out ,(9%out->HeaderN.x) ,floor(9/out->HeaderN.x) ,0 ,in->mode 
,mrcPixelRePart);  
}


void lmrcRefCorHeaderGet(mrcRefCorHeader* out ,mrcImage* in)
{
  double data;
  mrcPixelDataGet(in ,0                 ,0                      ,0 ,&data 
,mrcPixelRePart ,mrcPixelHowNearest); 
  out->ip = data;
  mrcPixelDataGet(in ,(1%in->HeaderN.x) ,floor(1/in->HeaderN.x) ,0 ,&data 
,mrcPixelRePart ,mrcPixelHowNearest); 
  out->iw = data;
  mrcPixelDataGet(in ,(2%in->HeaderN.x) ,floor(2/in->HeaderN.x) ,0 ,&data 
,mrcPixelRePart ,mrcPixelHowNearest); 
  out->ia = data;
  mrcPixelDataGet(in ,(3%in->HeaderN.x) ,floor(3/in->HeaderN.x) ,0 ,&data 
,mrcPixelRePart ,mrcPixelHowNearest); 
  out->dp = data;
  mrcPixelDataGet(in ,(4%in->HeaderN.x) ,floor(4/in->HeaderN.x) ,0 ,&data 
,mrcPixelRePart ,mrcPixelHowNearest); 
  out->dw = data;
  mrcPixelDataGet(in ,(5%in->HeaderN.x) ,floor(5/in->HeaderN.x) ,0 ,&data 
,mrcPixelRePart ,mrcPixelHowNearest); 
  out->da = data;
  mrcPixelDataGet(in ,(6%in->HeaderN.x) ,floor(6/in->HeaderN.x) ,0 ,&data 
,mrcPixelRePart ,mrcPixelHowNearest); 
  out->wp = data;
  mrcPixelDataGet(in ,(7%in->HeaderN.x) ,floor(7/in->HeaderN.x) ,0 ,&data 
,mrcPixelRePart ,mrcPixelHowNearest); 
  out->ww = data;
  mrcPixelDataGet(in ,(8%in->HeaderN.x) ,floor(8/in->HeaderN.x) ,0 ,&data 
,mrcPixelRePart ,mrcPixelHowNearest); 
  out->wa = data;
  mrcPixelDataGet(in ,(9%in->HeaderN.x) ,floor(9/in->HeaderN.x) ,0 ,&data 
,mrcPixelRePart ,mrcPixelHowNearest); 
  out->mode = data;
}


double lmrcRefCorrelationGet(mrcImage* in ,mrcRefDegCoordinate p1 ,mrcRefDegCoordinate w1 ,mrcRefDegCoordinate a1 ,mrcRefDegCoordinate p2 ,mrcRefDegCoordinate w2 ,mrcRefDegCoordinate a2 ,mrcRefCorHeader* header )
{
  double data;
  int z1,z2;

  z1 = lmrcRefCorrelationGetCordinate(p1 ,w1 ,a1 ,header);
  z2 = lmrcRefCorrelationGetCordinate(p2 ,w2 ,a2 ,header);
  if (z1 == -1 || z2== -1){
    return(-2);
  }
  mrcPixelDataGet(in ,z1 ,z2 ,1 ,&data ,mrcPixelRePart ,mrcPixelHowNearest);
  return(data);
}


int lmrcRefCorrelationGetCordinate(mrcRefDegCoordinate phi ,mrcRefDegCoordinate omega ,mrcRefDegCoordinate alpha ,mrcRefCorHeader* header )
{
  int z;

  if ( (header->wp != 0.0 && (phi > header->ip + header->wp || phi < header->ip - header->wp ) ) ||
       (header->ww != 0.0 && (omega > header->iw + header->ww || omega < header->iw - header ->ww ) ) ||
       (header->wa != 0.0 && (alpha > header->ia + header->wa || alpha < header->ia - header ->wa ) ) ){
    return(-1);
  }
  phi = (phi - header->ip + header->wp)/header->dp;
  omega = (omega - header->iw + header->ww)/header->dw;
  alpha = (alpha - header->ia + header->wa)/header->da;  
  z =  floor((header->wp / header->dp *2 +1)*(header->wa / header->da * 2 + 1)*omega + (header->wa / header->da * 2 + 1)*phi + alpha +0.5);
  
  return (z);
}


void lmrcRefCorrelationGetRefxCordinate(mrcRefDegCoordinate* phi ,mrcRefDegCoordinate* omega ,mrcRefDegCoordinate* alpha ,int x ,mrcImage* in ,mrcRefCorHeader* header)
{
/* variables */
  int np,na,z,flag;
  double data;

/* begin */
  np = floor(header->wp / header->dp * 2 + 1 +0.5);
  na = floor(header->wa / header->da * 2 + 1 +0.5);
  flag = 0;
  switch(header->mode){
  case 0:
    z = x;
    break;
  case 1:
    mrcPixelDataGet(in ,x ,in->HeaderN.y-1 ,1 ,&data , mrcPixelRePart,mrcPixelHowNearest);
    z = (int)data;
    break;
  case 2:
    *omega = 0;
    *phi = header->ip -header->wp +header->dp * x;
    *alpha = 0;
    DEBUGPRINT1("%d \n",*phi);
    flag = 1;
  }
  if (flag) return;
  *omega = z / (np*na) ;
  *omega = header->iw -header->ww +header->dw * (*omega); 
  *phi = ( z%(np*na) )/na;
  *phi = header->ip -header->wp +header->dp * (*phi) ;
  *alpha = z%na;
/*   DEBUGPRINT2("%d %d ",z,*alpha); */
  *alpha = header->ia -header->wa +header->da * (*alpha);
/*   DEBUGPRINT1(" %d \n ",*alpha); */
}

void lmrcRefCorrelationGetRefyCordinate(mrcRefDegCoordinate* phi ,mrcRefDegCoordinate* omega ,mrcRefDegCoordinate* alpha ,int y ,mrcImage* in ,mrcRefCorHeader* header)
{
/* variables */
  int np,na,z,flag;

/* begin */
  np = floor(header->wp / header->dp * 2 + 1 +0.5);
  na = floor(header->wa / header->da * 2 + 1 +0.5);
  flag = 0;
  z = y;
  *omega = z / (np*na) ;
  *omega = header->iw -header->ww +header->dw * (*omega); 
  *phi = ( z%(np*na) )/na;
  *phi = header->ip -header->wp +header->dp * (*phi) ;
  *alpha = z%na;
/*   DEBUGPRINT2("%d %d ",z,*alpha); */
  *alpha = header->ia -header->wa +header->da * (*alpha);
/*   DEBUGPRINT1(" %d\n",*alpha); */
}

/*-------------- For pwz Correlation File Operation -----------*/

void lmrcpwzCorHeaderSet(mrcImage* out ,mrcpwzCorHeader* in)
{
  lmrc3DZ1Clear(out ,0); 
  mrcPixelDataSet(out ,0 ,0 ,0 ,in->ip ,mrcPixelRePart);
  mrcPixelDataSet(out ,(1%out->HeaderN.x) ,floor(1/out->HeaderN.x) ,0 ,in->iw 
,mrcPixelRePart);
  mrcPixelDataSet(out ,(2%out->HeaderN.x) ,floor(2/out->HeaderN.x) ,0 ,in->ia 
,mrcPixelRePart);
  mrcPixelDataSet(out ,(3%out->HeaderN.x) ,floor(3/out->HeaderN.x) ,0 ,in->dp 
,mrcPixelRePart);
  mrcPixelDataSet(out ,(4%out->HeaderN.x) ,floor(4/out->HeaderN.x) ,0 ,in->dw 
,mrcPixelRePart);
  mrcPixelDataSet(out ,(5%out->HeaderN.x) ,floor(5/out->HeaderN.x) ,0 ,in->da 
,mrcPixelRePart);
  mrcPixelDataSet(out ,(6%out->HeaderN.x) ,floor(6/out->HeaderN.x) ,0 ,in->wp 
,mrcPixelRePart);
  mrcPixelDataSet(out ,(7%out->HeaderN.x) ,floor(7/out->HeaderN.x) ,0 ,in->ww 
,mrcPixelRePart);
  mrcPixelDataSet(out ,(8%out->HeaderN.x) ,floor(8/out->HeaderN.x) ,0 ,in->wa 
,mrcPixelRePart);
  mrcPixelDataSet(out ,(9%out->HeaderN.x) ,floor(9/out->HeaderN.x) ,0 ,in->sy 
,mrcPixelRePart);
  mrcPixelDataSet(out ,(10%out->HeaderN.x) ,floor(10/out->HeaderN.x) ,0 ,in->ey 
,mrcPixelRePart);
  mrcPixelDataSet(out ,(11%out->HeaderN.x) ,floor(11/out->HeaderN.x) ,0 ,in->refsize 
,mrcPixelRePart);
  mrcPixelDataSet(out ,(12%out->HeaderN.x) ,floor(12/out->HeaderN.x) ,0 ,in->inverse 
,mrcPixelRePart);
}

void lmrcpwzCorHeaderGet(mrcpwzCorHeader* out ,mrcImage* in)
{
  double data;
  mrcPixelDataGet(in ,0                 ,0                      ,0 ,&data 
,mrcPixelRePart ,mrcPixelHowNearest); 
  out->ip = data;
  mrcPixelDataGet(in ,(1%in->HeaderN.x) ,floor(1/in->HeaderN.x) ,0 ,&data 
,mrcPixelRePart ,mrcPixelHowNearest); 
  out->iw = data;
  mrcPixelDataGet(in ,(2%in->HeaderN.x) ,floor(2/in->HeaderN.x) ,0 ,&data 
,mrcPixelRePart ,mrcPixelHowNearest); 
  out->ia = data;
  mrcPixelDataGet(in ,(3%in->HeaderN.x) ,floor(3/in->HeaderN.x) ,0 ,&data 
,mrcPixelRePart ,mrcPixelHowNearest); 
  out->dp = data;
  mrcPixelDataGet(in ,(4%in->HeaderN.x) ,floor(4/in->HeaderN.x) ,0 ,&data 
,mrcPixelRePart ,mrcPixelHowNearest); 
  out->dw = data;
  mrcPixelDataGet(in ,(5%in->HeaderN.x) ,floor(5/in->HeaderN.x) ,0 ,&data 
,mrcPixelRePart ,mrcPixelHowNearest); 
  out->da = data;
  mrcPixelDataGet(in ,(6%in->HeaderN.x) ,floor(6/in->HeaderN.x) ,0 ,&data 
,mrcPixelRePart ,mrcPixelHowNearest); 
  out->wp = data;
  mrcPixelDataGet(in ,(7%in->HeaderN.x) ,floor(7/in->HeaderN.x) ,0 ,&data 
,mrcPixelRePart ,mrcPixelHowNearest); 
  out->ww = data;
  mrcPixelDataGet(in ,(8%in->HeaderN.x) ,floor(8/in->HeaderN.x) ,0 ,&data 
,mrcPixelRePart ,mrcPixelHowNearest); 
  out->wa = data;
  mrcPixelDataGet(in ,(9%in->HeaderN.x) ,floor(9/in->HeaderN.x) ,0 ,&data 
,mrcPixelRePart ,mrcPixelHowNearest); 
  out->sy = data;
  mrcPixelDataGet(in ,(10%in->HeaderN.x) ,floor(10/in->HeaderN.x) ,0 ,&data 
,mrcPixelRePart ,mrcPixelHowNearest); 
  out->ey = data;
  mrcPixelDataGet(in ,(11%in->HeaderN.x) ,floor(11/in->HeaderN.x) ,0 ,&data 
,mrcPixelRePart ,mrcPixelHowNearest); 
  out->refsize = data;
  mrcPixelDataGet(in ,(12%in->HeaderN.x) ,floor(12/in->HeaderN.x) ,0 ,&data 
,mrcPixelRePart ,mrcPixelHowNearest); 
  out->inverse = floor(data+0.5);
}







