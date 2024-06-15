/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% mrcImageSet ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : mrcImageSet 
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%mrcImageSet ver%I%; Date:%D% %Z%";
/* 
* mrcSet.c
*/
#include <math.h>

#undef DEBUG
#include "../inc/mrcImage.h"
#include "genUtil.h"
#include "eosString.h"

#define RTN_NAME "mrcSetPixelData"
#define SQR(x) ((x)*(x))
#define FOR_RINT (0.5)

inline 
double
mrcImageDataSetbyAU(mrcImage* mrc,
		mrcImageParaTypeReal x,
		mrcImageParaTypeReal y,
		mrcImageParaTypeReal z,
		double               data,
		mrcPixelDataType mode)
{
	return mrcPixelDataSet(mrc, 
						   x/mrc->HeaderLength.x - mrc->HeaderStartN.x,
						   y/mrc->HeaderLength.y - mrc->HeaderStartN.y,
						   z/mrc->HeaderLength.z - mrc->HeaderStartN.z, 
						   data,
						   mode);
}

inline 
double
mrcPixelDataSet(mrcImage* mrc,
		mrcImageParaTypeReal x,
		mrcImageParaTypeReal y,
		mrcImageParaTypeReal z,
		double               data,
		mrcPixelDataType mode)
{
    char s[20];
    mrcImageParaTypeInteger n, ix, iy, iz;
    double sig, phase, mag;

    switch(mrc->HeaderMode) {
		case mrcFloatRadonImage: 
		case mrcCharImage: 
		case mrcShortImage:
		case mrcUShortImage:
		case mrcLongImage:
		case mrcFloatImage:
		case mrcDoubleImage: {
			ix = POSITIVE_MODE(((mrcImageParaTypeInteger)floor(x+FOR_RINT)), mrc->Header.Cont.N.x);
			iy = POSITIVE_MODE(((mrcImageParaTypeInteger)floor(y+FOR_RINT)), mrc->Header.Cont.N.y);
			iz = POSITIVE_MODE(((mrcImageParaTypeInteger)floor(z+FOR_RINT)), mrc->Header.Cont.N.z);
            n =                           (ix%mrc->HeaderN.x) 
	      + mrc->HeaderN.x*               (iy%mrc->HeaderN.y) 
	      + mrc->HeaderN.x*mrc->HeaderN.y*(iz%mrc->HeaderN.z);
			sig = 1.0;
	        break;
        }
		case mrcComplexShortFT:
		case mrcComplexLongFT:
		case mrcComplexFloatFT:
		case mrcComplexDoubleFT: {
			if(x<0) {
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
			if(1 == mrc->HeaderN.z) {
				n = ix + (mrc->HeaderN.x/2+1)*iy;
            } else {
				n = ix + (mrc->HeaderN.x/2+1)*iy + (mrc->HeaderN.x/2+1)*(mrc->HeaderN.y)*iz;
            }
			if((mrc->HeaderN.x/2 + 1)*mrc->HeaderN.y*mrc->HeaderN.z<=n) {
				fprintf(stderr, "x,y,z is over range\n");
			}
			break;
		}
		case mrcComplexFloatOneDimFT: {
			if(x<0) {
				ix = -(mrcImageParaTypeInteger)floor(x+FOR_RINT);
				sig = -1.0;                    
			} else {
                ix = (mrcImageParaTypeInteger)floor(x+FOR_RINT);
				sig = 1.0;
			}
			iy = POSITIVE_MODE(((mrcImageParaTypeInteger)floor(y+FOR_RINT)), mrc->Header.Cont.N.y);
			iz = POSITIVE_MODE(((mrcImageParaTypeInteger)floor(z+FOR_RINT)), mrc->Header.Cont.N.z);
			n = ix + (mrc->HeaderN.x/2+1)*iy + (mrc->HeaderN.x/2+1)*mrc->HeaderN.y*iz;
			break;
		}
		case mrcFloatRadonFT: {
			if(x<0) {
				ix = -(mrcImageParaTypeInteger)floor(x+FOR_RINT);
				sig = -1.0;                    
			} else {
                ix = (mrcImageParaTypeInteger)floor(x+FOR_RINT);
				sig = 1.0;
			}
			iy = POSITIVE_MODE(((mrcImageParaTypeInteger)floor(y+FOR_RINT)), mrc->Header.Cont.N.y);
			iz = POSITIVE_MODE(((mrcImageParaTypeInteger)floor(z+FOR_RINT)), mrc->Header.Cont.N.z);
			n = ix + (mrc->HeaderN.x/2+1)*iy + (mrc->HeaderN.x/2+1)*mrc->HeaderN.y*iz;
			break;
		}
		default: {
			n = 0;
			sig = 1.0;
			sprintf(s, "mrcImage Mode %ld", mrc->HeaderMode);
			mrcError("", RTN_NAME, s, 
				 mrcStatusMask_ExitFailure|MRC_ModeNotSupported);
        }
    }

    switch(mode) {
        case mrcPixelRePart: {
			switch(mrc->HeaderMode) {
				case mrcCharImage: {
					mrc->ImageCharImage[n] = (unsigned char)data;
					break;
				}
				case mrcShortImage: {
					mrc->ImageShortImage[n] = (signed short)data;
					break;
				}
				case mrcUShortImage: {
					mrc->ImageShortImage[n] = (unsigned short)data;
					break;
				}
				case mrcFloatImage: {
					mrc->ImageFloatImage[n] = (float)data;
					break;
				}
				case mrcFloatRadonImage: {
					mrc->ImageFloatImage[n] = (float)data;
					break;
				}
				case mrcComplexShortFT: {
					mrc->ImageShortImage[2*n] = (short)data;
					break;
				}
				case mrcComplexFloatFT: {
					mrc->ImageFloatImage[2*n] = (float)data;
					break;
				}
				case mrcComplexFloatOneDimFT: {
					mrc->ImageFloatImage[2*n] = (float)data;
					DEBUGPRINT5("%g %d <- %d %d %d\n", data, n, ix, iy, iz);
					break;
				}
				case mrcFloatRadonFT: {
					mrc->ImageFloatImage[2*n] = (float)data;
					DEBUGPRINT5("%g %d <- %d %d %d\n", data, n, ix, iy, iz);
					break;
				}
				case mrcLongImage: {
					mrc->ImageLongImage[n] = (long)data;
					break;
				}
				case mrcDoubleImage: {
					mrc->ImageDoubleImage[n] = (double)data;
					break;
				}
				case mrcComplexLongFT: {
					mrc->ImageLongImage[2*n] = (long)data;
					break;
				}
				case mrcComplexDoubleFT: {
					mrc->ImageDoubleImage[2*n] = (double)data;
					break;
				}
				default: {
					sprintf(s, "mrcImage Mode %ld", mrc->HeaderMode);
					mrcError("", RTN_NAME, s, 
						 mrcStatusMask_ExitFailure|MRC_ModeNotSupported);
				}
	    	}
	    	break;
		}	
		case mrcPixelImPart: {
		    switch(mrc->HeaderMode) {
		        case mrcComplexShortFT: {
		            mrc->ImageShortImage[2*n+1] = (short)sig*data;
					break;
				}
		        case mrcComplexFloatFT: {
		            mrc->ImageFloatImage[2*n+1] = (float)sig*data;
					break;
				}
		        case mrcComplexFloatOneDimFT: {
		            mrc->ImageFloatImage[2*n+1] = (float)sig*data;
					break;
				}
		        case mrcFloatRadonFT: {
		            mrc->ImageFloatImage[2*n+1] = (float)sig*data;
					break;
				}
		        case mrcComplexLongFT: {
					mrc->ImageLongImage[2*n+1] = (long)sig*data;
					break;
		        }
		        case mrcComplexDoubleFT: {
		            mrc->ImageDoubleImage[2*n+1] = (double)sig*data;
		            break;
		        }
		        default: {
		            sprintf(s, "mrcPixelDataHowToGet %d", mode);
			        mrcError("", RTN_NAME, s, 
			                 mrcStatusMask_ExitFailure|MRC_ModeNotSupported);
		        }
		    }
			break;
    	}     
        case mrcPixelMag: {
			switch(mrc->HeaderMode) {
				case mrcCharImage: {
					mrc->ImageCharImage[n] = (unsigned char)data;
					break;
				}
				case mrcShortImage: { 
					mrc->ImageShortImage[n] = (short)data;
					break;
				}
				case mrcUShortImage: {
					mrc->ImageShortImage[n] = (unsigned short)data;
					break;
				}
				case mrcFloatImage: {
					mrc->ImageFloatImage[n] = (float)data;
					break;
				}
				case mrcLongImage: {
					mrc->ImageLongImage[n] = (long)data;
					break;
				}
				case mrcDoubleImage: {
					mrc->ImageDoubleImage[n] = (double)data;
					break;
				}

		        case mrcComplexShortFT: {
					if(mrc->ImageShortImage[2*n+1]==0 && mrc->ImageShortImage[2*n]==0) {
						phase = 0.0;
						data  = 0.0;
					} else {
		            	phase = atan2((double)sig*mrc->ImageShortImage[2*n+1], (double)mrc->ImageShortImage[2*n]);
					}
		            mrc->ImageShortImage[2*n]   = (short)data*cos(phase);
		            mrc->ImageShortImage[2*n+1] = (short)data*sin(phase);
					break;
				}
		        case mrcComplexFloatFT: {
					if(mrc->ImageFloatImage[2*n+1]==0 && mrc->ImageFloatImage[2*n]==0) {
						phase = 0.0;
						data  = 0.0;
					} else {
		            	phase = atan2((double)sig*mrc->ImageFloatImage[2*n+1], (double)mrc->ImageFloatImage[2*n]);
					}
					DEBUGPRINT4("%d: %f %f %f\n", 
						n, mrc->ImageFloatImage[2*n+1], mrc->ImageFloatImage[2*n], phase);
		            mrc->ImageFloatImage[2*n]   = (float)data*cos(phase);
		            mrc->ImageFloatImage[2*n+1] = (float)data*sin(phase);
					break;
				}
		        case mrcComplexFloatOneDimFT: {
					if(mrc->ImageFloatImage[2*n+1]==0 && mrc->ImageFloatImage[2*n]==0) {
						phase = 0.0;
						data  = 0.0;
					} else {
		            	phase = atan2((double)sig*mrc->ImageFloatImage[2*n+1], (double)mrc->ImageFloatImage[2*n]);
					}
					DEBUGPRINT4("%d: %f %f %f\n", 
						n, mrc->ImageFloatImage[2*n+1], mrc->ImageFloatImage[2*n], phase);
		            mrc->ImageFloatImage[2*n]   = (float)data*cos(phase);
		            mrc->ImageFloatImage[2*n+1] = (float)data*sin(phase);
					break;
				}
		        case mrcFloatRadonFT: {
					if(mrc->ImageFloatImage[2*n+1]==0 && mrc->ImageFloatImage[2*n]==0) {
						phase = 0.0;
						data  = 0.0;
					} else {
		            	phase = atan2((double)sig*mrc->ImageFloatImage[2*n+1], (double)mrc->ImageFloatImage[2*n]);
					}
					DEBUGPRINT4("%d: %f %f %f\n", 
						n, mrc->ImageFloatImage[2*n+1], mrc->ImageFloatImage[2*n], phase);
		            mrc->ImageFloatImage[2*n]   = (float)data*cos(phase);
		            mrc->ImageFloatImage[2*n+1] = (float)data*sin(phase);
					break;
				}
		        case mrcComplexLongFT: {
					if(mrc->ImageLongImage[2*n+1] ==0 && mrc->ImageLongImage[2*n]==0) {
						phase = 0;
						data  = 0.0;
					} else {
		            	phase = atan2((double)sig*mrc->ImageLongImage[2*n+1], (double)mrc->ImageLongImage[2*n]);
					}
		            mrc->ImageLongImage[2*n]   = (long)data*cos(phase);
		            mrc->ImageLongImage[2*n+1] = (long)data*sin(phase);
					break;
		        }
		        case mrcComplexDoubleFT: {
					if(mrc->ImageDoubleImage[2*n+1]==0 && mrc->ImageDoubleImage[2*n]==0) {
						phase = 0.0;
						data  = 0.0;
					} else {
		            	phase = atan2((double)sig*mrc->ImageDoubleImage[2*n+1], (double)mrc->ImageDoubleImage[2*n]);
					}
		            mrc->ImageDoubleImage[2*n]   = (double)data*cos(phase);
		            mrc->ImageDoubleImage[2*n+1] = (double)data*sin(phase);
		            break;
		        }
				default: {
					sprintf(s, "mrcImage Mode %ld", mrc->HeaderMode);
					mrcError("", RTN_NAME, s, 
						 mrcStatusMask_ExitFailure|MRC_ModeNotSupported);
				}
	    	}
	    	break;
		}
        case mrcPixelPow: {
			switch(mrc->HeaderMode) {
				case mrcCharImage: {
					mrc->ImageCharImage[n] = (unsigned char)mrc->ImageCharImage[n]/fabs(mrc->ImageCharImage[n])*sqrt(data);
					break;
				}
				case mrcShortImage: {
					mrc->ImageShortImage[n] = (short)mrc->ImageShortImage[n]/fabs(mrc->ImageShortImage[n])*sqrt(data);
					break;
				}
				case mrcUShortImage: {
					mrc->ImageShortImage[n] = (unsigned short)mrc->ImageShortImage[n]/fabs(mrc->ImageShortImage[n])*sqrt(data);
					break;
				}
				case mrcFloatImage: {
					mrc->ImageFloatImage[n] = (float)mrc->ImageFloatImage[n]/fabs(mrc->ImageFloatImage[n])*sqrt(data);
					break;
				}
				case mrcLongImage: {
					mrc->ImageLongImage[n] = (long)mrc->ImageLongImage[n]/fabs(mrc->ImageLongImage[n])*sqrt(data);
					break;
				}
				case mrcDoubleImage: {
					mrc->ImageDoubleImage[n] = (double)mrc->ImageDoubleImage[n]/fabs(mrc->ImageDoubleImage[n])*sqrt(data);
					break;
				}

		        case mrcComplexShortFT: {
					if(mrc->ImageShortImage[2*n+1]==0 && mrc->ImageShortImage[2*n]==0) {
						phase = 0.0;
						data  = 0.0;
					} else {
		            	phase = atan2((double)sig*mrc->ImageShortImage[2*n+1], (double)mrc->ImageShortImage[2*n]);
					}
		            mrc->ImageShortImage[2*n]   = (short)sqrt(data)*cos(phase);
		            mrc->ImageShortImage[2*n+1] = (short)sqrt(data)*sin(phase);
					break;
				}
		        case mrcComplexFloatFT: {
					if(mrc->ImageFloatImage[2*n+1]==0 && mrc->ImageFloatImage[2*n]==0) {
						phase = 0.0;
						data  = 0.0;
					} else {
		            	phase = atan2((double)sig*mrc->ImageFloatImage[2*n+1], (double)mrc->ImageFloatImage[2*n]);
					}
					DEBUGPRINT4("%d: %f %f %f\n", 
						n, mrc->ImageFloatImage[2*n+1], mrc->ImageFloatImage[2*n], phase);
		            mrc->ImageFloatImage[2*n]   = (float)sqrt(data)*cos(phase);
		            mrc->ImageFloatImage[2*n+1] = (float)sqrt(data)*sin(phase);
					break;
				}
		        case mrcComplexFloatOneDimFT: {
					if(mrc->ImageFloatImage[2*n+1]==0 && mrc->ImageFloatImage[2*n]==0) {
						phase = 0.0;
						data  = 0.0;
					} else {
		            	phase = atan2((double)sig*mrc->ImageFloatImage[2*n+1], (double)mrc->ImageFloatImage[2*n]);
					}
					DEBUGPRINT4("%d: %f %f %f\n", 
						n, mrc->ImageFloatImage[2*n+1], mrc->ImageFloatImage[2*n], phase);
		            mrc->ImageFloatImage[2*n]   = (float)sqrt(data)*cos(phase);
		            mrc->ImageFloatImage[2*n+1] = (float)sqrt(data)*sin(phase);
					break;
				}
		        case mrcFloatRadonFT: {
					if(mrc->ImageFloatImage[2*n+1]==0 && mrc->ImageFloatImage[2*n]==0) {
						phase = 0.0;
						data  = 0.0;
					} else {
		            	phase = atan2((double)sig*mrc->ImageFloatImage[2*n+1], (double)mrc->ImageFloatImage[2*n]);
					}
					DEBUGPRINT4("%d: %f %f %f\n", 
						n, mrc->ImageFloatImage[2*n+1], mrc->ImageFloatImage[2*n], phase);
		            mrc->ImageFloatImage[2*n]   = (float)sqrt(data)*cos(phase);
		            mrc->ImageFloatImage[2*n+1] = (float)sqrt(data)*sin(phase);
					break;
				}
		        case mrcComplexLongFT: {
					if(mrc->ImageLongImage[2*n+1]==0 && mrc->ImageLongImage[2*n]==0) {
						phase = 0;
						data  = 0.0;
					} else {
		            	phase = atan2((double)sig*mrc->ImageLongImage[2*n+1], (double)mrc->ImageLongImage[2*n]);
					}
		            mrc->ImageLongImage[2*n]   = (long)sqrt(data)*cos(phase);
		            mrc->ImageLongImage[2*n+1] = (long)sqrt(data)*sin(phase);
					break;
		        }
		        case mrcComplexDoubleFT: {
					if(mrc->ImageDoubleImage[2*n+1]==0 && mrc->ImageDoubleImage[2*n]==0) {
						phase = 0.0;
						data  = 0.0;
					} else {
		            	phase = atan2((double)sig*mrc->ImageDoubleImage[2*n+1], (double)mrc->ImageDoubleImage[2*n]);
					}
		            mrc->ImageDoubleImage[2*n]   = (double)sqrt(data)*cos(phase);
		            mrc->ImageDoubleImage[2*n+1] = (double)sqrt(data)*sin(phase);
		            break;
		        }
				default: {
					sprintf(s, "mrcImage Mode %ld", mrc->HeaderMode);
					mrcError("", RTN_NAME, s, 
						 mrcStatusMask_ExitFailure|MRC_ModeNotSupported);
				}
	    	}
	    	break;
		}
		case mrcPixelPhase: {
			switch(mrc->HeaderMode) {
				case mrcComplexShortFT: {
                    mag = sqrt(SQR((double)mrc->ImageShortImage[2*n])
			    			  +SQR((double)mrc->ImageShortImage[2*n+1]));
                    mrc->ImageShortImage[2*n]   =     mag*cos(data);
                    mrc->ImageShortImage[2*n+1] = sig*mag*sin(data);
				    break;
				}
				case mrcComplexLongFT: {
                    mag = sqrt(SQR((double)mrc->ImageLongImage[2*n])
			    			  +SQR((double)mrc->ImageLongImage[2*n+1]));
                    mrc->ImageLongImage[2*n]   =     mag*cos(data);
                    mrc->ImageLongImage[2*n+1] = sig*mag*sin(data);
                    break;
				}
				case mrcComplexFloatFT: {
                    mag = sqrt(SQR((double)mrc->ImageFloatImage[2*n])
			    			  +SQR((double)mrc->ImageFloatImage[2*n+1]));
                    mrc->ImageFloatImage[2*n]   =     mag*cos(data);
                    mrc->ImageFloatImage[2*n+1] = sig*mag*sin(data);
     			    break;
				}
				case mrcComplexFloatOneDimFT: {
                    mag = sqrt(SQR((double)mrc->ImageFloatImage[2*n])
			    			  +SQR((double)mrc->ImageFloatImage[2*n+1]));
                    mrc->ImageFloatImage[2*n]   =     mag*cos(data);
                    mrc->ImageFloatImage[2*n+1] = sig*mag*sin(data);
     			    break;
				}
				case mrcFloatRadonFT: {
                    mag = sqrt(SQR((double)mrc->ImageFloatImage[2*n])
			    			  +SQR((double)mrc->ImageFloatImage[2*n+1]));
                    mrc->ImageFloatImage[2*n]   =     mag*cos(data);
                    mrc->ImageFloatImage[2*n+1] = sig*mag*sin(data);
     			    break;
				}
				case mrcComplexDoubleFT: {
                    mag = sqrt(SQR((double)mrc->ImageDoubleImage[2*n])
			    			  +SQR((double)mrc->ImageDoubleImage[2*n+1]));
                    mrc->ImageDoubleImage[2*n]   =     mag*cos(data);
                    mrc->ImageDoubleImage[2*n+1] = sig*mag*sin(data);
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
		default: {
	   		sprintf(s, "PixelDataMode %d", mode);
	    	mrcError("", RTN_NAME, s,
		     mrcStatusMask_ExitFailure|MRC_ModeNotSupported);
		}
    }
    return data;
}

#undef RTN_NAME

#define RTN_NAME "mrcStatDataSet"

void
mrcStatDataSet(mrcImage* mrc, mrcImageParaTypeInteger mode)
{
    mrcImageParaTypeReal x, y, z;
    double data;
    double max, min, mean;

    mrcPixelDataGet(mrc, 0.0, 0.0, 0.0, &data, mrcPixelMag, mrcPixelHowNearest);
	max = min = data;
    mean = 0.0;
    if(IsImage(mrc, "", 0)) {
        for(x=0; x<mrc->HeaderN.x; x++) {
    		for(y=0; y<mrc->HeaderN.y; y++) {
    	    	for(z=0; z<mrc->HeaderN.z; z++) {
               		mrcPixelDataGet(mrc, x, y, z, &data, mrcPixelMag, mrcPixelHowNearest);
    	        	if(max<data) {
    	       	   		max = data;
    	        	}
    	        	if(min>data) {
    		    		min = data;
    				}
    	        	mean += data;
                }
    		}
        }
    } else if(IsFT(mrc, "", 0)) {
        for(x=-mrc->HeaderN.x/2.0; x<mrc->HeaderN.x/2.0; x++) {
    		for(y=-mrc->HeaderN.y/2.0; y<mrc->HeaderN.y/2.0; y++) {
    	    	for(z=-mrc->HeaderN.z/2.0; z<mrc->HeaderN.z/2.0; z++) {
               		mrcPixelDataGet(mrc, x, y, z, &data, mrcPixelMag, mrcPixelHowNearest);
    	        	if(max<data) {
    	       	   		max = data;
    	        	}
    	        	if(min>data) {
    		    		min = data;
    				}
    	        	mean += data;
                }
    		}
        }
    } else {
        fprintf(stderr, "Not Supported Data Mode: %ld", mrc->HeaderMode);
    }
    mean /= (mrc->HeaderN.x*mrc->HeaderN.y*mrc->HeaderN.z);
    mrc->HeaderAMax  = max;
    mrc->HeaderAMin  = min;
    mrc->HeaderAMean = mean;
} 
#undef RTN_NAME

#define RTN_NAME "mrcStatDataSet"
#define FILENAME_LENGTH 1024
void
mrcInfoSet(mrcImage* mrc, FILE* fptIn, FILE* fptOut, mrcImageParaTypeInteger mode)
{
    char message[FILENAME_LENGTH];
    char stmp[FILENAME_LENGTH];
    int  i;

    fprintf(fptOut, "If you don't want to change information, push return key only\n");
    sprintf(message, "N.x N.y N.z (Now(%ld, %ld, %ld))", mrc->HeaderN.x, mrc->HeaderN.y, mrc->HeaderN.z);
    stringGetFromFile(stmp, message, fptIn, fptOut, 0);
    if(stmp[0]!='\0') {
        mrc->HeaderN.x = stringGetNthIntegerData(stmp, 1, " ");
        mrc->HeaderN.y = stringGetNthIntegerData(stmp, 2, " ");
        mrc->HeaderN.z = stringGetNthIntegerData(stmp, 3, " ");
    }
    sprintf(message, "Mode (Now %ld)", mrc->HeaderMode);
    stringGetFromFile(stmp, message, fptIn, fptOut, 0);
    if(stmp[0]!='\0') {
        mrc->HeaderMode = stringGetNthIntegerData(stmp, 1, " ");
    }
    sprintf(message, "StartN.x StartN.y StartN.z (Now(%ld, %ld, %ld))", mrc->HeaderStartN.x, mrc->HeaderStartN.y, mrc->HeaderStartN.z); 
    stringGetFromFile(stmp, message, fptIn, fptOut, 0);
    if(stmp[0]!='\0') {
        mrc->HeaderStartN.x = stringGetNthIntegerData(stmp, 1, " ");
        mrc->HeaderStartN.y = stringGetNthIntegerData(stmp, 2, " ");
        mrc->HeaderStartN.z = stringGetNthIntegerData(stmp, 3, " ");
    }
    sprintf(message, "M.x M.y M.z (Now(%ld, %ld, %ld))", mrc->HeaderM.x, mrc->HeaderM.y, mrc->HeaderM.z); 
    stringGetFromFile(stmp, message, fptIn, fptOut, 0);
    if(stmp[0]!='\0') {
        mrc->HeaderM.x = stringGetNthIntegerData(stmp, 1, " ");
        mrc->HeaderM.y = stringGetNthIntegerData(stmp, 2, " ");
        mrc->HeaderM.z = stringGetNthIntegerData(stmp, 3, " ");
    }
    sprintf(message, "Length.x Length.y Length.z (Now(%f, %f, %f))", mrc->HeaderLength.x, mrc->HeaderLength.y, mrc->HeaderLength.z); 
    stringGetFromFile(stmp, message, fptIn, fptOut, 0);
    if(stmp[0]!='\0') {
        mrc->HeaderLength.x = stringGetNthRealData(stmp, 1, " ");
        mrc->HeaderLength.y = stringGetNthRealData(stmp, 2, " ");
        mrc->HeaderLength.z = stringGetNthRealData(stmp, 3, " ");
    }
    sprintf(message, "Alpha Beta Gamma (Now(%f, %f, %f))", mrc->HeaderAlpha, mrc->HeaderBeta, mrc->HeaderGamma); 
    stringGetFromFile(stmp, message, fptIn, fptOut, 0);
    if(stmp[0]!='\0') {
        mrc->HeaderAlpha = stringGetNthRealData(stmp, 1, " ");
        mrc->HeaderBeta  = stringGetNthRealData(stmp, 2, " ");
        mrc->HeaderGamma = stringGetNthRealData(stmp, 3, " ");
    }
    sprintf(message, "C R S (Now(%ld, %ld, %ld))", mrc->HeaderMAPC, mrc->HeaderMAPR, mrc->HeaderMAPS); 
    stringGetFromFile(stmp, message, fptIn, fptOut, 0);
    if(stmp[0]!='\0') {
        mrc->HeaderMAPC = stringGetNthIntegerData(stmp, 1, " ");
        mrc->HeaderMAPR = stringGetNthIntegerData(stmp, 2, " ");
        mrc->HeaderMAPS = stringGetNthIntegerData(stmp, 3, " ");
    }
    stringGetFromFile(stmp, "Do you want to reset Max,Min,Mean Data (yY/nN)?", fptIn, fptOut, 0);
    if(stmp[0]=='Y'||stmp[0]=='y') {
        fprintf(fptOut, "Wait a minutes!! Now Max, Min and Mean Set\n");
        mrcStatDataSet(mrc, 0);
    }
    sprintf(message, "SpaceGroup (Now %ld)", mrc->HeaderISPG);
    stringGetFromFile(stmp, message, fptIn, fptOut, 0);
    if(stmp[0]!='\0') {
        mrc->HeaderISPG = stringGetNthIntegerData(stmp, 1, " ");
    }
    sprintf(message, "NSYMBT (Now %ld)", mrc->HeaderNSYMBT);
    stringGetFromFile(stmp, message, fptIn, fptOut, 0);
    if(stmp[0]!='\0') {
        mrc->HeaderNSYMBT = stringGetNthIntegerData(stmp, 1, " ");
    }
    stringGetFromFile(stmp, "Do you want to reset Extra Data (yY/nN)?", fptIn, fptOut, 0);
    if(stmp[0]=='Y'||stmp[0]=='y') {
        for(i=0; i<MRC_MAX_EXTRA; i++) {
            sprintf(message, "EXTRA[%d] (Now %g)", i, mrc->HeaderEXTRA[i]);
            stringGetFromFile(stmp, message, fptIn, fptOut, 0);
            if(stmp[0]!='\0') {
                mrc->HeaderEXTRA[i] = stringGetNthRealData(stmp, 1, " ");
            }
        }
    }
    sprintf(message, "OriginX OriginY(Now(%g, %g))", mrc->HeaderOriginX, mrc->HeaderOriginY); 
    stringGetFromFile(stmp, message, fptIn, fptOut, 0);
    if(stmp[0]!='\0') {
        mrc->HeaderOriginX = stringGetNthRealData(stmp, 1, " ");
        mrc->HeaderOriginY = stringGetNthRealData(stmp, 2, " ");
    }
    stringGetFromFile(stmp, "Do you want to reset Label (yY/nN)?", fptIn, fptOut, 0);
    if(stmp[0]=='Y'||stmp[0]=='y') {
        for(i=0; i<MRC_MAX_LABEL_N; i++) {
            sprintf(message, "Label[%d] (Now %s)", i, mrc->HeaderLabel[i]);
            stringGetFromFile(stmp, message, fptIn, fptOut, 0);
            if(stmp[0]!='\0') {
                mrc->HeaderEXTRA[i] = stringGetNthRealData(stmp, 1, " ");
            } else {
                mrc->HeaderLabelN = i;
                break;
            }
        }
    }
}

#undef RTN_NAME


