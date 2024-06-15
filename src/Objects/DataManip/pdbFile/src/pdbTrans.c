/*
# pdbTrans.c  1.1
# The latest update : 07/13/96 at 11:39:21
#
#@(#) pdbTrans ver 1.1
#@(#) Created by 
#@(#)
#@(#) Usage : pdbTrans 
#@(#) Attention
#@(#)
*/
static char __sccs_id[] = "@(#)pdbTrans ver1.1; Date:96/07/13 @(#)";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#undef DEBUG
#undef DEBUG2
#include "../inc/pdbFile.h"
#include "eosString.h"
#include "eosCuda.h"
#include "genUtil.h"
#include "Vector.h"
#include "Matrix3D.h"
#include "Memory.h"

void
pdbMatrixFileFormat(FILE* fpt)
{
	matrix3DFileFormat(fpt);
}
void
pdbMatrixFileRead(FILE* fpt, Matrix3D Matrix)
{
	matrix3DFileRead(fpt, Matrix);
}
void
pdbMatrixFileWrite(FILE* fpt, Matrix3D Matrix)
{
	matrix3DFileWrite(fpt, Matrix);
}

#ifndef CUDA
int __eosCuda__ = 0;
#endif

void
pdbTrans(pdbFile* pdb, Matrix3D Matrix)
{
	floatVector v;
	clock_t t1;
	clock_t t2;

	DEBUGPRINT("pdbTrans Start\n");
	DEBUGCOMMAND(t1=clock());

	if(__eosCuda__) {
#ifndef CUDA
		fprintf(stderr, "Not supported CUDA\n");
		exit(EXIT_FAILURE);
#else
		float * hv;
		int i;
			
		hv    =  (float*)memoryAllocate(sizeof(float)*pdb->nAtom*4, "in pdbTransCuda");

		// List to Array 
    	i=0;
    	pdbFileTop(pdb);
    	//DEBUGPRINT2("%p %p\n", pdb->PDB, pdb->top);
    	while(NULL!=pdb->PDB) {
        	if(pdbFileIsAtom(pdb)) {
            	hv[i*4+0] = pdb->PDB->Coord.x;      
            	hv[i*4+1] = pdb->PDB->Coord.y;      
            	hv[i*4+2] = pdb->PDB->Coord.z;      
            	hv[i*4+3] = 1;
            	//DEBUGPRINT3("%f %f %f\n", hv[i*4+0], hv[i*4+1], hv[i*4+2]);
            	i++;
        	}   
        	//DEBUGPRINT2("%s next %p\n", pdb->PDB->FullRecord, pdb->PDB->next);
        	pdb->PDB = pdb->PDB->next;
    	}   
    	//DEBUGPRINT2("%d %d\n", pdb->nAtom, i); 
    	pdb->nAtom = i;
		
		//pdbTransCuda(pdb, Matrix);
		pdbTransCuda(hv, pdb->nAtom, Matrix);

		// Array to List
		
		i=0;
		pdbFileTop(pdb);
		//DEBUGPRINT2("%p %p\n", pdb->PDB, pdb->top);
		while(NULL!=pdb->PDB) {
			if(pdbFileIsAtom(pdb)) {
				//DEBUGPRINT3("%f %f %f\n", hv[i*4+0], hv[i*4+1], hv[i*4+2]);
				pdb->PDB->Coord.x = hv[i*4+0];    
				pdb->PDB->Coord.y = hv[i*4+1];    
				pdb->PDB->Coord.z = hv[i*4+2];    
				i++;
			}   
			pdb->PDB = pdb->PDB->next;
		}   
		memoryFree(hv);
#endif
	} else {
		floatVectorInit(&v, 4);
		v.data[3] = 1.0;

#ifdef DEBUG
	{
		int ii, jj;
		for(ii=0; ii<4; ii++) {
		for(jj=0; jj<4; jj++) {
			DEBUGPRINT1("%f ", Matrix[ii][jj]);
		}
			DEBUGPRINT("\n");
		}
	}
#endif
		pdbFileTop(pdb);
		while(1) {
		  if(0==strncmp(pdb->PDB->Record, pdbRecordAtom,       PDB_FILE_RECORD_LENGTH)
		   ||0==strncmp(pdb->PDB->Record, pdbRecordHeteroAtom, PDB_FILE_RECORD_LENGTH)) {
			
			v.data[0] = pdb->PDB->Coord.x;
			v.data[1] = pdb->PDB->Coord.y;
			v.data[2] = pdb->PDB->Coord.z;

			matrix3DMultiplyVector(&v, Matrix);

#ifdef DEBUG2
			DEBUGPRINT3("%f %f %f\n", Matrix[3][0], Matrix[3][1], Matrix[3][2]);
			DEBUGPRINT2("x %f -> %f\n", pdb->PDB->Coord.x, v.data[0]);
			DEBUGPRINT2("y %f -> %f\n", pdb->PDB->Coord.y, v.data[1]);
			DEBUGPRINT2("z %f -> %f\n", pdb->PDB->Coord.z, v.data[2]);
#endif

		    pdb->PDB->Coord.x = v.data[0];
		    pdb->PDB->Coord.y = v.data[1];
		    pdb->PDB->Coord.z = v.data[2];

		  }
		  if(NULL==pdb->PDB->next) {
		    break;
		  } else {
		    pdb->PDB = pdb->PDB->next;
		  }    
		}
		floatVectorFree(&v);
	}

	DEBUGCOMMAND(t2=clock());
	DEBUGPRINT1("%ld\n", t2-t1);
	DEBUGPRINT("pdbTrans End\n");
}

