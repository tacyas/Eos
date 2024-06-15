/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% pdbMolecularInterfaceFind ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : pdbMolecularInterfaceFind
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%pdbMolecularInterfaceFind ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"

#define DEBUG
#include "genUtil.h"
#include "pdbFile.h"
#include "nr2.h"

void lpdbMolecularInterfaceFind(pdbFile* in, char ID1, char ID2, double Thd, int mode);

int
main(int argc, char* argv[]) 
{
	pdbMolecularInterfaceFindInfo info;

/* variables */
	pdbFile in;

/* input patameters ,file open */
	init0(&info);
	argCheck(&info, argc, argv);
	init1(&info);
	pdbFileRead(info.fptIn, &in);

/* begin */
	lpdbMolecularInterfaceFind(&in, info.ID1, info.ID2, info.d, info.mode);
	DEBUGPRINT("Program Start\n");
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
}

void lpdbMolecularInterfaceFind(pdbFile* in, char ID1, char ID2, double Thd, int mode)
{
/* variables */
  float* x1;
  float* y1;
  float* z1;
  float* x2;
  float* y2;
  float* z2;
  long ID1Atomnum,ID2Atomnum, num1, num2, res;  
  double d;
  int flag;

/* begin */
  ID1Atomnum = ID2Atomnum = 0;
  pdbFileTop(in);
  while(1) {
    if(pdbFileIsAtom(in)) {
      if (ID1 == pdbFileChainIdentifierGet(in)){
	ID1Atomnum++;
      } else if (ID2 == pdbFileChainIdentifierGet(in)){
	ID2Atomnum++;
      }
    }
    if(pdbFileEnd(in)) {
      break;
    } else {
      pdbFileNext(in);
    }
  }
  x1=vector(0,ID1Atomnum);
  y1=vector(0,ID1Atomnum);
  z1=vector(0,ID1Atomnum);
  x2=vector(0,ID2Atomnum);
  y2=vector(0,ID2Atomnum);
  z2=vector(0,ID2Atomnum);
  pdbFileTop(in);
  num1=num2=0;
  while(1) {
    if(pdbFileIsAtom(in)) {
      if (ID1 == pdbFileChainIdentifierGet(in)){
	pdbFileCoordGet(in, &x1[num1], &y1[num1], &z1[num1]);
	num1++;
      } else if (ID2 == pdbFileChainIdentifierGet(in)){
	pdbFileCoordGet(in, &x2[num2], &y2[num2], &z2[num2]);
	num2++;
      }
    }
    if(pdbFileEnd(in)) {
      break;
    } else {
      pdbFileNext(in);
    }
  }
  num1=num2=0;
  pdbFileTop(in);
  while(1) {
    if(pdbFileIsAtom(in)) {
      if (ID1 == pdbFileChainIdentifierGet(in)){
	flag=0;
	for (num2=0; num2<ID2Atomnum; num2++){
	  d = SQR(x1[num1] - x2[num2]) + SQR(y1[num1] - y2[num2]) + SQR(z1[num1] - z2[num2]);
	  if (d < SQR(Thd) ){
	    flag=1;
	  }
	}
	if (flag){
	  res=pdbFileResidueSequenceNumberGet(in);
	  fprintf(stdout,"%d%c \n",res,ID1);
	}
      num1++;      
      }
    }
    if(pdbFileEnd(in)) {
      break;
    } else {
      pdbFileNext(in);
    }
  }    
  num1=num2=0;
  pdbFileTop(in);
  while(1) {
    if(pdbFileIsAtom(in)) {
      if (ID2 == pdbFileChainIdentifierGet(in)){
	flag=0;
	for (num1=0; num1<ID1Atomnum; num1++){
	  d = SQR(x1[num1] - x2[num2]) + SQR(y1[num1] - y2[num2]) + SQR(z1[num1] - z2[num2]);
	  if (d < SQR(Thd) ){
	    flag=1;
	  }
	}
	if (flag){
	  res=pdbFileResidueSequenceNumberGet(in);
	  fprintf(stdout,"%d%c \n",res,ID2);
	}
	num2++;
      }
    }
    if(pdbFileEnd(in)) {
      break;
    } else {
      pdbFileNext(in);
    }
  }    
}




















