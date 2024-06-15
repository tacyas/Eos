/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% mrc2lattice ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : mrc2lattice
#%Z% Attention
#%Z%
*/

static char __sccs_id[] = "%Z%mrc2lattice ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"

#define DEBUG
#include "genUtil.h"
#include "mrcImage.h"
#include "Memory.h"

typedef int   explorerLatticeParaTypeInteger;
typedef float explorerLatticeParaTypeReal;

typedef enum explorerLatticePrimType {
	primTypeByte   = 0,
	primTypeShort  = 1,
	primTypeLong   = 2,
	primTypeFloat  = 3,
	primTypeDouble = 4
} explorerLatticePrimType;

typedef enum explorerLatticeCoordType {
	coordTypeUniform = 0,
	coordTypePerimeter = 1,
	coordTypeCurvilinear = 2
} explorerLatticeCoordType;

typedef struct explorerLattice {
	explorerLatticeParaTypeInteger  nDim;
	explorerLatticeParaTypeInteger* dims;
	explorerLatticeParaTypeInteger  nDataVar;
	explorerLatticePrimType  primType;
	explorerLatticeCoordType coordType;
	explorerLatticeParaTypeInteger  n_steps;
	explorerLatticeParaTypeInteger  nCoordVar;
	explorerLatticeParaTypeReal* coordMin;
	explorerLatticeParaTypeReal* coordMax;
	void* data;
} explorerLattice;

void
explorerLatticeWrite(FILE* fpt, explorerLattice* exLat, int mode)
{
	int i;
	explorerLatticeParaTypeInteger  nVar;
	explorerLatticeParaTypeInteger* coord;
	int dims;

	coord = (explorerLatticeParaTypeInteger*)memoryAllocate(
		sizeof(explorerLatticeParaTypeInteger)*exLat->nDim,
		"in explorerLatticeWrite");
	fprintf(fpt, "# nDim\n");
	fprintf(fpt, "%d\n", exLat->nDim);
	fprintf(fpt, "# dims[nDim]\n");
	for(i=0; i<exLat->nDim; i++) {
		fprintf(fpt,"%d ", exLat->dims[i]);
	}
	fprintf(fpt, "\n");
	fprintf(fpt, "# nDataVar\n");
	fprintf(fpt, "%d\n", exLat->nDataVar);
	fprintf(fpt, "# primType\n");
	fprintf(fpt, "%d\n", exLat->primType);
	fprintf(fpt, "# coordType\n");
	fprintf(fpt, "%d\n", exLat->coordType);
	fprintf(fpt, "# n_steps\n");
	fprintf(fpt, "%d\n", exLat->n_steps);
	if(coordTypeCurvilinear==exLat->coordType) {
		fprintf(fpt, "# nCoordVar\n");
		fprintf(fpt, "%d\n", exLat->nCoordVar);
	}
	switch(exLat->coordType) {
		case coordTypeUniform: {
			fprintf(fpt, "# coord Min Max\n");
			for(i=0; i<exLat->nDim; i++) {
				fprintf(fpt, "%f %f\n", 
					exLat->coordMin[i],
					exLat->coordMax[i]);
			}
			break;
		}
		default: {
			fprintf(stderr, "Not supported: %d\n", exLat->coordType);
			exit(EXIT_FAILURE);
			break;
		}
	}
	fprintf(fpt, "# Data \n");
	dims = 1;
	for(i=0; i<exLat->nDim; i++) {
		dims *= exLat->dims[i];
	}
	for(nVar=0; nVar<exLat->nDataVar; nVar++) {
		for(i=0; i<dims; i++) {
			switch(exLat->primType) {
				case primTypeDouble: 
				case primTypeFloat: {
					fprintf(fpt, "%15.6g ", (float)(*(((float*)exLat->data) + i + nVar)));
					break;
				}
				case primTypeShort: {
					fprintf(fpt,"%15d ", (short)(*(((short*)exLat->data) + i + nVar)));
					break;
				}
				default: {
					fprintf(stderr, "Not supported: %d\n", exLat->primType);
					exit(EXIT_FAILURE);
					break;
				}
			}
			if(0==i%exLat->dims[0]) {
				fprintf(fpt, "\n");
			}
		}
	}
}

void
explorerLatticeInit(explorerLattice* exLat, int nDim, int mode)
{
	exLat->nDim = nDim;
	exLat->dims     = (explorerLatticeParaTypeInteger*)memoryAllocate(sizeof(explorerLatticeParaTypeInteger)*nDim, "in exploreLatticeInit");
	exLat->coordMin = (explorerLatticeParaTypeReal*)memoryAllocate(sizeof(explorerLatticeParaTypeReal)*nDim, "in exploreLatticeInit");
	exLat->coordMax = (explorerLatticeParaTypeReal*)memoryAllocate(sizeof(explorerLatticeParaTypeReal)*nDim, "in exploreLatticeInit");

}

void
explorerLatticeDataInit(explorerLattice* exLat, int mode)
{
	int bytes;
	int i;

	bytes = 1; 
	for(i=0; i<exLat->nDim; i++) {
		bytes *= exLat->dims[i];  
	}
	bytes *= exLat->nDataVar; 

	switch(exLat->primType) {
		case primTypeShort: {
			bytes *= sizeof(float);
			break;
		}
		case primTypeFloat: {
			bytes *= sizeof(float);
			break;
		}
		default: {
			fprintf(stderr, "Not supported: %d\n", exLat->primType);
			exit(EXIT_FAILURE);
			break;
		}
	}
	exLat->data = (void*)memoryAllocate(bytes, "in explorerLatticeDataInit");
}

void
exploreLatticeDataSet(explorerLattice* exLat, 
					  explorerLatticeParaTypeInteger* coord,
					  explorerLatticeParaTypeInteger  nDataVar,
					  double data
					  )
{					 
	int i;
	int where;
	int byte;

	for(i=0; i<exLat->nDim; i++) {
		if(exLat->dims[i] <= coord[i]) {
			fprintf(stderr, "coord is not in the range\n");
			return;
		}
	}
	if(exLat->nDataVar<=nDataVar) {
		fprintf(stderr, "nDataVar is not in the range\n");
		return;
	}
	where = 0;
	for(i=exLat->nDim-1; i>0; i--) {
		where = (coord[i]+where)*exLat->dims[i-1];
	}
	where = where + coord[0] + nDataVar;
	switch(exLat->primType){
		case primTypeShort: {
			(short)(*(((short*)exLat->data) + where)) 
				= (short)data;
			break;
		}
		case primTypeFloat: {
			(float)(*(((float*)exLat->data) + where)) 
				= (float)data;
			break;
		}
		default: {
			break;
		}
	}
}

void
exploreLatticeDataGet(explorerLattice* exLat, 
					  explorerLatticeParaTypeInteger* coord,
					  explorerLatticeParaTypeInteger  nDataVar,
					  double* data
					  )
{					 
	int i;
	int where;
	int byte;

	for(i=0; i<exLat->nDim; i++) {
		if(exLat->dims[i] <= coord[i]) {
			fprintf(stderr, "coord is not in the range\n");
			return;
		}
	}
	if(exLat->nDataVar<=nDataVar) {
		fprintf(stderr, "nDataVar is not in the range\n");
		return;
	}
	where = 0;
	for(i=exLat->nDim-1; i>0; i--) {
		where = (coord[i]+where)*exLat->dims[i-1];
	}
	where = where + coord[0] + nDataVar;
	switch(exLat->primType){
		case primTypeShort: {
			*data = (short)(*(((short*)exLat->data) + where));
			break;
		}
		case primTypeFloat: {
			*data = (short)(*(((float*)exLat->data) + where));
			break;
		}
		default: {
			break;
		}
	}
}

void
lmrc2explorerLattice(explorerLattice* exLat, mrcImage* mrc, int mode)
{
	int nDim;	
		
	nDim = 0;
	if(1<mrc->HeaderN.x) {
		nDim++;
	}
	if(1<mrc->HeaderN.y) {
		nDim++;
	}
	if(1<mrc->HeaderN.z) {
		nDim++;
	}
	explorerLatticeInit(exLat, nDim, 0); 
	exLat->nDataVar = 1;
	switch(mrc->HeaderMode) {
		case mrcFloatImage: {
			exLat->primType = primTypeFloat;
			break;
		}
		case mrcShortImage: {
			exLat->primType = primTypeShort;
			break;
		}
		default: {
			fprintf(stderr, "Not supported HeaderMode\n");
			exit(EXIT_FAILURE);
		}
	}
	exLat->coordType = coordTypeUniform;
	exLat->n_steps   = 1;
	nDim = 0;
	if(1<mrc->HeaderN.x) {
		exLat->dims[nDim] = mrc->HeaderN.x;
		exLat->coordMin[nDim] = 0.0;
		exLat->coordMax[nDim] = mrc->HeaderLength.x*(mrc->HeaderN.x - 1);
		nDim++;
	}
	if(1<mrc->HeaderN.y) {
		exLat->dims[nDim] = mrc->HeaderN.y;
		exLat->coordMin[nDim] = 0.0;
		exLat->coordMax[nDim] = mrc->HeaderLength.y*(mrc->HeaderN.y - 1);
		nDim++;
	}
	if(1<mrc->HeaderN.z) {
		exLat->dims[nDim] = mrc->HeaderN.z;
		exLat->coordMin[nDim] = 0.0;
		exLat->coordMax[nDim] = mrc->HeaderLength.z*(mrc->HeaderN.z - 1);
		nDim++;
	}

	exLat->data = mrc->Image;
}

void
main(int argc, char* argv[]) 
{
	mrcImage mrc;
	explorerLattice exLat;
	mrc2latticeInfo info;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");
	mrcFileRead(&mrc, info.In, "in main", 0);

	lmrc2explorerLattice(&exLat, &mrc, 0);

	explorerLatticeWrite(info.fptOut, &exLat, 0);
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
}
