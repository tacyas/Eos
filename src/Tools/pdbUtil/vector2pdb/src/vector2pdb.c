/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% vector2pdb ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : vector2pdb
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%vector2pdb ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"

#undef DEBUG
#include "genUtil.h"
#include "pdbFile.h"
#include "lDescartesIntoPolar.h"

int
main(int argc, char* argv[]) 
{
	vector2pdbInfo info;
	pdbFile pdb;	
	int i;
	double v;
	PolarCoord pp;
	DescartesCoord dp;
	lDescartesIntoPolarInfo linfo;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");
	if(info.flagphi && info.flagtheta) {
		linfo.xaxis.x = info.xx;
		linfo.xaxis.y = info.xy;
		linfo.xaxis.z = info.xz;
		linfo.zaxis.x = info.zx;
		linfo.zaxis.y = info.zy;
		linfo.zaxis.z = info.zz;
		linfo.centre.x = 0;
		linfo.centre.y = 0;
		linfo.centre.z = 0;
		lDescartesAxisCalc(&linfo, 0);
		pp.r = 1;
		pp.phi   = info.phi*RADIAN;
		pp.theta = info.theta*RADIAN;
	    dp = lPolarCoordIntoDescartesCoord(pp, linfo, 0);	
		info.vx = dp.x;
		info.vy = dp.y;
		info.vz = dp.z;
	}
	v = sqrt(SQR(info.vx) + SQR(info.vy) + SQR(info.vz));
	for(i=0; i<info.n; i++) {
		if(i==0) {
			pdbFileNew(&pdb);
		} else {
			pdbFileAppend(&pdb);
		}
		strncpy(pdb.PDB->Record, pdbRecordAtom, PDB_FILE_ATOM_NUMBER_LENGTH+1);	
		pdb.PDB->AtomSerialNumber  = i;
		strncpy(pdb.PDB->AtomName, " CA ", PDB_FILE_ATOM_NAME_LENGTH+1);
		pdb.PDB->LocationIndicator = ' ';
		strncpy(pdb.PDB->ResidueName, info.Res, PDB_FILE_RESIDUE_LENGTH+1);
		pdb.PDB->ChainIdentifier = info.ID;
		pdb.PDB->ResidueSequenceNumber = i;
		pdb.PDB->InsertionCode = ' ';
		pdb.PDB->Coord.x = i*info.step*info.vx/v + info.sx;
		pdb.PDB->Coord.y = i*info.step*info.vy/v + info.sy;
		pdb.PDB->Coord.z = i*info.step*info.vz/v + info.sz;
		pdb.PDB->Occupancy         = 1.0;
		pdb.PDB->TemperatureFactor = 0.0;
#ifdef DEBUG
		fprintf(stderr, "%s\n", pdb.PDB->Record);
		if(pdbFileIsAtom(&pdb)) {
			fprintf(stderr, "%s\n", pdb.PDB->Record);
		}
		pdbFileRecordPrint(stderr, &pdb);
#endif
	}
	pdb.nAtom = info.n;
	pdbFileWrite(info.fptOut, &pdb);
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
}
