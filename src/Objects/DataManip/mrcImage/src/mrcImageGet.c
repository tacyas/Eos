/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% mrcImageGet ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : mrcImageGet 
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%mrcImageGet ver%I%; Date:%D% %Z%";
/* 
* mrcGet.c
*/
#include <math.h>
#include <stdlib.h>

#undef DEBUG
#include "genUtil.h"

#include "../inc/mrcImage.h"

#define SQR(x) ((x)*(x))
#define FOR_RINT (0.5)

static void polyInitMatrix(double matrix[6][6], int m, int n);
static void polyInitVector(double vec[6], int m, int n, double* image, int nx, int ny);
static int polySolveMatrix(double matrix[6][6], double vec[6], double coefficient[6]);

#define RTN_NAME "mrc"
inline
double
mrcImageDataGetbyAU(mrcImage* mrc,
		mrcImageParaTypeReal x,
		mrcImageParaTypeReal y,
		mrcImageParaTypeReal z,
		double* data,
		mrcPixelDataType mode,
		mrcPixelDataHowToGet how)
{
	return mrcPixelDataGet(mrc, 
						 x/mrc->HeaderLength.x-mrc->HeaderStartN.x,	
						 y/mrc->HeaderLength.y-mrc->HeaderStartN.y,	
						 z/mrc->HeaderLength.z-mrc->HeaderStartN.z,	
						 data,
						 mode,
						 how);
}
#undef RTN_NAME

#define RTN_NAME "mrcPixelDataGet"
inline
double
mrcPixelDataGet(mrcImage* mrc,
		mrcImageParaTypeReal x,
		mrcImageParaTypeReal y,
		mrcImageParaTypeReal z,
		double* data,
		mrcPixelDataType mode,
		mrcPixelDataHowToGet how)
{
    char s[20];
    mrcImageParaTypeInteger n, ix, iy, iz;
    double sig;

	DEBUGPRINT("mrcPixelDataGet\n");
    switch(mrc->HeaderMode) {
		case mrcFloatRadonImage: 
		case mrcCharImage: 
		case mrcShortImage:
		case mrcUShortImage:
		case mrcLongImage:
		case mrcFloatImage:
		case mrcDoubleImage: {
			ix = (mrcImageParaTypeInteger)POSITIVE_MODE(((mrcImageParaTypeInteger)floor(x+FOR_RINT)), mrc->HeaderN.x);
			iy = (mrcImageParaTypeInteger)POSITIVE_MODE(((mrcImageParaTypeInteger)floor(y+FOR_RINT)), mrc->HeaderN.y);
			iz = (mrcImageParaTypeInteger)POSITIVE_MODE(((mrcImageParaTypeInteger)floor(z+FOR_RINT)), mrc->HeaderN.z);
			DEBUGPRINT3("(%d, %d, %d)\n", ix, iy, iz);
            n =  ix + mrc->HeaderN.x*iy + mrc->HeaderN.x*mrc->HeaderN.y*iz;
			sig = 1.0;
			break;
        }
		case mrcComplexShortFT:
		case mrcComplexLongFT:
		case mrcComplexFloatFT:
		case mrcComplexDoubleFT: {
			switch(how) {
				case mrcPixelHowNearest: {
					if((1<mrc->HeaderN.x && (x < -mrc->HeaderN.x/2 || mrc->HeaderN.x/2 <  x))
					 ||(1<mrc->HeaderN.y && (y < -mrc->HeaderN.y/2 || mrc->HeaderN.y/2 <= y))
					 ||(1<mrc->HeaderN.z && (z < -mrc->HeaderN.z/2 || mrc->HeaderN.z/2 <= z))) {
						sig = 0; 
					} else {
						if(floor(x+FOR_RINT)<0) {
							ix = -(mrcImageParaTypeInteger)floor(x+FOR_RINT);
							iy = -(mrcImageParaTypeInteger)floor(y+FOR_RINT) + mrc->HeaderN.y/2;
							iz = -(mrcImageParaTypeInteger)floor(z+FOR_RINT) + mrc->HeaderN.z/2;
							sig = -1.0;
						} else {
                            ix = (mrcImageParaTypeInteger)floor(x+FOR_RINT);
							iy = (mrcImageParaTypeInteger)floor(y+FOR_RINT) + mrc->HeaderN.y/2;
							iz = (mrcImageParaTypeInteger)floor(z+FOR_RINT) + mrc->HeaderN.z/2;
							sig = 1.0;
 						}
					}
					DEBUGPRINT6("in: %f %f %f %d %d %d\n", x, y, z, ix, iy, iz)
					break;
				}
				case mrcPixelHowLinear: {
					if((1<mrc->HeaderN.x && (x < -mrc->HeaderN.x/2+1 || mrc->HeaderN.x/2 - 1 <  x))
					 ||(1<mrc->HeaderN.y && (y < -mrc->HeaderN.y/2+1 || mrc->HeaderN.y/2 - 1 <= y))
					 ||(1<mrc->HeaderN.z && (z < -mrc->HeaderN.z/2+1 || mrc->HeaderN.z/2 - 1 <= z))) {
						sig = 0; 
					} else {
						if(floor(x+FOR_RINT)<0) {
							ix = -(mrcImageParaTypeInteger)floor(x+FOR_RINT);
							iy = -(mrcImageParaTypeInteger)floor(y+FOR_RINT) + mrc->HeaderN.y/2;
							iz = -(mrcImageParaTypeInteger)floor(z+FOR_RINT) + mrc->HeaderN.z/2;
							sig = -1.0;
						} else {
                            ix = (mrcImageParaTypeInteger)floor(x+FOR_RINT);
							iy = (mrcImageParaTypeInteger)floor(y+FOR_RINT) + mrc->HeaderN.y/2;
							iz = (mrcImageParaTypeInteger)floor(z+FOR_RINT) + mrc->HeaderN.z/2;
							sig = 1.0;
 						}
					}
					DEBUGPRINT6("in: %f %f %f %d %d %d\n", x, y, z, ix, iy, iz)
					break;
				}
				default: {
					fprintf(stderr, "Not supported mode: %d (%f %f %f), (%d %d %d)\n", mode, x, y, z, ix, iy, iz);
					break;
				}
			}
			if(1 == mrc->HeaderN.z) {
				n = (ix + (mrc->HeaderN.x/2+1)*iy)%((mrc->HeaderN.x/2 + 1)*(mrc->HeaderN.y));
            } else {
				n = (ix + (mrc->HeaderN.x/2+1)*iy + (mrc->HeaderN.x/2+1)*(mrc->HeaderN.y)*iz)%((mrc->HeaderN.x/2+1)*(mrc->HeaderN.y)*(mrc->HeaderN.z));
            }

			break;
		}
		case mrcComplexFloatOneDimFT: {
			if(floor(x+FOR_RINT)<0) {
				ix = -(mrcImageParaTypeInteger)floor(x+FOR_RINT);
				sig = -1.0;
			} else {
                ix = (mrcImageParaTypeInteger)floor(x+FOR_RINT);
				sig = 1.0;
 			}
			iy = (mrcImageParaTypeInteger)POSITIVE_MODE(((mrcImageParaTypeInteger)floor(y+FOR_RINT)), mrc->HeaderN.y);
			iz = (mrcImageParaTypeInteger)POSITIVE_MODE(((mrcImageParaTypeInteger)floor(z+FOR_RINT)), mrc->HeaderN.z);

			n = ix + (mrc->HeaderN.x/2+1)*iy + (mrc->HeaderN.x/2+1)*mrc->HeaderN.y*iz;
			break;
		}
		case mrcFloatRadonFT: {
			if(floor(x+FOR_RINT)<0) {
				ix = -(mrcImageParaTypeInteger)floor(x+FOR_RINT);
				sig = -1.0;
			} else {
                ix = (mrcImageParaTypeInteger)floor(x+FOR_RINT);
				sig = 1.0;
 			}
			iy = (mrcImageParaTypeInteger)floor(y+FOR_RINT);
			iz = (mrcImageParaTypeInteger)floor(z+FOR_RINT);
			if(1 == mrc->HeaderN.z) {
				n = (ix + (mrc->HeaderN.x/2+1)*iy)%((mrc->HeaderN.x/2 + 1)*(mrc->HeaderN.y));
            } else {
				n = (ix + (mrc->HeaderN.x/2+1)*iy + (mrc->HeaderN.x/2+1)*(mrc->HeaderN.y)*iz)%((mrc->HeaderN.x/2+1)*(mrc->HeaderN.y)*(mrc->HeaderN.z));
            }
			break;
        }
		default: {
			sprintf(s, "mrcImage Mode %ld", mrc->HeaderMode);
			mrcError("Check!", RTN_NAME, s, 
				 mrcStatusMask_ExitFailure|MRC_ModeNotSupported);
			exit(EXIT_FAILURE);
        }
    }

    switch(how) {
        case mrcPixelHowNearest: {
			switch(mode) {
				case mrcPixelRePart: {
					switch(mrc->HeaderMode) {
						case mrcCharImage: {
                            if(mrc->flagSigned) {
						        *data = (double)(signed char)mrc->ImageCharImage[n];
                            } else {
						        *data = (double)mrc->ImageCharImage[n];
                            }
						   break;
						}
						case mrcShortImage: {
						   *data = (double)(signed short)mrc->ImageShortImage[n];
                           break;
                        }
						case mrcUShortImage: {
						   *data = (double)(unsigned short)mrc->ImageShortImage[n];
						   break;
						}
						case mrcFloatImage: {
							*data = (double)mrc->ImageFloatImage[n];
							break;
						}
						case mrcComplexShortFT: {
							*data = (double)mrc->ImageShortImage[2*n];
							break;
                        }
						case mrcComplexFloatFT: {
							*data = (double)mrc->ImageFloatImage[2*n];
							break;
						}
						case mrcComplexFloatOneDimFT: {
							*data = (double)mrc->ImageFloatImage[2*n];
							break;
						}
						case mrcFloatRadonImage: {
							*data = (double)mrc->ImageFloatImage[n];
							break;
						}
						case mrcFloatRadonFT: {
							*data = (double)mrc->ImageFloatImage[2*n];
							break;
						}
						case mrcLongImage: {
							*data = (double)mrc->ImageLongImage[n];
							break;
						}
						case mrcDoubleImage: {
							*data = (double)mrc->ImageDoubleImage[n];
							break;
						}
						case mrcComplexLongFT: {
							*data = (double)mrc->ImageLongImage[2*n];
							break;
						}
						case mrcComplexDoubleFT: {
							*data = (double)mrc->ImageDoubleImage[2*n];
							break;
						}
						default: {
							sprintf(s, "mrcImage Mode %ld", mrc->HeaderMode);
							mrcError(RTN_NAME, "mrcPixelRePart", s, 
								 mrcStatusMask_ExitFailure|MRC_ModeNotSupported);
						}
					}
					break;
				}
				case mrcPixelImPart: {
					switch(mrc->HeaderMode) {
						case mrcComplexShortFT: {
							*data = sig*(double)mrc->ImageShortImage[2*n+1];
							break;
						}
						case mrcComplexLongFT: {
							*data = sig*(double)mrc->ImageLongImage[2*n+1];
							break;
						}
						case mrcComplexFloatFT: {
							*data = sig*(double)mrc->ImageFloatImage[2*n+1];
							break;
						}
						case mrcComplexFloatOneDimFT: {
							*data = sig*(double)mrc->ImageFloatImage[2*n+1];
							break;
						}
						case mrcFloatRadonFT: {
							*data = sig*(double)mrc->ImageFloatImage[2*n+1];
							break;
						}
						case mrcComplexDoubleFT: {
							*data = sig*(double)mrc->ImageDoubleImage[2*n+1];
							break;
						}
						default: {
							sprintf(s, "mrcImage Mode %ld", mrc->HeaderMode);
                            mrcError(RTN_NAME, "mrcPixelImPart", s, 
							 mrcStatusMask_ExitFailure|MRC_ModeNotSupported);
                        }
					}
					break;
                }
				case mrcPixelMag: {
					switch(mrc->HeaderMode) {
						case mrcCharImage: {
							*data = (double)mrc->ImageCharImage[n];
							break;
                        }
						case mrcShortImage: { 
							*data = (double)(short)mrc->ImageShortImage[n];
							break;
						}
						case mrcUShortImage: {
							*data = (double)(unsigned short)mrc->ImageShortImage[n];
							break;
						}
						case mrcFloatImage: {
							*data = (double)mrc->ImageFloatImage[n];
							break;
						}
						case mrcLongImage: {
							*data = (double)mrc->ImageLongImage[n];
							break;
						}
						case mrcDoubleImage: {
							*data = (double)mrc->ImageDoubleImage[n];
							break;
						}
						case mrcFloatRadonImage: {
							*data = (double)mrc->ImageFloatImage[n];
							break;
						}
						case mrcComplexShortFT: {
							*data = sqrt(SQR((double)mrc->ImageShortImage[2*n])
										+SQR((double)mrc->ImageShortImage[2*n+1]));
							break;
						}
						case mrcComplexLongFT: { 
							*data = sqrt(SQR((double)mrc->ImageLongImage[2*n]) 
						    +SQR((double)mrc->ImageLongImage[2*n+1]));
                            break;
						}
						case mrcComplexFloatFT: {
						    *data = sqrt(SQR((double)mrc->ImageFloatImage[2*n])
						                +SQR((double)mrc->ImageFloatImage[2*n+1]));
						    break;
						}
						case mrcComplexFloatOneDimFT: {
						    *data = sqrt(SQR((double)mrc->ImageFloatImage[2*n])
						                +SQR((double)mrc->ImageFloatImage[2*n+1]));
						    break;
						}
						case mrcFloatRadonFT: {
						    *data = sqrt(SQR((double)mrc->ImageFloatImage[2*n])
						                +SQR((double)mrc->ImageFloatImage[2*n+1]));
						    break;
						}
						case mrcComplexDoubleFT: {
						    *data = sqrt(SQR((double)mrc->ImageDoubleImage[2*n])
						                +SQR((double)mrc->ImageDoubleImage[2*n+1]));
						    break;
						}
						default: {
						    sprintf(s, "mrcImage Mode %ld", mrc->HeaderMode);
			                mrcError(RTN_NAME, "mrcPixelMagPart", s, 
							        mrcStatusMask_ExitFailure|MRC_ModeNotSupported);
						}
					}
					break;
				}
				case mrcPixelPow: {
					switch(mrc->HeaderMode) {
						case mrcCharImage: {
							*data = SQR((double)mrc->ImageCharImage[n]);
							break;
                        }
						case mrcShortImage: 
						case mrcUShortImage: {
							*data = SQR((double)mrc->ImageShortImage[n]);
							break;
						}
						case mrcFloatImage: {
							*data = SQR((double)mrc->ImageFloatImage[n]);
							break;
						}
						case mrcLongImage: {
							*data = SQR((double)mrc->ImageLongImage[n]);
							break;
						}
						case mrcDoubleImage: {
							*data = SQR((double)mrc->ImageDoubleImage[n]);
							break;
						}
						case mrcComplexShortFT: {
						    *data = (SQR((double)mrc->ImageShortImage[2*n])
						            +SQR((double)mrc->ImageShortImage[2*n+1]));
						    break;
						}
						case mrcComplexLongFT: {
						    *data = (SQR((double)mrc->ImageLongImage[2*n])
						            +SQR((double)mrc->ImageLongImage[2*n+1]));
			                break;
						}
						case mrcComplexFloatFT: {
						    *data = (SQR((double)mrc->ImageFloatImage[2*n])
						            +SQR((double)mrc->ImageFloatImage[2*n+1]));
						    break;
						}
						case mrcComplexFloatOneDimFT: {
						    *data = (SQR((double)mrc->ImageFloatImage[2*n])
						            +SQR((double)mrc->ImageFloatImage[2*n+1]));
						    break;
						}
						case mrcFloatRadonFT: {
						    *data = (SQR((double)mrc->ImageFloatImage[2*n])
						            +SQR((double)mrc->ImageFloatImage[2*n+1]));
						    break;
						}
						case mrcComplexDoubleFT: {
						    *data = (SQR((double)mrc->ImageDoubleImage[2*n])
						            +SQR((double)mrc->ImageDoubleImage[2*n+1]));
						    break;
						}
						default: {
						    sprintf(s, "mrcImage Mode %ld", mrc->HeaderMode);
			                mrcError(RTN_NAME, "mrcPixelPowPart", s, 
							     mrcStatusMask_ExitFailure|MRC_ModeNotSupported);
						}
					}
		    		break;
				}
				case mrcPixelLogMag: {
					switch(mrc->HeaderMode) {
						case mrcComplexShortFT: {
							*data = log10(SQR((double)mrc->ImageShortImage[2*n])
										 +SQR((double)mrc->ImageShortImage[2*n+1]))/2;
						    break;
						}
						case mrcComplexLongFT: {
						    *data = log10(SQR((double)mrc->ImageLongImage[2*n])
						                 +SQR((double)mrc->ImageLongImage[2*n+1]))/2;
			                            break;
						}
						case mrcComplexFloatFT: {
						    *data = log10(SQR((double)mrc->ImageFloatImage[2*n])
						                 +SQR((double)mrc->ImageFloatImage[2*n+1]))/2;
						    break;
						}
						case mrcComplexFloatOneDimFT: {
						    *data = log10(SQR((double)mrc->ImageFloatImage[2*n])
						                 +SQR((double)mrc->ImageFloatImage[2*n+1]))/2;
						    break;
						}
						case mrcFloatRadonFT: {
						    *data = log10(SQR((double)mrc->ImageFloatImage[2*n])
						                 +SQR((double)mrc->ImageFloatImage[2*n+1]))/2;
						    break;
						}
						case mrcComplexDoubleFT: {
						    *data = log10(SQR((double)mrc->ImageDoubleImage[2*n])
						                 +SQR((double)mrc->ImageDoubleImage[2*n+1]))/2;
						    break;
						}
						default: {
						    sprintf(s, "mrcImage Mode %ld", mrc->HeaderMode);
			                mrcError(RTN_NAME, "mrcPixelLogMagPart", s, 
							     mrcStatusMask_ExitFailure|MRC_ModeNotSupported);
						}
					}
					break;
				}
				case mrcPixelLogPow: {
					switch(mrc->HeaderMode) {
						case mrcComplexShortFT: {
						    *data = log10(SQR((double)mrc->ImageShortImage[2*n])
						                 +SQR((double)mrc->ImageShortImage[2*n+1]));
						    break;
						}
						case mrcComplexLongFT: {
						    *data = log10(SQR((double)mrc->ImageLongImage[2*n])
						                 +SQR((double)mrc->ImageLongImage[2*n+1]));
			                            break;
						}
						case mrcComplexFloatFT: {
						    *data = log10(SQR((double)mrc->ImageFloatImage[2*n])
						                 +SQR((double)mrc->ImageFloatImage[2*n+1]));
						    break;
						}
						case mrcComplexFloatOneDimFT: {
						    *data = log10(SQR((double)mrc->ImageFloatImage[2*n])
						                 +SQR((double)mrc->ImageFloatImage[2*n+1]));
						    break;
						}
						case mrcFloatRadonFT: {
						    *data = log10(SQR((double)mrc->ImageFloatImage[2*n])
						                 +SQR((double)mrc->ImageFloatImage[2*n+1]));
						    break;
						}
						case mrcComplexDoubleFT: {
						    *data = log10(SQR((double)mrc->ImageDoubleImage[2*n])
						                 +SQR((double)mrc->ImageDoubleImage[2*n+1]));
						    break;
						}
						default: {
						    sprintf(s, "mrcImage Mode %ld", mrc->HeaderMode);
			                mrcError(RTN_NAME, "mrcPixelLogPowPart", s, 
							     mrcStatusMask_ExitFailure|MRC_ModeNotSupported);
                        }
		    		}
		    		break;
				}
				case mrcPixelPhase: {
					switch(mrc->HeaderMode) {
						case mrcComplexShortFT: {
							if(mrc->ImageShortImage[2*n+1]==0 && mrc->ImageShortImage[2*n]==0) {
								*data = 0;
							} else {
						    	*data = atan2(sig*((double)mrc->ImageShortImage[2*n+1])
						                 ,((double)mrc->ImageShortImage[2*n]));
							}
						    break;
						}
						case mrcComplexLongFT: {
							if(mrc->ImageLongImage[2*n+1]==0 && mrc->ImageLongImage[2*n]==0) {
								*data = 0.0;
							} else {
						    	*data = atan2(sig*((double)mrc->ImageLongImage[2*n+1])
						                 ,((double)mrc->ImageLongImage[2*n]));
							}
			                            break;
						}
						case mrcComplexFloatFT: {
							if(mrc->ImageFloatImage[2*n+1]==0 && mrc->ImageFloatImage[2*n]==0) {
								*data = 0.0;
							} else {
						    	*data = atan2(sig*((double)mrc->ImageFloatImage[2*n+1])
						                 ,((double)mrc->ImageFloatImage[2*n]));
							}
						    break;
						}
						case mrcComplexFloatOneDimFT: {
							if(mrc->ImageFloatImage[2*n+1]==0 && mrc->ImageFloatImage[2*n]==0) {
								*data = 0.0;
							} else {
						    	*data = atan2(sig*((double)mrc->ImageFloatImage[2*n+1])
						                 ,((double)mrc->ImageFloatImage[2*n]));
							}
						    break;
						}
						case mrcFloatRadonFT: {
							if(mrc->ImageFloatImage[2*n+1]==0 && mrc->ImageFloatImage[2*n]==0) {
								*data = 0.0;
							} else {
						    	*data = atan2(sig*((double)mrc->ImageFloatImage[2*n+1])
						                 ,((double)mrc->ImageFloatImage[2*n]));
							}
						    break;
						}
						case mrcComplexDoubleFT: {
							if(mrc->ImageDoubleImage[2*n+1]== 0 && mrc->ImageDoubleImage[2*n]==0) {
								*data = 0.0;
							} else {
						    	*data = atan2(sig*((double)mrc->ImageDoubleImage[2*n+1])
						                 ,((double)mrc->ImageDoubleImage[2*n]));
							}
						    break;
						}
						default: {
						    sprintf(s, "mrcImage Mode %ld", mrc->HeaderMode);
			                mrcError(RTN_NAME, "mrcPixelPhasePart", s, 
							     mrcStatusMask_ExitFailure|MRC_ModeNotSupported);
                        }
					}
					break;
				}
				default: {
					sprintf(s, "mrcPixelType %d", mode);
					mrcError(RTN_NAME, "Pixel Data Type", s, 
						 mrcStatusMask_ExitFailure|MRC_ModeNotSupported);
					break;
				}
			}
            break;
		} 
		case mrcPixelHowLinear: {
			mrcImageParaTypeInteger ix0, iy0, iz0;
			mrcImageParaTypeInteger ix1, iy1, iz1;
			double xx, yy, zz;

			switch(mrc->HeaderMode) {
				case mrcShortImage: 
				case mrcUShortImage: 
				case mrcFloatImage: 
				case mrcDoubleImage: 
				case mrcFloatRadonImage: {
					ix0 = floor(x);
					iy0 = floor(y);
					iz0 = floor(z);
					ix1 = ix0 + 1;
					iy1 = iy0 + 1;
					iz1 = iz0 + 1;
					break;
				}
				case mrcComplexDoubleFT: 
				case mrcComplexFloatFT: {
					if(0<=floor(x)) {
						ix0 = floor(x);
						iy0 = floor(y);
						iz0 = floor(z);
						ix1 = ix0 + 1;
						iy1 = iy0 + 1;
						iz1 = iz0 + 1;
						xx = x;
						yy = y;
						zz = z;
					} else {
						ix0 = floor(-x);
						iy0 = floor(-y);
						iz0 = floor(-z);
						ix1 = ix0 + 1;
						iy1 = iy0 + 1;
						iz1 = iz0 + 1;
						xx = -x;
						yy = -y;
						zz = -z;
					}
					DEBUGPRINT6("in: %d %d %d <-> %d %d %d\n", ix0, iy0, iz0, ix1, iy1, iz1); 
					DEBUGPRINT4("in: %f %f %f %f\n", sig, x, y, z); 
					DEBUGPRINT4("in: %f %f %f %f\n", sig, xx, yy, zz); 
					break;
				}
				default: {
					sprintf(s, "mrcImage Mode %ld", mrc->HeaderMode);
			        mrcError(RTN_NAME, "mrcPixelPhasePart", s, 
						mrcStatusMask_ExitFailure|MRC_ModeNotSupported);
					break;
                }
			}
			switch(mode) {
				case mrcPixelRePart: {
					switch(mrc->HeaderMode) {
						case mrcShortImage: {
							*data = (ix1 -  x)*(iy1 -  y)*(iz1 -  z)*(signed short)mrc->ImageShortImage[
											 		 			 POSITIVE_MODE(ix0,mrc->HeaderN.x)
																+POSITIVE_MODE(iy0,mrc->HeaderN.y)*mrc->HeaderN.x
																+POSITIVE_MODE(iz0,mrc->HeaderN.z)*mrc->HeaderN.x*mrc->HeaderN.y]
								  + (ix1 -  x)*(  y -iy0)*(iz1 -  z)*(signed short)mrc->ImageShortImage[
																 POSITIVE_MODE(ix0,mrc->HeaderN.x)
																+POSITIVE_MODE(iy1,mrc->HeaderN.y)*mrc->HeaderN.x
																+POSITIVE_MODE(iz0,mrc->HeaderN.z)*mrc->HeaderN.x*mrc->HeaderN.y]
								  + (  x -ix0)*(iy1 -  y)*(iz1 -  z)*(signed short)mrc->ImageShortImage[
																 POSITIVE_MODE(ix1,mrc->HeaderN.x)
																+POSITIVE_MODE(iy0,mrc->HeaderN.y)*mrc->HeaderN.x
																+POSITIVE_MODE(iz0,mrc->HeaderN.z)*mrc->HeaderN.x*mrc->HeaderN.y]
								  + (  x -ix0)*(  y -iy0)*(iz1 -  z)*(signed short)mrc->ImageShortImage[
																 POSITIVE_MODE(ix1,mrc->HeaderN.x)
																+POSITIVE_MODE(iy1,mrc->HeaderN.y)*mrc->HeaderN.x
																+POSITIVE_MODE(iz0,mrc->HeaderN.z)*mrc->HeaderN.x*mrc->HeaderN.y]
							      + (ix1 -  x)*(iy1 -  y)*(  z -iz0)*(signed short)mrc->ImageShortImage[
																 POSITIVE_MODE(ix0,mrc->HeaderN.x)
																+POSITIVE_MODE(iy0,mrc->HeaderN.y)*mrc->HeaderN.x
																+POSITIVE_MODE(iz1,mrc->HeaderN.z)*mrc->HeaderN.x*mrc->HeaderN.y]
								  + (ix1 -  x)*(  y -iy0)*(  z -iz0)*(signed short)mrc->ImageShortImage[
																 POSITIVE_MODE(ix0,mrc->HeaderN.x)
																+POSITIVE_MODE(iy1,mrc->HeaderN.y)*mrc->HeaderN.x
																+POSITIVE_MODE(iz1,mrc->HeaderN.z)*mrc->HeaderN.x*mrc->HeaderN.y]
								  + (  x -ix0)*(iy1 -  y)*(  z -iz0)*(signed short)mrc->ImageShortImage[
																 POSITIVE_MODE(ix1,mrc->HeaderN.x)
																+POSITIVE_MODE(iy0,mrc->HeaderN.y)*mrc->HeaderN.x
																+POSITIVE_MODE(iz1,mrc->HeaderN.z)*mrc->HeaderN.x*mrc->HeaderN.y]
								  + (  x -ix0)*(  y -iy0)*(  z -iz0)*(signed short)mrc->ImageShortImage[
																 POSITIVE_MODE(ix1,mrc->HeaderN.x)
																+POSITIVE_MODE(iy1,mrc->HeaderN.y)*mrc->HeaderN.x
																+POSITIVE_MODE(iz1,mrc->HeaderN.z)*mrc->HeaderN.x*mrc->HeaderN.y];
							break;
						}
						case mrcUShortImage: {
							*data = (ix1 -  x)*(iy1 -  y)*(iz1 -  z)*(unsigned short)mrc->ImageShortImage[
											 		 			 POSITIVE_MODE(ix0,mrc->HeaderN.x)
																+POSITIVE_MODE(iy0,mrc->HeaderN.y)*mrc->HeaderN.x
																+POSITIVE_MODE(iz0,mrc->HeaderN.z)*mrc->HeaderN.x*mrc->HeaderN.y]
								  + (ix1 -  x)*(  y -iy0)*(iz1 -  z)*(unsigned short)mrc->ImageShortImage[
																 POSITIVE_MODE(ix0,mrc->HeaderN.x)
																+POSITIVE_MODE(iy1,mrc->HeaderN.y)*mrc->HeaderN.x
																+POSITIVE_MODE(iz0,mrc->HeaderN.z)*mrc->HeaderN.x*mrc->HeaderN.y]
								  + (  x -ix0)*(iy1 -  y)*(iz1 -  z)*(unsigned short)mrc->ImageShortImage[
																 POSITIVE_MODE(ix1,mrc->HeaderN.x)
																+POSITIVE_MODE(iy0,mrc->HeaderN.y)*mrc->HeaderN.x
																+POSITIVE_MODE(iz0,mrc->HeaderN.z)*mrc->HeaderN.x*mrc->HeaderN.y]
								  + (  x -ix0)*(  y -iy0)*(iz1 -  z)*(unsigned short)mrc->ImageShortImage[
																 POSITIVE_MODE(ix1,mrc->HeaderN.x)
																+POSITIVE_MODE(iy1,mrc->HeaderN.y)*mrc->HeaderN.x
																+POSITIVE_MODE(iz0,mrc->HeaderN.z)*mrc->HeaderN.x*mrc->HeaderN.y]
							      + (ix1 -  x)*(iy1 -  y)*(  z -iz0)*(unsigned short)mrc->ImageShortImage[
																 POSITIVE_MODE(ix0,mrc->HeaderN.x)
																+POSITIVE_MODE(iy0,mrc->HeaderN.y)*mrc->HeaderN.x
																+POSITIVE_MODE(iz1,mrc->HeaderN.z)*mrc->HeaderN.x*mrc->HeaderN.y]
								  + (ix1 -  x)*(  y -iy0)*(  z -iz0)*(unsigned short)mrc->ImageShortImage[
																 POSITIVE_MODE(ix0,mrc->HeaderN.x)
																+POSITIVE_MODE(iy1,mrc->HeaderN.y)*mrc->HeaderN.x
																+POSITIVE_MODE(iz1,mrc->HeaderN.z)*mrc->HeaderN.x*mrc->HeaderN.y]
								  + (  x -ix0)*(iy1 -  y)*(  z -iz0)*(unsigned short)mrc->ImageShortImage[
																 POSITIVE_MODE(ix1,mrc->HeaderN.x)
																+POSITIVE_MODE(iy0,mrc->HeaderN.y)*mrc->HeaderN.x
																+POSITIVE_MODE(iz1,mrc->HeaderN.z)*mrc->HeaderN.x*mrc->HeaderN.y]
								  + (  x -ix0)*(  y -iy0)*(  z -iz0)*(unsigned short)mrc->ImageShortImage[
																 POSITIVE_MODE(ix1,mrc->HeaderN.x)
																+POSITIVE_MODE(iy1,mrc->HeaderN.y)*mrc->HeaderN.x
																+POSITIVE_MODE(iz1,mrc->HeaderN.z)*mrc->HeaderN.x*mrc->HeaderN.y];
							break;
						}
						case mrcFloatImage: {
							*data = (ix1 -  x)*(iy1 -  y)*(iz1 -  z)*mrc->ImageFloatImage[
											 		 			 POSITIVE_MODE(ix0,mrc->HeaderN.x)
																+POSITIVE_MODE(iy0,mrc->HeaderN.y)*mrc->HeaderN.x
																+POSITIVE_MODE(iz0,mrc->HeaderN.z)*mrc->HeaderN.x*mrc->HeaderN.y]
								  + (ix1 -  x)*(  y -iy0)*(iz1 -  z)*mrc->ImageFloatImage[
																 POSITIVE_MODE(ix0,mrc->HeaderN.x)
																+POSITIVE_MODE(iy1,mrc->HeaderN.y)*mrc->HeaderN.x
																+POSITIVE_MODE(iz0,mrc->HeaderN.z)*mrc->HeaderN.x*mrc->HeaderN.y]
								  + (  x -ix0)*(iy1 -  y)*(iz1 -  z)*mrc->ImageFloatImage[
																 POSITIVE_MODE(ix1,mrc->HeaderN.x)
																+POSITIVE_MODE(iy0,mrc->HeaderN.y)*mrc->HeaderN.x
																+POSITIVE_MODE(iz0,mrc->HeaderN.z)*mrc->HeaderN.x*mrc->HeaderN.y]
								  + (  x -ix0)*(  y -iy0)*(iz1 -  z)*mrc->ImageFloatImage[
																 POSITIVE_MODE(ix1,mrc->HeaderN.x)
																+POSITIVE_MODE(iy1,mrc->HeaderN.y)*mrc->HeaderN.x
																+POSITIVE_MODE(iz0,mrc->HeaderN.z)*mrc->HeaderN.x*mrc->HeaderN.y]
							      + (ix1 -  x)*(iy1 -  y)*(  z -iz0)*mrc->ImageFloatImage[
																 POSITIVE_MODE(ix0,mrc->HeaderN.x)
																+POSITIVE_MODE(iy0,mrc->HeaderN.y)*mrc->HeaderN.x
																+POSITIVE_MODE(iz1,mrc->HeaderN.z)*mrc->HeaderN.x*mrc->HeaderN.y]
								  + (ix1 -  x)*(  y -iy0)*(  z -iz0)*mrc->ImageFloatImage[
																 POSITIVE_MODE(ix0,mrc->HeaderN.x)
																+POSITIVE_MODE(iy1,mrc->HeaderN.y)*mrc->HeaderN.x
																+POSITIVE_MODE(iz1,mrc->HeaderN.z)*mrc->HeaderN.x*mrc->HeaderN.y]
								  + (  x -ix0)*(iy1 -  y)*(  z -iz0)*mrc->ImageFloatImage[
																 POSITIVE_MODE(ix1,mrc->HeaderN.x)
																+POSITIVE_MODE(iy0,mrc->HeaderN.y)*mrc->HeaderN.x
																+POSITIVE_MODE(iz1,mrc->HeaderN.z)*mrc->HeaderN.x*mrc->HeaderN.y]
								  + (  x -ix0)*(  y -iy0)*(  z -iz0)*mrc->ImageFloatImage[
																 POSITIVE_MODE(ix1,mrc->HeaderN.x)
																+POSITIVE_MODE(iy1,mrc->HeaderN.y)*mrc->HeaderN.x
																+POSITIVE_MODE(iz1,mrc->HeaderN.z)*mrc->HeaderN.x*mrc->HeaderN.y];
							break;
						}
						case mrcDoubleImage: {
							*data = (ix1 -  x)*(iy1 -  y)*(iz1 -  z)*mrc->ImageDoubleImage[
											 		 			 POSITIVE_MODE(ix0,mrc->HeaderN.x)
																+POSITIVE_MODE(iy0,mrc->HeaderN.y)*mrc->HeaderN.x
																+POSITIVE_MODE(iz0,mrc->HeaderN.z)*mrc->HeaderN.x*mrc->HeaderN.y]
								  + (ix1 -  x)*(  y -iy0)*(iz1 -  z)*mrc->ImageDoubleImage[
																 POSITIVE_MODE(ix0,mrc->HeaderN.x)
																+POSITIVE_MODE(iy1,mrc->HeaderN.y)*mrc->HeaderN.x
																+POSITIVE_MODE(iz0,mrc->HeaderN.z)*mrc->HeaderN.x*mrc->HeaderN.y]
								  + (  x -ix0)*(iy1 -  y)*(iz1 -  z)*mrc->ImageDoubleImage[
																 POSITIVE_MODE(ix1,mrc->HeaderN.x)
																+POSITIVE_MODE(iy0,mrc->HeaderN.y)*mrc->HeaderN.x
																+POSITIVE_MODE(iz0,mrc->HeaderN.z)*mrc->HeaderN.x*mrc->HeaderN.y]
								  + (  x -ix0)*(  y -iy0)*(iz1 -  z)*mrc->ImageDoubleImage[
																 POSITIVE_MODE(ix1,mrc->HeaderN.x)
																+POSITIVE_MODE(iy1,mrc->HeaderN.y)*mrc->HeaderN.x
																+POSITIVE_MODE(iz0,mrc->HeaderN.z)*mrc->HeaderN.x*mrc->HeaderN.y]
							      + (ix1 -  x)*(iy1 -  y)*(  z -iz0)*mrc->ImageDoubleImage[
																 POSITIVE_MODE(ix0,mrc->HeaderN.x)
																+POSITIVE_MODE(iy0,mrc->HeaderN.y)*mrc->HeaderN.x
																+POSITIVE_MODE(iz1,mrc->HeaderN.z)*mrc->HeaderN.x*mrc->HeaderN.y]
								  + (ix1 -  x)*(  y -iy0)*(  z -iz0)*mrc->ImageDoubleImage[
																 POSITIVE_MODE(ix0,mrc->HeaderN.x)
																+POSITIVE_MODE(iy1,mrc->HeaderN.y)*mrc->HeaderN.x
																+POSITIVE_MODE(iz1,mrc->HeaderN.z)*mrc->HeaderN.x*mrc->HeaderN.y]
								  + (  x -ix0)*(iy1 -  y)*(  z -iz0)*mrc->ImageDoubleImage[
																 POSITIVE_MODE(ix1,mrc->HeaderN.x)
																+POSITIVE_MODE(iy0,mrc->HeaderN.y)*mrc->HeaderN.x
																+POSITIVE_MODE(iz1,mrc->HeaderN.z)*mrc->HeaderN.x*mrc->HeaderN.y]
								  + (  x -ix0)*(  y -iy0)*(  z -iz0)*mrc->ImageDoubleImage[
																 POSITIVE_MODE(ix1,mrc->HeaderN.x)
																+POSITIVE_MODE(iy1,mrc->HeaderN.y)*mrc->HeaderN.x
																+POSITIVE_MODE(iz1,mrc->HeaderN.z)*mrc->HeaderN.x*mrc->HeaderN.y];
							break;
						}
						case mrcFloatRadonImage: {
							*data = (ix1 -  x)*mrc->ImageFloatImage[
											 		 			 POSITIVE_MODE(ix0,mrc->HeaderN.x)
																+POSITIVE_MODE(iy0,mrc->HeaderN.y)*mrc->HeaderN.x
																+POSITIVE_MODE(iz0,mrc->HeaderN.z)*mrc->HeaderN.x*mrc->HeaderN.y]
								  + (  x -ix0)*mrc->ImageFloatImage[
																 POSITIVE_MODE(ix1,mrc->HeaderN.x)
																+POSITIVE_MODE(iy0,mrc->HeaderN.y)*mrc->HeaderN.x
																+POSITIVE_MODE(iz0,mrc->HeaderN.z)*mrc->HeaderN.x*mrc->HeaderN.y];
							break;
						}
						case mrcComplexFloatFT: {
							if(sig==0) {
								*data=0;
							} else {
							*data = (ix1 -  xx)*(iy1 -  yy)*(iz1 -  zz)*mrc->ImageFloatImage[2*(
											 		 			 POSITIVE_MODE(ix0,mrc->HeaderN.x/2+1)
																+POSITIVE_MODE(iy0+mrc->HeaderN.y/2,mrc->HeaderN.y)*(mrc->HeaderN.x/2+1)
																+POSITIVE_MODE(iz0+mrc->HeaderN.z/2,mrc->HeaderN.z)*(mrc->HeaderN.x/2+1)*(mrc->HeaderN.y))]
								  + (ix1 -  xx)*(  yy -iy0)*(iz1 -  zz)*mrc->ImageFloatImage[2*(
																 POSITIVE_MODE(ix0,mrc->HeaderN.x/2+1)
																+POSITIVE_MODE(iy1+mrc->HeaderN.y/2,mrc->HeaderN.y)*(mrc->HeaderN.x/2+1)
																+POSITIVE_MODE(iz0+mrc->HeaderN.z/2,mrc->HeaderN.z)*(mrc->HeaderN.x/2+1)*(mrc->HeaderN.y))]
								  + (  xx -ix0)*(iy1 -  yy)*(iz1 -  zz)*mrc->ImageFloatImage[2*(
																 POSITIVE_MODE(ix1,mrc->HeaderN.x/2+1)
																+POSITIVE_MODE(iy0+mrc->HeaderN.y/2,mrc->HeaderN.y)*(mrc->HeaderN.x/2+1)
																+POSITIVE_MODE(iz0+mrc->HeaderN.z/2,mrc->HeaderN.z)*(mrc->HeaderN.x/2+1)*(mrc->HeaderN.y))]
								  + (  xx -ix0)*(  yy -iy0)*(iz1 -  zz)*mrc->ImageFloatImage[2*(
																 POSITIVE_MODE(ix1,mrc->HeaderN.x/2+1)
																+POSITIVE_MODE(iy1+mrc->HeaderN.y/2,mrc->HeaderN.y)*(mrc->HeaderN.x/2+1)
																+POSITIVE_MODE(iz0+mrc->HeaderN.z/2,mrc->HeaderN.z)*(mrc->HeaderN.x/2+1)*(mrc->HeaderN.y))]
							      + (ix1 -  xx)*(iy1 -  yy)*(  zz -iz0)*mrc->ImageFloatImage[2*(
																 POSITIVE_MODE(ix0,mrc->HeaderN.x/2+1)
																+POSITIVE_MODE(iy0+mrc->HeaderN.y/2,mrc->HeaderN.y)*(mrc->HeaderN.x/2+1)
																+POSITIVE_MODE(iz1+mrc->HeaderN.z/2,mrc->HeaderN.z)*(mrc->HeaderN.x/2+1)*(mrc->HeaderN.y))]
								  + (ix1 -  xx)*(  yy -iy0)*(  zz -iz0)*mrc->ImageFloatImage[2*(
																 POSITIVE_MODE(ix0,mrc->HeaderN.x/2+1)
																+POSITIVE_MODE(iy1+mrc->HeaderN.y/2,mrc->HeaderN.y)*(mrc->HeaderN.x/2+1)
																+POSITIVE_MODE(iz1+mrc->HeaderN.z/2,mrc->HeaderN.z)*(mrc->HeaderN.x/2+1)*(mrc->HeaderN.y))]
								  + (  xx -ix0)*(iy1 -  yy)*(  zz -iz0)*mrc->ImageFloatImage[2*(
																 POSITIVE_MODE(ix1,mrc->HeaderN.x/2+1)
																+POSITIVE_MODE(iy0+mrc->HeaderN.y/2,mrc->HeaderN.y)*(mrc->HeaderN.x/2+1)
																+POSITIVE_MODE(iz1+mrc->HeaderN.z/2,mrc->HeaderN.z)*(mrc->HeaderN.x/2+1)*(mrc->HeaderN.y))]
								  + (  xx -ix0)*(  yy -iy0)*(  zz -iz0)*mrc->ImageFloatImage[2*(
																 POSITIVE_MODE(ix1,mrc->HeaderN.x/2+1)
																+POSITIVE_MODE(iy1+mrc->HeaderN.y/2,mrc->HeaderN.y)*(mrc->HeaderN.x/2+1)
																+POSITIVE_MODE(iz1+mrc->HeaderN.z/2,mrc->HeaderN.z)*(mrc->HeaderN.x/2+1)*(mrc->HeaderN.y))];
								DEBUGPRINT3("Re(x,y,z):    %f %f %f\n", xx, yy, zz);	
								DEBUGPRINT3("Re(x0,y0,z0): %d %d %d\n", ix0, iy0, iz0);	
								DEBUGPRINT3("Re(x1,y1,z1): %d %d %d\n", ix1, iy1, iz1);	
								
								DEBUGPRINT4("Re: %f %f %f %f\n", mrc->ImageFloatImage[2*(
								 								 POSITIVE_MODE(ix0,mrc->HeaderN.x/2+1)
								  								+POSITIVE_MODE(iy0+mrc->HeaderN.y/2,mrc->HeaderN.y)*(mrc->HeaderN.x/2+1)
								   								+POSITIVE_MODE(iz0+mrc->HeaderN.z/2,mrc->HeaderN.z)*(mrc->HeaderN.x/2+1)*(mrc->HeaderN.y))],
														   mrc->ImageFloatImage[2*(
								 								 POSITIVE_MODE(ix1,mrc->HeaderN.x/2+1)
								  								+POSITIVE_MODE(iy0+mrc->HeaderN.y/2,mrc->HeaderN.y)*(mrc->HeaderN.x/2+1)
								   								+POSITIVE_MODE(iz0+mrc->HeaderN.z/2,mrc->HeaderN.z)*(mrc->HeaderN.x/2+1)*(mrc->HeaderN.y))],
														   mrc->ImageFloatImage[2*(
								 								 POSITIVE_MODE(ix1,mrc->HeaderN.x/2+1)
								  								+POSITIVE_MODE(iy1+mrc->HeaderN.y/2,mrc->HeaderN.y)*(mrc->HeaderN.x/2+1)
								   								+POSITIVE_MODE(iz0+mrc->HeaderN.z/2,mrc->HeaderN.z)*(mrc->HeaderN.x/2+1)*(mrc->HeaderN.y))],
														   mrc->ImageFloatImage[2*(
								 								 POSITIVE_MODE(ix0,mrc->HeaderN.x/2+1)
								  								+POSITIVE_MODE(iy1+mrc->HeaderN.y/2,mrc->HeaderN.y)*(mrc->HeaderN.x/2+1)
								   								+POSITIVE_MODE(iz0+mrc->HeaderN.z/2,mrc->HeaderN.z)*(mrc->HeaderN.x/2+1)*(mrc->HeaderN.y))]);
								DEBUGPRINT4("Re: %f %f %f %f\n", mrc->ImageFloatImage[2*(
								 								 POSITIVE_MODE(ix0,mrc->HeaderN.x/2+1)
								  								+POSITIVE_MODE(iy0+mrc->HeaderN.y/2,mrc->HeaderN.y)*(mrc->HeaderN.x/2+1)
								   								+POSITIVE_MODE(iz1+mrc->HeaderN.z/2,mrc->HeaderN.z)*(mrc->HeaderN.x/2+1)*(mrc->HeaderN.y))],
														   mrc->ImageFloatImage[2*(
								 								 POSITIVE_MODE(ix1,mrc->HeaderN.x/2+1)
								  								+POSITIVE_MODE(iy0+mrc->HeaderN.y/2,mrc->HeaderN.y)*(mrc->HeaderN.x/2+1)
								   								+POSITIVE_MODE(iz1+mrc->HeaderN.z/2,mrc->HeaderN.z)*(mrc->HeaderN.x/2+1)*(mrc->HeaderN.y))],
														   mrc->ImageFloatImage[2*(
								 								 POSITIVE_MODE(ix1,mrc->HeaderN.x/2+1)
								  								+POSITIVE_MODE(iy1+mrc->HeaderN.y/2,mrc->HeaderN.y)*(mrc->HeaderN.x/2+1)
								   								+POSITIVE_MODE(iz1+mrc->HeaderN.z/2,mrc->HeaderN.z)*(mrc->HeaderN.x/2+1)*(mrc->HeaderN.y))],
														   mrc->ImageFloatImage[2*(
								 								 POSITIVE_MODE(ix0,mrc->HeaderN.x/2+1)
								  								+POSITIVE_MODE(iy1+mrc->HeaderN.y/2,mrc->HeaderN.y)*(mrc->HeaderN.x/2+1)
								   								+POSITIVE_MODE(iz1+mrc->HeaderN.z/2,mrc->HeaderN.z)*(mrc->HeaderN.x/2+1)*(mrc->HeaderN.y))]);
								DEBUGPRINT1("Re: %f\n", *data);
							}
							break;
						}
						case mrcComplexDoubleFT: {
							if(sig==0) {
								*data = 0;
							} else {
							*data = (ix1 -  xx)*(iy1 -  yy)*(iz1 -  zz)*mrc->ImageDoubleImage[2*(
											 		 			 POSITIVE_MODE(ix0,mrc->HeaderN.x/2+1)
																+POSITIVE_MODE(iy0+mrc->HeaderN.y/2,mrc->HeaderN.y)*(mrc->HeaderN.x/2+1)
																+POSITIVE_MODE(iz0+mrc->HeaderN.z/2,mrc->HeaderN.z)*(mrc->HeaderN.x/2+1)*(mrc->HeaderN.y))]
								  + (ix1 -  xx)*(  yy -iy0)*(iz1 -  zz)*mrc->ImageDoubleImage[2*(
																 POSITIVE_MODE(ix0,mrc->HeaderN.x/2+1)
																+POSITIVE_MODE(iy1+mrc->HeaderN.y/2,mrc->HeaderN.y)*(mrc->HeaderN.x/2+1)
																+POSITIVE_MODE(iz0+mrc->HeaderN.z/2,mrc->HeaderN.z)*(mrc->HeaderN.x/2+1)*(mrc->HeaderN.y))]
								  + (  xx -ix0)*(iy1 -  yy)*(iz1 -  zz)*mrc->ImageDoubleImage[2*(
																 POSITIVE_MODE(ix1,mrc->HeaderN.x/2+1)
																+POSITIVE_MODE(iy0+mrc->HeaderN.y/2,mrc->HeaderN.y)*(mrc->HeaderN.x/2+1)
																+POSITIVE_MODE(iz0+mrc->HeaderN.z/2,mrc->HeaderN.z)*(mrc->HeaderN.x/2+1)*(mrc->HeaderN.y))]
								  + (  xx -ix0)*(  yy -iy0)*(iz1 -  zz)*mrc->ImageDoubleImage[2*(
																 POSITIVE_MODE(ix1,mrc->HeaderN.x/2+1)
																+POSITIVE_MODE(iy1+mrc->HeaderN.y/2,mrc->HeaderN.y)*(mrc->HeaderN.x/2+1)
																+POSITIVE_MODE(iz0+mrc->HeaderN.z/2,mrc->HeaderN.z)*(mrc->HeaderN.x/2+1)*(mrc->HeaderN.y))]
							      + (ix1 -  xx)*(iy1 -  yy)*(  zz -iz0)*mrc->ImageDoubleImage[2*(
																 POSITIVE_MODE(ix0,mrc->HeaderN.x/2+1)
																+POSITIVE_MODE(iy0+mrc->HeaderN.y/2,mrc->HeaderN.y)*(mrc->HeaderN.x/2+1)
																+POSITIVE_MODE(iz1+mrc->HeaderN.z/2,mrc->HeaderN.z)*(mrc->HeaderN.x/2+1)*(mrc->HeaderN.y))]
								  + (ix1 -  xx)*(  yy -iy0)*(  zz -iz0)*mrc->ImageDoubleImage[2*(
																 POSITIVE_MODE(ix0,mrc->HeaderN.x/2+1)
																+POSITIVE_MODE(iy1+mrc->HeaderN.y/2,mrc->HeaderN.y)*(mrc->HeaderN.x/2+1)
																+POSITIVE_MODE(iz1+mrc->HeaderN.z/2,mrc->HeaderN.z)*(mrc->HeaderN.x/2+1)*(mrc->HeaderN.y))]
								  + (  xx -ix0)*(iy1 -  yy)*(  zz -iz0)*mrc->ImageDoubleImage[2*(
																 POSITIVE_MODE(ix1,mrc->HeaderN.x/2+1)
																+POSITIVE_MODE(iy0+mrc->HeaderN.y/2,mrc->HeaderN.y)*(mrc->HeaderN.x/2+1)
																+POSITIVE_MODE(iz1+mrc->HeaderN.z/2,mrc->HeaderN.z)*(mrc->HeaderN.x/2+1)*(mrc->HeaderN.y))]
								  + (  xx -ix0)*(  yy -iy0)*(  zz -iz0)*mrc->ImageDoubleImage[2*(
																 POSITIVE_MODE(ix1,mrc->HeaderN.x/2+1)
																+POSITIVE_MODE(iy1+mrc->HeaderN.y/2,mrc->HeaderN.y)*(mrc->HeaderN.x/2+1)
																+POSITIVE_MODE(iz1+mrc->HeaderN.z/2,mrc->HeaderN.z)*(mrc->HeaderN.x/2+1)*(mrc->HeaderN.y))];
							}
							break;
						}
						default: {
						    sprintf(s, "mrcImage Mode %ld ::", mrc->HeaderMode);
			                mrcError(RTN_NAME, "mrcPixelRePart", s, 
							     mrcStatusMask_ExitFailure|MRC_ModeNotSupported);
                        }
					}
					break;
				}
				case mrcPixelImPart: {
					switch(mrc->HeaderMode) {
						case mrcComplexFloatFT: {
							if(sig==0) {
							*data = 0;
							} else {
							*data = (ix1 -  xx)*(iy1 -  yy)*(iz1 -  zz)*mrc->ImageFloatImage[2*(
											 		 			 POSITIVE_MODE(ix0,mrc->HeaderN.x/2+1)
																+POSITIVE_MODE(iy0+mrc->HeaderN.y/2,mrc->HeaderN.y)*(mrc->HeaderN.x/2+1)
																+POSITIVE_MODE(iz0+mrc->HeaderN.z/2,mrc->HeaderN.z)*(mrc->HeaderN.x/2+1)*(mrc->HeaderN.y))+1]
								  + (ix1 -  xx)*(  yy -iy0)*(iz1 -  zz)*mrc->ImageFloatImage[2*(
																 POSITIVE_MODE(ix0,mrc->HeaderN.x/2+1)
																+POSITIVE_MODE(iy1+mrc->HeaderN.y/2,mrc->HeaderN.y)*(mrc->HeaderN.x/2+1)
																+POSITIVE_MODE(iz0+mrc->HeaderN.z/2,mrc->HeaderN.z)*(mrc->HeaderN.x/2+1)*(mrc->HeaderN.y))+1]
								  + (  xx -ix0)*(iy1 -  yy)*(iz1 -  zz)*mrc->ImageFloatImage[2*(
																 POSITIVE_MODE(ix1,mrc->HeaderN.x/2+1)
																+POSITIVE_MODE(iy0+mrc->HeaderN.y/2,mrc->HeaderN.y)*(mrc->HeaderN.x/2+1)
																+POSITIVE_MODE(iz0+mrc->HeaderN.z/2,mrc->HeaderN.z)*(mrc->HeaderN.x/2+1)*(mrc->HeaderN.y))+1]
								  + (  xx -ix0)*(  yy -iy0)*(iz1 -  zz)*mrc->ImageFloatImage[2*(
																 POSITIVE_MODE(ix1,mrc->HeaderN.x/2+1)
																+POSITIVE_MODE(iy1+mrc->HeaderN.y/2,mrc->HeaderN.y)*(mrc->HeaderN.x/2+1)
																+POSITIVE_MODE(iz0+mrc->HeaderN.z/2,mrc->HeaderN.z)*(mrc->HeaderN.x/2+1)*(mrc->HeaderN.y))+1]
							      + (ix1 -  xx)*(iy1 -  yy)*(  zz -iz0)*mrc->ImageFloatImage[2*(
																 POSITIVE_MODE(ix0,mrc->HeaderN.x/2+1)
																+POSITIVE_MODE(iy0+mrc->HeaderN.y/2,mrc->HeaderN.y)*(mrc->HeaderN.x/2+1)
																+POSITIVE_MODE(iz1+mrc->HeaderN.z/2,mrc->HeaderN.z)*(mrc->HeaderN.x/2+1)*(mrc->HeaderN.y))+1]
								  + (ix1 -  xx)*(  yy -iy0)*(  zz -iz0)*mrc->ImageFloatImage[2*(
																 POSITIVE_MODE(ix0,mrc->HeaderN.x/2+1)
																+POSITIVE_MODE(iy1+mrc->HeaderN.y/2,mrc->HeaderN.y)*(mrc->HeaderN.x/2+1)
																+POSITIVE_MODE(iz1+mrc->HeaderN.z/2,mrc->HeaderN.z)*(mrc->HeaderN.x/2+1)*(mrc->HeaderN.y))+1]
								  + (  xx -ix0)*(iy1 -  yy)*(  zz -iz0)*mrc->ImageFloatImage[2*(
																 POSITIVE_MODE(ix1,mrc->HeaderN.x/2+1)
																+POSITIVE_MODE(iy0+mrc->HeaderN.y/2,mrc->HeaderN.y)*(mrc->HeaderN.x/2+1)
																+POSITIVE_MODE(iz1+mrc->HeaderN.z/2,mrc->HeaderN.z)*(mrc->HeaderN.x/2+1)*(mrc->HeaderN.y))+1]
								  + (  xx -ix0)*(  yy -iy0)*(  zz -iz0)*mrc->ImageFloatImage[2*(
																 POSITIVE_MODE(ix1,mrc->HeaderN.x/2+1)
																+POSITIVE_MODE(iy1+mrc->HeaderN.y/2,mrc->HeaderN.y)*(mrc->HeaderN.x/2+1)
																+POSITIVE_MODE(iz1+mrc->HeaderN.z/2,mrc->HeaderN.z)*(mrc->HeaderN.x/2+1)*(mrc->HeaderN.y))+1];

								DEBUGPRINT2("Im: %f %f\n", mrc->ImageFloatImage[2*(
								 								 POSITIVE_MODE(ix0,mrc->HeaderN.x/2+1)
								  								+POSITIVE_MODE(iy0+mrc->HeaderN.y/2,mrc->HeaderN.y)*(mrc->HeaderN.x/2+1)
								   								+POSITIVE_MODE(iz0+mrc->HeaderN.z/2,mrc->HeaderN.z)*(mrc->HeaderN.x/2+1)*(mrc->HeaderN.y))+1],
														   mrc->ImageFloatImage[2*(
								 								 POSITIVE_MODE(ix1,mrc->HeaderN.x/2+1)
								  								+POSITIVE_MODE(iy0+mrc->HeaderN.y/2,mrc->HeaderN.y)*(mrc->HeaderN.x/2+1)
								   								+POSITIVE_MODE(iz0+mrc->HeaderN.z/2,mrc->HeaderN.z)*(mrc->HeaderN.x/2+1)*(mrc->HeaderN.y))+1]);
							*data = (*data)*sig;
							}
							break;
						}
						case mrcComplexDoubleFT: {
							if(sig==0) {
							*data = 0;
							} else {
							*data = (ix1 -  xx)*(iy1 -  yy)*(iz1 -  zz)*mrc->ImageDoubleImage[2*(
											 		 			 POSITIVE_MODE(ix0,mrc->HeaderN.x/2+1)
																+POSITIVE_MODE(iy0+mrc->HeaderN.y/2,mrc->HeaderN.y)*(mrc->HeaderN.x/2+1)
																+POSITIVE_MODE(iz0+mrc->HeaderN.z/2,mrc->HeaderN.z)*(mrc->HeaderN.x/2+1)*(mrc->HeaderN.y))+1]
								  + (ix1 -  xx)*(  yy -iy0)*(iz1 -  zz)*mrc->ImageDoubleImage[2*(
																 POSITIVE_MODE(ix0,mrc->HeaderN.x/2+1)
																+POSITIVE_MODE(iy1+mrc->HeaderN.y/2,mrc->HeaderN.y)*(mrc->HeaderN.x/2+1)
																+POSITIVE_MODE(iz0+mrc->HeaderN.z/2,mrc->HeaderN.z)*(mrc->HeaderN.x/2+1)*(mrc->HeaderN.y))+1]
								  + (  xx -ix0)*(iy1 -  yy)*(iz1 -  zz)*mrc->ImageDoubleImage[2*(
																 POSITIVE_MODE(ix1,mrc->HeaderN.x/2+1)
																+POSITIVE_MODE(iy0+mrc->HeaderN.y/2,mrc->HeaderN.y)*(mrc->HeaderN.x/2+1)
																+POSITIVE_MODE(iz0+mrc->HeaderN.z/2,mrc->HeaderN.z)*(mrc->HeaderN.x/2+1)*(mrc->HeaderN.y))+1]
								  + (  xx -ix0)*(  yy -iy0)*(iz1 -  zz)*mrc->ImageDoubleImage[2*(
																 POSITIVE_MODE(ix1,mrc->HeaderN.x/2+1)
																+POSITIVE_MODE(iy1+mrc->HeaderN.y/2,mrc->HeaderN.y)*(mrc->HeaderN.x/2+1)
																+POSITIVE_MODE(iz0+mrc->HeaderN.z/2,mrc->HeaderN.z)*(mrc->HeaderN.x/2+1)*(mrc->HeaderN.y))+1]
							      + (ix1 -  xx)*(iy1 -  yy)*(  zz -iz0)*mrc->ImageDoubleImage[2*(
																 POSITIVE_MODE(ix0,mrc->HeaderN.x/2+1)
																+POSITIVE_MODE(iy0+mrc->HeaderN.y/2,mrc->HeaderN.y)*(mrc->HeaderN.x/2+1)
																+POSITIVE_MODE(iz1+mrc->HeaderN.z/2,mrc->HeaderN.z)*(mrc->HeaderN.x/2+1)*(mrc->HeaderN.y))+1]
								  + (ix1 -  xx)*(  yy -iy0)*(  zz -iz0)*mrc->ImageDoubleImage[2*(
																 POSITIVE_MODE(ix0,mrc->HeaderN.x/2+1)
																+POSITIVE_MODE(iy1+mrc->HeaderN.y/2,mrc->HeaderN.y)*(mrc->HeaderN.x/2+1)
																+POSITIVE_MODE(iz1+mrc->HeaderN.z/2,mrc->HeaderN.z)*(mrc->HeaderN.x/2+1)*(mrc->HeaderN.y))+1]
								  + (  xx -ix0)*(iy1 -  yy)*(  zz -iz0)*mrc->ImageDoubleImage[2*(
																 POSITIVE_MODE(ix1,mrc->HeaderN.x/2+1)
																+POSITIVE_MODE(iy0+mrc->HeaderN.y/2,mrc->HeaderN.y)*(mrc->HeaderN.x/2+1)
																+POSITIVE_MODE(iz1+mrc->HeaderN.z/2,mrc->HeaderN.z)*(mrc->HeaderN.x/2+1)*(mrc->HeaderN.y))+1]
								  + (  xx -ix0)*(  yy -iy0)*(  zz -iz0)*mrc->ImageDoubleImage[2*(
																 POSITIVE_MODE(ix1,mrc->HeaderN.x/2+1)
																+POSITIVE_MODE(iy1+mrc->HeaderN.y/2,mrc->HeaderN.y)*(mrc->HeaderN.x/2+1)
																+POSITIVE_MODE(iz1+mrc->HeaderN.z/2,mrc->HeaderN.z)*(mrc->HeaderN.x/2+1)*(mrc->HeaderN.y))+1];
							*data = (*data)*sig;
							}
							break;
						}
						default: {
						    sprintf(s, "mrcImage Mode %ld ::", mrc->HeaderMode);
			                mrcError(RTN_NAME, "mrcPixelRePart", s, 
							     mrcStatusMask_ExitFailure|MRC_ModeNotSupported);
							break;
                        }
					}
					break;
				}
				default: {
					sprintf(s, "mrcPixelType %d", mode);
					mrcError(RTN_NAME, "Pixel Data Type", s, 
						 mrcStatusMask_ExitFailure|MRC_ModeNotSupported);
					break;
				}
			}
			break;
		}
        case mrcPixelHowCubicConv: {
	    double imagedata;
	    long int xl, yl ,zl;
	    long  int xmin, xmax, ymin, ymax ,zmin ,zmax;
	    double dx, dy ,dz;
	    long nx,ny,nz; 

	    /*
			ix = (int)x;
			iy = (int)y;
			iz = (int)z;
	    */
			switch(mode) {
				case mrcPixelRePart: {
					switch(mrc->HeaderMode) {
						case mrcShortImage: {
						  nx=mrc->HeaderN.x;
						  ny=mrc->HeaderN.y;
						  nz=mrc->HeaderN.z;
					  
						  xmin = (int)(x-3.0);
						  xmax = (int)(x+3.0);
						  ymin = (int)(y-3.0);
						  ymax = (int)(y+3.0);
						  if (nz == 1){
						    zmin = 0;
						    zmax = 0;
						  } else {
						    zmin = (int)(z-3.0);
						    zmax = (int)(z+3.0);
						  }
						  *data = 0.0;
						  for(xl=xmin; xl<=xmax; xl++) {
						    for(yl=ymin; yl<=ymax; yl++) {
						      for(zl=zmin; zl<=zmax; zl++) {
							dx = fabs(x-xl);
							dy = fabs(y-yl);
							dz = fabs(z-zl);

							imagedata = mrc->ImageShortImage[
											 POSITIVE_MODE(xl,mrc->HeaderN.x)
											 +POSITIVE_MODE(yl,mrc->HeaderN.y)*mrc->HeaderN.x
											 +POSITIVE_MODE(zl,mrc->HeaderN.z)*mrc->HeaderN.x*mrc->HeaderN.y] ;
							if(dx>=2.0 || dy>=2.0 || dz>=2.0) {
							    ;
							} else if(dx>=1.0 && dy>=1.0 && dz>=1.0 ) {
							  *data += ((4.0-8.0*dx+5.0*dx*dx-dx*dx*dx)
								    *(4.0-8.0*dy+5.0*dy*dy-dy*dy*dy)
								    *(4.0-8.0*dz+5.0*dz*dz-dz*dz*dz)
								    *imagedata);

							} else if(dx>=1.0 && dy>=1.0 && dz<1.0) {
							  *data += ((4.0-8.0*dx+5.0*dx*dx-dx*dx*dx)
								    *(4.0-8.0*dy+5.0*dy*dy-dy*dy*dy)
								    *(1.0-2.0*dz*dz+dz*dz*dz)
								    *imagedata);
						      
							} else if(dx>=1.0 && dy<1.0 && dz>=1.0) {
							  *data += ((4.0-8.0*dx+5.0*dx*dx-dx*dx*dx)
								    *(1.0-2.0*dy*dy+dy*dy*dy)
								    *(4.0-8.0*dz+5.0*dz*dz-dz*dz*dz)  
								    *imagedata);

							} else if(dx>=1.0 && dy<1.0 && dz<1.0) {
							  *data += ((4.0-8.0*dx+5.0*dx*dx-dx*dx*dx)
								    *(1.0-2.0*dy*dy+dy*dy*dy)
								    *(1.0-2.0*dz*dz+dz*dz*dz)
								    *imagedata);

							} else if(dx<1.0 && dy>=1.0 && dz>=1.0) {
							  *data += ((4.0-8.0*dy+5.0*dy*dy-dy*dy*dy)
								    *(1.0-2.0*dx*dx+dx*dx*dx)
								    *(4.0-8.0*dz+5.0*dz*dz-dz*dz*dz) 
								    *imagedata);

							} else if(dx<1.0 && dy>=1.0 && dz<1.0) {
							  *data += ((4.0-8.0*dy+5.0*dy*dy-dy*dy*dy)
								    *(1.0-2.0*dx*dx+dx*dx*dx)
								    *(1.0-2.0*dz*dz+dz*dz*dz)
								    *imagedata);

							} else if(dx<1.0 && dy<1.0 && dz>=1.0) {
							  *data += ((1.0-2.0*dx*dx+dx*dx*dx)
								    *(1.0-2.0*dy*dy+dy*dy*dy)
								    *(4.0-8.0*dz+5.0*dz*dz-dz*dz*dz) 
								    *imagedata);

							} else if(dx<1.0 && dy<1.0 && dz<1.0) {
							  *data += ((1.0-2.0*dx*dx+dx*dx*dx)
								    *(1.0-2.0*dy*dy+dy*dy*dy)
								    *(1.0-2.0*dz*dz+dz*dz*dz)
								    *imagedata);

							} else {
							  fprintf(stderr, "That's stupid!\n!");
							}
						      }
						    }
						  }
							break;
						}

						case mrcUShortImage: {
						  nx=mrc->HeaderN.x;
						  ny=mrc->HeaderN.y;
						  nz=mrc->HeaderN.z;
					  
						  xmin = (int)(x-3.0);
						  xmax = (int)(x+3.0);
						  ymin = (int)(y-3.0);
						  ymax = (int)(y+3.0);
						  if (nz == 1){
						    zmin = 0;
						    zmax = 0;
						  } else {
						    zmin = (int)(z-3.0);
						    zmax = (int)(z+3.0);
						  }
						  *data = 0.0;
						  for(xl=xmin; xl<=xmax; xl++) {
						    for(yl=ymin; yl<=ymax; yl++) {
						      for(zl=zmin; zl<=zmax; zl++) {
							dx = fabs(x-xl);
							dy = fabs(y-yl);
							dz = fabs(z-zl);

							imagedata = (unsigned short)mrc->ImageShortImage[
											 POSITIVE_MODE(xl,mrc->HeaderN.x)
											 +POSITIVE_MODE(yl,mrc->HeaderN.y)*mrc->HeaderN.x
											 +POSITIVE_MODE(zl,mrc->HeaderN.z)*mrc->HeaderN.x*mrc->HeaderN.y] ;
							if(dx>=2.0 || dy>=2.0 || dz>=2.0) {
							  ;
							} else if(dx>=1.0 && dy>=1.0 && dz>=1.0 ) {
							  *data += ((4.0-8.0*dx+5.0*dx*dx-dx*dx*dx)
								    *(4.0-8.0*dy+5.0*dy*dy-dy*dy*dy)
								    *(4.0-8.0*dz+5.0*dz*dz-dz*dz*dz)
								    *imagedata);

							} else if(dx>=1.0 && dy>=1.0 && dz<1.0) {
							  *data += ((4.0-8.0*dx+5.0*dx*dx-dx*dx*dx)
								    *(4.0-8.0*dy+5.0*dy*dy-dy*dy*dy)
								    *(1.0-2.0*dz*dz+dz*dz*dz)
								    *imagedata);
						      
							} else if(dx>=1.0 && dy<1.0 && dz>=1.0) {
							  *data += ((4.0-8.0*dx+5.0*dx*dx-dx*dx*dx)
								    *(1.0-2.0*dy*dy+dy*dy*dy)
								    *(4.0-8.0*dz+5.0*dz*dz-dz*dz*dz)  
								    *imagedata);

							} else if(dx>=1.0 && dy<1.0 && dz<1.0) {
							  *data += ((4.0-8.0*dx+5.0*dx*dx-dx*dx*dx)
								    *(1.0-2.0*dy*dy+dy*dy*dy)
								    *(1.0-2.0*dz*dz+dz*dz*dz)
								    *imagedata);

							} else if(dx<1.0 && dy>=1.0 && dz>=1.0) {
							  *data += ((4.0-8.0*dy+5.0*dy*dy-dy*dy*dy)
								    *(1.0-2.0*dx*dx+dx*dx*dx)
								    *(4.0-8.0*dz+5.0*dz*dz-dz*dz*dz) 
								    *imagedata);

							} else if(dx<1.0 && dy>=1.0 && dz<1.0) {
							  *data += ((4.0-8.0*dy+5.0*dy*dy-dy*dy*dy)
								    *(1.0-2.0*dx*dx+dx*dx*dx)
								    *(1.0-2.0*dz*dz+dz*dz*dz)
								    *imagedata);

							} else if(dx<1.0 && dy<1.0 && dz>=1.0) {
							  *data += ((1.0-2.0*dx*dx+dx*dx*dx)
								    *(1.0-2.0*dy*dy+dy*dy*dy)
								    *(4.0-8.0*dz+5.0*dz*dz-dz*dz*dz) 
								    *imagedata);

							} else if(dx<1.0 && dy<1.0 && dz<1.0) {
							  *data += ((1.0-2.0*dx*dx+dx*dx*dx)
								    *(1.0-2.0*dy*dy+dy*dy*dy)
								    *(1.0-2.0*dz*dz+dz*dz*dz)
								    *imagedata);

							} else {
							  fprintf(stderr, "That's stupid!\n!");
							}
						      }
						    }
						  }
							break;
						}

						case mrcFloatImage: {
						  nx=mrc->HeaderN.x;
						  ny=mrc->HeaderN.y;
						  nz=mrc->HeaderN.z;
					  
						  xmin = (int)(x-3.0);
						  xmax = (int)(x+3.0);
						  ymin = (int)(y-3.0);
						  ymax = (int)(y+3.0);
						  if (nz == 1){
						    zmin = 0;
						    zmax = 0;
						  } else {
						    zmin = (int)(z-3.0);
						    zmax = (int)(z+3.0);
						  }
						  *data = 0.0;
						  for(xl=xmin; xl<=xmax; xl++) {
						    for(yl=ymin; yl<=ymax; yl++) {
						      for(zl=zmin; zl<=zmax; zl++) {
							dx = fabs(x-xl);
							dy = fabs(y-yl);
							dz = fabs(z-zl);

							imagedata = mrc->ImageFloatImage[
											 POSITIVE_MODE(xl,mrc->HeaderN.x)
											 +POSITIVE_MODE(yl,mrc->HeaderN.y)*mrc->HeaderN.x
											 +POSITIVE_MODE(zl,mrc->HeaderN.z)*mrc->HeaderN.x*mrc->HeaderN.y] ;
							if(dx>=2.0 || dy>=2.0 || dz>=2.0) {
							  *data += 0.0;
							} else if(dx>=1.0 && dy>=1.0 && dz>=1.0 ) {
							  *data += ((4.0-8.0*dx+5.0*dx*dx-dx*dx*dx)
								    *(4.0-8.0*dy+5.0*dy*dy-dy*dy*dy)
								    *(4.0-8.0*dz+5.0*dz*dz-dz*dz*dz)
								    *imagedata);

							} else if(dx>=1.0 && dy>=1.0 && dz<1.0) {
							  *data += ((4.0-8.0*dx+5.0*dx*dx-dx*dx*dx)
								    *(4.0-8.0*dy+5.0*dy*dy-dy*dy*dy)
								    *(1.0-2.0*dz*dz+dz*dz*dz)
								    *imagedata);
						      
							} else if(dx>=1.0 && dy<1.0 && dz>=1.0) {
							  *data += ((4.0-8.0*dx+5.0*dx*dx-dx*dx*dx)
								    *(1.0-2.0*dy*dy+dy*dy*dy)
								    *(4.0-8.0*dz+5.0*dz*dz-dz*dz*dz)  
								    *imagedata);

							} else if(dx>=1.0 && dy<1.0 && dz<1.0) {
							  *data += ((4.0-8.0*dx+5.0*dx*dx-dx*dx*dx)
								    *(1.0-2.0*dy*dy+dy*dy*dy)
								    *(1.0-2.0*dz*dz+dz*dz*dz)
								    *imagedata);

							} else if(dx<1.0 && dy>=1.0 && dz>=1.0) {
							  *data += ((4.0-8.0*dy+5.0*dy*dy-dy*dy*dy)
								    *(1.0-2.0*dx*dx+dx*dx*dx)
								    *(4.0-8.0*dz+5.0*dz*dz-dz*dz*dz) 
								    *imagedata);

							} else if(dx<1.0 && dy>=1.0 && dz<1.0) {
							  *data += ((4.0-8.0*dy+5.0*dy*dy-dy*dy*dy)
								    *(1.0-2.0*dx*dx+dx*dx*dx)
								    *(1.0-2.0*dz*dz+dz*dz*dz)
								    *imagedata);

							} else if(dx<1.0 && dy<1.0 && dz>=1.0) {
							  *data += ((1.0-2.0*dx*dx+dx*dx*dx)
								    *(1.0-2.0*dy*dy+dy*dy*dy)
								    *(4.0-8.0*dz+5.0*dz*dz-dz*dz*dz) 
								    *imagedata);

							} else if(dx<1.0 && dy<1.0 && dz<1.0) {
							  *data += ((1.0-2.0*dx*dx+dx*dx*dx)
								    *(1.0-2.0*dy*dy+dy*dy*dy)
								    *(1.0-2.0*dz*dz+dz*dz*dz)
								    *imagedata);

							} else {
							  fprintf(stderr, "That's stupid!\n!");
							}
						      }
						    }
						  }
							break;
						}

						case mrcFloatRadonImage: {
						  nx=mrc->HeaderN.x;
						  ny=mrc->HeaderN.y;
						  nz=mrc->HeaderN.z;
					  
						  xmin = (int)(x-3.0);
						  xmax = (int)(x+3.0);

						  *data = 0.0;
						  for(xl=xmin; xl<=xmax; xl++) {
							dx = fabs(x-xl);

							imagedata = mrc->ImageFloatImage[
											 POSITIVE_MODE(xl,mrc->HeaderN.x)
											 +iy*mrc->HeaderN.x
											 +iz*mrc->HeaderN.x*mrc->HeaderN.y];
							if(dx>=2.0) {
							  *data += 0.0;
							} else if(dx>=1.0) {
							  *data += ((4.0-8.0*dx+5.0*dx*dx-dx*dx*dx)*imagedata);
							} else if(dx<1.0) {
							  *data += ((1.0-2.0*dx*dx+dx*dx*dx)*imagedata);
							} else {
							  fprintf(stderr, "That's stupid!\n!");
							}
						  }
						  break;
						}

						case mrcDoubleImage: {
						  nx=mrc->HeaderN.x;
						  ny=mrc->HeaderN.y;
						  nz=mrc->HeaderN.z;
					  
						  xmin = (int)(x-3.0);
						  xmax = (int)(x+3.0);
						  ymin = (int)(y-3.0);
						  ymax = (int)(y+3.0);
						  if (nz == 1){
						    zmin = 0;
						    zmax = 0;
						  } else {
						    zmin = (int)(z-3.0);
						    zmax = (int)(z+3.0);
						  }
						  *data = 0.0;
						  for(xl=xmin; xl<=xmax; xl++) {
						    for(yl=ymin; yl<=ymax; yl++) {
						      for(zl=zmin; zl<=zmax; zl++) {
							dx = fabs(x-xl);
							dy = fabs(y-yl);
							dz = fabs(z-zl);

							imagedata = mrc->ImageDoubleImage[
											 POSITIVE_MODE(xl,mrc->HeaderN.x)
											 +POSITIVE_MODE(yl,mrc->HeaderN.y)*mrc->HeaderN.x
											 +POSITIVE_MODE(zl,mrc->HeaderN.z)*mrc->HeaderN.x*mrc->HeaderN.y] ;
							if(dx>=2.0 || dy>=2.0 || dz>=2.0) {
							  *data += 0.0;
							} else if(dx>=1.0 && dy>=1.0 && dz>=1.0 ) {
							  *data += ((4.0-8.0*dx+5.0*dx*dx-dx*dx*dx)
								    *(4.0-8.0*dy+5.0*dy*dy-dy*dy*dy)
								    *(4.0-8.0*dz+5.0*dz*dz-dz*dz*dz)
								    *imagedata);

							} else if(dx>=1.0 && dy>=1.0 && dz<1.0) {
							  *data += ((4.0-8.0*dx+5.0*dx*dx-dx*dx*dx)
								    *(4.0-8.0*dy+5.0*dy*dy-dy*dy*dy)
								    *(1.0-2.0*dz*dz+dz*dz*dz)
								    *imagedata);
						      
							} else if(dx>=1.0 && dy<1.0 && dz>=1.0) {
							  *data += ((4.0-8.0*dx+5.0*dx*dx-dx*dx*dx)
								    *(1.0-2.0*dy*dy+dy*dy*dy)
								    *(4.0-8.0*dz+5.0*dz*dz-dz*dz*dz)  
								    *imagedata);

							} else if(dx>=1.0 && dy<1.0 && dz<1.0) {
							  *data += ((4.0-8.0*dx+5.0*dx*dx-dx*dx*dx)
								    *(1.0-2.0*dy*dy+dy*dy*dy)
								    *(1.0-2.0*dz*dz+dz*dz*dz)
								    *imagedata);

							} else if(dx<1.0 && dy>=1.0 && dz>=1.0) {
							  *data += ((4.0-8.0*dy+5.0*dy*dy-dy*dy*dy)
								    *(1.0-2.0*dx*dx+dx*dx*dx)
								    *(4.0-8.0*dz+5.0*dz*dz-dz*dz*dz) 
								    *imagedata);

							} else if(dx<1.0 && dy>=1.0 && dz<1.0) {
							  *data += ((4.0-8.0*dy+5.0*dy*dy-dy*dy*dy)
								    *(1.0-2.0*dx*dx+dx*dx*dx)
								    *(1.0-2.0*dz*dz+dz*dz*dz)
								    *imagedata);

							} else if(dx<1.0 && dy<1.0 && dz>=1.0) {
							  *data += ((1.0-2.0*dx*dx+dx*dx*dx)
								    *(1.0-2.0*dy*dy+dy*dy*dy)
								    *(4.0-8.0*dz+5.0*dz*dz-dz*dz*dz) 
								    *imagedata);

							} else if(dx<1.0 && dy<1.0 && dz<1.0) {
							  *data += ((1.0-2.0*dx*dx+dx*dx*dx)
								    *(1.0-2.0*dy*dy+dy*dy*dy)
								    *(1.0-2.0*dz*dz+dz*dz*dz)
								    *imagedata);

							} else {
							  fprintf(stderr, "That's stupid!\n!");
							}
						      }
						    }
						  }
							break;
						}
						default: {
						    sprintf(s, "mrcImage Mode %ld", mrc->HeaderMode);
			                mrcError(RTN_NAME, "mrcPixelRePart", s, 
							     mrcStatusMask_ExitFailure|MRC_ModeNotSupported);
                        }
					}
					break;
				}
				default: {
					sprintf(s, "mrcPixelType %d", mode);
					mrcError(RTN_NAME, "Pixel Data Type", s, 
     						 mrcStatusMask_ExitFailure|MRC_ModeNotSupported);
					break;
				}
			}
			break;
		}
        case mrcPixelHowPolySig: {
			static int flagFirst = 1;
		    int m, n;
			double imagedata[16];	
    		static double coefficient[6];
    		static double matrix[6][6];
    		static double vec[6];
			m = (int)floor(x);	
			n = (int)floor(y);	
			switch(mrc->HeaderMode) {
				case mrcShortImage: {
					imagedata[0+0*4] = mrc->ImageShortImage[
						 POSITIVE_MODE(m-1,mrc->HeaderN.x)
						+POSITIVE_MODE(n-1,mrc->HeaderN.y)*mrc->HeaderN.x
						+POSITIVE_MODE(iz,mrc->HeaderN.z)*mrc->HeaderN.x*mrc->HeaderN.y] ;
					imagedata[1+0*4] = mrc->ImageShortImage[
						 POSITIVE_MODE(m,mrc->HeaderN.x)
						+POSITIVE_MODE(n-1,mrc->HeaderN.y)*mrc->HeaderN.x
						+POSITIVE_MODE(iz,mrc->HeaderN.z)*mrc->HeaderN.x*mrc->HeaderN.y] ;
					imagedata[2+0*4] = mrc->ImageShortImage[
						 POSITIVE_MODE(m+1,mrc->HeaderN.x)
						+POSITIVE_MODE(n-1,mrc->HeaderN.y)*mrc->HeaderN.x
						+POSITIVE_MODE(iz,mrc->HeaderN.z)*mrc->HeaderN.x*mrc->HeaderN.y] ;
					imagedata[3+0*4] = mrc->ImageShortImage[
						 POSITIVE_MODE(m+2,mrc->HeaderN.x)
						+POSITIVE_MODE(n-1,mrc->HeaderN.y)*mrc->HeaderN.x
						+POSITIVE_MODE(iz,mrc->HeaderN.z)*mrc->HeaderN.x*mrc->HeaderN.y] ;
					imagedata[0+1*4] = mrc->ImageShortImage[
						 POSITIVE_MODE(m-1,mrc->HeaderN.x)
						+POSITIVE_MODE(n,mrc->HeaderN.y)*mrc->HeaderN.x
						+POSITIVE_MODE(iz,mrc->HeaderN.z)*mrc->HeaderN.x*mrc->HeaderN.y] ;
					imagedata[1+1*4] = mrc->ImageShortImage[
						 POSITIVE_MODE(m,mrc->HeaderN.x)
						+POSITIVE_MODE(n,mrc->HeaderN.y)*mrc->HeaderN.x
						+POSITIVE_MODE(iz,mrc->HeaderN.z)*mrc->HeaderN.x*mrc->HeaderN.y] ;
					imagedata[2+1*4] = mrc->ImageShortImage[
						 POSITIVE_MODE(m+1,mrc->HeaderN.x)
						+POSITIVE_MODE(n,mrc->HeaderN.y)*mrc->HeaderN.x
						+POSITIVE_MODE(iz,mrc->HeaderN.z)*mrc->HeaderN.x*mrc->HeaderN.y] ;
					imagedata[3+1*4] = mrc->ImageShortImage[
						 POSITIVE_MODE(m+2,mrc->HeaderN.x)
						+POSITIVE_MODE(n,mrc->HeaderN.y)*mrc->HeaderN.x
						+POSITIVE_MODE(iz,mrc->HeaderN.z)*mrc->HeaderN.x*mrc->HeaderN.y] ;
					imagedata[0+2*4] = mrc->ImageShortImage[
						 POSITIVE_MODE(m-1,mrc->HeaderN.x)
						+POSITIVE_MODE(n+1,mrc->HeaderN.y)*mrc->HeaderN.x
						+POSITIVE_MODE(iz,mrc->HeaderN.z)*mrc->HeaderN.x*mrc->HeaderN.y] ;
					imagedata[1+2*4] = mrc->ImageShortImage[
						 POSITIVE_MODE(m,mrc->HeaderN.x)
						+POSITIVE_MODE(n+1,mrc->HeaderN.y)*mrc->HeaderN.x
						+POSITIVE_MODE(iz,mrc->HeaderN.z)*mrc->HeaderN.x*mrc->HeaderN.y] ;
					imagedata[2+2*4] = mrc->ImageShortImage[
						 POSITIVE_MODE(m+1,mrc->HeaderN.x)
						+POSITIVE_MODE(n+1,mrc->HeaderN.y)*mrc->HeaderN.x
						+POSITIVE_MODE(iz,mrc->HeaderN.z)*mrc->HeaderN.x*mrc->HeaderN.y] ;
					imagedata[3+2*4] = mrc->ImageShortImage[
						 POSITIVE_MODE(m+2,mrc->HeaderN.x)
						+POSITIVE_MODE(n+1,mrc->HeaderN.y)*mrc->HeaderN.x
						+POSITIVE_MODE(iz,mrc->HeaderN.z)*mrc->HeaderN.x*mrc->HeaderN.y] ;
					imagedata[0+3*4] = mrc->ImageShortImage[
						 POSITIVE_MODE(m-1,mrc->HeaderN.x)
						+POSITIVE_MODE(n+2,mrc->HeaderN.y)*mrc->HeaderN.x
						+POSITIVE_MODE(iz,mrc->HeaderN.z)*mrc->HeaderN.x*mrc->HeaderN.y] ;
					imagedata[1+3*4] = mrc->ImageShortImage[
						 POSITIVE_MODE(m,mrc->HeaderN.x)
						+POSITIVE_MODE(n+2,mrc->HeaderN.y)*mrc->HeaderN.x
						+POSITIVE_MODE(iz,mrc->HeaderN.z)*mrc->HeaderN.x*mrc->HeaderN.y] ;
					imagedata[2+3*4] = mrc->ImageShortImage[
						 POSITIVE_MODE(m+1,mrc->HeaderN.x)
						+POSITIVE_MODE(n+2,mrc->HeaderN.y)*mrc->HeaderN.x
						+POSITIVE_MODE(iz,mrc->HeaderN.z)*mrc->HeaderN.x*mrc->HeaderN.y] ;
					imagedata[3+3*4] = mrc->ImageShortImage[
						 POSITIVE_MODE(m+2,mrc->HeaderN.x)
						+POSITIVE_MODE(n+2,mrc->HeaderN.y)*mrc->HeaderN.x
						+POSITIVE_MODE(iz,mrc->HeaderN.z)*mrc->HeaderN.x*mrc->HeaderN.y] ;
					break;
				}
				case mrcUShortImage: {
					imagedata[0+0*4] = (unsigned short)mrc->ImageShortImage[
						 POSITIVE_MODE(m-1,mrc->HeaderN.x)
						+POSITIVE_MODE(n-1,mrc->HeaderN.y)*mrc->HeaderN.x
						+POSITIVE_MODE(iz,mrc->HeaderN.z)*mrc->HeaderN.x*mrc->HeaderN.y] ;
					imagedata[1+0*4] = (unsigned short)mrc->ImageShortImage[
						 POSITIVE_MODE(m,mrc->HeaderN.x)
						+POSITIVE_MODE(n-1,mrc->HeaderN.y)*mrc->HeaderN.x
						+POSITIVE_MODE(iz,mrc->HeaderN.z)*mrc->HeaderN.x*mrc->HeaderN.y] ;
					imagedata[2+0*4] = (unsigned short)mrc->ImageShortImage[
						 POSITIVE_MODE(m+1,mrc->HeaderN.x)
						+POSITIVE_MODE(n-1,mrc->HeaderN.y)*mrc->HeaderN.x
						+POSITIVE_MODE(iz,mrc->HeaderN.z)*mrc->HeaderN.x*mrc->HeaderN.y] ;
					imagedata[3+0*4] = (unsigned short)mrc->ImageShortImage[
						 POSITIVE_MODE(m+2,mrc->HeaderN.x)
						+POSITIVE_MODE(n-1,mrc->HeaderN.y)*mrc->HeaderN.x
						+POSITIVE_MODE(iz,mrc->HeaderN.z)*mrc->HeaderN.x*mrc->HeaderN.y] ;
					imagedata[0+1*4] = (unsigned short)mrc->ImageShortImage[
						 POSITIVE_MODE(m-1,mrc->HeaderN.x)
						+POSITIVE_MODE(n,mrc->HeaderN.y)*mrc->HeaderN.x
						+POSITIVE_MODE(iz,mrc->HeaderN.z)*mrc->HeaderN.x*mrc->HeaderN.y] ;
					imagedata[1+1*4] = (unsigned short)mrc->ImageShortImage[
						 POSITIVE_MODE(m,mrc->HeaderN.x)
						+POSITIVE_MODE(n,mrc->HeaderN.y)*mrc->HeaderN.x
						+POSITIVE_MODE(iz,mrc->HeaderN.z)*mrc->HeaderN.x*mrc->HeaderN.y] ;
					imagedata[2+1*4] = (unsigned short)mrc->ImageShortImage[
						 POSITIVE_MODE(m+1,mrc->HeaderN.x)
						+POSITIVE_MODE(n,mrc->HeaderN.y)*mrc->HeaderN.x
						+POSITIVE_MODE(iz,mrc->HeaderN.z)*mrc->HeaderN.x*mrc->HeaderN.y] ;
					imagedata[3+1*4] = (unsigned short)mrc->ImageShortImage[
						 POSITIVE_MODE(m+2,mrc->HeaderN.x)
						+POSITIVE_MODE(n,mrc->HeaderN.y)*mrc->HeaderN.x
						+POSITIVE_MODE(iz,mrc->HeaderN.z)*mrc->HeaderN.x*mrc->HeaderN.y] ;
					imagedata[0+2*4] = (unsigned short)mrc->ImageShortImage[
						 POSITIVE_MODE(m-1,mrc->HeaderN.x)
						+POSITIVE_MODE(n+1,mrc->HeaderN.y)*mrc->HeaderN.x
						+POSITIVE_MODE(iz,mrc->HeaderN.z)*mrc->HeaderN.x*mrc->HeaderN.y] ;
					imagedata[1+2*4] = (unsigned short)mrc->ImageShortImage[
						 POSITIVE_MODE(m,mrc->HeaderN.x)
						+POSITIVE_MODE(n+1,mrc->HeaderN.y)*mrc->HeaderN.x
						+POSITIVE_MODE(iz,mrc->HeaderN.z)*mrc->HeaderN.x*mrc->HeaderN.y] ;
					imagedata[2+2*4] = (unsigned short)mrc->ImageShortImage[
						 POSITIVE_MODE(m+1,mrc->HeaderN.x)
						+POSITIVE_MODE(n+1,mrc->HeaderN.y)*mrc->HeaderN.x
						+POSITIVE_MODE(iz,mrc->HeaderN.z)*mrc->HeaderN.x*mrc->HeaderN.y] ;
					imagedata[3+2*4] = (unsigned short)mrc->ImageShortImage[
						 POSITIVE_MODE(m+2,mrc->HeaderN.x)
						+POSITIVE_MODE(n+1,mrc->HeaderN.y)*mrc->HeaderN.x
						+POSITIVE_MODE(iz,mrc->HeaderN.z)*mrc->HeaderN.x*mrc->HeaderN.y] ;
					imagedata[0+3*4] = (unsigned short)mrc->ImageShortImage[
						 POSITIVE_MODE(m-1,mrc->HeaderN.x)
						+POSITIVE_MODE(n+2,mrc->HeaderN.y)*mrc->HeaderN.x
						+POSITIVE_MODE(iz,mrc->HeaderN.z)*mrc->HeaderN.x*mrc->HeaderN.y] ;
					imagedata[1+3*4] = (unsigned short)mrc->ImageShortImage[
						 POSITIVE_MODE(m,mrc->HeaderN.x)
						+POSITIVE_MODE(n+2,mrc->HeaderN.y)*mrc->HeaderN.x
						+POSITIVE_MODE(iz,mrc->HeaderN.z)*mrc->HeaderN.x*mrc->HeaderN.y] ;
					imagedata[2+3*4] = (unsigned short) mrc->ImageShortImage[
						 POSITIVE_MODE(m+1,mrc->HeaderN.x)
						+POSITIVE_MODE(n+2,mrc->HeaderN.y)*mrc->HeaderN.x
						+POSITIVE_MODE(iz,mrc->HeaderN.z)*mrc->HeaderN.x*mrc->HeaderN.y] ;
					imagedata[3+3*4] = (unsigned short)mrc->ImageShortImage[
						 POSITIVE_MODE(m+2,mrc->HeaderN.x)
						+POSITIVE_MODE(n+2,mrc->HeaderN.y)*mrc->HeaderN.x
						+POSITIVE_MODE(iz,mrc->HeaderN.z)*mrc->HeaderN.x*mrc->HeaderN.y] ;
					break;
				}
				case mrcFloatImage: {
					imagedata[0+0*4] = mrc->ImageFloatImage[
						 POSITIVE_MODE(m-1,mrc->HeaderN.x)
						+POSITIVE_MODE(n-1,mrc->HeaderN.y)*mrc->HeaderN.x
						+POSITIVE_MODE(iz,mrc->HeaderN.z)*mrc->HeaderN.x*mrc->HeaderN.y] ;
					imagedata[1+0*4] = mrc->ImageFloatImage[
						 POSITIVE_MODE(m,mrc->HeaderN.x)
						+POSITIVE_MODE(n-1,mrc->HeaderN.y)*mrc->HeaderN.x
						+POSITIVE_MODE(iz,mrc->HeaderN.z)*mrc->HeaderN.x*mrc->HeaderN.y] ;
					imagedata[2+0*4] = mrc->ImageFloatImage[
						 POSITIVE_MODE(m+1,mrc->HeaderN.x)
						+POSITIVE_MODE(n-1,mrc->HeaderN.y)*mrc->HeaderN.x
						+POSITIVE_MODE(iz,mrc->HeaderN.z)*mrc->HeaderN.x*mrc->HeaderN.y] ;
					imagedata[3+0*4] = mrc->ImageFloatImage[
						 POSITIVE_MODE(m+2,mrc->HeaderN.x)
						+POSITIVE_MODE(n-1,mrc->HeaderN.y)*mrc->HeaderN.x
						+POSITIVE_MODE(iz,mrc->HeaderN.z)*mrc->HeaderN.x*mrc->HeaderN.y] ;
					imagedata[0+1*4] = mrc->ImageFloatImage[
						 POSITIVE_MODE(m-1,mrc->HeaderN.x)
						+POSITIVE_MODE(n,mrc->HeaderN.y)*mrc->HeaderN.x
						+POSITIVE_MODE(iz,mrc->HeaderN.z)*mrc->HeaderN.x*mrc->HeaderN.y] ;
					imagedata[1+1*4] = mrc->ImageFloatImage[
						 POSITIVE_MODE(m,mrc->HeaderN.x)
						+POSITIVE_MODE(n,mrc->HeaderN.y)*mrc->HeaderN.x
						+POSITIVE_MODE(iz,mrc->HeaderN.z)*mrc->HeaderN.x*mrc->HeaderN.y] ;
					imagedata[2+1*4] = mrc->ImageFloatImage[
						 POSITIVE_MODE(m+1,mrc->HeaderN.x)
						+POSITIVE_MODE(n,mrc->HeaderN.y)*mrc->HeaderN.x
						+POSITIVE_MODE(iz,mrc->HeaderN.z)*mrc->HeaderN.x*mrc->HeaderN.y] ;
					imagedata[3+1*4] = mrc->ImageFloatImage[
						 POSITIVE_MODE(m+2,mrc->HeaderN.x)
						+POSITIVE_MODE(n,mrc->HeaderN.y)*mrc->HeaderN.x
						+POSITIVE_MODE(iz,mrc->HeaderN.z)*mrc->HeaderN.x*mrc->HeaderN.y] ;
					imagedata[0+2*4] = mrc->ImageFloatImage[
						 POSITIVE_MODE(m-1,mrc->HeaderN.x)
						+POSITIVE_MODE(n+1,mrc->HeaderN.y)*mrc->HeaderN.x
						+POSITIVE_MODE(iz,mrc->HeaderN.z)*mrc->HeaderN.x*mrc->HeaderN.y] ;
					imagedata[1+2*4] = mrc->ImageFloatImage[
						 POSITIVE_MODE(m,mrc->HeaderN.x)
						+POSITIVE_MODE(n+1,mrc->HeaderN.y)*mrc->HeaderN.x
						+POSITIVE_MODE(iz,mrc->HeaderN.z)*mrc->HeaderN.x*mrc->HeaderN.y] ;
					imagedata[2+2*4] = mrc->ImageFloatImage[
						 POSITIVE_MODE(m+1,mrc->HeaderN.x)
						+POSITIVE_MODE(n+1,mrc->HeaderN.y)*mrc->HeaderN.x
						+POSITIVE_MODE(iz,mrc->HeaderN.z)*mrc->HeaderN.x*mrc->HeaderN.y] ;
					imagedata[3+2*4] = mrc->ImageFloatImage[
						 POSITIVE_MODE(m+2,mrc->HeaderN.x)
						+POSITIVE_MODE(n+1,mrc->HeaderN.y)*mrc->HeaderN.x
						+POSITIVE_MODE(iz,mrc->HeaderN.z)*mrc->HeaderN.x*mrc->HeaderN.y] ;
					imagedata[0+3*4] = mrc->ImageFloatImage[
						 POSITIVE_MODE(m-1,mrc->HeaderN.x)
						+POSITIVE_MODE(n+2,mrc->HeaderN.y)*mrc->HeaderN.x
						+POSITIVE_MODE(iz,mrc->HeaderN.z)*mrc->HeaderN.x*mrc->HeaderN.y] ;
					imagedata[1+3*4] = mrc->ImageFloatImage[
						 POSITIVE_MODE(m,mrc->HeaderN.x)
						+POSITIVE_MODE(n+2,mrc->HeaderN.y)*mrc->HeaderN.x
						+POSITIVE_MODE(iz,mrc->HeaderN.z)*mrc->HeaderN.x*mrc->HeaderN.y] ;
					imagedata[2+3*4] = mrc->ImageFloatImage[
						 POSITIVE_MODE(m+1,mrc->HeaderN.x)
						+POSITIVE_MODE(n+2,mrc->HeaderN.y)*mrc->HeaderN.x
						+POSITIVE_MODE(iz,mrc->HeaderN.z)*mrc->HeaderN.x*mrc->HeaderN.y] ;
					imagedata[3+3*4] = mrc->ImageFloatImage[
						 POSITIVE_MODE(m+2,mrc->HeaderN.x)
						+POSITIVE_MODE(n+2,mrc->HeaderN.y)*mrc->HeaderN.x
						+POSITIVE_MODE(iz,mrc->HeaderN.z)*mrc->HeaderN.x*mrc->HeaderN.y] ;
					break;
				}
				case mrcDoubleImage: {
					imagedata[0+0*4] = mrc->ImageDoubleImage[
						 POSITIVE_MODE(m-1,mrc->HeaderN.x)
						+POSITIVE_MODE(n-1,mrc->HeaderN.y)*mrc->HeaderN.x
						+POSITIVE_MODE(iz,mrc->HeaderN.z)*mrc->HeaderN.x*mrc->HeaderN.y] ;
					imagedata[1+0*4] = mrc->ImageDoubleImage[
						 POSITIVE_MODE(m,mrc->HeaderN.x)
						+POSITIVE_MODE(n-1,mrc->HeaderN.y)*mrc->HeaderN.x
						+POSITIVE_MODE(iz,mrc->HeaderN.z)*mrc->HeaderN.x*mrc->HeaderN.y] ;
					imagedata[2+0*4] = mrc->ImageDoubleImage[
						 POSITIVE_MODE(m+1,mrc->HeaderN.x)
						+POSITIVE_MODE(n-1,mrc->HeaderN.y)*mrc->HeaderN.x
						+POSITIVE_MODE(iz,mrc->HeaderN.z)*mrc->HeaderN.x*mrc->HeaderN.y] ;
					imagedata[3+0*4] = mrc->ImageDoubleImage[
						 POSITIVE_MODE(m+2,mrc->HeaderN.x)
						+POSITIVE_MODE(n-1,mrc->HeaderN.y)*mrc->HeaderN.x
						+POSITIVE_MODE(iz,mrc->HeaderN.z)*mrc->HeaderN.x*mrc->HeaderN.y] ;
					imagedata[0+1*4] = mrc->ImageDoubleImage[
						 POSITIVE_MODE(m-1,mrc->HeaderN.x)
						+POSITIVE_MODE(n,mrc->HeaderN.y)*mrc->HeaderN.x
						+POSITIVE_MODE(iz,mrc->HeaderN.z)*mrc->HeaderN.x*mrc->HeaderN.y] ;
					imagedata[1+1*4] = mrc->ImageDoubleImage[
						 POSITIVE_MODE(m,mrc->HeaderN.x)
						+POSITIVE_MODE(n,mrc->HeaderN.y)*mrc->HeaderN.x
						+POSITIVE_MODE(iz,mrc->HeaderN.z)*mrc->HeaderN.x*mrc->HeaderN.y] ;
					imagedata[2+1*4] = mrc->ImageDoubleImage[
						 POSITIVE_MODE(m+1,mrc->HeaderN.x)
						+POSITIVE_MODE(n,mrc->HeaderN.y)*mrc->HeaderN.x
						+POSITIVE_MODE(iz,mrc->HeaderN.z)*mrc->HeaderN.x*mrc->HeaderN.y] ;
					imagedata[3+1*4] = mrc->ImageDoubleImage[
						 POSITIVE_MODE(m+2,mrc->HeaderN.x)
						+POSITIVE_MODE(n,mrc->HeaderN.y)*mrc->HeaderN.x
						+POSITIVE_MODE(iz,mrc->HeaderN.z)*mrc->HeaderN.x*mrc->HeaderN.y] ;
					imagedata[0+2*4] = mrc->ImageDoubleImage[
						 POSITIVE_MODE(m-1,mrc->HeaderN.x)
						+POSITIVE_MODE(n+1,mrc->HeaderN.y)*mrc->HeaderN.x
						+POSITIVE_MODE(iz,mrc->HeaderN.z)*mrc->HeaderN.x*mrc->HeaderN.y] ;
					imagedata[1+2*4] = mrc->ImageDoubleImage[
						 POSITIVE_MODE(m,mrc->HeaderN.x)
						+POSITIVE_MODE(n+1,mrc->HeaderN.y)*mrc->HeaderN.x
						+POSITIVE_MODE(iz,mrc->HeaderN.z)*mrc->HeaderN.x*mrc->HeaderN.y] ;
					imagedata[2+2*4] = mrc->ImageDoubleImage[
						 POSITIVE_MODE(m+1,mrc->HeaderN.x)
						+POSITIVE_MODE(n+1,mrc->HeaderN.y)*mrc->HeaderN.x
						+POSITIVE_MODE(iz,mrc->HeaderN.z)*mrc->HeaderN.x*mrc->HeaderN.y] ;
					imagedata[3+2*4] = mrc->ImageDoubleImage[
						 POSITIVE_MODE(m+2,mrc->HeaderN.x)
						+POSITIVE_MODE(n+1,mrc->HeaderN.y)*mrc->HeaderN.x
						+POSITIVE_MODE(iz,mrc->HeaderN.z)*mrc->HeaderN.x*mrc->HeaderN.y] ;
					imagedata[0+3*4] = mrc->ImageDoubleImage[
						 POSITIVE_MODE(m-1,mrc->HeaderN.x)
						+POSITIVE_MODE(n+2,mrc->HeaderN.y)*mrc->HeaderN.x
						+POSITIVE_MODE(iz,mrc->HeaderN.z)*mrc->HeaderN.x*mrc->HeaderN.y] ;
					imagedata[1+3*4] = mrc->ImageDoubleImage[
						 POSITIVE_MODE(m,mrc->HeaderN.x)
						+POSITIVE_MODE(n+2,mrc->HeaderN.y)*mrc->HeaderN.x
						+POSITIVE_MODE(iz,mrc->HeaderN.z)*mrc->HeaderN.x*mrc->HeaderN.y] ;
					imagedata[2+3*4] = mrc->ImageDoubleImage[
						 POSITIVE_MODE(m+1,mrc->HeaderN.x)
						+POSITIVE_MODE(n+2,mrc->HeaderN.y)*mrc->HeaderN.x
						+POSITIVE_MODE(iz,mrc->HeaderN.z)*mrc->HeaderN.x*mrc->HeaderN.y] ;
					imagedata[3+3*4] = mrc->ImageDoubleImage[
						 POSITIVE_MODE(m+2,mrc->HeaderN.x)
						+POSITIVE_MODE(n+2,mrc->HeaderN.y)*mrc->HeaderN.x
						+POSITIVE_MODE(iz,mrc->HeaderN.z)*mrc->HeaderN.x*mrc->HeaderN.y] ;
					break;
				}
				default: {
					sprintf(s, "mrcPixelType %d", mode);
					mrcError(RTN_NAME, "Pixel Data Type", s, 
     						 mrcStatusMask_ExitFailure|MRC_ModeNotSupported);
					break;
				}
			}
			if(flagFirst) { 
				polyInitMatrix(matrix, 1, 1);
				flagFirst=0;
			}
			polyInitVector(vec, 1, 1, imagedata, 4, 4);
			if(polySolveMatrix(matrix, vec, coefficient)) {
				*data = coefficient[0]*x*x + coefficient[1]*x*y
				      + coefficient[2]*y*y + coefficient[3]*x
				      + coefficient[4]*y   + coefficient[5];
			} else {
			    fprintf(stderr, "trace = 0 at (%f, %f)\n", x, y);
				*data = (1-(y-n))*((1-(x-m))*imagedata[1+1*4] + (x-m)*imagedata[2+1*4])
				      +    (y-n) *((1-(x-m))*imagedata[1+2*4] + (x-m)*imagedata[2+2*4]);
			}
			break;
		}
		default: {
		    sprintf(s, "Unkown Methods:%d", how);
		    mrcError(RTN_NAME, "How to Get Image Data", s, 
		  			  mrcStatusMask_ExitFailure|MRC_ModeNotSupported);
		}
    }
    return *data;
}

void
polyInitMatrix(double matrix[6][6], int m, int n)
{
    int  i,j;

    for(i=0; i<6; i++) {
        for(j=0; j<6; j++) {
            matrix[i][j] = 0.0;
        }
    }
    i=m-1;
    for(j=n;j<=n+1;j++) {
        matrix[0][0] += (double)(i*i*i*i);
        matrix[0][1] += (double)(i*i*i*j);
        matrix[0][2] += (double)(i*i*j*j);
        matrix[0][3] += (double)(i*i*i);
        matrix[0][4] += (double)(i*i*j);
        matrix[0][5] += (double)(i*i);
        matrix[1][1] += (double)(i*i*j*j);
        matrix[1][2] += (double)(i*j*j*j);
        matrix[1][3] += (double)(i*i*j);
        matrix[1][4] += (double)(i*j*j);
        matrix[1][5] += (double)(i*j);
        matrix[2][2] += (double)(j*j*j*j);
        matrix[2][3] += (double)(i*j*j);
        matrix[2][4] += (double)(j*j*j);
        matrix[2][5] += (double)(j*j);
        matrix[3][3] += (double)(i*i);
        matrix[3][4] += (double)(i*j);
        matrix[3][5] += (double)i;
        matrix[4][4] += (double)(j*j);
        matrix[4][5] += (double)j;
        matrix[5][5] += 1.0;
    }
    for(i=m;i<=m+1;i++) {
        for(j=n-1;j<=n+2;j++) {
            matrix[0][0] += (double)(i*i*i*i);
            matrix[0][1] += (double)(i*i*i*j);
            matrix[0][2] += (double)(i*i*j*j);
            matrix[0][3] += (double)(i*i*i);
            matrix[0][4] += (double)(i*i*j);
            matrix[0][5] += (double)(i*i);
            matrix[1][1] += (double)(i*i*j*j);
            matrix[1][2] += (double)(i*j*j*j);
            matrix[1][3] += (double)(i*i*j);
            matrix[1][4] += (double)(i*j*j);
            matrix[1][5] += (double)(i*j);
            matrix[2][2] += (double)(j*j*j*j);
            matrix[2][3] += (double)(i*j*j);
            matrix[2][4] += (double)(j*j*j);
            matrix[2][5] += (double)(j*j);
            matrix[3][3] += (double)(i*i);
            matrix[3][4] += (double)(i*j);
            matrix[3][5] += (double)i;
            matrix[4][4] += (double)(j*j);
            matrix[4][5] += (double)j;
            matrix[5][5] += 1.0;
        }
    }
    i=m+2;
    for(j=n;j<=n+1;j++) {
        matrix[0][0] += (double)(i*i*i*i);
        matrix[0][1] += (double)(i*i*i*j);
        matrix[0][2] += (double)(i*i*j*j);
        matrix[0][3] += (double)(i*i*i);
        matrix[0][4] += (double)(i*i*j);
        matrix[0][5] += (double)(i*i);
        matrix[1][1] += (double)(i*i*j*j);
        matrix[1][2] += (double)(i*j*j*j);
        matrix[1][3] += (double)(i*i*j);
        matrix[1][4] += (double)(i*j*j);
        matrix[1][5] += (double)(i*j);
        matrix[2][2] += (double)(j*j*j*j);
        matrix[2][3] += (double)(i*j*j);
        matrix[2][4] += (double)(j*j*j);
        matrix[2][5] += (double)(j*j);
        matrix[3][3] += (double)(i*i);
        matrix[3][4] += (double)(i*j);
        matrix[3][5] += (double)i;
        matrix[4][4] += (double)(j*j);
        matrix[4][5] += (double)j;
        matrix[5][5] += 1.0;
    }
    for(i=1;i<6;i++) {
        for(j=0;j<i;j++) {
            matrix[i][j] = matrix[j][i];
        }
    }
}


void
polyInitVector(double vec[6], int m, int n, double* image, int nx, int ny)
{
    int  i,j;
    int  value;

    for(i=0;i<6;i++) {
         vec[i] = 0.0;
    }
    i=m-1;
    for(j=n;j<=n+1;j++) {
         value = image[i+j*nx];
         vec[0] += (double)(i*i*value);
         vec[1] += (double)(i*j*value);
         vec[2] += (double)(j*j*value);
         vec[3] += (double)(i*value);
         vec[4] += (double)(j*value);
         vec[5] += (double)(value);
    }
    for(i=m;i<=m+1;i++) {
        for(j=n-1;j<=n+2;j++) {
            value = image[i+j*nx];
            vec[0] += (double)(i*i*value);
            vec[1] += (double)(i*j*value);
            vec[2] += (double)(j*j*value);
            vec[3] += (double)(i*value);
            vec[4] += (double)(j*value);
            vec[5] += (double)(value);
        }
    }
    i=m+2;
    for(j=n;j<=n+1;j++) {
        value = image[i+j*nx];
        vec[0] += (double)(i*i*value);
        vec[1] += (double)(i*j*value);
        vec[2] += (double)(j*j*value);
        vec[3] += (double)(i*value);
        vec[4] += (double)(j*value);
        vec[5] += (double)(value);
    }
}

int
polySolveMatrix(double matrix[6][6], double vec[6], double coefficient[6])
{
    int  i, j, k;

    for(i=0;i<6;i++) {
        if(matrix[i][i]==0) {
            return 0;
        }
        for(j=i+1;j<6;j++) {
             matrix[i][j] /= matrix[i][i];
        }
        vec[i] /= matrix[i][i];
        for(k=0;k<6;k++) {
            if(k!=i) {
                for(j=i+1;j<6;j++) {
                       matrix[k][j] -= matrix[k][i]*matrix[i][j];
                }
                vec[k] -= matrix[k][i]*vec[i];
            }
        }
    }
    for(i=0;i<6;i++) {
        coefficient[i] = vec[i];
    }
    return 1;
}

#undef RTN_NAME
