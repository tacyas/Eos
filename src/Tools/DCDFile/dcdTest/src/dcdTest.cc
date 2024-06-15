/*
# dcdTest : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : dcdTest
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
typedef struct ldcdTestInfo {
	float a;
	int   b;
} ldcdTestInfo;

typedef enum ldcdTestMode {
	a=0,
	b=1
} ldcdTestMode;
*/

int
main(int argc, char* argv[]) 
{
	dcdTestInfo info;
  DCD coordinate;

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

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");

   strcpy(mode1,"r");
   strcpy(mode2,"w");
   strcpy(mode3,"a");

/*   cout <<"How many Atoms? = ";
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
   coordinate.Open(info.In,mode1);
   coordinate.Read(Step,Atom,nStep,nAtom);
   coordinate.Close();
   coordinate.Open(info.Out,mode3);
   coordinate.Write(Step,Atom,nStep,nAtom);
   coordinate.Close();*/


   coordinate.HeaderRead(info.In);
   coordinate.Open(info.In,mode1);
   coordinate.DistanceOfAtomFromAverageGet();
   coordinate.Close();
   coordinate.Open(info.Out,mode3);
   coordinate.DistanceOfAtomFromAverageWrite();
   coordinate.Close();

	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
}
