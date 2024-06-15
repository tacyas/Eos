/*
# ltlg2mrc.c  1.6
# The latest update : 05/23/97 at 17:50:28
#
#@(#) ltlg2mrc ver 1.6
#@(#) Created by 
#@(#)
#@(#) Usage : ltlg2mrc
#@(#) Attention
#@(#)
*/
static char __sccs_id[] = "@(#)ltlg2mrc ver1.6; Date:97/05/23 @(#)";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#undef DEBUG
#include "../inc/config.h"
#include "genUtil.h"
#include "Memory.h"
#include "File.h"
#include "eosString.h"
#include "ltlgData.h"
#include "mrcImage.h"

extern void lltlg2mrc(ltlgData* ltlg, mrcImage* mrc, ltlg2mrcInfo* info);
extern void configFileRead(ltlg2mrcInfo* info, FILE* fpt);

int
main(int argc, char* argv[]) 
{
    ltlgData ltlg;
    mrcImage mrc;
    ltlg2mrcInfo info;
    ltlgDataParaTypeInteger status;
	ltlgDataLLDataInfo w;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);
	
	memoryClear(&mrc, sizeof(mrc), (char)0);

	if(info.flagconfigFile) {
		configFileRead(&info, info.fptconfigFile);
	}
	if(!info.flagconfigFile && !info.flagIn) {
		usage(argv[0]);
		exit(EXIT_FAILURE);
	}

    ltlgDataReadFile(info.fptIn, &ltlg, 0, &status);

	if(info.flagLayer) {
		DEBUGPRINT1("%f\n", ltlg.llInfo[0].WT);	
    	ltlgDataWeightModifyFromFile(&ltlg, info.fptLayer, 0);
		DEBUGPRINT1("%f\n", ltlg.llInfo[0].WT);	
	}
    if(info.flagWeightOf0thLayer) {
        w.NL = 0;
        w.WT = info.WeightOf0thLayer;
		DEBUGPRINT1("%f\n", ltlg.llInfo[0].WT);	
        ltlgDataWeightModify(&ltlg, w, 1);
		DEBUGPRINT1("%f\n", info.WeightOf0thLayer);	
		DEBUGPRINT1("%f\n", ltlg.llInfo[0].WT);	
    }
	if(info.f99) {
        ltlgDataWeightOfNEqualLOnly(&ltlg);
	}
	if(!info.notInteractive) {
		ltlgDataPrint(stdout, ltlg, 3);
	}


    lltlg2mrc(&ltlg, &mrc, &info);


	if(!info.notInteractive) {
		mrcInfoPrint(stdout, &mrc, 3);
	}
	DEBUGPRINT1("%s\n", info.Out);
    mrcFileWrite(&mrc, info.Out, "in main", 0);
}

void
additionalUsage()
{
    fprintf(stderr, "Mode:\n");
    fprintf(stderr, "\n");
    fprintf(stderr, "\n");
    fprintf(stderr, "If control file is used, control file fora filename to output\n");
	fprintf(stderr, "\n");
	fprintf(stderr, "InputFileName(char[72])A])\n");
	fprintf(stderr, "Title(char[60])A])\n");
	fprintf(stderr, "Y|N(char[1])                              : No use\n");
    fprintf(stderr, "deltaX[A](if Y)||deltaY[A](if N)(F10.5)   : You need not care for deltaX or deltaY in this tool because deltaX = deltaY. You had better care for that for compatibility.\n");
	fprintf(stderr, "C[A]rMax[A](2F7.0)                        : C[A]: Spacing of the 1st layer line in real space ; rMax: Maximum of radial elements.\n");
	fprintf(stderr, "phiStart[degree](F7.0)                    : phi at Z = 0\n");
	fprintf(stderr, "zMin[A],zMax[A],deltaz[A](3F7.0)          : z-section parameters for(z=zMin; z<zMax; z+=deltaz)\n");
	fprintf(stderr, "Weight(F7.0)                              : Weight of the 0th layer line\n");
	fprintf(stderr, "NNL,WEIGHT(I2,F8.0)                       : IF(NNL==99 && NN(LL)!=NL(LL)) WT(LL) = 0.0; IF(NNL!=0 && NNL==NL(LL)) WT(LL) = WEIGHT  and Repeat until NNL == 0 or 99 or None\n");
	fprintf(stderr, "ACUT(F7.0)                                : IF(ACUT>Density[x][y]) Density[x][y]= 0.0\n");
	fprintf(stderr, "Mean,Sigma(2F7.0)                         : Mean : Mean of hrzData?; Sigma : Standard Deviation of hrzData?\n");
	fprintf(stderr, "OutputFile                                : hrz-data filename to output\n");
	fprintf(stderr, "\n");
	fprintf(stderr, "#### Attention ####\n");
	fprintf(stderr, " In using this tool, you need not keep promises about format(F7.0 etc.).\n");
	fprintf(stderr, "Instead, you need separate numbers with more space than one.\n");
	fprintf(stderr, "Usually compatible but you need care when numbers have a line with no space.\n");
								 
}
                        
void
configFileRead(ltlg2mrcInfo* info, FILE* fpt)
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
	if(!info->flagIn) {
		info->flagIn++;
		info->In =  stringGetNthWord(s, 1, " \t");
		info->flagIn++;
		info->fptIn = fileOpen(info->In, "r");
	}
	stringGetFromFile(s, "Title", fpt, stdout, mode); 
	if(!info->flagTitle) {
		info->flagTitle++;
		info->Title = stringGetNthWord(s, 1, " \t,");
		info->flagTitle++;
	}
	stringGetFromFile(s, "any", fpt, stdout, mode);  /* Skip */
	stringGetFromFile(s, "delta[A]", fpt, stdout, mode);  
	if(!info->flagdelta) {
		info->flagdelta++;
		info->delta = stringGetNthRealData(s, 1, " ,\t");
	}
	stringGetFromFile(s, "RepeatDistance rMax", fpt, stdout, mode);  
	if(!info->flagRepeatDistance) {
		info->flagRepeatDistance++;
		info->RepeatDistance = stringGetNthRealData(s, 1, " ,\t");
	}
	if(!info->flagrMax) {
		info->flagrMax++;
		info->rMax = stringGetNthRealData(s, 2, " ,\t");
	}
	stringGetFromFile(s, "phiStart[degree]", fpt, stdout, mode);  
	if(!info->flagphiStart) {
		info->flagphiStart++;
		info->phiStart = stringGetNthRealData(s, 1, " ,\t")*RADIAN;
	}
	stringGetFromFile(s, "zMin[A] zMax[A] deltaz[A] ", fpt, stdout, mode);  
	if(!info->flagzMin) {
		info->flagzMin++;
		info->zMin = stringGetNthRealData(s, 1, " ,\t");
	}
	if(!info->flagzMax) {
		info->flagzMax++;
		info->zMax = stringGetNthRealData(s, 2, " ,\t");
	}
	if(!info->flagdeltaz) {
		info->flagdeltaz++;
		info->deltaz = stringGetNthRealData(s, 3, " ,\t");
	}
	stringGetFromFile(s, "WeightOfOthLayer", fpt, stdout, mode);  
	if(!info->flagWeightOf0thLayer) {
		info->flagWeightOf0thLayer++;
		info->WeightOf0thLayer = stringGetNthRealData(s, 1, " ,\t");
	}
	while(NULL!=stringGetFromFile(s, "NL WEIGHT", fpt, stdout, mode)) {
		if(0==stringLength(s)) {
			break;
		} else {
			if(!info->flagLayer) {
				w.NL= stringGetNthIntegerData(s, 1, " \t,");
				if(99==w.NL) {
					if(!info->f99) {
						info->f99++;
					}
				} else {
					w.WT = stringGetNthRealData(s, 2, " \t,");
				}
			}
		}
	}

	stringGetFromFile(s, "ACUT", fpt, stdout, mode);  
	if(!info->flagCUT) {
		info->flagCUT++;
		info->CUT = stringGetNthRealData(s, 1, " ,\t");
	}
	stringGetFromFile(s, "Mean Sigma", fpt, stdout, mode);  
	if(!info->flagMean) {
		info->flagMean++;
		info->Mean = stringGetNthRealData(s, 1, " ,\t");
	}
	if(!info->flagSigma) {
		info->flagSigma++;
		info->Sigma = stringGetNthRealData(s, 2, " ,\t");
	}
	stringGetFromFile(s, "Mean Sigma", fpt, stdout, mode);  
	if(!info->flagOut) {
		info->Out = stringGetNthWord(s, 1, " ,\t"); 
		info->flagOut++;
		info->fptOut = fileOpen(info->Out, "w");
	}
}
/*
*
*     RHO(R) = SUM(GLIT(R).EXP(i(N*PHI-2*M_PI*L*Z/c)))
*     COMBINING GLIT (-L,-N) AND GLIT(L,N), RHO=A*COS()-B*SIN()
*
*/

void
lltlg2mrc(ltlgData* ltlg, mrcImage* mrc, ltlg2mrcInfo* info)
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

    mrc->HeaderN.x = mrc->HeaderN.y = fabs(2.0*info->rMax/info->delta + 1);
    mrc->HeaderN.z                  = fabs((info->zMax-info->zMin)/info->deltaz + 1);

    mrc->HeaderMode = mrcFloatImage;

	mrc->HeaderM.x = 1;
	mrc->HeaderM.y = 1;
	mrc->HeaderM.z = 1;

    mrc->HeaderLength.x = info->delta;
	mrc->HeaderLength.y = info->delta;
    mrc->HeaderLength.z = info->deltaz;

    mrc->HeaderAlpha = mrc->HeaderBeta = mrc->HeaderGamma = 90.0;
    mrc->HeaderMAPC = 1;
    mrc->HeaderMAPR = 2;
    mrc->HeaderMAPS = 3;
    mrcInit(mrc, NULL);

	if(!info->AntiPole) {
		xmin   = -info->rMax;
		xmax   =  info->rMax;
		xdelta =  info->delta;
		ymin   = -info->rMax;
		ymax   =  info->rMax;
		ydelta =  info->delta;
		zmin   =  info->zMin;
		zmax   =  info->zMax;
		zdelta =  info->deltaz;
	} else {
		xmin   =  info->rMax;
		xmax   = -info->rMax;
		xdelta = -info->delta;
		ymin   = -info->rMax;
		ymax   =  info->rMax;
		ydelta =  info->delta;
		zmax   =  info->zMin;
		zmin   =  info->zMax;
		zdelta = -info->deltaz;
	}
    n = 0.0;
    min = 0.0; max = 0.0;
    recz = 2*PI/info->RepeatDistance;
    for(z=zmin, iz=0; iz<mrc->HeaderN.z; z+=zdelta, iz++) {
        fprintf(stderr, "z: %10.2f [A] ", z);
        for(x=xmin, ix=0; ix<mrc->HeaderN.x; x+=xdelta, ix++) {
        	for(y=ymin, iy=0; iy<mrc->HeaderN.y; y+=ydelta, iy++) {
                rho = 0.0;
                r = sqrt(x*x + y*y);
                rr = r/ltlg->r.d;
                ir = (ltlgDataParaTypeInteger)rr;
                rbit = rr - ir;
                rbar = 1.0 - rbit;
                if(info->rMax < r || ltlg->r.Max < r ) {
                    rho = 0.0;
                } else if (ltlg->r.n - 1 < ir + 1) {
                    if(r==0.0) {
                        ang = 0.0;
                    } else {
                        ang = atan2(y, x) + PI/2 + info->phiStart;
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
                        ang = atan2(y, x) + PI/2 + info->phiStart;
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
    }
    if(n!=(mrc->HeaderN.x*mrc->HeaderN.y*mrc->HeaderN.z)) {
        fprintf(stderr, "Different Number %d != %f\n", (int)(mrc->HeaderN.x*mrc->HeaderN.y*mrc->HeaderN.z), n);
	}
    sumrho = sumrho2 = n = 0.0;
    for(z=info->zMin, iz=0; z<=info->zMax; z+=info->deltaz, iz++) {
        for(x=-info->rMax, ix=0; x<=info->rMax; x+=info->delta, ix++) {
            for(y=-info->rMax, iy=0; y<=info->rMax; y+=info->delta, iy++) {
                r = sqrt(x*x + y*y);
                if(info->rMax-1<r && r<=info->rMax) {
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
    for(z=info->zMin, iz=0; z<=info->zMax; z+=info->deltaz, iz++) {
        for(x=-info->rMax, ix=0; x<=info->rMax; x+=info->delta, ix++) {
            for(y=-info->rMax, iy=0; y<=info->rMax; y+=info->delta, iy++) {
                r = sqrt(x*x + y*y);
                if(info->rMax<r) {
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

	switch(info->mode) {
		case 0: {
		    if(info->Inverse==0) {
		        if(sig!=0.0) {
		            for(iz=0; iz<mrc->HeaderN.z; iz++) {
		                for(ix=0; ix<mrc->HeaderN.x; ix++) {
		                    for(iy=0; iy<mrc->HeaderN.y; iy++) {
		                        mrcPixelDataGet(mrc, ix, iy, iz, &rho, mrcPixelMag, mrcPixelHowNearest);
		                        rho = (rho-ave)/sig*info->Sigma+info->Mean;
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
		                        rho = (ave-rho)/sig*info->Sigma+info->Mean;
		                        mrcPixelDataSet(mrc, ix, iy, iz, rho, mrcPixelMag);
		                    }
		                }
		            }
		        }
		    }
			break;
		}
		case 1: {
		    if(info->Inverse==0) {
		        for(iz=0; iz<mrc->HeaderN.z; iz++) {
		        	for(ix=0; ix<mrc->HeaderN.x; ix++) {
	                    for(iy=0; iy<mrc->HeaderN.y; iy++) {
	                        mrcPixelDataGet(mrc, ix, iy, iz, &rho, mrcPixelMag, mrcPixelHowNearest);
	                        rho = (rho-aveEdge)*info->Sigma;
	                        mrcPixelDataSet(mrc, ix, iy, iz, rho, mrcPixelMag);
	                    }
	                }
				}
		    } else {
	            for(iz=0; iz<mrc->HeaderN.z; iz++) {
	                for(ix=0; ix<mrc->HeaderN.x; ix++) {
	                    for(iy=0; iy<mrc->HeaderN.y; iy++) {
	                        mrcPixelDataGet(mrc, ix, iy, iz, &rho, mrcPixelMag, mrcPixelHowNearest);
	                        rho = (aveEdge-rho)*info->Sigma;
	                        mrcPixelDataSet(mrc, ix, iy, iz, rho, mrcPixelMag);
	                    }
	                }
	            }
		    }
			break;
		}
		case 2: {
		    if(info->Inverse==0) {
		        for(iz=0; iz<mrc->HeaderN.z; iz++) {
		        	for(ix=0; ix<mrc->HeaderN.x; ix++) {
	                    for(iy=0; iy<mrc->HeaderN.y; iy++) {
	                        mrcPixelDataGet(mrc, ix, iy, iz, &rho, mrcPixelMag, mrcPixelHowNearest);
	                        rho = rho*info->Sigma;
	                        mrcPixelDataSet(mrc, ix, iy, iz, rho, mrcPixelMag);
	                    }
	                }
				}
		    } else {
	            for(iz=0; iz<mrc->HeaderN.z; iz++) {
	                for(ix=0; ix<mrc->HeaderN.x; ix++) {
	                    for(iy=0; iy<mrc->HeaderN.y; iy++) {
	                        mrcPixelDataGet(mrc, ix, iy, iz, &rho, mrcPixelMag, mrcPixelHowNearest);
	                        rho = aveEdge*info->Sigma;
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

