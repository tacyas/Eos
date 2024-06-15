/*
# dcdInfo : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : dcdInfo
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
typedef struct ldcdInfoInfo {
	float a;
	int   b;
} ldcdInfoInfo;

typedef enum ldcdInfoMode {
	a=0,
	b=1
} ldcdInfoMode;
*/

int
main(int argc, char* argv[]) 
{
  dcdInfoInfo info;
  DCD coordinate;
  pdbFile pdb;

  char  mode1[3];
  char  mode2[3];
  char  mode3[3];

  int   nAtom;
  int   nStep;
  int   selectAtom;
  int   selectStep;
  int   Atom[50];
  int   Step[100];
  int   i,k;

   strcpy(mode1,"r");
   strcpy(mode2,"w");
   strcpy(mode3,"a");

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");

   if(info.flagInPDB) {
     pdbFileRead(info.fptInPDB, &pdb);
}
   cout <<"How many Atoms? = ";
   cin  >> nAtom;
   cout <<"How many Steps? = ";
   cin  >> nStep;

   for(i=0; i<nAtom; i++){
     cout << i+1 <<"th Atom number? =";
     cin  >> selectAtom;
     Atom[i]=selectAtom;
   }
   for(k=0; k<nStep; k++){
     cout << k+1 <<"th Step number? =";
     cin  >> selectStep;
     Step[k]=selectStep;
  }
   coordinate.HeaderRead(info.In);


  if(info.flagOutPDB) {
    coordinate.Open(info.In,mode1);
    coordinate.Write(info.fptOutPDB, &pdb, Step,Atom,nStep,nAtom);
    coordinate.Close();
  }
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
}
