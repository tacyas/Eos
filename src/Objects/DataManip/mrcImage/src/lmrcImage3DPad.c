/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% lmrcImage3DPad ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : lmrcImage3DPad 
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%lmrcImage3DPad ver%I%; Date:%D% %Z%";

#define DEBUG
#include "genUtil.h"
#include "./lmrcImage3DPad.h"

void
lmrcImage3DPadUsage(FILE* fpt)
{
	fprintf(fpt, "%d: Filament-type(cylinder)\n", lmrcImage3DPadShapeModeFilament);
 	fprintf(fpt, "%d: SingleParticle-type(sphere)\n", lmrcImage3DPadShapeModeSphere);
  	fprintf(fpt, "%d: SigplePartilce-type(ellipsoid)\n", lmrcImage3DPadShapeModeEllipsoid);
   	fprintf(fpt, "%d: Rectangle\n", lmrcImage3DPadShapeModeRectangle);
}

void
lmrcImage3DPad(mrcImage* out, mrcImage* in, lmrcImage3DPadInfo linfo, int mode)
{
	switch(linfo.ShapeMode) {
		case lmrcImage3DPadShapeModeFilament: {
			lmrcImage3DPadfilament(out, in, linfo, mode);
			break;
		}
		case lmrcImage3DPadShapeModeSphere: {
			lmrcImage3DPadSphere(out, in, linfo, mode);
			break;
		}
		case lmrcImage3DPadShapeModeEllipsoid: {
			lmrcImage3DPadEllipsoid(out, in, linfo, mode);
			break;
		}
		case lmrcImage3DPadShapeModeRectangle: {
			lmrcImage3DPadRectangle(out, in, linfo, mode);
			break;
		}
	}
}

void 
lmrcImage3DPadfilament(mrcImage* out ,mrcImage* in , lmrcImage3DPadInfo linfo, int mode)
{
	/* variables */
	int x,y,z;
	double data,cx,cy,sx,sy,r2,av,c,dr2,averager;
	double offset;
	double delr;

	/* begin */
	out->Header    = in->Header;
	out->HeaderN.x = linfo.Nx;
	out->HeaderN.y = linfo.Ny;
	out->HeaderN.z = linfo.Nz;
    DEBUGPRINT3("N: %d %d %d\n", out->HeaderN.x, out->HeaderN.y, out->HeaderN.z);
	mrcInit(out,NULL);
	DEBUGPRINT1("TailerNum %d\n", in->numTailer);
	if(0<in->numTailer) {
		out->numTailer = in->numTailer;
		out->Tailer = in->Tailer;
		DEBUGPRINT1("TailerNum %d in Out\n", out->numTailer);
	}

	// Centre
	cx=(in->HeaderN.x-1)*0.5;
	cy=(in->HeaderN.y-1)*0.5;

	// Offset
	sx=(out->HeaderN.x-in->HeaderN.x)*0.5;
	sy=(out->HeaderN.y-in->HeaderN.y)*0.5;

	// Radius^2
	r2=SQR(linfo.rmax);
	
	// 
	if(linfo.flagShell) {
		delr = linfo.shell*linfo.rmax;
	} else {
		delr = 1;
	}	

	switch(mode){
		case 0: // Ideal-win
			if (!linfo.flagv){
				if (linfo.rmax > (in->HeaderN.x - 1)/2.0 || linfo.rmax > (in->HeaderN.y - 1)/2.0){
					averager = MIN((in->HeaderN.x - 1)/2.0, (in->HeaderN.y - 1)/2.0 );
				} else {
					averager = linfo.rmax;
				}
				DEBUGPRINT1("r: %g \n",averager);
				av=lmrcImage3DPadfilamentCalcavr(in, averager, delr);
			} else {
				av=linfo.v;
			}
			if(linfo.flagFloating) {
				fprintf(stderr, "Floating avg:%f\n", av);
				offset = av;
			} else {
				offset = 0;
			}
			for (z=0;z<out->HeaderN.z;z++){
			for (y=0;y<out->HeaderN.y;y++){
			for (x=0;x<out->HeaderN.x;x++){
				mrcPixelDataSet(out, x, y, z , av-offset, mrcPixelRePart);
			}
			}
			}

			for (z=0;z<in->HeaderN.z;z++){
			for (y=0;y<in->HeaderN.y;y++){
			for (x=0;x<in->HeaderN.x;x++){
				mrcPixelDataGet(in ,x ,y ,z ,&data, mrcPixelRePart, mrcPixelHowNearest);
				if(linfo.flagr) {
					dr2=SQR(x-cx)+SQR(y-cy);
					if (dr2<=r2) {
						mrcPixelDataSet(out, x+sx, y+sy, z, data-offset, mrcPixelRePart);
					} 
				} else {	      
					mrcPixelDataSet(out, x+sx, y+sy, z, data-offset, mrcPixelRePart);
				}
			}
			}
			}
			break;
		case 1: // Smooth Connection by cosine-win
			if (!linfo.flagv){
				av = lmrcImage3DPadfilamentCalcavr(in, linfo.rmax+linfo.w, delr);
				DEBUGPRINT1("r: %g \n",averager);
				fprintf(stdout,"av: %g \n",av);
			} else {
				av=linfo.v;
			}
			if(linfo.flagFloating) {
				offset = av;
			} else {
				offset = 0;
			}
			for (z=0;z<in->HeaderN.z;z++){
			for (y=0;y<in->HeaderN.y;y++){
			for (x=0;x<in->HeaderN.x;x++){
				mrcPixelDataGet(in ,x ,y ,z ,&data, mrcPixelRePart, mrcPixelHowNearest);
				if (linfo.flagr){
					dr2=SQR(x-cx)+SQR(y-cy);
					if (dr2 < SQR(linfo.rmax-linfo.w) ) {
						mrcPixelDataSet(out, x+sx, y+sy, z, data - offset, mrcPixelRePart);
					} else if (SQR(linfo.rmax+linfo.w) < dr2 ){
						mrcPixelDataSet(out, x+sx, y+sy, z, av - offset, mrcPixelRePart);
					} else {
						c= (sin( ( linfo.rmax-sqrt(dr2)) / linfo.w *PI/2 )+1 ) /2;
						mrcPixelDataSet(out, x+sx, y+sy, z, (data-av)*c+av-offset, mrcPixelRePart);
					}
				} else {
					mrcPixelDataSet(out, x+sx, y+sy, z, av-offset, mrcPixelRePart);
				}	    
			}
			}
			} 
	}
	mrcStatDataSet(out ,0);
}

double lmrcImage3DPadfilamentCalcavr(mrcImage* in, double rmax, double delr)
{
	/* variables */
	int x,y,z,n;
	double cx,cy,r2,sum,data,av;

	/* begin */
	n=0;
	sum=0;
	// Centre
	cx=(in->HeaderN.x-1)*0.5;
	cy=(in->HeaderN.y-1)*0.5; 

	for (y=0;y<in->HeaderN.y;y++){
	for (x=0;x<in->HeaderN.x;x++){
		r2=SQR(x-cx)+SQR(y-cy);
		if (SQR(rmax) <= r2 && r2<SQR(rmax+delr)){
			for (z=0 ;z<in->HeaderN.z;z++){
				mrcPixelDataGet(in, x, y, z, &data, mrcPixelRePart, mrcPixelHowNearest);
				sum+=data;
				n++;
			}
		}
	}
	}
	av=sum/n;
	return(av);
}


void 
lmrcImage3DPadSphere(mrcImage* out, mrcImage* in, lmrcImage3DPadInfo linfo, int mode) 
{
	/* variables */
	int x,y,z;
	double data,cx,cy,cz,sx,sy,sz,r2,av,c,dr2;
	double dstx, dsty, dstz;
	double offset;
	double rmax, rmin, ww, rmax2, rmin2;
	double delr;

	out->Header = in->Header;
	out->HeaderN.x = linfo.Nx;
	out->HeaderN.y = linfo.Ny;
	out->HeaderN.z = linfo.Nz;
	if(0<in->numTailer) {
		out->numTailer = in->numTailer;
		out->Tailer = in->Tailer;
	}
	DEBUGPRINT3("%d %d %d\n", out->HeaderN.x, out->HeaderN.y, out->HeaderN.z);
	cx=(in->HeaderN.x-1)*0.5;
	cy=(in->HeaderN.y-1)*0.5;
	cz=(in->HeaderN.z-1)*0.5;
	sx=(out->HeaderN.x-in->HeaderN.x)*0.5;
	sy=(out->HeaderN.y-in->HeaderN.y)*0.5;
	sz=(out->HeaderN.z-in->HeaderN.z)*0.5;
	r2=SQR(linfo.rmax);
	ww = linfo.w*2;
	rmax  = linfo.rmax+linfo.w;
	rmax2 = SQR(rmax); 	
	rmin  = linfo.rmax-linfo.w;
	rmin2 = SQR(rmin);


	// 
	if(linfo.flagShell) {
		delr = linfo.shell*rmax;
	} else {
		delr = 1;
	}	

	if (!linfo.flagv){
		av=lmrcImage3DPadSphereCalcavr(in, linfo.rmax, delr);
	} else {
		av=linfo.v;
	}
	if(linfo.flagFloating) {
		offset = av;
	} else {
		offset = 0;
	}

	switch(mode){
		case 0:
			for (z=0;z<out->HeaderN.z;z++){
			for (y=0;y<out->HeaderN.y;y++){
			for (x=0;x<out->HeaderN.x;x++){
				mrcPixelDataSet(out, x, y, z, av-offset, mrcPixelRePart);
			}
			}
			}
			for (z=0;z<in->HeaderN.z;z++){
			for (y=0;y<in->HeaderN.y;y++){
			for (x=0;x<in->HeaderN.x;x++){
				mrcPixelDataGet(in, x, y, z, &data, mrcPixelRePart, mrcPixelHowNearest);
				if (linfo.flagr){
					dr2=SQR(x-cx)+SQR(y-cy)+SQR(z-cz);
					if (dr2<=r2) {
						mrcPixelDataSet(out, x+sx, y+sy, z+sz, data-offset, mrcPixelRePart);
					} 
				} else { 
					mrcPixelDataSet(out, x+sx, y+sy, z+sz, data-offset, mrcPixelRePart);
				}	    
			}
			}
			}
			break;
		case 1:
			fprintf(stdout,"av :%g\n",av); 
			for (z=0;z<in->HeaderN.z;z++){
			for (y=0;y<in->HeaderN.y;y++){
			for (x=0;x<in->HeaderN.x;x++){
				dstx = x + sx;
				dsty = y + sy;
				dstz = z + sz;
				if(-0.5<=dstx && dstx<out->HeaderN.x-0.5
				 &&-0.5<=dsty && dsty<out->HeaderN.y-0.5
				 &&-0.5<=dstz && dstz<out->HeaderN.z-0.5) {
					mrcPixelDataGet(in ,x ,y ,z ,&data, mrcPixelRePart, mrcPixelHowNearest);
					if (linfo.flagr) {
						dr2=SQR(x-cx)+SQR(y-cy)+SQR(z-cz);
						if (dr2<rmin2) {
							mrcPixelDataSet(out ,dstx, dsty, dstz, data-offset, mrcPixelRePart);
						} else if (rmax2<dr2) {
							mrcPixelDataSet(out ,dstx, dsty, dstz, av-offset, mrcPixelRePart);
						} else {
							c= (cos((sqrt(dr2) - rmin)/ww*PI ) + 1 )/2;
							mrcPixelDataSet(out, dstx, dsty, dstz, (data-av)*c+av-offset , mrcPixelRePart);
						}
					} else {
						mrcPixelDataSet(out ,x+sx ,y+sy ,z+sz ,av-offset, mrcPixelRePart);
					}	  
				}	
			}
			}
			}  
	}
	mrcStatDataSet(out ,0);
}

double 
lmrcImage3DPadSphereCalcavr(mrcImage* in, double rmax, double delr)
{
	/* variables */
	int x,y,z,n;
	double cx,cy,cz,r2,sum,data,av;

	/* begin */
	n=0;
	sum=0;
	cx=(in->HeaderN.x-1)*0.5;
	cy=(in->HeaderN.y-1)*0.5; 
	cz=(in->HeaderN.z-1)*0.5; 
	
	for (z=0;z<in->HeaderN.z;z++){
	for (y=0;y<in->HeaderN.y;y++){
	for (x=0;x<in->HeaderN.x;x++){
		r2=SQR(x-cx)+SQR(y-cy)+SQR(z-cz);
		if (SQR(rmax) <= r2 && r2<SQR(rmax+delr)) {
			mrcPixelDataGet(in ,x ,y ,z ,&data, mrcPixelRePart, mrcPixelHowNearest);
			sum+=data;
			n++;
		}
	}
	}
	}
	if(0<n) {
		av=sum/n;
	} else {
		fprintf(stderr, "rmax is too large in lmrcImage3DPadCalcavr: %f\n", rmax);	
		av = 0;
	}
	return(av);
}

void 
lmrcImage3DPadEllipsoid(mrcImage* out, mrcImage* in, lmrcImage3DPadInfo linfo, int mode) 
{
	/* variables */
	int x,y,z;
	double data,cx,cy,cz,sx,sy,sz,r2,av,c,dr2;
	double dstx, dsty, dstz;
	double offset;
	double rmax, rmin, ww, rmax2, rmin2;
	double delxmax, delymax, delzmax;

	out->Header = in->Header;
	out->HeaderN.x = linfo.Nx;
	out->HeaderN.y = linfo.Ny;
	out->HeaderN.z = linfo.Nz;
	mrcInit(out,NULL);
	if(0<in->numTailer) {
		out->numTailer = in->numTailer;
		out->Tailer = in->Tailer;
	}
	DEBUGPRINT3("%d %d %d\n", out->HeaderN.x, out->HeaderN.y, out->HeaderN.z);
	cx=(in->HeaderN.x-1)*0.5;
	cy=(in->HeaderN.y-1)*0.5;
	cz=(in->HeaderN.z-1)*0.5;
	sx=(out->HeaderN.x-in->HeaderN.x)*0.5;
	sy=(out->HeaderN.y-in->HeaderN.y)*0.5;
	sz=(out->HeaderN.z-in->HeaderN.z)*0.5;
	r2=SQR(linfo.rmax);
	ww = linfo.w*2;
	rmax  = linfo.rmax+linfo.w;
	rmax2 = SQR(rmax); 	
	rmin  = linfo.rmax-linfo.w;
	rmin2 = SQR(rmin);

	// 
	if(linfo.flagShell) {
		delxmax = linfo.shell;
		delymax = linfo.shell;
		delzmax = linfo.shell;
	} else {
		delxmax = 1.0/linfo.rxmax;
		delymax = 1.0/linfo.rymax;
		delzmax = 1.0/linfo.rzmax;
	}	

	if (!linfo.flagv){
		av=lmrcImage3DPadEllipsoidCalcavr(in, linfo.rxmax, linfo.rymax, linfo.rzmax, delxmax, delymax, delzmax);
	} else {
		av=linfo.v;
	}
	if(linfo.flagFloating) {
		offset = av;
	} else {
		offset = 0;
	}
	switch(mode){
		case 0:
			data = av - offset;
			for (z=0;z<out->HeaderN.z;z++){
			for (y=0;y<out->HeaderN.y;y++){
			for (x=0;x<out->HeaderN.x;x++){
				mrcPixelDataSet(out, x, y, z, data, mrcPixelRePart);
			}
			}
			}
			for (z=0;z<in->HeaderN.z;z++){
			for (y=0;y<in->HeaderN.y;y++){
			for (x=0;x<in->HeaderN.x;x++){
				mrcPixelDataGet(in, x, y, z, &data, mrcPixelRePart, mrcPixelHowNearest);
				if (linfo.flagr){
					dr2=SQR(x-cx)+SQR(y-cy)+SQR(z-cz);
					if (r2>=dr2 ){
						mrcPixelDataSet(out, x+sx, y+sy, z+sz, data-offset, mrcPixelRePart);
					} 
				} else {	      
					mrcPixelDataSet(out, x+sx, y+sy, z+sz , data-offset, mrcPixelRePart);
				}	    
			}
			}
			}
			break;
		case 1:
			fprintf(stdout,"av :%g\n",av); 
			for (z=0;z<in->HeaderN.z;z++){
			for (y=0;y<in->HeaderN.y;y++){
			for (x=0;x<in->HeaderN.x;x++){
				dstx = x + sx;
				dsty = y + sy;
				dstz = z + sz;
				if(-0.5<=dstx && dstx<out->HeaderN.x-0.5
				 &&-0.5<=dsty && dsty<out->HeaderN.y-0.5
				 &&-0.5<=dstz && dstz<out->HeaderN.z-0.5) {
					mrcPixelDataGet(in ,x ,y ,z ,&data, mrcPixelRePart, mrcPixelHowNearest);
					if (linfo.flagr) {
						dr2=SQR(x-cx)+SQR(y-cy)+SQR(z-cz);
						if (dr2<rmin2) {
							mrcPixelDataSet(out ,dstx, dsty, dstz, data-offset, mrcPixelRePart);
						} else if (rmax2<dr2) {
							mrcPixelDataSet(out ,dstx, dsty, dstz, av-offset, mrcPixelRePart);
						} else {
							c= (cos((sqrt(dr2) - rmin)/ww*PI ) + 1 )/2;
							mrcPixelDataSet(out, dstx, dsty, dstz, (data-av)*c+av-offset , mrcPixelRePart);
						}
					} else {
						mrcPixelDataSet(out ,x+sx ,y+sy ,z+sz ,av-offset, mrcPixelRePart);
					}	  
				}	
			}
			}
			} 
			break;
	}
	mrcStatDataSet(out ,0);
}

double 
lmrcImage3DPadEllipsoidCalcavr(mrcImage* in ,double rxmax, double rymax, double rzmax, double delxmax, double delymax, double delzmax)
{
	/* variables */
	int x,y,z,n;
	double cx,cy,cz,r2,r2max, sum,data,av;

	/* begin */
	n=0;
	sum=0;
	// Centre
	cx=(in->HeaderN.x-1)*0.5;
	cy=(in->HeaderN.y-1)*0.5; 
	cz=(in->HeaderN.z-1)*0.5; 

	for (z=0;z<in->HeaderN.z;z++){
	for (y=0;y<in->HeaderN.y;y++){
	for (x=0;x<in->HeaderN.x;x++){
		r2   =SQR((x-cx)/rxmax)+SQR((y-cy)/rymax)+SQR((z-cz)/rzmax);
		r2max=SQR((x-cx)/(rxmax*(1+delxmax)))+SQR((y-cy)/(rymax*(1+delymax)))+SQR((z-cz)/(rzmax*(1+delzmax)));
		if (1 <= r2 && r2max <=1) {
			mrcPixelDataGet(in, x, y, z, &data, mrcPixelRePart, mrcPixelHowNearest);
			sum+=data;
			n++;
		}
	}
	}
	}
	if(0<n) {
		av=sum/n;
	} else {
		fprintf(stderr, "rmax is too large in lmrcImage3DPadCalcavr: %f %f %f\n", rxmax, rymax, rzmax);	
		av = 0;
	}
	return(av);
}


void 
lmrcImage3DPadRectangle(mrcImage* out, mrcImage* in, lmrcImage3DPadInfo linfo, int mode) 
{
	/* variables */
	int x,y,z;
	double data,cx,cy,cz,sx,sy,sz,r2,av,c,dr2;
	double dstx, dsty, dstz;
	double offset;
	double rmax, rmin, ww, rmax2, rmin2;
	double delxmax, delymax, delzmax;
	double wx, wy, wz;
	double dwx, dwy, dwz;

	out->Header = in->Header;
	out->HeaderN.x = linfo.Nx;
	out->HeaderN.y = linfo.Ny;
	out->HeaderN.z = linfo.Nz;
	mrcInit(out,NULL);
	if(0<in->numTailer) {
		out->numTailer = in->numTailer;
		out->Tailer = in->Tailer;
	}
	DEBUGPRINT3("%d %d %d\n", out->HeaderN.x, out->HeaderN.y, out->HeaderN.z);
	cx=(in->HeaderN.x-1)*0.5;
	cy=(in->HeaderN.y-1)*0.5;
	cz=(in->HeaderN.z-1)*0.5;
	sx=(out->HeaderN.x-in->HeaderN.x)*0.5; // 
	sy=(out->HeaderN.y-in->HeaderN.y)*0.5;
	sz=(out->HeaderN.z-in->HeaderN.z)*0.5; 
	r2=SQR(linfo.rmax);
	ww = linfo.w*2;
	rmax  = linfo.rmax+linfo.w;
	rmax2 = SQR(rmax); 	
	rmin  = linfo.rmax-linfo.w;
	rmin2 = SQR(rmin);

	// 
	if(linfo.flagShell) {
		delxmax = linfo.shell;
		delymax = linfo.shell;
		delzmax = linfo.shell;
	} else {
		delxmax = 1.0/linfo.xmax;
		delymax = 1.0/linfo.ymax;
		delzmax = 1.0/linfo.zmax;
	}	

	if (!linfo.flagv){
		av=lmrcImage3DPadRectangleCalcavr(in, linfo.xmax, linfo.ymax, linfo.zmax, delxmax, delymax, delzmax);
	} else {
		av=linfo.v;
	}
	if(linfo.flagFloating) {
		offset = av;
	} else {
		offset = 0;
	}
	switch(mode){
		case 0:
			data = av - offset;
			for (z=0;z<out->HeaderN.z;z++){
			for (y=0;y<out->HeaderN.y;y++){
			for (x=0;x<out->HeaderN.x;x++){
				mrcPixelDataSet(out, x, y, z, data, mrcPixelRePart);
			}
			}
			}
			for (z=0;z<in->HeaderN.z;z++){
				wz = fabs(z-cz)*2.0; // c[x|y|z]: centre of in
                dstz = z + sz;
			for (y=0;y<in->HeaderN.y;y++){
				wy = fabs(y-cy)*2.0;
                dsty = y + sy;
			for (x=0;x<in->HeaderN.x;x++){
				wx = fabs(x-cx)*2.0;
                dstx =  x + sx;

				mrcPixelDataGet(in, x, y, z, &data, mrcPixelRePart, mrcPixelHowNearest);
				if (linfo.flagr) {
					if((wx<linfo.xmax)
					 ||(wy<linfo.ymax)
					 ||(wz<linfo.zmax)) {
						mrcPixelDataSet(out, x+sx, y+sy, z+sz, data-offset, mrcPixelRePart);
					}
				} else { // s: start	      
                    if( -0.5<=dstx && dstx<out->HeaderN.x-0.5
                     && -0.5<=dsty && dsty<out->HeaderN.y-0.5
                     && -0.5<=dstz && dstz<out->HeaderN.z-0.5 ) {
					    mrcPixelDataSet(out, dstx, dsty, dstz, data-offset, mrcPixelRePart);
                    }
				}
			}
			}
			}
			break;
		case 1:
			fprintf(stdout,"av :%g\n",av); 
			for (z=0;z<in->HeaderN.z;z++){
				wz = fabs(z-cz)*2.0;
			for (y=0;y<in->HeaderN.y;y++){
				wy = fabs(y-cy)*2.0;
			for (x=0;x<in->HeaderN.x;x++){
				wx = fabs(x-cx)*2.0;
				dstx = x + sx;
				dsty = y + sy;
				dstz = z + sz;
				if(-0.5<=dstx && dstx<out->HeaderN.x-0.5
				 &&-0.5<=dsty && dsty<out->HeaderN.y-0.5
				 &&-0.5<=dstz && dstz<out->HeaderN.z-0.5) {
					mrcPixelDataGet(in, x, y, z, &data, mrcPixelRePart, mrcPixelHowNearest);
					if (linfo.flagr) {
						if((wx<linfo.xmax*(1-linfo.shell))
					 	 ||(wy<linfo.ymax*(1-linfo.shell))
					 	 ||(wz<linfo.zmax*(1-linfo.shell))){
							mrcPixelDataSet(out, x+sx, y+sy, z+sz, data-offset, mrcPixelRePart);
						} else if(linfo.xmax*(1+linfo.shell)<wx
						        ||linfo.ymax*(1+linfo.shell)<wy
						        ||linfo.zmax*(1+linfo.shell)<wz) {
							mrcPixelDataSet(out ,dstx, dsty, dstz, av-offset, mrcPixelRePart);
						} else {
							c = (cos((wx-linfo.xmax*(1-linfo.shell))/(2*linfo.shell)*M_PI)+1)/2.0
							   *(cos((wy-linfo.ymax*(1-linfo.shell))/(2*linfo.shell)*M_PI)+1)/2.0
							   *(cos((wz-linfo.zmax*(1-linfo.shell))/(2*linfo.shell)*M_PI)+1)/2.0;
							mrcPixelDataSet(out, dstx, dsty, dstz, (data-av)*c+av-offset , mrcPixelRePart);
						}
					} else {
						mrcPixelDataSet(out ,x+sx ,y+sy ,z+sz ,av-offset, mrcPixelRePart);
					}	  
				}	
			}
			}
			} 
			break;
	}
	mrcStatDataSet(out ,0);
}

double 
lmrcImage3DPadRectangleCalcavr(mrcImage* in ,double xmax, double ymax, double zmax, double delxmax, double delymax, double delzmax)
{
	/* variables */
	int x,y,z,n;
	double cx,cy,cz,r2,r2max, sum,data,av;
	double wx, wy, wz;
	double dwx, dwy, dwz;

	/* begin */
	n=0;
	sum=0;
	// Centre
	cx=(in->HeaderN.x-1)*0.5;
	cy=(in->HeaderN.y-1)*0.5; 
	cz=(in->HeaderN.z-1)*0.5; 

	dwx = xmax*(1+delxmax);
	dwy = ymax*(1+delymax);
	dwz = zmax*(1+delzmax);

	for (z=0;z<in->HeaderN.z;z++){
		wz = fabs(z-cz)*2.0;
	for (y=0;y<in->HeaderN.y;y++){
		wy = fabs(y-cy)*2.0;
	for (x=0;x<in->HeaderN.x;x++){
		wx = fabs(x-cx)*2.0;

		if((xmax<wx && wx<xmax+dwx)
		 ||(ymax<wy && wy<ymax+dwy)
		 ||(zmax<wz && wz<zmax+dwz)) {
			mrcPixelDataGet(in, x, y, z, &data, mrcPixelRePart, mrcPixelHowNearest);
			sum+=data;
			n++;
		}
	}
	}
	}
	if(0<n) {
		av=sum/n;
	} else {
		fprintf(stderr, "rmax is too large in lmrcImage3DPadCalcavr: %f %f %f\n", xmax, ymax, zmax);	
		av = 0;
	}
	return(av);
}


