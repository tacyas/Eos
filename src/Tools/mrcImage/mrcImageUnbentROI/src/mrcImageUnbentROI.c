#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"
#define DEBUG
#include "genUtil.h"
#include "mrcImage.h"

typedef struct lmrcImageUnbentROIInfo {
	int    nUnbentPoint;	
	float* unbentPoint;
	int Nx;
	int Ny;
	float deltax;
	float deltay;
	float correlationWindow; 
} lmrcImageUnbentROIInfo;

extern void lmrcImageUnbentROI(mrcImage* out, mrcImage* in, lmrcImageUnbentROIInfo* linfo, int mode);

int
main(int argc, char* argv[]) 
{
	mrcImageUnbentROIInfo  info;
	lmrcImageUnbentROIInfo linfo;
	mrcImage in;
	mrcImage out;
	int i;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);
	mrcFileRead(&in, info.In, "in main", 0);
	
	linfo.nUnbentPoint = info.flagroiLine/2;
	linfo.unbentPoint  = info.roiLine;
	
	if(info.flagWidth) {	
		linfo.Nx     = info.Width;
		linfo.deltax = info.x/info.Width;
	} else {
		linfo.Nx     = info.x;
		linfo.deltax = 1.0;
	}
	if(info.flagHeight) {
		linfo.Ny = info.Height;
		if(!info.flagy) {
			info.y = 0;
		}
		linfo.deltay = info.y/info.Height;
	} else {
		if(!info.flagy) {
			info.y = 0;
		}
		linfo.deltay = 1.0;
		linfo.Ny     = info.y;
	}
	if(info.flagShrink) {
		for(i=0; i<linfo.nUnbentPoint*2; i++) {
			linfo.unbentPoint[i] *= info.Shrink;
		}
	}

	if(info.flagCor) {
		linfo.correlationWindow = info.Cor;
	} else {
		linfo.correlationWindow = 0;
	}

	lmrcImageUnbentROI(&out, &in, &linfo, info.mode);

	mrcFileWrite(&out, info.Out, "in main", 0);
	exit(EXIT_SUCCESS);
}

void 
lmrcImageUnbentROI(mrcImage* out, mrcImage* in, lmrcImageUnbentROIInfo* linfo, int mode)
{
	long i, n;
	floatVector x, y, p, a, b;
	floatVector newx, newy, newp, newa, newb;
	floatVector oldx, oldy, oldp, olda, oldb;
	double dx, dy;
	double px[3];
	double py[3];
	double vx, vy, l, sx, sy;
	double data, data2, s;
	long num;

	/* Preparation of Spline Table */
	n = linfo->nUnbentPoint;
	floatVectorInit(&x, n);
	floatVectorInit(&y, n);
	for(i=0; i<n; i++) {
		x.data[i] = linfo->unbentPoint[2*i];
		y.data[i] = linfo->unbentPoint[2*i + 1];
	}
	floatVectorInit(&p, n); /* Parameter along a bent line */
	floatVectorInit(&a, n); 
	floatVectorInit(&b, n);
	lVectorSplineTable2DMake(&p, &x, &y, &a, &b);

	/* Output File */
	out->Header = in->Header;
	out->HeaderMode = mrcFloatImage; 
	out->HeaderN.x = linfo->Nx;
	if(0<linfo->Ny) {
		out->HeaderN.y = linfo->Ny;
	} else {
		out->HeaderN.y = p.data[n-1];
	}

	out->HeaderLength.x *= linfo->deltax;
	out->HeaderLength.y *= linfo->deltay;

	mrcInit(out, NULL);
	
	/* With Correlation */
	if(0<linfo->correlationWindow) {
		int m;
		int flagIter;
		int flagOK;
		mrcImage ref;
		mrcImage tmp;
		mrcImage tmp2;
		mrcImage avg;
		mrcImageParaTypeRealCoord shift;
		mrcImage cor;
		mrcImageInformation info;

		/* Reference */	
		ref.Header    = out->Header; 
		ref.HeaderN.x = out->HeaderN.x; 
		ref.HeaderN.y = ((int)(linfo->correlationWindow/out->HeaderLength.y/2))*2; 
		mrcInit(&ref, NULL);
		/* Temporary for fitting */
		tmp.Header = ref.Header; 
		mrcInit(&tmp, NULL);
		tmp2.Header = ref.Header; 
		mrcInit(&tmp2, NULL);
		avg.Header = ref.Header; 
		mrcInit(&avg, NULL);

		/* Number of new points */
		m = (int)(out->HeaderN.y*out->HeaderLength.y/linfo->correlationWindow) + 1;
		floatVectorInit(&newx, m);
		floatVectorInit(&newy, m);
		floatVectorInit(&newp, m);
		floatVectorInit(&newa, m);
		floatVectorInit(&newb, m);
		flagIter = 0;
		while(0<=flagIter && flagIter<1) {
			if(0==flagIter) { /* Attention: first time, the size of oldx is n, not m */
				oldx = x;
				oldy = y;
				oldp = p;
				olda = a;
				oldb = b;
			} else {
				if(flagIter == 1) {
					floatVectorInit(&oldx, m);
					floatVectorInit(&oldy, m);
					floatVectorInit(&oldp, m);
					floatVectorInit(&olda, m);
					floatVectorInit(&oldb, m);
				}
				for(i=0; i<m; i++) { oldx.data[i] = newx.data[i]; }
				for(i=0; i<m; i++) { oldy.data[i] = newy.data[i]; }
				for(i=0; i<m; i++) { oldp.data[i] = newp.data[i]; }
				for(i=0; i<m; i++) { olda.data[i] = newa.data[i]; }
				for(i=0; i<m; i++) { oldb.data[i] = newb.data[i]; }
			}
			DEBUGPRINT1("Correlation  : %d\n", flagIter);
			DEBUGPRINT1("Reference Set: %d\n", flagIter);
			for(dy=0; dy<ref.HeaderN.y; dy++) { 
				lVectorSpline2D((dy-1.0)*linfo->deltay, &(px[0]), &(py[0]), &oldp, &oldx, &oldy, &olda, &oldb);
				lVectorSpline2D( dy     *linfo->deltay, &(px[1]), &(py[1]), &oldp, &oldx, &oldy, &olda, &oldb);
				lVectorSpline2D((dy+1.0)*linfo->deltay, &(px[2]), &(py[2]), &oldp, &oldx, &oldy, &olda, &oldb);
				vy = -(px[2] - px[0])/2.0;
				vx =  (py[2] - py[0])/2.0;
				l  = sqrt(SQR(vx) + SQR(vy));
				vx /= l;
				vy /= l;
				for(dx=0; dx<ref.HeaderN.x; dx++) {
					s  = (dx - ref.HeaderN.x/2.0)*linfo->deltax;
					sx = px[1] + vx*s;
					sy = py[1] + vy*s;
					mrcPixelDataGet(in,   sx, sy, 0.0, &data, mrcPixelMag, mrcPixelHowNearest);
					if(flagIter==0) {
						mrcPixelDataSet(&ref, dx, dy, 0.0,  data, mrcPixelMag);
					} else {
						mrcPixelDataGet(&avg, dx, dy, 0.0, &data2, mrcPixelMag, mrcPixelHowNearest);
						mrcPixelDataSet(&ref, dx, dy, 0.0,  data2, mrcPixelMag);
					}
					mrcPixelDataSet(&avg, dx, dy, 0.0,  data, mrcPixelMag);
				}
			}
			DEBUGPRINT("StartingPoint\n")
			newx.data[0] = x.data[0];
			newy.data[0] = y.data[0];

			flagOK = 0;
			for(i=1; i<m; i++) {
				DEBUGPRINT("Temporary Image Get\n");	
				for(dy=0; dy<tmp.HeaderN.y; dy++) {
					lVectorSpline2D((dy-1.0)*linfo->deltay+i*tmp.HeaderN.y, 
						&(px[0]), &(py[0]), &oldp, &oldx, &oldy, &olda, &oldb);
					lVectorSpline2D( dy     *linfo->deltay+i*tmp.HeaderN.y, 
						&(px[1]), &(py[1]), &oldp, &oldx, &oldy, &olda, &oldb);
					lVectorSpline2D((dy+1.0)*linfo->deltay+i*tmp.HeaderN.y, 
						&(px[2]), &(py[2]), &oldp, &oldx, &oldy, &olda, &oldb);
					vy = -(px[2] - px[0])/2.0;
					vx =  (py[2] - py[0])/2.0;
					l  = sqrt(SQR(vx) + SQR(vy));
					vx /= l;
					vy /= l;
					for(dx=0; dx<tmp.HeaderN.x; dx++) {
						s  = (dx - tmp.HeaderN.x/2.0)*linfo->deltax;   
						sx = px[1] + vx*s; 
						sy = py[1] + vy*s;
						mrcPixelDataGet(in,   sx, sy, 0.0, &data, mrcPixelMag, mrcPixelHowNearest);
						mrcPixelDataSet(&tmp, dx, dy, 0.0,  data, mrcPixelMag);
					}
				}

				/* newx etc. */
				lmrcImageCorrelation(&cor, &tmp, &ref, 16);
				info.mode = meanOfAll;
				lmrcImageInformation(&info, &cor);
				DEBUGPRINT3("%d: %f %f\n", i, info.maxCoord.x, info.maxCoord.y);
				if(info.maxCoord.y < cor.HeaderN.y - info.maxCoord.y) {  
					dy =                   info.maxCoord.y; 
				} else {
					dy = -(cor.HeaderN.y - info.maxCoord.y);
				}
				lVectorSpline2D((dy-1.0)*linfo->deltay+i*tmp.HeaderN.y, &(px[0]), &(py[0]), &oldp, &oldx, &oldy, &olda, &oldb);
				lVectorSpline2D((dy    )*linfo->deltay+i*tmp.HeaderN.y, &(px[1]), &(py[1]), &oldp, &oldx, &oldy, &olda, &oldb);
				lVectorSpline2D((dy+1.0)*linfo->deltay+i*tmp.HeaderN.y, &(px[2]), &(py[2]), &oldp, &oldx, &oldy, &olda, &oldb);
				vy = -(px[2] - px[0])/2.0;
				vx =  (py[2] - py[0])/2.0;
				l  = sqrt(SQR(vx) + SQR(vy));
				vx /= l;
				vy /= l;
				DEBUGPRINT3("%d: %f %f\n", i, info.maxCoord.x, info.maxCoord.y);
				if(info.maxCoord.x < cor.HeaderN.x - info.maxCoord.x) { 
					s =  (info.maxCoord.x                )*linfo->deltax;	
				} else {
					s = -(cor.HeaderN.x - info.maxCoord.x)*linfo->deltax;	
				} 
				newx.data[i] = px[1] + vx*s; 
				newy.data[i] = py[1] + vy*s; 

				DEBUGPRINT3("%d: %f %f\n", i, info.maxCoord.x, info.maxCoord.y);
				DEBUGPRINT3("%d: old %f %f\n", i, px[1], py[1]);
				DEBUGPRINT3("%d: new %f %f\n", i, newx.data[i], newy.data[i]);
				DEBUGPRINT3("%d: v   %f %f\n", i, vx, vy);
				DEBUGPRINT2("%d: s   %f \n", i, s);
				flagOK += (dy + s);
				
				shift.x = -info.maxCoord.x;
				shift.y = -info.maxCoord.y;
				shift.z = 0;
				lmrcImageShift(&tmp2, &tmp, shift, 0);
				lmrcImageAdd(&avg, &tmp, &num);
				{
					char s[1024];
					sprintf(s, "/tmp/tmp.test.%d", i);
					mrcFileWrite(&tmp, s, "", 0);
				}
			}	
			if(0 == flagOK) {
				flagIter=-1;
			} else {
				flagIter++;
			}
			lVectorSplineTable2DMake(&newp, &newx, &newy, &newa, &newb);
			fprintf(stdout, "mrcImageUnbentROI -r ");
			for(i=0; i<m; i++) {
				fprintf(stdout, "%f %f ", newx.data[i], newy.data[i]);
			}
			fprintf(stdout, "\n");
			lmrcImageDividedByReal(&avg, (double)m);
			mrcFileWrite(&avg, "/tmp/avg.test", "", 0);
		}
		p = newp;
		x = newx;
		y = newy;
		a = newa;
		b = newb;
	}	

	
	for(dy=0; dy<out->HeaderN.y; dy++) {
		lVectorSpline2D((dy-1.0)*linfo->deltay, &(px[0]), &(py[0]), &p, &x, &y, &a, &b);
		lVectorSpline2D( dy     *linfo->deltay, &(px[1]), &(py[1]), &p, &x, &y, &a, &b);
		lVectorSpline2D((dy+1.0)*linfo->deltay, &(px[2]), &(py[2]), &p, &x, &y, &a, &b);

		vy = -(px[2] - px[0])/2.0;
		vx =  (py[2] - py[0])/2.0;
		l  = sqrt(SQR(vx) + SQR(vy));
		vx /= l;
		vy /= l;
		for(dx=0; dx<out->HeaderN.x; dx++) {
			s = (dx - out->HeaderN.x/2.0)*linfo->deltax;   
			sx = px[1] + vx*s; 
			sy = py[1] + vy*s;
			mrcPixelDataGet(in,  sx, sy, 0.0, &data, mrcPixelMag, mrcPixelHowNearest);
			mrcPixelDataSet(out, dx, dy, 0.0,  data, mrcPixelMag);
		}
	}	
}

void
additionalUsage()
{
}
