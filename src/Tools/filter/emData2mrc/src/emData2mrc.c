/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% emData2mrc ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : emData2mrc
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%emData2mrc ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"

#undef DEBUG
#include "genUtil.h"
#include "mrcImage.h"
#include "emData.h"

typedef struct lemData2mrcInfo {
	mrcImageParaTypeReal magCorrection;
} lemData2mrcInfo;

typedef enum lemData2mrcMode {
	lemData2mrcModeMode=0
} lemData2mrcMode;

extern void lemData2mrc(mrcImage* mrc, emData* em, lemData2mrcInfo linfo, lemData2mrcMode mode);

int
main(int argc, char* argv[]) 
{
	emData2mrcInfo info;
	lemData2mrcInfo linfo;
	lemData2mrcMode lmode;
	emData em;
	mrcImage mrc;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");
	emDataFileRead(&em, info.fptIn, "in main", 0);
	linfo.magCorrection = info.magCorrection;
	lmode =  info.mode;

	DEBUGPRINT("lemData2mrc Before\n");

	lemData2mrc(&mrc, &em, linfo, lmode);

	DEBUGPRINT("lemData2mrc After\n");

	mrcFileWrite(&mrc, info.Out, "in main", 0);
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
}

void
lemData2mrc(mrcImage* mrc, emData* em, lemData2mrcInfo linfo, lemData2mrcMode mode)
{
	int i;
	int j;
	DEBUGPRINT("lemData2mrc Start\n");
	if(0!=(mode&0x01)) {
		emDataHeaderPrint(em, stdout, "##### lemData2mrc", 0); 
	}

	mrc->HeaderN.x = em->Header.Cont.Nx;
	mrc->HeaderN.y = em->Header.Cont.Ny;
	mrc->HeaderN.z = em->Header.Cont.Nz;
	mrc->HeaderMode = mrcShortImage;
	mrc->HeaderLength.x = em->Header.Cont.pixelSize*1e1*em->Header.Cont.binning
					/em->Header.Cont.Magnification
					/em->Header.Cont.PostMagnification
					/linfo.magCorrection;
	mrc->HeaderLength.y = mrc->HeaderLength.x;
	mrc->HeaderLength.z = mrc->HeaderLength.x;

	DEBUGPRINT1("Size: %f\n", em->Header.Cont.pixelSize);
	DEBUGPRINT1("Bin: %f\n", em->Header.Cont.binning);
	DEBUGPRINT1("Mag: %f\n", em->Header.Cont.Magnification);
	DEBUGPRINT1("Post: %f\n", em->Header.Cont.PostMagnification);
	DEBUGPRINT1("Cor: %f\n", linfo.magCorrection);
	DEBUGPRINT1("LENGTH: %f\n", mrc->HeaderLength.x);
	mrcInit(mrc, NULL);

	for(i=0; i<mrc->HeaderN.x*mrc->HeaderN.y*mrc->HeaderN.z; i++) {
		/*
		src
			srcx  i%(mrc->HeaderN.x) 
			srcy (i/(mrc->HeaderN.x))%(mrc->HeaderN.y) 
			srcz (i/(mrc->HeaderN.x*mrc->HeaderN.y))%(mrc->HeaderN.z)
		dst 
			dstx srcx
			dsty mrc->HeaderN.y - 1 - srcy 
			dstz dstz
			j = dstx + dsty*mrc->HeaderN.x + dstz*mrc->HeaderN.x*mrc->HeaderN.y
		*/
		j = i%(mrc->HeaderN.x)
		  + (mrc->HeaderN.y - 1 - (i/(mrc->HeaderN.x))%(mrc->HeaderN.y))*mrc->HeaderN.x
		  + (i/(mrc->HeaderN.x*mrc->HeaderN.y))%(mrc->HeaderN.z)*mrc->HeaderN.x*mrc->HeaderN.y;
		mrc->ImageShortImage[j] = em->ShortImage[i];
	}
	DEBUGPRINT("lemData2mrc En\n");
}

