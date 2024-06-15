/*
# dcdFilePrint : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : dcdFilePrint
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
typedef struct ldcdFilePrintInfo {
	float a;
	int   b;
} ldcdFilePrintInfo;

typedef enum ldcdFilePrintMode {
	a=0,
	b=1
} ldcdFilePrintMode;
*/

int
main(int argc, char* argv[]) 
{
  dcdFilePrintInfo info;
  DCD coordinate;
  pdbFile pdb;
  
  //char* in_filename;
  //char* out_filename;
  char  mode1[3];
  char  mode2[3];
  char  mode3[3];
  //int   start;
  //int   end;
  //int   interval;
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

	if(info.flagrStart) {
		info.Start = info.rStart;
		info.End   = info.rEnd;
		info.Delta = info.rDelta;
	}

  if(info.flagInPDB) {
    pdbFileRead(info.fptInPDB, &pdb);
  }
  
 /* coordinate.HeaderRead(info.In);
  coordinate.Open(info.Out,mode3);
  coordinate.Close();	 
  coordinate.Open(info.In,mode1);        
  coordinate.Read(info.Start,info.End,info.Delta);
  coordinate.Close();
  coordinate.Open(info.Out,mode3);
  coordinate.Write(info.Start,info.End,info.Delta);
  coordinate.Close();*/

/*   coordinate.HeaderRead(info.In);
   coordinate.Open(info.In,mode1);
   coordinate.Read(Step,Atom,nStep,nAtom);
   coordinate.Close();
   coordinate.Open(info.Out,mode3);
   coordinate.Write(Step,Atom,nStep,nAtom);
   coordinate.Close();*/

   coordinate.HeaderRead(info.In);
   coordinate.Open(info.In,mode1);
   coordinate.CoordinateFromPDB(&pdb);
   coordinate.Close();
   coordinate.Open(info.Out,mode3);
   coordinate.DistanceWrite();
   coordinate.Close();

    
/*  if(info.flagOutPDB) {
    coordinate.Open(info.In,mode1);
    coordinate.Write(info.fptOutPDB, &pdb, (int)info.Start, (int)info.End, (int)info.Delta);
    coordinate.Close();
  }*/
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
}
