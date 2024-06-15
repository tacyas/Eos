/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% pdbFileMerge ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : pdbFileMerge
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%pdbFileMerge ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"

#define DEBUG
#include "genUtil.h"
#include "pdbFile.h"

void lpdbFileMerge(FILE* out, pdbFile* in1, pdbFile* in2, char startID);

int
main(int argc, char* argv[]) 
{
	pdbFileMergeInfo info;

/* variables */
	pdbFile in1;
	pdbFile in2;
	
/* input patameters ,file open */
	init0(&info);
	argCheck(&info, argc, argv);
	init1(&info);
	DEBUGPRINT("Program Start\n");
	pdbFileRead(info.fptIn1, &in1);
	pdbFileRead(info.fptIn2, &in2);
	
/* begin */
	lpdbFileMerge(info.fptOut, &in1, &in2, info.startID);
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
}

void lpdbFileMerge(FILE* out, pdbFile* in1, pdbFile* in2, char startID)
{
/* variables */
  char outID;
  char inID;
  char orginID;

/* begin */
  pdbFileTop(in1);
  outID=startID-1;
  orginID = 0;

  while(1) {
    if(pdbFileIsAtom(in1)) {
      inID = pdbFileChainIdentifierGet(in1);
      if (inID != orginID){
	outID++;
      }
      pdbFileChainIdentifierSet(in1, outID);
      orginID=inID;
    }
    if(pdbFileEnd(in1)) {
      break;
    } else {
      pdbFileNext(in1);
    }
  }    
  pdbFileWrite(out, in1);

  orginID = 0;
  pdbFileTop(in2);
  while(1) {
    if(pdbFileIsAtom(in2)) {
      inID = pdbFileChainIdentifierGet(in2);
      if (inID != orginID){
	outID++;
      }
      pdbFileChainIdentifierSet(in2, outID);
      orginID=inID;
    }
    if(pdbFileEnd(in2)) {
      break;
    } else {
      pdbFileNext(in2);
    }
  }    
  pdbFileWrite(out, in2);
}
