/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% Vector ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : Vector 
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%Vector ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <math.h>

#include "Memory.h"
#include "../inc/Vector.h"

floatVector* 
floatVectorInit(floatVector* v, long size)
{
	floatVector* tmp;
	if(NULL==v) {
		tmp = (floatVector*)memoryAllocate(sizeof(floatVector), "in floatVectorInit");	
	} else {
		tmp = v;
	}
	tmp->size = size;
	tmp->data = (float*)memoryAllocate(sizeof(float)*tmp->size, "in floatVectorInit");
	return tmp;
}

floatVector* 
floatVectorFree(floatVector* v)
{
	memoryFree(v->data);
	v->size = 0;
	return NULL;
}


intVector* 
intVectorInit(intVector* v, long size)
{
	intVector* tmp;
	if(NULL==v) {
		tmp = (intVector*)memoryAllocate(sizeof(intVector), "in intVectorInit");	
	} else {
		tmp = v;
	}
	tmp->size = size;
	tmp->data = (int*)memoryAllocate(sizeof(int)*tmp->size, "in intVectorInit");
	return tmp;
}

intVector* 
intVectorFree(intVector* v)
{
	memoryFree(v->data);
	v->size = 0;
	return NULL;
}




floatVector*
floatVectorAdd(floatVector* v, floatVector* u, floatVector* w)
{
	floatVector* tmp;
	long i;

	if(NULL==u || NULL==w) {
		fprintf(stderr, "floatVector is NULL in floatVectorAdd\n");
		return NULL;
	}
	if(u->size!=w->size) {
		fprintf(stderr, "floatVectors have different size.\n");
		return NULL;
	}
	if(NULL==v) {
		tmp = floatVectorInit(NULL, u->size);
	} else {
		tmp = v;
	}
	if(tmp->size!=u->size) {
		fprintf(stderr, "floatVectors have different size.\n");
		return NULL;
	}
	for(i=0; i<tmp->size; i++) {
		tmp->data[i] = u->data[i] + w->data[i];
	}
	return tmp;
}

floatVector*
floatVectorMinus(floatVector* v, floatVector* u, floatVector* w)
{
/* v = u - w */
	floatVector* tmp;
	long i;

	if(NULL==u || NULL==w) {
		fprintf(stderr, "floatVector is NULL in floatVectorAdd\n");
		return NULL;
	}
	if(u->size!=w->size) {
		fprintf(stderr, "floatVectors have different size.\n");
		return NULL;
	}
	if(NULL==v) {
		tmp = floatVectorInit(NULL, u->size);
	} else {
		tmp = v;
	}
	if(tmp->size!=u->size) {
		fprintf(stderr, "floatVectors have different size.\n");
		return NULL;
	}
	for(i=0; i<tmp->size; i++) {
		tmp->data[i] = u->data[i] - w->data[i];
	}
	return tmp;
}
double
lfloatVectorLength(floatVector* x)
{
	long i;
	double value;

	value=0;
	if(NULL==x) {
		fprintf(stderr, "floatVector is NULL in floatVectorLength\n");
		return 0;
	}
	for(i=0;i<x->size;i++){
		value += x->data[i]*x->data[i];
	}
	value=sqrt(value);
	return value;
}


doubleVector* 
doubleVectorInit(doubleVector* v, long size)
{
	doubleVector* tmp;
	if(NULL==v) {
		tmp = (doubleVector*)memoryAllocate(sizeof(doubleVector), "in doubleVectorInit");	
	} else {
		tmp = v;
	}
	tmp->size = size;
	tmp->data = (double*)memoryAllocate(sizeof(double)*tmp->size, "in doubleVectorInit");
	return tmp;
}

doubleVector* 
doubleVectorFree(doubleVector* v)
{
	memoryFree(v->data);
	v->size = 0;
	return NULL;
}

doubleVector*
doubleVectorAdd(doubleVector* v, doubleVector* u, doubleVector* w)
{
	doubleVector* tmp;
	long i;

	if(NULL==u || NULL==w) {
		fprintf(stderr, "doubleVector is NULL in doubleVectorAdd\n");
		return NULL;
	}
	if(u->size!=w->size) {
		fprintf(stderr, "doubleVectors have different size.\n");
		return NULL;
	}
	if(NULL==v) {
		tmp = doubleVectorInit(NULL, u->size);
	} else {
		tmp = v;
	}
	if(tmp->size!=u->size) {
		fprintf(stderr, "doubleVectors have different size.\n");
		return NULL;
	}
	for(i=0; i<tmp->size; i++) {
		tmp->data[i] = u->data[i] + w->data[i];
	}
	return tmp;
}

doubleVector*
doubleVectorMinus(doubleVector* v, doubleVector* u, doubleVector* w)
{
/* v = u - w */
	doubleVector* tmp;
	long i;

	if(NULL==u || NULL==w) {
		fprintf(stderr, "doubleVector is NULL in doubleVectorAdd\n");
		return NULL;
	}
	if(u->size!=w->size) {
		fprintf(stderr, "doubleVectors have different size.\n");
		return NULL;
	}
	if(NULL==v) {
		tmp = doubleVectorInit(NULL, u->size);
	} else {
		tmp = v;
	}
	if(tmp->size!=u->size) {
		fprintf(stderr, "doubleVectors have different size.\n");
		return NULL;
	}
	for(i=0; i<tmp->size; i++) {
		tmp->data[i] = u->data[i] - w->data[i];
	}
	return tmp;
}
double
ldoubleVectorLength(doubleVector* x)
{
	long i;
	double value;

	value=0;
	if(NULL==x) {
		fprintf(stderr, "doubleVector is NULL in doubleVectorLength\n");
		return 0;
	}
	for(i=0;i<x->size;i++){
		value += x->data[i]*x->data[i];
	}
	value=sqrt(value);
	return value;
}

