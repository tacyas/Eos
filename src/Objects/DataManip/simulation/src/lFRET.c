/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% lFRET ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : lFRET 
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%lFRET ver%I%; Date:%D% %Z%";
#include <stdlib.h>
#define DEBUG
#include "genUtil.h"
#include "eosString.h"
#include "Memory.h"
#include "./lFRET.h"

extern inline double lFRETWeightCalc(double distance, double length, double variance, energyTransferPointMode mode);

extern void lenergyTransferModelExpectedFRETOutput(FILE* fpt, energyTransferData* dst, mrcImage* unfix,
    lenergyTransferModelCheckInfo linfo, int mode);

extern void lenergyTransferModelExpectedFRETSD(FILE* fpt, energyTransferData* dst, mrcImage* unfix,
    lenergyTransferModelCheckInfo linfo, int mode);

extern void energyTransferDataWriteFix(char* head, char* subhead, energyTransferData* dst, int i, FILE* fpt, int lmode);

extern void energyTransferDataWriteUnfix(char* head, char* subhead, energyTransferData* dst, int i, FILE* fpt, int lmode);

extern void energyTransferDataWriteConnect(char* head, energyTransferData* dst, int i, FILE* fpt, int lmode);

extern void energyTransferDataWrite0(char* head, energyTransferData* dst, FILE* fpt, int lmode);

void
lenergyTransferModelCheck(energyTransferData* src, mrcImage* unfix, mrcImage* fix,
    lenergyTransferModelCheckInfo linfo, int mode)
{
    int i, j, k;
    mrcImageParaTypeReal x, y, z;
    mrcImageParaTypeReal x0, y0, z0;
    mrcImageParaTypeInteger dx, dy, dz;
    mrcImageParaTypeInteger rx, ry, rz;
    mrcImageParaTypeInteger rdx, rdy, rdz;
    mrcImageParaTypeReal rdx0, rdy0, rdz0;
    mrcImageParaTypeReal realx, realy, realz;
    mrcImageParaTypeReal realx0, realy0, realz0;
    mrcImageParaTypeReal xk, yk, zk;
    mrcImageParaTypeReal realxk, realyk, realzk;
    mrcImageParaTypeReal xk0, yk0, zk0;
    mrcImageParaTypeReal realxk0, realyk0, realzk0;
    double data, data1, data2, data3, data4, data5, data6, data0, datak0, weight, variance, tmpdata;
    double distance;
    double In;
    mrcImageInformation info;

    DEBUGPRINT("lenergyTransferModelCheck Start-----\n");
    /* 
		Fix Value Initialize 
			linfo.iter == 0: 
				0<= fix, fix = 1;
			    fix<0,   fix = fix; if negative, the area must be rejected.	
			linfo.iter > 0:
				0<unfix; fix = unfix;
				fix<0,   fix = fix;
				unfix == 0 && 0<=fix, fix=averaged;
	*/
    for(i=0; i<src->numUnfix; i++) {
        for(x=0; x<fix[i].HeaderN.x; x++) {
        for(y=0; y<fix[i].HeaderN.y; y++) {
        for(z=0; z<fix[i].HeaderN.z; z++) {
            if(linfo.iter==0) { /* First iteration */
                mrcPixelDataGet(&(fix[i]), x, y, z, &data, mrcPixelRePart, mrcPixelHowNearest);
                if(0<=data) {
                    data = 1.0;
                }
                mrcPixelDataSet(&(fix[i]), x, y, z,  data, mrcPixelRePart);
            } else if(0<linfo.iter) { /* After the first iteration */
                mrcPixelDataGet(&(unfix[i]), x, y, z, &data,  mrcPixelRePart, mrcPixelHowNearest);
                mrcPixelDataGet(&(  fix[i]), x, y, z, &data0, mrcPixelRePart, mrcPixelHowNearest);
                if(0<data) {         /* in current positive region : */
                    data = data;
                } else if(data0<0) { /* in negative region : Reject Region */
                    data = data0;
                } else {             /* in special region : Peripheral region */
									 /* data <= 0 || 0<=data0 */
									 /* (Probability is zero)   ||   (Not Reject region) */
                    mrcPixelDataGet(&(unfix[i]), x-1, y, z, &data1, mrcPixelRePart, mrcPixelHowNearest);
                    mrcPixelDataGet(&(unfix[i]), x+1, y, z, &data2, mrcPixelRePart, mrcPixelHowNearest);
                    mrcPixelDataGet(&(unfix[i]), x, y-1, z, &data3, mrcPixelRePart, mrcPixelHowNearest);
                    mrcPixelDataGet(&(unfix[i]), x, y+1, z, &data4, mrcPixelRePart, mrcPixelHowNearest);
                    mrcPixelDataGet(&(unfix[i]), x, y, z-1, &data5, mrcPixelRePart, mrcPixelHowNearest);
                    mrcPixelDataGet(&(unfix[i]), x, y, z+1, &data6, mrcPixelRePart, mrcPixelHowNearest);
                    if(0<data1||0<data2||0<data3||0<data4||0<data5||0<data6) {
                        data = 0;
                        if(0<data1) {
                            data += data1;
                        }
                        if(0<data2) {
                            data += data2;
                        }
                        if(0<data3) {
                            data += data3;
                        }
                        if(0<data4) {
                            data += data4;
                        }
                        if(0<data5) {
                            data += data5;
                        }
                        if(0<data6) {
                            data += data6;
                        }
                        data /= 6;
                    } else {
                        data = 0.0;
                    }
                }
                mrcPixelDataSet(&(fix[i]), x, y, z,  data, mrcPixelRePart);
            } else {
                fprintf(stderr, "Something wrong: iteration %d is negative\n", linfo.iter);
            }
        }
        }
        }
    }
    
    DEBUGPRINT("Using Fixed Point\n");
	/*
		Fixed point(j) <-> Unfixed Point(k)
			i: Connection No. (max: src->numConnect)
			j: Fixed point   No. (max: numFix) 
			k: Unfixed point No. (max: numUnfix) 
	*/
    for(i=0; i<src->numConnect; i++) {
        for(j=0; j<src->numFix; j++) {
            DEBUGPRINT1("CONNECTION: %d\n", i);
            k = -1;
            if(src->connect[i].nID  == src->fix[j].nID
            && src->numFix <= src->connect[i].nID2) {        /* ID: Fixed,    ID2: Unfixed: */
                k = src->connect[i].nID2 - src->numFix;         
            } else if(src->connect[i].nID2 == src->fix[j].nID
                   && src->numFix <= src->connect[i].nID ) { /* ID: Unfixed, ID2: Fixed */
                k = src->connect[i].nID  - src->numFix;
            }
            if(0<=k && k<src->numUnfix) {                    /* j: Fixed Point, k: Unfixed Point */

                DEBUGPRINT3("CONNECTION: %d Fixed ID %d <-> Unfixed %d\n", i, j, k);
                fprintf(stdout, "CONNECTION: %d Fixed ID %d <-> Unfixed %d\n", i, j, k);
                rdx = floor(src->unfix[k].radius/fix[k].HeaderLength.x); 
                rdy = floor(src->unfix[k].radius/fix[k].HeaderLength.y); 
                rdz = floor(src->unfix[k].radius/fix[k].HeaderLength.z); 
                variance = SQR(src->connect[i].rootB)
                         + SQR(src->fix[j].rootB)
                         + SQR(src->unfix[k].rootB);

                if(0<=linfo.iter) {
                    for(x0=0; x0<fix[k].HeaderN.x; x0++) {        /* k: Unfixed Point */
                        fprintf(stdout, "## iter: %02d x: %10.2f\n", linfo.iter, x0);
                        realx0 = (fix[k].HeaderStartN.x + x0)*fix[k].HeaderLength.x;
                    for(y0=0; y0<fix[k].HeaderN.y; y0++) {
                        realy0 = (fix[k].HeaderStartN.y + y0)*fix[k].HeaderLength.y;
                    for(z0=0; z0<fix[k].HeaderN.z; z0++) {
                        realz0 = (fix[k].HeaderStartN.z + z0)*fix[k].HeaderLength.z;
					
                        /* Unfixed Point (realx, realy, realz) */
                        /* Fixed Point    src->fix[j].(x, y, z) */
                        /* data0 at (x0, y0, z0) in fix[k] */
                        mrcPixelDataGet(&(fix[k]), x0, y0, z0,
                                    &data0, mrcPixelRePart, mrcPixelHowNearest);

                        if(0<=data0) {
                            /* Fluophor reject space : No protein */
                            In = 1.0;
                            for(rx=x0-rdx; rx<=x0+rdx; rx++) {
                            for(ry=y0-rdy; ry<=y0+rdy; ry++) {
                            for(rz=z0-rdz; rz<=z0+rdz; rz++) {
								if(0<rdx) {
									rdx0 = SQR((rx-x0)/rdx);
								} else if(0==rdx) {
									rdx0 = 0;
								} else {
									fprintf(stderr, "Something Wrong!");
									exit(EXIT_FAILURE);
								}
								if(0<rdy) {
									rdy0 = SQR((ry-y0)/rdy);
								} else if(0==rdy) {
									rdy0 = 0;
								} else {
									fprintf(stderr, "Something Wrong!");
									exit(EXIT_FAILURE);
								}
								if(0<rdz) {
									rdz0 = SQR((rz-z0)/rdz);
								} else if(0==rdz) {
									rdz0 = 0;
								} else {
									fprintf(stderr, "Something Wrong!");
									exit(EXIT_FAILURE);
								}
                                if(rdx0+rdy0+rdz0<=1) {
                                    mrcPixelDataGet(&(fix[k]), rx, ry, rz,
                                        &data1, mrcPixelRePart, mrcPixelHowNearest);
                                    if(data1<0) {
                                        In = 0.0;
                                        break;
                                    }
                                }
                            }
                                if(In==0.0) {
                                    break;
                                }
                            }
                                if(In==0.0) {
                                    break;
                                }
                            }
							if(In==0.0) { /* Rejection  Area */
								data0 = 0.0;
							} else {
                            	distance = sqrt(SQR(realx0 - src->fix[j].x)
                               	          	  + SQR(realy0 - src->fix[j].y)
                                          	  + SQR(realz0 - src->fix[j].z));
								weight = lFRETWeightCalc(distance, src->connect[i].length, variance, src->connect[i].mode);
                            	if(weight<linfo.neglect) {
                                	weight = 0.0;
                            	}
                            	data0 *= weight;
							}
                            mrcPixelDataSet(&(fix[k]), x0, y0, z0, data0, mrcPixelRePart);
                        }
                    }
                    }
                    }
                } else {
                    fprintf(stderr, "Something wrong: iter is negative.\n");
                }
                break;
            }
        }
    }

    /* For speed up : neglect 1/100*max */
    for(i=0; i<src->numUnfix; i++) {
        info.max = lmrcImageMaxDataGet(&(fix[i]), 0);
		if(info.max<=0) {
			fprintf(stderr, "!!! Attention: Probability is zero : unfix %d\n", i);
			exit(EXIT_FAILURE);
		}
        for(x=0; x<fix[i].HeaderN.x; x++) {
        for(y=0; y<fix[i].HeaderN.y; y++) {
        for(z=0; z<fix[i].HeaderN.z; z++) {
            mrcPixelDataGet(&(fix[i]), x, y, z, &data, mrcPixelRePart, mrcPixelHowNearest);
            if(0 < data
             &&    data < 1e-2*info.max) {
                data = 0.0;
            }
            mrcPixelDataSet(&(fix[i]), x, y, z, data, mrcPixelRePart);
        }
        }
        }
    }

    DEBUGPRINT("Using Only Unfixed Point\n");
    /* 
		Clearing of unfix 
		All values are zero.
	*/
    for(i=0; i<src->numUnfix; i++) {
        for(x=0; x<unfix[i].HeaderN.x; x++) {
        for(y=0; y<unfix[i].HeaderN.y; y++) {
        for(z=0; z<unfix[i].HeaderN.z; z++) {
            mrcPixelDataSet(&(unfix[i]), x, y, z, 0.0, mrcPixelRePart);
        }
        }
        }
    } 

    /* 
		No Unfix-unfix connection check 
	*/
    for(j=0; j<src->numUnfix; j++) {
        k = -1;
        for(i=0; i<src->numConnect; i++) {
            if(       src->connect[i].nID  == src->unfix[j].nID
             &&       src->numFix          <= src->connect[i].nID2) {  /* ID: Unfixed, ID2: Unfixed */
                k = src->connect[i].nID2 - src->numFix;

            } else if(src->connect[i].nID2 == src->unfix[j].nID
             &&       src->numFix          <= src->connect[i].nID) {   /* ID: Unfixed, ID2: Unfixed */
                k = src->connect[i].nID  - src->numFix;
            }
        }
        if(-1==k) {
            DEBUGPRINT1("No unfix-unfix data related to %d\n", j);
            for(x =0; x <unfix[j].HeaderN.x; x++) {
            for(y =0; y <unfix[j].HeaderN.y; y++) {  
            for(z =0; z <unfix[j].HeaderN.z; z++) {
                mrcPixelDataGet(&(  fix[j]), x,  y,  z,  &data, mrcPixelRePart, mrcPixelHowNearest);
                if(0<=data) {
                    mrcPixelDataSet(&(unfix[j]), x,  y,  z,   data, mrcPixelRePart);
                } else {
                    mrcPixelDataSet(&(unfix[j]), x,  y,  z,   0.0, mrcPixelRePart);
                }
            }
            }
            }
        }
    }

    DEBUGPRINT("UNFIX-UNFIX CONNECTION\n");
    for(i=0; i<src->numConnect; i++) {
        for(j=0; j<src->numUnfix; j++) {
            DEBUGPRINT2("CONNECTION: %d : unfix %d\n", i, j);
            k = -1; 
            if(       src->connect[i].nID  == src->unfix[j].nID
             &&       src->numFix          <= src->connect[i].nID2) {  /* ID: Unfixed, ID2: Unfixed */
                k = src->connect[i].nID2 - src->numFix;
                if(src->unfix[k].nID!=src->connect[i].nID2) {
                    fprintf(stderr, "Something wrong: ID different\n");
                } else {
                    DEBUGPRINT("OK ID\n"); 
                }  
            } else if(src->connect[i].nID2 == src->unfix[j].nID
                   && src->numFix          <= src->connect[i].nID) {   /* ID: Unfixed, ID2: Unfixed */
                k = src->connect[i].nID  - src->numFix;
                if(src->unfix[k].nID!=src->connect[i].nID) {
                    fprintf(stderr, "Something wrong: ID different\n");
                } else {
                    DEBUGPRINT("OK ID\n");
                }
            }
            if(0<=k && k<src->numUnfix
             &&0<=j && j<src->numUnfix) { /* Unfixed: point: j, k */
                fprintf(stdout, "CONNECTION: %d : unfix %d <-> unfix %d\n", i, j, k);
                variance =   SQR(src->connect[i].rootB)
                            +SQR(src->unfix[j].rootB)
                            +SQR(src->unfix[k].rootB);
                if(0==linfo.iter) {
                    dx = MAX(1, linfo.sdx/fix[k].HeaderLength.x);
                    dy = MAX(1, linfo.sdy/fix[k].HeaderLength.y);
                    dz = MAX(1, linfo.sdz/fix[k].HeaderLength.z);
                    for(x =0; x <unfix[j].HeaderN.x; x+=dx) {
                        fprintf(stdout, "x: %f\n", x);
                        realx  = (unfix[j].HeaderStartN.x + x )*unfix[j].HeaderLength.x;
                    for(y =0; y <unfix[j].HeaderN.y; y+=dy) {
                        realy  = (unfix[j].HeaderStartN.y + y )*unfix[j].HeaderLength.y;
                    for(z =0; z <unfix[j].HeaderN.z; z+=dz) {
                        /* data1 at (x, y, z) in fix[j] */
                        mrcPixelDataGet(&(  fix[j]), x,  y,  z,  &data1, mrcPixelRePart, mrcPixelHowNearest);

                        if(0<data1) {
                            realz  = (unfix[j].HeaderStartN.z + z )*unfix[j].HeaderLength.z;

                            for(xk=0; xk<unfix[k].HeaderN.x; xk+=dx) {
                                realxk = (unfix[k].HeaderStartN.x + xk)*unfix[k].HeaderLength.x;
                            for(yk=0; yk<unfix[k].HeaderN.y; yk+=dy) {
                                realyk = (unfix[k].HeaderStartN.y + yk)*unfix[k].HeaderLength.y;
                            for(zk=0; zk<unfix[k].HeaderN.z; zk+=dz) {
                                /* data2 at (xk, yk, zk) in fix[k] */
                                mrcPixelDataGet(&(  fix[k]), xk, yk, zk, &data2, mrcPixelRePart, mrcPixelHowNearest);

                                if(0<data2) {
                                    realzk = (unfix[k].HeaderStartN.z + zk)*unfix[k].HeaderLength.z;

                                    distance = sqrt( SQR(realx - realxk)
                                                    +SQR(realy - realyk)
                                                    +SQR(realz - realzk));
                                    weight   = lFRETWeightCalc(distance, src->connect[i].length, variance, src->connect[i].mode);

                                    if(linfo.neglect < weight) {
                                        /* Fine Search */
                                        for(x0=x-dx/2; x0<x+dx-dx/2; x0++) {
                                            realx0 = (unfix[k].HeaderStartN.x + x0)*unfix[k].HeaderLength.x;
                                        for(y0=y-dy/2; y0<y+dy-dy/2; y0++) {
                                            realy0 = (unfix[k].HeaderStartN.y + y0)*unfix[k].HeaderLength.y;
                                        for(z0=z-dz/2; z0<z+dz-dz/2; z0++) {
                                            /* data1 at (x0, y0, z0) in fix[j] */
                                            mrcPixelDataGet(&(  fix[j]), x0,  y0,  z0,  &data1, mrcPixelRePart, mrcPixelHowNearest);

                                            if(0<data1) {
                                                realz0 = (unfix[k].HeaderStartN.z + z0)*unfix[k].HeaderLength.z;
                                                /* data0 at (x0, y0, z0) in unfix[j] */
                                                mrcPixelDataGet(&(unfix[j]), x0,  y0,  z0,  &data0, mrcPixelRePart, mrcPixelHowNearest);

                                                for(xk0=xk-dx/2; xk0<xk+dx-dx/2; xk0++) {
                                                    realxk0 = (unfix[k].HeaderStartN.x + xk0)*unfix[k].HeaderLength.x;
                                                for(yk0=yk-dy/2; yk0<yk+dy-dy/2; yk0++) {
                                                    realyk0 = (unfix[k].HeaderStartN.y + yk0)*unfix[k].HeaderLength.y;
                                                for(zk0=zk-dz/2; zk0<zk+dz-dz/2; zk0++) {
                                                    /* data2 at (xk0, yk0, zk0) in fix[k] */
                                                    mrcPixelDataGet(&(  fix[k]), xk0, yk0, zk0, &data2, mrcPixelRePart, mrcPixelHowNearest);
                                                    if(0 < data2) {
                                                        realzk0 = (unfix[k].HeaderStartN.z + zk0)*unfix[k].HeaderLength.z;

                                                        /* data0 at (xk0, yk0, zk0) in unfix[k] */
                                                        mrcPixelDataGet(&(unfix[k]), xk0,  yk0,  zk0,  &datak0, mrcPixelRePart, mrcPixelHowNearest);

                                                        distance = sqrt( SQR(realx0 - realxk0)
                                                                        +SQR(realy0 - realyk0)
                                                                        +SQR(realz0 - realzk0));
                                                        weight   = lFRETWeightCalc(distance, src->connect[i].length, variance, src->connect[i].mode);

                                                        if(linfo.neglect<weight) {  
                                                            tmpdata = weight*data1*data2;
                                                            data0  = data0  + tmpdata;
                                                            datak0 = datak0 + tmpdata;
                                                        }
                                                        mrcPixelDataSet(&(unfix[k]), xk0,  yk0,  zk0,  datak0, mrcPixelRePart);
                                                    } else { /* data2 */
                                                             /* No added */
                                                    }
                                                }
                                                }
                                                }
                                                mrcPixelDataSet(&(unfix[j]), x0,  y0,  z0,   data0, mrcPixelRePart);
                                            } else { /* data1 */
                                                     /* No added */
                                            }
                                        }
                                        }
                                        } 
                                    }
                                } else { /* data2 < neglect */
                                    /* No added */
                                }
                            }
                            } 
                            }
                        } else { /* data1 < neglect */
                        /* No added */
                        }
                    }
                    }
                    }
                } else if(0<linfo.iter) {
                    for(x0=0; x0<unfix[j].HeaderN.x; x0++) {
                        DEBUGPRINT2("iter %d x: %f\n", linfo.iter, x0);
                        realx0 = (unfix[j].HeaderStartN.x + x0)*unfix[j].HeaderLength.x;
                    for(y0=0; y0<unfix[j].HeaderN.y; y0++) {
                        realy0 = (unfix[j].HeaderStartN.y + y0)*unfix[j].HeaderLength.y;
                    for(z0=0; z0<unfix[j].HeaderN.z; z0++) {
                        /* data1 at (x0, y0, z0) in fix[j] */
                        mrcPixelDataGet(&(  fix[j]), x0,  y0,  z0,  &data1, mrcPixelRePart, mrcPixelHowNearest);

                        if(0<data1) {
                            realz0 = (unfix[j].HeaderStartN.z + z0)*unfix[j].HeaderLength.z;
                            /* data0 at (x0, y0, z0) in unfix[j] */
                            mrcPixelDataGet(&(unfix[j]), x0,  y0,  z0,  &data0, mrcPixelRePart, mrcPixelHowNearest);

                            for(xk0=0; xk0<unfix[k].HeaderN.x; xk0++) {
                                realxk0 = (unfix[k].HeaderStartN.x + xk0)*unfix[k].HeaderLength.x;
                            for(yk0=0; yk0<unfix[k].HeaderN.y; yk0++) {
                                realyk0 = (unfix[k].HeaderStartN.y + yk0)*unfix[k].HeaderLength.y;
                            for(zk0=0; zk0<unfix[k].HeaderN.z; zk0++) {
                                /* data2 at (x0, y0, z0) n fix[k] */
                                mrcPixelDataGet(&(  fix[k]), xk0,  yk0,  zk0,  &data2, mrcPixelRePart, mrcPixelHowNearest);

                                if(0<data2) {
                                    realzk0 = (unfix[k].HeaderStartN.z + zk0)*unfix[k].HeaderLength.z;
                                    /* datak0 at (x0, y0, z0) n unfix[k] */
                                    mrcPixelDataGet(&(unfix[k]), xk0,  yk0,  zk0,  &datak0, mrcPixelRePart, mrcPixelHowNearest);

                                    distance = sqrt( SQR(realx0 - realxk0)
                                                    +SQR(realy0 - realyk0)
                                                    +SQR(realz0 - realzk0));
           			                weight   = lFRETWeightCalc(distance, src->connect[i].length, variance, src->connect[i].mode);

									if(linfo.neglect < weight) { 
										tmpdata = weight*data1*data2;
                                       	data0  = data0  + tmpdata; 
										datak0 = datak0 + tmpdata;
                                    }
                                    mrcPixelDataSet(&(unfix[k]), xk0,  yk0,  zk0,  datak0, mrcPixelRePart);
                                } else {
                                    /* No added */
                                }
                            }
                            }
                            }
                            mrcPixelDataSet(&(unfix[j]), x0,  y0,  z0,  data0, mrcPixelRePart);
                        } else {
                            /* No added */
                        }
                    }
                    }
                    }
                } else {
                    fprintf(stderr, "Something wrong : iteration is negative\n");
                }
                break; /* If i-th connection is between j-th unfixed and k-th unfixed */
            } /* k, j */
        } /* j: Unfixed ID */
    } /* i : Connection */
    DEBUGPRINT("---- lenergyTransferModelCheck End\n");
}

void
lenergyTransferModelExpectedFRET(FILE* fpt, energyTransferData* dst, mrcImage* unfix,
    lenergyTransferModelCheckInfo linfo, int mode)
{
    int i, j, k, flagJ, flagK;
    mrcImageInformation info;
	double rms2;
	int num;
	char s[1024];

    DEBUGPRINT("lenergyTransferModelExpectedFRET Start -----\n");
    /* Max Probability */
    for(i=0; i<dst->numUnfix; i++) {
        info.mode = meanOfAll;
        lmrcImageInformation(&info, &(unfix[i])); /* Get Max */
        dst->unfix[i].probability = info.max;
        dst->unfix[i].x = (info.maxCoord.x + unfix[i].HeaderStartN.x)*unfix[i].HeaderLength.x;
        dst->unfix[i].y = (info.maxCoord.y + unfix[i].HeaderStartN.y)*unfix[i].HeaderLength.y;
        dst->unfix[i].z = (info.maxCoord.z + unfix[i].HeaderStartN.z)*unfix[i].HeaderLength.z;
        LOGPRINT6(fpt, "ITER", "UNFIX", "MaxProbability: %10s %5d %10.2f %10.2f %10.2f : prob %15.6e",
            dst->unfix[i].ID, dst->unfix[i].nID, dst->unfix[i].x, dst->unfix[i].y, dst->unfix[i].z, dst->unfix[i].probability);
    }

    /* Expected FRET : Using Max Probability*/
    dst->rms = 0;
	num = 0;
    for(i=0; i<dst->numConnect; i++) {
        if(dst->numFix <= dst->connect[i].nID) { /* Unfix : j */
            j =  dst->connect[i].nID - dst->numFix;
            flagJ = 1;
        } else {                                 /* Fix   : j */
            j =  dst->connect[i].nID;
            flagJ = 0;
        }

        if(dst->numFix <= dst->connect[i].nID2) { /* Unfix : k*/
            k =  dst->connect[i].nID2 - dst->numFix;
            flagK = 1;
        } else {                                 /* Fix    : k*/
            k =  dst->connect[i].nID2;
            flagK = 0;
        }

        switch(flagJ) {
            case 0: {
                switch(flagK) {
                    case 0: { /* FixJ <-> FixK */
                        fprintf(stderr, "Something wrong\n");
                        break;
                    }
                    case 1: { /* FixJ <-> unFixK */
                        dst->connect[i].estimatedLength =
                            sqrt(SQR(dst->fix[j].x - dst->unfix[k].x)
                                +SQR(dst->fix[j].y - dst->unfix[k].y)
                                +SQR(dst->fix[j].z - dst->unfix[k].z));
                        break;
                    }
                    default: {
                        fprintf(stderr, "Not supported\n");
                        break;
                    }
                }
                break;
            }
            case 1: {
                switch(flagK) { /* unFixJ <-> FixK */
                    case 0: {
                        dst->connect[i].estimatedLength =
                            sqrt(SQR(dst->unfix[j].x - dst->fix[k].x)
                                +SQR(dst->unfix[j].y - dst->fix[k].y)
                                +SQR(dst->unfix[j].z - dst->fix[k].z));
                        break;
                    }
                    case 1: { /* unFixJ <-> unFixK */
                        dst->connect[i].estimatedLength =
                            sqrt(SQR(dst->unfix[j].x - dst->unfix[k].x)
                                +SQR(dst->unfix[j].y - dst->unfix[k].y)
                                +SQR(dst->unfix[j].z - dst->unfix[k].z));
                        break;
                    }
                    default: {
                        fprintf(stderr, "Not supported\n");
                        break;
                    }
                }
                break;
            }
            default: {
                fprintf(stderr, "Not supported\n");
                break;
            }
        }
		sprintf(s, "ITER %02d", linfo.iter);
		energyTransferDataWriteConnect(s, dst, i, fpt, 2);
		if(dst->connect[i].mode == energyTransferPointModeConnect) {
        	rms2      = SQR(dst->connect[i].length - dst->connect[i].estimatedLength);
        	dst->rms += rms2;
			num++;
		}
    }
    dst->rms = sqrt(dst->rms/num);
	DEBUGPRINT2("dst->rms: %g n=%d\n", dst->rms, num);
	if((mode&0x1)==0x1) {
		lenergyTransferModelExpectedFRETSD(fpt, dst, unfix, linfo, mode);
	}
	lenergyTransferModelExpectedFRETOutput(fpt, dst, unfix, linfo, mode); 
}

void
lenergyTransferModelExpectedFRET2(FILE* fpt, energyTransferData* dst, mrcImage* unfix,
    lenergyTransferModelCheckInfo linfo, int mode)
{
    int i, j, k, flagJ, flagK;
	mrcImageParaTypeReal x, y, z;
	mrcImageParaTypeReal x1, y1, z1;
	double rmsRootB, rms2;
	char s[1024];
	int num;

    DEBUGPRINT("lenergyTransferModelExpectedFRET2 Start -----\n");
    /* Expected FRET-1 : Using Max Probability*/
    dst->rms = 0;
	rmsRootB = 0;
	num = 0;
    for(i=0; i<dst->numConnect; i++) {
        if(dst->numFix <= dst->connect[i].nID) { /* Unfix : j */
            j =  dst->connect[i].nID - dst->numFix;
            flagJ = 1;
        } else {                                 /* Fix   : j */
            j =  dst->connect[i].nID;
            flagJ = 0;
        }

        if(dst->numFix <= dst->connect[i].nID2) { /* Unfix : k*/
            k =  dst->connect[i].nID2 - dst->numFix;
            flagK = 1;
        } else {                                 /* Fix    : k*/
            k =  dst->connect[i].nID2;
            flagK = 0;
        }

        switch(flagJ) {
            case 0: { /* J: Fixed Point */ 
                switch(flagK) {
                    case 0: { /* K: Fixed Point */
                        fprintf(stderr, "Something wrong\n");
                        break;
                    }
                    case 1: { /* K: Unfixed Point */
						/* Fixed(j) - Unfixed(k) */
						double weight = 0.0;
						double length = 0.0; 
						double data;
						for(x=0; x<unfix[k].HeaderN.x; x++) {
						for(y=0; y<unfix[k].HeaderN.y; y++) {
						for(z=0; z<unfix[k].HeaderN.z; z++) {
							mrcPixelDataGet(&(unfix[k]), x, y, z, &data, mrcPixelRePart, mrcPixelHowNearest);	
							weight += data; 
							length += data*sqrt(
								 SQR(dst->fix[j].x - (x+unfix[k].HeaderStartN.x)*unfix[k].HeaderLength.x)
                                +SQR(dst->fix[j].y - (y+unfix[k].HeaderStartN.y)*unfix[k].HeaderLength.y)
                                +SQR(dst->fix[j].z - (z+unfix[k].HeaderStartN.z)*unfix[k].HeaderLength.z));
						}
						}
						}
                        dst->connect[i].estimatedLength = length/weight;
                        break;
                    }
                    default: {
                        fprintf(stderr, "Not supported\n");
                        break;
                    }
                }
                break;
            }
            case 1: { /* J: Unfixed Point */
                switch(flagK) { 
                    case 0: { /* K: Fixed Point */
						/* Fixed(k) - Unfixed(j) */
						double weight = 0.0;
						double length = 0.0; 
						double data;
						for(x=0; x<unfix[j].HeaderN.x; x++) {
						for(y=0; y<unfix[j].HeaderN.y; y++) {
						for(z=0; z<unfix[j].HeaderN.z; z++) {
							mrcPixelDataGet(&(unfix[j]), x, y, z, &data, mrcPixelRePart, mrcPixelHowNearest);	
							weight += data; 
							length += data*sqrt(
								 SQR(dst->fix[k].x - (x+unfix[j].HeaderStartN.x)*unfix[j].HeaderLength.x)
                                +SQR(dst->fix[k].y - (y+unfix[j].HeaderStartN.y)*unfix[j].HeaderLength.y)
                                +SQR(dst->fix[k].z - (z+unfix[j].HeaderStartN.z)*unfix[j].HeaderLength.z));
						}
						}
						}
                        dst->connect[i].estimatedLength = length/weight;
                        break;
                    }
                    case 1: { /* K: Unfixed Point */
						/* Unfixed(k) - Unfixed(j) */
						double weight = 0.0;
						double length = 0.0; 
						double data, data1, l;

						for(x=0; x<unfix[j].HeaderN.x; x++) {
						for(y=0; y<unfix[j].HeaderN.y; y++) {
						for(z=0; z<unfix[j].HeaderN.z; z++) {
							mrcPixelDataGet(&(unfix[j]), x, y, z, &data, mrcPixelRePart, mrcPixelHowNearest);	
							if(linfo.neglect<data) { 
								for(x1=0; x1<unfix[k].HeaderN.x; x1++) {
								for(y1=0; y1<unfix[k].HeaderN.y; y1++) {
								for(z1=0; z1<unfix[k].HeaderN.z; z1++) {
									mrcPixelDataGet(&(unfix[k]), x1, y1, z1, &data1, mrcPixelRePart, mrcPixelHowNearest);	
									if(linfo.neglect<data1) { 
										weight += data*data1; 
										l = sqrt(SQR((x+unfix[j].HeaderStartN.x)*unfix[j].HeaderLength.x - (x1+unfix[k].HeaderStartN.x)*unfix[k].HeaderLength.x)
                           		     			+SQR((y+unfix[j].HeaderStartN.y)*unfix[j].HeaderLength.y - (y1+unfix[k].HeaderStartN.y)*unfix[k].HeaderLength.y)
                           	   		  			+SQR((z+unfix[j].HeaderStartN.z)*unfix[j].HeaderLength.z - (z1+unfix[k].HeaderStartN.z)*unfix[k].HeaderLength.z));
										length += data*l*data1;
											
									}
								}
								}
								} /* k-loop */ 
							}
						}
						}
						} /* j-loop */
                        dst->connect[i].estimatedLength = length/weight;
                        break;
                    }
                    default: {
                        fprintf(stderr, "Not supported\n");
                        break;
                    }
                }
                break;
            }
            default: {
                fprintf(stderr, "Not supported\n");
                break;
            }
        }
		sprintf(s, "ITER %02d", linfo.iter);
		energyTransferDataWriteConnect(s, dst, i, fpt, 2);
		if(dst->connect[i].mode == energyTransferPointModeConnect) {
        	rms2      = SQR(dst->connect[i].length - dst->connect[i].estimatedLength);
        	dst->rms += rms2;
			num++;
		}
    }
    dst->rms = sqrt(dst->rms/num);

	if((mode&0x1)==0x1) {
		lenergyTransferModelExpectedFRETSD(fpt, dst, unfix, linfo, mode);
	}
	lenergyTransferModelExpectedFRETOutput(fpt, dst, unfix, linfo, mode); 
}

void
lenergyTransferModelExpectedFRETOutput(FILE* fpt, energyTransferData* dst, mrcImage* unfix,
    lenergyTransferModelCheckInfo linfo, int mode)
{
    LOGPRINT2(fpt, "ITER", "CONNECT", "iter: %02d rms %10.4f", linfo.iter, dst->rms);
	if((mode&0x1)==0x1) {
    	LOGPRINT2(fpt, "ITER", "CONNECT", "iter: %02d rmsRootB %10.4f", linfo.iter, dst->rmsRootB);
	}
}

void
lenergyTransferModelExpectedFRETSD(FILE* fpt, energyTransferData* dst, mrcImage* unfix,
    lenergyTransferModelCheckInfo linfo, int mode)
{
    int i, j, k, flagJ, flagK;
	mrcImageParaTypeReal x, y, z;
	mrcImageParaTypeReal x1, y1, z1;
	double rmsRootB, rms2;
	double weight = 0.0;
	double length = 0.0; 
	double data, data1, l;
	char s[1024];
	int num;

    DEBUGPRINT("lenergyTransferModelExpectedFRETSD Start -----\n");
	rmsRootB = 0;
	num = 0;
    for(i=0; i<dst->numConnect; i++) {
        if(dst->numFix <= dst->connect[i].nID) { /* Unfix : j */
            j =  dst->connect[i].nID - dst->numFix;
            flagJ = 1;
        } else {                                 /* Fix   : j */
            j =  dst->connect[i].nID;
            flagJ = 0;
        }

        if(dst->numFix <= dst->connect[i].nID2) { /* Unfix : k*/
            k =  dst->connect[i].nID2 - dst->numFix;
            flagK = 1;
        } else {                                 /* Fix    : k*/
            k =  dst->connect[i].nID2;
            flagK = 0;
        }

		/* Stardard Deviation (SD) */	
        switch(flagJ) {
            case 0: { /* J: Fixed Point */ 
                switch(flagK) {
                    case 0: { /* K: Fixed Point */
                        fprintf(stderr, "Something wrong\n");
                        break;
                    }
                    case 1: { /* K: Unfixed Point */
						/* Fixed(j) - Unfixed(k) */
						weight = length = 0;
						for(x=0; x<unfix[k].HeaderN.x; x++) {
						for(y=0; y<unfix[k].HeaderN.y; y++) {
						for(z=0; z<unfix[k].HeaderN.z; z++) {
							mrcPixelDataGet(&(unfix[k]), x, y, z, &data, mrcPixelRePart, mrcPixelHowNearest);	
							weight += data; 
							length += data*SQR(sqrt(
								 SQR(dst->fix[j].x - (x+unfix[k].HeaderStartN.x)*unfix[k].HeaderLength.x)
                                +SQR(dst->fix[j].y - (y+unfix[k].HeaderStartN.y)*unfix[k].HeaderLength.y)
                                +SQR(dst->fix[j].z - (z+unfix[k].HeaderStartN.z)*unfix[k].HeaderLength.z))
								-dst->connect[i].estimatedLength);
						}
						}
						}
                        dst->connect[i].estimatedRootB = sqrt(length/weight);
                        break;
                    }
                    default: {
                        fprintf(stderr, "Not supported\n");
                        break;
                    }
                }
                break;
            }
            case 1: { /* J: Unfixed Point */
                switch(flagK) { 
                    case 0: { /* K: Fixed Point */
						/* Fixed(k) - Unfixed(j) */
						weight = 0.0;
						length = 0.0; 
						for(x=0; x<unfix[j].HeaderN.x; x++) {
						for(y=0; y<unfix[j].HeaderN.y; y++) {
						for(z=0; z<unfix[j].HeaderN.z; z++) {
							mrcPixelDataGet(&(unfix[j]), x, y, z, &data, mrcPixelRePart, mrcPixelHowNearest);	
							weight += data; 
							length += data*SQR(sqrt(
								 SQR(dst->fix[k].x - (x+unfix[j].HeaderStartN.x)*unfix[j].HeaderLength.x)
                                +SQR(dst->fix[k].y - (y+unfix[j].HeaderStartN.y)*unfix[j].HeaderLength.y)
                                +SQR(dst->fix[k].z - (z+unfix[j].HeaderStartN.z)*unfix[j].HeaderLength.z))
								-dst->connect[i].estimatedLength);
						}
						}
						}
                        dst->connect[i].estimatedRootB = sqrt(length/weight);
                        break;
                    }
                    case 1: { /* K: Unfixed Point */
						/* Unfixed(k) - Unfixed(j) */
						weight = 0.0;
						length = 0.0; 

						for(x=0; x<unfix[j].HeaderN.x; x++) {
						for(y=0; y<unfix[j].HeaderN.y; y++) {
						for(z=0; z<unfix[j].HeaderN.z; z++) {
							mrcPixelDataGet(&(unfix[j]), x, y, z, &data, mrcPixelRePart, mrcPixelHowNearest);	
							if(linfo.neglect<data) { 
								for(x1=0; x1<unfix[k].HeaderN.x; x1++) {
								for(y1=0; y1<unfix[k].HeaderN.y; y1++) {
								for(z1=0; z1<unfix[k].HeaderN.z; z1++) {
									mrcPixelDataGet(&(unfix[k]), x1, y1, z1, &data1, mrcPixelRePart, mrcPixelHowNearest);	
									if(linfo.neglect<data1) { 
										weight += data*data1; 
										l = sqrt(SQR((x+unfix[j].HeaderStartN.x)*unfix[j].HeaderLength.x - (x1+unfix[k].HeaderStartN.x)*unfix[k].HeaderLength.x)
                           		     			+SQR((y+unfix[j].HeaderStartN.y)*unfix[j].HeaderLength.y - (y1+unfix[k].HeaderStartN.y)*unfix[k].HeaderLength.y)
                           	   		  			+SQR((z+unfix[j].HeaderStartN.z)*unfix[j].HeaderLength.z - (z1+unfix[k].HeaderStartN.z)*unfix[k].HeaderLength.z));
										length += data*SQR(l-dst->connect[i].estimatedLength)*data1;
											
									}
								}
								}
								} /* k-loop */ 
							}
						}
						}
						} /* j-loop */
                        dst->connect[i].estimatedRootB = sqrt(length/weight);
                        break;
                    }
                    default: {
                        fprintf(stderr, "Not supported\n");
                        break;
                    }
                }
                break;
            }
            default: {
                fprintf(stderr, "Not supported\n");
                break;
            }
        }
		sprintf(s, "ITER %02d", linfo.iter); 
		energyTransferDataWriteConnect(s, dst, i, fpt, 3);
		if(dst->connect[i].mode == energyTransferPointModeConnect) { 
			rms2 = SQR(dst->connect[i].length-dst->connect[i].estimatedLength);
        	rmsRootB += rms2*SQR(dst->connect[i].estimatedRootB);
			num++;
		}	
   	}
	DEBUGPRINT3("rmsRootB2: %g dst->rms: %g n=%d\n", rmsRootB, dst->rms, num);
	dst->rmsRootB = sqrt(rmsRootB/SQR(dst->rms*num));
	DEBUGPRINT3("rms: %g +- %g n=%d\n", dst->rms, dst->rmsRootB, num);
}

void
energyTransferDataWrite(energyTransferData* dst, FILE* fpt, int lmode)
{
	energyTransferDataWrite0("INIT", dst, fpt, 0);
}

void
energyTransferDataWrite0(char* head, energyTransferData* dst, FILE* fpt, int lmode)
{
    int i;

	switch(lmode) {
		case 0: {
		    for(i=0; i<dst->numFix; i++) {
				energyTransferDataWriteFix(head, "FIX", dst, i, fpt, 0);
		    }
		    for(i=0; i<dst->numUnfix; i++) {
				energyTransferDataWriteUnfix(head, "UNFIX", dst, i, fpt, 0);
		    }
		    for(i=0; i<dst->numConnect; i++) {
				energyTransferDataWriteConnect(head, dst, i, fpt, 0);
		    }
			break;
		}	
		case 1: {
		    for(i=0; i<dst->numConnect; i++) {
				energyTransferDataWriteConnect(head, dst, i, fpt, 1);
		    }
			break;
		}	
		default: {
			break;
		}
	}
}
void
energyTransferDataWriteFix(char* head, char* subhead, energyTransferData* dst, int i, FILE* fpt, int lmode)
{
	LOGPRINT6(fpt, head, subhead, "%10s %5d %10.4f %10.4f %10.4f %10.4f",
		            dst->fix[i].ID, dst->fix[i].nID, dst->fix[i].x, dst->fix[i].y, dst->fix[i].z, dst->fix[i].rootB);
}

void
energyTransferDataWriteUnfix(char* head, char* subhead, energyTransferData* dst, int i, FILE* fpt, int lmode)
{
	LOGPRINT6(fpt, head, subhead, "%10s %5d %10.4f %10.4f %10.4f %10.4f",
		            dst->unfix[i].ID, dst->unfix[i].nID, dst->unfix[i].x, dst->unfix[i].y, dst->unfix[i].z, dst->unfix[i].rootB);   
}

void
energyTransferDataWriteConnect0(char* head, char* subhead, energyTransferData* dst, int i, FILE* fpt, int lmode)
{
	switch(lmode) {
		case 0: {
			LOGPRINT6(fpt, head, subhead, "%10s %5d %10s %5d %10.4f %10.4f",
	            		dst->connect[i].ID, dst->connect[i].nID, dst->connect[i].ID2, dst->connect[i].nID2,
	            		dst->connect[i].length, dst->connect[i].rootB);
			break;
		}
		case 1: {
			LOGPRINT6(fpt, head, subhead, "%10s %5d %10s %5d %10.4f %10.4f",
	            		dst->connect[i].ID, dst->connect[i].nID, dst->connect[i].ID2, dst->connect[i].nID2,
	            		dst->connect[i].estimatedLength, dst->connect[i].estimatedRootB);
			break;
		}
		case 2: {
        	LOGPRINT6(fpt, head, subhead, "%10s %5d %10s %5d Length %10.4f esitmatedLength %10.4f",
            	dst->connect[i].ID, dst->connect[i].nID, dst->connect[i].ID2, dst->connect[i].nID2,
            	dst->connect[i].length,
            	dst->connect[i].estimatedLength);
			break;
		}
		case 3: {
        	LOGPRINT6(fpt, head, subhead, "%10s %5d %10s %5d RootB  %10.4f esitmatedRootB  %10.4f",
            	dst->connect[i].ID, dst->connect[i].nID, dst->connect[i].ID2, dst->connect[i].nID2,
            	dst->connect[i].rootB,
            	dst->connect[i].estimatedRootB);
			break;
		}
		default: {
			break;
		}
	}
}
void
energyTransferDataWriteConnect(char* head, energyTransferData* dst, int i, FILE* fpt, int lmode)
{
	switch(dst->connect[i].mode) {
		case energyTransferPointModeConnect: {
			energyTransferDataWriteConnect0(head, "CONNECT", dst, i, fpt, lmode);
			break;
		}
		case energyTransferPointModeFar: {
	        energyTransferDataWriteConnect0(head, "FAR", dst, i, fpt, lmode);
			break;
		}
	    case energyTransferPointModeNear: {
	        energyTransferDataWriteConnect0(head, "NEAR", dst, i, fpt, lmode);
			break;
		}	
		default: {
			break;
		}
	}
}

void
energyTransferDataRead(energyTransferData* dst, FILE* fpt, int lmode)
{
    char s[1024];
    char* ID;
    char* mode;
    int ifix, iunfix, iconnect;

    fseek(fpt, 0L, SEEK_SET);
    dst->numFix = 0;
    dst->numUnfix = 0;
    dst->numConnect = 0;
    while(NULL!=stringGetFromFile(s, "", fpt, stdout, 3)) {
        ID   = stringGetNthWord(s, 1, " ,\t");
        mode = stringGetNthWord(s, 2, " ,\t");
        SSWITCH(mode)
            SCASE("fix") {
                dst->numFix++;
                SBREAK;
            }
            SCASE("unfix") {
                dst->numUnfix++;
                SBREAK;
            }
            SCASE("connect") {
                dst->numConnect++;
                SBREAK;
            }
            SCASE("far") {
                dst->numConnect++;
                SBREAK;
            }
            SCASE("near") {
                dst->numConnect++;
                SBREAK;
            }
            SDEFAULT {
                SBREAK;
            }
        SSWITCHEND;
    }
    DEBUGPRINT3("Fix: %d Unfix: %d Connect: %d\n", dst->numFix, dst->numUnfix, dst->numConnect);
    if(dst->numFix) {
        dst->fix = (energyTransferPoint*)memoryAllocate(sizeof(energyTransferPoint)*dst->numFix, "in Read");
    }
    if(dst->numUnfix) {
        dst->unfix = (energyTransferPoint*)memoryAllocate(sizeof(energyTransferPoint)*dst->numUnfix, "in Read");
    }
    if(dst->numConnect) {
        dst->connect = (energyTransferConnect*)memoryAllocate(sizeof(energyTransferConnect)*dst->numConnect, "in Read");
    }

    ifix = 0;
    iunfix = 0;
    iconnect = 0;
    fseek(fpt, 0L, SEEK_SET);
    while(NULL!=stringGetFromFile(s, "", fpt, stdout, 3)) {
        ID   = stringGetNthWord(s, 1, " ,\t");
        mode = stringGetNthWord(s, 2, " ,\t");
        SSWITCH(mode)
            SCASE("fix") {
                dst->fix[ifix].ID    = ID;
                dst->fix[ifix].nID   = ifix;
                dst->fix[ifix].mode  = energyTransferPointModeFixedPoint;
                dst->fix[ifix].x     = stringGetNthRealData(s, 3, " ,\t");
                dst->fix[ifix].y     = stringGetNthRealData(s, 4, " ,\t");
                dst->fix[ifix].z     = stringGetNthRealData(s, 5, " ,\t");
                dst->fix[ifix].rootB = stringGetNthRealData(s, 6, " ,\t");
                dst->fix[ifix].radius = stringGetNthRealData(s, 7, " ,\t");
                ifix++;
                SBREAK;
            }
            SCASE("unfix") {
                dst->unfix[iunfix].ID    = ID;
                dst->unfix[iunfix].nID   = iunfix + dst->numFix;
                dst->unfix[iunfix].mode  = energyTransferPointModeUnfixedPoint;
                dst->unfix[iunfix].x     = stringGetNthRealData(s, 3, " ,\t");
                dst->unfix[iunfix].y     = stringGetNthRealData(s, 4, " ,\t");
                dst->unfix[iunfix].z     = stringGetNthRealData(s, 5, " ,\t");
                dst->unfix[iunfix].rootB = stringGetNthRealData(s, 6, " ,\t");
                dst->unfix[iunfix].radius = stringGetNthRealData(s, 7, " ,\t");
                iunfix++;
                SBREAK;
            }
            SCASE("connect") {
                dst->connect[iconnect].ID     = ID;
                dst->connect[iconnect].mode   = energyTransferPointModeConnect;
                dst->connect[iconnect].ID2    = stringGetNthWord(s, 3, " ,\t");
                dst->connect[iconnect].length = stringGetNthRealData(s, 4, " ,\t");
                dst->connect[iconnect].rootB  = stringGetNthRealData(s, 5, " ,\t");
                iconnect++;
                SBREAK;
            }
            SCASE("far") {
                dst->connect[iconnect].ID     = ID;
                dst->connect[iconnect].mode   = energyTransferPointModeFar;
                dst->connect[iconnect].ID2    = stringGetNthWord(s, 3, " ,\t");
                dst->connect[iconnect].length = stringGetNthRealData(s, 4, " ,\t");
                dst->connect[iconnect].rootB  = stringGetNthRealData(s, 5, " ,\t");
                iconnect++;
                SBREAK;
            }
            SCASE("near") {
                dst->connect[iconnect].ID     = ID;
                dst->connect[iconnect].mode   = energyTransferPointModeNear;
                dst->connect[iconnect].ID2    = stringGetNthWord(s, 3, " ,\t");
                dst->connect[iconnect].length = stringGetNthRealData(s, 4, " ,\t");
                dst->connect[iconnect].rootB  = stringGetNthRealData(s, 5, " ,\t");
                iconnect++;
                SBREAK;
            }
            SDEFAULT {
                SBREAK;
            }
        SSWITCHEND;
    }

    for(iconnect=0; iconnect<dst->numConnect; iconnect++) {
/*
        DEBUGPRINT2("ID: %s ID2: %s \n", dst->connect[iconnect].ID, dst->connect[iconnect].ID2);
*/
        dst->connect[iconnect].nID  = dst->numFix + dst->numUnfix;
        dst->connect[iconnect].nID2 = dst->numFix + dst->numUnfix;
        for(ifix=0; ifix<dst->numFix; ifix++) {
/*
            DEBUGPRINT1("Fix: ID: %s \n", dst->fix[ifix].ID);
*/
            if(stringIsSame(dst->connect[iconnect].ID,  dst->fix[ifix].ID, 10)) {
                dst->connect[iconnect].nID  = dst->fix[ifix].nID;
            } else {
/*
                DEBUGPRINT2("Fix: ID: %s != %s\n", dst->fix[ifix].ID, dst->connect[iconnect].ID);
*/
            }
            if(stringIsSame(dst->connect[iconnect].ID2, dst->fix[ifix].ID, 10)) {
                dst->connect[iconnect].nID2 = dst->fix[ifix].nID;
            }
        }
        for(iunfix=0; iunfix<dst->numUnfix; iunfix++) {
/*
            DEBUGPRINT1("Unfix: ID: %s \n", dst->unfix[iunfix].ID);
*/
            if(stringIsSame(dst->connect[iconnect].ID,  dst->unfix[iunfix].ID, 10)) {
                dst->connect[iconnect].nID  = dst->unfix[iunfix].nID;
            } else {
/*
                DEBUGPRINT2("Fix: ID: %s != %s\n", dst->unfix[iunfix].ID, dst->connect[iconnect].ID);
*/
            }
            if(stringIsSame(dst->connect[iconnect].ID2, dst->unfix[iunfix].ID, 10)) {
                dst->connect[iconnect].nID2 = dst->unfix[iunfix].nID;
            }
        }

        if(dst->numFix + dst->numUnfix == dst->connect[iconnect].nID) {
            fprintf(stderr, "something wrong: please check your data file: no id connection\n");
            fprintf(stderr, "ID: %s \n", dst->connect[iconnect].ID);
        }
        if(dst->numFix + dst->numUnfix == dst->connect[iconnect].nID2) {
            fprintf(stderr, "something wrong: please check your data file: no id connection\n");
            fprintf(stderr, "ID2: %s \n", dst->connect[iconnect].ID2);
        }
        DEBUGPRINT3("CONNECT: ID: %20s <-> ID: %20s mode: %d\n", dst->connect[iconnect].ID, dst->connect[iconnect].ID2,
		                                                     dst->connect[iconnect].mode);
    }
}

inline
double
lFRETWeightCalc(double distance, double length, double variance, energyTransferPointMode mode)
{
	double weight;
	switch(mode) {
		case energyTransferPointModeConnect: {
        	weight   = exp(-SQR(distance - length)/variance/2.0)/sqrt(2*M_PI*variance);
			break;
		}
		case energyTransferPointModeFar: {
            weight   = SQR(distance)*SQR(distance)*SQR(distance)
					/(SQR(distance)*SQR(distance)*SQR(distance)+SQR(length)*SQR(length)*SQR(length));
			break;
		}
		case energyTransferPointModeNear: {
            weight   = SQR(length)*SQR(length)*SQR(length)
					/(SQR(distance)*SQR(distance)*SQR(distance)+SQR(length)*SQR(length)*SQR(length));
			break;
		}
		default: {
			fprintf(stderr, "Not supported mode: connection mode: %d\n", mode);
			exit(EXIT_FAILURE);
			break;
		} 
	}
	return weight;
}
