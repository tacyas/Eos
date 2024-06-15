/*
# eosMath.h : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : eosMath.h 
# Attention
#   $Loccker$
#  	$State$ 
#
*/
/* $Log$ */
#ifndef EOS_MATH_H
#define EOS_MATH_H

#include <stdio.h>

/* constant begin */


/* constant end */

/* struct begin */


/* struct end */

#ifdef __cplusplus
extern "C" {
#endif

/* prototype begin */

extern void eosMathSorting(double* v, int n);
extern double eosMathMedian(double* v, int n);
extern double eosMathAverage(double* v, int n);
extern double eosMathStdDev(double* v, int n);
extern double eosMathTrimmedAverage(double* v, int n, double trim);
extern double eosMathHodgesLehmannEstimator(double* v, int n);


/* prototype end */

#ifdef __cplusplus
};
#endif

#endif  /* EOS_MATH_H */ 
