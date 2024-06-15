/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% mrcImageGetPixelsCUDA.cu ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : mrcImageGetPixelsCUDA.cu 
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%mrcImageGetPixelsCUDA.cu ver%I%; Date:%D% %Z%";

#include <stdio.h>
#include <cuda.h>
#define DEBUG
#include "genUtil.h"
#include "eosCuda.h"
#include "../inc/mrcImage.h"
#include "./mrcImageGetPixelsCUDA.h"


__device__ float mrcPixelDataGetDevice(float x, float y, float z, float* inD, int nx, int ny, int nz, mrcPixelDataHowToGet howToMode)
{
	float data;

	switch(howToMode) {
		case mrcPixelHowNearest: {
			int   ix, iy, iz;
			int   n;
			ix = (int)(x+0.5);
			iy = (int)(y+0.5);
			iz = (int)(z+0.5);

			n = ix + iy*nx + iz*nx*ny;
			data = inD[n];
			break;
		}
		case mrcPixelHowLinear: {
			int   ix0, iy0, iz0;
			int   ix1, iy1, iz1;

			if(1<ny && 1<nz) { // 3D  
				int n000, n001, n010, n011;	
				int n100, n101, n110, n111;	
				float data000, data010, data100, data110;
				float data001, data011, data101, data111;

				ix0 = (int)x;
				iy0 = (int)y;
				iz0 = (int)z;
				ix1 = ix0+1;
				iy1 = iy0+1;
				iz1 = iz0+1;

				n000 = ix0 + iy0*nx + iz0*nx*ny; 
				n010 = ix0 + iy1*nx + iz0*nx*ny;
				n100 = ix1 + iy0*nx + iz0*nx*ny;
				n110 = ix1 + iy1*nx + iz0*nx*ny;
				n001 = ix0 + iy0*nx + iz1*nx*ny; 
				n011 = ix0 + iy1*nx + iz1*nx*ny;
				n101 = ix1 + iy0*nx + iz1*nx*ny;
				n111 = ix1 + iy1*nx + iz1*nx*ny;

				data000 = inD[n000];
				data010 = inD[n010];
				data100 = inD[n100];
				data110 = inD[n110];
				data001 = inD[n001];
				data011 = inD[n011];
				data101 = inD[n101];
				data111 = inD[n111];

				data = (ix1 - x  )*(iy1 - y  )*(iz1 - z  )*data000 
					 + (ix1 - x  )*(y   - iy0)*(iz1 - z  )*data010
					 + (x   - ix0)*(iy1 - y  )*(iz1 - z  )*data100
				  	 + (x   - ix0)*(y   - iy0)*(iz1 - z  )*data110
					 + (ix1 - x  )*(iy1 - y  )*(z   - iz0)*data001 
					 + (ix1 - x  )*(y   - iy0)*(z   - iz0)*data011
					 + (x   - ix0)*(iy1 - y  )*(z   - iz0)*data101
				  	 + (x   - ix0)*(y   - iy0)*(z   - iz0)*data111;

			} else if(1<ny) { // 2D 
				int n00, n01, n10, n11;	
				float data00, data01, data10, data11;

				ix0 = (int)x;
				iy0 = (int)y;
				ix1 = ix0+1;
				iy1 = iy0+1;

				n00 = ix0 + iy0*nx;
				n01 = ix0 + iy1*nx;
				n10 = ix1 + iy0*nx;
				n11 = ix1 + iy1*nx;

				data00 = inD[n00];
				data01 = inD[n01];
				data10 = inD[n10];
				data11 = inD[n11];

				data = (ix1 - x  )*(iy1 - y  )*data00 
					 + (ix1 - x  )*(y   - iy0)*data01
					 + (x   - ix0)*(iy1 - y  )*data10
					 + (x   - ix0)*(y   - iy0)*data11;
			} else { // 1D
				int n0, n1;	
				float data0, data1;

				ix0 = (int)x;
				ix1 = ix0+1;

				n0 = ix0;
				n1 = ix1;
				data0 = inD[n0];
				data1 = inD[n1];

				data = (ix1 - x  )*data0 
				  	 + (x   - ix0)*data1; 
			}
			break;
		}
		case mrcPixelHowCubicConv: {
			break;
		}
		case mrcPixelHowPolySig: {
			break;
		}
		default: {
			break;
		}
	}
		
	return data;
}

__global__ void mrcPixelsDataGetKernel(float* outD, float* inCoordD, int num, float* inD, int nx, int ny, int nz, mrcPixelDataHowToGet howToMode)
{
	int offset = threadIdx.x + blockIdx.x*blockDim.x; 

	if(offset<num) {
		float x, y, z;

		x = inCoordD[3*offset+0];	
		y = inCoordD[3*offset+1];	
		z = inCoordD[3*offset+2];	

		outD[offset] = mrcPixelDataGetDevice(x, y, z, inD, nx, ny, nz, howToMode);
	}
}

__global__ void mrcPixelDataGetbyMatrix3DKernel(float* outD, float* matD, float* inD, int nx, int ny, int nz, mrcPixelDataHowToGet howToMode)
{
	int offset = threadIdx.x + blockIdx.x*blockDim.x; 
	int num = nx*ny*nz;

	if(offset<num) {
		float dstx, dsty, dstz;
		float srcx, srcy, srcz;
		float x, y, z;

		// offset = dstx + dsty*nx + dstz*nx*ny; // 3D
		// offset = dstx + dsty*nx;              // 2D
		// offset = dstx ;                       // 1D
		if(1<ny && 1<nz) { // 3D
			dstz = offset/(nx*ny);
			dsty = (offset - dstz*nx*ny)/nx;	
			dstx = (offset - dstz*nx*ny - dsty*nx);	
		} else if(1<ny) { // 2D
			dstz = 0;
			dsty = offset/nx;
			dstx = offset%nx;
		} else {          // 1D
			dstz = 0;
			dsty = 0;
			dstx = offset;
		}
		x = dstx - matD[3*4 + 0]; 
		y = dsty - matD[3*4 + 1];
		z = dstz - matD[3*4 + 2]; 
		srcx = matD[0*4+0]*x + matD[0*4+1]*y + matD[0*4+2]*z;
		srcy = matD[1*4+0]*x + matD[1*4+1]*y + matD[1*4+2]*z;
		srcz = matD[2*4+0]*x + matD[2*4+1]*y + matD[2*4+2]*z;
		outD[offset] = mrcPixelDataGetDevice(srcx, srcy, srcz, inD, nx, ny, nz, howToMode);
	}
}


void
mrcPixelsDataGetCUDA(float* out, float* inCoord, int num, float* in, mrcImageMode imageMode,  int nx, int ny, int nz, mrcPixelDataType type,  mrcPixelDataHowToGet howToMode)
{
	cudaError_t err = cudaSuccess;
	int nPixel = nx*ny*nz;
	
	DEBUGPRINT("mrcPixelsDataGetCUDA start ----> \n");	

	switch(imageMode) {
		case mrcFloatImage: {
			float* inD;
			float* outD;
			float* inCoordD;

			// inD
			DEBUGPRINT3("%d %p -> %p\n", nPixel, in, out);
			err = cudaMalloc((void **)&inD,  sizeof(float)*nPixel);
			if(err !=  cudaSuccess) {
				fprintf(stderr, "Memory Not Allocated\n");
				exit(EXIT_FAILURE);
			} else {
				DEBUGPRINT("Success cudaMalloc\n");
			}
			// outD
			err = cudaMalloc((void **)&outD,  sizeof(float)*num);
			if(err !=  cudaSuccess) {
				fprintf(stderr, "Memory Not Allocated\n");
				exit(EXIT_FAILURE);
			} else {
				DEBUGPRINT("Success cudaMalloc\n");
			}
			// inCoordD
			err = cudaMalloc((void **)&inCoordD,  sizeof(float)*num*3);
			if(err !=  cudaSuccess) {
				fprintf(stderr, "Memory Not Allocated\n");
				exit(EXIT_FAILURE);
			} else {
				DEBUGPRINT("Success cudaMalloc\n");
			}
			
			// in -> inD
			cudaMemcpy(inD, in, sizeof(float)*nPixel, cudaMemcpyHostToDevice);
			// inCoord -> inD
			cudaMemcpy(inCoordD, inCoord, sizeof(float)*3*num, cudaMemcpyHostToDevice);

			if(err !=  cudaSuccess) {
				fprintf(stderr, "cudaMemcpy\n");
				exit(EXIT_FAILURE);
			} else {
				DEBUGPRINT("Success cudaMemcpy: HostToDevice\n");
			}
			mrcPixelsDataGetKernel<<<num/__eosCudaThreadsPerBlock__,__eosCudaThreadsPerBlock__>>>(outD, inCoordD, num, inD, nx, ny, nz, howToMode);
			
			cudaMemcpy(out, outD, sizeof(float)*num, cudaMemcpyDeviceToHost);
			if(err !=  cudaSuccess) {
				fprintf(stderr, "cudaMemcpy\n");
				exit(EXIT_FAILURE);
			} else {
				DEBUGPRINT("Success cudaMemcpy: DeviceToHost\n");
			}
			cudaFree(inD);
			cudaFree(inCoordD);
			cudaFree(outD);
			break;
		}
		default: {
			fprintf(stderr, "Not supported mode in mrcPixelDataGetCUDA: %d\n", imageMode);
			exit(EXIT_FAILURE);
			break;
		}
	}
}


void
mrcPixelDataGetbyMatrix3DCUDA(float* out, float* mat, float* in, mrcImageMode imageMode, int nx, int ny, int nz, mrcPixelDataType type, mrcPixelDataHowToGet howToMode)
{
	cudaError_t err = cudaSuccess;
	int nPixel = nx*ny*nz;

	switch(imageMode) {
		case mrcFloatImage: {
			float* inD;
			float* outD;
			float* matD;

			// inD
			DEBUGPRINT3("%d %p -> %p\n", nPixel, in, out);
			err = cudaMalloc((void **)&inD,  sizeof(float)*nPixel);
			if(err !=  cudaSuccess) {
				fprintf(stderr, "Memory Not Allocated\n");
				exit(EXIT_FAILURE);
			} else {
				DEBUGPRINT("Success cudaMalloc\n");
			}
			// outD
			err = cudaMalloc((void **)&outD,  sizeof(float)*nPixel);
			if(err !=  cudaSuccess) {
				fprintf(stderr, "Memory Not Allocated\n");
				exit(EXIT_FAILURE);
			} else {
				DEBUGPRINT("Success cudaMalloc\n");
			}
			// matD 
			err = cudaMalloc((void **)&matD,  sizeof(float)*4*4);
			if(err !=  cudaSuccess) {
				fprintf(stderr, "Memory Not Allocated\n");
				exit(EXIT_FAILURE);
			} else {
				DEBUGPRINT("Success cudaMalloc\n");
			}
			
			// in -> inD
			cudaMemcpy(inD, in, sizeof(float)*nPixel, cudaMemcpyHostToDevice);
			// inCoord -> inD
			cudaMemcpy(matD, mat, sizeof(float)*4*4, cudaMemcpyHostToDevice);

			if(err !=  cudaSuccess) {
				fprintf(stderr, "cudaMemcpy\n");
				exit(EXIT_FAILURE);
			} else {
				DEBUGPRINT("Success cudaMemcpy: HostToDevice\n");
			}
			mrcPixelDataGetbyMatrix3DKernel<<<nPixel/__eosCudaThreadsPerBlock__,__eosCudaThreadsPerBlock__>>>(outD, matD, inD, nx, ny, nz, howToMode);
			
			cudaMemcpy(out, outD, sizeof(float)*nPixel, cudaMemcpyDeviceToHost);
			if(err !=  cudaSuccess) {
				fprintf(stderr, "cudaMemcpy\n");
				exit(EXIT_FAILURE);
			} else {
				DEBUGPRINT("Success cudaMemcpy: DeviceToHost\n");
			}
			cudaFree(inD);
			cudaFree(matD);
			cudaFree(outD);
			break;
		}
		default: {
			fprintf(stderr, "Not supported mode in mrcPixelDataGetCUDA: %d\n", imageMode);
			exit(EXIT_FAILURE);
			break;
		}
	}

}

