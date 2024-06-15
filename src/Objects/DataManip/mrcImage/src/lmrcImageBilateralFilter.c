/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% lmrcImageBilateral ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : lmrcImageBilateral 
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%lmrcImageBilateral ver%I%; Date:%D% %Z%";
#undef DEBUG
#include "genUtil.h"
#include "Memory.h"
#include "./lmrcImageBilateralFilter.h"

void
lmrcImageBilateralFilterUsage(FILE* fpt)
{
	fprintf(fpt, "Bilateral Filter\n"); 
	fprintf(fpt, "    by Tomashi and Manduchi\n"); 
	fprintf(fpt, "    C. Tomasi and R. Manduchi, Bilateral Filtering for Gray and Color Images, Proceedings of the 1998 IEEE International Conference on Computer Vision, Bombay, India\n"); 
	fprintf(fpt, " fi = Sigma_j(W(i,j)*Ij)/ Sigma_j(Wj)   \n"); 
	fprintf(fpt, "   ,where W(i,j)=W_x(xi,xj)*W_I(Ii,Ij)    \n"); 
	fprintf(fpt, "------- linfo.mode : %d \n", lmrcImageBilateralFilterInfoModeGaussian); 
	fprintf(fpt, "                 W_x(xi,xj) = exp(-|xi-xj|^2/2 sigmaSpace^2  )\n"); 
	fprintf(fpt, "                 W_I(Ii,Ij) = exp(-|Ii-Ij|^2/2 sigmaDensity^2)\n"); 
	fprintf(fpt, "------- linfo.mode : %d \n", lmrcImageBilateralFilterInfoModeLorentzian); 
	fprintf(fpt, "                 W_x(xi,xj) = 1/(1+|xi-xj|^2/sigmaSpace^2  )   \n"); 
	fprintf(fpt, "                 W_I(Ii,Ij) = 1/(1+|Ii-Ij|^2/sigmaDensity^2)   \n"); 
}

static double __lmrcImageBilateralFilterKernel3Gaussian(double x, double y, double z,  double sigx, double sigy, double sigz)
{
	return exp(-(SQR(x/sigx)+SQR(y/sigy)+SQR(z/sigz))/2.0);
}

static double __lmrcImageBilateralFilterKernel3Lorentzian(double x, double y, double z,  double sigx, double sigy, double sigz)
{
	return 1.0/(1.0 + SQR(x/sigx) + SQR(y/sigy) + SQR(z/sigz));
}

static double __lmrcImageBilateralFilterKernelGaussian(double x, double sigx)
{
	return exp(-SQR(x/sigx)/2.0);
}

static double __lmrcImageBilateralFilterKernelLorentzian(double x, double sigx)
{
	return 1.0/(1.0 + SQR(x/sigx));
}

void
lmrcImageBilateralFilter(mrcImage* out, mrcImage* in, lmrcImageBilateralFilterInfo linfo, int mode)
{
	mrcImageParaTypeReal x, y, z;
	mrcImageParaTypeReal srcx, srcy, srcz;
	mrcImageParaTypeInteger minx, miny, minz;
	mrcImageParaTypeInteger maxx, maxy, maxz;
	mrcImageParaTypeInteger wx, wy, wz;
	mrcImageParaTypeInteger sx, sy, sz;
	mrcImageParaTypeInteger ix, iy, iz;
	mrcImageParaTypeInteger idx, idy, idz;
	mrcImageParaTypeInteger i;

	double* kernel;
	double dataSum;
	double wSum;
	double w;
	double dataJ, dataI;
	double data;
	int    count; 	

	double (*kernelSpace)(double x, double y, double z, double sigx, double sigy, double sigz);
	double (*kernelDensity)(double x, double sigx);

	if(!linfo.flagKernelSize) {
		linfo.kernelSize.x = 2*3*linfo.sigmaSpace.x;
		linfo.kernelSize.y = 2*3*linfo.sigmaSpace.y;
		linfo.kernelSize.z = 2*3*linfo.sigmaSpace.z;
	}

	wx = MAX(1, MIN(linfo.kernelSize.x, in->HeaderN.x));
	wy = MAX(1, MIN(linfo.kernelSize.y, in->HeaderN.y));
	wz = MAX(1, MIN(linfo.kernelSize.z, in->HeaderN.z));

	sx = wx/2;	
	sy = wy/2;	
	sz = wz/2;	

	kernel = (double*)memoryAllocate(sizeof(double)*wx*wy*wz, "in lmrcImageBilateralFilter");

	switch(linfo.sigmaSpaceMode) {
		case lmrcImageBilateralFilterInfoModeGaussian: {
			kernelSpace = __lmrcImageBilateralFilterKernel3Gaussian;
			break;
		}
		case lmrcImageBilateralFilterInfoModeLorentzian: {
			kernelSpace = __lmrcImageBilateralFilterKernel3Lorentzian;
			break;
		}
		default: {
			fprintf(stderr, "Not supported Mode in lmrcImageBilateralFilter: SigmaSpaceMode %d\n", linfo.sigmaSpaceMode);
			exit(EXIT_FAILURE);
			break;
		}
	}
	DEBUGPRINT1("kernelSpace: %f ( 0, 0, 0,1,1,1)\n", kernelSpace( 0,  0,  0, 1, 1, 1));
	DEBUGPRINT1("kernelSpace: %f ( 1, 1, 1,1,1,1)\n", kernelSpace( 1,  1,  1, 1, 1, 1));
	DEBUGPRINT1("kernelSpace: %f (-1,-1,-1,1,1,1)\n", kernelSpace(-1, -1, -1, 1, 1, 1));

	switch(linfo.sigmaDensityMode) {
		case lmrcImageBilateralFilterInfoModeGaussian: {
			kernelDensity = __lmrcImageBilateralFilterKernelGaussian;
			break;
		}
		case lmrcImageBilateralFilterInfoModeLorentzian: {
			kernelDensity = __lmrcImageBilateralFilterKernelLorentzian;
			break;
		}
		default: {
			fprintf(stderr, "Not supported Mode in lmrcImageBilateralFilter: SigmaDensityMode %d\n", linfo.sigmaDensityMode);
			exit(EXIT_FAILURE);
			break;
		}
	}
	DEBUGPRINT1("kernelDensity: %f ( 0, 1)\n", kernelDensity( 0, 1));
	DEBUGPRINT1("kernelDensity: %f ( 1, 1)\n", kernelDensity( 1, 1));
	DEBUGPRINT1("kernelDensity: %f (-1, 1)\n", kernelDensity(-1, 1));
	if(0==linfo.sigmaDensity) {
		fprintf(stderr, "Simgma is zero: %f\n", linfo.sigmaDensity);
		exit(EXIT_FAILURE);
	}


	i = 0;
	if(0==linfo.sigmaSpace.x*linfo.sigmaSpace.y*linfo.sigmaSpace.z) {
		fprintf(stderr, "Simgma is zero: %f %f %f\n", linfo.sigmaSpace.x, linfo.sigmaSpace.y, linfo.sigmaSpace.z);
		exit(EXIT_FAILURE);
	}
	for(iz=0, idz=-sz; iz<wz; iz++, idz++) {
	for(iy=0, idy=-sy; iy<wy; iy++, idy++) {
	for(ix=0, idx=-sx; ix<wx; ix++, idx++) {
		kernel[i] = kernelSpace(idx, idy, idz, linfo.sigmaSpace.x, linfo.sigmaSpace.y, linfo.sigmaSpace.z);
		i++;
	}
	}
	}

	out->Header = in->Header;
	mrcInit(out, NULL);

	DEBUGPRINT3("HeaderN %d %d %d", out->HeaderN.x, out->HeaderN.y, out->HeaderN.z);

	for(z=0; z<out->HeaderN.z; z++) {
		minz = MAX(0, z-sz);  
		maxz = MIN(in->HeaderN.z-1, z+sz);
	for(y=0; y<out->HeaderN.y; y++) {
		miny = MAX(0, y-sy);  
		maxy = MIN(in->HeaderN.y-1, y+sy);
	for(x=0; x<out->HeaderN.x; x++) {
		minx = MAX(0, x-sx);  
		maxx = MIN(in->HeaderN.x-1, x+sx);

		mrcPixelDataGet(in, x, y, z, &dataI, mrcPixelRePart, mrcPixelHowNearest);
		dataSum = 0;
		wSum = 0;
		count = 0;	
		
		DEBUGPRINT4("%f at %f %f %f", dataI, x, y, z);
		DEBUGPRINT6("min %d %d %d <-> max %d %d %d\n", minx, miny, minz, maxx, maxy, maxz);
		
		for(srcz=minz; srcz<=maxz; srcz++) {
		for(srcy=miny; srcy<=maxy; srcy++) {
		for(srcx=minx; srcx<=maxx; srcx++) {
			ix =(int)(x - srcx + sx);
			iy =(int)(y - srcy + sy);
			iz =(int)(z - srcz + sz);
			i = ix + iy*wx + iz*wx*wy;
			
			mrcPixelDataGet(in, srcx, srcy, srcz, &dataJ, mrcPixelRePart, mrcPixelHowNearest);

			w = kernel[i]*kernelDensity(dataI-dataJ, linfo.sigmaDensity);

			DEBUGPRINT4("%f at %f %f %f\n", w, srcx, srcy, srcz);
			wSum    += w;
			dataSum += w*dataJ;
			count++;
		}
		}
		}

		if(0<count) {
			data = dataSum/wSum;
		} else {
			data = 0;
		}
		mrcPixelDataSet(out, x, y, z, data, mrcPixelRePart);
		DEBUGPRINT4("%f at %f %f %f\n", data, x, y, z);
	}
	}
	}
}
