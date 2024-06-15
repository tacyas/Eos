#include <stdio.h>
#include <stdlib.h>
#include "../inc/Array.h"
#include "Memory.h"
#include "File.h"
#include "eosString.h"

void
arrayReadFromFile(FILE* fpt, Array* A, char* message)
{
	char s[STRING_MAX_LENGTH*16];
	arrayParaTypeInteger n, i, j;
    int NN, KK, k;

		
	stringGetFromFile(s, "", fpt, stdout, 1);
	A->dim = stringGetNthIntegerData(s, 1, ARRAY_SEPARATOR);
	if(A->dim>ARRAY_MAX_DIMENSION || A->dim<1) {
		fprintf(stderr, "%s\n", message);
		fprintf(stderr, "Array Dimension(%d) is more than Max(%d) or less than %d in arrayInit\n",
			(int)A->dim, ARRAY_MAX_DIMENSION, ARRAY_MIN_DIMENSION);
		exit(EXIT_FAILURE);
	} 
	for(i=0; i<A->dim; i++) {
		A->n[i] = stringGetNthIntegerData(s, i+2, ARRAY_SEPARATOR); 
	}

    NN = stringGetNthIntegerData(s, A->dim+2, ARRAY_SEPARATOR);
    if(NN<=0) NN=A->n[0];

	arrayInit(A, "in arrayReadFile");

	n = 1;
	for(i=1; i<A->dim; i++) { /* Calculation Line Number */
		n *= A->n[i];
	}
	for(i=0; i<n; i++) {
        KK = A->n[0]/NN;
        if(KK*NN<A->n[0]) KK++;


        for(k=0; k<KK; k++) { 
		fgets(s, STRING_MAX_LENGTH*16, fpt);
		for(j=0; j<NN; j++) {
			A->A[j+k*NN + i*A->n[0]] =stringGetNthRealData(s, j+1, ARRAY_SEPARATOR);
		}
        }
	}
}
