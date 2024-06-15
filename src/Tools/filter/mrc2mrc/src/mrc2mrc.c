/*
# mrc2mrc : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : mrc2mrc
# Attention
#   $Loccker$
#  	$State$ 
#
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"

#define DEBUG
#include "genUtil.h"
#include "mrcImage.h"

/*
Example:
typedef struct lmrc2mrcInfo {
	float a;
	int   b;
} lmrc2mrcInfo;

typedef enum lmrc2mrcMode {
	a=0,
	b=1
} lmrc2mrcMode;
*/

int lmrc2mrc(mrcImage* out, char* outType, mrcImage* in, char* inType, int mode) ;


int
main(int argc, char* argv[]) 
{
	mrc2mrcInfo info;
	mrcImage in;
	mrcImage out;
	mrcImage header;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");
	memset(&in, 0, sizeof(in));
	mrcFileReadGeneral(&in, info.In, info.InType, "in main", info.mode);

	if(info.flagLenX) {
		in.HeaderLength.x = info.LenX; 
		in.HeaderLength.y = info.LenY;
		in.HeaderLength.z = info.LenZ;
	}
	if(info.flagMx) {
		in.HeaderM.x = info.Mx; 
		in.HeaderM.y = info.My;
		in.HeaderM.z = info.Mz;
	}
	if(info.flagStat) {
		mrcStatDataSet(&in, 0);
	}

	lmrc2mrc(&out, info.OutType, &in, info.InType, info.mode) ;

	mrcFileWrite(&out, info.Out, "in main", info.mode);

	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
	fprintf(stderr, ">> To be suppoerted (Not all)\n");
	mrcFileGeneralListPrint(stderr);
}


int 
lmrc2mrc(mrcImage* out, char* outType, mrcImage* in, char* inType, int mode)
{
	int ix, iy, iz, index;

	SSWITCH(inType) 
		SCASE("Eos") {
			SSWITCH(outType) 
				SCASE("Eos") {
					*out = *in;
					SBREAK;
				}
				SDEFAULT {
					fprintf(stderr, "Not supported and so I try Eos as OutType\n");
					*out = *in;	
					SBREAK;
				}
			SSWITCHEND;
			SBREAK;
		}
		SCASE("FEIextendedMRC") {
			SSWITCH(outType) 
				SCASE("Eos") {
					switch(in->HeaderMode) {
						case mrcShortImage: {
							out->Header.Cont = in->Header.Cont;
							out->Header.Cont.Mode = mrcFloatImage;
							mrcInit(out, NULL);
							for(iz=0; iz<in->HeaderN.z; iz++) { 
							for(iy=0; iy<in->HeaderN.y; iy++) { 
							for(ix=0; ix<in->HeaderN.x; ix++) { 
								index = ix + iy*in->HeaderN.x + iz*in->HeaderN.x*in->HeaderN.y;
								out->ImageFloatImage[index] = (float)((signed short)in->ImageShortImage[index]);
							}
							}
							}
							break;
						}
						default: {
							*out = *in;
							break;
						}
					}
					SBREAK;
				}
				SDEFAULT {
					fprintf(stderr, "Not supported and so I try Eos as OutType\n");
					*out = *in;	
					SBREAK;
				}
			SSWITCHEND;
			SBREAK;
		}
		SCASE("IMODextendedMRC") {
			SSWITCH(outType) 
				SCASE("Eos") {
					switch(in->HeaderMode) {
						case mrcShortImage: {
							out->Header.Cont = in->Header.Cont;
							out->Header.Cont.Mode = mrcFloatImage;
							mrcInit(out, NULL);
							for(iz=0; iz<in->HeaderN.z; iz++) { 
							for(iy=0; iy<in->HeaderN.y; iy++) { 
							for(ix=0; ix<in->HeaderN.x; ix++) { 
								index = ix + iy*in->HeaderN.x + iz*in->HeaderN.x*in->HeaderN.y;
								out->ImageFloatImage[index] = (float)((signed short)in->ImageShortImage[index]);
							}
							}
							}
							break;
						}
						case mrcUShortImage: {
							out->Header.Cont = in->Header.Cont;
							out->Header.Cont.Mode = mrcFloatImage;
							mrcInit(out, NULL);
							for(iz=0; iz<in->HeaderN.z; iz++) { 
							for(iy=0; iy<in->HeaderN.y; iy++) { 
							for(ix=0; ix<in->HeaderN.x; ix++) { 
								index = ix + iy*in->HeaderN.x + iz*in->HeaderN.x*in->HeaderN.y;
								out->ImageFloatImage[index] = (float)((unsigned short)in->ImageShortImage[index]);
							}
							}
							}
							break;
						}
						default: {
							*out = *in;
							break;
						}
					}
					SBREAK;
				}
				SDEFAULT {
					fprintf(stderr, "Not supported and so I try Eos as OutType\n");
					*out = *in;	
					SBREAK;
				}
			SSWITCHEND;
			SBREAK;
		}
		SDEFAULT {
			*out = *in;	
			SBREAK;
		}
	SSWITCHEND;
	return 0;
}
