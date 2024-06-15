/*
# dcdSelectAtoms : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : dcdSelectAtoms
# Attention
#   $Loccker$
#  	$State$ 
#
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"

#define DEBUG
#include "genUtil.h"
#include "DCDFile.h"

/*
Example:
typedef struct ldcdSelectAtomsInfo {
	float a;
	int   b;
} ldcdSelectAtomsInfo;

typedef enum ldcdSelectAtomsMode {
	a=0,
	b=1
} ldcdSelectAtomsMode;
*/

int
main(int argc, char* argv[]) 
{
	dcdSelectAtomsInfo info;
  DCD coordinate;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");

  char mode1[3];
  char mode2[3];
  char mode3[3];
  int  selectAtom;
  int  nAtoms;
  int  Atoms[1];

  strcpy(mode1,"r");
  strcpy(mode2,"w");
  strcpy(mode3,"a");

  coordinate.HeaderRead(info.In);
  cout << "How many Atoms? = " ;
  cin  >> nAtoms ;
  coordinate.Open(info.In,mode1);
  coordinate.SelectedAtomsGet(nAtoms);
  coordinate.Close();
  coordinate.Open(info.Out,mode3);
  coordinate.SelectedAtomsWrite(nAtoms);
  coordinate.Close();

/*  coordinate.HeaderRead(info.In);
  cout << "How many Atoms? = " ;
  cin  >> nAtoms ;
  cout << "Atom Number? = " ;
  cin  >> selectAtom; 
  Atoms[0]=selectAtom;
  coordinate.Open(info.In,mode1);
  coordinate.SelectedAtomGet(Atoms,nAtoms);
  coordinate.Close();
  coordinate.Open(info.Out,mode3);
  coordinate.SelectedAtomWrite(nAtoms);
  coordinate.Close();*/


	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
}
