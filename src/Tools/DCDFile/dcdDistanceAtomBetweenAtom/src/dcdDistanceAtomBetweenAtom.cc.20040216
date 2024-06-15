/*
# dcdDistanceAtomBetweenAtom : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : dcdDistanceAtomBetweenAtom
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
typedef struct ldcdDistanceAtomBetweenAtomInfo {
	float a;
	int   b;
} ldcdDistanceAtomBetweenAtomInfo;

typedef enum ldcdDistanceAtomBetweenAtomMode {
	a=0,
	b=1
} ldcdDistanceAtomBetweenAtomMode;
*/

int
main(int argc, char* argv[]) 
{
	dcdDistanceAtomBetweenAtomInfo info;
 DCD coordinate;

  char mode1[3];
  char mode2[3];
  char mode3[3];
  int  serectAtom;
  int  serectAtom2;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");

 strcpy(mode1,"r");
 strcpy(mode2,"w");
 strcpy(mode3,"a");

 coordinate.HeaderRead(info.In,info.Out);
 coordinate.CoordinateNew();
 for(int i=0;i<2;i++)
 {
    cout << " Atom number? ---> ";
   if(i==0)
   {
     cin >> serectAtom;
   }
   if(i==1)
   {
     cin >> serectAtom2;
   }
 }
 coordinate.Open(info.In,mode1);
 coordinate.AtomAtomDistanceGet(serectAtom,serectAtom2);
 coordinate.Close();
 coordinate.Open(info.Out,mode3);
 //coordinate.SerectAtomWrite(serectAtom);
 coordinate.CenterSerectAtomDistanceWrite(serectAtom);
 coordinate.Close();
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
}
