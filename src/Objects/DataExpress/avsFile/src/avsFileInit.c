/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% avsFileInit ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : avsFileInit 
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%avsFileInit ver%I%; Date:%D% %Z%";
#undef DEBUG
#include "genUtil.h"
#include <string.h>
#include "Memory.h"
#include "../inc/avsFile.h"

void
avsFileInit(avsFile* avs, long mode)
{
	switch(avs->FileType) {
		case avsFileTypeUCD: {
			avsFileUCDInit(&(avs->UCD), mode);	
			break;
		}
		case avsFileTypeField: {
			avsFileFieldInit(&(avs->field), mode);	
			break;
		}
		default: {
			fprintf(stderr, "Not supported");
			break;
		}
	}
}
/*
	field
*/
void
avsFileFieldInit(avsFileField* avs, long mode)
{
	int i;
	size_t byte=1;

	/* Label */
	avs->Label = (char**)memoryAllocate(sizeof(char*)*avs->veclen, "in avsFileFieldInit");	

	/* Image */
	switch(avs->dataType) {
        case avsFileFieldDataTypeByte: {
            byte = 1;
            break;
        }
        case avsFileFieldDataTypeFloat: {
            byte = 4;
            break;
        }
        case avsFileFieldDataTypeDouble: {
            byte = 8;
            break;
        }
        default: {
            fprintf(stderr, "Not supported Dat Type: %d\n", avs->dataType);
			exit(EXIT_FAILURE);
            break;
        }
    }
	switch(avs->ndim) {
		case 1: {
			avs->Image = (void*)memoryAllocate(byte*avs->dim1*avs->veclen, "in avsFileFieldInit");
			break;
		}
		case 2: {
			avs->Image = (void*)memoryAllocate(byte*avs->dim1*avs->dim2*avs->veclen, 
					"in avsFileFieldInit");
			break;
		}
		case 3: {
			avs->Image = (void*)memoryAllocate(byte*avs->dim1*avs->dim2*avs->dim3*avs->veclen, 
					"in avsFileFieldInit");
			break;
		}
	}
	/* Coordinate */
    switch(avs->type) {
        case avsFileFieldTypeRectilinear: {
			avs->Coord = (float**)memoryAllocate(sizeof(float*)*avs->ndim, "in avsFileFieldInit");
		    switch(avs->ndim) {
   		    	case 1: {
					avs->Coord[0] = (float*)memoryAllocate(sizeof(float)*avs->dim1, "in avsFileFieldInit");
            		break;
        		}
        		case 2: {
					avs->Coord[0] = (float*)memoryAllocate(sizeof(float)*avs->dim1, "in avsFileFieldInit");
					avs->Coord[1] = (float*)memoryAllocate(sizeof(float)*avs->dim2, "in avsFileFieldInit");
            		break;  
        		}
        		case 3: {
					avs->Coord[0] = (float*)memoryAllocate(sizeof(float)*avs->dim1, "in avsFileFieldInit");
					avs->Coord[1] = (float*)memoryAllocate(sizeof(float)*avs->dim2, "in avsFileFieldInit");
					avs->Coord[2] = (float*)memoryAllocate(sizeof(float)*avs->dim3, "in avsFileFieldInit");
            		break;  
        		}       
				default: {
					fprintf(stderr, "Not supproted\n");
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
/*
	UCD
*/
void
avsFileUCDInit(avsFileUCD* avs, long mode)
{
	avsFileUCDGlobalInit(avs, mode);
}
/*
	nNode
	nCell
	nModel
	nNodeComponent
	nCellComponent
*/
void
avsFileUCDGlobalInit(avsFileUCD* avs, long mode)
{
	int i;

	DEBUGPRINT("GlobalInit--");
	DEBUGPRINT2("Start[%d, %d]--", avs->nNode, avs->nCell);
	if(0!=avs->nNode) {
    	avs->Node = (avsFileUCDNode*)memoryAllocate(sizeof(avsFileUCDNode)*avs->nNode, 
			"in avsFileUCDGlobalInit");
	}
	if(0!=avs->nCell) {
    	avs->Cell = (avsFileUCDCell*)memoryAllocate(sizeof(avsFileUCDCell)*avs->nCell,
			"in avsFileUCDGlobalInit");
	}
	DEBUGPRINT("NodeComponent--");
	if(0!=avs->nNodeComponent) {
		avs->NodeComponent = (avsFileUCDComponent*)
			memoryAllocate(sizeof(avsFileUCDComponent)*avs->nNodeComponent,
			"in avsFileUCDGlobalInit");
	}	
	for(i=0; i<avs->nNode; i++) {
		avs->Node[i].Component = (avsFileUCDComponentData*)
			memoryAllocate(sizeof(avsFileUCDComponentData)*avs->nNodeComponent,
			"in avsFileUCDGlobalInit");
	}

	DEBUGPRINT1("CellComponent[%d]--", avs->nCellComponent);
	if(0!=avs->nCellComponent) {
		avs->CellComponent = (avsFileUCDComponent*)
			memoryAllocate(sizeof(avsFileUCDComponent)*avs->nCellComponent,
			"in avsFileUCDGlobalInit");
	}
	for(i=0; i<avs->nCell; i++) {
		if(0!=avs->nCellComponent) {
			avs->Cell[i].Component = (avsFileUCDComponentData*)
				memoryAllocate(sizeof(avsFileUCDComponentData)*avs->nCellComponent,
				"in avsFileUCDGlobalInit");
		}				
	}
}

void 
avsFileUCDNodeComponentInit(avsFileUCD* avs, int ID, int nElement, char* Label, char* Unit, long mode)
{
	int i;

	if(0!=avs->nNodeComponent) {
		avs->NodeComponent[ID].nElement = nElement;
		avs->NodeComponent[ID].Label    = strdup(Label);
		avs->NodeComponent[ID].Unit     = strdup(Unit);
		for(i=0; i<avs->nNode; i++) {
			if(0!=nElement) {
				avs->Node[i].Component[ID].data = (avsFileParaTypeReal*)
					memoryAllocate(sizeof(avsFileParaTypeReal)*nElement,
					"in avsFileUCDNOdeComponentInit");
			}
		}
	}
}

void
avsFileUCDCellComponentInit(avsFileUCD* avs, int ID, int nElement, char* Label, char* Unit, long mode)
{
	int i;
	
	if(0!=avs->nCellComponent) {
		avs->CellComponent[ID].nElement = nElement;
		avs->CellComponent[ID].Label    = strdup(Label);
		avs->CellComponent[ID].Unit     = strdup(Unit);
		for(i=0; i<avs->nCell; i++) {
			if(0!=nElement) {
				avs->Cell[i].Component[ID].data = (avsFileParaTypeReal*)
					memoryAllocate(sizeof(avsFileParaTypeReal)*nElement,
					"in avsFileUCDCellComponentInit");
			}
		}
	}
}
	
