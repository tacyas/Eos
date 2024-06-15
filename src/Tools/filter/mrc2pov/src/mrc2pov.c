/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% mrc2pov ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : mrc2pov
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%mrc2pov ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"

#define DEBUG
#include "genUtil.h"
#include "eosString.h"
#include "File.h"
#include "mrcImage.h"
/*
#include "povRay.h"
*/

typedef struct povRay {
	FILE* fpt;
	char* filename;

	int flagShape;
	FILE* fptShape;
	char* shape;

	int flagTexture;
	FILE* fptTexture;
	char* texture;

	int flagLight;
	FILE* fptLight;
	char* light;

	int flagCamera;
	FILE* fptCamera;
	char* camera;
} povRay;

extern void povRayInit(povRay* pov, char* filename, int mode);
extern void povRayFileWrite(povRay* pov, int mode);

typedef enum lmrc2povInfoMode {
	lmrc2povInfoModeSection = 0,
	lmrc2povInfoModeSolid   = 1
} lmrc2povInfoMode;

typedef struct lmrc2povInfo {
	lmrc2povInfoMode mode;
	double* contourLevel;
	int     nContourLevel;
} lmrc2povInfo;

extern void lmrc2pov(povRay* pov, mrcImage* mrc, lmrc2povInfo* linfo, int mode);
extern void lmrc2povSection(povRay* pov, mrcImage* mrc, lmrc2povInfo* linfo, int mode);

void
main(int argc, char* argv[]) 
{
	mrcImage mrc;
	povRay   pov;
	mrc2povInfo   info;
	lmrc2povInfo linfo;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");
	mrcFileRead(&mrc, info.In, "main", 0);

	povRayInit(&pov, info.Out, 0);
	lmrc2pov(&pov, &mrc, &linfo, 0);


	povRayFileWrite(&pov, 0);
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
}


void 
lmrc2pov(povRay* pov, mrcImage* mrc, lmrc2povInfo* linfo, int mode)
{
	switch(linfo->mode) {
		case lmrc2povInfoModeSection: {
			lmrc2povSection(pov, mrc, linfo, mode);
			break;
		}
		default: {
			fprintf(stderr, "Sorry, Not supported mode: %d\n", linfo->mode);
			exit(EXIT_FAILURE);
			break;
		}
	}
}
void 
lmrc2povSection(povRay* pov, mrcImage* mrc, lmrc2povInfo* linfo, int mode)
{
	fprintf(pov->fpt, "object {\n");
	fprintf(pov->fpt, "    merge {\n");
	for(z=0; z<mrc->HeaderN.z; z++) {
		for(x=0; x<mrc->HeaderN.x; x++) {
		for(y=0; y<mrc->HeaderN.y; y++) {
			fprintf(pov->fpt, "object ");
		}
		}
	}
	fprintf(pov->fpt, "    }\n");
	fprintf(pov->fpt, "}\n");
}

void 
povRayInit(povRay* pov, char* filename, int mode)
{
	char s[1024];

	pov->filename = stringGetNthWord(filename, 1, " ");
	pov->fpt      = fileOpen(pov->filename, "w");
	if(pov->flagShape) {
		sprintf(s, "%s.shape", pov->filename);
		pov->shape = stringGetNthWord(s, 1, " ");
		pov->fptShape = fileOpen(pov->shape, "w");
	}
	if(pov->flagTexture) {
		sprintf(s, "%s.texture", pov->filename);
		pov->shape = stringGetNthWord(s, 1, " ");
		pov->fptTexture = fileOpen(pov->texture, "w");
	}
	if(pov->flagCamera) {
		sprintf(s, "%s.camera", pov->filename);
		pov->shape = stringGetNthWord(s, 1, " ");
		pov->fptCamera = fileOpen(pov->camera, "w");
	}
	if(pov->flagLight) {
		sprintf(s, "%s.light", pov->filename);
		pov->shape = stringGetNthWord(s, 1, " ");
		pov->fptLight = fileOpen(pov->light, "w");
	}
}

void 
povRayFileWrite(povRay* pov, int mode)
{
	if(pov->flagShape) {
		fprintf(pov->fpt, "#include \"%s\"", pov->shape);
	}
	if(pov->flagTexture) {
		fprintf(pov->fpt, "#include \"%s\"", pov->texture);
	}
	if(pov->flagCamera) {
		fprintf(pov->fpt, "#include \"%s\"", pov->camera);
	}
	if(pov->flagLight) {
		fprintf(pov->fpt, "#include \"%s\"", pov->light);
	}
}

