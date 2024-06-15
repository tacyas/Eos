/*
# mrcImageAdaptiveBinalization.c  1.1
# The latest update : 06/14/96 at 22:17:23
#
#@(#) mrcImageAdaptiveBinalization ver 1.1
#@(#) Created by 
#@(#)
#@(#) Usage : mrcImageAdaptiveBinalization
#@(#) Attention
#@(#)
*/
static char __sccs_id[] = "@(#)mrcImageAdaptiveBinalization ver1.1; Date:96/06/14 @(#)";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#undef DEBUG
#include "genUtil.h"
#include "../inc/config.h"
#include "mrcImage.h"

void mrcImageAdaptiveBinalizationAveraging(mrcImage* out ,mrcImage* in ,int size ) ;
void lmrcImageAdaptiveBinalization( mrcImage* out ,mrcImage* in ,mrcImage* av);

void
main(int argc, char* argv[]) 
{
	long status;
	mrcImageAdaptiveBinalizationInfo info;

/* variables */
	mrcImage in;
	mrcImage out;
	mrcImage av;

/* input parameters ,file open */
	DEBUGPRINT("start\n");  
	init0(&info);
	argCheck(&info, argc, argv);
	init1(&info);


/* begin */
	DEBUGPRINT("Reading\n");
	mrcFileRead(&in,  info.In , "in main" ,0);

	DEBUGPRINT("Averaging\n"); 
	mrcImageAdaptiveBinalizationAveraging(&av ,&in ,info.Size );

	DEBUGPRINT("Binalizing\n");
	lmrcImageAdaptiveBinalization(&out ,&in ,&av );

	DEBUGPRINT("Writing\n"); 
	mrcFileWrite(&out ,info.Out ,"in main" ,0);

	exit(EXIT_SUCCESS);
}


void  mrcImageAdaptiveBinalizationAveraging(mrcImage* out ,mrcImage* in ,int size )
{
/* variables */
	int area,i,j,m,k;
    double data1,data2,op;
    float* av;

/* begin */
    out->Header = in->Header;
	mrcInit(out ,NULL);
	if(NULL == ( av = (float*)malloc(sizeof(float)* in->HeaderN.x * in->HeaderN.y) )) { 
		fprintf(stderr, "Enough memory is not available!\n");
	    exit(EXIT_FAILURE);
	}
	     
	area = 4 * size * (size+1) + 1 ;
	i = size ;
	j = size ;
	op = 0.0 ;
	for (k = 0; k  <= 2  * size ; k++){
	   for (m=0; m <= 2 * size ; m++){
	      mrcPixelDataGet(in, k,m,0, &data1, mrcPixelRePart, mrcPixelHowNearest);
	      op = op + data1;
	   }
	}
	av[j * in->HeaderN.x + i] = op;
    

	for (j=size+1 ; j<=in->HeaderN.y-size-1 ; j++){
	    op=av[ (j-1) * in->HeaderN.x + i];
	    for (k=i-size; k<i+size+1 ;k++){
	      mrcPixelDataGet(in, k, j+size,   0, &data1, mrcPixelRePart,mrcPixelHowNearest);
	      mrcPixelDataGet(in, k, j-size-1, 0, &data2, mrcPixelRePart,mrcPixelHowNearest);
	      op = op +data1 -data2;
	    }
	    av[j * in->HeaderN.x + i] = op; 
	}  

	for ( j = size ; j <= in->HeaderN.y - size - 1 ; j++){
	  for ( i = size + 1 ; i <= in->HeaderN.x - size - 1 ; i++){
	    op = av[j * in->HeaderN.x + i - 1 ]; 
	    for ( m = j - size ; m <= j + size ; m++){
	      mrcPixelDataGet(in, i+size,   m, 0, &data1, mrcPixelRePart,mrcPixelHowNearest);
	      mrcPixelDataGet(in, i-size-1, m, 0, &data2, mrcPixelRePart,mrcPixelHowNearest);
	      op = op +data1 -data2;
	    }
	    av[j * in->HeaderN.x + i] = op;
	  }
	}

	for (i = 0 ; i < size ; i++) {
		for (j = 0 ; j < size ; j++) {
	      av[ j * in->HeaderN.x + i] = av[ size * in->HeaderN.x + size] ;
		 }
	    for (j = in->HeaderN.y - size ; j < in->HeaderN.y ;j++) {
	      av[j * in->HeaderN.x + i] 
			= av[(in->HeaderN.y - size - 1) * in->HeaderN.x + size];
		}
	    for (j = size ; j < in->HeaderN.y - size ;j++) {
	      av[j * in->HeaderN.x + i] =av[j * in->HeaderN.x + size];
		}
	}

	for (i = in->HeaderN.x - size ; i < in->HeaderN.x ; i++){
	  for (j = 0 ; j < size ;j++) {
	    av[ j * in->HeaderN.x + i] 
	      = av[(in->HeaderN.x - size - 1) + in->HeaderN.x * size] ;
		}
	  for (j = in->HeaderN.y-size ; j < in->HeaderN.y ; j++) {
	    av[ j * in->HeaderN.x + i] 
	      =av[(in->HeaderN.x - size - 1) + in->HeaderN.x * (in->HeaderN.y - size - 1)];
	  }
	  for (j = size ;j < in->HeaderN.y-size ;j++) {
	    av[ j * in->HeaderN.x+i] 
	      =av[(in->HeaderN.x - size - 1) + in->HeaderN.x * j];
	  }
	}

	
	for (i=0 ; i < in->HeaderN.x ; i++) {
	  for (j=0 ; j < out->HeaderN.y ; j++){
	    av[ j * in->HeaderN.x + i] =  av[ j * in->HeaderN.x + i ] / area;
	    mrcPixelDataSet
	      (out, i, j,0, av[ j * in->HeaderN.x + i ], mrcPixelRePart);
	    }
	} 
	mrcStatDataSet(out,0);
}


void lmrcImageAdaptiveBinalization(mrcImage* out, mrcImage* in, mrcImage* av)
{
/* variables */
  int i,j;
  double din,dav,dout;

/* begin */
  out->Header = in->Header;
  mrcInit(out ,NULL);

  for (j = 0 ;j < in->HeaderN.x ;j++)
    { for (i=0 ;i < in->HeaderN.y ;i++)
	{ mrcPixelDataGet(in, i, j, 0, &din, mrcPixelRePart,mrcPixelHowNearest);
	  mrcPixelDataGet(av, i, j, 0, &dav, mrcPixelRePart,mrcPixelHowNearest);
	  if (din > dav)  {
		dout = 1.0;
	  } else {
		dout = 0.0 ;
	  }
	  mrcPixelDataSet(out, i, j, 0, dout, mrcPixelRePart);
	}
  }
  mrcStatDataSet(out,0);
}

void
additionalUsage()
{
}






