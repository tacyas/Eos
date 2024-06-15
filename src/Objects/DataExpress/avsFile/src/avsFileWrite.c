/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% avsFileWrite ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : avsFileWrite 
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%avsFileWrite ver%I%; Date:%D% %Z%";
#define DEBUG
#include "genUtil.h"
#include <stdio.h>
#include <stdlib.h>
#include "../inc/avsFile.h"
#include "Memory.h"

void
avsFileWrite(avsFile* avs, FILE* fpt, long mode)
{
	switch(avs->FileType) {
		case avsFileTypeField: {
			avsFileFieldWrite(&(avs->field), fpt, mode);
			break;
		}
		case avsFileTypeUCD: {
			avsFileUCDWrite(&(avs->UCD), fpt, mode);
			break;
		}
		default: {
			fprintf(stderr, "Not supported\n");
			break;
		}
	}
}

void
avsFileFieldWrite(avsFileField* avs, FILE* fpt, long mode)
{
	int i;
	size_t byte=1;

	fprintf(fpt, "# AVS field file\n");
	fprintf(fpt, "#\n");
	fprintf(fpt, "ndim = %d\n", avs->ndim);
	if(1<=avs->ndim) {
		fprintf(fpt, "dim1 = %d\n", avs->dim1);
	}
	if(2<=avs->ndim) {
		fprintf(fpt, "dim2 = %d\n", avs->dim2);
	}
	if(3<=avs->ndim) {
		fprintf(fpt, "dim3 = %d\n", avs->dim3);
	}
	fprintf(fpt, "nspace = %d\n", avs->nspace);
	fprintf(fpt, "veclen = %d\n", avs->veclen);

	switch(avs->dataType) {
		case avsFileFieldDataTypeByte: {
			fprintf(fpt, "data = byte\n");
			byte = 1;
			break;
		}
		case avsFileFieldDataTypeFloat: {
			fprintf(fpt, "data = float\n");
			byte = 4;
			break;
		}
		case avsFileFieldDataTypeDouble: {
			fprintf(fpt, "data = double\n");
			byte = 8;
			break;
		}
		default: {
			fprintf(stderr, "Not supported Dat Type: %d\n", avs->dataType);
			break;
		}
	}

	switch(avs->type) {
		case avsFileFieldTypeUniform: {
			fprintf(fpt, "field = uniform\n");
			break;
		}
		case avsFileFieldTypeRectilinear: {
			fprintf(fpt, "field = rectilinear\n");
			break;
		}
		default: {
			fprintf(stderr, "Not supported Field Type: %d\n", avs->type);
			break;	
		}
	}

	fprintf(fpt, "label = ");
	for(i=0; i<avs->veclen; i++) {
		fprintf(fpt, "%s ", avs->Label[i]);
	}
	fprintf(fpt, "\n");
	fprintf(fpt, "");

#ifdef M68
#else
	switch(avs->ndim) {
		case 1: {
			memoryByteSwap(avs->Image, byte, avs->dim1/byte*avs->veclen);
			break;
		}
		case 2: {
			memoryByteSwap(avs->Image, byte, avs->dim1*avs->dim2/byte*avs->veclen);
			break;
		}
		case 3: {
			memoryByteSwap(avs->Image, byte, avs->dim1*avs->dim2*avs->dim3/byte*avs->veclen);
			break;
		}
		default: {
			fprintf(stderr, "Not supported ndim: %d", avs->ndim);
			exit(EXIT_FAILURE);
		}
	}
#endif
	switch(avs->ndim) {
		case 1: {
			fwrite(avs->Image, byte, avs->dim1*avs->veclen, fpt);
			break;
		}
		case 2: {
			fwrite(avs->Image, byte, avs->dim1*avs->dim2*avs->veclen, fpt);
			break;
		}
		case 3: {
			fwrite(avs->Image, byte, avs->dim1*avs->dim2*avs->dim3*avs->veclen, fpt);
			break;
		}
		default: {
			fprintf(stderr, "Not supported ndim: %d", avs->ndim);
			exit(EXIT_FAILURE);
		}
	}

	switch(avs->type) {
		case avsFileFieldTypeRectilinear: {
#ifdef M68
#else
			switch(avs->ndim) {
		        case 1: {
       				memoryByteSwap(avs->Coord[0], sizeof(float), avs->dim1/sizeof(float));
            		break;
        		}
        		case 2: {
            		memoryByteSwap(avs->Coord[0], sizeof(float), avs->dim1/sizeof(float));
            		memoryByteSwap(avs->Coord[1], sizeof(float), avs->dim2/sizeof(float));
            		break;  
        		}
        		case 3: {
					DEBUGPRINT3("Before ByteSwap: %f %f %f\n", avs->Coord[0][1], avs->Coord[1][1], avs->Coord[2][1]);
					/*
            		memoryByteSwap(avs->Coord[0], sizeof(float), avs->dim1/sizeof(float));
            		memoryByteSwap(avs->Coord[1], sizeof(float), avs->dim2/sizeof(float));
            		memoryByteSwap(avs->Coord[2], sizeof(float), avs->dim3/sizeof(float));
					*/
					DEBUGPRINT3("After ByteSwap: %f %f %f\n", avs->Coord[0][1], avs->Coord[1][1], avs->Coord[2][1]);
            		break;  
				}
			}
#endif
			switch(avs->ndim) {
		        case 1: {
       				fwrite(avs->Coord[0], sizeof(float), avs->dim1, fpt);
            		break;
        		}
        		case 2: {
            		fwrite(avs->Coord[0], sizeof(float), avs->dim1, fpt);
            		fwrite(avs->Coord[1], sizeof(float), avs->dim2, fpt);
            		break;  
        		}
        		case 3: {
            		fwrite(avs->Coord[0], sizeof(float), avs->dim1, fpt);
            		fwrite(avs->Coord[1], sizeof(float), avs->dim2, fpt);
            		fwrite(avs->Coord[2], sizeof(float), avs->dim3, fpt);
            		break;  
				}
			}
			break;
        }       
		default: {
			break;
		}
    }

}

void
avsFileUCDWrite(avsFileUCD* avs, FILE* fpt, long mode)
{
	avsFileParaTypeInteger i, j, k;

	/* Data Size Set */
	fprintf(fpt, "%d %d %d %d %d\n", avs->nNode,
									 avs->nCell,
									 avs->nNodeComponent,
									 avs->nCellComponent,
									 avs->nModel);
	/* Node Position Set */
	for(i=0; i<avs->nNode; i++) {
		fprintf(fpt, "%d %f %f %f\n", avs->Node[i].ID,	
									  avs->Node[i].x,
									  avs->Node[i].y,
									  avs->Node[i].z);
	}
	/* Cell Information Set */
	for(i=0; i<avs->nCell; i++) {
		fprintf(fpt, "%d %d ", avs->Cell[i].ID,
							   avs->Cell[i].MaterialID);
		switch(avs->Cell[i].Type) {
			case avsFileUCDCellTypeLine: {
				fprintf(fpt, "line ");
				for(j=0; j<2; j++) {
					fprintf(fpt, "%d ", avs->Cell[i].Node[j]->ID);
				}
				fprintf(fpt, "\n");
				break;
			}
			default: {
				fprintf(stderr, "Not supported\n");
				break;
			}
		}
	}

	/* Node Data Set */
	if(0!=avs->nNodeComponent) {
		DEBUGPRINT1("nNodeComponent %d", avs->nNodeComponent);
		fprintf(fpt, "%d ", avs->nNodeComponent);
		for(i=0; i<avs->nNodeComponent; i++) {
			DEBUGPRINT1("nElement %d\n", avs->NodeComponent[i].nElement);
			fprintf(fpt, "%d ", avs->NodeComponent[i].nElement);
		}
		fprintf(fpt, "\n");
		for(i=0; i<avs->nNodeComponent; i++) {
			DEBUGPRINT3("%d %s %s\n", i, avs->NodeComponent[i].Label, avs->NodeComponent[i].Unit);
			fprintf(fpt, "%s, %s\n", avs->NodeComponent[i].Label,
			                         avs->NodeComponent[i].Unit);
		}
		for(i=0; i<avs->nNode; i++) {
			fprintf(fpt, "%d ", avs->Node[i].ID);
			for(j=0; j<avs->nNodeComponent; j++) {
				for(k=0; k<avs->NodeComponent[j].nElement; k++) {
					fprintf(fpt, "%f ", avs->Node[i].Component[j].data[k]);
				}
			}
			fprintf(fpt, "\n");
		}
	}

	/* Cell Data Set */
	if(0!=avs->nCellComponent) {
		fprintf(fpt, "%d ", avs->nCellComponent);
		for(i=0; i<avs->nCellComponent; i++) {
			fprintf(fpt, "%d ", avs->CellComponent[i].nElement);
		}
		fprintf(fpt, "\n");
		for(i=0; i<avs->nCellComponent; i++) {
			fprintf(fpt, "%s, %s", avs->CellComponent[i].Label,
			                       avs->CellComponent[i].Unit);
		}
		for(i=0; i<avs->nCell; i++) {
			fprintf(fpt, "%d ", avs->Cell[i].ID);
			for(j=0; j<avs->nCellComponent; j++) {
				for(k=0; k<avs->CellComponent[j].nElement; k++) {
					fprintf(fpt, "%f ", avs->Cell[i].Component[j].data[k]);
				}
			}
			fprintf(fpt, "\n");
		}
	}
}
