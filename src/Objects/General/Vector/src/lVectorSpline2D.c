/*
# lVectorSpline2D.c  1.1
# The latest update : 07/12/96 at 22:42:31
#
#@(#) lVectorSpline2D ver 1.1
#@(#) Created by 
#@(#)
#@(#) Usage : lVectorSpline2D 
#@(#) Attention
#@(#)
*/
static char __sccs_id[] = "@(#)lVectorSpline2D ver1.1; Date:96/07/12 @(#)";
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "Memory.h"
#include "../inc/Vector.h"

void
lVectorSplineTableMake(floatVector* x, floatVector* y, floatVector* z)
{
	int i, n;
	double t;
	double* h;
	double* d;
	
	if( x->size!=y->size
	  ||x->size!=z->size) {
		fprintf(stderr, "The size is wrong !: x: %ld y: %ld z: %ld\n",
			x->size,
			y->size,
			z->size);
		return;
	} else {
		n = x->size;
		h = (double*)memoryAllocate(sizeof(double)*n, "in lVectorSplineTableMake");
		d = (double*)memoryAllocate(sizeof(double)*n, "in lVectorSplineTableMake");
	}
	z->data[0] = 0;
	z->data[n-1] = 0;
	for(i=0; i<n-1; i++) {
		h[i  ] =  x->data[i+1] - x->data[i];
		d[i+1] = (y->data[i+1] - y->data[i])/h[i];
	}
	z->data[1] = d[2] - d[1] - h[0]*z->data[0];
	d[1]       = 2*(x->data[2] - x->data[0]);
	for(i=1; i<n-2; i++) {
		t = h[i]/d[i];
		z->data[i+1] = d[i+2] - d[i+1] - z->data[i]*t;
		d[i+1] = 2*(x->data[i+2] - x->data[i]) - h[i]*t;
	}
	z->data[n-2] -= h[n-2]*z->data[n-1];
	for(i=n-2; i>0; i--) {
		z->data[i] = (z->data[i] - h[i]*z->data[i+1])/d[i];
	}
	free(h);
	free(d);
}

double
lVectorSpline(double t, floatVector* x, floatVector* y, floatVector* z)
{
	int i, j, k, n;
	double d, h, data;
	
	n = x->size;
	i = 0; j = n - 1;
	while(i < j) { /* Which interval 't' is in ? */
		k = (i + j)/2;
		if(x->data[k] < t) {
			i = k + 1;
		} else {
			j = k;
		}
	}
	if(0 < i) {
		i--;
	}

	h = x->data[i+1] - x->data[i];
	d = t - x->data[i];

	data = (((z->data[i+1]   - z->data[i  ])*d/h
			+ z->data[i]*3)*d
		   +((y->data[i+1]   - y->data[i  ])/h
			-(z->data[i  ]*2 + z->data[i+1])*h))*d
		   +y->data[i];

	return data;
}

void
lVectorSplineTable2DMake(floatVector* p, floatVector* x, floatVector* y, floatVector* a, floatVector* b)
{
	int i;
	int n;

	double t1, t2;
	if( p->size!=x->size
	  ||p->size!=y->size
	  ||p->size!=a->size
	  ||p->size!=b->size) {
		fprintf(stderr, "The size is wrong !: p: %ld x: %ld y: %ld a: %ld b:%ld \n", 
			p->size,
			x->size,
			y->size,
			a->size,
			b->size);
		return; 
	} else {
		n = p->size;
	}

	p->data[0] = 0;
	for(i=1; i<n; i++) {
		t1 = x->data[i] - x->data[i-1];
		t2 = y->data[i] - y->data[i-1];
		p->data[i] = p->data[i-1] + sqrt(t1*t1 + t2*t2);
	}
	lVectorSplineTableMake(p, x, a);
	lVectorSplineTableMake(p, y, b);
}

void
lVectorSpline2D(double t, double* px, double* py, 
	floatVector* p, floatVector* x, floatVector* y,
	floatVector* a, floatVector* b)
{
	*px = lVectorSpline(t, p, x, a);
	*py = lVectorSpline(t, p, y, b);
}

