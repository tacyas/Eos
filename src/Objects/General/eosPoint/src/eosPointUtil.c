/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% eosPointUtil ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : eosPointUtil 
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%eosPointUtil ver%I%; Date:%D% %Z%";

#include "genUtil.h"
#include "Memory.h"
#include "../inc/eosPoint.h"

eosPointList*
eosPointTop(eosPoint* p)
{
	p->current = p->top; 
	return p->current;
}

eosPointList*
eosPointBottom(eosPoint* p)
{
	p->current = p->bottom; 
	return p->current;
}

eosPointList*
eosPointNext(eosPoint* p)
{
	if(NULL!=p->current) {
		p->current = p->current->next; 
	}
	return p->current;
}

eosPointList*
eosPointPrev(eosPoint* p)
{
	if(NULL!=p->current) {
		p->current = p->current->prev; 
	}
	return p->current;
}

void
eosPointCoordInit(eosPointCoord* pc, int mode)
{
	floatVectorInit(&(pc->coord), 4); 
	floatVectorInit(&(pc->sig), 4); 
}

void
eosPointCoordSet(eosPointCoord* pc, eosPointParaTypeReal x, eosPointParaTypeReal y, eosPointParaTypeReal z)
{
	pc->coord.data[0] = x;
	pc->coord.data[1] = y;
	pc->coord.data[2] = z;
	pc->coord.data[3] = 1;
}

void
eosPointCoordSigSet(eosPointCoord* pc, eosPointParaTypeReal x, eosPointParaTypeReal y, eosPointParaTypeReal z)
{
    pc->sigma = sqrt(SQR(x) + SQR(y) + SQR(z));
	pc->sig.data[0] = x;
	pc->sig.data[1] = y;
	pc->sig.data[2] = z;
	pc->sig.data[3] = 1;
}

void
eosPointInit(eosPoint* p, eosPointCoord* pc) 
{
	p->current = NULL;
	p->top     = NULL;
	p->bottom  = NULL;
	if(NULL!=pc) {	
		eosPointAppend(p, pc, 0);
	}	
}

eosPointList*
eosPointAppend(eosPoint* p, eosPointCoord* pc, int mode)
{
	eosPointList* tmp;

	tmp = (eosPointList*)memoryAllocate(sizeof(eosPointList), "in eosPointAppend");
	if(NULL==p->top) {
		p->top = tmp;
		p->top->prev = NULL;
		p->top->next = NULL;
		p->current = p->top;
		p->bottom  = p->top;
	} else {
		switch(mode) {
			case +1:
			case  0: { // current --> tmp --> current->next
				tmp->prev = p->current;
				tmp->next = p->current->next;
				if(NULL==tmp->next) { // If Bottom,
					p->bottom = tmp;
				}
				break;
			}
			case -1: { // current->prev --> tmp --> current 
				tmp->prev = p->current->prev; 
				tmp->next = p->current; 
				if(NULL==tmp->prev) { // If top,
					p->top = tmp;
				}
				break;
			}
			case +2: { // bottom --> tmp
				tmp->prev = p->bottom;
				tmp->next = NULL;
				p->bottom = tmp;
				break;
			}
			case -2: { // tmp --> top
				tmp->prev = NULL;
				tmp->next = p->top;
				p->top = tmp;
				break;	
			}
			dafault: {
				fprintf(stderr, "Not supported Mode: %d\n", mode);
				fprintf(stderr, " Append new after current\n");
				tmp->prev = p->current;
				tmp->next = p->current->next;
				break;
			}
		}
		// Current Connection Change
		if(NULL!=tmp->next) { // next->prev = tmp   
			tmp->next->prev = tmp;			
		}
		if(NULL!=tmp->prev) { // prev->next = tmp
			tmp->prev->next = tmp;			
		}
		p->current = tmp;
	}
	eosPointCoordInit(&(tmp->p), 0);
	eosPointCoordSet(&(tmp->p), pc->coord.data[0], pc->coord.data[1], pc->coord.data[2]);
	tmp->p.sigma = pc->sigma;
	eosPointCoordSigSet(&(tmp->p), pc->sig.data[0],   pc->sig.data[1],   pc->sig.data[2]);

	return p->current;
}

