/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% mrcImageInit ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : mrcImageInit 
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%mrcImageInit ver%I%; Date:%D% %Z%";

#undef DEBUG
#include "genUtil.h"
#include "Memory.h"
#include <stdio.h>
#include <stdlib.h>
#include "../inc/mrcImage.h"

/* Intrinsic Function */
extern void __mrcAllocate(mrcImage* mrc, char* message);

#define RTN_NAME "mrcInit"

/*
* mrcInit
*    Initialize mrcImage
*
*/
mrcStatusType
mrcInit(mrcImage* mrc, char* filename)
{
	DEBUGPRINT("in mrcInit\n");
    /* Unless filename == NULL, File Header Read */
    if(NULL!=filename) {
        mrcHeaderRead(mrc, filename, "in mrcInit", 0);
    } else {
	    mrcDefaultHeaderValueSetOnlyFixedValue(mrc);
		mrc->numTailer = 0;
	}
    /* Label Number Check */
    if(mrc->HeaderLabelN>MRC_MAX_LABEL_N) {
        mrc->HeaderLabelN = 0L;
    }
   	mrcHiddenDataSet(mrc, 0); 

    __mrcAllocate(mrc, filename);
	
    mrc->status = 0;
    return 0;
}
#undef RTN_NAME

void
__mrcAllocate(mrcImage* mrc, char* message)
{
    size_t bufsize;
    char s[20];
	size_t i;

    bufsize = (size_t)((size_t)mrc->BytePerBand*(size_t)mrc->BandPerPixel*(size_t)mrc->PixelPerImage);
	mrc->BytePerImage = bufsize;
	DEBUGPRINT1("bufsize: %d\n", bufsize);
    if(NULL==(mrc->Image=(char*)malloc(bufsize))) {
        sprintf(s, "%16ld", bufsize);
    	mrcError(message, "__mrcAllocate", s,
    	mrcStatusMask_ExitFailure|MRC_MemoryNotAllocate);
    }
	for(i=0; i<bufsize; i++) {
		mrc->Image[i] = (char)0;
	}
    mrc->ImageCharImage = mrc->ImageShortImage 
						= mrc->ImageLongImage
        				= mrc->ImageFloatImage 
						= mrc->ImageDoubleImage 
						= (double*)mrc->Image;
}

void
mrcImageFree(mrcImage* mrc, char* message) 
{
	if(NULL!=mrc->Image) {
		free(mrc->Image);
	}
    mrc->ImageCharImage = mrc->ImageShortImage 
						= mrc->ImageLongImage
        				= mrc->ImageFloatImage 
						= mrc->ImageDoubleImage 
						= mrc->Image 
						= (void*)NULL;
}

#define RTN_NAME "mrcHiddenDataSet"

mrcStatusType
mrcHiddenDataSet(mrcImage* mrc, long mode)
{
	char s[20];

	/* Set Byte/Band */
    switch(mrc->HeaderMode) {
        case mrcCharImage: {
    	    mrc->BytePerBand = 1L;
            break;
        }
        case mrcShortImage: 
        case mrcUShortImage: 
        case mrcComplexShortFT: 
        case mrcComplexShortFFT: {
    	    mrc->BytePerBand = 2L;
            break;
        }
        case mrcFloatRadonImage: 
        case mrcFloatRadonFT: 
        case mrcFloatImage: 
        case mrcLongImage: 
        case mrcComplexFloatFT: 
        case mrcComplexFloatOneDimFT: 
        case mrcComplexLongFT: 
        case mrcComplexFloatFFT: 
        case mrcComplexLongFFT: {
    	    mrc->BytePerBand = 4L;
            break;
        }
        case mrcDoubleImage: 
        case mrcComplexDoubleFT: 
        case mrcComplexDoubleFFT: {
    	    mrc->BytePerBand = 8L;
            break;
    	}
        default: {
            sprintf(s, "ImageMode %ld", mrc->HeaderMode);
            return mrcError("", RTN_NAME, s,
        			  mrcStatusMask_ExitFailure|MRC_ModeNotSupported);
        }
    }
    /* Set Band/Pixel */
    switch(mrc->HeaderMode) {
        case mrcFloatRadonImage:
        case mrcCharImage:
        case mrcShortImage:
        case mrcUShortImage:
        case mrcFloatImage: 
        case mrcLongImage: 
        case mrcDoubleImage: {
    	    mrc->BandPerPixel = 1L;
    	    break;
    	}
        case mrcFloatRadonFT: 
        case mrcComplexShortFT: 
        case mrcComplexFloatFT: 
        case mrcComplexFloatOneDimFT: 
        case mrcComplexLongFT: 
        case mrcComplexDoubleFT: 
        case mrcComplexShortFFT: 
        case mrcComplexFloatFFT: 
        case mrcComplexLongFFT: 
        case mrcComplexDoubleFFT: {
    	    mrc->BandPerPixel = 2L;
    	    break;
    	}
        case mrcCharImageRGB: {
    	    mrc->BandPerPixel = 3L;
    	    break;
		}
        default: {
            sprintf(s, "ImageMode %ld", mrc->HeaderMode);
            return mrcError("", RTN_NAME, s,
        			  mrcStatusMask_ExitFailure|MRC_ModeNotSupported);
        }
    }

	/* Pixel/Image */
    if(0==mrc->HeaderN.z) {
        mrc->HeaderN.z = (mrcImageParaTypeInteger)1;
    	mrcError("", RTN_NAME, "z element",
        		 MRC_SizeOfZero);
    }
    if(0==mrc->HeaderN.y) {
	mrc->HeaderN.y = (mrcImageParaTypeInteger)1;
	mrcError("", RTN_NAME, "y element",
		 MRC_SizeOfZero);
    }
    if(0==mrc->HeaderN.x) {
	mrc->HeaderN.x = (mrcImageParaTypeInteger)1;
	mrcError("", RTN_NAME, "x element",
		 MRC_SizeOfZero);
    }

    switch(mrc->HeaderMode) {
        case mrcFloatRadonImage:
        case mrcCharImage:
        case mrcShortImage:
        case mrcUShortImage:
        case mrcFloatImage: 
        case mrcLongImage: 
        case mrcDoubleImage: {
    		mrc->PixelPerImage = (size_t)mrc->HeaderN.x*(size_t)mrc->HeaderN.y*(size_t)mrc->HeaderN.z;
    	    break;
    	}
        case mrcFloatRadonFT:
        case mrcComplexShortFT: 
        case mrcComplexFloatFT: 
        case mrcComplexFloatOneDimFT: 
        case mrcComplexLongFT: 
        case mrcComplexDoubleFT: 
        case mrcComplexShortFFT: 
        case mrcComplexFloatFFT: 
        case mrcComplexLongFFT: 
        case mrcComplexDoubleFFT: {
    		mrc->PixelPerImage = (size_t)(mrc->HeaderN.x/2+1)*(size_t)mrc->HeaderN.y*(size_t)mrc->HeaderN.z;
    	    break;
    	}
        default: {
            sprintf(s, "ImageMode %ld", mrc->HeaderMode);
            return mrcError("", RTN_NAME, s,
        			  mrcStatusMask_ExitFailure|MRC_ModeNotSupported);
        }
    }

	/* Byte/Image */
	mrc->BytePerImage = mrc->BytePerBand
						*mrc->BandPerPixel
						*mrc->PixelPerImage;
	DEBUGPRINT4("b/i: %lu, b/B: %d, B/p: %d, p/i:%lu in mrcHiddenDataSet\n", mrc->BytePerImage, mrc->BytePerBand, mrc->BandPerPixel, mrc->PixelPerImage);	
	return 1;
}

/*
	Default Header Value Set
*/
mrcStatusType
mrcDefaultHeaderValueSet(mrcImage* mrc)
{
	memoryClear(mrc->Header.All, sizeof(char)*MRC_HEADER, 0);
	mrc->HeaderN.x  = 1;
	mrc->HeaderN.y  = 1;
	mrc->HeaderN.z  = 1;
	mrc->HeaderM.x  = 1;
	mrc->HeaderM.y  = 1;
	mrc->HeaderM.z  = 1;
	mrc->HeaderLength.x  = 1;
	mrc->HeaderLength.y  = 1;
	mrc->HeaderLength.z  = 1;
	mrc->HeaderAlpha  = 90;
	mrc->HeaderBeta   = 90;
	mrc->HeaderGamma  = 90;
	mrc->HeaderMAPC   = 1;
	mrc->HeaderMAPR   = 2;
	mrc->HeaderMAPS   = 3;
}

mrcStatusType
mrcDefaultHeaderValueSetOnlyFixedValue(mrcImage* mrc)
{
	mrc->HeaderM.x  = 1;
	mrc->HeaderM.y  = 1;
	mrc->HeaderM.z  = 1;
	mrc->HeaderAlpha  = 90;
	mrc->HeaderBeta   = 90;
	mrc->HeaderGamma  = 90;
	mrc->HeaderMAPC   = 1;
	mrc->HeaderMAPR   = 2;
	mrc->HeaderMAPS   = 3;
	mrc->HeaderISPG    = 0;
	mrc->HeaderNSYMBT  = 0;
	mrc->HeaderLSKFLG  = 0;
}

