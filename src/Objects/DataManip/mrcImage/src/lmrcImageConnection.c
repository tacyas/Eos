/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% lmrcImageConnection ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : lmrcImageConnection 
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%lmrcImageConnection ver%I%; Date:%D% %Z%";

#include "lmrcImageConnection.h"
#undef DEBUG

void
lmrcImageConnection( mrcImage* out,
					 mrcImage* in1,    
					 mrcImage* in2,    
				    lmrcImageConnectionInfo* info)
{
	mrcImageParaTypeReal x1,y1,z1;	
	mrcImageParaTypeReal x2,y2,z2;	
	double data;

	out->Header = in1->Header;

	switch(info->mode){
		case 0:{
			DEBUGPRINT("z connection\n");

			out->HeaderN.z = in1->HeaderN.z + in2->HeaderN.z;
 			mrcInit(out, NULL);

			for(x1=0; x1<in1->HeaderN.x; x1++) {
				for(y1=0; y1<in1->HeaderN.y; y1++) {
					for(z1=0; z1<in1->HeaderN.z; z1++) {
			 			mrcPixelDataGet(in1, x1 , y1, z1 
										,&data, mrcPixelRePart, mrcPixelHowNearest);
						DEBUGPRINT4("(x1,y1,z1)=(%15.6f %15.6f %15.6f) data:%15.6f\n", x1, y1, z1, data);
						mrcPixelDataSet(out, x1, y1, z1,
										data, mrcPixelRePart);
					}
				}
			}

			for(x2=0; x2<in2->HeaderN.x; x2++) {
				for(y2=0; y2<in2->HeaderN.y; y2++) {
					for(z2=0; z2<in2->HeaderN.z; z2++) {
			 			mrcPixelDataGet(in2, x2 , y2, z2 
										,&data, mrcPixelRePart, mrcPixelHowNearest);
						DEBUGPRINT4("(x2,y2,z2)=(%15.6f %15.6f %15.6f) data:%15.6f\n", x2, y2, z2, data);
						mrcPixelDataSet(out, x2, y2, z2+in1->HeaderN.z, 
										data, mrcPixelRePart);
					}
				}
			}

			break;
		}
		default:{
			fprintf(stderr, "Not supported mode :%ld", info->mode);
			exit(EXIT_FAILURE);
		}
	}
	

}
