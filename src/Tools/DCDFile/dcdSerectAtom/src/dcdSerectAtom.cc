/*
# dcdSerectAtom : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : dcdSerectAtom
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
typedef struct ldcdSerectAtomInfo {
	float a;
	int   b;
} ldcdSerectAtomInfo;

typedef enum ldcdSerectAtomMode {
	a=0,
	b=1
} ldcdSerectAtomMode;
*/

int
main(int argc, char* argv[]) 
{
	dcdSerectAtomInfo info;
  DCD coordinate;

  char mode1[3];
  char mode2[3];
  char mode3[3];
  char user[10];
  int  selectAtom;

     init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");

 strcpy(mode1,"r");
 strcpy(mode2,"w");
 strcpy(mode3,"a");

 coordinate.HeaderRead(info.In);
// do
// {
   coordinate.Open(info.In,mode1);
   cout << " Atom number? ---> ";
   cin >> selectAtom;
   coordinate.SelectedAtomGet(selectAtom);
   coordinate.Close();
   coordinate.Open(info.Out,mode3);
   coordinate.SelectedAtomWrite(selectAtom);
   coordinate.Close();
  // cout << " Dose it run once again?(y/n) ---> ";
  // cin >> user ;
  /* if(strlen(user)!=1)
   {
      cout << "* Input (y) or (n) ! " << endl;
      exit(0);
   }
   else
   {
      if(strcmp(user,"y")!=0 && strcmp(user,"n")!=0)
      {
         cout << " Input (y) or (n) ! " << endl;
         exit(0);
      }
   }
  }while(user[0]!='n');*/
}


void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
}
