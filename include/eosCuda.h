/*
# eosCuda.h : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : eosCuda.h 
# Attention
#   $Loccker$
#  	$State$ 
#
*/
/* $Log$ */
#ifndef EOS_CUDA_H 
#define EOS_CUDA_H 

#include <stdio.h>

/* constant begin */
extern int __eosCuda__;
extern int __eosCudaDeviceID__;
extern int __eosCudaBlockSize__;
extern int __eosCudaThreadsPerBlock__;

/* constant end */

/* struct begin */


/* struct end */

#ifdef __cplusplus
extern "C" {
#endif

/* prototype begin */
extern void eosCudaInit(int deviceID);
extern void eosCudaPropertiesPrint(FILE* fpt, int id);


/* prototype end */

#ifdef __cplusplus
};
#endif

#endif  /* XXXX */ 
