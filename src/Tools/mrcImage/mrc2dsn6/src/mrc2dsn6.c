#include <stdio.h>
#include <stdlib.h>
#include <math.h>
       
#include "../inc/config.h"
#define DEBUG
#include "genUtil.h"
#include "Memory.h"
#include "mrcImage.h"
#include "dsn6File.h"

typedef struct lmrc2dsn6Info {
	float shiftx;
	float shifty;
	float shiftz;
} lmrc2dsn6Info;

int
main(int argc, char* argv[])
{
    mrcImage img;
	Dsn6     map;

	mrc2dsn6Info   info;
	lmrc2dsn6Info  linfo;

    init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	linfo.shiftx = info.shiftx;
	linfo.shifty = info.shifty;
	linfo.shiftz = info.shiftz;

    mrcFileRead(&img, info.In, "from Main Routine", 0);
	if(info.flagmul) {
		DEBUGPRINT1("MUL: %e\n", info.mul);
		lmrcImageDividedByReal(&img, 1.0/info.mul);
		mrcStatDataSet(&img, 0);
	}
	lmrc2dsn6(&map, &img, linfo, info.mode);

	dsn6FileWrite(&map, info.fptOut, info.mode);
	return 1; 
}

void
additionalUsage()
{
}

void 
lmrc2dsn6(dsn6File* map, mrcImage* img, lmrc2mapInfo linfo, long mode)
{
	int i, x, y, z, i1, i2;
	int qx, qy, qz, qx2, qy2, qz2, qnx, qny, qnz, n;
	double data, plus, prod;
	unsigned char record[8*8*8], uctmp;
	unsigned char* rhobyte;
	int itmp;

	if(img->HeaderAMax - img->HeaderAMin <=0) {
		mrcStatDataSet(img, 0);
	}
	if(mode==0) {
		map->Dsn6Header.Start.x = img->HeaderStartN.x;
		map->Dsn6Header.Start.y = img->HeaderStartN.y;
		map->Dsn6Header.Start.z = img->HeaderStartN.z;
	} else if(mode==1) {
		if(img->HeaderN.x%2==0) {
			map->Dsn6Header.Start.x = img->HeaderStartN.x - (img->HeaderN.x - 0)/2;
		} else {
			map->Dsn6Header.Start.x = img->HeaderStartN.x - (img->HeaderN.x - 1)/2;
		}
		if(img->HeaderN.y%2==0) {
			map->Dsn6Header.Start.y = img->HeaderStartN.y - (img->HeaderN.y - 0)/2;
		} else {
			map->Dsn6Header.Start.y = img->HeaderStartN.y - (img->HeaderN.y - 1)/2;
		}
		map->Dsn6Header.Start.z = img->HeaderStartN.z;
	} else if(mode==2) {
		map->Dsn6Header.Start.x = 0;
		map->Dsn6Header.Start.y = 0;
		map->Dsn6Header.Start.z = 0;
	}

	map->Dsn6Header.Start.x += floor(linfo.shiftx/img->HeaderLength.x + 0.5);
	map->Dsn6Header.Start.y += floor(linfo.shifty/img->HeaderLength.y + 0.5);
	map->Dsn6Header.Start.z += floor(linfo.shiftz/img->HeaderLength.z + 0.5);

	map->Dsn6Header.Extent.x     = img->HeaderN.x;
	map->Dsn6Header.Extent.y     = img->HeaderN.y;
	map->Dsn6Header.Extent.z     = img->HeaderN.z;
	if(img->HeaderM.x!=0) {
		map->Dsn6Header.SamplingRate.x     = img->HeaderM.x;
	} else {
		map->Dsn6Header.SamplingRate.x     = 1;
	}
	if(img->HeaderM.y!=0) {
		map->Dsn6Header.SamplingRate.y     = img->HeaderM.y;
	} else {
		map->Dsn6Header.SamplingRate.y     = 1;
	}
	if(img->HeaderM.z!=0) {
		map->Dsn6Header.SamplingRate.z     = img->HeaderM.z;
	} else {
		map->Dsn6Header.SamplingRate.z     = 1;
	}

    dsn6ImageAllocate 

#ifdef II
	memoryByteSwap(&map, sizeof(short), sizeof(map)/sizeof(short));
#endif
	fwrite(&map, sizeof(map), 1, fpt);
#ifdef II
	memoryByteSwap(&map, sizeof(short), sizeof(map)/sizeof(short));
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
