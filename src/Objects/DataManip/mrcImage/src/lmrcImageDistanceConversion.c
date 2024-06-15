/*
# lmrcImageDistanceConversion : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : lmrcImageDistanceConversion 
# Attention
#   $Loccker$
#  	$State$ 
#
*/
/* $Log$ */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#undef DEBUG
#include "genUtil.h"
#include "Memory.h"
#include "../inc/mrcImage.h"
#include "lmrcImageDistanceConversion.h"
#include "lmrcImageConnectivityNumberCalc.h"

void
lmrcImageDistanceConversion(mrcImage* in,mrcImage* out, int mode, int form)
{
	if( (mode == lmrcImageDistanceConversionMode4Neibour        || mode ==  4)) {
		lmrcImageDistanceConversion_4Neighborhood(in,out);
	} else if( (mode == lmrcImageDistanceConversionMode8Neibour || mode ==  8)) {
		lmrcImageDistanceConversion_8Neighborhood(in,out);
	} else if( (mode ==lmrcImageDistanceConversionMode6Neibour  || mode ==  6)){
		lmrcImageDistanceConversion_6Neighborhood(in,out);
	} else if( (mode ==lmrcImageDistanceConversionMode18Neibour || mode == 18)){
		lmrcImageDistanceConversion_18Neighborhood(in,out);
	} else if( (mode ==lmrcImageDistanceConversionMode26Neibour || mode == 26)){ 
		lmrcImageDistanceConversion_26Neighborhood(in,out);
	} else {
		fprintf(stderr, "Not suported: %d\n", mode);
	}
	if( form == 1 ){
		lmrcImageMakingFrame(in,out,mode);
	} else if( form == 2 ){
				
	} else{
		mrcStatDataSet(out,0);
	}	
}	


/*
	26-neighbor
*/
void
lmrcImageDistanceConversion_26Neighborhood(mrcImage* in, mrcImage* out)
{
	mrcImageParaTypeReal x, y, z;
	mrcImageParaTypeReal x_max, y_max, z_max;
	int n = 0;
	double data[28];
	double min;

	out->Header = in->Header;
	mrcInit(out,NULL);
	for(z=0; z < in->HeaderN.z; z++){
	for(y=0; y < in->HeaderN.y; y++){
	for(x=0; x < in->HeaderN.x; x++){
		mrcPixelDataGet(in, x, y, z, &data[0], mrcPixelRePart, mrcPixelHowNearest); 		
		if(data[0]==1) {
		} else if(data[0]==0) {
			min = 0.0;
		} else {
		}
		mrcPixelDataSet(in,x,y,z,min,mrcPixelRePart);
	}
	}
	}

	for(z=in->HeaderN.z-1; 0<=z; z--){
	for(y=in->HeaderN.y-1; 0<=y; y--){
	for(x=in->HeaderN.x-1; 0<=x; x--){ 
	}
	}
	}
}

/*
	18-neighbor
*/
void
lmrcImageDistanceConversion_18Neighborhood(mrcImage* in, mrcImage* out)
{
	mrcImageParaTypeReal x, y, z;
	mrcImageParaTypeReal x_max, y_max, z_max;
	int n = 0;
	double data[28];
	double min;

	out->Header = in->Header;
	mrcInit(out,NULL);
	for(z=0; z < in->HeaderN.z; z++){
	for(y=0; y < in->HeaderN.y; y++){
	for(x=0; x < in->HeaderN.x; x++){
		mrcPixelDataGet(in, x, y, z, &data[0], mrcPixelRePart, mrcPixelHowNearest); 		
		if(data[0]==1) {
		} else if(data[0]==0) {
			min = 0.0;
		} else {
		}
		mrcPixelDataSet(in,x,y,z,min,mrcPixelRePart);
	}
	}
	}

	for(z=in->HeaderN.z-1; 0<=z; z--){
	for(y=in->HeaderN.y-1; 0<=y; y--){
	for(x=in->HeaderN.x-1; 0<=x; x--){ 
	}
	}
	}
}

/*
	6-neighbor
*/
void
lmrcImageDistanceConversion_6Neighborhood(mrcImage* in, mrcImage* out)
{
	mrcImageParaTypeReal x, y, z;
	mrcImageParaTypeReal x_max, y_max, z_max;
	int n = 0;
	double data[28];
	double min;

	out->Header = in->Header;
	mrcInit(out,NULL);
	for(z=0; z < in->HeaderN.z; z++){
	for(y=0; y < in->HeaderN.y; y++){
	for(x=0; x < in->HeaderN.x; x++){
		mrcPixelDataGet(in, x, y, z, &data[0], mrcPixelRePart, mrcPixelHowNearest); 		
		if(data[0]==1) {
		} else if(data[0]==0) {
			min = 0.0;
		} else {
		}
		mrcPixelDataSet(in,x,y,z,min,mrcPixelRePart);
	}
	}
	}

	for(z=in->HeaderN.z-1; 0<=z; z--){
	for(y=in->HeaderN.y-1; 0<=y; y--){
	for(x=in->HeaderN.x-1; 0<=x; x--){ 
	}
	}
	}
}

void
lmrcImageDistanceConversion_4Neighborhood(mrcImage* in,mrcImage* out)
{ 
	mrcImageParaTypeReal x,y,z;
	mrcImageParaTypeReal x_max,y_max,z_max;
	int n=0;
	double data[10];
	double min;
	
	out->Header = in->Header;
	mrcInit(out,NULL);
	for(z=0; z < in->HeaderN.z; z++){
	for(y=0; y < in->HeaderN.y; y++){
	for(x=0; x < in->HeaderN.x; x++){
		mrcNinePixelDataGet(in,out,x,y,z,data);
		data[5] += 1.0 ; data[7] += 1.0 ;
		if( data[0] == 1.0 ){
			if( data[5] < data[7] ){
				min = data[5];
			}else{
				min = data[7];
			}
		}else if( data[0] == 0.0 ){
			min = 0.0;
		}else{
			min = data[0];
			if( min > data[5] ){
				min = data[5];
			}
			if( min > data[7] ){
				min = data[7];
			}
		}	
		mrcPixelDataSet(in,x,y,z,min,mrcPixelRePart);
	}
	}
	}
	x_max = x-1.0 ; y_max = y-1.0 ; z_max = z-1.0 ;
	for(z = z_max ; z >= 0.0 ; z--){
	for(y = y_max ; y >= 0.0 ; y--){
	for(x = x_max ; x >= 0.0 ; x--){
		mrcNinePixelDataGet(in,out,x,y,z,data);
		data[1] += 1.0 ; data[3] += 1.0 ;
		min = data[0];
		if( min > data[1] ){
			min = data[1];
		}
		if( min > data[3] ){
			min = data[3];
		}
		mrcPixelDataSet(in,x,y,z,min,mrcPixelRePart);
		mrcPixelDataSet(out,x,y,z,min,mrcPixelRePart);
	}
	}
	}
}

void
lmrcImageDistanceConversion_8Neighborhood(mrcImage* in,mrcImage* out)
{

	mrcImageParaTypeReal x,y,z;
	mrcImageParaTypeReal x_max,y_max,z_max;
	int n=0,i;
	double data[10];
	double min;

	out->Header = in->Header;
	mrcInit(out,NULL);
	for(z=0; z < in->HeaderN.z; z++){
	for(y=0; y < in->HeaderN.y; y++){
	for(x=0; x < in->HeaderN.x; x++){
		mrcNinePixelDataGet(in,out,x,y,z,data);	
		data[5] += 1.0 ; data[6] += 1.0;
		data[7] += 1.0 ; data[8] += 1.0;
		if( data[0] == 1.0 ){
			min = data[5];
			for( i = 6 ; i < 9 ; i++ ){
				if( min > data[i] ){
					min = data[i];
				}
			}
		}else if( data[0] == 0.0 ){
			min = 0.0;
		}else{
			min = data[0];
			for( i = 5 ; i < 9 ; i++ ){
				if( min > data[i] ){
					min = data[i];
				}
			}
		}
		mrcPixelDataSet(in,x,y,z,min,mrcPixelRePart);
	}
	}
	}
	x_max = x-1.0 ; y_max = y-1.0 ; z_max = z-1.0 ;
	for(z = z_max ; z >= 0.0 ; z--){
	for(y = y_max ; y >= 0.0 ; y--){
	for(x = x_max ; x >= 0.0 ; x--){
		mrcNinePixelDataGet(in,out,x,y,z,data);
		data[1] += 1.0 ; data[2] += 1.0 ; 
		data[3] += 1.0 ; data[4] += 1.0 ;
		min = data[0];
		for( i = 1 ; i < 5 ; i++ ){
			if( min > data[i] ){
				min = data[i];
			}
		}	
		mrcPixelDataSet(in,x,y,z,min,mrcPixelRePart);
		mrcPixelDataSet(out,x,y,z,min,mrcPixelRePart);
	}
	}
	}
}

void
lmrcImageMakingFrame(mrcImage* in,mrcImage* out,int mode)
{
	mrcImageParaTypeReal x,y,z;
	int i;
	double data[10];
	double max;

	for( z=0; z < in->HeaderN.z; z++){
	for( y=0; y < in->HeaderN.y; y++){
	for( x=0; x < in->HeaderN.x; x++){
		max = 0.0;
		mrcNinePixelDataGet(in,out,x,y,z,data);
		if( mode == 0 ){
			for( i = 1; i < 9; i += 2 ){
				if( max < data[i] ){
					max = data[i];
				}	
			}
			if( data[0] >= max && data[0] > 0.0 ){
				data[0] = 1.0;
			}else{
				data[0] = 0.0;
			}	
		}else if( mode == 1 ){
			for( i = 1; i < 9; i++ ){
				if( max < data[i] ){
					max = data[i];
				}	
			}
			if( data[0] >= max && data[0] > 0.0 ){
				data[0] = 1.0;
			}else{	
				data[0] = 0.0;
			}	
		}	
		mrcPixelDataSet(out,x,y,z,data[0],mrcPixelRePart);
	}
	}
	}
	mrcStatDataSet(out,0);
}
