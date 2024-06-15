/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% lltlg2mrc ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : lltlg2mrc 
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%lltlg2mrc ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define UNDEBUG
#include "genUtil.h"
#include "File.h"
#include "eosString.h"
#include "ltlgData.h"
#include "mrcImage.h"
#include "lltlg2mrc.h"

void
ltlg2mrcConfigFileRead(lltlg2mrcInfo* linfo, FILE* fpt)
{
	char s[1024];
	ltlgDataLLDataInfo w;
	long mode;

	if(stdin==fpt) {
		mode = 0;	
	} else {
		mode = 3;
	}
	fseek(fpt, 0L, SEEK_SET);	
	stringGetFromFile(s, "Input", fpt, stdout, mode); 
	if(!linfo->flagIn) {
		linfo->flagIn++;
		linfo->In =  stringGetNthWord(s, 1, " \t");
		linfo->flagIn++;
		linfo->fptIn = fileOpen(linfo->In, "r");
	}
	stringGetFromFile(s, "Title", fpt, stdout, mode); 
	if(!linfo->flagTitle) {
		linfo->flagTitle++;
		linfo->Title = stringGetNthWord(s, 1, " \t,");
		linfo->flagTitle++;
	}
	stringGetFromFile(s, "any", fpt, stdout, mode);  /* Skip */
	stringGetFromFile(s, "delta[A]", fpt, stdout, mode);  
	if(!linfo->flagdelta) {
		linfo->flagdelta++;
		linfo->delta = stringGetNthRealData(s, 1, " ,\t");
	}
	stringGetFromFile(s, "RepeatDistance rMax", fpt, stdout, mode);  
	if(!linfo->flagRepeatDistance) {
		linfo->flagRepeatDistance++;
		linfo->RepeatDistance = stringGetNthRealData(s, 1, " ,\t");
	}
	if(!linfo->flagrMax) {
		linfo->flagrMax++;
		linfo->rMax = stringGetNthRealData(s, 2, " ,\t");
	}
	stringGetFromFile(s, "phiStart[degree]", fpt, stdout, mode);  
	if(!linfo->flagphiStart) {
		linfo->flagphiStart++;
		linfo->phiStart = stringGetNthRealData(s, 1, " ,\t")*RADIAN;
	}
	stringGetFromFile(s, "zMin[A] zMax[A] deltaz[A] ", fpt, stdout, mode);  
	if(!linfo->flagzMin) {
		linfo->flagzMin++;
		linfo->zMin = stringGetNthRealData(s, 1, " ,\t");
	}
	if(!linfo->flagzMax) {
		linfo->flagzMax++;
		linfo->zMax = stringGetNthRealData(s, 2, " ,\t");
	}
	if(!linfo->flagdeltaz) {
		linfo->flagdeltaz++;
		linfo->deltaz = stringGetNthRealData(s, 3, " ,\t");
	}
	stringGetFromFile(s, "WeightOfOthLayer", fpt, stdout, mode);  
	if(!linfo->flagWeightOf0thLayer) {
		linfo->flagWeightOf0thLayer++;
		linfo->WeightOf0thLayer = stringGetNthRealData(s, 1, " ,\t");
	}
	while(NULL!=stringGetFromFile(s, "NL WEIGHT", fpt, stdout, mode)) {
		if(0==stringLength(s)) {
			break;
		} else {
			if(!linfo->flagLayer) {
				w.NL= stringGetNthIntegerData(s, 1, " \t,");
				if(99==w.NL) {
					if(!linfo->f99) {
						linfo->f99++;
					}
				} else {
					w.WT = stringGetNthRealData(s, 2, " \t,");
				}
			}
		}
	}

	stringGetFromFile(s, "ACUT", fpt, stdout, mode);  
	if(!linfo->flagCUT) {
		linfo->flagCUT++;
		linfo->CUT = stringGetNthRealData(s, 1, " ,\t");
	}
	stringGetFromFile(s, "Mean Sigma", fpt, stdout, mode);  
	if(!linfo->flagMean) {
		linfo->flagMean++;
		linfo->Mean = stringGetNthRealData(s, 1, " ,\t");
	}
	if(!linfo->flagSigma) {
		linfo->flagSigma++;
		linfo->Sigma = stringGetNthRealData(s, 2, " ,\t");
	}
	stringGetFromFile(s, "Mean Sigma", fpt, stdout, mode);  
	if(!linfo->flagOut) {
		linfo->Out = stringGetNthWord(s, 1, " ,\t"); 
		linfo->flagOut++;
		linfo->fptOut = fileOpen(linfo->Out, "w");
	}
}
/*
*
*     RHO(R) = SUM(GLIT(R).EXP(i(N*PHI-2*M_PI*L*Z/c)))
*     COMBINING GLIT (-L,-N) AND GLIT(L,N), RHO=A*COS()-B*SIN()
*
*/

void
lltlg2mrc(ltlgData* ltlg, mrcImage* mrc, lltlg2mrcInfo* linfo)
{
    mrcImageParaTypeReal  x,  y,  z;
    mrcImageParaTypeReal ix, iy, iz;
    ltlgDataParaTypeInteger ll, ir;
    double                  r, rr, rbit, rbar, recz; 
    double ang, phi, rho, re, im;
    double sumrho, sumrho2, min, max;
    double ave, sig, n, aveEdge;
	double re0, im0, re1, im1; 
	mrcImageParaTypeReal xmin, xmax, xdelta;
	mrcImageParaTypeReal ymin, ymax, ydelta;
	mrcImageParaTypeReal zmin, zmax, zdelta;

    mrc->HeaderN.x = mrc->HeaderN.y = fabs(2.0*linfo->rMax/linfo->delta + 1);
    mrc->HeaderN.z                  = fabs((linfo->zMax-linfo->zMin)/linfo->deltaz + 1);

    mrc->HeaderMode = mrcFloatImage;

	mrc->HeaderM.x = 1;
	mrc->HeaderM.y = 1;
	mrc->HeaderM.z = 1;

    mrc->HeaderLength.x = linfo->delta;
	mrc->HeaderLength.y = linfo->delta;
    mrc->HeaderLength.z = linfo->deltaz;

    mrc->HeaderAlpha = mrc->HeaderBeta = mrc->HeaderGamma = 90.0;
    mrc->HeaderMAPC = 1;
    mrc->HeaderMAPR = 2;
    mrc->HeaderMAPS = 3;
    mrcInit(mrc, NULL);

	if(!linfo->AntiPole) {
		xmin   = -linfo->rMax;
		xmax   =  linfo->rMax;
		xdelta =  linfo->delta;
		ymin   = -linfo->rMax;
		ymax   =  linfo->rMax;
		ydelta =  linfo->delta;
		zmin   =  linfo->zMin;
		zmax   =  linfo->zMax;
		zdelta =  linfo->deltaz;
	} else {
		xmin   =  linfo->rMax;
		xmax   = -linfo->rMax;
		xdelta = -linfo->delta;
		ymin   = -linfo->rMax;
		ymax   =  linfo->rMax;
		ydelta =  linfo->delta;
		zmax   =  linfo->zMin;
		zmin   =  linfo->zMax;
		zdelta = -linfo->deltaz;
	}
    n = 0.0;
    min = 0.0; max = 0.0;
    recz = 2*PI/linfo->RepeatDistance;
    for(z=zmin, iz=0; iz<mrc->HeaderN.z; z+=zdelta, iz++) {
        fprintf(stderr, "z: %10.2f [A] ", z);
        DEBUGPRINT1("z: %10.2f [A] ", z);
        for(x=xmin, ix=0; ix<mrc->HeaderN.x; x+=xdelta, ix++) {
        	for(y=ymin, iy=0; iy<mrc->HeaderN.y; y+=ydelta, iy++) {
                rho = 0.0;
                r = sqrt(x*x + y*y);
                rr = r/ltlg->r.d;
                ir = (ltlgDataParaTypeInteger)rr;
                rbit = rr - ir;
                rbar = 1.0 - rbit;
                if(linfo->rMax < r || ltlg->r.Max < r ) {
                    rho = 0.0;
                } else if (ltlg->r.n - 1 < ir + 1) {
                    if(r==0.0) {
                        ang = 0.0;
                    } else {
                        ang = atan2(y, x) + PI/2 + linfo->phiStart;
                    }
                    for(ll=0; ll<ltlg->ll.Max; ll++) { /* Linear Interpolation */
                        if(ltlg->llInfo[ll].WT>0) {
                            phi = ltlg->llInfo[ll].NN*ang - ltlg->llInfo[ll].NL*z*recz;
							if(ltlg->r.n - 1 < ir) {
								re0 = 0;
								im0 = 0;
							} else {
								re0 = ltlg->ltlg[ll][ir].Re;
								im0 = ltlg->ltlg[ll][ir].Im;
							}
							if(ltlg->r.n - 1 < ir + 1) {
								re1 = 0;
								im1 = 0;
							} else {
								re1 = ltlg->ltlg[ll][ir].Re;
								im1 = ltlg->ltlg[ll][ir].Im;
							}
                            re  = rbar*re0 + rbit*im0;
                            im  = rbar*re1 + rbit*im1;
                           	rho = rho + cos(phi)*re - sin(phi)*im;
                        }
                    }
				} else {
                    if(r==0.0) {
                        ang = 0.0;
                    } else {
                        ang = atan2(y, x) + PI/2 + linfo->phiStart;
                    }
                    for(ll=0; ll<ltlg->ll.Max; ll++) { /* Linear Interpolation */
                        if(ltlg->llInfo[ll].WT>0) {
                            phi = ltlg->llInfo[ll].NN*ang - ltlg->llInfo[ll].NL*z*recz;
                            re  = rbar*ltlg->ltlg[ll][ir].Re + rbit*ltlg->ltlg[ll][ir+1].Re;
                            im  = rbar*ltlg->ltlg[ll][ir].Im + rbit*ltlg->ltlg[ll][ir+1].Im;
                           	rho = rho + cos(phi)*re - sin(phi)*im;
                        }
                    }
                }
                mrcPixelDataSet(mrc, ix, iy, iz, rho, mrcPixelMag);
                if(min>rho) {
                    min = rho;
                }
                if(max<rho) {
                    max = rho;
                }
                n++;
            }
        }
        mrcPixelDataGet(mrc, ix/2, iy/2, iz, &rho, mrcPixelMag, mrcPixelHowNearest);
        fprintf(stderr, "(%f, %f) = %g\n", ix/2.0, iy/2.0, rho);
		DEBUGPRINT3("(%f, %f) = %g\n", ix/2.0, iy/2.0, rho);
    }
    if(n!=(mrc->HeaderN.x*mrc->HeaderN.y*mrc->HeaderN.z)) {
        fprintf(stderr, "Different Number %d != %f\n", (int)(mrc->HeaderN.x*mrc->HeaderN.y*mrc->HeaderN.z), n);
	}
    sumrho = sumrho2 = n = 0.0;
    for(z=linfo->zMin, iz=0; z<=linfo->zMax; z+=linfo->deltaz, iz++) {
        for(x=-linfo->rMax, ix=0; x<=linfo->rMax; x+=linfo->delta, ix++) {
            for(y=-linfo->rMax, iy=0; y<=linfo->rMax; y+=linfo->delta, iy++) {
                r = sqrt(x*x + y*y);
                if(linfo->rMax-1<r && r<=linfo->rMax) {
                    mrcPixelDataGet(mrc, ix, iy, iz, &rho, mrcPixelMag, mrcPixelHowNearest);
                    sumrho += rho;
                    n++;
                }
            }
        }
    }
    ave = sumrho/n;
	aveEdge = ave;
    sumrho = sumrho2 = n = 0.0;
    for(z=linfo->zMin, iz=0; z<=linfo->zMax; z+=linfo->deltaz, iz++) {
        for(x=-linfo->rMax, ix=0; x<=linfo->rMax; x+=linfo->delta, ix++) {
            for(y=-linfo->rMax, iy=0; y<=linfo->rMax; y+=linfo->delta, iy++) {
                r = sqrt(x*x + y*y);
                if(linfo->rMax<r) {
                    mrcPixelDataSet(mrc, ix, iy, iz, ave, mrcPixelMag);
                }
                mrcPixelDataGet(mrc, ix, iy, iz, &rho, mrcPixelMag, mrcPixelHowNearest);
                sumrho  += rho;
                sumrho2 += SQR(rho);
                n++;
            }
        }
    }
    ave = sumrho/n;
    sig = sqrt(sumrho2/n - ave*ave);

	switch(linfo->mode) {
		case 0: {
		    if(linfo->Inverse==0) {
		        if(sig!=0.0) {
		            for(iz=0; iz<mrc->HeaderN.z; iz++) {
		                for(ix=0; ix<mrc->HeaderN.x; ix++) {
		                    for(iy=0; iy<mrc->HeaderN.y; iy++) {
		                        mrcPixelDataGet(mrc, ix, iy, iz, &rho, mrcPixelMag, mrcPixelHowNearest);
		                        rho = (rho-ave)/sig*linfo->Sigma+linfo->Mean;
		                        mrcPixelDataSet(mrc, ix, iy, iz, rho, mrcPixelMag);
		                    }
		                }
		            }
		        }
		    } else {
		        if(sig!=0.0) {
		            for(iz=0; iz<mrc->HeaderN.z; iz++) {
		                for(ix=0; ix<mrc->HeaderN.x; ix++) {
		                    for(iy=0; iy<mrc->HeaderN.y; iy++) {
		                        mrcPixelDataGet(mrc, ix, iy, iz, &rho, mrcPixelMag, mrcPixelHowNearest);
		                        rho = (ave-rho)/sig*linfo->Sigma+linfo->Mean;
		                        mrcPixelDataSet(mrc, ix, iy, iz, rho, mrcPixelMag);
		                    }
		                }
		            }
		        }
		    }
			break;
		}
		case 1: {
		    if(linfo->Inverse==0) {
		        for(iz=0; iz<mrc->HeaderN.z; iz++) {
		        	for(ix=0; ix<mrc->HeaderN.x; ix++) {
	                    for(iy=0; iy<mrc->HeaderN.y; iy++) {
	                        mrcPixelDataGet(mrc, ix, iy, iz, &rho, mrcPixelMag, mrcPixelHowNearest);
	                        rho = (rho-aveEdge)*linfo->Sigma;
	                        mrcPixelDataSet(mrc, ix, iy, iz, rho, mrcPixelMag);
	                    }
	                }
				}
		    } else {
	            for(iz=0; iz<mrc->HeaderN.z; iz++) {
	                for(ix=0; ix<mrc->HeaderN.x; ix++) {
	                    for(iy=0; iy<mrc->HeaderN.y; iy++) {
	                        mrcPixelDataGet(mrc, ix, iy, iz, &rho, mrcPixelMag, mrcPixelHowNearest);
	                        rho = (aveEdge-rho)*linfo->Sigma;
	                        mrcPixelDataSet(mrc, ix, iy, iz, rho, mrcPixelMag);
	                    }
	                }
	            }
		    }
			break;
		}
		case 2: {
		    if(linfo->Inverse==0) {
		        for(iz=0; iz<mrc->HeaderN.z; iz++) {
		        	for(ix=0; ix<mrc->HeaderN.x; ix++) {
	                    for(iy=0; iy<mrc->HeaderN.y; iy++) {
	                        mrcPixelDataGet(mrc, ix, iy, iz, &rho, mrcPixelMag, mrcPixelHowNearest);
	                        rho = rho*linfo->Sigma;
	                        mrcPixelDataSet(mrc, ix, iy, iz, rho, mrcPixelMag);
	                    }
	                }
				}
		    } else {
	            for(iz=0; iz<mrc->HeaderN.z; iz++) {
	                for(ix=0; ix<mrc->HeaderN.x; ix++) {
	                    for(iy=0; iy<mrc->HeaderN.y; iy++) {
	                        mrcPixelDataGet(mrc, ix, iy, iz, &rho, mrcPixelMag, mrcPixelHowNearest);
	                        rho = aveEdge*linfo->Sigma;
	                        mrcPixelDataSet(mrc, ix, iy, iz, rho, mrcPixelMag);
	                    }
	                }
	            }
		    }
			break;
		}
		default: {
			fprintf(stderr, "Not supported Mode\n");
			exit(EXIT_FAILURE);
		}
	}
    mrcStatDataSet(mrc, 0);
}
