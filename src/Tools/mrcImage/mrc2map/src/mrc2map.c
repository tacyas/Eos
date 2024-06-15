#include <stdio.h>
#include <stdlib.h>
#include <math.h>
       
#include "../inc/config.h"
#define DEBUG
#include "genUtil.h"
#include "Memory.h"
#include "mrcImage.h"

typedef struct shortCoord {
	short x;
	short y;
	short z;
} shortCoord;

typedef struct mapHeader {
	shortCoord Start;
	shortCoord N;
	shortCoord M;
	shortCoord Length; /* x i1 */
	shortCoord Angle;  /* x i1 */
	short prod;        /* x i2 */
	short plus;
	short i1;
	short i2;
	short dummy[256-19];
} mapHeader;

typedef struct lmrc2mapInfo {
	float shiftx;
	float shifty;
	float shiftz;
	int   noSwap;
} lmrc2mapInfo;

extern void lmrc2map(FILE* fpt, mrcImage* img, lmrc2mapInfo linfo, long mode);

int
main(int argc, char* argv[])
{
    mrcImage img;
	mrc2mapInfo   info;
	lmrc2mapInfo  linfo;

    init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	linfo.shiftx = info.shiftx;
	linfo.shifty = info.shifty;
	linfo.shiftz = info.shiftz;
	linfo.noSwap = info.noswap;
    mrcFileRead(&img, info.In, "from Main Routine", 0);
	if(info.flagmul) {
		DEBUGPRINT1("MUL: %e\n", info.mul);
		lmrcImageDividedByReal(&img, 1.0/info.mul);
		mrcStatDataSet(&img, 0);
	}
	lmrc2map(info.fptOut, &img, linfo, info.mode);
	return 0; 
}

void
additionalUsage()
{
}

void 
lmrc2map(FILE* fpt, mrcImage* img, lmrc2mapInfo linfo, long mode)
{
	int i, x, y, z, i1, i2;
	int qx, qy, qz, qx2, qy2, qz2, qnx, qny, qnz, n;
	double data, plus, prod;
	mapHeader map;
	unsigned char record[8*8*8], uctmp;
	unsigned char* rhobyte;
	int itmp;

	i1 = 100;
	i2 = 100;
	if(img->HeaderAMax - img->HeaderAMin <=0) {
		mrcStatDataSet(img, 0);
	}
	prod = 254.0/(img->HeaderAMax - img->HeaderAMin);
	plus = (int)(0.5 - (prod*img->HeaderAMin));
	if(mode==0) {
		map.Start.x = img->HeaderStartN.x;
		map.Start.y = img->HeaderStartN.y;
		map.Start.z = img->HeaderStartN.z;
	} else if(mode==1) {
		if(img->HeaderN.x%2==0) {
			map.Start.x = img->HeaderStartN.x - (img->HeaderN.x - 0)/2;
		} else {
			map.Start.x = img->HeaderStartN.x - (img->HeaderN.x - 1)/2;
		}
		if(img->HeaderN.y%2==0) {
			map.Start.y = img->HeaderStartN.y - (img->HeaderN.y - 0)/2;
		} else {
			map.Start.y = img->HeaderStartN.y - (img->HeaderN.y - 1)/2;
		}
		map.Start.z = img->HeaderStartN.z;
	} else if(mode==2) {
		map.Start.x = 0;
		map.Start.y = 0;
		map.Start.z = 0;
	} else if(mode==3) {
		if(img->HeaderN.x%2==0) {
			map.Start.x = img->HeaderStartN.x - (img->HeaderN.x - 0)/2;
		} else {
			map.Start.x = img->HeaderStartN.x - (img->HeaderN.x - 1)/2;
		}
		if(img->HeaderN.y%2==0) {
			map.Start.y = img->HeaderStartN.y - (img->HeaderN.y - 0)/2;
		} else {
			map.Start.y = img->HeaderStartN.y - (img->HeaderN.y - 1)/2;
		}
		if(img->HeaderN.z%2==0) {
			map.Start.z = img->HeaderStartN.z - (img->HeaderN.z - 0)/2;
		} else {
			map.Start.z = img->HeaderStartN.z - (img->HeaderN.z - 1)/2;
		}
	}

	map.Start.x += floor(linfo.shiftx/img->HeaderLength.x + 0.5);
	map.Start.y += floor(linfo.shifty/img->HeaderLength.y + 0.5);
	map.Start.z += floor(linfo.shiftz/img->HeaderLength.z + 0.5);

	map.N.x     = img->HeaderN.x;
	map.N.y     = img->HeaderN.y;
	map.N.z     = img->HeaderN.z;
	DEBUGPRINT3("N: %d %d %d\n", map.N.x, map.N.y, map.N.z);
	if(img->HeaderM.x!=0) {
		map.M.x     = img->HeaderM.x;
	} else {
		map.M.x     = 1;
	}
	if(img->HeaderM.y!=0) {
		map.M.y     = img->HeaderM.y;
	} else {
		map.M.y     = 1;
	}
	if(img->HeaderM.z!=0) {
		map.M.z     = img->HeaderM.z;
	} else {
		map.M.z     = 1;
	}
	map.Length.x = img->HeaderLength.x*i1;
	map.Length.y = img->HeaderLength.y*i1;
	map.Length.z = img->HeaderLength.z*i1;
	if(img->HeaderAlpha!=0) {
		map.Angle.x  = img->HeaderAlpha*i1; 
	} else {
		map.Angle.x  = 90*i1; 
	}
	if(img->HeaderBeta!=0) {
		map.Angle.y  = img->HeaderBeta *i1;
	} else { 
		map.Angle.y  = 90*i1;
	}
	if(img->HeaderGamma!=0) {
		map.Angle.z  = img->HeaderGamma*i1;
	} else {
		map.Angle.z  = 90*i1;
	}
	map.prod = prod*i2;
	map.plus = plus;
	map.i1 = i1;
	map.i2 = i2;
    for(i=0; i<256-19; i++) {
		map.dummy[i] = 0;
	}
	fseek(fpt, 0L, SEEK_SET);

#ifdef II
	if(linfo.noSwap) {
	} else {
		memoryByteSwap(&map, sizeof(short), sizeof(map)/sizeof(short));
	}
#endif
	fwrite(&map, sizeof(map), 1, fpt);
#ifdef II
	if(linfo.noSwap) {
	} else {
		memoryByteSwap(&map, sizeof(short), sizeof(map)/sizeof(short));
	}
#endif

    qnx = map.N.x/8; if(qnx*8!=map.N.x) { qnx += 1; }
    qny = map.N.y/8; if(qny*8!=map.N.y) { qny += 1; }
    qnz = map.N.z/8; if(qnz*8!=map.N.z) { qnz += 1; }
	n = qnx*8*qny*8*qnz*8;
	rhobyte=(unsigned char*)memoryAllocate(sizeof(unsigned char)*n, "in lmrc2map");
	
	for(i=0; i<n; i++) {
		rhobyte[i] = 0;
	}
	for(x=0; x<map.N.x; x++) {
		for(y=0; y<map.N.y; y++) {
			for(z=0; z<map.N.z; z++) {
				mrcPixelDataGet(img, x, y, z, &data, mrcPixelMag, mrcPixelHowNearest);
				itmp = data*prod + plus + 0.5;
				if(itmp>255) {
					itmp = 255;
				} else if (itmp<0) {
					itmp = 0;
				}
				rhobyte[x+qnx*8*y+qnx*8*qny*8*z] = (unsigned char)itmp;
			}
		}
	}

	for(qz=0; qz<qnz; qz++) {
		for(qy=0; qy<qny; qy++) {
			for(qx=0; qx<qnx; qx++) {
				for(qz2=0; qz2<8; qz2++) {
					for(qy2=0; qy2<8; qy2++) {
						for(qx2=0; qx2<8; qx2+=2) {
							x = qx*8 + qx2;
							y = qy*8 + qy2;
							z = qz*8 + qz2;
							record[qx2+1+qy2*8+qz2*8*8] = rhobyte[x   + y*qnx*8 + z*qnx*8*qny*8];
							record[qx2  +qy2*8+qz2*8*8] = rhobyte[x+1 + y*qnx*8 + z*qnx*8*qny*8];
						}
					}
				}
				fwrite(record, sizeof(unsigned char), 8*8*8, fpt);
			}
		}
	}
}
