/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% mrcImage2pdb ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : mrcImage2pdb
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%mrcImage2pdb ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"

#define DEBUG
#include "genUtil.h"
#include "mrcImage.h"
#include "Random.h"
#include "mrcRefUtil.h" 

void lmrcImage2pdb(FILE* out, mrcImage* in, float h, float l, int mode, double random);
double lmrcImage2pdbCalcPositionOnsurface(double* ox, double* oy, double* oz, int x, int y, int z, double data, mrcImage* in, double Th, int shiftx, int shifty, int shiftz, int flaglattice );
void lmrcImage2pdbOnsurface(FILE* out, mrcImage* in, float Th, int mode, double random, float delta, int flaglattice, int Skip);
int lmrcImageInImage(mrcImage* in, double x, double y, double z);
void lmrcImage2pdbOnsurfaceCageMode(FILE* out, mrcImage* in, float Th, int mode, double Random ,int Skip);

int
main(int argc, char* argv[]) 
{
	mrcImage2pdbInfo info;

/* variables */
	mrcImage in;

	init0(&info);
	argCheck(&info, argc, argv);
	init1(&info);

/* begin */
	DEBUGPRINT("Program Start\n");
	mrcFileRead(&in,  info.In , "in main" ,0);
	if (!info.flagh){
	  info.h = in.HeaderAMax;
	}
	if (!info.flagl){
	  info.l = in.HeaderAMin;
	}
	if (info.mode == 5){
	  DEBUGPRINT("mode = 5\n");
	  lmrcImage2pdbOnsurfaceCageMode(info.fptOut, &in, info.h, info.mode, info.Random ,info.Skip);
	  DEBUGPRINT("mode 5 end\n");
	} else {
	  if (info.mode >= 2){
	    lmrcImage2pdbOnsurface(info.fptOut, &in, info.h, info.mode, info.Random , info.delta, info.Lattice ,info.Skip);
	  } else {
	    lmrcImage2pdb(info.fptOut, &in, info.h, info.l, info.mode, info.Random);
	  }
	}
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
	fprintf(stderr, "mode0: One atom for one boxel.\n");
	fprintf(stderr, "mode1: Eight atoms for one boxel.\n");
	fprintf(stderr, "mode2: On the surface of high threshold. Atoms few.\n");
	fprintf(stderr, "mode3: On the surface of high threshold. Atoms medium.\n");
	fprintf(stderr, "mode4: On the surface of high threshold. Atoms many\n");
	fprintf(stderr, "mode5 (Default) : On the surface of high threshold. Mesh mode.\n");
}

void lmrcImage2pdb(FILE* out, mrcImage* in, float h, float l, int mode, double random)
{
/* variables */
  int x,y,z,n,m;
  double data,dx,dy,dz,fx,fy,fz;
  
  n=0;
  m=0;
  dx=in->HeaderLength.x;
  dy=in->HeaderLength.y;
  dz=in->HeaderLength.z;

  lRandShuffle();
  for (z=0 ;z < in->HeaderN.z ;z++){
    for (y=0 ;y < in->HeaderN.y ;y++){
      for (x=0 ;x < in->HeaderN.x ;x++){
	mrcPixelDataGet(in, x, y, z, &data, mrcPixelRePart,mrcPixelHowNearest);
	if (data > l && data < h){
	  switch(mode){
	  case 0:
	    fx=(x + random * (random() - 0.5) + in->HeaderStartN.x) *dx;
	    fy=(y + random * (random() - 0.5) + in->HeaderStartN.y) *dy;
	    fz=(z + random * (random() - 0.5) + in->HeaderStartN.z) *dz;
	    fprintf(out, "ATOM%7d  CA  GLY%6d    %8.3f%8.3f%8.3f  1.00%6.2f \n", n, m, fx, fy, fz, data );
	    n++;
	    m++;
	    break;
	  case 1:
	    fx=(x-0.25 + random * (random()*0.5 - 0.25))*dx;
	    fy=(y-0.25 + random * (random()*0.5 - 0.25))*dy;
	    fz=(z-0.25 + random * (random()*0.5 - 0.25))*dz;
	    fprintf(out, "ATOM%7d  CA  GLY%6d    %8.3f%8.3f%8.3f  1.00%6.2f \n", n, m, fx, fy, fz, data );
	    n++;
	    fx=(x-0.25 + random * (random()*0.5 - 0.25))*dx;
	    fy=(y-0.25 + random * (random()*0.5 - 0.25))*dy;
	    fz=(z+0.25 + random * (random()*0.5 - 0.25))*dz;
	    fprintf(out, "ATOM%7d  CA  GLY%6d    %8.3f%8.3f%8.3f  1.00%6.2f \n", n, m, fx, fy, fz, data );
	    n++;
	    fx=(x-0.25 + random * (random()*0.5 - 0.25))*dx;
	    fy=(y+0.25 + random * (random()*0.5 - 0.25))*dy;
	    fz=(z-0.25 + random * (random()*0.5 - 0.25))*dz;
	    fprintf(out, "ATOM%7d  CA  GLY%6d    %8.3f%8.3f%8.3f  1.00%6.2f \n", n, m, fx, fy, fz, data );
	    n++;
	    fx=(x-0.25 + random * (random()*0.5 - 0.25))*dx;
	    fy=(y+0.25 + random * (random()*0.5 - 0.25))*dy;
	    fz=(z+0.25 + random * (random()*0.5 - 0.25))*dz;
	    fprintf(out, "ATOM%7d  CA  GLY%6d    %8.3f%8.3f%8.3f  1.00%6.2f \n", n, m, fx, fy, fz, data );
	    n++;
	    fx=(x+0.25 + random * (random()*0.5 - 0.25))*dx;
	    fy=(y-0.25 + random * (random()*0.5 - 0.25))*dy;
	    fz=(z-0.25 + random * (random()*0.5 - 0.25))*dz;
	    fprintf(out, "ATOM%7d  CA  GLY%6d    %8.3f%8.3f%8.3f  1.00%6.2f \n", n, m, fx, fy, fz, data );
	    n++;
	    fx=(x+0.25 + random * (random()*0.5 - 0.25))*dx;
	    fy=(y-0.25 + random * (random()*0.5 - 0.25))*dy;
	    fz=(z+0.25 + random * (random()*0.5 - 0.25))*dz;
	    fprintf(out, "ATOM%7d  CA  GLY%6d    %8.3f%8.3f%8.3f  1.00%6.2f \n", n, m, fx, fy, fz, data );
	    n++;
	    fx=(x+0.25 + random * (random()*0.5 - 0.25))*dx;
	    fy=(y+0.25 + random * (random()*0.5 - 0.25))*dy;
	    fz=(z-0.25 + random * (random()*0.5 - 0.25))*dz;
	    fprintf(out, "ATOM%7d  CA  GLY%6d    %8.3f%8.3f%8.3f  1.00%6.2f \n", n, m, fx, fy, fz, data );
	    n++;
	    fx=(x+0.25 + random * (random()*0.5 - 0.25))*dx;
	    fy=(y+0.25 + random * (random()*0.5 - 0.25))*dy;
	    fz=(z+0.25 + random * (random()*0.5 - 0.25))*dz;
	    fprintf(out, "ATOM%7d  CA  GLY%6d    %8.3f%8.3f%8.3f  1.00%6.2f \n", n, m, fx, fy, fz, data );
	    n++;
	    m++;
	    break;
	  } 
	}	  
      }      
    }
  }
}



void lmrcImage2pdbOnsurface(FILE* out, mrcImage* in, float Th, int mode, double random, float delta, int flaglattice, int Skip)
{
/* variables */
  int x,y,z,n,m,flag,shiftx,shifty,shiftz,maxr2,shiftr,onum,i,j,outz;
  double data,dx,dy,dz,fx,fy,fz,tmpox,tmpoy,tmpoz,d;
  double ox[27],oy[27],oz[27];
  int flagout[27];

  dx=in->HeaderLength.x;
  dy=in->HeaderLength.y;
  dz=in->HeaderLength.z;
  maxr2=mode-1;

/* begin */
  n = m = flag = outz = 0;
  for (z=0 ;z < in->HeaderN.z ;z++){
    for (y=0 ;y < in->HeaderN.y ;y++){
      for (x=0 ;x < in->HeaderN.x ;x++){
	mrcPixelDataGet(in, x, y, z, &data, mrcPixelRePart,mrcPixelHowNearest);
	onum=0;
	for (shiftz = -1; shiftz <=1; shiftz++){
	  for (shifty = -1; shifty <=1; shifty++){
	    for (shiftx = -1; shiftx <=1; shiftx++){
	      shiftr = shiftx*shiftx + shifty*shifty + shiftz*shiftz;
	      if (shiftr != 0 && shiftr <= maxr2 && lmrcImageInImage(in, x+shiftx, y+shifty, z+shiftz) && (Skip == 1 || (z*2+shiftz)%Skip) ) {
		if ( lmrcImage2pdbCalcPositionOnsurface(&tmpox, &tmpoy, &tmpoz, x, y, z, data, in, Th, shiftx, shifty, shiftz, flaglattice) ) {
		  ox[onum]=tmpox;
		  oy[onum]=tmpoy;
		  oz[onum]=tmpoz;
		  onum++;
		}
	      }
	    }
	  }
	}
	if (onum != 0){
	  for (i=0; i<onum; i++){
	    flagout[i]=1;
	    for (j=i+1; j<onum; j++){
	      d = SQR(ox[i]-ox[j]) + SQR(oy[i]-oy[j]) + SQR(oz[i]-oz[j]);
	      if (d<SQR(delta)){
		flagout[i]=0;
		break;
	      }
	    } 
	  }
	  for (i=0; i<onum; i++){	
	    if (flagout[i]){
	      fx=(ox[i]+ random * (random()*0.5 - 0.25))*dx;
	      fy=(oy[i]+ random * (random()*0.5 - 0.25))*dy;
	      fz=(oz[i]+ random * (random()*0.5 - 0.25))*dz;
	      fprintf(out, "ATOM%7d  CA  GLY%6d    %8.3f%8.3f%8.3f  1.00%6.2f \n", n, m, fx, fy, fz, data );
	      n++;
	    }
	  }
	  m++;
	}
      }
    }
  } 
}


double lmrcImage2pdbCalcPositionOnsurface(double* ox, double* oy, double* oz, int x, int y, int z, double data, mrcImage* in, double Th, int shiftx, int shifty, int shiftz, int flaglattice)
{
  double data2,rate;

  mrcPixelDataGet(in, x+shiftx, y+shifty, z+shiftz, &data2, mrcPixelRePart,mrcPixelHowNearest);
  if ( (data - Th) * (data2 - Th) < 0){
    rate = (data - Th) / (data - data2);
    if (rate <= 0.5){
      if (flaglattice){
	*ox = x + shiftx * 0.5;
	*oy = y + shifty * 0.5;
	*oz = z + shiftz * 0.5;
      } else {
	*ox = x + shiftx * rate;
	*oy = y + shifty * rate;
	*oz = z + shiftz * rate;
      }
     return rate;
    } else {
      return 0;
    }
  } else {
    return 0;
  }
}

int lmrcImageInImage(mrcImage* in, double x, double y, double z)
{
  if (x < 0 || x > in->HeaderN.x-1 ||
      y < 0 || y > in->HeaderN.y-1 ||      
      z < 0 || z > in->HeaderN.z-1 ){
    /*
    DEBUGPRINT3("%g %g %g \n",x,y,z);
    */
    return(0);
  } else {
    return(1);
  }
}

void lmrcImage2pdbOnsurfaceCageMode(FILE* out, mrcImage* in, float Th, int mode, double random ,int Skip)
{
/* variables */
  int x,y,z,n,m,flag,shiftx,shifty,shiftz,maxr2,shiftr,onum,i,outz;
  double data,dx,dy,dz,fx,fy,fz,tmpox,tmpoy,tmpoz;
  double ox[27],oy[27],oz[27];

  dx=in->HeaderLength.x;
  dy=in->HeaderLength.y;
  dz=in->HeaderLength.z;
  maxr2=mode-1;

/* begin */
  n = m = flag = outz = 0;
  for (z=0 ;z < in->HeaderN.z ;z++){
    for (y=0 ;y < in->HeaderN.y ;y++){
      for (x=0 ;x < in->HeaderN.x ;x++){
	mrcPixelDataGet(in, x, y, z, &data, mrcPixelRePart,mrcPixelHowNearest);
	onum=0;
	for (shiftz = -1; shiftz <=1; shiftz++){
	  for (shifty = -1; shifty <=1; shifty++){
	    for (shiftx = -1; shiftx <=1; shiftx++){
	      shiftr = shiftx*shiftx + shifty*shifty + shiftz*shiftz;
	      if (shiftr != 0 
		  && shiftr <= maxr2 
		  && lmrcImageInImage(in, x+shiftx, y+shifty, z+shiftz) 
		  && (!((z*2+shiftz)%Skip) || !((y*2+shifty)%Skip) || !((x*2+shiftx)%Skip) )) {
		if ( lmrcImage2pdbCalcPositionOnsurface(&tmpox, &tmpoy, &tmpoz, x, y, z, data, in, Th, shiftx, shifty, shiftz, 1) ) {
		  ox[onum]=tmpox;
		  oy[onum]=tmpoy;
		  oz[onum]=tmpoz;
		  onum++;
		}
	      }
	    }
	  }
	}
	if (onum != 0){
	  for (i=0; i<onum; i++){	
	    fx=(ox[i]+ random * (random()*0.5 - 0.25))*dx;
	    fy=(oy[i]+ random * (random()*0.5 - 0.25))*dy;
	    fz=(oz[i]+ random * (random()*0.5 - 0.25))*dz;
	    fprintf(out, "ATOM%7d  CA  GLY%6d    %8.3f%8.3f%8.3f  1.00%6.2f \n", n, m, fx, fy, fz, data );
	    n++;
	  }
	  m++;
	}
      }
    }
  } 
}
  












