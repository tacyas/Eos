/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% lmrcImageCrystalCreate ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : lmrcImageCrystalCreate 
#%Z% Attention
#%Z%
*/
#undef DEBUG
#include "genUtil.h"
#include "lmrcImageCrystalCreate.h"


void 
lmrcImageCrystalCreate(mrcImage* out, mrcImage* in, lmrcImageCrystalCreateInfo* info)
{
	mrcImageParaTypeReal xout, yout, zout;
	mrcImageParaTypeReal orgx, orgy, orgz;
	mrcImageParaTypeReal realxout, realyout, realzout;
	mrcImageParaTypeReal ix, iy, iz;
	mrcImageParaTypeReal na, nb, nc;
	mrcImageParaTypeReal orgna, orgnb, orgnc;
	mrcImageParaTypeReal La, Lb, Lc;
    double det, Ax, Ay, Az, Bx, By, Bz, Cx, Cy, Cz;
    int flagInCrystal;
	double data;

    DEBUGPRINT("start lmrcImageCrystalCreate\n");
	out->Header = in->Header;
/*
	out->HeaderN.x *= info->nx;
	out->HeaderN.y *= info->ny;
	out->HeaderN.z *= info->nz;
*/
    DEBUGPRINT3("A: %f %f %f\n", info->ax, info->ay, info->az);
    DEBUGPRINT3("B: %f %f %f\n", info->bx, info->by, info->bz);
    DEBUGPRINT3("C: %f %f %f\n", info->cx, info->cy, info->cz);
    DEBUGPRINT3("N: %ld %ld %ld\n", info->nx, info->ny, info->nz);
  // nx*a + ny*b + nz*c
    out->HeaderN.x = (int)((info->nx*info->ax + info->ny*info->bx + info->nz*info->cx)/out->HeaderLength.x+0.5);  
    out->HeaderN.y = (int)((info->nx*info->ay + info->ny*info->by + info->nz*info->cy)/out->HeaderLength.y+0.5);  
    out->HeaderN.z = (int)((info->nx*info->az + info->ny*info->bz + info->nz*info->cz)/out->HeaderLength.z+0.5);  
    DEBUGPRINT3("inN: %d %d %d\n", in->HeaderN.x, in->HeaderN.y, in->HeaderN.z);
    DEBUGPRINT3("outN: %d %d %d\n", out->HeaderN.x, out->HeaderN.y, out->HeaderN.z);

	mrcInit(out, NULL);

    La = SQR(info->ax) + SQR(info->ay) + SQR(info->az); if(0<La) { La = sqrt(La); } else { La = 0;} 
    Lb = SQR(info->bx) + SQR(info->by) + SQR(info->bz); if(0<Lb) { Lb = sqrt(Lb); } else { Lb = 0;} 
    Lc = SQR(info->cx) + SQR(info->cy) + SQR(info->cz); if(0<Lc) { Lc = sqrt(Lc); } else { Lc = 0;} 

    det = 
        info->ax*info->by*info->cz
       +info->bx*info->cy*info->az 
       +info->cx*info->ay*info->bz 
       -info->cx*info->by*info->az 
       -info->bx*info->ay*info->cz 
       -info->ax*info->cy*info->bz; 

  if(fabs(det)==0) {
    fprintf(stderr, "Two of a, b, c are parallel. Please check\n");
    exit(EXIT_FAILURE);
  } else {
    DEBUGPRINT1("Det of A, B, C: %f\n", det);
  }

  // Inverse of (a b c)
  Ax =  (info->by*info->cz - info->cy*info->bz)/det;
  Ay = -(info->bx*info->cz - info->cx*info->bz)/det;
  Az =  (info->bx*info->cy - info->cx*info->by)/det;
  Bx = -(info->ay*info->cz - info->cy*info->az)/det;
  By =  (info->ax*info->cz - info->cx*info->az)/det;
  Bz = -(info->ax*info->cy - info->cx*info->ay)/det;
  Cx =  (info->ay*info->bz - info->by*info->az)/det;
  Cy = -(info->ax*info->bz - info->bx*info->az)/det;
  Cz =  (info->ax*info->by - info->bx*info->ay)/det;

  DEBUGPRINT3("A-1: %f %f %f\n", Ax, Ay, Az);  
  DEBUGPRINT3("B-1: %f %f %f\n", Bx, By, Bz);  
  DEBUGPRINT3("C-1: %f %f %f\n", Cx, Cy, Cz);  
  DEBUGPRINT3("L: %f %f %f\n", La, Lb, Lc);

  // out->StartN
  out->HeaderStartN.x = round(info->sx/out->HeaderLength.x); 
  out->HeaderStartN.y = round(info->sy/out->HeaderLength.y); 
  out->HeaderStartN.z = round(info->sz/out->HeaderLength.z); 

	for(zout=0; zout<out->HeaderN.z; zout++) {
	for(yout=0; yout<out->HeaderN.y; yout++) {
	for(xout=0; xout<out->HeaderN.x; xout++) {
  /*
    xout      ax      bx      cx
    yout = na ay + nb by + nc cy 
    zout      az      bz      cz

        ax bx cx    xout      na
    A = ay by cy    yout  = A nb 
        az bz cz ,  zout      nc

    na        xout
    nb = A^-1 yout
    nc        zout

  */
    realxout = xout*in->HeaderLength.x;
    realyout = yout*in->HeaderLength.y;
    realzout = zout*in->HeaderLength.z;
    
    na = Ax*realxout + Ay*realyout + Az*realzout; 
    nb = Bx*realxout + By*realyout + Bz*realzout;
    nc = Cx*realxout + Cy*realyout + Cz*realzout;
    //DEBUGPRINT3("d: %f %f %f\n", na, nb, nc);
    DEBUGPRINT6("n: %f %f %f at %f %f %f\n", na, nb, nc, realxout, realyout, realzout);

    flagInCrystal = 1;

    if(flagInCrystal) { // in cyrstal
        // Position of In Unit Cell
        orgna = na - floor(na);
        orgnb = nb - floor(nb);
        orgnc = nc - floor(nc);
        
        // pixel                                       Angstrom  + start              -> pixel    -> Start              
        orgx = (orgna*info->ax + orgnb*info->bx + orgnc*info->cx + info->sx)/in->HeaderLength.x - in->HeaderStartN.x;  
        orgy = (orgna*info->ay + orgnb*info->by + orgnc*info->cy + info->sy)/in->HeaderLength.y - in->HeaderStartN.y;  
        orgz = (orgna*info->az + orgnb*info->bz + orgnc*info->cz + info->sz)/in->HeaderLength.z - in->HeaderStartN.z;  
        
        DEBUGPRINT6("n(unit): %f %f %f coord(unit):  %f %f %f\n", orgna, orgnb, orgnc, orgx, orgy, orgz);

				mrcPixelDataGet(in,  orgx, orgy, orgz, &data, mrcPixelRePart, info->pixelMode);
				mrcPixelDataSet(out, xout, yout, zout,  data, mrcPixelRePart);
    }
	}
	}
	}
}
