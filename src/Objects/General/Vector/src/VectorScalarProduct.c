/*
# VectorScalarProduct.c  1.1
# The latest update : 07/16/96 at 12:14:14
#
#@(#) VectorScalarProduct ver 1.1
#@(#) Created by 
#@(#)
#@(#) Usage : VectorScalarProduct 
#@(#) Attention
#@(#)
*/
static char __sccs_id[] = "@(#)VectorScalarProduct ver1.1; Date:96/07/16 @(#)";
#include <stdio.h>
#include <stdlib.h>
#include "../inc/Vector.h"

double
floatVectorScalarProduct(floatVector* v, floatVector* w)
{
	long i;
	double sc;

	if(v->size!=w->size) {
		fprintf(stderr, "Two vectors have ifferent size in floatVectorScalarProduct : %ld != %ld\n", v->size, w->size) ;
		exit(EXIT_FAILURE);
	}
	sc = 0.0;
	for(i=0; i<v->size; i++) {
		sc += (v->data[i]*w->data[i]);
	}
	return sc;
}
