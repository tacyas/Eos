#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define GLOBAL_DECLARATION       
#undef DEBUG
#include "../inc/config.h"
#include "mrcImage.h"
#include "genUtil.h"
#include "eosString.h"

#define SQR(x) ((x)*(x))
#define SECTION_MARK " ,"
extern void lmrcFFTCTFDataSet(mrcImage* fft, FILE* fpt, long mode);
void
main(int argc, char* argv[])
{
    mrcImage fft0;
    mrcImage fft1;
	mrcImage fft2;
    mrcFFTCTFCompensationInfo info;

    init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);
    mrcFileRead (&fft0, info.In,  "from Main Routine", 0);
	fft2.Header = fft1.Header = fft0.Header;
	mrcInit(&fft1, NULL);
	mrcInit(&fft2, NULL);
    lmrcFFTCTFDataSet(&fft1, info.fptCTFIn, info.mode);
	lmrcFFTFxG(&fft2, &fft1, &fft0);
    mrcFileWrite(&fft2, info.Out, "from Main Routine", 0);
}
void
additionalUsage()
{
	fprintf(stderr, ">>> CTFWeigting File\n");	
	fprintf(stderr, "RR0 F0 : If R<RR0, Weight=0. If RR0<=R<RR1,  Weight={(RR1-R)*F0+(R-RR0)*F1}/(RR1-RR0), i.e., Linear Interpolation\n");	
	fprintf(stderr, "RR1 F1 : \n");	
	fprintf(stderr, "...................................\n");	
	fprintf(stderr, "RRn Fn	: If RRn<=R, Fn\n");
}
void
lmrcFFTCTFDataSet(mrcImage* fft, FILE* fpt, long mode)
{
    mrcImageParaTypeReal iX, iY, iZ;
    double R, data;
	double RR0, F0;           
	double RR1, F1;           
	char s[GEN_UTIL_MAX_STRING_LENGTH];

	iZ = 0.0;
	DEBUGPRINT("in lmrcFFTCTFDataSet\n");
    for(iX=0; iX<fft->HeaderN.x/2; iX++) {
    	for(iY=-fft->HeaderN.y/2; iY<fft->HeaderN.y/2; iY++) {
            mrcPixelDataSet(fft, iX, iY, iZ, 1.0, mrcPixelRePart);
            mrcPixelDataSet(fft, iX, iY, iZ, 1.0, mrcPixelImPart);
	   }
    }
	fseek(fpt, 0L, SEEK_SET);
    stringGetFromFile(s, "", fpt, NULL, 1);
    RR0  = stringGetNthRealData(s, 1, SECTION_MARK);
    F0   = stringGetNthRealData(s, 2, SECTION_MARK);
    for(iX=0; iX<fft->HeaderN.x/2; iX++) {
    	for(iY=-fft->HeaderN.y/2; iY<fft->HeaderN.y/2; iY++) {
            R = sqrt(SQR(iX/fft->HeaderN.x/fft->HeaderLength.x)
					+SQR(iY/fft->HeaderN.y/fft->HeaderLength.y));
            if(R<RR0) {
                mrcPixelDataSet(fft, iX, iY, iZ, 0.0, mrcPixelRePart);
                mrcPixelDataSet(fft, iX, iY, iZ, 0.0, mrcPixelImPart);
            } 
        }
    }
    while(NULL!=stringGetFromFile(s, "", fpt, NULL, 1)) {
        RR1  = stringGetNthRealData(s, 1, SECTION_MARK);
        F1   = stringGetNthRealData(s, 2, SECTION_MARK);
		if(RR0>RR1) {
			fprintf(stderr, "Funny Data of RR in CTF File RR(0:%g-1:%g)\n", RR0, RR1);
			exit(EXIT_FAILURE);
		} 
    	for(iX=0; iX<fft->HeaderN.x/2; iX++) {
    		for(iY=-fft->HeaderN.y/2; iY<fft->HeaderN.y/2; iY++) {
            	R = sqrt(SQR(iX/fft->HeaderN.x/fft->HeaderLength.x)
						+SQR(iY/fft->HeaderN.y/fft->HeaderLength.y));
                if(RR0<=R && R<=RR1) {
					data = (F0*(RR1-R)+F1*(R-RR0))/(RR1-RR0);
					mrcPixelDataSet(fft, iX, iY, iZ, (F0*(RR1-R)+F1*(R-RR0))/(RR1-RR0), mrcPixelRePart);	
					mrcPixelDataSet(fft, iX, iY, iZ,                               0.0, mrcPixelImPart);	
                }
            }
        }
        RR0  = RR1;
        F0   = F1;
    }
    for(iX=0; iX<fft->HeaderN.x/2; iX++) {
    	for(iY=-fft->HeaderN.y/2; iY<fft->HeaderN.y/2; iY++) {
            R = sqrt(SQR(iX/fft->HeaderN.x/fft->HeaderLength.x)
					+SQR(iY/fft->HeaderN.y/fft->HeaderLength.y));
            if(RR0<R) {
				mrcPixelDataSet(fft, iX, iY, iZ,  F0, mrcPixelRePart);
				mrcPixelDataSet(fft, iX, iY, iZ, 0.0, mrcPixelImPart);
            }
        }
    }
}
