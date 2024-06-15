/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% lmrcImageFFT ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : lmrcImageFFT 
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%lmrcImageFFT ver%I%; Date:%D% %Z%";

#undef DEBUG
#include "genUtil.h"
#include "Memory.h"
#include "eosPThread.h"
#include "../inc/mrcImage.h"

#ifdef CUDA
#include <cuda.h>
#endif
//#undef FFTW
#ifdef FFTW
#ifdef CUDA
#include <cufftw.h>
//#include "fftw3.h"
#else
#include "fftw3.h"
#endif
static unsigned int flagFFTW=FFTW_ESTIMATE;
void
lmrcImageFFTWFlagSet(unsigned int flag)
{
	flagFFTW=flag;
}
typedef float         fftwReal;
typedef fftwf_complex fftwComplex;
#else

#include "./fftn.h"

#endif

#ifdef FFTW
static void __lmrcImageFFTBeforeFFTChar (fftwReal* inImg, mrcImage* in);
static void __lmrcImageFFTBeforeFFTShort(fftwReal* inImg, mrcImage* in);
static void __lmrcImageFFTBeforeFFTFloat(fftwReal* inImg, mrcImage* in);
static void __lmrcImageFFTAfterFFT(mrcImage* out, fftwComplex* outFT);

static void __lmrcImageFFTBeforeInverseFFT(fftwComplex* inFT, mrcImage* in);
static void __lmrcImageFFTAfterInverseFFT (mrcImage*     out, fftwReal* outImg);

#else
static void __ImageSetBeforeFFT(mrcImageParaTypeReal* Re, 
								mrcImageParaTypeReal* Im,
								mrcImage* mrc);

static void __ImageSetBeforeFFTChar(mrcImageParaTypeReal* Re, 
								mrcImageParaTypeReal* Im,
								mrcImage* mrc);

static void __ImageSetBeforeFFTShort(mrcImageParaTypeReal* Re, 
								mrcImageParaTypeReal* Im,
								mrcImage* mrc);

static void __FourierSetAfterFFT(mrcImage* mrc,
								mrcImageParaTypeReal* Re, 
								mrcImageParaTypeReal* Im);

static void __FourierSetBeforeFFT(mrcImageParaTypeReal* Re, 
								mrcImageParaTypeReal* Im,
								mrcImage* mrc);

static void __ImageSetAfterFFT(mrcImage* mrc, 
								mrcImageParaTypeReal* Re, 
								mrcImageParaTypeReal* Im);
#endif


void
lmrcImageFFTCenterChange(mrcImage* fft, int mode)
{
	mrcImageParaTypeInteger X, Y, Z;	
	int n;
	int mx, my, mz, sig;
	double re, im;

	for(Z=-fft->HeaderN.z/2; Z< fft->HeaderN.z/2.0; Z++) {
		mz = Z%2;   					
	for(Y=-fft->HeaderN.y/2; Y< fft->HeaderN.y/2.0; Y++) {
		my = Y%2;   					
	for(X=0;                 X<=fft->HeaderN.x/2.0; X++) {
		mx = X%2;   					
		sig = 1;
		if(mx) {
			sig *= -1;
		}
		if(my) {
			sig *= -1;
		}
		if(mz) {
			sig *= -1;
		}
		if(sig<0) {
			mrcPixelDataGet(fft, X, Y, Z, &re, mrcPixelRePart, mrcPixelHowNearest);	
			mrcPixelDataGet(fft, X, Y, Z, &im, mrcPixelImPart, mrcPixelHowNearest);	
			mrcPixelDataSet(fft, X, Y, Z, -re, mrcPixelRePart);
			mrcPixelDataSet(fft, X, Y, Z, -im, mrcPixelImPart);	
		}
	}
	}
	}	
}

void
lmrcImageFFTFirstDimensionOnly(mrcImage* out, mrcImage* in, long mode)
{
	mrcImage tmp;
	mrcImage tmpfft;
	mrcImageParaTypeReal x, y, z;
	double data;
	double re;
	double im;

	tmp.Header = in->Header;
	tmp.HeaderN.y = 1;
	tmp.HeaderN.y = 1;
	mrcInit(&tmp, NULL);

	out->Header     = in->Header;
	out->HeaderMode = mrcComplexFloatOneDimFT;
	mrcInit(out, NULL);

	for(y=0; y<out->HeaderN.y; y++) {
	for(z=0; z<out->HeaderN.z; z++) {
		if(IsImage(in, "", 0)) {
			for(x=0; x<tmp.HeaderN.x; x++) {
				mrcPixelDataGet(  in, x, y, z, &data, mrcPixelRePart, mrcPixelHowNearest);	
				mrcPixelDataSet(&tmp, x, 0, 0,  data, mrcPixelRePart);
			} 
			DEBUGPRINT3("size: %d %d %d\n", tmp.HeaderN.x, tmp.HeaderN.y, tmp.HeaderN.z);
			lmrcImageFFT(&tmpfft, &tmp, 1);
			for(x=0; x<=out->HeaderN.x/2; x++) {
				mrcPixelDataGet(&tmpfft, x, 0, 0, &re, mrcPixelRePart, mrcPixelHowNearest);	
				mrcPixelDataGet(&tmpfft, x, 0, 0, &im, mrcPixelImPart, mrcPixelHowNearest);	
				mrcPixelDataSet(    out, x, y, z,  re, mrcPixelRePart);
				mrcPixelDataSet(    out, x, y, z,  im, mrcPixelImPart);
			}
		} else {
			fprintf(stderr, "Not supported: in lmrcImageFFTFirstDimensionOnly\n");
			exit(EXIT_FAILURE);
		}
	}
	}
}

void
lmrcImageFFT(mrcImage* out, mrcImage* in, long mode)
{
	int i, j, x, y, z, X, Y, Z;
#ifdef FFTW
	float* inImg;
	fftwf_complex* outFT;
	fftwf_complex* inFT;
	float* outImg;
	fftwf_plan p;
#else
	int ndim;
	int dims[3];
	mrcImageParaTypeReal* Re;
	mrcImageParaTypeReal* Im;
	int isign;
	double scaling;
#endif
	int NX2, NY2, NZ2, total;
	/* Even Check */
	if(!((0==in->HeaderN.x%2 || 1==in->HeaderN.x)&& 
		 (0==in->HeaderN.y%2 || 1==in->HeaderN.y)&&
		 (0==in->HeaderN.z%2 || 1==in->HeaderN.z))||
		 (1==in->HeaderN.x && 1==in->HeaderN.y && 1==in->HeaderN.z)){
			if((0x01&mode)!=1) {
				fprintf(stderr, "Warning! Odd size image: ");
				fprintf(stderr, "(x, y, z)=(%d, %d, %d)\n", 
								(int)in->HeaderN.x, 
								(int)in->HeaderN.y,
								(int)in->HeaderN.z);
			}
	}
	
	NX2=MAX(in->HeaderN.x/2, 1)+1;
	NY2=MAX(in->HeaderN.y/2, 1);
	NZ2=MAX(in->HeaderN.z/2, 1);

	out->Header = in->Header;

#ifdef FFTW 

if(__eosPThread__) {
	DEBUGPRINT("MutexLock for plan->");
	eosPThreadMutexLock(NULL);
}

	if(IsImage(in, "", 0)) {
		inImg = (float*)        fftwf_malloc(sizeof(float)*in->HeaderN.x*in->HeaderN.y*in->HeaderN.z);
		outFT = (fftwf_complex*)fftwf_malloc(sizeof(fftwf_complex)*NX2*in->HeaderN.y*in->HeaderN.z);
		//fprintf(stderr, "%x %x\n", inImg, outFT);
		if(in->HeaderN.y==1 && in->HeaderN.z==1) {
			p = fftwf_plan_dft_r2c_1d(in->HeaderN.x, inImg, outFT, flagFFTW);
		} else if(in->HeaderN.z==1) {
			p = fftwf_plan_dft_r2c_2d(in->HeaderN.y, in->HeaderN.x, inImg, outFT, flagFFTW);
		} else {
			p = fftwf_plan_dft_r2c_3d(in->HeaderN.z, in->HeaderN.y, in->HeaderN.x, inImg, outFT, flagFFTW);
		}
	} else if(IsFT(in, "", 0)) {
		inFT   = (fftwf_complex*)fftwf_malloc(sizeof(fftwf_complex)*NX2*in->HeaderN.y*in->HeaderN.z);
		outImg = (float*)fftwf_malloc(sizeof(float)*in->HeaderN.x*in->HeaderN.y*in->HeaderN.z);
		if(in->HeaderN.y==1 && in->HeaderN.z==1) {
			p = fftwf_plan_dft_c2r_1d(in->HeaderN.x, inFT, outImg, flagFFTW);
		} else if(in->HeaderN.z==1) {
			p = fftwf_plan_dft_c2r_2d(in->HeaderN.y, in->HeaderN.x, inFT, outImg, flagFFTW);
		} else {
			p = fftwf_plan_dft_c2r_3d(in->HeaderN.z, in->HeaderN.y, in->HeaderN.x, inFT, outImg, flagFFTW);
		}
	} else {
		fprintf(stderr, "Not supported Image Mode %d\n", in->HeaderMode);
		exit(EXIT_FAILURE);
	}

if(__eosPThread__) {
	DEBUGPRINT("MutexUnlock for plan->");
	eosPThreadMutexUnlock(NULL);
}

#else
	scaling = -2.0; 
	ndim = 3;
	dims[0] = in->HeaderN.x;
	dims[1] = in->HeaderN.y;
	dims[2] = in->HeaderN.z;
	Re = (mrcImageParaTypeReal*)memoryAllocate(sizeof(mrcImageParaTypeReal)*in->HeaderN.x*in->HeaderN.y*in->HeaderN.z, "in lmrcImageFFT");
	Im = (mrcImageParaTypeReal*)memoryAllocate(sizeof(mrcImageParaTypeReal)*in->HeaderN.x*in->HeaderN.y*in->HeaderN.z, "in lmrcImageFFT");
#endif

	switch(in->HeaderMode) {
		case mrcCharImage: {
#ifdef FFTW
			__lmrcImageFFTBeforeFFTChar(inImg, in);
			fftwf_execute(p);
			__lmrcImageFFTAfterFFT(out, outFT);
#else
			__ImageSetBeforeFFTChar(Re, Im, in);
			isign = +1;
			fftnf(ndim, dims, Re, Im, isign, scaling);
			__FourierSetAfterFFT(out, Re, Im);
#endif
			break;
		}
		case mrcShortImage: {
#ifdef FFTW
			__lmrcImageFFTBeforeFFTShort(inImg, in);
			fftwf_execute(p);
			__lmrcImageFFTAfterFFT(out, outFT);
#else
			__ImageSetBeforeFFTShort(Re, Im, in);
			isign = +1;
			fftnf(ndim, dims, Re, Im, isign, scaling);
			__FourierSetAfterFFT(out, Re, Im);
#endif
			break;
		}
		case mrcFloatRadonImage: 
		case mrcFloatImage: {
#ifdef FFTW
			__lmrcImageFFTBeforeFFTFloat(inImg, in);
			fftwf_execute(p);
			__lmrcImageFFTAfterFFT(out, outFT);
#else
			__ImageSetBeforeFFT(Re, Im, in);
			isign = +1;
			fftnf(ndim, dims, Re, Im, isign, scaling);
			__FourierSetAfterFFT(out, Re, Im);
#endif
			break;
		}
		case mrcFloatRadonFT: 
		case mrcComplexFloatFT: {
#ifdef FFTW
			__lmrcImageFFTBeforeInverseFFT(inFT, in);
			fftwf_execute(p);
			__lmrcImageFFTAfterInverseFFT(out, outImg);
#else
			__FourierSetBeforeFFT(Re, Im, in);
			isign = -1;
			fftnf(ndim, dims, Re, Im, isign, scaling);
			__ImageSetAfterFFT(out, Re, Im);
#endif
			break;
		}	
		default: {
			fprintf(stderr, "Not supported mode:%d\n", in->HeaderMode);
			exit(EXIT_FAILURE);
		}
	}

	mrcStatDataSet(out,0);
#ifdef FFTW
if(__eosPThread__) {
	DEBUGPRINT("MutexLock for destroy->");;
	eosPThreadMutexLock(NULL);
}

	fftwf_destroy_plan(p);

if(__eosPThread__) {
	DEBUGPRINT("MutexUnLock\n");
	eosPThreadMutexUnlock(NULL);
}
	if(IsImage(in, "", 0)) {
		fftwf_free(inImg);
		fftwf_free(outFT);
	} else if(IsFT(in, "", 0)) {
		fftwf_free(inFT);
		fftwf_free(outImg);
	}
#else
	fft_free();
	memoryFree(Re);
	memoryFree(Im);
#endif
}


#ifdef FFTW
void
__lmrcImageFFTBeforeFFTChar(float* inImg, mrcImage* in)
{
	mrcImageParaTypeInteger x, y, z, X, Y, Z, i, j;

	for(z=0; z<in->HeaderN.z; z++) {
	for(y=0; y<in->HeaderN.y; y++) {
	for(x=0; x<in->HeaderN.x; x++) {
		i = x + in->HeaderN.x*(y + z*in->HeaderN.y);
		inImg[i] = in->ImageCharImage[i];
	}
	}
	}
}

void
__lmrcImageFFTBeforeFFTShort(float* inImg, mrcImage* in)
{
	mrcImageParaTypeInteger x, y, z, X, Y, Z, i, j;

	for(z=0; z<in->HeaderN.z; z++) {
	for(y=0; y<in->HeaderN.y; y++) {
	for(x=0; x<in->HeaderN.x; x++) {
		i = x + in->HeaderN.x*(y + z*in->HeaderN.y);
		inImg[i] = in->ImageShortImage[i];
	}
	}
	}
}

void
__lmrcImageFFTBeforeFFTFloat(float* inImg, mrcImage* in)
{
	mrcImageParaTypeInteger x, y, z, X, Y, Z, i, j;

	for(z=0; z<in->HeaderN.z; z++) {
	for(y=0; y<in->HeaderN.y; y++) {
	for(x=0; x<in->HeaderN.x; x++) {
		i = x + in->HeaderN.x*(y + z*in->HeaderN.y);
		inImg[i] = in->ImageFloatImage[i];
	}
	}
	}
}

void
__lmrcImageFFTBeforeInverseFFT(fftwComplex* inFT, mrcImage* in )
{
	mrcImageParaTypeInteger x, y, z, X, Y, Z, i, j;
	mrcImageParaTypeInteger NX2, NY2, NZ2;
	mrcImageParaTypeInteger NX2Max, NY2Max, NZ2Max;

	NX2=in->HeaderN.x/2+1;
	NX2Max=in->HeaderN.x/2+1;

	NY2=in->HeaderN.y/2;
	if(in->HeaderN.y%2==0) {
		NY2Max=MAX(in->HeaderN.y/2, 1);
	} else {
		NY2Max=MAX(in->HeaderN.y/2+1, 1);
	}

	NZ2=in->HeaderN.z/2;
	if(in->HeaderN.z%2==0) {
		NZ2Max=MAX(in->HeaderN.z/2, 1);
	} else {
		NZ2Max=MAX(in->HeaderN.z/2+1, 1);
	}

	for(z=-NZ2; z<NZ2Max; z++) {
	for(y=-NY2; y<NY2Max; y++) {
	for(x=0;    x<NX2Max; x++) {
		X = x;
		Y = ((y>=0)?(y):(in->HeaderN.y+y));
		Z = ((z>=0)?(z):(in->HeaderN.z+z));
		i = x+NX2*(y+NY2 + (z+NZ2)*in->HeaderN.y);
		j = X+NX2*(Y     +  Z     *in->HeaderN.y);
		inFT[j][0] = in->ImageFloatImage[2*i]; 
		inFT[j][1] = in->ImageFloatImage[2*i+1]; 
		DEBUGPRINT6("%d %f %f at (%d %d %d) <- ", j, inFT[j][0], inFT[j][1], X, Y, Z);	
		DEBUGPRINT4("<- %d at (%d %d %d)\n", i, x, y, z);	
	}
	}
	}
}

void
__lmrcImageFFTAfterFFT(mrcImage* out, fftwComplex* outFT)
{
	mrcImageParaTypeInteger x, y, z, X, Y, Z, i, j;
	mrcImageParaTypeInteger NX2, NY2, NZ2;
	mrcImageParaTypeInteger NX2Max, NY2Max, NZ2Max;
	double w;

	out->HeaderMode = mrcComplexFloatFT;
	mrcInit(out, NULL);

	NX2   =out->HeaderN.x/2+1;
	NX2Max=out->HeaderN.x/2+1;

	NY2=out->HeaderN.y/2;
	if(out->HeaderN.y%2==0) { 
		NY2Max=MAX(out->HeaderN.y/2, 1);
	} else {
		NY2Max=MAX(out->HeaderN.y/2+1, 1);
	}
	NZ2=out->HeaderN.z/2;
	if(out->HeaderN.z%2==0) { 
		NZ2Max=MAX(out->HeaderN.z/2, 1);
	} else {
		NZ2Max=MAX(out->HeaderN.z/2+1, 1);
	}
	w = sqrt(out->HeaderN.x*out->HeaderN.y*out->HeaderN.z);

	for(z=-NZ2; z<NZ2Max; z++) {						
	for(y=-NY2; y<NY2Max; y++) {						
	for(x=0;    x<NX2Max; x++) {						
		X = x;
		Y = ((y>=0)?(y):(out->HeaderN.y+y));
		Z = ((z>=0)?(z):(out->HeaderN.z+z));
		i = x+NX2*(y+NY2 + (z+NZ2)*out->HeaderN.y);
		j = X+NX2*(Y     +  Z     *out->HeaderN.y);
		out->ImageFloatImage[2*i]   = outFT[j][0]/w;
		out->ImageFloatImage[2*i+1] = outFT[j][1]/w;
		DEBUGPRINT6("%d %f %f at (%d %d %d) -> ", j, outFT[j][0], outFT[j][1], X, Y, Z);	
		DEBUGPRINT6("-> %d %f %f at (%d %d %d)\n", i, out->ImageFloatImage[2*i], out->ImageFloatImage[2*i+1], x, y, z);	
	}
	}
	}
}

void
__lmrcImageFFTAfterInverseFFT(mrcImage* out, float* outImg)
{
	mrcImageParaTypeInteger x, y, z, i;
	double w;
	out->HeaderMode = mrcFloatImage;
	mrcInit(out, NULL);	

	w = sqrt(out->HeaderN.x*out->HeaderN.y*out->HeaderN.z);

	for(z=0; z<out->HeaderN.z; z++) {
	for(y=0; y<out->HeaderN.y; y++) {
	for(x=0; x<out->HeaderN.x; x++) {
		i = x + out->HeaderN.x*(y + z*out->HeaderN.y);
		out->ImageFloatImage[i] = outImg[i]/w;
	}
	}
	}
}

#else

void 
__ImageSetBeforeFFTChar(mrcImageParaTypeReal* Re, 
					     mrcImageParaTypeReal* Im,
					     mrcImage* mrc)
{
	mrcImageParaTypeInteger nbuf, i;
	
	nbuf = mrc->HeaderN.x*mrc->HeaderN.y*mrc->HeaderN.z;
	for(i=0; i<nbuf; i++) {
		Re[i] = (float)mrc->ImageCharImage[i];
		Im[i] = 0.0;
		DEBUGPRINT2("%ld: %g\n", i, Re[i]);
	}
}

void 
__ImageSetBeforeFFTShort(mrcImageParaTypeReal* Re, 
					     mrcImageParaTypeReal* Im,
					     mrcImage* mrc)
{
	mrcImageParaTypeInteger nbuf, i;
	
	nbuf = mrc->HeaderN.x*mrc->HeaderN.y*mrc->HeaderN.z;
	for(i=0; i<nbuf; i++) {
		Re[i] = (float)mrc->ImageShortImage[i];
		Im[i] = 0.0;
		DEBUGPRINT2("%ld: %g\n", i, Re[i]);
	}
}

void 
__ImageSetBeforeFFT(mrcImageParaTypeReal* Re, 
					mrcImageParaTypeReal* Im,
					mrcImage* mrc)
{
	mrcImageParaTypeInteger nbuf, i;
	//fprtinf(stderr, "in __ImageSetBeforeFFT\n");	
	nbuf = mrc->HeaderN.x*mrc->HeaderN.y*mrc->HeaderN.z;
	for(i=0; i<nbuf; i++) {
		Re[i] = mrc->ImageFloatImage[i];
		Im[i] = 0.0;
		DEBUGPRINT2("%ld: %g\n", i, Re[i]);
	}
}

void 
__FourierSetAfterFFT(mrcImage* fft,
					 mrcImageParaTypeReal* Re, 
					 mrcImageParaTypeReal* Im)
{
	mrcImageParaTypeInteger ix, iy, iz;
	mrcImageParaTypeInteger x, y, z;
	double re, im;

	//fprtinf(stderr, "in __ImageSetAfterFFT\n");	
	fft->HeaderMode = mrcComplexFloatFT;
	mrcInit(fft, NULL);

	DEBUGPRINT3("__FourierSetAfterFFT: %ld %ld %ld\n",
		fft->HeaderN.x,
		fft->HeaderN.y,
		fft->HeaderN.z);
	for(ix=0; ix<=fft->HeaderN.x/2; ix++) {
		for(iy=-fft->HeaderN.y/2; iy<MAX(fft->HeaderN.y/2,1); iy++) {
			for(iz=-fft->HeaderN.z/2; iz<MAX(fft->HeaderN.z/2,1); iz++) {
				DEBUGPRINT3("%ld %ld %ld\n", ix, iy, iz);
				x = ix;
				if(iy<0) {
					y = iy + fft->HeaderN.y;
				} else {
					y = iy;
				}
				if(iz<0) {
					z = iz + fft->HeaderN.z;
				} else {
					z = iz;
				}
				re = Re[x + y *fft->HeaderN.x + z*fft->HeaderN.x*fft->HeaderN.y];
				im = Im[x + y *fft->HeaderN.x + z*fft->HeaderN.x*fft->HeaderN.y];
				DEBUGPRINT5("%ld %ld %ld := %g %g\n", x, y, z, re ,im);
				mrcPixelDataSet(fft, (mrcImageParaTypeReal)ix, 
									 (mrcImageParaTypeReal)iy,
									 (mrcImageParaTypeReal)iz,
									 re,
									 mrcPixelRePart);
				mrcPixelDataSet(fft, (mrcImageParaTypeReal)ix, 
									 (mrcImageParaTypeReal)iy,
									 (mrcImageParaTypeReal)iz,
									 im, 
									 mrcPixelImPart);
			}
		}
	}
}

void 
__FourierSetBeforeFFT(mrcImageParaTypeReal* Re, 
					  mrcImageParaTypeReal* Im,
					  mrcImage* fft)
{
	mrcImageParaTypeInteger ix, iy, iz;
	mrcImageParaTypeInteger x, y, z;
	double re, im;

	for(ix=-fft->HeaderN.x/2; ix<fft->HeaderN.x/2; ix++) {
		for(iy=-fft->HeaderN.y/2; iy<MAX(fft->HeaderN.y/2,1); iy++) {
			for(iz=-fft->HeaderN.z/2; iz<MAX(fft->HeaderN.z/2,1); iz++) {
			        DEBUGPRINT3("%ld %ld %ld\n", ix, iy, iz);
			        mrcPixelDataGet(fft, (mrcImageParaTypeReal)ix, 
									 (mrcImageParaTypeReal)iy,
									 (mrcImageParaTypeReal)iz,
									 &re, 
									 mrcPixelRePart,
									 mrcPixelHowNearest);
				mrcPixelDataGet(fft, (mrcImageParaTypeReal)ix, 
									 (mrcImageParaTypeReal)iy,
									 (mrcImageParaTypeReal)iz,
									 &im, 
									 mrcPixelImPart,
									 mrcPixelHowNearest);
				if(ix<0) {
					x = ix + fft->HeaderN.x;
				} else {
					x = ix;
				}
				if(iy<0) {
					y = iy + fft->HeaderN.y;
				} else {
					y = iy;
				}
				if(iz<0) {
					z = iz + fft->HeaderN.z;
				} else {
					z = iz;
				}
				Re[x + y*fft->HeaderN.x + z*fft->HeaderN.x*fft->HeaderN.y] = re;
				Im[x + y*fft->HeaderN.x + z*fft->HeaderN.x*fft->HeaderN.y] = im;
				DEBUGPRINT5("%ld %ld %ld := %g %g\n", x, y, z, re ,im);
			}
		}
	}
}

void
__ImageSetAfterFFT(mrcImage* mrc,
				   mrcImageParaTypeReal* Re, 
				   mrcImageParaTypeReal* Im)
{
	mrcImageParaTypeInteger i, nbuf;
	
	mrc->HeaderMode = mrcFloatImage;
	mrcInit(mrc, NULL);
	nbuf = mrc->HeaderN.x*mrc->HeaderN.y*mrc->HeaderN.z;
	for(i=0; i<nbuf; i++) {
		mrc->ImageFloatImage[i] = Re[i];
		DEBUGPRINT2("%ld: %g\n", i, Re[i]);
	}
}

#endif
