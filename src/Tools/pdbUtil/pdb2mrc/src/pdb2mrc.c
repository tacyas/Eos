/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% pdb2mrc ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : pdb2mrc
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%pdb2mrc ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"
#undef DEBUG
#include "genUtil.h"
#include "pdbFile.h"
#include "lpdb2mrcInfo.h"
#include "mrcImage.h"
#include "pdbInfoGet.h"

int
main(int argc, char* argv[]) 
{
	long status;
	pdb2mrcInfo info;
	pdbFile pdb;
	mrcImage mrc;
    lpdb2mrc3dInfo lpdbinfo3;
    pdbInfoData pdbinfo;
	double maxdistance;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

    DEBUGPRINT("Program start \n");

	pdbFileRead(info.fptIn, &pdb);
	DEBUGPRINT("Read a \n");

	pdbInfoGet(&pdb, &pdbinfo, 0);
	DEBUGPRINT("Read b \n");

	maxdistance = MAX(fabs(pdbinfo.cx)+pdbinfo.distance, MAX(fabs(pdbinfo.cy)+pdbinfo.distance, fabs(pdbinfo.cz)+pdbinfo.distance));
    DEBUGPRINT("Read end \n");
    if(info.flagStartx) {
        lpdbinfo3.sx = info.Startx;
    } else if(!info.flagnx){
        lpdbinfo3.sx = -maxdistance*1.5;
    }
    if(info.flagStarty) {
        lpdbinfo3.sy = info.Starty;
    } else {
        lpdbinfo3.sy = -maxdistance*1.5;
    }
    if(info.flagStartz) {
        lpdbinfo3.sz = info.Startz;
    } else {
        lpdbinfo3.sz = -maxdistance*1.5;
    }
    if(info.flagnx) {
        lpdbinfo3.nx = info.nx;
    } else {
        lpdbinfo3.nx = 2.0*fabs(lpdbinfo3.sx)/info.dx;
    }
    if(info.flagny) {
        lpdbinfo3.ny = info.ny;
    } else {
        lpdbinfo3.ny = 2.0*fabs(lpdbinfo3.sy)/info.dy;
    }
    if(info.flagnz) {
        lpdbinfo3.nz = info.nz;
    } else {
        lpdbinfo3.nz = 2.0*fabs(lpdbinfo3.sz)/info.dz;
    }
    lpdbinfo3.dx = info.dx;
    lpdbinfo3.dy = info.dy;
    lpdbinfo3.dz = info.dz;

    lpdbinfo3.Weight = info.Weight;
    lpdbinfo3.Sigma  = info.Sigma;


	lpdbinfo3.DensityMode = info.mode;
    DEBUGPRINT("lpdb2mrc3d start \n");
    lpdb2mrc3d(&mrc, &pdb, &lpdbinfo3, 0);
    DEBUGPRINT("lpdb2mrc3d end \n");
 	mrcFileWrite(&mrc, info.Out, "in main", 0);
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, ">>> mode \n");
	fprintf(stderr, "mode: DensityMode\n");
	lpdb2mrc3dUsage(stderr);
}
