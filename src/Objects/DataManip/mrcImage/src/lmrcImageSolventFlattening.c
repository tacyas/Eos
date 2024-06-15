/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% lmrcImageSolventFlattening ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : lmrcImageSolventFlattening 
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%lmrcImageSolventFlattening ver%I%; Date:%D% %Z%";
#include "../inc/mrcImage.h"
#include "lmrcImageSolventFlattening.h"
#undef DEBUG
#include "genUtil.h"

void
lmrcImageSolventFlattening( mrcImage* out,
						    mrcImage* in,    
							lmrcImageSolventFlatteningInfo* linfo,
						    mrcImageInformation* info)
{
	mrcImageParaTypeReal x,y,z;	
	double data, mean;
	double sd;
	double threshold;

	out->Header = in->Header;
 	mrcInit(out, NULL);

	sd = 0; 	
	if (linfo->flagdensity){
		mean = linfo->density;
	} else {
		switch(info->mode){
			case meanOfAll:{
				DEBUGPRINT("meanOfAll\n");
				mean = info->mean;
				sd   = info->sd;
				break;
			}
			case meanOfCylinderSurface:{
				DEBUGPRINT("meanOfCylinderSurface\n");
				mean = info->meanOfCylinderSurface;
				sd   = info->sdOfCylinderSurface;
				break;
			}
			case meanOfSphereSurface:{
				DEBUGPRINT("meanOfSphereSurface\n");
				mean = info->meanOfSphereSurface;
				sd   = info->sdOfSphereSurface;
				break;
	   		}
			case meanOf2DEdgeY:{
				DEBUGPRINT("meanOf2DEdgeY\n");
				mean = info->meanOfEdge;
				sd   = info->sdOfEdge;
				break;
	   		}
			default:{
				fprintf(stderr, "Not supported mode :%d", info->mode);
				exit(EXIT_FAILURE);
			}
		}
	}

	if(linfo->flagrange) {
		threshold = mean+linfo->range*sd; 
	} else{
		threshold = mean; 
	}

	for(z=0; z<in->HeaderN.z; z++) {
	for(y=0; y<in->HeaderN.y; y++) {
	for(x=0; x<in->HeaderN.x; x++) {
		mrcPixelDataGet(in, x , y, z ,&data, mrcPixelRePart, mrcPixelHowNearest);
		DEBUGPRINT4("(x,y,z)=(%15.6f %15.6f %15.6f) data:%15.6f\n", x, y, z, data);
		if(linfo->flagFloating) {
			if(data<=threshold){
				mrcPixelDataSet(out, x, y, z, 0.0, mrcPixelRePart);
				DEBUGPRINT2("data:%15.6f <= thres:%15.6f   MEAN SET\n", data, mean);
			}else{
				mrcPixelDataSet(out, x, y, z, data-threshold, mrcPixelRePart);
				DEBUGPRINT2("data:%15.6f >  thres:%15.6f   DATA SET\n", data, mean);
			}
		} else {
			if(data<=threshold){
				mrcPixelDataSet(out, x, y, z, threshold, mrcPixelRePart);
				DEBUGPRINT2("data:%15.6f <= thres:%15.6f   MEAN SET\n", data, mean);
			}else{
				mrcPixelDataSet(out, x, y, z, data, mrcPixelRePart);
				DEBUGPRINT2("data:%15.6f >  thres:%15.6f   DATA SET\n", data, mean);
			}
		}
	}
	}
	}

	linfo->Mean = mean;	
	linfo->SD = sd;
}
