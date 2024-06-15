/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% lmrcImageMeanFreePath ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : lmrcImageMeanFreePath 
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%lmrcImageMeanFreePath ver%I%; Date:%D% %Z%";


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  

#undef DEBUG
#include "./lmrcImageMeanFreePath.h"


void
lmrcImageMeanFreePathCalcModePrint(FILE* fpt)
{
	fprintf(fpt, ">>>> mode \n");
	fprintf(fpt, "%d: Along Z-axis\n", MeanFreePathCalcModeAlongZaxis);
	fprintf(fpt, "%d: Along X-axis\n", MeanFreePathCalcModeAlongXaxis);
	fprintf(fpt, "%d: Along Y-axis\n", MeanFreePathCalcModeAlongYaxis);
	fprintf(fpt, "%d: For any direction\n", MeanFreePathCalcModeAnyDirection);
	fprintf(fpt, "+%d: Length is shown in real using HeaderLength \n", MeanFreePathCalcModeRealLength);

	fprintf(fpt, ">>>> line shape\n");
	fprintf(fpt, "%d: LineShape-Rectangle\n", lmrcImageMeanFreePathCalcLineShapeRectangle);
	fprintf(fpt, "%d: LineShape-Disk\n", lmrcImageMeanFreePathCalcLineShapeDisk);
	fprintf(fpt, ">>>> line mode\n");
	fprintf(fpt, "%d: LineMode-And \n", lmrcImageMeanFreePathCalcLineModeAnd);
	fprintf(fpt, "%d: LineMode-Or  \n", lmrcImageMeanFreePathCalcLineModeOr);
	fprintf(fpt, "%d: LineMode-GE(Greater than or equal to) \n", lmrcImageMeanFreePathCalcLineModeGE);
}

void
lmrcImageMeanFreePathCalc(mrcImage* in, lmrcImageMeanFreePathCalcInfo* linfo, lmrcImageMeanFreePathCalcMode mode)
{
	mrcImage tmp;
	DEBUGPRINT1("mode: %d in Calc 1st \n", mode);
	switch(MeanFreePathCalcModeCalcMode&mode) {
		case MeanFreePathCalcModeAlongZaxis: {
			DEBUGPRINT1("mode: %d in AlongZaxis\n", mode);
			lmrcImageMeanFreePathCalcAlongZaxis(in, linfo, mode);
			break;
		}
		case MeanFreePathCalcModeAlongXaxis: {
			DEBUGPRINT1("mode: %d in AlongXaxis\n", mode);
			lmrcImageTranspose(&tmp, in, 4, 0); 
			lmrcImageMeanFreePathCalcAlongZaxis(&tmp, linfo, mode);
			break;
		}
		case MeanFreePathCalcModeAlongYaxis: {
			DEBUGPRINT1("mode: %d in AlongYaxis\n", mode);
			lmrcImageTranspose(&tmp, in, 2, 0); 
			lmrcImageMeanFreePathCalcAlongZaxis(&tmp, linfo, mode);
			break;
		}
		case MeanFreePathCalcModeAnyDirection: {
			DEBUGPRINT1("mode: %d in Any Direction\n", mode);
			lmrcImageMeanFreePathCalcAnyDirection(in, linfo, mode);
			break;
		}
		default: {
			DEBUGPRINT1("mode: %d in default\n", mode);
			fprintf(stderr, "Not supported mode: %d\n", mode);
			fprintf(stderr, "Thus, process as -m %d \n", MeanFreePathCalcModeAlongZaxis);
			lmrcImageMeanFreePathCalcAlongZaxis(in, linfo, mode);
			break;
		}
	}
}

void
lmrcImageMeanFreePathCalcPrint(FILE* fpt, lmrcImageMeanFreePathCalcInfo* linfo, lmrcImageMeanFreePathCalcMode mode)
{
	int i;

	fprintf(fpt, "ANALYSIS Average HowManyLines HowManyVoxels\n");
	fprintf(fpt, "White: %15.6f %d %d\n", linfo->averageWhite, linfo->sumWhite, linfo->countWhite[0]);
	fprintf(fpt, "Black: %15.6f %d %d\n", linfo->averageBlack, linfo->sumBlack, linfo->countBlack[0]);
	fprintf(fpt, "WhiteEdge: %15.6f %d %d\n", linfo->averageWhiteEdge, linfo->sumWhiteEdge, linfo->countWhiteEdge[0]);
	fprintf(fpt, "BlackEdge: %15.6f %d %d\n", linfo->averageBlackEdge, linfo->sumBlackEdge, linfo->countBlackEdge[0]);
	fprintf(fpt, "\n");
	fprintf(fpt, "DATA: \n");
	fprintf(fpt, "%6s %10s %10s %10s %10s %15s %15s %15s %15s %15s %15s %15s %15s %15s\n", 
		"length", "White", "Black", "WhiteEdge", "BlackEdge",
		          "rateWhite", "rateBlack", "rateWhiteEdge", "rateBlackEdge",
				  "aveWhite", "aveBlack", "aveWhiteEdge", "aveBlackEdge", "realLength");
	for(i=1; i<=linfo->N; i++) {
		fprintf(fpt, "%6d %10d %10d %10d %10d %15.6f %15.6f %15.6f %15.6f %15.6f %15.6f %15.6f %15.6f %15.6f\n", 
			i,
			linfo->countWhite[i], 
			linfo->countBlack[i],
			linfo->countWhiteEdge[i], 
			linfo->countBlackEdge[i],
			(linfo->countWhite[0]?linfo->countWhite[i]/(double)linfo->countWhite[0]*100:0), 
			(linfo->countBlack[0]?linfo->countBlack[i]/(double)linfo->countBlack[0]*100:0),
			(linfo->countWhiteEdge[0]?linfo->countWhiteEdge[i]/(double)linfo->countWhiteEdge[0]*100:0), 
			(linfo->countBlackEdge[0]?linfo->countBlackEdge[i]/(double)linfo->countBlackEdge[0]*100:0),
			(linfo->sumWhite?linfo->countWhite[i]/(double)linfo->sumWhite*100:0), 
			(linfo->sumBlack?linfo->countBlack[i]/(double)linfo->sumBlack*100:0),
			(linfo->sumWhiteEdge?linfo->countWhiteEdge[i]/(double)linfo->sumWhiteEdge*100:0), 
			(linfo->sumBlackEdge?linfo->countBlackEdge[i]/(double)linfo->sumBlackEdge*100:0),
			i*linfo->Length.z);
	}
}


void
lmrcImageMeanFreePathCalcAlongZaxis(mrcImage* in, lmrcImageMeanFreePathCalcInfo* linfo, lmrcImageMeanFreePathCalcMode mode)
{
	int* countBlack;
	int* countWhite; 
	int* countBlackEdge; 
	int* countWhiteEdge; 
	int x, y, z;
	int srcx, srcy;
	//int minx, miny;
	//int maxx, maxy;
	int flagEdge;
	double data;
	double data0;
	double prevData;
	int lengthWhite;
	int lengthBlack;
	int i;
	int k;
	
	countBlack     = memoryAllocate(sizeof(int)*(in->HeaderN.z+1), "in lmrcImageMeanFreePathCalc");
	countWhite     = memoryAllocate(sizeof(int)*(in->HeaderN.z+1), "in lmrcImageMeanFreePathCalc");
	countBlackEdge = memoryAllocate(sizeof(int)*(in->HeaderN.z+1), "in lmrcImageMeanFreePathCalc");
	countWhiteEdge = memoryAllocate(sizeof(int)*(in->HeaderN.z+1), "in lmrcImageMeanFreePathCalc");

	linfo->white.Header = in->Header;	
	linfo->black.Header = in->Header;	
	linfo->whiteEdge.Header = in->Header;	
	linfo->blackEdge.Header = in->Header;	
	mrcInit(&linfo->white, NULL);
	mrcInit(&linfo->black, NULL);
	mrcInit(&linfo->whiteEdge, NULL);
	mrcInit(&linfo->blackEdge, NULL);

	linfo->countBlack = countBlack;
	linfo->countWhite = countWhite;
	linfo->countBlackEdge = countBlackEdge;
	linfo->countWhiteEdge = countWhiteEdge;
	linfo->N = in->HeaderN.z;

	for(y=0; y<in->HeaderN.y; y++) {
		linfo->min.y = floor(y - linfo->LineThickness.y/2.0 + 0.5); 
		linfo->max.y = floor(y + linfo->LineThickness.y/2.0 + 0.5); 
		linfo->cur.y = y;
	for(x=0; x<in->HeaderN.x; x++) {
		linfo->min.x = floor(x - linfo->LineThickness.x/2.0 + 0.5); 
		linfo->max.x = floor(x + linfo->LineThickness.x/2.0 + 0.5); 
		linfo->cur.x = x;

		flagEdge = 1;
		lengthWhite = 0;
		lengthBlack = 0;

		// Start
		linfo->cur.z = 0;
		data = lmrcImageMeanFreePathCalcBWEvaluation(in, linfo, mode);

		if(0<data) {
			countWhiteEdge[0]++;		
			lengthWhite++;
		} else {
			countBlackEdge[0]++;
			lengthBlack++;
		}
		prevData = data;

		// Intermediate 
		for(z=1; z<in->HeaderN.z-1; z++) {
			linfo->cur.z = z;
			data = lmrcImageMeanFreePathCalcBWEvaluation(in, linfo, mode);

			if(0<prevData) {
				if(0<data) { // White continue
					if(flagEdge) {
						countWhiteEdge[0]++;
					} else {
						countWhite[0]++;
					}
					lengthWhite++;
				} else {     // White -> Black
					if(flagEdge) {
						countWhiteEdge[lengthWhite]++;	
						for(k=z-1; z-lengthWhite<=k; k--) {
							mrcPixelDataSet(&linfo->whiteEdge, x, y, k, lengthWhite, mrcPixelRePart);
						}
						flagEdge=0;
					} else {
						countWhite[lengthWhite]++;
						for(k=z-1; z-lengthWhite<=k; k--) {
							mrcPixelDataSet(&linfo->white, x, y, k, lengthWhite, mrcPixelRePart);
						}
					}
					countBlack[0]++;
					lengthWhite=0;			
					lengthBlack++;
				}
			} else {
				if(0<data) { // Black -> White 
					if(flagEdge) {
						countBlackEdge[lengthBlack]++;	
						for(k=z-1; z-lengthBlack<=k; k--) {
							mrcPixelDataSet(&linfo->blackEdge, x, y, k, lengthBlack, mrcPixelRePart);
						}
						flagEdge=0;
					} else {
						countBlack[lengthBlack]++;
						for(k=z-1; z-lengthBlack<=k; k--) {
							mrcPixelDataSet(&linfo->black, x, y, k, lengthBlack, mrcPixelRePart);
						}
					}
					countWhite[0]++;
					lengthBlack=0;
					lengthWhite++;
				} else {    // Black continue
					if(flagEdge) {
						countBlackEdge[0]++;	
					} else {
						countBlack[0]++;	
					}
					lengthBlack++;			
				}
			}
			prevData = data;
		}

		// End
		z = in->HeaderN.z-1;
		linfo->cur.z = z;
		data = lmrcImageMeanFreePathCalcBWEvaluation(in, linfo, mode);

		if(0<prevData) {
			if(0<data) { // White continue
				lengthWhite++;
				for(k=z; z-lengthWhite<k; k--) {
					mrcPixelDataSet(&linfo->whiteEdge, x, y, k, lengthWhite, mrcPixelRePart);
				}
				countWhiteEdge[lengthWhite]++;	
				countWhiteEdge[0]++;
			} else {     // White -> Black
				if(flagEdge) {
					countWhiteEdge[lengthWhite]++;
					for(k=z-1; z-lengthWhite<=k; k--) {
						mrcPixelDataSet(&linfo->whiteEdge, x, y, k, lengthWhite, mrcPixelRePart);
					}
				} else {
					countWhite[lengthWhite]++;
					for(k=z-1; z-lengthWhite<=k; k--) {
						mrcPixelDataSet(&linfo->white, x, y, k, lengthWhite, mrcPixelRePart);
					}
				}
				mrcPixelDataSet(&linfo->blackEdge, x, y, z, 1, mrcPixelRePart);
				countBlackEdge[1]++;	
				countBlackEdge[0]++;
			}
		} else {
			if(0<data) { // Black -> White 
				if(flagEdge) {
					countBlackEdge[lengthBlack]++;	
					for(k=z-1; z-lengthBlack<=k; k--) {
						mrcPixelDataSet(&linfo->blackEdge, x, y, k, lengthBlack, mrcPixelRePart);
					}
				} else {
					countBlack[lengthBlack]++;
					for(k=z-1; z-lengthBlack<=k; k--) {
						mrcPixelDataSet(&linfo->black, x, y, k, lengthBlack, mrcPixelRePart);
					}
				}
				mrcPixelDataSet(&linfo->whiteEdge, x, y, z, 1, mrcPixelRePart);
				countWhiteEdge[1]++;	
				countWhiteEdge[0]++;
			} else {    // Black continue
				lengthBlack++;
				countBlackEdge[lengthBlack]++;	
				for(k=z; z-lengthBlack<k; k--) {
					mrcPixelDataSet(&linfo->blackEdge, x, y, k, lengthBlack, mrcPixelRePart);
				}
				countBlackEdge[0]++;	
			}
		}
	}
	}
	lmrcImageMeanFreePathCalcMeanCalc(in, linfo, mode);
}

void
lmrcImageMeanFreePathCalcMeanCalc(mrcImage* in, lmrcImageMeanFreePathCalcInfo* linfo, lmrcImageMeanFreePathCalcMode  mode)
{
	int i;

	linfo->averageWhite = linfo->averageBlack = 0; 
	linfo->averageWhiteEdge = linfo->averageBlackEdge = 0; 
	linfo->sumWhite = linfo->sumBlack = 0; 
	linfo->sumWhiteEdge = linfo->sumBlackEdge = 0; 
	for(i=1; i<=linfo->N; i++) {
		linfo->averageWhite	    += i*i*linfo->countWhite[i];		
		linfo->averageBlack     += i*i*linfo->countBlack[i];		
		linfo->averageWhiteEdge	+= i*i*linfo->countWhiteEdge[i];			
		linfo->averageBlackEdge += i*i*linfo->countBlackEdge[i];			
		linfo->sumWhite	    += linfo->countWhite[i];		
		linfo->sumBlack     += linfo->countBlack[i];		
		linfo->sumWhiteEdge	+= linfo->countWhiteEdge[i];			
		linfo->sumBlackEdge += linfo->countBlackEdge[i];			
	}

	if(0<linfo->countWhite[0]) {
		linfo->averageWhite	    /= linfo->countWhite[0];		
	} else { 
		linfo->averageWhite	    = 0;
	}
	if(0<linfo->countBlack[0]) {
		linfo->averageBlack	    /= linfo->countBlack[0];		
	} else { 
		linfo->averageBlack	    = 0;
	}
	if(0<linfo->countWhiteEdge[0]) {
		linfo->averageWhiteEdge	    /= linfo->countWhiteEdge[0];		
	} else { 
		linfo->averageWhiteEdge	    = 0;
	}
	if(0<linfo->countBlackEdge[0]) {
		linfo->averageBlackEdge	    /= linfo->countBlackEdge[0];		
	} else { 
		linfo->averageBlackEdge	    = 0;
	}

	if(MeanFreePathCalcModeRealLength&mode) {
		DEBUGPRINT1("mode: %d in Calc: RealLength Start\n", mode);
		lmrcImageMultiplying2(&linfo->white, linfo->white.HeaderLength.z, linfo->white.HeaderMode);
		lmrcImageMultiplying2(&linfo->whiteEdge, linfo->whiteEdge.HeaderLength.z, linfo->whiteEdge.HeaderMode);
		lmrcImageMultiplying2(&linfo->black, linfo->black.HeaderLength.z, linfo->black.HeaderMode);
		lmrcImageMultiplying2(&linfo->blackEdge, linfo->blackEdge.HeaderLength.z, linfo->blackEdge.HeaderMode);
		DEBUGPRINT1("mode: %d in Calc: RealLength End\n", mode);
	}
}


double 
lmrcImageMeanFreePathCalcBWEvaluation(mrcImage* in, lmrcImageMeanFreePathCalcInfo* linfo, lmrcImageMeanFreePathCalcMode  mode)
{
	double data, data0;
	double rx, ry, r0x, r0y;
	mrcImageParaTypeReal srcx, srcy;
	int max;

	switch(linfo->LineShape) {
		case lmrcImageMeanFreePathCalcLineShapeRectangle: {
			switch(linfo->LineMode) {
				case lmrcImageMeanFreePathCalcLineModeAnd: {
					data = 1;
					for(srcy=linfo->min.y; srcy<linfo->max.y; srcy++) { 
					for(srcx=linfo->min.x; srcx<linfo->max.x; srcx++) { 
						mrcPixelDataGet(in, srcx, srcy, linfo->cur.z, &data0, mrcPixelRePart, mrcPixelHowNearest);
						data *= data0;
					}
					}
					if(0<data) data = 1;
					break;
				}
				case lmrcImageMeanFreePathCalcLineModeOr: {
					data = 0;
					for(srcy=linfo->min.y; srcy<linfo->max.y; srcy++) { 
					for(srcx=linfo->min.x; srcx<linfo->max.x; srcx++) { 
						mrcPixelDataGet(in, srcx, srcy, linfo->cur.z, &data0, mrcPixelRePart, mrcPixelHowNearest);
						data += data0;
						if(0<data) break;
					}
						if(0<data) break;
					}
					if(0<data) data = 1;
					break;
				}
				case lmrcImageMeanFreePathCalcLineModeGE: {
					data = 0;
					max  = 0;
					for(srcy=linfo->min.y; srcy<linfo->max.y; srcy++) { 
					for(srcx=linfo->min.x; srcx<linfo->max.x; srcx++) { 
						mrcPixelDataGet(in, srcx, srcy, linfo->cur.z, &data0, mrcPixelRePart, mrcPixelHowNearest);
						data += data0;
						max++;
					}
					}
					if(max/2<=data) {
						data = 1;
					}
					break;
				}
				default: {
					fprintf(stderr, "Not supported Line Mode: %d\n", linfo->LineMode);
					exit(EXIT_FAILURE);
					break;
				}
			}
			break;
		}
		case lmrcImageMeanFreePathCalcLineShapeDisk: {
			r0x = (linfo->max.x - linfo->cur.x);
			r0y = (linfo->max.y - linfo->cur.y);
			switch(linfo->LineMode) {
				case lmrcImageMeanFreePathCalcLineModeAnd: {
					data = 1;
					for(srcy=linfo->min.y; srcy<=linfo->max.y; srcy++) { 
						ry = SQR((srcy - linfo->cur.y)/r0y); 
					for(srcx=linfo->min.x; srcx<linfo->max.x; srcx++) { 
						rx = SQR((srcx - linfo->cur.x)/r0x); 

						if(rx + ry <= 1) {
							mrcPixelDataGet(in, srcx, srcy, linfo->cur.z, &data0, mrcPixelRePart, mrcPixelHowNearest);
							data *= data0;
						}
					}
					}
					if(0<data) data = 1;
					break;
				}
				case lmrcImageMeanFreePathCalcLineModeOr: {
					data = 0;
					for(srcy=linfo->min.y; srcy<linfo->max.y; srcy++) { 
						ry = SQR((srcy - linfo->cur.y)/r0y); 
					for(srcx=linfo->min.x; srcx<linfo->max.x; srcx++) { 
						rx = SQR((srcx - linfo->cur.x)/r0x); 

						if(rx + ry <= 1) {
							mrcPixelDataGet(in, srcx, srcy, linfo->cur.z, &data0, mrcPixelRePart, mrcPixelHowNearest);
							data += data0;
							if(0<data) break;
						}
					}
						if(0<data) break;
					}
					if(0<data) data = 1;
					break;
				}
				case lmrcImageMeanFreePathCalcLineModeGE: {
					data = 0;
					max  = 0;
					for(srcy=linfo->min.y; srcy<linfo->max.y; srcy++) { 
						ry = SQR((srcy - linfo->cur.y)/r0y); 
					for(srcx=linfo->min.x; srcx<linfo->max.x; srcx++) { 
						rx = SQR((srcx - linfo->cur.x)/r0x); 

						if(rx + ry <= 1) {
							mrcPixelDataGet(in, srcx, srcy, linfo->cur.z, &data0, mrcPixelRePart, mrcPixelHowNearest);
							data += data0;
							max++;
						}
					}
					}
					if(max/2<=data) {
						data = 1;
					}
					break;
				}
				default: {
					fprintf(stderr, "Not supported Line Mode: %d\n", linfo->LineMode);
					exit(EXIT_FAILURE);
					break;
				}
			}
			break;
		}
		default: {
			fprintf(stderr, "Not supported Line Shape: %d\n", linfo->LineShape);
			exit(EXIT_FAILURE);
			break;
		}
	}
	return data;
}


void 
lmrcImageMeanFreePathCalcAnyDirection(mrcImage* in, lmrcImageMeanFreePathCalcInfo* linfo, lmrcImageMeanFreePathCalcMode  mode)
{
	/*
	mrcImageParaTypeRealCoord Length;
	mrcImageParaTypeRealCoord LineThickness;   
	lmrcImageMeanFreePathCalcLineMode  LineMode;
	lmrcImageMeanFreePathCalcLineShape LineShape;
	*/
	
	mrcImageParaTypeReal x, y, z;
	mrcImageParaTypeReal dstx, dsty, dstz;
	mrcImageParaTypeReal phi, theta, dphi, dtheta, dr, r, rmax, rmaxmax, thetamax, phimax;
	int ntheta, nphi, itheta, iphi, ir, nr;
	int flagEdge, flagEdgeMax;
	double data, dstdata;
	int i, irmaxmax;
	int* countWhite;
	int* countBlack;
	int* countWhiteEdge;
	int* countBlackEdge;

	linfo->white.Header = in->Header; 
	linfo->black.Header = in->Header; 
	linfo->whiteEdge.Header = in->Header; 
	linfo->blackEdge.Header = in->Header; 
	mrcInit(&linfo->white, NULL);
	mrcInit(&linfo->black, NULL);
	mrcInit(&linfo->whiteEdge, NULL);
	mrcInit(&linfo->blackEdge, NULL);

	for(i=0; i<3; i++) {
		linfo->direction[i].Header = in->Header;
		mrcInit(&linfo->direction[i], NULL);
	}

	nphi   = floor(2*M_PI/linfo->deltaPhi + 1);
	if(1<in->HeaderN.z) {
		ntheta = floor(M_PI/linfo->deltaTheta + 1);
	} else {
		ntheta = 1; 
		theta  = 0;
	}
	nr = sqrt(SQR(in->HeaderN.x)+SQR(in->HeaderN.y)+SQR(in->HeaderN.z));

	DEBUGPRINT3("(nr, nphi, ntheta) = (%d %d %d)\n", nr, nphi, ntheta);
	countBlack     = memoryAllocate(sizeof(int)*(nr+1), "in lmrcImageMeanFreePathCalc");
	countWhite     = memoryAllocate(sizeof(int)*(nr+1), "in lmrcImageMeanFreePathCalc");
	countBlackEdge = memoryAllocate(sizeof(int)*(nr+1), "in lmrcImageMeanFreePathCalc");
	countWhiteEdge = memoryAllocate(sizeof(int)*(nr+1), "in lmrcImageMeanFreePathCalc");

	linfo->countBlack = countBlack;
	linfo->countWhite = countWhite;
	linfo->countBlackEdge = countBlackEdge;
	linfo->countWhiteEdge = countWhiteEdge;
	linfo->N = nr;

	for(z=0; z<in->HeaderN.z; z++) {
	for(y=0; y<in->HeaderN.y; y++) {
	for(x=0; x<in->HeaderN.x; x++) {

		mrcPixelDataGet(in, x, y, z, &data, mrcPixelRePart, mrcPixelHowNearest);

		rmaxmax = 0;
		for(itheta=0; itheta<ntheta; itheta++) {
			if(1<in->HeaderN.z) {
				theta = itheta*linfo->deltaTheta - M_PI/2.0; 
			} else {
				theta = 0;
			}
		for(iphi=0; iphi<nphi; iphi++) {
			phi = iphi*linfo->deltaPhi;
		
			flagEdge = 0;
			rmax = -1;
			for(ir=1; ir<nr; ir++) {
				r=ir;

				dstx = r*cos(phi)*cos(theta)+x;	
				dsty = r*sin(phi)*cos(theta)+y;	
				dstz = r*sin(theta)         +z;	

				if(-0.5<=dstx && dstx < in->HeaderN.x -0.5
				 &&-0.5<=dsty && dsty < in->HeaderN.y -0.5
				 &&-0.5<=dstz && dstz < in->HeaderN.z -0.5) {
					mrcPixelDataGet(in, dstx, dsty, dstz, &dstdata, mrcPixelRePart, mrcPixelHowNearest);
				} else {
					rmax = r - 1;
					flagEdge = 1;
					break;
				}
				if(dstdata != data) {
					rmax = r - 1;
					break;
				}
			}
			if(rmaxmax<rmax) {
				rmaxmax  = rmax;
				phimax   = phi;
				thetamax = theta;
				flagEdgeMax = flagEdge;
			}
		}
		}

		irmaxmax = (int)rmaxmax;
		if(0<data) { // white
			if(0<flagEdgeMax) { // whiteEdge
				mrcPixelDataSet(&linfo->whiteEdge, x, y, z, rmaxmax, mrcPixelRePart);
				countWhiteEdge[irmaxmax]++;
			} else { // white
				mrcPixelDataSet(&linfo->white, x, y, z, rmaxmax, mrcPixelRePart);
				countWhite[irmaxmax]++;
			}
		} else {     // black
			if(0<flagEdgeMax) { // blackEdge
				mrcPixelDataSet(&linfo->blackEdge, x, y, z, rmaxmax, mrcPixelRePart);
				countBlackEdge[irmaxmax]++;
			} else { // black 
				mrcPixelDataSet(&linfo->black, x, y, z, rmaxmax, mrcPixelRePart);
				countBlack[irmaxmax]++;
			}
		}
		mrcPixelDataSet(&linfo->direction[0], x, y, z, cos(phimax)*cos(thetamax), mrcPixelRePart);
		mrcPixelDataSet(&linfo->direction[1], x, y, z, sin(phimax)*cos(thetamax), mrcPixelRePart);
		mrcPixelDataSet(&linfo->direction[2], x, y, z,             sin(thetamax), mrcPixelRePart);
	}
	}
	}

	lmrcImageMeanFreePathCalcMeanCalc(in, linfo, mode);
}
