/*
# mrcImageLucasKanade : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : mrcImageLucasKanade
# Attention
#   $Loccker$
#  	$State$ 
#
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"

#define DEBUG
#include "genUtil.h"
#include "mrcImage.h"
#include "Memory.h"

/*
Example:
typedef struct lmrcImageLucasKanadeInfo {
	float a;
	int   b;
} lmrcImageLucasKanadeInfo;

typedef enum lmrcImageLucasKanadeMode {
	a=0,
	b=1
} lmrcImageLucasKanadeMode;
*/

int
main(int argc, char* argv[]) 
{
	mrcImageLucasKanadeInfo info;

	
	int i=5;
	//i=info.NOS;

	mrcImage* InVx;
	mrcImage* InVy;
	mrcImage* InVz;

	/*	
	mrcImage in1Vx, in1Vy, in1Vz;
	mrcImage in2Vx, in2Vy, in2Vz;
	mrcImage in3Vx, in3Vy, in3Vz;
	mrcImage in4Vx, in4Vy, in4Vz;	
	*/

	mrcImage outVx;
	mrcImage outVy;
	mrcImage outVz;
	mrcImage Size;
	
	mrcImage* tmpx;
	mrcImage* tmpy;
	mrcImage* tmpz;

	double x,y,z;
	double data1,data2,data3,data4,data5,data6;
	double size;

	init0(&info);
	argCheck(&info, argc, argv);
	init1(&info);

        DEBUGPRINT("Program Start\n");

    InVx = (mrcImage*)memoryAllocate(sizeof(mrcImage)*info.flagInVxList, "in main");
    InVy = (mrcImage*)memoryAllocate(sizeof(mrcImage)*info.flagInVxList, "in main");
    InVz = (mrcImage*)memoryAllocate(sizeof(mrcImage)*info.flagInVxList, "in main");

    tmpx = (mrcImage*)memoryAllocate(sizeof(mrcImage)*info.flagInVxList, "in main");
    tmpy = (mrcImage*)memoryAllocate(sizeof(mrcImage)*info.flagInVxList, "in main");
    tmpz = (mrcImage*)memoryAllocate(sizeof(mrcImage)*info.flagInVxList, "in main");

	for(i=0; i<info.flagInVxList; i++) {
		mrcFileRead(&(InVx[i]), info.InVxList[i], "in main", 0);
		mrcFileRead(&(InVy[i]), info.InVyList[i], "in main", 0);
		mrcFileRead(&(InVz[i]), info.InVzList[i], "in main", 0);


		tmpx[i].Header = InVx[i].Header;
		tmpy[i].Header = InVy[i].Header;
		tmpz[i].Header = InVz[i].Header;

		mrcInit(&tmpx[i], NULL);
		mrcInit(&tmpy[i], NULL);
		mrcInit(&tmpz[i], NULL);
	}

	outVx.Header = InVx[0].Header;
	outVy.Header = InVx[0].Header;
	outVz.Header = InVx[0].Header;
	Size.Header = InVx[0].Header;

	/*
	mrcFileRead(&in1Vx, info.In1Vx, "in main", 0);
	mrcFileRead(&in1Vy, info.In1Vy, "in main", 0);
	mrcFileRead(&in1Vz, info.In1Vz, "in main", 0);
        
	mrcFileRead(&in2Vx, info.In2Vx, "in main", 0);
        mrcFileRead(&in2Vy, info.In2Vy, "in main", 0);
        mrcFileRead(&in2Vz, info.In2Vz, "in main", 0);

	mrcFileRead(&in3Vx, info.In3Vx, "in main", 0);
        mrcFileRead(&in3Vy, info.In3Vy, "in main", 0);
        mrcFileRead(&in3Vz, info.In3Vz, "in main", 0);

        mrcFileRead(&in4Vx, info.In4Vx, "in main", 0);
        mrcFileRead(&in4Vy, info.In4Vy, "in main", 0);
        mrcFileRead(&in4Vz, info.In4Vz, "in main", 0);

	outVx.Header = in1Vx.Header;
	outVy.Header = in1Vx.Header;
	outVz.Header = in1Vx.Header;
	*/

	mrcInit(&outVx, NULL);
	mrcInit(&outVy, NULL);
	mrcInit(&outVz, NULL);
	mrcInit(&Size, NULL);

	//ピラミダルの計算(inFileList)
	for(i=info.flagInVxList-1; i>0; i--){      


		for(z=0; z<InVx[i].HeaderN.z; z++){
        	        for(y=0; y<InVx[i].HeaderN.y; y++){
                	        for(x=0; x<InVx[i].HeaderN.x; x++){
		
                	                if(info.flagInVxList){
                        	        mrcPixelDataGet(&(InVx[i]), x, y, z, &data1, mrcPixelRePart, mrcPixelHowNearest);
                                	mrcPixelDataGet(&(InVy[i]), x, y, z, &data2, mrcPixelRePart, mrcPixelHowNearest);
	                                mrcPixelDataGet(&(InVz[i]), x, y, z, &data3, mrcPixelRePart, mrcPixelHowNearest);

        	                        mrcPixelDataGet(&outVx, x, y, z, &data4, mrcPixelRePart, mrcPixelHowNearest);
        	                        mrcPixelDataGet(&outVy, x, y, z, &data5, mrcPixelRePart, mrcPixelHowNearest);
        	                        mrcPixelDataGet(&outVz, x, y, z, &data6, mrcPixelRePart, mrcPixelHowNearest);

	                                data1 = 2 * ( data1 + data4 );
	                                data2 = 2 * ( data2 + data5 );
	                                data3 = 2 * ( data3 + data6 );
	                                
//					mrcPixelDataSet(&(InVx[i-1]), 2*x, 2*y, 2*z, data1, mrcPixelRePart);
//	                                mrcPixelDataSet(&(InVy[i-1]), 2*x, 2*y, 2*z, data2, mrcPixelRePart);
//	                                mrcPixelDataSet(&(InVz[i-1]), 2*x, 2*y, 2*z, data3, mrcPixelRePart);

					mrcPixelDataSet(&(tmpx[i]), 2*x, 2*y, 2*z, data1, mrcPixelRePart);
					mrcPixelDataSet(&(tmpy[i]), 2*x, 2*y, 2*z, data2, mrcPixelRePart);
					mrcPixelDataSet(&(tmpz[i]), 2*x, 2*y, 2*z, data3, mrcPixelRePart);
	                                }

	                        }
	                }
	        }
	        for(z=0; z<InVx[i-1].HeaderN.z; z++){
	                for(y=0; y<InVx[i-1].HeaderN.y; y++){
	                        for(x=0; x<InVx[i-1].HeaderN.x; x++){
                        
					mrcPixelDataGet(&(tmpx[i]), x/2.0, y/2.0, z/2.0, &data1, mrcPixelRePart, mrcPixelHowLinear);
					mrcPixelDataSet(&outVx, x, y, z, data1, mrcPixelRePart);

	                                mrcPixelDataGet(&(tmpy[i]), x/2.0, y/2.0, z/2.0, &data1, mrcPixelRePart, mrcPixelHowLinear);
	                                mrcPixelDataSet(&outVy, x, y, z, data1, mrcPixelRePart);
                                        
	                                mrcPixelDataGet(&(tmpz[i]), x/2.0, y/2.0, z/2.0, &data1, mrcPixelRePart, mrcPixelHowLinear);
	                                mrcPixelDataSet(&outVz, x, y, z, data1, mrcPixelRePart);
	                        }
	                }
	        }
	

	}

	for(z=0; z<InVx[i].HeaderN.z; z++){
		for(y=0; y<InVx[i].HeaderN.y; y++){
			for(x=0; x<InVx[i].HeaderN.x; x++){
                                        
				if(info.flagInVxList){
                                mrcPixelDataGet(&(InVx[i]), x, y, z, &data1, mrcPixelRePart, mrcPixelHowNearest);
				mrcPixelDataGet(&(InVy[i]), x, y, z, &data2, mrcPixelRePart, mrcPixelHowNearest);
				mrcPixelDataGet(&(InVz[i]), x, y, z, &data3, mrcPixelRePart, mrcPixelHowNearest);
				
				mrcPixelDataGet(&outVx, x, y, z, &data4, mrcPixelRePart, mrcPixelHowNearest);
				mrcPixelDataGet(&outVy, x, y, z, &data5, mrcPixelRePart, mrcPixelHowNearest);
				mrcPixelDataGet(&outVz, x, y, z, &data6, mrcPixelRePart, mrcPixelHowNearest);

				data1 = 2 * ( data1 + data4 );
				data2 = 2 * ( data2 + data5 );
				data3 = 2 * ( data3 + data6 );
				size = sqrt(data1*data1 + data2*data2 + data3*data3);
					
                                mrcPixelDataSet(&outVx, 2*x, 2*y, 2*z, data1, mrcPixelRePart);
				mrcPixelDataSet(&outVy, 2*x, 2*y, 2*z, data2, mrcPixelRePart);
				mrcPixelDataSet(&outVz, 2*x, 2*y, 2*z, data3, mrcPixelRePart);
				mrcPixelDataSet(&Size, x, y, z, size, mrcPixelRePart);
				
				}

			}
		}
	}


	/*
	for(z=0; z<in4Vx.HeaderN.z; z++){
         	for(y=0; y<in4Vx.HeaderN.y; y++){
              		for(x=0; x<in4Vx.HeaderN.x; x++){
			
				if(info.flagIn4Vx){
				mrcPixelDataGet(&in4Vx, x, y, z, &data1, mrcPixelRePart, mrcPixelHowNearest);
				mrcPixelDataGet(&in4Vy, x, y, z, &data2, mrcPixelRePart, mrcPixelHowNearest);
				mrcPixelDataGet(&in4Vz, x, y, z, &data3, mrcPixelRePart, mrcPixelHowNearest);
				data1 = 2 * data1;
				data2 = 2 * data2;
				data3 = 2 * data3;
				}
			
				if(info.flagIn3Vx){
				mrcPixelDataSet(&in3Vx, x+2, y+2, z+2, data1, mrcPixelRePart);
				mrcPixelDataSet(&in3Vy, x+2, y+2, z+2, data2, mrcPixelRePart);
				mrcPixelDataSet(&in3Vz, x+2, y+2, z+2, data3, mrcPixelRePart);
				}

			}
		}
	}
	for(z=0; z<in3Vx.HeaderN.z; z++){
        	for(y=0; y<in3Vx.HeaderN.y; y++){
			for(x=0; x<in3Vx.HeaderN.x; x++){
			
				if( ((int)x%2) != 0 && ((int)y%2) != 0 && ((int)z%2) != 0 ){
					mrcPixelDataGet(&in3Vx, x+1, y, z, &data1, mrcPixelRePart, mrcPixelHowNearest);
					mrcPixelDataGet(&in3Vx, x-1, y, z, &data2, mrcPixelRePart, mrcPixelHowNearest);
					mrcPixelDataGet(&in3Vx, x, y+1, z, &data3, mrcPixelRePart, mrcPixelHowNearest);
					mrcPixelDataGet(&in3Vx, x, y-1, z, &data4, mrcPixelRePart, mrcPixelHowNearest);
					mrcPixelDataGet(&in3Vx, x, y, z+1, &data5, mrcPixelRePart, mrcPixelHowNearest);
					mrcPixelDataGet(&in3Vx, x, y, z-1, &data6, mrcPixelRePart, mrcPixelHowNearest);
					
					data1 = (data1 + data2 + data3 + data4 + data5 + data6) / 6;
					mrcPixelDataSet(&outVx, x, y, z, data1, mrcPixelRePart);


					mrcPixelDataGet(&in3Vy, x+1, y, z, &data1, mrcPixelRePart, mrcPixelHowNearest);
                                        mrcPixelDataGet(&in3Vy, x-1, y, z, &data2, mrcPixelRePart, mrcPixelHowNearest);
                                        mrcPixelDataGet(&in3Vy, x, y+1, z, &data3, mrcPixelRePart, mrcPixelHowNearest);
                                        mrcPixelDataGet(&in3Vy, x, y-1, z, &data4, mrcPixelRePart, mrcPixelHowNearest);
                                        mrcPixelDataGet(&in3Vy, x, y, z+1, &data5, mrcPixelRePart, mrcPixelHowNearest);
                                        mrcPixelDataGet(&in3Vy, x, y, z-1, &data6, mrcPixelRePart, mrcPixelHowNearest);

                                        data1 = (data1 + data2 + data3 + data4 + data5 + data6) / 6;
                                        mrcPixelDataSet(&outVy, x, y, z, data1, mrcPixelRePart);
					

                                        mrcPixelDataGet(&in3Vz, x+1, y, z, &data1, mrcPixelRePart, mrcPixelHowNearest);
                                        mrcPixelDataGet(&in3Vz, x-1, y, z, &data2, mrcPixelRePart, mrcPixelHowNearest);
                                        mrcPixelDataGet(&in3Vz, x, y+1, z, &data3, mrcPixelRePart, mrcPixelHowNearest);
                                        mrcPixelDataGet(&in3Vz, x, y-1, z, &data4, mrcPixelRePart, mrcPixelHowNearest);
                                        mrcPixelDataGet(&in3Vz, x, y, z+1, &data5, mrcPixelRePart, mrcPixelHowNearest);
                                        mrcPixelDataGet(&in3Vz, x, y, z-1, &data6, mrcPixelRePart, mrcPixelHowNearest);

                                        data1 = (data1 + data2 + data3 + data4 + data5 + data6) / 6;
                                        mrcPixelDataSet(&outVz, x, y, z, data1, mrcPixelRePart);
				}
			}
		}
	}






	for(z=0; z<in3Vx.HeaderN.z; z++){
                for(y=0; y<in3Vx.HeaderN.y; y++){
                        for(x=0; x<in3Vx.HeaderN.x; x++){

                                if(info.flagIn3Vx){
				mrcPixelDataGet(&in3Vx, x, y, z, &data1, mrcPixelRePart, mrcPixelHowNearest);
                                mrcPixelDataGet(&in3Vy, x, y, z, &data2, mrcPixelRePart, mrcPixelHowNearest);
                                mrcPixelDataGet(&in3Vz, x, y, z, &data3, mrcPixelRePart, mrcPixelHowNearest);

				mrcPixelDataGet(&outVx, x, y, z, &data4, mrcPixelRePart, mrcPixelHowNearest);
				mrcPixelDataGet(&outVy, x, y, z, &data5, mrcPixelRePart, mrcPixelHowNearest);
				mrcPixelDataGet(&outVz, x, y, z, &data6, mrcPixelRePart, mrcPixelHowNearest);

                                data1 =2 * ( data1 + data4 );
                                data2 =2 * ( data2 + data5 );
                                data3 =2 * ( data3 + data6 );
				}

                                if(info.flagIn2Vx){
                                mrcPixelDataSet(&in2Vx, x+2, y+2, z+2, data1, mrcPixelRePart);
                                mrcPixelDataSet(&in2Vy, x+2, y+2, z+2, data2, mrcPixelRePart);
				mrcPixelDataSet(&in2Vz, x+2, y+2, z+2, data3, mrcPixelRePart);
				}

                        }
                }
        }
        for(z=0; z<in2Vx.HeaderN.z; z++){
                for(y=0; y<in2Vx.HeaderN.y; y++){
                        for(x=0; x<in2Vx.HeaderN.x; x++){

                                if( ((int)x%2) != 0 && ((int)y%2) != 0 && ((int)z%2) != 0 ){
                                        mrcPixelDataGet(&in2Vx, x+1, y, z, &data1, mrcPixelRePart, mrcPixelHowNearest);
                                        mrcPixelDataGet(&in2Vx, x-1, y, z, &data2, mrcPixelRePart, mrcPixelHowNearest);
                                        mrcPixelDataGet(&in2Vx, x, y+1, z, &data3, mrcPixelRePart, mrcPixelHowNearest);
                                        mrcPixelDataGet(&in2Vx, x, y-1, z, &data4, mrcPixelRePart, mrcPixelHowNearest);
                                        mrcPixelDataGet(&in2Vx, x, y, z+1, &data5, mrcPixelRePart, mrcPixelHowNearest);
                                        mrcPixelDataGet(&in2Vx, x, y, z-1, &data6, mrcPixelRePart, mrcPixelHowNearest);

                                        data1 = (data1 + data2 + data3 + data4 + data5 + data6) / 6;
                                        mrcPixelDataSet(&outVx, x, y, z, data1, mrcPixelRePart);


                                        mrcPixelDataGet(&in2Vy, x+1, y, z, &data1, mrcPixelRePart, mrcPixelHowNearest);
                                        mrcPixelDataGet(&in2Vy, x-1, y, z, &data2, mrcPixelRePart, mrcPixelHowNearest);
                                        mrcPixelDataGet(&in2Vy, x, y+1, z, &data3, mrcPixelRePart, mrcPixelHowNearest);
                                        mrcPixelDataGet(&in2Vy, x, y-1, z, &data4, mrcPixelRePart, mrcPixelHowNearest);
                                        mrcPixelDataGet(&in2Vy, x, y, z+1, &data5, mrcPixelRePart, mrcPixelHowNearest);
                                        mrcPixelDataGet(&in2Vy, x, y, z-1, &data6, mrcPixelRePart, mrcPixelHowNearest);

                                        data1 = (data1 + data2 + data3 + data4 + data5 + data6) / 6;
                                        mrcPixelDataSet(&outVy, x, y, z, data1, mrcPixelRePart);


                                        mrcPixelDataGet(&in2Vz, x+1, y, z, &data1, mrcPixelRePart, mrcPixelHowNearest);
                                        mrcPixelDataGet(&in2Vz, x-1, y, z, &data2, mrcPixelRePart, mrcPixelHowNearest);
                                        mrcPixelDataGet(&in2Vz, x, y+1, z, &data3, mrcPixelRePart, mrcPixelHowNearest);
                                        mrcPixelDataGet(&in2Vz, x, y-1, z, &data4, mrcPixelRePart, mrcPixelHowNearest);
                                        mrcPixelDataGet(&in2Vz, x, y, z+1, &data5, mrcPixelRePart, mrcPixelHowNearest);
                                        mrcPixelDataGet(&in2Vz, x, y, z-1, &data6, mrcPixelRePart, mrcPixelHowNearest);

                                        data1 = (data1 + data2 + data3 + data4 + data5 + data6) / 6;
                                        mrcPixelDataSet(&outVz, x, y, z, data1, mrcPixelRePart);
                                }

			}
		}
	}







        for(z=0; z<in2Vx.HeaderN.z; z++){
                for(y=0; y<in2Vx.HeaderN.y; y++){
                        for(x=0; x<in2Vx.HeaderN.x; x++){

                                if(info.flagIn2Vx){
                                mrcPixelDataGet(&in2Vx, x, y, z, &data1, mrcPixelRePart, mrcPixelHowNearest);
                                mrcPixelDataGet(&in2Vy, x, y, z, &data2, mrcPixelRePart, mrcPixelHowNearest);
                                mrcPixelDataGet(&in2Vz, x, y, z, &data3, mrcPixelRePart, mrcPixelHowNearest);

                                mrcPixelDataGet(&outVx, x, y, z, &data4, mrcPixelRePart, mrcPixelHowNearest);
                                mrcPixelDataGet(&outVy, x, y, z, &data5, mrcPixelRePart, mrcPixelHowNearest);
                                mrcPixelDataGet(&outVz, x, y, z, &data6, mrcPixelRePart, mrcPixelHowNearest);

                                data1 = 2 * ( data1 + data4 );
                                data2 = 2 * ( data2 + data5 );
                                data3 = 2 * ( data3 + data6 );
                                }

                                if(info.flagIn1Vx){
                                mrcPixelDataSet(&in1Vx, x+2, y+2, z+2, data1, mrcPixelRePart);
                                mrcPixelDataSet(&in1Vy, x+2, y+2, z+2, data2, mrcPixelRePart);
                                mrcPixelDataSet(&in1Vz, x+2, y+2, z+2, data3, mrcPixelRePart);
                                }

                        }
                }
        }
        for(z=0; z<in1Vx.HeaderN.z; z++){
                for(y=0; y<in1Vx.HeaderN.y; y++){
                        for(x=0; x<in1Vx.HeaderN.x; x++){

                                if( ((int)x%2) != 0 && ((int)y%2) != 0 && ((int)z%2) != 0 ){
                                        mrcPixelDataGet(&in1Vx, x+1, y, z, &data1, mrcPixelRePart, mrcPixelHowNearest);
                                        mrcPixelDataGet(&in1Vx, x-1, y, z, &data2, mrcPixelRePart, mrcPixelHowNearest);
                                        mrcPixelDataGet(&in1Vx, x, y+1, z, &data3, mrcPixelRePart, mrcPixelHowNearest);
                                        mrcPixelDataGet(&in1Vx, x, y-1, z, &data4, mrcPixelRePart, mrcPixelHowNearest);
                                        mrcPixelDataGet(&in1Vx, x, y, z+1, &data5, mrcPixelRePart, mrcPixelHowNearest);
                                        mrcPixelDataGet(&in1Vx, x, y, z-1, &data6, mrcPixelRePart, mrcPixelHowNearest);

                                        data1 = (data1 + data2 + data3 + data4 + data5 + data6) / 6;
                                        mrcPixelDataSet(&outVx, x, y, z, data1, mrcPixelRePart);


                                        mrcPixelDataGet(&in1Vy, x+1, y, z, &data1, mrcPixelRePart, mrcPixelHowNearest);
                                        mrcPixelDataGet(&in1Vy, x-1, y, z, &data2, mrcPixelRePart, mrcPixelHowNearest);
                                        mrcPixelDataGet(&in1Vy, x, y+1, z, &data3, mrcPixelRePart, mrcPixelHowNearest);
                                        mrcPixelDataGet(&in1Vy, x, y-1, z, &data4, mrcPixelRePart, mrcPixelHowNearest);
                                        mrcPixelDataGet(&in1Vy, x, y, z+1, &data5, mrcPixelRePart, mrcPixelHowNearest);
                                        mrcPixelDataGet(&in1Vy, x, y, z-1, &data6, mrcPixelRePart, mrcPixelHowNearest);

                                        data1 = (data1 + data2 + data3 + data4 + data5 + data6) / 6;
                                        mrcPixelDataSet(&outVy, x, y, z, data1, mrcPixelRePart);


                                        mrcPixelDataGet(&in1Vz, x+1, y, z, &data1, mrcPixelRePart, mrcPixelHowNearest);
                                        mrcPixelDataGet(&in1Vz, x-1, y, z, &data2, mrcPixelRePart, mrcPixelHowNearest);
                                        mrcPixelDataGet(&in1Vz, x, y+1, z, &data3, mrcPixelRePart, mrcPixelHowNearest);
                                        mrcPixelDataGet(&in1Vz, x, y-1, z, &data4, mrcPixelRePart, mrcPixelHowNearest);
                                        mrcPixelDataGet(&in1Vz, x, y, z+1, &data5, mrcPixelRePart, mrcPixelHowNearest);
                                        mrcPixelDataGet(&in1Vz, x, y, z-1, &data6, mrcPixelRePart, mrcPixelHowNearest);

                                        data1 = (data1 + data2 + data3 + data4 + data5 + data6) / 6;
                                        mrcPixelDataSet(&outVz, x, y, z, data1, mrcPixelRePart);
                                }

			}
		}
	}*/





	if(info.flagoutVx){
		mrcFileWrite(&outVx, info.outVx, "in main", 0);
        	mrcFileWrite(&outVy, info.outVy, "in main", 0);
        	mrcFileWrite(&outVz, info.outVz, "in main", 0);
	}

	if(info.flagSize) {
        	mrcFileWrite(&Size, info.Size, "in main", 0);
	}
	return 0;	

}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
}
