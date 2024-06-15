/*
# lmrcImageAddValueCuda.cu : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : lmrcImageAddValueCuda.cu 
# Attention
#   $Loccker$
#  	$State$ 
#
*/
/* $Log$ */
#include <stdio.h>
#include <cuda.h>
#undef DEBUG
#include "genUtil.h"
#include "eosCuda.h"
#include "./lmrcImageAddValue.h"

__global__ void lmrcImageAddValueKernel(float* im, float v, int max)
{
	int offset = threadIdx.x + blockIdx.x*blockDim.x;
	
	if(offset<max) {
		im[offset] = im[offset] + v;
	}
}

void 
lmrcImageAddValueCuda(float* out, float* in, float value, int nPixel, int imageMode, int mode)
{
	cudaError_t err = cudaSuccess;
	switch(imageMode) {
		case mrcFloatImage: {
			float* im;

			DEBUGPRINT3("%d %p -> %p\n", nPixel, in, out);
			err = cudaMalloc((void **)&im,  sizeof(float)*nPixel);
			if(err !=  cudaSuccess) {
				fprintf(stderr, "Memory Not Allocated\n");
				exit(EXIT_FAILURE);
			} else {
				DEBUGPRINT("Success cudaMalloc\n");
			}
		
			cudaMemcpy(im, in, sizeof(float)*nPixel, cudaMemcpyHostToDevice);
			if(err !=  cudaSuccess) {
				fprintf(stderr, "cudaMemcpy\n");
				exit(EXIT_FAILURE);
			} else {
				DEBUGPRINT("Success cudaMemcpy: HostToDevice\n");
			}

		    lmrcImageAddValueKernel<<<nPixel/__eosCudaThreadsPerBlock__,__eosCudaThreadsPerBlock__>>>(im, value, nPixel); 

			cudaMemcpy(out, im, sizeof(float)*nPixel, cudaMemcpyDeviceToHost);
			if(err !=  cudaSuccess) {
				fprintf(stderr, "cudaMemcpy\n");
				exit(EXIT_FAILURE);
			} else {
				DEBUGPRINT("Success cudaMemcpy: DeviceToHost\n");
			}
			cudaFree(im);

			break;
		}
		default: {
			fprintf(stderr, "Not supported Mode in lmrcImageAddValueCuda:  %d\n", imageMode); 
			exit(EXIT_FAILURE);
			break;
		}
	}	
}

