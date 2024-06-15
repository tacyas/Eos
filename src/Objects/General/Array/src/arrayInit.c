#include <stdio.h>
#include <stdlib.h>
#include "Array.h"
#include "Memory.h"

void
arrayInit(Array* A, char* message)
{
	arrayParaTypeInteger n, i;

	if(A->dim>ARRAY_MAX_DIMENSION) {
		fprintf(stderr, "%s\n", message);
		fprintf(stderr, "Array Dimension(%d) is more than Max(%d) in arrayInit\n",
			(int)A->dim, ARRAY_MAX_DIMENSION);
		exit(EXIT_FAILURE);
	}
	n = 1;
	for(i=0; i<A->dim; i++) {
		n *= A->n[i];
	}
	if(n==0) {
		fprintf(stderr, "%s\n", message);
		fprintf(stderr, "Size is zero in arrayInit.\n");
		exit(EXIT_FAILURE);
	}
	A->A = (arrayParaTypeReal*)memoryAllocate(n*sizeof(arrayParaTypeReal), "in arrayInit");
}

void
arrayFree(Array* A, char* message)
{
	free(A->A);
}
