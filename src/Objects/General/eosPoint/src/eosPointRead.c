/*
# eosPointRead : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : eosPointRead 
# Attention
#   $Loccker$
#  	$State$ 
#
*/
/* $Log$ */

#undef DEBUG
#include "genUtil.h"
#include "eosString.h"
#include "../inc/eosPoint.h"

void
eosPointFileFormatUsage(FILE* fpt)
{
	fprintf(fpt, "type-0: x y z\n");
	fprintf(fpt, "type-1: x y z sig\n");
	fprintf(fpt, "type-2: x y z sigx sigy sigz\n");
	fprintf(fpt, "type-3: x y z sig sigx sigy sigz\n");
}

void
eosPointRead(FILE* fpt, eosPoint* p, int mode)
{
	char s[STRING_MAX_LENGTH];
	eosPointCoord pc;
	eosPointParaTypeReal x, y, z, sig, sigx, sigy, sigz;
	int index;

	eosPointInit(p, NULL);
	eosPointCoordInit(&pc, 0); 
	while(NULL!=stringGetFromFileWithSkippingComment(s, "in eosPointRead", fpt, stderr, 3)) {
		index = 1;
		x = stringGetNthRealData(s, 1, " ,\t"); index++;
		y = stringGetNthRealData(s, 2, " ,\t"); index++;
		z = stringGetNthRealData(s, 3, " ,\t"); index++;
		eosPointCoordSet(&pc, x, y, z);
		if(mode&0x01) {
			sig = stringGetNthRealData(s, index, " ,\t"); index++;
			pc.sigma = sig;
		}
		if(mode&0x02) {
			sigx = stringGetNthRealData(s, index, " ,\t"); index++;
			sigy = stringGetNthRealData(s, 6, " ,\t"); index++;
			sigz = stringGetNthRealData(s, 7, " ,\t"); index++;
			eosPointCoordSigSet(&pc, sigx, sigy, sigz);
		}
		eosPointAppend(p, &pc, 0);
		DEBUGPRINT7("%f %f %f %f %f %f %f\n", x, y, z, sig, sigx, sigy, sigz);
		DEBUGPRINT7("%f %f %f %f %f %f %f\n", p->current->p.coord.data[0], 
												p->current->p.coord.data[1],	
												p->current->p.coord.data[2],	
												p->current->p.sigma,	
												p->current->p.sig.data[0],	
												p->current->p.sig.data[1],	
												p->current->p.sig.data[2]);
	}
}
