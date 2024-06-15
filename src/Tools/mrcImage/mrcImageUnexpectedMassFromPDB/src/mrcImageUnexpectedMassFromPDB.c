#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"
#include "mrcImage.h"
#include "pdbFile.h"

typedef struct lmrcImageUnexpectedMassFromPDBInfo {
	double thres;
	double data;
	int    atomMode;
	double radius;
} lmrcImageUnexpectedMassFromPDBInfo;

extern void lmrcImageUnexpectedMassFromPDB(mrcImage* mrcOut, mrcImage* mrcIn, pdbFile* pdbIn, lmrcImageUnexpectedMassFromPDBInfo, long mode);

int
main(int argc, char* argv[]) 
{
	long status;
	mrcImageUnexpectedMassFromPDBInfo info;
	lmrcImageUnexpectedMassFromPDBInfo lInfo;
	mrcImage mrcIn;
	mrcImage mrcOut;
	pdbFile  pdbIn;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	mrcFileRead(&mrcIn, info.In, "in mail routine", 0);
	pdbFileRead(info.fptInPDB, &pdbIn);
	lInfo.thres = info.Thres;
	lInfo.data  = info.Data;
	lInfo.atomMode = info.AtomMode;
	lInfo.radius = info.radius;
	lmrcImageUnexpectedMassFromPDB(&mrcOut, &mrcIn, &pdbIn, lInfo, info.mode);
	mrcFileWrite(&mrcOut, info.Out, "in mail routine", 0);
	return 0;
}

void
additionalUsage()
{
	fprintf(stderr, ">>> Mode:	\n");
	fprintf(stderr, "\t0: Origin is BottomLeft.\n");
	fprintf(stderr, "\t1: Origin is Center.(Helix)\n");
	fprintf(stderr, "\t2: Origin is Center.(3D Single)\n");
	fprintf(stderr, "\t3: Origin is shown by StartN.\n");
	fprintf(stderr, "\t16: MaxIsProtein : Default: MinIsProtein\n");
	fprintf(stderr, ">>> Algorism\n");
	fprintf(stderr, "If MinIsProtein mode, \n");
	fprintf(stderr, "\tif density>Thres \n");
	fprintf(stderr, "\tthen\n");
	fprintf(stderr, "\t\tdensity := density\n");
	fprintf(stderr, "\telse\n");
	fprintf(stderr, "\t\tdensity := Data\n");
	fprintf(stderr, "\tendif\n");
	fprintf(stderr, ">>> AtomMode \n");
	fprintf(stderr, "\t0: Nearest Voxel -> Data\n");
	fprintf(stderr, "\t1: Nearest and 6-linked voxel -> Data\n");
	fprintf(stderr, "\t2: Specified spheres(Outside) -> Data\n");
	fprintf(stderr, "\t3: Inside of Specified spheres  -> Data\n");
	fprintf(stderr, "\t2: Outside of Specified spheres -> Data\n");
}

void
lmrcImageUnexpectedMassFromPDB(mrcImage* mrcOut, mrcImage* mrcIn, pdbFile* pdbIn, lmrcImageUnexpectedMassFromPDBInfo info, long mode)
{
	pdbFileParaTypeReal x, y, z;
	double data;
	long flag;

	if(!IsImage(mrcIn, "in lmrcImageAssignedToTFofPDB", 0)) {
		fprintf(stderr, "Not supported mode of mrcImage\n");
		exit(EXIT_FAILURE);
	}
	mrcOut->Header = mrcIn->Header;
	mrcInit(mrcOut, NULL);
	for(x=0; x<mrcIn->HeaderN.x; x++) {
		for(y=0; y<mrcIn->HeaderN.y; y++) {
			for(z=0; z<mrcIn->HeaderN.z; z++) {
				mrcPixelDataGet(mrcIn, x, y, z, &data, mrcPixelRePart, mrcPixelHowNearest);
				mrcPixelDataSet(mrcOut, x, y, z, data, mrcPixelRePart);
			}
		}
	}
	flag = 0;
	pdbFileTop(pdbIn);
	do {
		if(pdbFileIsAtom(pdbIn)) {
			pdbFileCoordGet(pdbIn, &x, &y, &z);
			switch(0x0000000f&mode) {
				case 0: {
					x = x/mrcIn->HeaderLength.x;
					y = y/mrcIn->HeaderLength.y;
					z = z/mrcIn->HeaderLength.z;
					break;
				}
				case 1: {
					 x = x/mrcIn->HeaderLength.x+(mrcIn->HeaderN.x)/2;
					 y = y/mrcIn->HeaderLength.y+(mrcIn->HeaderN.y)/2;
					 z = z/mrcIn->HeaderLength.z;
					break;
				}
				case 2: {
					 x = x/mrcIn->HeaderLength.x+(mrcIn->HeaderN.x-1.0)/2.0;
					 y = y/mrcIn->HeaderLength.y+(mrcIn->HeaderN.y-1.0)/2.0;
					 z = z/mrcIn->HeaderLength.z+(mrcIn->HeaderN.z-1.0)/2.0;
					break;
				}
				case 3: {
					 x = x/mrcIn->HeaderLength.x+mrcIn->HeaderStartN.x;
					 y = y/mrcIn->HeaderLength.y+mrcIn->HeaderStartN.y;
					 z = z/mrcIn->HeaderLength.z+mrcIn->HeaderStartN.z;
					break;
				}
				default: {
					fprintf(stderr, "Not supported Mode\n");
					exit(EXIT_FAILURE);
					break;
				}
			}
			mrcPixelDataGet(mrcIn, x, y, z, &data, mrcPixelRePart, mrcPixelHowNearest);
			switch(0x000000f0&mode) {
				case 0: {
					if(info.thres<data) {
						data = data;
					} else {
						data = info.data;
					}
					break;
				}	
				case 16: {
					if(data<info.thres) {
						data = data;
					} else {
						data = info.data;
					}
					break;
				}
				default: {
					fprintf(stderr, "Not supported mode: %d\n", mode);
					exit(EXIT_FAILURE);
				}
			}
			switch(info.atomMode) {
				case 0: {
					mrcPixelDataSet(mrcOut, x, y, z, data, mrcPixelRePart);
					break;
				} 
				case 1: {
					mrcPixelDataSet(mrcOut, x, y, z, data, mrcPixelRePart);
					mrcPixelDataSet(mrcOut, x-1, y, z, data, mrcPixelRePart);
					mrcPixelDataSet(mrcOut, x, y-1, z, data, mrcPixelRePart);
					mrcPixelDataSet(mrcOut, x, y, z-1, data, mrcPixelRePart);
					mrcPixelDataSet(mrcOut, x+1, y, z, data, mrcPixelRePart);
					mrcPixelDataSet(mrcOut, x, y+1, z, data, mrcPixelRePart);
					mrcPixelDataSet(mrcOut, x, y, z+1, data, mrcPixelRePart);
					break;
				}
				case 2: {
					mrcImageParaTypeReal dstx, dsty, dstz, r, r2, maxx, maxy, maxz;
					r2 = SQR(info.radius); 
					maxx = info.radius/mrcIn->HeaderLength.x + 1;
					maxy = info.radius/mrcIn->HeaderLength.y + 1;
					maxz = info.radius/mrcIn->HeaderLength.z + 1;

					for(dstx=x-maxx; dstx<=x+maxx; dstx++) { 
					for(dsty=y-maxy; dsty<=y+maxy; dsty++) { 
					for(dstz=z-maxz; dstz<=z+maxz; dstz++) { 
						r = SQR((dstx-x)*mrcIn->HeaderLength.x)
						  + SQR((dsty-y)*mrcIn->HeaderLength.y)
						  + SQR((dstz-z)*mrcIn->HeaderLength.z);
						if(r<r2) {
							mrcPixelDataSet(mrcOut, dstx, dsty, dstz, data, mrcPixelRePart);
						}
					}
					}
					}
					break;
				}
				case 3: {
					mrcImageParaTypeReal dstx, dsty, dstz, r, r2;
					mrcImageParaTypeInteger ix, iy, iz, maxx, maxy, maxz;
					r2 = SQR(info.radius); 
					maxx = info.radius/mrcIn->HeaderLength.x + 1;
					maxy = info.radius/mrcIn->HeaderLength.y + 1;
					maxz = info.radius/mrcIn->HeaderLength.z + 1;
					ix = x/mrcIn->HeaderLength.x+0.5;
					iy = y/mrcIn->HeaderLength.y+0.5;
					iz = z/mrcIn->HeaderLength.z+0.5;
					for(dstx=ix-maxx; dstx<=ix+maxx; dstx++) { 
					for(dsty=iy-maxy; dsty<=iy+maxy; dsty++) { 
					for(dstz=iz-maxz; dstz<=iz+maxz; dstz++) { 
						r = SQR((dstx-x)*mrcIn->HeaderLength.x) 
						  + SQR((dsty-y)*mrcIn->HeaderLength.y)
						  + SQR((dstz-z)*mrcIn->HeaderLength.z);
						if(r<r2) {
							mrcPixelDataSet(mrcOut, dstx, dsty, dstz, data, mrcPixelRePart);
						}
					}
					}
					}
					break;
				}
				default:  {
					fprintf(stderr, "Not supported AtomMode: %d\n", info.atomMode);
					exit(EXIT_FAILURE);	
					break;
				}
			}

		}
	} while(NULL!=pdbFileNext(pdbIn));
	mrcStatDataSet(mrcOut, 0);
}
