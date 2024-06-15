#include <stdio.h>
#include <stdlib.h>
#include "Array.h"
#include "Memory.h"
#include "File.h"
#include "eosString.h"

void
arrayWriteToFile(FILE* fpt, Array* A, char* message)
{
	arrayParaTypeInteger n, i, j;

	fprintf(fpt, "%lu ", A->dim);
	for(i=0; i<A->dim; i++) {
		fprintf(fpt, "%lu ", A->n[i]);
	}
	fprintf(fpt, "\n");
	n = 1;
	for(i=1; i<A->dim; i++) { /* Calculation Line Number */
		n *= A->n[i];
	}
	for(i=0; i<n; i++) {
		for(j=0; j<A->n[0]; j++) {
			fprintf(fpt, "%15.6f ", A->A[j + i*A->n[0]]);
		}
		fprintf(fpt, "\n");
	}
}
