#define UNDEBUG
#undef UNDEBUG2
#include "genUtil.h"
#include <math.h>
#include <stdlib.h>
#include "../inc/mrcImage.h"

void mrcImageDataSet(mrcImage* out, mrcImage* in, mrcImageParaTypeReal x,
												  mrcImageParaTypeReal y,
												  mrcImageParaTypeReal z, 
												  float phi,
												  mrcImageDataSetMode  mode)
{
	mrcImageParaTypeReal srcx,srcy,srcz;
	mrcImageParaTypeReal startx,starty,startz;
	mrcImageParaTypeReal dx,dy,dz;
	mrcImageParaTypeReal endx,endy,endz;
	mrcImageParaTypeReal dstx,dsty,dstz;
	mrcImageParaTypeReal tdstx,tdsty,tdstz;
	mrcImageParaTypeReal sftx,sfty,sftz;
	mrcImageParaTypeReal offsetx,offsety,offsetz;
	float theta;
	mrcImageParaTypeReal cos_theta,sin_theta;
	mrcImageParaTypeReal rotx,roty,rotz;
	mrcImageParaTypeReal maxN;

	double data,dataIn;

	theta = phi;

	DEBUGPRINT1("x:%f\n",x);
	DEBUGPRINT1("y:%f\n",y);
	DEBUGPRINT1("z:%f\n",z);
	DEBUGPRINT1("theta:%f\n",theta);
	DEBUGPRINT1("phi:%f\n",phi);

	cos_theta = cos(theta);
	sin_theta = sin(theta);

	maxN = sqrt( SQR(in->HeaderN.x*in->HeaderLength.x/out->HeaderLength.x)
				+SQR(in->HeaderN.y*in->HeaderLength.y/out->HeaderLength.y));

	dx = floor(x + 0.5) - x;
	dy = floor(y + 0.5) - y;
	dz = floor(z + 0.5) - z;
	switch(mode) {
		case mrcImageDataSetModeCentre: {
			offsetx = -(in->HeaderN.x - 1)/2.0;
			offsety = -(in->HeaderN.y - 1)/2.0;
			offsetz = -(in->HeaderN.z - 1)/2.0;
			startx = floor(-offsetx - maxN/2.0 + 0.5) - 1; 
			starty = floor(-offsetx - maxN/2.0 + 0.5) - 1;
			startz = 0.0;
			endx   = floor(-offsetx + maxN/2.0 + 0.5) + 1; 
			endy   = floor(-offsety + maxN/2.0 + 0.5) + 1;
			endz   = in->HeaderN.z;
			break;
		}
		case mrcImageDataSetModeOrigin: {
			offsetx = 0.0;
			offsety = 0.0;
			offsetz = 0.0;
			startx = floor(-offsetx - maxN + 0.5) - 1;
			starty = floor(-offsety - maxN + 0.5) + 1;
			startz = -offsetz - 0.0;
			endx = floor(offsetx + maxN + 0.5) + 1;
			endy = floor(offsety + maxN + 0.5) + 1;
			endz = offsetz + in->HeaderN.z;
			break;
		}
		default: {
			fprintf(stderr, "Not supported mode in mrcImageDataSet: %d\n", mode);
			exit(EXIT_FAILURE);
		}
	}

	for(dstx=startx; dstx<=endx; dstx++) {
		for(dsty=starty; dsty<=endy; dsty++) {
			for(dstz=startz; dstz<endz; dstz++) {
				sftx = dstx + offsetx + dx;
				sfty = dsty + offsety + dy;
				sftz = dstz + offsetz + dz;

				rotx =  sftx*cos_theta + sfty*sin_theta;
				roty = -sftx*sin_theta + sfty*cos_theta;
				rotz = sftz;

				srcx = rotx - offsetx;
				srcy = roty - offsety;
				srcz = rotz - offsetz;
				if(   -0.5 <= srcx && srcx < in->HeaderN.x-0.5
				  	&&-0.5 <= srcy && srcy < in->HeaderN.y-0.5
				  	&&-0.5 <= srcz && srcz < in->HeaderN.z-0.5) {

					tdstx = x + dstx + offsetx; 
					tdsty = y + dsty + offsety; 
					tdstz = z + dstz + offsetz; 

					if( -0.5 <= tdstx && tdstx < out->HeaderN.x-0.5
					  &&-0.5 <= tdsty && tdsty < out->HeaderN.y-0.5
					  &&-0.5 <= tdstz && tdstz < out->HeaderN.z-0.5) { 

						mrcPixelDataGet(in,  srcx,  srcy,  srcz,  &dataIn, mrcPixelRePart, mrcPixelHowLinear);

						/* Attention!!! Essential: mrcPixelHowNearest */
						mrcPixelDataGet(out, tdstx, tdsty, tdstz, &data,   mrcPixelRePart, mrcPixelHowNearest);

/*
						if(40.0<data) {
							fprintf(stderr, "(%f, %f, %f) -> (%f %f %f): %f + %f = %f\n", 
																				srcx,  srcy,  srcz, 
							                                                    tdstx, tdsty, tdstz, 
																				data,
																				dataIn,
																				data+dataIn);
						}
*/
						mrcPixelDataSet(out, tdstx, tdsty, tdstz, data+dataIn, mrcPixelRePart);
					} 
				}
			}
		}
	}
}

