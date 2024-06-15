/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% ip2mrc ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : ip2mrc
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%ip2mrc ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"

#define DEBUG
#include "genUtil.h"
#include "Memory.h"
#include "mrcImage.h"

typedef long IPFileParaTypeInteger;
typedef float IPFileParaTypeReal;
typedef unsigned short IPFileDataType;

typedef struct IPFile {
	IPFileParaTypeInteger width; 
	IPFileParaTypeInteger height; 
	IPFileParaTypeReal    xLength; 
	IPFileParaTypeReal    yLength; 
	IPFileDataType*       image;
} IPFile;

typedef struct lip2mrcInfo {
	IPFileParaTypeReal Magnification;
	IPFileParaTypeReal SE;
} lip2mrcInfo;

extern void ipInit(IPFile* ip, FILE* fptTem, FILE* fptInf, long mode);
extern void ipFileRead(FILE* fpt, FILE* fptTem, FILE* fptInf, IPFile* ip, long mode);
extern void lip2mrc(mrcImage* mrc, IPFile* ip, lip2mrcInfo* linfo, long mode);

#define IPBITS  (0x3fff)

void
main(int argc, char* argv[]) 
{
	mrcImage mrc;
	IPFile ip;
	ip2mrcInfo info;
	lip2mrcInfo linfo;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");
	memoryClear(&(mrc), sizeof(mrc), 0);
	
	ipFileRead(info.fptIn, info.fptInTem, info.fptInInf, &ip, info.mode);

	linfo.SE            = info.SE; 
	linfo.Magnification = info.Mag;

	lip2mrc(&mrc, &ip, &linfo, info.OutMode);

	mrcFileWrite(&mrc, info.Out, "in main", 0);

	if(info.flagOut2) {
		mrcFileWriteLowerResolution(&mrc, info.Out2, "in main", 4, 0);
	}
	exit(EXIT_SUCCESS);
}

void
lip2mrc(mrcImage* mrc, IPFile* ip, lip2mrcInfo* linfo, long mode)
{
	unsigned short d;
	unsigned char upper, lower;
	mrcImageParaTypeReal x, y;
	double data;

	mrc->HeaderN.x = ip->width;	
	mrc->HeaderN.y = ip->height;	
	mrc->HeaderN.z = 1;
	mrc->HeaderMode = mode;
	mrc->HeaderLength.x = ip->xLength/linfo->Magnification;
	mrc->HeaderLength.y = ip->yLength/linfo->Magnification;
	mrc->HeaderLength.z = 0.0; 
	mrcInit(mrc, NULL);
	
	for(x=0; x<mrc->HeaderN.x; x++) {
		for(y=0; y<mrc->HeaderN.y; y++) {
			d = ip->image[((int)x)+((int)y)*ip->width];
			upper = 0x3f & ((0x00ff & d)     );
			lower = 0xff & ((0xff00 & d) >> 8);
			data = (double) (((unsigned short)upper)*256 + ((unsigned short)lower));
			data = 78.125/linfo->SE*pow(10.0, data/4096);
			mrcPixelDataSet(mrc, x, y, 0.0, data, mrcPixelRePart);
		}
	}
}

void
ipFileRead(FILE* fpt, FILE* fptTem, FILE* fptInf, IPFile* ip, long mode)
{
	size_t skip;
	DEBUGPRINT("ipFileRead Start\n");		
	
	ipInit(ip, fptTem, fptInf, mode);
	if(mode==1) {
		skip = 128;	
	} else {
		skip = 0;
	}
	fseek(fpt, skip, SEEK_SET);
	fread(ip->image, sizeof(unsigned short), ip->width*ip->height, fpt);
}

void
ipInit(IPFile* ip, FILE* fptTem, FILE* fptInf, long mode)
{
	ip->width  = 3760;
	ip->height = 3000;
	ip->xLength = 250000;
	ip->yLength = 250000;
	ip->image  = (unsigned short*)memoryAllocate(sizeof(unsigned short)*ip->width*ip->height, "in ipInit");
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
	fprintf(stderr, "mode: 0: No Skip\n");
	fprintf(stderr, "mode: 1: Skip(128 byte)\n");
}

