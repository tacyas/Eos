#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include "nr2.h"

#define NR_END   (1)
#define FREE_ARG char*

void
nrerror(char error_txt[])
{
    fprintf(stderr, "Numerical Recipes Run-Time Error ...\n");
    fprintf(stderr, "%s\n", error_txt);
    fprintf(stderr, "...Now exiting to system...\n");
    exit(EXIT_FAILURE);
}

float* 
vector(long nl, long nh)
{
    float *v;

    v = (float*)malloc((size_t)((nh-nl+1+NR_END)*sizeof(float)));
    if(!v) nrerror("Allocation Filure in vector()");
    return v-nl+NR_END;
}

int* 
ivector(long nl, long nh)
{
    int *v;

    v = (int*)malloc((size_t)((nh-nl+1+NR_END)*sizeof(int)));
    if(!v) nrerror("Allocation Filure in ivector()");
    return v-nl+NR_END;
}

void
free_vector(float* v, long nl, long nh)
{
    free((FREE_ARG) (v+nl-NR_END));
}

void
free_ivector(int* v, long nl, long nh)
{
    free((FREE_ARG) (v+nl-NR_END));
}

float **matrix(long nrl, long nrh, long ncl, long nch)
/* allocate a float matrix with subscript range m[nrl..nrh][ncl..nch] */
{
	long i, nrow=nrh-nrl+1,ncol=nch-ncl+1;
	float **m;

	/* allocate pointers to rows */
	m=(float **) malloc((size_t)((nrow+NR_END)*sizeof(float*)));
	if (!m) nrerror("allocation failure 1 in matrix()");
	m += NR_END;
	m -= nrl;

	/* allocate rows and set pointers to them */
	m[nrl]=(float *) malloc((size_t)((nrow*ncol+NR_END)*sizeof(float)));
	if (!m[nrl]) nrerror("allocation failure 2 in matrix()");
	m[nrl] += NR_END;
	m[nrl] -= ncl;

	for(i=nrl+1;i<=nrh;i++) m[i]=m[i-1]+ncol;

	/* return pointer to array of pointers to rows */
	return m;
}

void free_matrix(float **m, long nrl, long nrh, long ncl, long nch)
/* free a float matrix allocated by matrix() */
{
	free((FREE_ARG) (m[nrl]+ncl-NR_END));
	free((FREE_ARG) (m+nrl-NR_END));
}
