#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define GLOBAL_DECLARATION       
#include "../inc/config.h"
#undef DEBUG
#include "genUtil.h"
#include "mrcImage.h"
#include "Vector.h"
#include "lmrcFFTInfo.h"

int
main(int argc, char* argv[])
{
    mrcImage fft;
	mrcFFTInfoInfo info;
	FILE* fpt;
	floatVector* ScatteringAngularDistribution;
	floatVector* ScatteringAngularDistributionAverage;
	floatVector** ScatteringAngularDistributionAverageDivision;
	floatVector* ScatteringAngularDistributionSD;
	floatVector** ScatteringAngularDistributionSDDivision;
	floatVector* XAxisMag;
	floatVector* XAxisPhase;
	floatVector* YAxisMag;
	floatVector* YAxisMagAvg;
	floatVector* YAxisPhase;
	floatVector* Spacing;
	long i, j;
	int mode;

    init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);
    mrcFileRead (&fft, info.In,  "from Main Routine", 0);
	fpt = info.fptOut;

    if(0x00000010&info.mode) {
        Spacing = lmrcFSInfoSpacing(&fft);
    }

	switch(0x0000000F&info.mode) {
		case 1: {
        	ScatteringAngularDistribution = lmrcFSInfoScatteringAngularDistribution(&fft);
			break;
		}
		case 2: {
        	XAxisMag = lmrcFSInfoXAxisMag(&fft);
			XAxisPhase = lmrcFSInfoXAxisPhase(&fft);
			break;
		}
		case 4: {
        	YAxisMag = lmrcFSInfoYAxisMag(&fft);
        	YAxisPhase = lmrcFSInfoYAxisPhase(&fft);
			break;
		}
		case 5: {
        	YAxisMagAvg = lmrcFSInfoYAxisMagAverage(&fft);
			break;
		}
		case 7: {
			DEBUGPRINT("lmrcFSInfoScatteringAngularDistributionDivisionAverage Call: Start\n");
        	ScatteringAngularDistributionAverageDivision = lmrcFSInfoScatteringAngularDistributionDivisionAverage(&fft, info.Angle*RADIAN, info.nDivision, 0);
			DEBUGPRINT("lmrcFSInfoScatteringAngularDistributionDivisionAverage Call: End\n");
			break;
		}
		case 8: {
        	ScatteringAngularDistributionAverage = lmrcFSInfoScatteringAngularDistributionAverage(&fft);
			break;
		}
		default: {
			fprintf(stderr, "Not supported mode: %ld", info.mode);
			exit(EXIT_FAILURE);
		}
    }

	DEBUGPRINT("SD\n");
    if((0x00000020&info.mode)&&((0x0f&info.mode)==7)) {
		DEBUGPRINT("lmrcFSInfoScatteringAngularDistributionDivisionSD Call: Start\n");
        ScatteringAngularDistributionSDDivision = lmrcFSInfoScatteringAngularDistributionDivisionSD(&fft, info.Angle*RADIAN, info.nDivision, 0);
		DEBUGPRINT("lmrcFSInfoScatteringAngularDistributionDivisionSD Call: End\n");
    }
    if((0x00000020&info.mode)&&((0x0f&info.mode)==8)) {
        ScatteringAngularDistributionSD = lmrcFSInfoScatteringAngularDistributionSD(&fft);
    }

	DEBUGPRINT("Information Print");
	switch(0xf&info.mode) { 
		case 1: {
        	fprintf(fpt, "%ld\n", ScatteringAngularDistribution->size);
        	for(i=0; i<ScatteringAngularDistribution->size; i++) {
				if(0x40&info.mode) {
           			fprintf(fpt, "%12.3e\n", log10(MAX(1e-30, ScatteringAngularDistribution->data[i])));
				} else {
           			fprintf(fpt, "%15.6e\n", ScatteringAngularDistribution->data[i]);
				}
        	}
			break;
		}
		case 2: {
        	fprintf(fpt, "%ld\n", XAxisMag->size);
        	for(i=0; i<XAxisMag->size; i++) {
				if(0x40&info.mode) {
           			fprintf(fpt, "%12.3e %15.6e\n", log10(MAX(1e-30, fabs(XAxisMag->data[i]))), XAxisPhase->data[i]*DEGREE);
				} else {
           			fprintf(fpt, "%15.6e %15.6e\n", XAxisMag->data[i], XAxisPhase->data[i]*DEGREE);
				}
        	}
			break;
    	}
		case 4: {
	        fprintf(fpt, "%ld\n", YAxisMag->size);
	        for(i=0; i<YAxisMag->size; i++) {
				if(0x40&info.mode) {
	            	fprintf(fpt, "%12.3e %15.6e\n", log10(MAX(1e-30, fabs(YAxisMag->data[i]))), YAxisPhase->data[i]*DEGREE);
				} else {
	            	fprintf(fpt, "%15.6e %15.6e\n",YAxisMag->data[i], YAxisPhase->data[i]*DEGREE);
				}
	        }
			break;
    	}
		case 5: {
	        fprintf(fpt, "%ld\n", YAxisMag->size);
	        for(i=0; i<YAxisMagAvg->size; i++) {
				if(0x40&info.mode) {
	            	fprintf(fpt, "%12.3e %15.6e\n", log10(MAX(1e-30, fabs(YAxisMagAvg->data[i]))), YAxisPhase->data[i]*DEGREE);
				} else {
	            	fprintf(fpt, "%15.6e %15.6e\n",YAxisMagAvg->data[i], YAxisPhase->data[i]*DEGREE);
				}
	        }
			break;
    	}
		case 7: { 
			mode = 0x00000030&info.mode; 	
			switch(mode) {
				case 0: {
					fprintf(fpt, "%ld %ld\n", info.nDivision, ScatteringAngularDistributionAverageDivision[0]->size);
					break;
				}
				case 0x10: {
					fprintf(fpt, "%ld %ld\n", info.nDivision+1, ScatteringAngularDistributionAverageDivision[0]->size);
					break;
				}
				case 0x20: {
					fprintf(fpt, "%ld %ld\n", info.nDivision*2, ScatteringAngularDistributionAverageDivision[0]->size);
					break;
				}
				case 0x30: {
					fprintf(fpt, "%ld %ld\n", info.nDivision*2+1, ScatteringAngularDistributionAverageDivision[0]->size);
					break;
				}
			}
	   		for(i=0; i<ScatteringAngularDistributionAverageDivision[0]->size; i++) {
				if(info.mode&0x10) {
	   	        	fprintf(fpt, "%15.6e ", Spacing->data[i]);
				}
				for(j=0; j<info.nDivision; j++) {
					if(0x40&info.mode) {
	   	        		fprintf(fpt, "%12.3e ", log10(MAX(1e-30,ScatteringAngularDistributionAverageDivision[j]->data[i])));
					} else {
	   	        		fprintf(fpt, "%15.6e ", ScatteringAngularDistributionAverageDivision[j]->data[i]);
					}
					if(info.mode&0x20) {
						if(0x40&info.mode) {
	   	        			fprintf(fpt, "%12.3e ", log10(MAX(1e-30,ScatteringAngularDistributionSDDivision[j]->data[i])));
						} else {
	   	        			fprintf(fpt, "%15.6e ", ScatteringAngularDistributionSDDivision[j]->data[i]);
						}		
					}
				}
				fprintf(fpt, "\n");
			}	
			break;
		}
		case 8: {		
			mode = 0x00000030&info.mode; 	
			switch(mode) {
				case 0: {
					fprintf(fpt, "%d %ld\n", 1, ScatteringAngularDistributionAverage->size);
					break;
				}
				case 0x10: {
					fprintf(fpt, "%d %ld\n", 1+1, ScatteringAngularDistributionAverage->size);
					break;
				}
				case 0x20: {
					fprintf(fpt, "%d %ld\n", 1*2, ScatteringAngularDistributionAverage->size);
					break;
				}
				case 0x30: {
					fprintf(fpt, "%d %ld\n", 1*2+1, ScatteringAngularDistributionAverage->size);
					break;
				}
			}
	   		for(i=0; i<ScatteringAngularDistributionAverage->size; i++) {
				if(info.mode&0x10) {
	   	        	fprintf(fpt, "%15.6e ", Spacing->data[i]);
				}
				if(0x40&info.mode) {
	   	        	fprintf(fpt, "%12.3e ", log10(MAX(1e-30,ScatteringAngularDistributionAverage->data[i])));
				} else {
	   	        	fprintf(fpt, "%15.6e ", ScatteringAngularDistributionAverage->data[i]);
				}
				if(info.mode&0x20) {
					if(0x40&info.mode) {
	   	        		fprintf(fpt, "%12.3e ", log10(MAX(1e-30,ScatteringAngularDistributionSD->data[i])));
					} else {
	   	        		fprintf(fpt, "%15.6e ", ScatteringAngularDistributionSD->data[i]);
					}		
				}
				fprintf(fpt, "\n");
			}	
			break;
		}
    }
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "Mode: \n");
	fprintf(stderr, "\t 1 :Scattering Angular Distribution(Sum)\n");
	fprintf(stderr, "\t 2 :X-axis (OutPut: Mag, Phase)\n");
	fprintf(stderr, "\t 4 :Y-axis (OutPut: Mag, Phase)\n");
	fprintf(stderr, "\t 5 :Y-axis (Average:Along X-axis)(OutPut: Mag, Phase)\n");
	fprintf(stderr, "\t 7 :Scattering Angular Distribution(Average, range(angle, nDivion)xnDiv; e.g. (10, 18) -> range(10-360/18/2, 10+360/18/2) x nDiv\n");
	fprintf(stderr, "\t 8 :Scattering Angular Distribution(Average)\n");
	fprintf(stderr, "\t+16 :with spacing \n");
	fprintf(stderr, "\t+32 :with Angular Distribution(SD)\n");
	fprintf(stderr, "\t+64 :Log Scaling for |value| \n");
}
