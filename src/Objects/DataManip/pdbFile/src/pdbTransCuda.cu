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
//static char __sccs_id[] = "@(#)pdbTrans ver1.1; Date:96/07/13 @(#)";

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <cuda.h>
#include <sys/times.h>

#undef DEBUG
extern "C" {
#include "../inc/pdbFile.h"
#include "String.h"
#include "eosCuda.h"
#include "genUtil.h"
#include "Vector.h"
#include "Memory.h"
#include "Matrix3D.h"
};
// pdbTransKernel
// pdbTransXXXKernel: __global__
// pdbTrasnKernelYYY: __device__  
// pdbTrans: __host__

__global__ void pdbTransKernel(float* v, float* mat, int max)
{
	int offset = threadIdx.x + blockIdx.x*blockDim.x;
	float vx, vy, vz, w;
	if(offset<max) {
		vx = v[offset*4+0];
		vy = v[offset*4+1];
		vz = v[offset*4+2];
		w  = v[offset*4+3];

		v[offset*4+0]=mat[0+4*0]*vx + mat[0+4*1]*vy + mat[0+4*2]*vz + mat[0+4*3]*w;
		v[offset*4+1]=mat[1+4*0]*vx + mat[1+4*1]*vy + mat[1+4*2]*vz + mat[1+4*3]*w;
		v[offset*4+2]=mat[2+4*0]*vx + mat[2+4*1]*vy + mat[2+4*2]*vz + mat[2+4*3]*w;
	}
}

void
//pdbTransCuda(pdbFile* pdb, Matrix3D Matrix)
pdbTransCuda(float* hv, int nAtom, Matrix3D Matrix)
{
	//int i;
	//int nAtom;
	//float* hv;
	float* dv;
	float* dmat;
	cudaError_t error;
	clock_t t1;
	clock_t t2;

	DEBUGPRINT("pdbTransCuda Start\n");
	DEBUGCOMMAND(t1=clock());
// List to Array 
/*
	nAtom= pdb->nAtom;

	hv    =  (float*)memoryAllocate(sizeof(float)*nAtom*4, "in pdbTransCuda");

	i=0;
	pdbFileTop(pdb);
	DEBUGPRINT2("%p %p\n", pdb->PDB, pdb->top);
	while(NULL!=pdb->PDB) {
		if(pdbFileIsAtom(pdb)) {
			hv[i*4+0] = pdb->PDB->Coord.x; 		
			hv[i*4+1] = pdb->PDB->Coord.y; 		
			hv[i*4+2] = pdb->PDB->Coord.z; 		
			hv[i*4+3] = 1;
		 	DEBUGPRINT3("%f %f %f\n", hv[i*4+0], hv[i*4+1], hv[i*4+2]);
			i++;
		}
		DEBUGPRINT2("%s next %p\n", pdb->PDB->FullRecord, pdb->PDB->next);
	    pdb->PDB = pdb->PDB->next;
	}
	DEBUGPRINT2("%d %d\n", nAtom, i);
	pdb->nAtom = i;
*/

// Array to Cuda 
	error = cudaMalloc((void **) &dv, sizeof(float)*nAtom*4);
	if (error != cudaSuccess) {
		printf("cudaMalloc dv returned error code %d, line(%d)\n", error, __LINE__);
		exit(EXIT_FAILURE);
	}
	error = cudaMalloc((void **) &dmat, sizeof(float)*4*4);
	if (error != cudaSuccess) {
		printf("cudaMalloc dv returned error code %d, line(%d)\n", error, __LINE__);
		exit(EXIT_FAILURE);
	}

	error = cudaMemcpy(dv, hv, nAtom*4*sizeof(float), cudaMemcpyHostToDevice);
	if (error != cudaSuccess) {
		printf("cudaMemcpy %d, line(%d)\n", error, __LINE__);
		exit(EXIT_FAILURE);
	}

	error = cudaMemcpy(dmat, (float*)Matrix, 4*4*sizeof(float), cudaMemcpyHostToDevice);
	if (error != cudaSuccess) {
		printf("cudaMemcpy %d, line(%d)\n", error, __LINE__);
		exit(EXIT_FAILURE);
	}

//
	pdbTransKernel<<<nAtom/__eosCudaThreadsPerBlock__+1, __eosCudaThreadsPerBlock__>>>(dv, dmat, nAtom);
/*
			matrix3DMultiplyVector(&v, Matrix);

			DEBUGPRINT3("%f %f %f\n", Matrix[3][0], Matrix[3][1], Matrix[3][2]);
			DEBUGPRINT2("x %f -> %f\n", pdb->PDB->Coord.x, v.data[0]);
			DEBUGPRINT2("y %f -> %f\n", pdb->PDB->Coord.y, v.data[1]);
			DEBUGPRINT2("z %f -> %f\n", pdb->PDB->Coord.z, v.data[2]);

*/

// Cuda to Array  
	error = cudaMemcpy(hv, dv, nAtom*4*sizeof(float), cudaMemcpyDeviceToHost);
	if (error != cudaSuccess) {
		printf("cudaMemcpy %d, line(%d)\n", error, __LINE__);
		exit(EXIT_FAILURE);
	}
	cudaFree(dv);
	cudaFree(dmat);


// Array to List
/*
	i=0;
	pdbFileTop(pdb);
	DEBUGPRINT2("%p %p\n", pdb->PDB, pdb->top);
	while(NULL!=pdb->PDB) {
		if(pdbFileIsAtom(pdb)) {
		 	DEBUGPRINT3("%f %f %f\n", hv[i*4+0], hv[i*4+1], hv[i*4+2]);
			pdb->PDB->Coord.x = hv[i*4+0]; 		
			pdb->PDB->Coord.y = hv[i*4+1]; 		
			pdb->PDB->Coord.z = hv[i*4+2]; 		
			i++;
	 	}
	    pdb->PDB = pdb->PDB->next;
	}
	memoryFree(hv);
*/
//

	DEBUGCOMMAND(t2=clock());
	DEBUGPRINT1("%ld\n", t2-t1);
	DEBUGPRINT("pdbTransCuda End\n");
}

