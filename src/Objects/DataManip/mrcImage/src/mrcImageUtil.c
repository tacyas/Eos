#include <string.h>
#include <stdlib.h>
#include "../inc/mrcImage.h"

int
IsFloatImage(mrcImage* img, char* message, mrcImageParaTypeInteger mode)
{

    switch(img->HeaderMode) {
        case mrcFloatRadonImage:
		case mrcFloatImage: {
			return 1;
		}
		default: {
			return 0;
		}
	}
}

int
IsFloatFT(mrcImage* img, char* message, mrcImageParaTypeInteger mode)
{

    switch(img->HeaderMode) {
        case mrcFloatRadonFT:
		case mrcComplexFloatFT: {
			return 1;
		}
		default: {
			return 0;
		}
	}
}

int
IsImage(mrcImage* img, char* message, mrcImageParaTypeInteger mode)
{
    switch(img->HeaderMode) {
        case mrcFloatRadonFT:
        case mrcComplexShortFT:
		case mrcComplexLongFT:
		case mrcComplexFloatFT:
		case mrcComplexDoubleFT: {
			return 0;
		}
        case mrcFloatRadonImage:
        case mrcCharImage:
        case mrcShortImage:
        case mrcUShortImage:
		case mrcLongImage:
		case mrcFloatImage:
		case mrcDoubleImage: {
			return 1;
		}
        case mrcComplexShortFFT:
		case mrcComplexLongFFT:
		case mrcComplexFloatFFT:
		case mrcComplexDoubleFFT: {
			return 0;
		}
		default: {
			char s[20];
			sprintf(s, "mrcImage Mode %ld", img->HeaderMode);
			mrcError(message, "IsImage", s,
				mode|MRC_ModeNotSupported);
		}
	}
	return -1;
}

int
IsFT(mrcImage* FT, char* message, mrcImageParaTypeInteger mode)
{
    switch(FT->HeaderMode) {
        case mrcComplexShortFT:
		case mrcComplexLongFT:
		case mrcFloatRadonFT:
		case mrcComplexFloatFT:
		case mrcComplexDoubleFT: {
			return 1;
		}
        case mrcFloatRadonImage:
        case mrcCharImage:
        case mrcShortImage:
        case mrcUShortImage:
		case mrcLongImage:
		case mrcFloatImage:
		case mrcDoubleImage: {
			return 0;
		}
        case mrcComplexShortFFT:
		case mrcComplexLongFFT:
		case mrcComplexFloatFFT:
		case mrcComplexDoubleFFT: {
			return 0;
		}
		default: {
			char s[20];
			sprintf(s, "mrcImage Mode %ld", FT->HeaderMode);
			mrcError(message, "IsFT", s,
				mode|MRC_ModeNotSupported);
		}
	}
	return -1;
}


int
IsFFT(mrcImage* FFT, char* message, mrcImageParaTypeInteger mode)
{
    switch(FFT->HeaderMode) {
        case mrcFloatRadonImage:
        case mrcCharImage:
        case mrcShortImage:
		case mrcLongImage:
		case mrcFloatImage:
		case mrcDoubleImage: {
			return 0;
		}
        case mrcFloatRadonFT:
        case mrcComplexShortFT:
		case mrcComplexLongFT:
		case mrcComplexFloatFT:
		case mrcComplexDoubleFT: {
			return 0;
		}
        case mrcComplexShortFFT:
		case mrcComplexLongFFT:
		case mrcComplexFloatFFT:
		case mrcComplexDoubleFFT: {
			return 1;
		}
		default: {
			char s[20];
			sprintf(s, "mrcImage Mode %ld", FFT->HeaderMode);
			mrcError(message, "IsFFT", s,
				mode|MRC_ModeNotSupported);
		}
	}
	return -1;
}


