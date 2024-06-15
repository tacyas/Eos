/*
# lmrcImageLabeling : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : lmrcImageLabeling 
# Attention
#   $Loccker$
#  	$State$ 
#
*/
/* $Log$ */

#undef DEBUG
#include "genUtil.h"
#include "Memory.h"
#include "./lmrcImageLabeling.h"

void
lmrcImageLabelingUsage(FILE* fpt)
{
	fprintf(fpt, "mode: 0 (default: speed)\n");
	fprintf(fpt, "      1 (No vacancy)\n");
}

void
lmrcImageLabelingOrder(mrcImage* dst, int mode)
{
	mrcImageParaTypeReal x, y, z;
	int max;
	int* num;
	int* newlabel;
	int i, j;
	double data;

	DEBUGPRINT("lmrcImageLabelingOrder\n");
	max = 0;
	for(z=0; z<dst->HeaderN.z; z++) {
	for(y=0; y<dst->HeaderN.y; y++) {
	for(x=0; x<dst->HeaderN.x; x++) {
		mrcPixelDataGet(dst, x, y, z, &data, mrcPixelRePart, mrcPixelHowNearest);		
		if(max<data) {
			max = data;
		}
	}
	}
	}
	num = (int*)memoryAllocate(sizeof(int)*(max+1), "in lmrcImageLabelingOrder");
	newlabel = (int*)memoryAllocate(sizeof(int)*(max+1), "in lmrcImageLabelingOrder");
	for(i=0; i<=max; i++) {
		num[i]=0;
		newlabel[i]=0;
	}

	for(z=0; z<dst->HeaderN.z; z++) {
	for(y=0; y<dst->HeaderN.y; y++) {
	for(x=0; x<dst->HeaderN.x; x++) {
		mrcPixelDataGet(dst, x, y, z, &data, mrcPixelRePart, mrcPixelHowNearest);		
		i = (int)(data+0.5);
		num[i]++;
	}
	}
	}

	for(i=1, j=1; i<=max; i++) {
		DEBUGPRINT3("%d/%d: %d \n", i, max, num[i]);
		if(num[i]!=0) {
			newlabel[i] = j;
			DEBUGPRINT4("%d <- %d: %d max %d\n", j, i, num[i], max);
			j++;
		}
	}
	dst->HeaderAMax = j;	

	for(z=0; z<dst->HeaderN.z; z++) {
	for(y=0; y<dst->HeaderN.y; y++) {
	for(x=0; x<dst->HeaderN.x; x++) {
		mrcPixelDataGet(dst, x, y, z, &data, mrcPixelRePart, mrcPixelHowNearest);		
		if(0<data) {
			mrcPixelDataSet(dst, x, y, z, newlabel[(int)(data+0.5)], mrcPixelRePart);
		}
	}
	}
	}
}

void
lmrcImageLabeling(mrcImage* label, mrcImage* in, int neighbor, int mode)
{
	if(1==in->HeaderN.z) {
		lmrcImageLabeling2D(label, in, neighbor, mode);
	} else {
		lmrcImageLabeling3D(label, in, neighbor, mode);
	}

	switch(mode) {
		case 1: {
			lmrcImageLabelingOrder(label, mode);
			break;
		}
	}
}

void
lmrcImageLabeling2D(mrcImage* label, mrcImage* in, int neighbor, int mode)
{
	mrcImageParaTypeReal x, y, z;
	mrcImageParaTypeReal srcx, srcy, srcz;
	double data, mindata, data0, data1, data2, data3, data4;
	int number, total, max;

	if(neighbor==0) {
		neighbor = 4;
	}

	DEBUGPRINT("lmrcImageLabeling Start\n");
	label->Header = in->Header;
	mrcInit(label, NULL);

	for(y=0; y<in->HeaderN.y; y++) {
	for(x=0; x<in->HeaderN.x; x++) {
		mrcPixelDataSet(label, x, y, 0, 0.0, mrcPixelRePart);
	}
	}

	number = 0;
	max = 0;
	while(1) {
		total = 0;
		for(y=0; y<in->HeaderN.y; y++) {
		for(x=0; x<in->HeaderN.x; x++) {
			mrcPixelDataGet(in, x, y, 0, &data, mrcPixelRePart, mrcPixelHowNearest);
			if(1e-6<data) {
				switch(neighbor) {
					case 4: {
						mrcPixelDataGet(label, x,                       y,                         0, &data0, mrcPixelRePart, mrcPixelHowNearest);
						mrcPixelDataGet(label, x,                       MIN(in->HeaderN.y-1,y+1),  0, &data1, mrcPixelRePart, mrcPixelHowNearest);
						mrcPixelDataGet(label, x,                       MAX(0,y-1),                0, &data2, mrcPixelRePart, mrcPixelHowNearest);
						mrcPixelDataGet(label, MAX(0,x-1),               y, 0, &data3, mrcPixelRePart, mrcPixelHowNearest);
						mrcPixelDataGet(label, MIN(in->HeaderN.x-1,x+1), y, 0, &data4, mrcPixelRePart, mrcPixelHowNearest);
						
						if(data0<1e-6 && data1<1e-6 && data2<1e-6 && data3<1e-6 && data4<1e-6) {
							number++;
#ifdef DEBUG2
							DEBUGPRINT1("NUMBER: %d\n", number)
#endif
							mrcPixelDataSet(label, x, y, 0, number, mrcPixelRePart);
							total++;
						} else if(1e-6<data1 || 1e-6<data2 || 1e-6<data3 || 1e-6<data4) {
							mindata = data0;
							if(1e-6<data1) {
								if(1e-6<mindata) {
									mindata = MIN(mindata, data1);
								} else {
									mindata = data1;
								}
							}
							if(1e-6<data2) {
								if(1e-6<mindata) {
									mindata = MIN(mindata, data2);
								} else {
									mindata = data2;
								}
							}
							if(1e-6<data3) {
								if(1e-6<mindata) {
									mindata = MIN(mindata, data3);
								} else {
									mindata = data3;
								}
							}
							if(1e-6<data4) {
								if(1e-6<mindata) {
									mindata = MIN(mindata, data4);
								} else {
									mindata = data4;
								}
							}
							if(mindata!=data0) {
								mrcPixelDataSet(label, x, y, 0, (int)(mindata+0.5), mrcPixelRePart);
								total++;
							}
						}
						break;
					} // case 4:
					case 8: {
						mindata = 0;
						for(srcy=MAX(0,y-1); srcy<=MIN(label->HeaderN.y-1,y+1); srcy++) {		
						for(srcx=MAX(0,x-1); srcx<=MIN(label->HeaderN.x-1,x+1); srcx++) {		
							mrcPixelDataGet(label, srcx, srcy, 0, &data0, mrcPixelRePart, mrcPixelHowNearest);
							if(1e-6<data0) {
								if(mindata==0 || data0<mindata) {
									mindata = data0;
								}
							}
						}
						}
						if(mindata==0) {
							number++;
							mrcPixelDataSet(label, x, y, 0, number, mrcPixelRePart);
							total++;
						} else {
							mrcPixelDataGet(label, x, y, 0, &data0, mrcPixelRePart, mrcPixelHowNearest);
							if(data0!=mindata) {
								mrcPixelDataSet(label, x, y, 0, mindata, mrcPixelRePart);
								total++;
							}
						}
						break;
					}
					default: {
						fprintf(stderr, "Not supported neighbor: %d\n", neighbor);
						exit(EXIT_FAILURE);
						break;
					}
				} // switch	
			} // data=1 
		}
		}

		DEBUGPRINT1("Total: %d\n", total);
		if(0==total) {
			break;
		}
	}
}

void
lmrcImageLabeling3D(mrcImage* label, mrcImage* in, int neighbor, int mode)
{
	mrcImageParaTypeReal x, y, z;
	mrcImageParaTypeReal srcx, srcy, srcz;
	double data, mindata, data0;
	double labeldata[7];
	int number, total;
	int flag, i;
	int direction;
	DEBUGPRINT("lmrcImageLabeling Start\n");
	label->Header = in->Header;
	mrcInit(label, NULL);

	if(neighbor==0) {
		neighbor=6;
	}
	for(z=0; z<in->HeaderN.z; z++) {
	for(y=0; y<in->HeaderN.y; y++) {
	for(y=0; y<in->HeaderN.y; y++) {
		mrcPixelDataSet(label, x, y, z, 0.0, mrcPixelRePart);
	}
	}
	}

	number = 0;
	do {
		total = 0;
		for(direction=0; direction<2; direction++) {
			int startx, starty, startz;
			int endx, endy, endz;
			int delx, dely, delz;

			switch(direction) {
				case 0: {
					startx = 0;
					starty = 0;
					startz = 0;
					endx = in->HeaderN.x;
					endy = in->HeaderN.y;
					endz = in->HeaderN.z;
					delx = 1;
					dely = 1;
					delz = 1;
					break;
				}
				case 1: {
					startx = in->HeaderN.x - 1;
					starty = in->HeaderN.y - 1;
					startz = in->HeaderN.z - 1;
					endx = -1;
					endy = -1;
					endz = -1;
					delx = -1;
					dely = -1;
					delz = -1;
					break;
				}
			}
		for(z=startz; 0<delz*(endz-z); z+=delz) {
		for(y=starty; 0<dely*(endy-y); y+=dely) {
		for(x=startx; 0<delx*(endx-x); x+=delx) {
			mrcPixelDataGet(in, x, y, z, &data, mrcPixelRePart, mrcPixelHowNearest);
			if(1e-6<data) { /* Must Be Labelled */
				switch(neighbor) {
					case 6: {
						mrcPixelDataGet(label, x,                        y,                         z, &labeldata[0], mrcPixelRePart, mrcPixelHowNearest);
						mrcPixelDataGet(label, x,                        y,  MAX(0,z-1),               &labeldata[1], mrcPixelRePart, mrcPixelHowNearest);
						mrcPixelDataGet(label, x,                        y,  MIN(in->HeaderN.z-1,z+1), &labeldata[2], mrcPixelRePart, mrcPixelHowNearest);
						mrcPixelDataGet(label, x,                        MAX(0,y-1),                z, &labeldata[3], mrcPixelRePart, mrcPixelHowNearest);
						mrcPixelDataGet(label, x,                        MIN(in->HeaderN.y-1,y+1),  z, &labeldata[4], mrcPixelRePart, mrcPixelHowNearest);
						mrcPixelDataGet(label, MAX(0,x-1),               y,                         z, &labeldata[5], mrcPixelRePart, mrcPixelHowNearest);
						mrcPixelDataGet(label, MIN(in->HeaderN.x-1,x+1), y,                         z, &labeldata[6], mrcPixelRePart, mrcPixelHowNearest);
						flag = 0;
						for(i=1; i < 7; i++) {
							if(1e-6<labeldata[i]) {
								flag++;
							}
						}
						if(labeldata[0] < 1e-6 && flag==0) {
							number++;
#ifdef DEBUG2
							DEBUGPRINT1("NUMBER: %d\n", number)
#endif
							mrcPixelDataSet(label, x, y, z, number, mrcPixelRePart);
						} else if(0<flag) { 
							mindata = labeldata[0];
							for(i=1; i<7; i++) {
								if(1e-6<labeldata[i]) {
									if(1e-6<mindata) {
										mindata = MIN(mindata, labeldata[i]);
									} else {
										mindata = labeldata[i];
									}
								}
							}
							mrcPixelDataSet(label, x, y, z, (int)(mindata+0.5), mrcPixelRePart);
							if(mindata!=labeldata[0]) {
								total++;
							}
						}
						break;
					}
					case 18: {
						mindata = 0;
						for(srcz=MAX(0,z-1); srcz<=MIN(label->HeaderN.z-1,z+1); srcz++) {
						for(srcy=MAX(0,y-1); srcy<=MIN(label->HeaderN.y-1,y+1); srcy++) {
						for(srcx=MAX(0,x-1); srcx<=MIN(label->HeaderN.x-1,x+1); srcx++) {
							if(fabs((srcx-x)*(srcy-y)*(srcz-z))<=1e-6) { 
								mrcPixelDataGet(label, srcx, srcy, srcz, &data0, mrcPixelRePart, mrcPixelHowNearest);
								if(1e-6<data0) {
									if(mindata ==0 || data0 < mindata) {
										mindata = data0;
									}
								}
							}
						}
						}
						}
						if(mindata==0) {
							number++;
							mrcPixelDataSet(label, x, y, z, number, mrcPixelRePart);
							total++;
						} else {
							mrcPixelDataGet(label, x, y, z, &data0, mrcPixelRePart, mrcPixelHowNearest);
							if(data0 != mindata) {
								mrcPixelDataSet(label, x, y, z, mindata, mrcPixelRePart);
								total++;
							}
						}
						break;
					}
					case 26: {
						mindata = 0;
						for(srcz=MAX(0,z-1); srcz<=MIN(label->HeaderN.z-1,z+1); srcz++) {
						for(srcy=MAX(0,y-1); srcy<=MIN(label->HeaderN.y-1,y+1); srcy++) {
						for(srcx=MAX(0,x-1); srcx<=MIN(label->HeaderN.x-1,x+1); srcx++) {
							mrcPixelDataGet(label, srcx, srcy, srcz, &data0, mrcPixelRePart, mrcPixelHowNearest);
							if(1e-6<data0) {
								if(mindata ==0 || data0 < mindata) {
									mindata = data0;
								}
							}
						}
						}
						}
						if(mindata==0) {
							number++;
							mrcPixelDataSet(label, x, y, z, number, mrcPixelRePart);
							total++;
						} else {
							mrcPixelDataGet(label, x, y, z, &data0, mrcPixelRePart, mrcPixelHowNearest);
							if(data0 != mindata) {
								mrcPixelDataSet(label, x, y, z, mindata, mrcPixelRePart);
								total++;
							}
						}
						break;
					}
					default: {
						fprintf(stderr, "Not supported neighbor: %d\n", neighbor);
						exit(EXIT_FAILURE);
						break;
					}
				} // switch
			} // data == 1
		}
		}
		}
		}
		DEBUGPRINT2("Total: %d Number: %d\n", total, number);
	} while(total!=0);  

	label->HeaderAMax = number;
}
