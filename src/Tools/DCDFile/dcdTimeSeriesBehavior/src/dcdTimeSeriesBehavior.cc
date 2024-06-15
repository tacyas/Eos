/*
# dcdTimeSeriesBehavior : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : dcdTimeSeriesBehavior
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
typedef struct ldcdTimeSeriesBehaviorInfo {
	float a;
	int   b;
} ldcdTimeSeriesBehaviorInfo;

typedef enum ldcdTimeSeriesBehaviorMode {
	a=0,
	b=1
} ldcdTimeSeriesBehaviorMode;
*/

int
main(int argc, char* argv[]) 
{
	dcdTimeSeriesBehaviorInfo info;
  DCD coordinate;

  char mode1[3];
  char mode2[3];
  char mode3[3];
  int  selectAtom;
  int  step;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");

 strcpy(mode1,"r");
 strcpy(mode2,"w");
 strcpy(mode3,"a");

 cout << " Atom number? ---> ";
 cin >> selectAtom;
 
 coordinate.HeaderRead(info.In);
 coordinate.Open(info.In,mode1);
 coordinate.CenterSelectedAtomDistanceGet(selectAtom);
 coordinate.Close();

/* coordinate.Open(info.Out,mode3);
 coordinate.SelectedAtomWrite(selectAtom);
 coordinate.Close();*/
 
/* cout << " Step? ---> ";
 cin >> step;
 coordinate.Open(info.In,mode1);
 coordinate.Read(step);
 coordinate.Close();
 coordinate.Open(info.Out,mode3);
 coordinate.Write();
 coordinate.Close();*/

 coordinate.Open(info.Out,mode3);
 coordinate.DistanceWrite();
 coordinate.Close();
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
}
