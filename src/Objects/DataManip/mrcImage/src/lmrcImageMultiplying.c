#include "./lmrcImageMultiplying.h"

void
lmrcImageMultiplyingByFile(mrcImage* inout, mrcImage* in)
{
	mrcImageParaTypeReal x, y, z;
	double data1, data2;

	for(z=0; z<in->HeaderN.z; z++) {
	for(y=0; y<in->HeaderN.y; y++) {
	for(x=0; x<in->HeaderN.x; x++) {
		mrcPixelDataGet(inout, x, y, z, &data1,      mrcPixelRePart, mrcPixelHowNearest);
		mrcPixelDataGet(in,    x, y, z, &data2,      mrcPixelRePart, mrcPixelHowNearest);
		mrcPixelDataSet(inout, x, y, z, data1*data2, mrcPixelRePart);
	}
	}
	}
}

void
lmrcImageMultiplying2(mrcImage* in, float value, long mode)
{

	mrcImageParaTypeReal x, y, z;
	double data;

	if(mode==mrcComplexFloatFT) {
	  for(x=0; x<=in->HeaderN.x/2; x++) {
	    for(y= - in->HeaderN.y / 2 ; y<in->HeaderN.y/2; y++) {
	      if (in->HeaderN.z==1){
		mrcPixelDataGet(in,  x, y, 0, &data, mrcPixelRePart,mrcPixelHowNearest);
		mrcPixelDataSet(in, x, y, 0, data*value, mrcPixelRePart);
		mrcPixelDataGet(in,  x, y, 0, &data, mrcPixelImPart,mrcPixelHowNearest);
		mrcPixelDataSet(in, x, y, 0, data*value, mrcPixelImPart);
	      }else{
		for(z= -in->HeaderN.z / 2  ; z<in->HeaderN.z/2; z++) {
		  mrcPixelDataGet(in,  x, y, z, &data, mrcPixelRePart,mrcPixelHowNearest);
		  mrcPixelDataSet(in, x, y, z, data*value, mrcPixelRePart);
		  fprintf(stdout,"%f ",data);
		  mrcPixelDataGet(in,  x, y, z, &data, mrcPixelImPart,mrcPixelHowNearest);
		  mrcPixelDataSet(in, x, y, z, data*value, mrcPixelImPart);
		}
	      }
	    }
	  }
	} else if (mode==mrcFloatImage) {
	  for(x=0; x<in->HeaderN.x; x++) {
	    for(y=0; y<in->HeaderN.y; y++) {
	      for(z=0; z<in->HeaderN.z; z++) {
		mrcPixelDataGet(in,  x, y, z, &data, mrcPixelRePart,mrcPixelHowNearest);
		mrcPixelDataSet(in, x, y, z,  data*value, mrcPixelRePart);
	      }
	    }
	  }
	} else {
		fprintf(stderr, "Not supported mode: %ld\n", mode) ;
		exit(EXIT_FAILURE);
	}
	mrcStatDataSet(in, 0);
}

void 
lmrcImageMultiplying(mrcImage* out, mrcImage* in, float value, long mode)
{
	mrcImageParaTypeReal x, y, z;
	double data;
	if(mode==mrcComplexFloatFT) {
	  out->Header = in->Header;
	  mrcInit(out, NULL);
	  for(x=0; x<=in->HeaderN.x/2; x++) {
	    for(y= - in->HeaderN.y / 2 ; y<in->HeaderN.y/2; y++) {
	      if (in->HeaderN.z==1){
		mrcPixelDataGet(in,  x, y, 0, &data, mrcPixelRePart,mrcPixelHowNearest);
		mrcPixelDataSet(out, x, y, 0, data*value, mrcPixelRePart);
		mrcPixelDataGet(in,  x, y, 0, &data, mrcPixelImPart,mrcPixelHowNearest);
		mrcPixelDataSet(out, x, y, 0, data*value, mrcPixelImPart);
	      }else{
		for(z= -in->HeaderN.z / 2  ; z<in->HeaderN.z/2; z++) {
		  mrcPixelDataGet(in,  x, y, z, &data, mrcPixelRePart,mrcPixelHowNearest);
		  mrcPixelDataSet(out, x, y, z, data*value, mrcPixelRePart);
		  fprintf(stdout,"%f ",data);
		  mrcPixelDataGet(in,  x, y, z, &data, mrcPixelImPart,mrcPixelHowNearest);
		  mrcPixelDataSet(out, x, y, z, data*value, mrcPixelImPart);
		}
	      }
	    }
	  }
	} else if (mode==mrcFloatImage) {
	  out->Header = in->Header;
	  mrcInit(out, NULL);
	  for(x=0; x<in->HeaderN.x; x++) {
	    for(y=0; y<in->HeaderN.y; y++) {
	      for(z=0; z<in->HeaderN.z; z++) {
		mrcPixelDataGet(in,  x, y, z, &data, mrcPixelRePart,mrcPixelHowNearest);
		mrcPixelDataSet(out, x, y, z, data*value, mrcPixelRePart);
	      }
	    }
	  }
	}
	mrcStatDataSet(out, 0);
}

