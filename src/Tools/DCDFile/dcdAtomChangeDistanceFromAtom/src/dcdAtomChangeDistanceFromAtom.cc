/*
# dcdAtomChangeDistanceFromAtom : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : dcdAtomChangeDistanceFromAtom
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
typedef struct ldcdAtomChangeDistanceFromAtomInfo {
	float a;
	int   b;
} ldcdAtomChangeDistanceFromAtomInfo;

typedef enum ldcdAtomChangeDistanceFromAtomMode {
	a=0,
	b=1
} ldcdAtomChangeDistanceFromAtomMode;
*/

int
main(int argc, char* argv[]) 
{
	dcdAtomChangeDistanceFromAtomInfo info;

 DCD coordinate;

 char mode1[3];
 char mode2[3];
 char mode3[3];
 int  selectAtom;
 int selectAtom2;

       init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");

 strcpy(mode1,"r");
 strcpy(mode2,"w");
 strcpy(mode3,"a");

 coordinate.HeaderRead(info.In);
/* cout << "Center Atom number? = ";
 cin >> selectAtom;

 cout << "Change Atom number? = ";
 cin >> selectAtom2;*/

 coordinate.Open(info.In,mode1);
 //coordinate.AtomChangeFromAtomGet(selectAtom,selectAtom2);
 coordinate.AtomAtomDistanceGet();
 coordinate.Close();
 coordinate.Open(info.Out,mode3);
 coordinate.DistanceWrite();
 coordinate.Close();

}


void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
}
