/*
# lmrcImageMasking.c  1.1
# The latest update : 01/23/97 at 10:38:49
#
#@(#) lmrcImageMasking ver 1.1
#@(#) Created by
#@(#)
#@(#) Usage : lmrcImageMasking
#@(#) Attention
#@(#)
*/
static char __sccs_id[] = "@(#)lmrcImageMasking ver1.1; Date:97/01/23 @(#)";

#include <stdio.h>
#include <stdlib.h>

#undef DEBUG
#include "genUtil.h"
#include "mrcImage.h"
#include "lmrcImageMasking.h"

void
lmrcImageMasking(mrcImage* out, mrcImage* in, lmrcImageMaskingInfo* linfo, int mode)
{
	mrcImageParaTypeInteger x, y, z;
	double data;
	double sum;
	int count;
	double avg;
	mrcImageParaTypeReal sx, sy, sz;
	floatVector nx, ny, nz, cx0, cx1, cy0, cy1, cz0, cz1;
	floatVector tmp;
	Matrix3D mat;
	Matrix3D matRotAnti;
	Matrix3D matRot;
	float x0, x1, y0, y1, z0, z1;
    int flagIn = 0;
    int flagAvg = 0;
    int orgData;

	out->Header =	in->Header;
	mrcInit (out, NULL);

	if(linfo->flagRotation) {
		floatVectorInit(&nx, 4);
		floatVectorInit(&ny, 4);
		floatVectorInit(&nz, 4);
		floatVectorInit(&cx0, 4);
		floatVectorInit(&cx1, 4);
		floatVectorInit(&cy0, 4);
		floatVectorInit(&cy1, 4);
		floatVectorInit(&cz0, 4);
		floatVectorInit(&cz1, 4);
		floatVectorInit(&tmp, 4);

		nx.data[0] = 1; nx.data[1] = 0; nx.data[2] = 0; nx.data[3] = 1;
		ny.data[0] = 0; ny.data[1] = 1; ny.data[2] = 0; ny.data[3] = 1;
        nz.data[0] = 0; nz.data[1] = 0; nz.data[2] = 1; nz.data[3] = 1;

		cx0.data[0] = -linfo->n.x/2.0;   cx0.data[1] = 0; cx0.data[2] = 0; cx0.data[3] = 1;
		cx1.data[0] = +linfo->n.x/2.0;   cx1.data[1] = 0; cx1.data[2] = 0; cx1.data[3] = 1;
		cy0.data[0] = 0;   cy0.data[1] = -linfo->n.y/2.0; cy0.data[2] = 0; cy0.data[3] = 1;
		cy1.data[0] = 0;   cy1.data[1] = +linfo->n.y/2.0; cy1.data[2] = 0; cy1.data[3] = 1;
		cz0.data[0] = 0;   cz0.data[1] = 0; cz0.data[2] = -linfo->n.z/2.0; cz0.data[3] = 1;
		cz1.data[0] = 0;   cz1.data[1] = 0; cz1.data[2] = +linfo->n.z/2.0; cz1.data[3] = 1;

		tmp.data[0] = 0; tmp.data[1] = 0; tmp.data[2] = 0; tmp.data[3] = 1;

		matrix3DRotationAntiSetFollowingEulerAngle(matRotAnti, linfo->Euler, linfo->Rot1, linfo->Rot2, linfo->Rot3,  MATRIX_3D_MODE_INITIALIZE);
		matrix3DRotationSetFollowingEulerAngle    (matRot,     linfo->Euler, linfo->Rot1, linfo->Rot2, linfo->Rot3,  MATRIX_3D_MODE_INITIALIZE);

		matrix3DRotationSetFollowingEulerAngle(mat, linfo->Euler, linfo->Rot1, linfo->Rot2, linfo->Rot3,  MATRIX_3D_MODE_INITIALIZE);
		matrix3DTranslationSet(mat, linfo->c.x , linfo->c.y, linfo->c.z, MATRIX_3D_MODE_NOT_INITIALIZE);

		matrix3DMultiplyVector(&nx, matRot); DEBUGPRINT3("nx %f %f %f\n", nx.data[0], nx.data[1], nx.data[2]);
		matrix3DMultiplyVector(&ny, matRot); DEBUGPRINT3("ny %f %f %f\n", ny.data[0], ny.data[1], ny.data[2]);
		matrix3DMultiplyVector(&nz, matRot); DEBUGPRINT3("nz %f %f %f\n", nz.data[0], nz.data[1], nz.data[2]);
		matrix3DMultiplyVector(&cx0, mat);   DEBUGPRINT3("cx0 %f %f %f\n", cx0.data[0], cx0.data[1], cx0.data[2]);
		matrix3DMultiplyVector(&cy0, mat);   DEBUGPRINT3("cy0 %f %f %f\n", cy0.data[0], cy0.data[1], cy0.data[2]);
		matrix3DMultiplyVector(&cz0, mat);   DEBUGPRINT3("cz0 %f %f %f\n", cz0.data[0], cz0.data[1], cz0.data[2]);
		matrix3DMultiplyVector(&cx1, mat);   DEBUGPRINT3("cx1 %f %f %f\n", cx1.data[0], cx1.data[1], cx1.data[2]);
		matrix3DMultiplyVector(&cy1, mat);   DEBUGPRINT3("cy1 %f %f %f\n", cy1.data[0], cy1.data[1], cy1.data[2]);
		matrix3DMultiplyVector(&cz1, mat);   DEBUGPRINT3("cz1 %f %f %f\n", cz1.data[0], cz1.data[1], cz1.data[2]);

	}

    if(linfo->mode==1) {
	    orgData = 1;
    } else {
        orgData = 0;
    }

	DEBUGPRINT3("shape %d mode %d rotation %d\n", linfo->shape, linfo->mode, linfo->flagRotation);
	switch(linfo->shape) {
		case lmrcImageMaskingInfoShapeSphere:
			DEBUGPRINT("lmrcImageMaskingInfoShapeSphere\n");
			sum	 = 0.0; count = 0; avg = 0;
			if (linfo->mode==0){ // Calculate Average density outside a sphere
				for(z=0; z<out->HeaderN.z; z++) {
				for(y=0; y<out->HeaderN.y; y++) {
				for(x=0; x<out->HeaderN.x; x++) {
					if(!linfo->flagRotation) {
						if(SQR((x - linfo->c.x )/(linfo->n.x/2.0))
					 	 + SQR((y - linfo->c.y )/(linfo->n.y/2.0))
				 	 	 + SQR((z - linfo->c.z )/(linfo->n.z/2.0)) >= 1) { // Outside
						 	mrcPixelDataGet(in, x, y, z,	&data, mrcPixelRePart, mrcPixelHowNearest);
							sum += data;
							count ++;
						}
					} else {
						tmp.data[0] = x - linfo->c.x;
						tmp.data[1] = y - linfo->c.y;
						tmp.data[2] = z - linfo->c.z;
						matrix3DMultiplyVector(&tmp, matRotAnti);
						if(SQR((tmp.data[0])/(linfo->n.x/2.0))
					 	 + SQR((tmp.data[1])/(linfo->n.y/2.0))
				 	 	 + SQR((tmp.data[2])/(linfo->n.z/2.0)) >= 1) {    // Outside
						 	mrcPixelDataGet(in, x, y, z,	&data, mrcPixelRePart, mrcPixelHowNearest);
							sum += data;
							count ++;
						}
					}
				}
				}
				}
				if(0<count) {
					avg = sum/count;
				}
			}
			DEBUGPRINT2("average %f %d\n", avg, count);

			for(z=0; z<out->HeaderN.z; z++) {
			for(y=0; y<out->HeaderN.y; y++) {
			for(x=0; x<out->HeaderN.x; x++) {
				data = orgData;
                flagIn = 0;
				if(!linfo->flagRotation) {
					if(SQR((x - linfo->c.x )/(linfo->n.x/2.0))
				 	 + SQR((y - linfo->c.y )/(linfo->n.y/2.0))
				 	 + SQR((z - linfo->c.z )/(linfo->n.z/2.0)) <= 1) { // Inside
					 	mrcPixelDataGet(in, x, y, z,	&data, mrcPixelRePart, mrcPixelHowNearest);
                        flagIn = 1;
					}
				} else {
					tmp.data[0] = x -linfo->c.x;
					tmp.data[1] = y -linfo->c.y;
					tmp.data[2] = z -linfo->c.z;
					matrix3DMultiplyVector(&tmp, matRotAnti);
					if(SQR((tmp.data[0])/(linfo->n.x/2.0))
					 + SQR((tmp.data[1])/(linfo->n.y/2.0))
				 	 + SQR((tmp.data[2])/(linfo->n.z/2.0)) <= 1) {     // Inside
					 	mrcPixelDataGet(in, x, y, z,	&data, mrcPixelRePart, mrcPixelHowNearest);
                        flagIn=1;
					}
				}
                if(flagIn==1) {
					if(linfo->mode==0) {
						data -= avg;
					} else if(linfo->mode==1)  {
						data = 0;
					} else if(linfo->mode==2) {
                        data = 1;
                    }
                }
				mrcPixelDataSet(out, x, y, z, data, mrcPixelRePart);
			}
			}
			}
			break;

		case lmrcImageMaskingInfoSquare:
			sum	 = 0.0; count = 0; avg = 0;
			if (linfo->mode==0){
				for(z=0; z<out->HeaderN.z; z++) {
				for(y=0; y<out->HeaderN.y; y++) {
				for(x=0; x<out->HeaderN.x; x++) {
					if(!linfo->flagRotation) {
						if(	fabs(x - linfo->c.x ) > (linfo->n.x/2.0)
			 			 || fabs(y - linfo->c.y ) > (linfo->n.y/2.0)
						 || fabs(z - linfo->c.z ) > (linfo->n.z/2.0) ) { // Outside
							mrcPixelDataGet(in, x, y, z,	&data, mrcPixelRePart, mrcPixelHowNearest);
							sum += data;
							count++;
						}
					} else {
						x0 = (nx.data[0]*(x-cx0.data[0])+nx.data[1]*(y-cx0.data[1])+nx.data[2]*(z-cx0.data[2]));
						x1 = (nx.data[0]*(x-cx1.data[0])+nx.data[1]*(y-cx1.data[1])+nx.data[2]*(z-cx1.data[2]));
						y0 = (ny.data[0]*(x-cy0.data[0])+ny.data[1]*(y-cy0.data[1])+ny.data[2]*(z-cy0.data[2]));
						y1 = (ny.data[0]*(x-cy1.data[0])+ny.data[1]*(y-cy1.data[1])+ny.data[2]*(z-cy1.data[2]));
						z0 = (nz.data[0]*(x-cz0.data[0])+nz.data[1]*(y-cz0.data[1])+nz.data[2]*(z-cz0.data[2]));
						z1 = (nz.data[0]*(x-cz1.data[0])+nz.data[1]*(y-cz1.data[1])+nz.data[2]*(z-cz1.data[2]));
						if(x0*x1 > 0 || y0*y1 > 0 || z0*z1 > 0) { //
							//DEBUGPRINT6("x0-z1: %f %f %f %f %f %f\n", x0, x1, y0, y1, z0, z1);
							mrcPixelDataGet(in, x, y, z,	&data, mrcPixelRePart, mrcPixelHowNearest);
							sum += data;
							count++;
						}
					}
				}
				}
				}
				if(0<count) {
					avg = sum/count;
				}
			}
			DEBUGPRINT2("average %f %d\n", avg, count);

			for(z=0; z<out->HeaderN.z; z++) {
			for(y=0; y<out->HeaderN.y; y++) {
			for(x=0; x<out->HeaderN.x; x++) {
				data = orgData;
                flagIn = 0;
				if(!linfo->flagRotation) {
					//DEBUGPRINT("Not Rotated\n")
					if(	fabs(x - linfo->c.x ) <= (linfo->n.x/2.0)
					 && fabs(y - linfo->c.y ) <= (linfo->n.y/2.0)
					 && fabs(z - linfo->c.z ) <= (linfo->n.z/2.0) ) { // Inside
						mrcPixelDataGet(in, x, y, z,	&data, mrcPixelRePart, mrcPixelHowNearest);
						DEBUGPRINT3("(%d, %d, %d) inside square\n", x, y, z);
                        flagIn = 1;
					}
				} else {
					x0 = (nx.data[0]*(x-cx0.data[0])+nx.data[1]*(y-cx0.data[1])+nx.data[2]*(z-cx0.data[2]));
					x1 = (nx.data[0]*(x-cx1.data[0])+nx.data[1]*(y-cx1.data[1])+nx.data[2]*(z-cx1.data[2]));
					y0 = (ny.data[0]*(x-cy0.data[0])+ny.data[1]*(y-cy0.data[1])+ny.data[2]*(z-cy0.data[2]));
					y1 = (ny.data[0]*(x-cy1.data[0])+ny.data[1]*(y-cy1.data[1])+ny.data[2]*(z-cy1.data[2]));
					z0 = (nz.data[0]*(x-cz0.data[0])+nz.data[1]*(y-cz0.data[1])+nz.data[2]*(z-cz0.data[2]));
					z1 = (nz.data[0]*(x-cz1.data[0])+nz.data[1]*(y-cz1.data[1])+nz.data[2]*(z-cz1.data[2]));
                    if(x0*x1 <= 0 && y0*y1 <= 0 && z0*z1 <= 0) {
					    mrcPixelDataGet(in, x, y, z,	&data, mrcPixelRePart, mrcPixelHowNearest);
                        flagIn = 1;
                    }
				}
                if(flagIn==1) {
				    if(linfo->mode==0) {
					    data -= avg;
				    } else if(linfo->mode==1) {
				        data = 0.0;
				    } else if(linfo->mode==2) {
                        data = 1.0;
                    }
                }
				mrcPixelDataSet(out, x, y, z, data, mrcPixelRePart);
			}
			}
			}
			break;

		case lmrcImageMaskingInfoCylinder:
			sum	 = 0.0; count = 0; avg = 0;
			if (linfo->mode==0){
				for(z=0; z<out->HeaderN.z; z++) {
				for(y=0; y<out->HeaderN.y; y++) {
				for(x=0; x<out->HeaderN.x; x++) {
					if(!linfo->flagRotation) {
						if(	SQR((x - linfo->c.x )/(linfo->n.x/2.0))
			 			  + SQR((y - linfo->c.y )/(linfo->n.y/2.0)) > 1
						 || fabs(z - linfo->c.z ) > (linfo->n.z/2.0) ) { // Outside
							mrcPixelDataGet(in, x, y, z,	&data, mrcPixelRePart, mrcPixelHowNearest);
							sum += data;
							count++;
						}
					} else {
						tmp.data[0] = x -linfo->c.x;
						tmp.data[1] = y -linfo->c.y;
						tmp.data[2] = z -linfo->c.z;
						matrix3DMultiplyVector(&tmp, matRotAnti);
						z0 = (nz.data[0]*(x-cz0.data[0])+nz.data[1]*(y-cz0.data[1])+nz.data[2]*(z-cz0.data[2]));
						z1 = (nz.data[0]*(x-cz1.data[0])+nz.data[1]*(y-cz1.data[1])+nz.data[2]*(z-cz1.data[2]));
						if(SQR((tmp.data[0])/(linfo->n.x/2.0))
					 	 + SQR((tmp.data[1])/(linfo->n.y/2.0))  > 1
				 	 	|| z0*z1 > 0) {                                  // Outside
							mrcPixelDataGet(in, x, y, z,	&data, mrcPixelRePart, mrcPixelHowNearest);
							sum += data;
							count++;
						}
					}
				}
				}
				}
				if(0<count) {
					avg = sum/count;
				}
			}
			DEBUGPRINT2("average %f %d\n", avg, count);

			for(z=0; z<out->HeaderN.z; z++) {
			for(y=0; y<out->HeaderN.y; y++) {
			for(x=0; x<out->HeaderN.x; x++) {
				data = orgData;
                flagIn = 0;
				if(!linfo->flagRotation) {
					//DEBUGPRINT("Not Rotated\n")
					if(SQR((x - linfo->c.x )/(linfo->n.x/2.0))
			 		 + SQR((y - linfo->c.y )/(linfo->n.y/2.0)) <= 1
					&& fabs(z - linfo->c.z ) <= (linfo->n.z/2.0) ) { // Inside
						mrcPixelDataGet(in, x, y, z,	&data, mrcPixelRePart, mrcPixelHowNearest);
                        flagIn = 1;
						DEBUGPRINT3("(%d, %d, %d) inside square\n", x, y, z);
					}
				} else {
					tmp.data[0] = x -linfo->c.x;
					tmp.data[1] = y -linfo->c.y;
					tmp.data[2] = z -linfo->c.z;
					matrix3DMultiplyVector(&tmp, matRotAnti);
					z0 = (nz.data[0]*(x-cz0.data[0])+nz.data[1]*(y-cz0.data[1])+nz.data[2]*(z-cz0.data[2]));
					z1 = (nz.data[0]*(x-cz1.data[0])+nz.data[1]*(y-cz1.data[1])+nz.data[2]*(z-cz1.data[2]));
					if(SQR((tmp.data[0])/(linfo->n.x/2.0))
					 + SQR((tmp.data[1])/(linfo->n.y/2.0)) <= 1
				 	&& z0*z1 <= 0) {   // Inside
						mrcPixelDataGet(in, x, y, z,	&data, mrcPixelRePart, mrcPixelHowNearest);
                        flagIn = 1;
					}
				}
                if(flagIn==1) {
				    if(linfo->mode==0) {
					    data -= avg;
				    } else if(linfo->mode==1) {
				        data = 0.0;
				    } else if(linfo->mode==2) {
                        data = 1.0;
                    }
                }
				mrcPixelDataSet(out, x, y, z, data, mrcPixelRePart);
			}
			}
			}
			break;

		case lmrcImageMaskingInfoRoundedSquare:
			sum	 = 0.0; count = 0; avg = 0;
			if (linfo->mode==0){
				for(z=0; z<out->HeaderN.z; z++) {
				for(y=0; y<out->HeaderN.y; y++) {
				for(x=0; x<out->HeaderN.x; x++) {
					if(!linfo->flagRotation) {
						if(	fabs(x - linfo->c.x ) > (linfo->n.x/2.0)
			 			 || fabs(y - linfo->c.y ) > (linfo->n.y/2.0)
						 || fabs(z - linfo->c.z ) > (linfo->n.z/2.0) ) { // Outside
							mrcPixelDataGet(in, x, y, z,	&data, mrcPixelRePart, mrcPixelHowNearest);
							sum += data;
							count++;
						}
					} else {
						x0 = (nx.data[0]*(x-cx0.data[0])+nx.data[1]*(y-cx0.data[1])+nx.data[2]*(z-cx0.data[2]));
						x1 = (nx.data[0]*(x-cx1.data[0])+nx.data[1]*(y-cx1.data[1])+nx.data[2]*(z-cx1.data[2]));
						y0 = (ny.data[0]*(x-cy0.data[0])+ny.data[1]*(y-cy0.data[1])+ny.data[2]*(z-cy0.data[2]));
						y1 = (ny.data[0]*(x-cy1.data[0])+ny.data[1]*(y-cy1.data[1])+ny.data[2]*(z-cy1.data[2]));
						z0 = (nz.data[0]*(x-cz0.data[0])+nz.data[1]*(y-cz0.data[1])+nz.data[2]*(z-cz0.data[2]));
						z1 = (nz.data[0]*(x-cz1.data[0])+nz.data[1]*(y-cz1.data[1])+nz.data[2]*(z-cz1.data[2]));
						if(x0*x1 > 0 || y0*y1 > 0 || z0*z1 > 0) { //
							//DEBUGPRINT6("x0-z1: %f %f %f %f %f %f\n", x0, x1, y0, y1, z0, z1);
							mrcPixelDataGet(in, x, y, z,	&data, mrcPixelRePart, mrcPixelHowNearest);
							sum += data;
							count++;
						}
					}
				}
				}
				}
				if(0<count) {
					avg = sum/count;
				}
			}
			DEBUGPRINT2("average %f %d\n", avg, count);

			for(z=0; z<out->HeaderN.z; z++) {
			for(y=0; y<out->HeaderN.y; y++) {
			for(x=0; x<out->HeaderN.x; x++) {
				data = orgData;
                flagIn = 0;
				if(!linfo->flagRotation) {
					//DEBUGPRINT("Not Rotated\n")
					if(	fabs(x - linfo->c.x ) <= (linfo->n.x/2.0)
					 && fabs(y - linfo->c.y ) <= (linfo->n.y/2.0)
					 && fabs(z - linfo->c.z ) <= (linfo->n.z/2.0) ) { // Inside
						mrcPixelDataGet(in, x, y, z,	&data, mrcPixelRePart, mrcPixelHowNearest);
						DEBUGPRINT3("(%d, %d, %d) inside square\n", x, y, z);
                        flagIn = 1;
					}
				} else {
					x0 = (nx.data[0]*(x-cx0.data[0])+nx.data[1]*(y-cx0.data[1])+nx.data[2]*(z-cx0.data[2]));
					x1 = (nx.data[0]*(x-cx1.data[0])+nx.data[1]*(y-cx1.data[1])+nx.data[2]*(z-cx1.data[2]));
					y0 = (ny.data[0]*(x-cy0.data[0])+ny.data[1]*(y-cy0.data[1])+ny.data[2]*(z-cy0.data[2]));
					y1 = (ny.data[0]*(x-cy1.data[0])+ny.data[1]*(y-cy1.data[1])+ny.data[2]*(z-cy1.data[2]));
					z0 = (nz.data[0]*(x-cz0.data[0])+nz.data[1]*(y-cz0.data[1])+nz.data[2]*(z-cz0.data[2]));
					z1 = (nz.data[0]*(x-cz1.data[0])+nz.data[1]*(y-cz1.data[1])+nz.data[2]*(z-cz1.data[2]));
                    if(x0*x1 <= 0 && y0*y1 <= 0 && z0*z1 <= 0) {
					    mrcPixelDataGet(in, x, y, z,	&data, mrcPixelRePart, mrcPixelHowNearest);
                        flagIn = 1;
                    }
				}
                if(flagIn==1) {
				    if(linfo->mode==0) {
					    data -= avg;
				    } else if(linfo->mode==1) {
				        data = 0.0;
				    } else if(linfo->mode==2) {
                        data = 1.0;
                    }
                }
				mrcPixelDataSet(out, x, y, z, data, mrcPixelRePart);
			}
			}
			}
			break;

		default: {
			fprintf(stderr, "Not supported shape: %d\n", linfo->shape);
			exit(EXIT_FAILURE);
			break;
		}
	}
}
