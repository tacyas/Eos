/*
# lmrcImageConnectivityNumberCalc : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : lmrcImageConnectivityNumberCalc 
# Attention
#   $Loccker$
#  	$State$ 
#
*/
/* $Log$ */

static char __sccs_id[] = "%Z%lmrcImageConnectivityNumberCalc ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#undef DEBUG
#include "genUtil.h"
#include "Memory.h"
#include "../inc/mrcImage.h"
#include "lmrcImageConnectivityNumberCalc.h"

void
lmrcImageConnectivityNumberCalc(mrcImage* in, mrcImage* out, int mode, int form,int invers)
{
	if( ( mode <= 1 ) && ( in->HeaderN.z == 1.0 ) ){
		lmrcImageConnectivityNumberCalc_ver2D(in,out,mode,form,invers);
	}else if( ( mode >= 2 && mode <= 3 ) && ( in->HeaderN.z > 1.0 ) ){
		lmrcImageConnectivityNumberCalc_ver3D(in,out,mode,form);
	}else{
		fprintf(stderr,"The dimension of image and the mode of the option are not correct.\n");
		fprintf(stderr,"The option [ -m ] ( 0 or 1 ) is for 2D image.\n");
		fprintf(stderr,"And The option [ -m ] ( only 3 ) is for 3D image.\n");
		exit(1);
	}
}

void
lmrcImageConnectivityNumberCalc_ver2D(mrcImage* in,mrcImage* out,int mode,int form,int invers)
{
	mrcImageParaTypeReal x,y,z;
	int n=0,i;
	double data[ NEIGHBORHOOD + 1 ];
	double connectivity;
	
	out->Header = in->Header;
	mrcInit(out, NULL);
	//fprintf(stdout,"x\ty\tz\tConect\tPixelData\n",0);
	for(z=0 ;z < in->HeaderN.z ;z++) {
	 for(y=0 ;y < in->HeaderN.y ;y++) {
	  for(x=0 ;x < in->HeaderN.x ;x++) {
		
		connectivity = 0.0;
		mrcNinePixelDataGet(in,out,x,y,z,data);
		
		if( ( mode == 1 && invers == 0 ) || ( mode != 1 && invers == 1 ) ) {
			for( i = ( 1 - invers ) ; i < NEIGHBORHOOD ; i++ ) {
				data[i]=1.0-data[i];
			}
			data[NEIGHBORHOOD]=data[1];
		}
		
		for( i = 1 ; i <= 7  ; i += 2 ) {
			connectivity += data[i] - data[i] * data[i+1] * data[i+2];	
		}
		
		fprintf(stdout,"%0.1lf\t%0.1lf\t%0.1lf\t%0.1lf\t%0.1lf\n",x,y,z,connectivity,data[0]);
		
		if(       connectivity == 1.0 && data[0] == 0.0 && form == 1 ) {
			data[0]=1.0;
		}else if( connectivity == 1.0 && data[0] == 1.0 && form == 2 ) {	
			data[0]=0.0;
		}else if( connectivity == 0.0 && data[0] == 1.0 && form == 3 ) {
			data[0]=0.0;
		}else if( form != 0 && form != 1 && form != 2 && form != 3   ) {
			fprintf(stderr,"The option [ -f ] ( form ) is not support [ %d ].\n",form);
			fprintf(stderr,"Please check : $> mrcImageConnectionNumberCalc -h\n");
			exit(EXIT_SUCCESS);
		}

		if( invers == 1 ){
			data[0] = 1.0 -data[0];
		}
		
		mrcPixelDataSet(out, x, y, z, data[0], mrcPixelRePart);
		n++;
		
	  }
	 }
	}		
	mrcStatDataSet(out, 0);
	fprintf(stdout ,"N= %d",n);
}

void
lmrcImageConnectivityNumberCalc_ver3D(mrcImage* in,mrcImage* out,int mode,int form)
{
	mrcImageParaTypeReal x,y,z;
	int n=0,i,j;
	int sixEighteenSwitch = 1;
	double data[ Z_LINE ][ NEIGHBORHOOD + 1 ];
	double buff;
	double connectivity;

	out->Header=in->Header;
	mrcInit(out,NULL);
	//fprintf(stdout,"x\ty\tz\tConnect\tPixelData\n",0);

	for(z=0 ;z < in->HeaderN.z ;z++) {
	 for(y=0 ;y < in->HeaderN.y ;y++) {
	  for(x=0 ;x < in->HeaderN.x ;x++) {
		
		connectivity = 0.0;
		sixEighteenSwitch = 1;
		
		mrcNinePixelDataGet(in,out,x,y,z-1.0,data[0]);
		mrcNinePixelDataGet(in,out,x,y,z    ,data[1]);
		mrcNinePixelDataGet(in,out,x,y,z+1.0,data[2]);
		
		if( mode == 3 ){
			for( i = 0 ; i < 3 ; i++ ){
				for( j = 1 ; j <= NEIGHBORHOOD ; j++ ){
					data[i][j] = 1.0 - data[i][j];
				}
			}
			connectivity += 2.0;
			sixEighteenSwitch = sixEighteenSwitch * ( -1 );
		}
		for( i = 0 ; i < 3 ; i += 2 ) {
			buff = 0.0;
			for( j = 1 ; j <= 7 ; j += 2 ) {
				buff += data[i][j]*data[1][j];
			}
			connectivity += data[i][0] * ( 1.0 - buff ) * (double)sixEighteenSwitch;
		}
		for( i = 1 ; i <= 7 ; i += 2 ) {
			buff = 0.0;
			for( j = 0 ; j <= 2 ; j += 2 ) {
				buff += data[j][0]*data[j][i]*data[j][i+1]*data[j][i+2];
			}
			connectivity += data[1][i] * ( 1.0 - data[1][i+1] * data[1][i+2] * ( 1.0 - buff ) ) * (double)sixEighteenSwitch;
		}

		fprintf(stdout,"%0.1lf\t%0.1lf\t%0.1lf\t%0.1lf\t%0.1lf\n",x,y,z,connectivity,data[1][0]);
		
		if( connectivity == 1.0 && data[1][0] == 0.0 && form == 1 ){
			data[1][0] = 1.0;
		}else if( connectivity == 1.0 && data[1][0] == 1.0 && form == 2 ){
			data[1][0] = 0.0;
		}
		
		mrcPixelDataSet(out, x, y, z, data[1][0], mrcPixelRePart);

		n++;
		
	  }
	 }
	}
	mrcStatDataSet(out, 0);
	fprintf(stdout ,"N= %d",n);
}

void
mrc27PixelDataGet(mrcImage* in, mrcImageParaTypeReal x, mrcImageParaTypeReal y, mrcImageParaTypeReal z, double data[])
{

	mrcImageParaTypeReal x0 = x , y0 = y , z0 = z ;
	int i;

 	for( i = 0 ; i < NEIGHBORHOOD3D ; i++ ){
		if( ( x0 >= -0.5 && x0 < in->HeaderN.x-0.5 ) 
		 && ( y0 >= -0.5 && y0 < in->HeaderN.y-0.5 ) 
		 && ( z0 >= -0.5 && z0 < in->HeaderN.z-0.5 ) ){		
			mrcPixelDataGet(in , x0, y0, z0, &data[i], mrcPixelRePart,mrcPixelHowNearest);
		}else{
			//mrcPixelDataGet(in , x , y , z, &data[i], mrcPixelRePart,mrcPixelHowNearest);
			data[i]=0.0;
		}
		
		switch(i) {
			case 0:
				x0 += 1; //100
				break;
			case 1:
				x0 -= 1; //010
				y0 += 1;
				break;
			case 2:
				y0 -= 1; //001
				z0 += 1;
				break;
			case 3:
				z0 -= 1; //-100
				x0 -= 1;
				break;
			case 4:
				x0 += 1; //0-10
				y0 -= 1;
				break;
			case 5:
				y0 += 1; //00-1
				z0 -= 1;
				break;
			case 6: //110
				x0 += 1;
				y0 += 1;
				y0 += 1;
				break;
			case 7: //011
				x0 -= 1; 
				z0 += 1;
				break;
			case 8: //101
				x0 += 1;
				y0 -= 1;
				break;
			case 9: //-110
				x0 -= 2;
				y0 += 1;
				z0 -= 1; 
				break;
			case 10: //0-11
				x0 += 1;
				y0 -= 2;
				z0 += 1;
				break;
			case 11: //10-1
				x0 += 1;
				y0 += 1;
				z0 -= 2;
				break;
			case 12: //1-10
				y0 -= 1;
				z0 += 1;
				break;
			case 13: //01-1
				x0 -= 1;
				y0 += 2;
				z0 -= 1;
				break;
			case 14: //-101
				x0 -= 1;
				y0 -= 1;
				z0 += 2;
				break;
			case 15: //-1-10
				y0 -= 1;
				z0 -= 1;
				break;
			case 16: //0-1-1
				x0 += 1;
				z0 -= 1;
				break;
			case 17: //-10-1
				x0 -= 1;
				y0 += 1;
				break;
			case 18: //111
				x0 += 2;
				y0 += 1;
				z0 += 1;
				break;
			case 19: //-111
				x0 -= 2;
				break;
			case 20: //1-11
				x0 += 2;
				y0 -= 2;
				break;
			case 21: //11-1
				y0 += 2;
				z0 -= 2;
				break;
			case 22: //-1-11
				x0 -= 2;
				y0 -= 2;
				z0 += 2;
				break;
			case 23: //1-1-1
				x0 += 2;
				z0 -= 2;
				break;
			case 24: //-11-1
				x0 -= 2;
				y0 += 2;
				break;
			case 25: //-1-1-1
				y0 -= 2;
				break;
			default: {
				fprintf(stderr, "Not supported mode: %d\n", i);
				break;
			}

		}
	}
	data[NEIGHBORHOOD3D]=data[1];	
}

void
mrcNinePixelDataGet(mrcImage* in,mrcImage* out,mrcImageParaTypeReal x,mrcImageParaTypeReal y,mrcImageParaTypeReal z,double data[])
{
	mrcImageParaTypeReal x0 = x , y0 = y , z0 = z ;
	
	int i,flag;
	int CoodPlus              =-1 ;
	int PlusMinusXswitch      = 0 ;
	int PlusMinusXswitchCount = 1 ; 
	int Yswitch               = 1 ;
	int YswitchCount          = 1 ;

 	for( i = 0 ; i < NEIGHBORHOOD ; i++ ){
	
		if( ( x0 >= -0.5 && x0 < in->HeaderN.x-0.5 ) 
		 && ( y0 >= -0.5 && y0 < in->HeaderN.y-0.5 ) 
		 && ( z0 >= -0.5 && z0 < in->HeaderN.z-0.5 ) ){		
			mrcPixelDataGet(in , x0, y0, z0, &data[i], mrcPixelRePart,mrcPixelHowNearest);
		}else{
			//mrcPixelDataGet(in , x , y , z, &data[i], mrcPixelRePart,mrcPixelHowNearest);
			data[i]=0.0;
		}
		
		if( i == 0 ) {
			CoodPlus=CoodPlus*(-1);
			flag=1;
			PlusMinusXswitch += PlusMinusXswitchCount * 2 ;
			PlusMinusXswitchCount++;
		}else{
			if( ((double)i)/((double)PlusMinusXswitch) == 1.0 ) {
				CoodPlus=CoodPlus*(-1);
				flag=1;	
				PlusMinusXswitch += PlusMinusXswitchCount * 2 ;
				PlusMinusXswitchCount++;
			}else if( ( (double)i)/((double)Yswitch) == 1.0 ){
				flag=0;
				Yswitch += YswitchCount * 2 + 1 ;
				YswitchCount++;
			}
		}
		
		if( flag == 1 ) {
			x0 += CoodPlus;
		}else if( flag == 0 ) {
			y0 += CoodPlus;
		}else{
			fprintf(stderr,"Error : Please check lmrcImageConnectionNumberCalc.c\n");
			exit(EXIT_SUCCESS);
		}
		
	}
	data[NEIGHBORHOOD]=data[1];	
}	


