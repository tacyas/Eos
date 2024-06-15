/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% lmrcImageFilterCreate ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : lmrcImageFilterCreate 
#%Z% Attention
#%Z%
*/
#include "Memory.h"
#include "eosString.h"
#include "lmrcImageFilterCreate.h"

static char __sccs_id[] = "%Z%lmrcImageFilterCreate ver%I%; Date:%D% %Z%";

void 
lmrcImageFilterInfoFileRead(FILE* fpt, lmrcImageFilterCreateInfo* linfo, int mode)
{
	int i, n;
	char s[1024][1024];
	
	fseek(fpt, 0L, SEEK_SET);
	n = 0;
	while(NULL!=stringGetFromFile(s[n], "", fpt, stdout, 3)) {
		n++;
	}
	linfo->np = n;
	linfo->p      = (mrcImageParaTypeRealCoord*)memoryAllocate(sizeof(mrcImageParaTypeRealCoord)*n, "in ");
	linfo->weight = (mrcImageParaTypeReal*)memoryAllocate(sizeof(mrcImageParaTypeReal)*n, "in ");

	for(i=0; i<n; i++) {
		linfo->p[i].x = stringGetNthRealData(s[i], 1, " \t,");
		linfo->p[i].y = stringGetNthRealData(s[i], 2, " \t,");
		linfo->p[i].z = stringGetNthRealData(s[i], 3, " \t,");
		linfo->weight[i] = stringGetNthRealData(s[i], 4, " \t,");
	}
}
void 
lmrcImageFilterInfoPrint(FILE* fpt, lmrcImageFilterCreateInfo linfo, int mode)
{
	int i;
		
	fprintf(fpt, "np %d\n", linfo.np); 
	for(i=0; i<linfo.np; i++) {
		fprintf(fpt, "p %d %f %f %f %f\n", i, linfo.p[i].x, linfo.p[i].y, linfo.p[i].z, linfo.weight[i]);
	}
	fprintf(fpt, "Size %d %d %d\n", linfo.Size.x, linfo.Size.y, linfo.Size.z);
	fprintf(fpt, "N    %d %d %d\n", linfo.N.x,    linfo.N.y,    linfo.N.z);
	fprintf(fpt, "Shape "); 
	switch(linfo.shape) {
		case lmrcImageFilterModeSquare: {
			fprintf(fpt, "Square\n");
			break;
		}
		case lmrcImageFilterModeCircle: {
			fprintf(fpt, "Circle\n");
			break;
		}
		default: {
			fprintf(stderr, "Not supported shape in lmrcImageFilterInfoPrint : %d\n",linfo.shape); 
			exit(EXIT_FAILURE);
		}
	}
	fprintf(fpt, "outputMode %d\n", linfo.outputMode);
}

void 
lmrcImageFilterInfoFileFormat(FILE* fpt, int mode)
{
	    fprintf(fpt, "x0 y0 z0 weight0\n");
		fprintf(fpt, "x1 y1 z1 weight1\n");
		fprintf(fpt, "......          \n");
}

void 
lmrcImageFilterCreate(mrcImage* out, lmrcImageFilterCreateInfo linfo, int mode)
{
	mrcImageParaTypeReal x, y, z;
	mrcImageParaTypeReal X, Y, Z;
	mrcImageParaTypeReal sx2, sy2, sz2;
	int i;

	mrcDefaultHeaderValueSet(out);
	out->HeaderN.x = linfo.N.x;
	out->HeaderN.y = linfo.N.y;
	out->HeaderN.z = linfo.N.z;
	out->HeaderMode = linfo.outputMode;	
	mrcInit(out, NULL);

	sx2 = (linfo.Size.x - 1)/2.0;
	sy2 = (linfo.Size.y - 1)/2.0;
	sz2 = (linfo.Size.z - 1)/2.0;
	switch(linfo.shape) {
		case lmrcImageFilterModeCircle: {
			if(sx2 == 0 || sy2 == 0) {
				fprintf(stderr, "When shape is circle, Size must be > 1\n");
				exit(EXIT_FAILURE);
			}
			break;
		}
		default: {
			break;
		}
	}
	for(i=0; i<linfo.np; i++) {
		if(IsImage(out, "in lmrcImageFilterCreate", 0)) {
			for(x=linfo.p[i].x - sx2; x<=linfo.p[i].x + sx2; x++) {
			for(y=linfo.p[i].y - sy2; y<=linfo.p[i].y + sy2; y++) {
			for(z=linfo.p[i].z - sz2; z<=linfo.p[i].z + sz2; z++) {
				switch(linfo.shape) {
					case lmrcImageFilterModeSquare: {
						mrcPixelDataSet(out, x, y, z, linfo.weight[i], mrcPixelRePart);
						break;
					}
					case lmrcImageFilterModeCircle: {
						if(SQR((x-linfo.p[i].x)/sx2)
						  +SQR((y-linfo.p[i].y)/sy2) <= 1 
						 && 
						  z == linfo.p[i].z ) {
						  	mrcPixelDataSet(out, x, y, z, linfo.weight[i], mrcPixelRePart);
						} else if(SQR((x-linfo.p[i].x)/sx2)
						  +SQR((y-linfo.p[i].y)/sy2)
						  +SQR((z-linfo.p[i].z)/sz2)<=1) {
							mrcPixelDataSet(out, x, y, z, linfo.weight[i], mrcPixelRePart);
						}
						break;
					}
				}
			}
			}	
			}
		} else if(IsFT(out, "in lmrcImageFilterCreate", 0)) {
			for(X=linfo.p[i].x - sx2; X<=linfo.p[i].x + sx2; X++) {
			for(Y=linfo.p[i].y - sy2; Y<=linfo.p[i].y + sy2; Y++) {
			for(Z=linfo.p[i].z - sz2; Z<=linfo.p[i].z + sz2; Z++) {
				switch(linfo.shape) {
					case lmrcImageFilterModeSquare: {
						mrcPixelDataSet(out, X, Y, Z, linfo.weight[i], mrcPixelRePart);
						mrcPixelDataSet(out, X, Y, Z, 0.0,             mrcPixelImPart);
						break;
					}
					case lmrcImageFilterModeCircle: {
						if(SQR((x-linfo.p[i].x)/sx2)
						  +SQR((y-linfo.p[i].y)/sy2) <= 1 
						 && 
						  z == linfo.p[i].z ) {
						  	mrcPixelDataSet(out, x, y, z, linfo.weight[i], mrcPixelRePart);
						  	mrcPixelDataSet(out, x, y, z, 0.0,             mrcPixelImPart);
						} else if(SQR((X-linfo.p[i].x)/sx2)
						  +SQR((Y-linfo.p[i].y)/sy2)
						  +SQR((Z-linfo.p[i].z)/sz2)<=1) {
							mrcPixelDataSet(out, X, Y, Z, linfo.weight[i], mrcPixelRePart);
							mrcPixelDataSet(out, X, Y, Z, 0.0,             mrcPixelImPart);
						}
						break;
					}
				}
			}
			}	
			}
		} else {
			fprintf(stderr, "Not supported\n");
			exit(EXIT_FAILURE);
		}
	}
}
