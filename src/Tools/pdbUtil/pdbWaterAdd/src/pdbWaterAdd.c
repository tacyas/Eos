/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% pdbWaterAdd ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : pdbWaterAdd
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%pdbWaterAdd ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"

#define DEBUG
#include <string.h>
#include "genUtil.h"
#include "Random.h"
#include "pdbFile.h"
#include "mrcImage.h"
#include "pdbInfoGet.h"
#include "lpdb2mrcInfo.h"

#define WATERMASS (18)
#define AB_CONST  (6.02e23)
#define ONE_LITTLE (1e

typedef enum lpdbWaterAddMode  {
	lpdbWaterAddModeSphere   = 0,
	lpdbWaterAddModeCylinder = 1,
	lpdbWaterAddModeEdge     = 2,
	lpdbWaterAddModeCube     = 3
} lpdbWaterAddMode;

typedef struct lpdbWaterAddInfo {
	double radius;
	double height; 
	double X;
	double Y;
	double Z;
	double molarOfWater;
	int    layer;
	lpdbWaterAddMode mode;
} lpdbWaterAddInfo;

extern int lpdbWaterAdd(pdbFile* water, pdbFile* in, lpdbWaterAddInfo* linfo, int mode);

int
main(int argc, char* argv[]) 
{
	pdbWaterAddInfo info;
	pdbFile pdb;
	pdbFile water;
	lpdbWaterAddInfo linfo;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");
	pdbFileRead(info.fptIn, &pdb);

	linfo.radius       = info.Radius;
	linfo.height       = info.Height;
	linfo.X = info.X;
	linfo.Y = info.Y;
	linfo.Z = info.Z;
	linfo.layer        = info.Edge;
	linfo.molarOfWater = info.Density;
	linfo.mode         = info.mode;
	lpdbWaterAdd(&water, &pdb, &linfo, 0);

	pdbFileWrite(info.fptOut, &water);
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
	fprintf(stderr, "----- Mode: -m  -----\n");
	fprintf(stderr, "-m %d :  sphere   \n", lpdbWaterAddModeSphere);
	fprintf(stderr, "-m %d :  cylinder \n", lpdbWaterAddModeCylinder);
	fprintf(stderr, "-m %d :  Edge     \n", lpdbWaterAddModeEdge);
	fprintf(stderr, "-m %d :  Cube     \n", lpdbWaterAddModeCube);
}

int
lpdbWaterAdd(pdbFile* water, pdbFile* in, lpdbWaterAddInfo* linfo, int mode)
{
	pdbInfoData pdbinfo;
	double volume;
	double length;
	mrcImage mrc;
	pdbRecord* pdbTmp;
	float x, y, z;
	float sx, sy, sz;
	float rx, ry, rz;
	double data;
	int flag;

	mrc.HeaderMode = mrcShortImage;

	pdbInfoGet(in, &pdbinfo, 0);	
	volume = 1e27/(linfo->molarOfWater*AB_CONST); /* Averaged volume for one water molecule */ 
	length = pow(volume, 1.0/3.0);
	DEBUGPRINT2("Vol: %f Length: %f\n", volume, length);
	mrc.HeaderLength.x = length; 
	mrc.HeaderLength.y = length; 
	mrc.HeaderLength.z = length; 
	
	switch(linfo->mode) {
		case lpdbWaterAddModeSphere: {
			mrc.HeaderN.x = 2*linfo->radius/length+1;
			mrc.HeaderN.y = 2*linfo->radius/length+1;
			mrc.HeaderN.z = 2*linfo->radius/length+1;

			mrc.HeaderStartN.x = (int)((pdbinfo.cx - linfo->radius)/length+0.5); /* (cx-radius) at mrc(0,0,0) */
			mrc.HeaderStartN.y = (int)((pdbinfo.cy - linfo->radius)/length+0.5);
			mrc.HeaderStartN.z = (int)((pdbinfo.cz - linfo->radius)/length+0.5);
			break;
		} 
		case lpdbWaterAddModeCylinder: {
			mrc.HeaderN.x = 2*linfo->radius/length+1;
			mrc.HeaderN.y = 2*linfo->radius/length+1;
			mrc.HeaderN.z = linfo->height/length  +1;

			mrc.HeaderStartN.x = (int)((pdbinfo.cx - linfo->radius)    /length+0.5); 
			mrc.HeaderStartN.y = (int)((pdbinfo.cy - linfo->radius)    /length+0.5);
			mrc.HeaderStartN.z = (int)((pdbinfo.cz - linfo->height/2.0)/length+0.5);
			break;
		}
		case lpdbWaterAddModeEdge: {
			mrc.HeaderN.x = pdbinfo.distancex*2.0/length + (linfo->layer+1)*2 + 1;
			mrc.HeaderN.y = pdbinfo.distancey*2.0/length + (linfo->layer+1)*2 + 1;
			mrc.HeaderN.z = pdbinfo.distancez*2.0/length + (linfo->layer+1)*2 + 1;
			DEBUGPRINT3("distance: %f %f %f\n", pdbinfo.distancex, pdbinfo.distancey, pdbinfo.distancez);
			mrc.HeaderStartN.x = (int)(pdbinfo.cx/length+0.5)-(mrc.HeaderN.x-1)/2; 
			mrc.HeaderStartN.y = (int)(pdbinfo.cy/length+0.5)-(mrc.HeaderN.y-1)/2; 
			mrc.HeaderStartN.z = (int)(pdbinfo.cz/length+0.5)-(mrc.HeaderN.z-1)/2; 
			break;
		}
		case lpdbWaterAddModeCube: {
			mrc.HeaderN.x = (int)(linfo->X/length + 0.5);
			mrc.HeaderN.y = (int)(linfo->Y/length + 0.5);
			mrc.HeaderN.z = (int)(linfo->Z/length + 0.5);

			mrc.HeaderStartN.x = (int)((pdbinfo.cx - linfo->X/2)/length+0.5); /* (cx-radius) at mrc(0,0,0) */
			mrc.HeaderStartN.y = (int)((pdbinfo.cy - linfo->Y/2)/length+0.5);
			mrc.HeaderStartN.z = (int)((pdbinfo.cz - linfo->Z/2)/length+0.5);
			break;
		} 
		default: {
			fprintf(stderr, "Not supported mode in lpdbWaterAdd: %d\n", linfo->mode);
			exit(EXIT_FAILURE);
		}
	}
	mrcInit(&mrc, NULL);

	for(x=0; x<mrc.HeaderN.x; x++) {
	for(y=0; y<mrc.HeaderN.y; y++) {
	for(z=0; z<mrc.HeaderN.z; z++) {
		switch(linfo->mode) {
			case lpdbWaterAddModeSphere: {
				if(SQR(x-mrc.HeaderN.x/2)
				  +SQR(y-mrc.HeaderN.y/2)
				  +SQR(z-mrc.HeaderN.z/2) > SQR(linfo->radius/length)) {
					mrcPixelDataSet(&mrc, x, y, z, 1, mrcPixelRePart);
				} else {
					mrcPixelDataSet(&mrc, x, y, z, 0, mrcPixelRePart);
				}
				break;
			}
			case lpdbWaterAddModeCylinder: {
				if(SQR(x-mrc.HeaderN.x/2)
				  +SQR(y-mrc.HeaderN.y/2)    > SQR(linfo->radius/length)
				  || fabs(z-mrc.HeaderN.z/2) > linfo->height/length/2.0) {
					mrcPixelDataSet(&mrc, x, y, z, 1, mrcPixelRePart);
				} else {
					mrcPixelDataSet(&mrc, x, y, z, 0, mrcPixelRePart);
				}
				break;
			}
			case lpdbWaterAddModeEdge: 
			case lpdbWaterAddModeCube: {
				mrcPixelDataSet(&mrc, x, y, z, 0, mrcPixelRePart);
				break;
			}
			default: {
				fprintf(stderr, "Not supported mode in lpdbWaterAdd: %d\n", linfo->mode);
				exit(EXIT_FAILURE);
			}
		}
	}
	}
	}

	pdbTmp = pdbFileTop(in);
	while(pdbTmp != NULL) {
		if(pdbFileIsAtom(in)) {
			pdbFileCoordGet(in, &x, &y, &z);

			switch(linfo->mode) {
				case lpdbWaterAddModeSphere: {
					if(SQR(x-pdbinfo.cx)+SQR(y-pdbinfo.cy)+SQR(z-pdbinfo.cz)<=SQR(linfo->radius)) {		
						mrcImageDataGetbyAU(&mrc, x, y, z, &data,  mrcPixelRePart, mrcPixelHowNearest);
						mrcImageDataSetbyAU(&mrc, x, y, z, data+1, mrcPixelRePart);
					}
					break;
				}
				case lpdbWaterAddModeCylinder: {
					if(SQR(x-pdbinfo.cx)+SQR(y-pdbinfo.cy)<=SQR(linfo->radius)
					&& fabs(z-pdbinfo.cz)                 <=linfo->height/2.0) {		
						mrcImageDataGetbyAU(&mrc, x, y, z, &data,  mrcPixelRePart, mrcPixelHowNearest);
						mrcImageDataSetbyAU(&mrc, x, y, z, data+1, mrcPixelRePart);
					}
					break;
				}
				case lpdbWaterAddModeEdge: 
				case lpdbWaterAddModeCube: {
					mrcImageDataGetbyAU(&mrc, x, y, z, &data,  mrcPixelRePart, mrcPixelHowNearest);
					mrcImageDataSetbyAU(&mrc, x, y, z, data+1, mrcPixelRePart);
					break;
				}
				default: {
					fprintf(stderr, "Not supported mode in lpdbWaterAdd: %d\n", linfo->mode);
					exit(EXIT_FAILURE);
				}
			}
		}	
		pdbTmp = pdbFileNextAtom(in);
	}

	switch(linfo->mode) {
		case lpdbWaterAddModeEdge: {
			for(x=0; x<mrc.HeaderN.x; x++) {
			for(y=0; y<mrc.HeaderN.y; y++) {
			for(z=0; z<mrc.HeaderN.z; z++) {
				mrcPixelDataGet(&mrc, x, y, z, &data, mrcPixelRePart, mrcPixelHowNearest);
				if(data==0) {
					flag = 0;
					for(sx=MAX(0,x-linfo->layer); sx<MIN(mrc.HeaderN.x,x+linfo->layer+1); sx++) {
					for(sy=MAX(0,y-linfo->layer); sy<MIN(mrc.HeaderN.y,y+linfo->layer+1); sy++) {
					for(sz=MAX(0,z-linfo->layer); sz<MIN(mrc.HeaderN.z,z+linfo->layer+1); sz++) {
						if(SQR(sx-x)+SQR(sy-y)+SQR(sz-z)<=SQR(linfo->layer)) {
							mrcPixelDataGet(&mrc, sx, sy, sz, &data, mrcPixelRePart, mrcPixelHowNearest);
							if(1<data) {
								flag++;
								break;
							}
						}
					}
						if(0<flag) {
							break;
						}	
					}
						if(0<flag) {
							break;
						}	
					}
					if(flag==0) {
						mrcPixelDataSet(&mrc, x, y, z, data+1, mrcPixelRePart);
					}
				}
			}
			}
			}
			break;
		}
		default: {
			break;
		}
	}
#ifdef DEBUG
	mrcFileWrite(&mrc, "/tmp/test.mrc", "DEBUG", 0);
#endif
	flag = 0;
	for(x=0; x<mrc.HeaderN.x; x++) {
	for(y=0; y<mrc.HeaderN.y; y++) {
	for(z=0; z<mrc.HeaderN.z; z++) {
		mrcPixelDataGet(&mrc, x, y, z, &data, mrcPixelRePart, mrcPixelHowNearest);
		if(data==0) {
			if(flag==0) {
				pdbFileNew(water);
			} else {
				pdbFileAppend(water);
			}
			flag++;
			rx = (x + mrc.HeaderStartN.x)*mrc.HeaderLength.x;
			ry = (y + mrc.HeaderStartN.y)*mrc.HeaderLength.y;
			rz = (z + mrc.HeaderStartN.z)*mrc.HeaderLength.z;
			rx = rx+randomNormalGet(1)*mrc.HeaderLength.x/8.0;  
			ry = ry+randomNormalGet(1)*mrc.HeaderLength.y/8.0;  
			rz = rz+randomNormalGet(1)*mrc.HeaderLength.z/8.0;  
			strncpy(water->PDB->Record, "ATOM  ", PDB_FILE_RECORD_LENGTH);
			water->PDB->AtomSerialNumber = flag%100000;
			strncpy(water->PDB->AtomName,    "OH2", PDB_FILE_ATOM_NAME_LENGTH);
			water->PDB->LocationIndicator = ' ';
			strncpy(water->PDB->ResidueName, "WAT", PDB_FILE_ATOM_NAME_LENGTH);
			water->PDB->ChainIdentifier       = 'A'+(flag%100000)/10000;
			water->PDB->ResidueSequenceNumber = flag%10000;
			water->PDB->InsertionCode = ' ';
			water->PDB->Coord.x = rx;
			water->PDB->Coord.y = ry;
			water->PDB->Coord.z = rz;
			water->PDB->Occupancy         =   0.0;
			water->PDB->TemperatureFactor = 100.0;
			water->PDB->FootnoteNumber = flag;
		}
	}
	}
	}
}

