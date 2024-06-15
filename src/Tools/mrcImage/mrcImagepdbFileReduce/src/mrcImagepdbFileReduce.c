/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% mrcImagepdbFileReduce ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : mrcImagepdbFileReduce
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%mrcImagepdbFileReduce ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"

#define DEBUG
#include "genUtil.h"
#include "mrcImage.h"
#include "pdbFile.h"
#include "pdbInfoGet.h"

void lmrcImagepdbFileReduce(mrcImage* out, mrcImage* in, pdbFile* pdb, double Th, double R, double v, double ITh);

int
main(int argc, char* argv[]) 
{

	mrcImagepdbFileReduceInfo info;

/* variables */
	pdbFile pdb;
	mrcImage in;
	mrcImage out;
	pdbInfoData pdbinfo;
	

/* input patameters ,file open */
	init0(&info);
	argCheck(&info, argc, argv);
	init1(&info);
	mrcFileRead(&in ,info.In ,"in main" ,0);
	pdbFileRead(info.fptPdb, &pdb);
	pdbInfoGet(&pdb, &pdbinfo, 0);

/* begin */
	
	DEBUGPRINT("Program Start\n");
	lmrcImagepdbFileReduce(&out, &in, &pdb, info.Th ,info.R, info.Value ,info.ITh);
	mrcFileWrite(&out, info.Out, "in main", 0);


	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
}

void lmrcImagepdbFileReduce(mrcImage* out, mrcImage* in, pdbFile* pdb, double Th ,double R, double v, double ITh)
{
 /* variables */
  long x,y,z,ix,iy,iz,wx,wy,wz,flag,res,orgres;
  double data,d,dx,dy,dz;
  float px,py,pz;
  char chain;

 /* begin */
  out->Header = in->Header;
  mrcInit(out,0);

  for (z=0 ;z < in->HeaderN.z ;z++){
    for (y=0 ;y < in->HeaderN.y ;y++){
      for (x=0 ;x < in->HeaderN.x ;x++){
	mrcPixelDataGet(in,x,y,z,&data,mrcPixelRePart ,mrcPixelHowNearest); 
	if (data < Th) {
	  data = v;
	}
	mrcPixelDataSet(out,x,y,z,data ,mrcPixelRePart);
      }
    }
  }

  wx=floor(R/in->HeaderLength.x +0.5);
  wy=floor(R/in->HeaderLength.y +0.5);
  wz=floor(R/in->HeaderLength.z +0.5);

  orgres=0;
  flag=0;

  pdbFileTop(pdb);
  while(1) {
    if(pdbFileIsAtom(pdb)) {
      res=pdbFileResidueSequenceNumberGet(pdb);
      if (res != orgres){
	if (flag){
	  chain=pdbFileChainIdentifierGet(pdb);
	  fprintf(stdout,"%d%c \n",res,chain);
	}
	flag=0;
      }
      orgres=res;
      pdbFileCoordGet(pdb, &px, &py, &pz);
      ix=floor(px / in->HeaderLength.x +0.5);
      iy=floor(py / in->HeaderLength.y +0.5);
      iz=floor(pz / in->HeaderLength.z +0.5);
      for (x =ix-wx ;x <=ix+wx ;x++){
	dx = (px - x*in->HeaderLength.x );
	for (y =iy-wy ;y <=iy+wy ;y++){
	  dy = (py - y*in->HeaderLength.y );
	  for (z =iz-wz ;z <=iz+wz ;z++){
	    dz = (pz - z*in->HeaderLength.z );
	    d = dx*dx + dy*dy +dz*dz;
	    if (d < R*R && x>=0 && x < in->HeaderN.x 
		        && y>=0 && y < in->HeaderN.y 
	                && z>=0 && z < in->HeaderN.z ){
	      mrcPixelDataGet(in,x,y,z,&data, mrcPixelRePart, mrcPixelHowNearest );
	      if (data > ITh){
		flag=1;
	      }
	      mrcPixelDataSet(out,x,y,z,v ,mrcPixelRePart);
	    }
	  }
	}
      }
    }
    if(pdbFileEnd(pdb)) {
      break;
    } else {
      pdbFileNext(pdb);
    }
  }    
  mrcStatDataSet(out, 0);
}  
  



