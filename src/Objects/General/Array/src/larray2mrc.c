/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% larray2mrc ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : larray2mrc 
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%larray2mrc ver%I%; Date:%D% %Z%";


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  

#define DEBUG
#include "genUtil.h"
#include "Array.h"
#include "mrcImage.h"
#include "larray2mrc.h"

void 
larray2mrc(mrcImage* out, Array array, larray2mrcInfo* linfo, int mode)
{
	int i, j, k;
    int nx, ny, nz;


	mrcDefaultHeaderValueSet(out);	
	out->HeaderMode = linfo->mrcMode;




	out->HeaderLength.x = linfo->mrcLengthX;
    out->HeaderLength.y = linfo->mrcLengthY;
    out->HeaderLength.z = linfo->mrcLengthZ;
	switch(array.dim){
		case 1 :
			out->HeaderN.x = (int)array.n[linfo->ax-1];
			out->HeaderN.y = 0;
			out->HeaderN.z = 0;
			break;
		case 2 :
			out->HeaderN.x = (int)array.n[linfo->ax-1];
			out->HeaderN.y = (int)array.n[linfo->ay-1];
			out->HeaderN.z = 0;
			break;
		case 3 :
			out->HeaderN.x = (int)array.n[linfo->ax-1];
			out->HeaderN.y = (int)array.n[linfo->ay-1];
			out->HeaderN.z = (int)array.n[linfo->az-1];
			break;
		default: {
			fprintf(stderr, "Not supported array.dim in larray2mrc: %ld\n", array.dim);
		}
	}	
	mrcInit(out, NULL);


	switch(array.dim){
		case 1:
			for(j=0; j<array.n[linfo->ax-1]; j++){
				mrcPixelDataSet(out, j, 0, 0, array.A[j], mrcPixelRePart);
			}
			break;
		case 2:
			for(i=0; i<array.n[1]; i++){
			for(j=0; j<array.n[0]; j++){
                if(linfo->ax==1 && linfo->ay==2) {
				    mrcPixelDataSet(out, j, i, 0, array.A[j+i*array.n[0]], mrcPixelRePart);
                } else {
				    mrcPixelDataSet(out, i, j, 0, array.A[j+i*array.n[0]], mrcPixelRePart);
                }
			}
			}
			break;
		case 3:
			for(k=0; k<array.n[2]; k++){
			for(i=0; i<array.n[1]; i++){
			for(j=0; j<array.n[0]; j++){
                if(linfo->ax==1 && linfo->ay==2 && linfo->az==3) {
				    mrcPixelDataSet(out, j, i, k, array.A[j+i*array.n[0]+k*array.n[0]*array.n[1]], mrcPixelRePart);
                } else if(linfo->ax==1 && linfo->ay==3 && linfo->az==2) {
				    mrcPixelDataSet(out, j, k, i, array.A[j+i*array.n[0]+k*array.n[0]*array.n[1]], mrcPixelRePart);
                } else if(linfo->ax==2 && linfo->ay==1 && linfo->az==3) {
				    mrcPixelDataSet(out, i, j, k, array.A[j+i*array.n[0]+k*array.n[0]*array.n[1]], mrcPixelRePart);
                } else if(linfo->ax==2 && linfo->ay==3 && linfo->az==1) {
				    mrcPixelDataSet(out, i, k, j, array.A[j+i*array.n[0]+k*array.n[0]*array.n[1]], mrcPixelRePart);
                } else if(linfo->ax==3 && linfo->ay==1 && linfo->az==2) {
				    mrcPixelDataSet(out, k, j, i, array.A[j+i*array.n[0]+k*array.n[0]*array.n[1]], mrcPixelRePart);
                } else if(linfo->ax==3 && linfo->ay==2 && linfo->az==1) {
				    mrcPixelDataSet(out, k, i, j, array.A[j+i*array.n[0]+k*array.n[0]*array.n[1]], mrcPixelRePart);
                }
			}
			}
			}
			break;
	}
}
