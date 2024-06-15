/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% mrcImageMappingtoPdb ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : mrcImageMappingtoPdb
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%mrcImageMappingtoPdb ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"

#define DEBUG
#include "genUtil.h"
#include "mrcImage.h"
#include "pdbFile.h"
#include "pdbInfoGet.h"

void lmrcImageMappingtoPdb(pdbFile* pdb, mrcImage* in, int mode);

int
main(int argc, char* argv[]) 
{
	mrcImageMappingtoPdbInfo info;
	pdbFile pdb;
	pdbInfoData pdbinfo;
	mrcImage in;

	init0(&info);
	argCheck(&info, argc, argv);
	init1(&info);
	
	mrcFileRead(&in ,info.In ,"in main" ,0);
	DEBUGPRINT("1 ");
	pdbFileRead(info.fptInPdb, &pdb);
	DEBUGPRINT("2 ");
	pdbInfoGet(&pdb, &pdbinfo, 0);


	DEBUGPRINT("Program Start\n");
	lmrcImageMappingtoPdb(&pdb, &in, info.mode);
	pdbFileWrite(info.fptOut, &pdb);
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
}

void lmrcImageMappingtoPdb(pdbFile* pdb, mrcImage* in, int mode)
{
  float px,py,pz,x,y,z;
  double data;

  pdbFileTop(pdb);
  while(1) {
    if(pdbFileIsAtom(pdb)) {
      pdbFileCoordGet(pdb, &px, &py, &pz);
      x=px / in->HeaderLength.x ;
      y=py / in->HeaderLength.y ;
      z=pz / in->HeaderLength.z ;
      mrcPixelDataGet(in,x,y,z,&data,mrcPixelRePart ,3); 
      pdb->PDB->TemperatureFactor = data;
    }
    if(pdbFileEnd(pdb)) {
      break;
    } else {
      pdbFileNext(pdb);
    }
  }    
}

