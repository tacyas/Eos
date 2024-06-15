/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% lmrcImageModelCreate ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : lmrcImageModelCreate 
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%lmrcImageModelCreate ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  

#undef DEBUG
#include "genUtil.h"
#include "Matrix3D.h"
#include "mrcImage.h"
#include "lmrcImageModelCreate.h"

void 
_lmrcImageModelCreateCylinder(mrcImage* out, mrcImageParaTypeReal radius, mrcImageParaTypeReal length)
{
	mrcImageParaTypeReal x, y, z;
	double data;
	double radius2;
	double length_2;
	double x2;
	double y2;
	double z2;


	radius2 = SQR(radius); 
	length_2 = length/2;
	for(z=0; z<out->HeaderN.z; z++) {
		z2 = fabs(z-out->HeaderN.z/2);	
		if(z2<=length_2) {
			for(y=0; y<out->HeaderN.y; y++) {
				y2 = SQR(y-out->HeaderN.y/2); 
			for(x=0; x<out->HeaderN.x; x++) {
				x2 = SQR(x-out->HeaderN.x/2);
				if(x2+y2<=radius2) {
					mrcPixelDataSet(out, x, y, z, 1.0, mrcPixelRePart);
				} else {
					mrcPixelDataSet(out, x, y, z, 0.0, mrcPixelRePart);
				}

			}
			}
		}
	}
}

void 
_lmrcImageModelCreateMode0(mrcImage* out, mrcImageParaTypeReal radius)
{
	mrcImageParaTypeReal x, y, z;
	double data;

	for(x=0; x<out->HeaderN.x; x++) {
		for(y=0; y<out->HeaderN.y; y++) {
			for(z=0; z<out->HeaderN.z; z++) {
				if(SQR(x-out->HeaderN.x/2)+SQR(y-out->HeaderN.y/2)+SQR(z-out->HeaderN.z/2)<=SQR(radius)) {
					mrcPixelDataSet(out, x, y, z, 1.0, mrcPixelRePart);
				} else {
					mrcPixelDataSet(out, x, y, z, 0.0, mrcPixelRePart);
				}
			}
		}
	}
	for(x=0; x<out->HeaderN.x; x++) {
		for(y=0; y<out->HeaderN.y; y++) {
			for(z=0; z<out->HeaderN.z; z++) {
				if(x < y) {	
					mrcPixelDataGet(out, x, y, z, &data, mrcPixelRePart, mrcPixelHowNearest);
					mrcPixelDataSet(out, x, y, z, data+1.0, mrcPixelRePart);
				} 
			}
		}
	}
}


void 
_lmrcImageModelCreateMode1(mrcImage* out, _lmrcImageModelCreateMode1Info info)
{
	mrcImageParaTypeInteger i1=0, i2=0;
	int count=0;
	mrcImageParaTypeReal x=0, y=0, z=0, zTurn=0;
	float Phi=0, Phi1=0, Phi2=0;
	mrcImageParaTypeReal dstx=0, dsty=0, dstz=0;
	double data=0;

	zTurn = (int) ( fabs( info.endZ - info.startZ ) / info.zPitch );
	DEBUGPRINT1("phiAngle: %f\n", info.phiAngle);

	if(0==out->HeaderN.x%2 || 0==out->HeaderN.y%2) {
		fprintf(stderr, "Even size is not supported\n");
		exit(EXIT_FAILURE);
	}

	switch(info.units) {
		case 9: {
			for ( i2 = 0; i2 <= zTurn; i2++){ 
				for ( i1 = 0; i1 < info.nHelix; i1++){
					count++;
					Phi = info.startPhi + i1*info.phiAngle  + i2*info.deltaPhi;
					Phi1 = Phi + 30.0*RADIAN;
					Phi2 = Phi + 60.0*RADIAN;

					x = info.radius * cos(Phi);
					y = info.radius * sin(Phi);
					z = info.startZ + i2*info.zPitch; 

					fprintf(stderr ,"(%8.3f %8.3f %8.3f) ThickFilaments %d \n",x,y,z,count);
					dstx = x/out->HeaderLength.x + (out->HeaderN.x-1.0)/2.0;
					dsty = y/out->HeaderLength.y + (out->HeaderN.y-1.0)/2.0;
					dstz = z/out->HeaderLength.z;
			
					if(info.flagIn) {
						switch(info.fm) {
							case 0: {
								mrcImageDataSet(out, info.in, dstx, dsty, dstz, Phi, info.inMode);
								break;
							}
							case 1: {
								mrcImageDataSet(out, info.in, dstx, dsty, dstz, Phi, info.inMode);

								x = info.radius * cos(Phi1);
								y = info.radius * sin(Phi1);
								z = info.startZ + i2*info.zPitch; 
								dstx = x/out->HeaderLength.x + (out->HeaderN.x-1.0)/2.0;
								dsty = y/out->HeaderLength.y + (out->HeaderN.y-1.0)/2.0;
								dstz = z/out->HeaderLength.z;
								mrcImageDataSet(out, info.in, dstx, dsty, dstz, Phi1, info.inMode);
	
								x = info.radius * cos(Phi2);
								y = info.radius * sin(Phi2);
								z = info.startZ + i2*info.zPitch; 
								dstx = x/out->HeaderLength.x + (out->HeaderN.x-1.0)/2.0;
								dsty = y/out->HeaderLength.y + (out->HeaderN.y-1.0)/2.0;
								dstz = z/out->HeaderLength.z;
								mrcImageDataSet(out, info.in, dstx, dsty, dstz, Phi2, info.inMode);
	
								break;
							}
							case 2: {
								mrcImageDataSet(out, info.in, dstx, dsty, dstz, Phi, info.inMode);
	
								x = 1.2 * info.radius * cos(Phi);
								y = 1.2 * info.radius * sin(Phi);
								z = 30 + info.startZ + i2*info.zPitch; 
								dstx = x/out->HeaderLength.x + (out->HeaderN.x-1.0)/2.0;
								dsty = y/out->HeaderLength.y + (out->HeaderN.y-1.0)/2.0;
								dstz = z/out->HeaderLength.z;
								mrcImageDataSet(out, info.in, dstx, dsty, dstz, Phi, info.inMode);
	
								x = 1.4 * info.radius * cos(Phi);
								y = 1.4 * info.radius * sin(Phi);
								z = 60 + info.startZ + i2*info.zPitch; 
								dstx = x/out->HeaderLength.x + (out->HeaderN.x-1.0)/2.0;
								dsty = y/out->HeaderLength.y + (out->HeaderN.y-1.0)/2.0;
								dstz = z/out->HeaderLength.z;
								mrcImageDataSet(out, info.in, dstx, dsty, dstz, Phi, info.inMode);
	
								break;
							}
							case 3: {
								mrcImageDataSet(out, info.in, dstx, dsty, dstz, Phi, info.inMode);
	
								x = 1.2 * info.radius * cos(Phi1);
								y = 1.2 * info.radius * sin(Phi1);
								z = info.startZ + i2*info.zPitch; 
								dstx = x/out->HeaderLength.x + (out->HeaderN.x-1.0)/2.0;
								dsty = y/out->HeaderLength.y + (out->HeaderN.y-1.0)/2.0;
								dstz = z/out->HeaderLength.z;
								mrcImageDataSet(out, info.in, dstx, dsty, dstz, Phi1, info.inMode);
	
								x = 1.4 * info.radius * cos(Phi2);
								y = 1.4 * info.radius * sin(Phi2);
								z = info.startZ + i2*info.zPitch; 
								dstx = x/out->HeaderLength.x + (out->HeaderN.x-1.0)/2.0;
								dsty = y/out->HeaderLength.y + (out->HeaderN.y-1.0)/2.0;
								dstz = z/out->HeaderLength.z;
								mrcImageDataSet(out, info.in, dstx, dsty, dstz, Phi2, info.inMode);
	
								break;
							}
							default: {
								fprintf(stderr, "Not supported mode in formation: %d\n", info.fm);
								exit(EXIT_FAILURE);
							}
						}
					} else {
						mrcPixelDataGet(out, dstx, dsty, dstz, &data, mrcPixelRePart, mrcPixelHowLinear);
						mrcPixelDataSet(out, dstx, dsty, dstz, data+1.0, mrcPixelRePart);
					}
				}
			}
		break;
		}
		case 3: {
			DEBUGPRINT2("startZ %f, zPitch %f\n",info.startZ, info.zPitch)
			for ( i1 = 0; i1 < info.nHelix; i1++){
				count++;
				Phi  = info.startPhi + i1*info.phiAngle  + i2*info.deltaPhi;
				Phi1 = Phi + 30.0*RADIAN;
				Phi2 = Phi + 60.0*RADIAN;

				DEBUGPRINT3("Phi %f, Phi1 %f, Phi2 %f\n",Phi, Phi1, Phi2)

				fprintf(stderr ,"(%8.3f %8.3f %8.3f) ThickFilaments %d \n",x,y,z,count);
			
				if(info.flagIn) {
					switch(info.fm) {
						case 0: {
							/* First Crown*/
							/* 1 */
							x = info.radius * cos(Phi);
							y = info.radius * sin(Phi);
							z = info.startZ; 
							dstx = x/out->HeaderLength.x + (out->HeaderN.x-1.0)/2.0;
							dsty = y/out->HeaderLength.y + (out->HeaderN.y-1.0)/2.0;
							dstz = z/out->HeaderLength.z;
							mrcImageDataSet(out, info.in, dstx, dsty, dstz, Phi, info.inMode);

							/* 2 */
							x = info.radius * cos(Phi);
							x = 1.4*info.radius * cos(Phi);
							y = 1.4*info.radius * sin(Phi);
							z = info.startZ; 
							dstx = x/out->HeaderLength.x + (out->HeaderN.x-1.0)/2.0;
							dsty = y/out->HeaderLength.y + (out->HeaderN.y-1.0)/2.0;
							dstz = z/out->HeaderLength.z;
							mrcImageDataSet(out, info.in, dstx, dsty, dstz, Phi, info.inMode);

							/* 3 */
							x = 1.8*info.radius * cos(Phi);
							y = 1.8*info.radius * sin(Phi);
							z = info.startZ; 
							dstx = x/out->HeaderLength.x + (out->HeaderN.x-1.0)/2.0;
							dsty = y/out->HeaderLength.y + (out->HeaderN.y-1.0)/2.0;
							dstz = z/out->HeaderLength.z;
							mrcImageDataSet(out, info.in, dstx, dsty, dstz, Phi, info.inMode);

							/* Second Crown*/
							/* 1 */
							x = info.radius * cos(Phi1);
							y = info.radius * sin(Phi1);
							z = info.startZ + info.zPitch; 
							dstx = x/out->HeaderLength.x + (out->HeaderN.x-1.0)/2.0;
							dsty = y/out->HeaderLength.y + (out->HeaderN.y-1.0)/2.0;
							dstz = z/out->HeaderLength.z;
							mrcImageDataSet(out, info.in, dstx, dsty, dstz, Phi1, info.inMode);
	
							/* 2 */
							x = 1.3*info.radius * cos(Phi1-5*RADIAN);
							y = 1.3*info.radius * sin(Phi1-5*RADIAN);
							z = info.startZ + info.zPitch +25; 
							dstx = x/out->HeaderLength.x + (out->HeaderN.x-1.0)/2.0;
							dsty = y/out->HeaderLength.y + (out->HeaderN.y-1.0)/2.0;
							dstz = z/out->HeaderLength.z;
							mrcImageDataSet(out, info.in, dstx, dsty, dstz, Phi1, info.inMode);
	
							/* 3 */
							x = 1.6*info.radius * cos(Phi1-10*RADIAN);
							y = 1.6*info.radius * sin(Phi1-10*RADIAN);
							z = info.startZ + info.zPitch +50; 
							dstx = x/out->HeaderLength.x + (out->HeaderN.x-1.0)/2.0;
							dsty = y/out->HeaderLength.y + (out->HeaderN.y-1.0)/2.0;
							dstz = z/out->HeaderLength.z;
							mrcImageDataSet(out, info.in, dstx, dsty, dstz, Phi1, info.inMode);
	
							/* Third Crown*/
							/* 1 */
							x = info.radius * cos(Phi2);
							y = info.radius * sin(Phi2);
							z = info.startZ + 2*info.zPitch; 
							dstx = x/out->HeaderLength.x + (out->HeaderN.x-1.0)/2.0;
							dsty = y/out->HeaderLength.y + (out->HeaderN.y-1.0)/2.0;
							dstz = z/out->HeaderLength.z;
							mrcImageDataSet(out, info.in, dstx, dsty, dstz, Phi2, info.inMode);

							/* 2 */
							x = 1.3*info.radius * cos(Phi2+10*RADIAN);
							y = 1.3*info.radius * sin(Phi2+10*RADIAN);
							z = info.startZ + 2*info.zPitch -10; 
							dstx = x/out->HeaderLength.x + (out->HeaderN.x-1.0)/2.0;
							dsty = y/out->HeaderLength.y + (out->HeaderN.y-1.0)/2.0;
							dstz = z/out->HeaderLength.z;
							mrcImageDataSet(out, info.in, dstx, dsty, dstz, Phi2, info.inMode);

							/* 3 */
							x = 1.6*info.radius * cos(Phi2+20*RADIAN);
							y = 1.6*info.radius * sin(Phi2+20*RADIAN);
							z = info.startZ + 2*info.zPitch -20; 
							dstx = x/out->HeaderLength.x + (out->HeaderN.x-1.0)/2.0;
							dsty = y/out->HeaderLength.y + (out->HeaderN.y-1.0)/2.0;
							dstz = z/out->HeaderLength.z;
							mrcImageDataSet(out, info.in, dstx, dsty, dstz, Phi2, info.inMode);

							/* First Crown Again */
							/* 1 */
							x = info.radius * cos(Phi);
							y = info.radius * sin(Phi);
							z = info.startZ + 3*info.zPitch; 
							dstx = x/out->HeaderLength.x + (out->HeaderN.x-1.0)/2.0;
							dsty = y/out->HeaderLength.y + (out->HeaderN.y-1.0)/2.0;
							dstz = z/out->HeaderLength.z;
							mrcImageDataSet(out, info.in, dstx, dsty, dstz, Phi, info.inMode);

							x = 1.4*info.radius * cos(Phi);
							y = 1.4*info.radius * sin(Phi);
							z = info.startZ + 3*info.zPitch; 
							dstx = x/out->HeaderLength.x + (out->HeaderN.x-1.0)/2.0;
							dsty = y/out->HeaderLength.y + (out->HeaderN.y-1.0)/2.0;
							dstz = z/out->HeaderLength.z;
							mrcImageDataSet(out, info.in, dstx, dsty, dstz, Phi, info.inMode);

							x = 1.8*info.radius * cos(Phi);
							y = 1.8*info.radius * sin(Phi);
							z = info.startZ + 3*info.zPitch; 
							dstx = x/out->HeaderLength.x + (out->HeaderN.x-1.0)/2.0;
							dsty = y/out->HeaderLength.y + (out->HeaderN.y-1.0)/2.0;
							dstz = z/out->HeaderLength.z;
							mrcImageDataSet(out, info.in, dstx, dsty, dstz, Phi, info.inMode);

							/* Second Crown Again */
							/* 1 */
							x = info.radius * cos(Phi1);
							y = info.radius * sin(Phi1);
							z = info.startZ + 4*info.zPitch; 
							dstx = x/out->HeaderLength.x + (out->HeaderN.x-1.0)/2.0;
							dsty = y/out->HeaderLength.y + (out->HeaderN.y-1.0)/2.0;
							dstz = z/out->HeaderLength.z;
							mrcImageDataSet(out, info.in, dstx, dsty, dstz, Phi1, info.inMode);
	
							/* 2 */
							x = 1.3*info.radius * cos(Phi1-5*RADIAN);
							y = 1.3*info.radius * sin(Phi1-5*RADIAN);
							z = info.startZ + 4*info.zPitch +25; 
							dstx = x/out->HeaderLength.x + (out->HeaderN.x-1.0)/2.0;
							dsty = y/out->HeaderLength.y + (out->HeaderN.y-1.0)/2.0;
							dstz = z/out->HeaderLength.z;
							mrcImageDataSet(out, info.in, dstx, dsty, dstz, Phi1, info.inMode);
	
							/* 3 */
							x = 1.6*info.radius * cos(Phi1-10*RADIAN);
							y = 1.6*info.radius * sin(Phi1-10*RADIAN);
							z = info.startZ + 4*info.zPitch +50; 
							dstx = x/out->HeaderLength.x + (out->HeaderN.x-1.0)/2.0;
							dsty = y/out->HeaderLength.y + (out->HeaderN.y-1.0)/2.0;
							dstz = z/out->HeaderLength.z;
							mrcImageDataSet(out, info.in, dstx, dsty, dstz, Phi1, info.inMode);
	


							break;
						}
						default: {
							fprintf(stderr, "Not supported mode in formation: %d\n", info.fm);
							exit(EXIT_FAILURE);
						}
					}
				}
			}
		break;
		}
		default: {
			fprintf(stderr, "Not supported units in formation: %d\n", info.units);
			exit(EXIT_FAILURE);
		}
	}
}


void
_lmrcImageModelCreateMode2(mrcImage* out)
{

	mrcImageParaTypeReal x,y;

	for(x=0; x<=out->HeaderN.x; x++){
		for(y=0; y<=out->HeaderN.y; y++){
			if(x== out->HeaderN.x/4 && y== out->HeaderN.y/4){
				mrcPixelDataSet(out,x,y,0.0,1.0,mrcPixelRePart);
			}
			
			else if(x== out->HeaderN.x/4+5 && y==out->HeaderN.y/4+5){
				mrcPixelDataSet(out,x,y,0.0,1.0,mrcPixelRePart);
			}
			
			else if(x== out->HeaderN.x/4+10 && y==out->HeaderN.y/4){
				mrcPixelDataSet(out,x,y,0.0,1.0,mrcPixelRePart);
			}
			else{
				mrcPixelDataSet(out,x,y,0.0,0.0,mrcPixelRePart);
			}	
			
		}
	}
}	

void
_lmrcImageModelCreateMode3(mrcImage* out)
{
	double data;
	mrcImageParaTypeReal x,y,z;

	for(x=0; x<=out->HeaderN.x; x++){
		for(y=0; y<=out->HeaderN.y; y++){
			for(z=0; z<=out->HeaderN.y; z++){
				if( SQR(x-out->HeaderN.x/2)
				   +SQR(y-out->HeaderN.y/2)
				   +SQR(z-out->HeaderN.y/2) < SQR(out->HeaderN.x/5.0) ) {
					mrcPixelDataGet(out,x,y,0.0,&data,mrcPixelRePart, mrcPixelHowNearest);
					mrcPixelDataSet(out,x,y,0.0,data+1,mrcPixelRePart);
				}
				if( SQR(x-out->HeaderN.x/2+out->HeaderN.x/5.0)
				   +SQR(y-out->HeaderN.y/2+out->HeaderN.x/5.0)
				   +SQR(z-out->HeaderN.y/2+out->HeaderN.x/5.0) < SQR(out->HeaderN.x/7.5) ) {
					mrcPixelDataGet(out,x,y,0.0,&data,mrcPixelRePart, mrcPixelHowNearest);
					mrcPixelDataSet(out,x,y,0.0,data+1,mrcPixelRePart);
				}
				if( SQR(x-out->HeaderN.x/2-out->HeaderN.x/5.0)
				   +SQR(y-out->HeaderN.y/2-out->HeaderN.x/5.0)
				   +SQR(z-out->HeaderN.y/2-out->HeaderN.x/5.0) < SQR(out->HeaderN.x/5) ) {
					mrcPixelDataGet(out,x,y,0.0,&data,mrcPixelRePart, mrcPixelHowNearest);
					mrcPixelDataSet(out,x,y,0.0,data+1,mrcPixelRePart);
				}
			}
		}
	}
}	

void
_lmrcImageModelCreateMode4(mrcImage* out)
{
	double data;
	mrcImageParaTypeReal x,y,z;

	for(x=0; x<=out->HeaderN.x; x++){
		for(y=0; y<=out->HeaderN.y; y++){
			for(z=0; z<=out->HeaderN.y; z++){
				if( SQR(x-out->HeaderN.x/2)
				   +SQR(y-out->HeaderN.y/2)
				   +SQR(z-out->HeaderN.y/2) < SQR(out->HeaderN.x/8.0) 
				 && -out->HeaderN.y/10.6<z-out->HeaderN.y/2) {
					mrcPixelDataGet(out,x,y,0.0,&data,mrcPixelRePart, mrcPixelHowNearest);
					mrcPixelDataSet(out,x,y,0.0,data+1,mrcPixelRePart);
				}
				if( SQR(x-out->HeaderN.x/2-out->HeaderN.x/4*cos(M_PI/2.0))
				   +SQR(y-out->HeaderN.y/2-out->HeaderN.x/4*sin(M_PI/2.0))
				   +SQR(z-out->HeaderN.y/2) < SQR(out->HeaderN.x/8.0) 
				 && -out->HeaderN.y/10.6<z-out->HeaderN.y/2) {
					mrcPixelDataGet(out,x,y,0.0,&data,mrcPixelRePart, mrcPixelHowNearest);
					mrcPixelDataSet(out,x,y,0.0,data+1,mrcPixelRePart);
				}
				if( SQR(x-out->HeaderN.x/2-out->HeaderN.x/4*cos(M_PI/2.0+M_PI/3.0))
				   +SQR(y-out->HeaderN.y/2-out->HeaderN.x/4*sin(M_PI/2.0+M_PI/3.0))
				   +SQR(z-out->HeaderN.y/2) < SQR(out->HeaderN.x/8.0) 
				 && -out->HeaderN.y/10.6<z-out->HeaderN.y/2) {
					mrcPixelDataGet(out,x,y,0.0,&data,mrcPixelRePart, mrcPixelHowNearest);
					mrcPixelDataSet(out,x,y,0.0,data+1,mrcPixelRePart);
				}
				if( SQR(x-out->HeaderN.x/2-out->HeaderN.x/4*cos(M_PI/2.0-M_PI/3.0))
				   +SQR(y-out->HeaderN.y/2-out->HeaderN.x/4*sin(M_PI/2.0-M_PI/3.0))
				   +SQR(z-out->HeaderN.y/2) < SQR(out->HeaderN.x/8.0) 
				 && -out->HeaderN.y/10.6<z-out->HeaderN.y/2) {
					mrcPixelDataGet(out,x,y,0.0,&data,mrcPixelRePart, mrcPixelHowNearest);
					mrcPixelDataSet(out,x,y,0.0,data+1,mrcPixelRePart);
				}
				if( SQR(x-out->HeaderN.x/2+out->HeaderN.x/8.0)
				   +SQR(y-out->HeaderN.y/2+out->HeaderN.x/8.0)
				   +SQR(z-out->HeaderN.y/2+out->HeaderN.x/8.0) < SQR(out->HeaderN.x/7.5) 
				  && 0<z-out->HeaderN.y/2+out->HeaderN.x/5.0) {
					mrcPixelDataGet(out,x,y,0.0,&data,mrcPixelRePart, mrcPixelHowNearest);
					mrcPixelDataSet(out,x,y,0.0,data+1,mrcPixelRePart);
				}
				if( SQR(x-out->HeaderN.x/2-out->HeaderN.x/4/sqrt(3)*cos(M_PI/2.0-M_PI/6.0))
				   +SQR(y-out->HeaderN.y/2-out->HeaderN.x/4/sqrt(3)*sin(M_PI/2.0-M_PI/6.0))
				   +SQR(z-out->HeaderN.y/2-out->HeaderN.x/5.0) < SQR(out->HeaderN.x/15) 
				   && 0<z-out->HeaderN.y/2-out->HeaderN.x/5.0) {
					mrcPixelDataGet(out,x,y,0.0,&data,mrcPixelRePart, mrcPixelHowNearest);
					mrcPixelDataSet(out,x,y,0.0,data+1,mrcPixelRePart);
				}
				if( SQR(x-out->HeaderN.x/2-out->HeaderN.x/6)
				   +SQR(y-out->HeaderN.y/2+out->HeaderN.x/6)
				   +SQR(z-out->HeaderN.y/2+out->HeaderN.x/6) < SQR(out->HeaderN.x/5) 
				   && out->HeaderN.y/8<z-out->HeaderN.y/2+out->HeaderN.x/6.0) {
					mrcPixelDataGet(out,x,y,0.0,&data,mrcPixelRePart, mrcPixelHowNearest);
					mrcPixelDataSet(out,x,y,0.0,data+1,mrcPixelRePart);
				}
			}
		}
	}
}	
void
_lmrcImageModelCreateMode5(mrcImage* out)
{
	double data;
	double ratio = 0.7;
	mrcImageParaTypeReal x,y,z,r, roffset, rmax, redge, redgeoffset, offset, d, doffset, xx, xxoffset, yy, yyoffset, w, woffset;
	rmax = out->HeaderN.x/8.0;
	offset = sqrt(2.0)*rmax;
	for(x=0; x<=out->HeaderN.x; x++){
		for(y=0; y<=out->HeaderN.y; y++){
			for(z=0; z<=out->HeaderN.y; z++){
				r       = SQR(x-out->HeaderN.x/2       ) +SQR(y-out->HeaderN.y/2);
				roffset = SQR(x-out->HeaderN.x/2-offset) +SQR(y-out->HeaderN.y/2);
				if(0<r) {
					r = sqrt(r);
				}	
				if(0<roffset) {
					roffset = sqrt(roffset);
				}	

				if(SQR((z-out->HeaderN.x/2)/(ratio*rmax)) + SQR(r/rmax) <= 1 
			     && 1<SQR(roffset/rmax) ) {
					mrcPixelDataGet(out,x,y,0.0,&data,mrcPixelRePart, mrcPixelHowNearest);
					mrcPixelDataSet(out,x,y,0.0,data+1,mrcPixelRePart);
				} else if(SQR(r/rmax)<=1 
				 && SQR(roffset/rmax)<=1 ) {

					d  = x-out->HeaderN.x/2;
					yy = y-out->HeaderN.y/2;
					doffset = x-out->HeaderN.x/2-offset;

					xx       = sqrt(SQR(rmax) - SQR(yy));
					xxoffset = offset - sqrt(SQR(rmax) - SQR(yy)); 
					redgeoffset = sqrt(SQR(xxoffset)+SQR(yy));    	
					w = (ratio*rmax*sqrt(1-SQR(redgeoffset/rmax)) - 0)/(xx - xxoffset) ;

				 	if(fabs(z-out->HeaderN.x/2) < w*(xx - d)) {
						mrcPixelDataGet(out,x,y,0.0,&data,mrcPixelRePart, mrcPixelHowNearest);
						mrcPixelDataSet(out,x,y,0.0,data+1,mrcPixelRePart);
					}
				}

				if(SQR((z-out->HeaderN.x/2)/(ratio*rmax)) + SQR(roffset/rmax) <= 1 
			     && 1<SQR(r/rmax) ) {
					mrcPixelDataGet(out,x,y,0.0,&data,mrcPixelRePart, mrcPixelHowNearest);
					mrcPixelDataSet(out,x,y,0.0,data+1,mrcPixelRePart);
				} else if(SQR(roffset/rmax)<=1 
				     && SQR(r/rmax)<=1 ) {

					d  = x-out->HeaderN.x/2;
					yy = y-out->HeaderN.y/2;
					doffset = x-out->HeaderN.x/2-offset;

					xx       = sqrt(SQR(rmax) - SQR(yy));
					xxoffset = offset - sqrt(SQR(rmax) - SQR(yy)); 
					redge    = sqrt(SQR(offset-xx)+SQR(yy));    	
					
					w = (ratio*rmax*sqrt(1-SQR(redge/rmax)) - 0)/(xx-xxoffset) ;

				 	if(fabs(z-out->HeaderN.x/2) < w*(d-xxoffset)) {
						mrcPixelDataGet(out,x,y,0.0,&data,mrcPixelRePart, mrcPixelHowNearest);
						mrcPixelDataSet(out,x,y,0.0,data+1,mrcPixelRePart);
					}
				}
/*
				if(SQR((z-out->HeaderN.x/2)/(0.7*rmax)) + SQR(roffset/rmax) <= 1 
			     && 1<SQR(r/rmax) 
				 && -0.6*rmax < z-out->HeaderN.x/2.0) {
					mrcPixelDataGet(out,x,y,0.0,&data,mrcPixelRePart, mrcPixelHowNearest);
					mrcPixelDataSet(out,x,y,0.0,data+1,mrcPixelRePart);
				} else if(SQR(roffset/rmax)<=1  
			     &&	SQR(r/rmax) <=1
				 && -0.6*rmax<z-out->HeaderN.x/2.0
				 &&	fabs(z-out->HeaderN.x/2) < sqrt(3)*0.7*(rmax -roffset)) {
					mrcPixelDataGet(out,x,y,0.0,&data,mrcPixelRePart, mrcPixelHowNearest);
					mrcPixelDataSet(out,x,y,0.0,data+1,mrcPixelRePart);
				}
*/				
			}
		}
	}
}	

/*
* SheppLogan 2D
*
*/

void
_lmrcImageModelCreateSheppLogan2D(mrcImage* out)
{
	mrcImageParaTypeReal x, y;
	double srcx, srcy, dsrcx, dsrcy;
	double dstx, dsty;
	double a[10], b[10], theta[10], antitheta, rt[10][2][2], rho[10], dx[10], dy[10];
	double rr, data;
	int i;
	static double ellipses[10][6] =
	//  { delta_x, delta_y,           a,       b,       theta,             rho }
	{  	{       0,       0,        0.69,    0.92,             0.0,      2.0  },
		{       0, -0.0184,        0.6624,  0.874,            0.0,     -0.98 },
		{    0.22,      0.,        0.11,    0.31,     -(M_PI)/10.,     -0.02 },
		{   -0.22,      0.,        0.16,    0.41,      (M_PI)/10.,     -0.02 },
		{       0,    0.35,        0.21,    0.25,               0,      0.01 },
		{       0,     0.1,        0.046,   0.046,              0,      0.01 },
		{      0.,    -0.1,        0.046,   0.046,              0,      0.02 },
		{   -0.08,   -0.605,       0.046,   0.023,              0,      0.01 },
		{      0.,   -0.605,       0.023,   0.023,              0,      0.01 },
		{    0.06,   -0.605,       0.023,   0.046,              0,      0.01 }};

	for(i=0; i<10; i++) {
		dx[i] = ellipses[i][0];
		dy[i] = ellipses[i][1];
		a[i]  = ellipses[i][2];
		b[i]  = ellipses[i][3];
		theta[i] = ellipses[i][4];
		rho[i]   = ellipses[i][5];
		antitheta = - theta[i];
		rt[i][0][0] =  cos(antitheta);
		rt[i][0][1] = -sin(antitheta);
		rt[i][1][0] =  sin(antitheta);
		rt[i][1][1] =  cos(antitheta);
	}
	DEBUGPRINT("_lmrcImageModelCreateSheppLogan2D\n");
	for(y=0; y<out->HeaderN.y; y++) {
		srcy = 2*y/out->HeaderN.y-1.0;
	for(x=0; x<out->HeaderN.x; x++) {
		srcx = 2*x/out->HeaderN.x-1.0;
		for(i=0; i<10; i++) {
			dsrcx = srcx - dx[i];
			dsrcy = srcy - dy[i];
			dstx = dsrcx*rt[i][0][0] + dsrcy*rt[i][0][1];
			dsty = dsrcx*rt[i][1][0] + dsrcy*rt[i][1][1];	

			rr = SQR(dstx/a[i]) + SQR(dsty/b[i]); 	
			if(rr<=1) {
				DEBUGPRINT6("%f %f %f %f %f %f \n", dx[i], dy[i], a[i], b[i], theta[i], rho[i]);
				DEBUGPRINT2("%f %f\n", x, y); 
				mrcPixelDataGet(out, x, y, 0, &data,    mrcPixelRePart, mrcPixelHowNearest);
				mrcPixelDataSet(out, x, y, 0, data+rho[i], mrcPixelRePart);
			}
		}
	}
	}
}


void
_lmrcImageModelCreateSheppLogan3D(mrcImage* out)
{
	mrcImageParaTypeReal x, y, z;
	double srcx, srcy, srcz, dsrcx, dsrcy, dsrcz;
	double dstx, dsty, dstz;
	double a[10], b[10], c[10];
	double theta[10], phi[10], psi[10];
	double rho[10], dx[10], dy[10], dz[10];
	double rt[10][3][3];
	double rr, data;
	int i;
	static double ellipsoids[10][10] =
	// { delta_x, delta_y, delta_z,        a,       b,       c,            phi,  theta,  psi,     rho }
	{   {       0,       0,       0,     0.69,    0.92,     0.9,              0,      0,    0,      2. },
		{       0,       0,       0,   0.6624,   0.874,    0.88,              0,      0,    0,    -0.8 },
		{   -0.22,      0.,   -0.25,     0.41,    0.16,    0.21,    (3*M_PI)/5.,      0,    0,    -0.2 },
		{    0.22,      0.,   -0.25,     0.31,    0.11,    0.22,    (2*M_PI)/5.,      0,    0,    -0.2 },
		{       0,    0.35,   -0.25,     0.21,    0.25,     0.5,              0,      0,    0,     0.2 },
		{       0,     0.1,   -0.25,    0.046,   0.046,   0.046,              0,      0,    0,     0.2 },
		{   -0.08,   -0.65,   -0.25,    0.046,   0.023,    0.02,              0,      0,    0,     0.1 },
		{    0.06,   -0.65,   -0.25,    0.046,   0.023,    0.02,        M_PI/2.,      0,    0,     0.1 },
		{    0.06,  -0.105,   0.625,    0.056,    0.04,     0.1,        M_PI/2.,      0,    0,     0.2 },
		{      0.,     0.1,   0.625,    0.056,   0.056,     0.1,              0,      0,    0,    -0.2 }};


	for(i=0; i<10; i++) {
		Matrix3D mat;
		int j, k; 
	
		dx[i] = ellipsoids[i][0];
		dy[i] = ellipsoids[i][1];
		dz[i] = ellipsoids[i][2];
		a[i]  = ellipsoids[i][3];
		b[i]  = ellipsoids[i][4];
		c[i]  = ellipsoids[i][5];
		phi[i]   = ellipsoids[i][6];
		theta[i] = ellipsoids[i][7];
		psi[i]   = ellipsoids[i][8];
		rho[i]   = ellipsoids[i][9];

		matrix3DRotationSetFollowingEulerAngle(mat, "ZONS", -phi[i], -theta[i], -psi[i], MATRIX_3D_MODE_INITIALIZE);

		for(j=0; j<3; j++) {
		for(k=0; k<3; k++) {
			rt[i][j][k] = mat[j][k];
		}
		}
	}

	for(z=0; z<out->HeaderN.z; z++) {
		srcz = 2*z/out->HeaderN.z-1.0;
	for(y=0; y<out->HeaderN.y; y++) {
		srcy = 2*y/out->HeaderN.y-1.0;
	for(x=0; x<out->HeaderN.x; x++) {
		srcx = 2*x/out->HeaderN.x-1.0;
		for(i=0; i<10; i++) {
			dsrcx = srcx - dx[i];
			dsrcy = srcy - dy[i];
			dsrcz = srcz - dz[i];

			dstx = dsrcx*rt[i][0][0] + dsrcy*rt[i][1][0] + dsrcz*rt[i][2][0];
			dsty = dsrcx*rt[i][0][1] + dsrcy*rt[i][1][1] + dsrcz*rt[i][2][1];
			dstz = dsrcx*rt[i][0][2] + dsrcy*rt[i][1][2] + dsrcz*rt[i][2][2];

			rr = SQR(dstx/a[i]) + SQR(dsty/b[i]) + SQR(dstz/c[i]); 	
			if(rr<=1) {
				mrcPixelDataGet(out, x, y, z, &data,    mrcPixelRePart, mrcPixelHowNearest);
				mrcPixelDataSet(out, x, y, z, data+rho[i], mrcPixelRePart);
			}
		}
	}
	}
	}
}

void
_lmrcImageModelCreateGradientBarX(mrcImage* out, float min, float max)
{
    float x, y, z;
    double gain;
    double data;
    gain = (max - min)/(out->HeaderN.x-1);
	for(z=0; z<out->HeaderN.z; z++) {
	for(y=0; y<out->HeaderN.y; y++) {
	for(x=0; x<out->HeaderN.x; x++) {
        data = x*gain+min; 
        mrcPixelDataSet(out, x, y, z, data, mrcPixelRePart); 
    }
    }
    }
}
