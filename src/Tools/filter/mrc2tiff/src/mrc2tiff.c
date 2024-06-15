
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION

#include "../inc/config.h"
#include "Memory.h"
#include "mrcImage.h"
#include "tiffio.h"

typedef enum lmrc2tiffColorMode {
    lmrc2tiffColorModeOneChannel = 0,
    lmrc2tiffColorModeThreeChannelZ= 1
} lmrc2tiffColorMode;

typedef  struct lmrc2tiffInfo {
    double offset;
    int    finalMode;
    lmrc2tiffColorMode colorMode;
    float  colorRangeMin;
    float  colorRangeMax;
} lmrc2tiffInfo;


extern void lmrc2tiff(TIFF* tiff, mrcImage* mrc, lmrc2tiffInfo linfo, long mode);


int
main(int argc, char* argv[]) 
{
    mrcImage mrc;
    mrcImage mrc2;
	mrcImage section;
	TIFF *tiff;
	mrc2tiffInfo info;
	float tmp;
	char filename[1024];
    lmrc2tiffInfo linfo;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	mrcFileRead(&mrc, info.inFile, "in main routine", 0);
    if(info.flagResolution) {
        mrc.HeaderLength.x = info.Resolution;
        mrc.HeaderLength.y = info.Resolution;
        mrc.HeaderLength.z = info.Resolution;
    } else if(info.flagResolutionX) {
        mrc.HeaderLength.x = info.ResolutionX;
        mrc.HeaderLength.y = info.ResolutionY;
        mrc.HeaderLength.z = info.ResolutionZ;
    }
	if(info.flagHigh) {
		mrc.HeaderAMax = info.High;
	}
	if(info.flagLow) {
		mrc.HeaderAMin = info.Low;
	}
	if(info.Inverse) {
		tmp = mrc.HeaderAMax;
		mrc.HeaderAMax = mrc.HeaderAMin;
		mrc.HeaderAMin = tmp;
	}
    if(info.raw) {
        mrc2 = mrc;
        linfo.finalMode = mrc2.HeaderMode;
    } else {
	    lmrcImageToIntImage(&mrc2, &mrc, (mrcImageParaTypeInteger)info.mode);
        linfo.finalMode = info.mode;
	    fclose(info.fptoutFile);
    }

    if(info.flagMode) {
        linfo.finalMode = info.Mode;
    }
    if(info.flagOffset) {
        linfo.offset = info.Offset;
    } else {
        linfo.offset = 0;
    }

	if(info.flagZ) {
		if(info.Z<0) {
			int z;
			for(z=0; z<mrc2.HeaderN.z; z++) {
				mrcImageSectionGet(&section, &mrc2, z, 1);	
				sprintf(filename, info.format, info.outFile, z);
				tiff = TIFFOpen(filename, "w");
				if(tiff != NULL) {
					lmrc2tiff(tiff, &mrc2, linfo, info.mode);
				} else {
					fprintf(stderr, "Cannot open tiff file (%s).\n", info.outFile);
					exit(EXIT_FAILURE);
				}	
				TIFFClose(tiff);
			}
		} else {
			mrcImageSectionGet(&section, &mrc2, info.Z, 1);	
			tiff = TIFFOpen(info.outFile, "w");
			if(tiff != NULL) {
				lmrc2tiff(tiff, &mrc2, linfo, info.mode);
			} else {
				fprintf(stderr, "Cannot open tiff file (%s).\n", info.outFile);
				exit(EXIT_FAILURE);
			}	
			TIFFClose(tiff);
		}
	} else {
		tiff = TIFFOpen(info.outFile, "w");
		if(tiff != NULL) {
			lmrc2tiff(tiff, &mrc2, linfo, info.mode);
		} else {
			fprintf(stderr, "Cannot open tiff file (%s).\n", info.outFile);
			exit(EXIT_FAILURE);
		}	
		TIFFClose(tiff);
	}
	return EXIT_SUCCESS;
}

void
additionalUsage()
{
	fprintf(stderr, "--- Attention ---\n");
	fprintf(stderr, "Previously, the black and white were inter-changed between mrc and tiff.  Now they are not changed\n");
}

void
lmrc2tiff(TIFF* tiff, mrcImage* mrc, lmrc2tiffInfo linfo, long mode)
{
	unsigned short samplesPerPixel;
	unsigned short sampleFormat;
	unsigned short bitsPerSample;
	unsigned short bytesPerSample;
	unsigned short planarConfiguration;
	unsigned short photometric;
	unsigned short bytesPerRow;
	unsigned short resUnit, resTag;
	unsigned long  w, h, row, col;
	float ox, oy, xres, yres, z;
	unsigned char*  tiffBuffer;
	double data;
    char s[1024];

	switch(linfo.finalMode) {
		case mrcCharImage: {
			bytesPerRow = sizeof(char)*mrc->HeaderN.x; 
			bitsPerSample = 8;
            sampleFormat=SAMPLEFORMAT_UINT;
			break;
		}
		case mrcShortImage: {
			bytesPerRow = sizeof(short)*mrc->HeaderN.x; 
			bitsPerSample = 16;
            sampleFormat=SAMPLEFORMAT_INT;
			break;
		}
		case mrcUShortImage: {
			bytesPerRow = sizeof(unsigned short)*mrc->HeaderN.x; 
			bitsPerSample = 16;
            sampleFormat=SAMPLEFORMAT_UINT;
			break;
		}
		case mrcFloatImage: {
			bytesPerRow = sizeof(float)*mrc->HeaderN.x; 
			bitsPerSample = 32;
            sampleFormat=SAMPLEFORMAT_IEEEFP;
			break;
		}
		default: {
			fprintf(stderr, "Not Supported mode : %d in lmrc2tiff \n", mrc->HeaderMode);
			exit(EXIT_FAILURE);
		}
	}

    /*
	if(1!=mrc->HeaderN.z) {
		fprintf(stderr, "Nut supported nz : %d\n", mrc->HeaderN.z);
	}		
    */
	photometric = PHOTOMETRIC_MINISBLACK;
	samplesPerPixel = 1;
	bytesPerSample = bitsPerSample/8;
	planarConfiguration = 1;
	w = mrc->HeaderN.x;
	h = mrc->HeaderN.y;
	ox = 0;
	oy = 0;
	resUnit=1;

    for(z=0; z<mrc->HeaderN.z; z++) {
       

	TIFFSetField(tiff, TIFFTAG_IMAGEWIDTH, w);
	TIFFSetField(tiff, TIFFTAG_IMAGELENGTH, h);
	TIFFSetField(tiff, TIFFTAG_ORIENTATION, ORIENTATION_TOPLEFT);
	TIFFSetField(tiff, TIFFTAG_SAMPLESPERPIXEL, samplesPerPixel);
	TIFFSetField(tiff, TIFFTAG_BITSPERSAMPLE, bitsPerSample);
	TIFFSetField(tiff, TIFFTAG_PLANARCONFIG, planarConfiguration);
	TIFFSetField(tiff, TIFFTAG_PHOTOMETRIC, photometric);
	TIFFSetField(tiff, TIFFTAG_COMPRESSION, COMPRESSION_NONE);
	TIFFSetField(tiff, TIFFTAG_SAMPLEFORMAT, sampleFormat);
    TIFFSetField(tiff, TIFFTAG_FILLORDER, FILLORDER_MSB2LSB);
    TIFFSetField(tiff, TIFFTAG_XRESOLUTION, 1e4/mrc->HeaderLength.x);
    TIFFSetField(tiff, TIFFTAG_YRESOLUTION, 1e4/mrc->HeaderLength.y);
    TIFFSetField(tiff, TIFFTAG_RESOLUTIONUNIT, 1);

    // IMAGE DESCRIPTION 
    sprintf(s, "mImageJ=1.53a\nimages=%d\slices=%d\nunit=micron\nspacing=%f\nloop=false\n", (int)z, (int)z, mrc->HeaderLength.z/1e4);
    TIFFSetField(tiff, TIFFTAG_IMAGEDESCRIPTION, s);

    TIFFSetField(tiff, TIFFTAG_SOFTWARE, "mrc2tiff");

	tiffBuffer = (unsigned char*)memoryAllocate(samplesPerPixel*w*bytesPerSample, "in lmrc2tiff");
	switch(bitsPerSample) {
		case 8: {
			for(row=0; row < h; row++) {
				for(col=0; col < w; col++) {
					mrcPixelDataGet(mrc, col, h - 1 - row, z, &data, mrcPixelRePart, mrcPixelHowNearest);
					*(((unsigned char*)tiffBuffer)+col) = (unsigned char)(data + linfo.offset);
				}
				if(TIFFWriteScanline(tiff, tiffBuffer, row, 0)<0) {
					break;
				}
			}
			break;
		}
		case 16: {
			for(row=0; row < h; row++) {
				for(col=0; col < w; col++) {
					mrcPixelDataGet(mrc, col, h - 1 - row, z, &data, mrcPixelRePart, mrcPixelHowNearest);
					*(((unsigned short*)tiffBuffer)+col) = (unsigned short)((data + linfo.offset - mrc->HeaderAMin)/(mrc->HeaderAMax - mrc->HeaderAMin)*65535.0);
				}
				if(TIFFWriteScanline(tiff, tiffBuffer, row, 0)<0) {
					break;
				}
			}
			break;
		}
		case 32: { // Float
			for(row=0; row < h; row++) {
				for(col=0; col < w; col++) {
					mrcPixelDataGet(mrc, col, h - 1 - row, z, &data, mrcPixelRePart, mrcPixelHowNearest);
					*(((float*)tiffBuffer)+col) = (float)(data + linfo.offset);
				}
				if(TIFFWriteScanline(tiff, tiffBuffer, row, 0)<0) {
					break;
				}
			}
			break;
		}
	}
    TIFFWriteDirectory(tiff);
    }
}
