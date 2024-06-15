/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% eosCuda ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : eosCuda 
#%Z% Attention
#%Z%
*/

#ifdef CUDA

static char __sccs_id[] = "%Z%eosCuda ver%I%; Date:%D% %Z%";
#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>
#include <cuda_runtime.h>
#include "../inc/eosCuda.h"

#ifdef __cplusplus
} ;

#endif
int __eosCuda__=0;
int __eosCudaDeviceID__=0;
int __eosCudaBlockSize__=32;
int __eosCudaThreadsPerBlock__=1024;
static cudaDeviceProp __eosCudaDeviceProp__;

void
eosCudaInit(int id)
{
	cudaError_t error;

	__eosCuda__=1;
	__eosCudaDeviceID__ = id;

	// By default, we use device 0, otherwise we override the device ID based on what is provided at the command line
	cudaSetDevice(__eosCudaDeviceID__);
	error = cudaGetDevice(&__eosCudaDeviceID__);
	if (error != cudaSuccess) {
		fprintf(stderr, "cudaGetDevice returned error code %d, line(%d)\n", error, __LINE__);
		exit(EXIT_FAILURE);
	}

	error = cudaGetDeviceProperties(&__eosCudaDeviceProp__, __eosCudaDeviceID__);
	if (__eosCudaDeviceProp__.computeMode == cudaComputeModeProhibited) {
		fprintf(stderr, "Error: device is running in <Compute Mode Prohibited>, no threads can use ::cudaSetDevice().\n");
		exit(EXIT_SUCCESS);
	}
	if (error != cudaSuccess) {
		printf("cudaGetDeviceProperties returned error code %d, line(%d)\n", error, __LINE__);
	} 
    __eosCudaBlockSize__ = (__eosCudaDeviceProp__.major < 2) ? 16 : 32;
    __eosCudaThreadsPerBlock__ = __eosCudaDeviceProp__.maxThreadsPerBlock;
}


void
eosCudaPropertiesPrint(FILE* fpt, int id)
{
	cudaError_t error;

	__eosCuda__=1;
	__eosCudaDeviceID__ = id;

	// By default, we use device 0, otherwise we override the device ID based on what is provided at the command line
	cudaSetDevice(__eosCudaDeviceID__);
	error = cudaGetDevice(&__eosCudaDeviceID__);
	if (error != cudaSuccess) {
		fprintf(stderr, "cudaGetDevice returned error code %d, line(%d)\n", error, __LINE__);
		exit(EXIT_FAILURE);
	}

	error = cudaGetDeviceProperties(&__eosCudaDeviceProp__, __eosCudaDeviceID__);
	if (__eosCudaDeviceProp__.computeMode == cudaComputeModeProhibited) {
		fprintf(stderr, "Error: device is running in <Compute Mode Prohibited>, no threads can use ::cudaSetDevice().\n");
		exit(EXIT_SUCCESS);
	}
	if (error != cudaSuccess) {
		printf("cudaGetDeviceProperties returned error code %d, line(%d)\n", error, __LINE__);
		return;
	} 
    __eosCudaBlockSize__ = (__eosCudaDeviceProp__.major < 2) ? 16 : 32;

	fprintf(fpt, "GPU Device %d: \"%s\" with compute capability %d.%d\n\n", __eosCudaDeviceID__, __eosCudaDeviceProp__.name, __eosCudaDeviceProp__.major, __eosCudaDeviceProp__.minor);

	fprintf(fpt, "totalGlobalMem:     %d\n", __eosCudaDeviceProp__.totalGlobalMem);
	fprintf(fpt, "sharedMemPerBlock:  %d\n", __eosCudaDeviceProp__.sharedMemPerBlock);
	fprintf(fpt, "maxThreadsPerBlock: %d\n", __eosCudaDeviceProp__.maxThreadsPerBlock);
}

#endif
