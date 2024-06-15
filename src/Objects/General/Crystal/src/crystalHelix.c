/*
# crystalHelix : $Revision: 1.1 $  
# $Date: 2002/02/14 10:18:46 $ 
# Created by $Author: tacyas $
# Usage : crystalHelix 
# Attention
#   $Loccker$
#  	$State: Exp $ 
#
*/
/* $Log: crystalHelix.c,v $
/* Revision 1.1  2002/02/14 10:18:46  tacyas
/* First
/* */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../inc/Crystal.h"

void __crystalHelixInfoIndirectVariablesSet(CrystalInfo* linfo, int mode);

void
crystalHelixInfoSet(CrystalInfo* linfo, 
					CrystalParaTypeInteger t, 
					CrystalParaTypeInteger u, 
					CrystalParaTypeInteger n, 
					CrystalParaTypeReal    truePitch, int mode)
{
	linfo->SpaceGroup = CrystalSpaceGroupHelical;

	linfo->HelixInfo.t = t;
	linfo->HelixInfo.u = u;
	linfo->HelixInfo.n = n;

	/* c-axis : filament-axis */
	linfo->CellLength.c = truePitch;

	/* b-axis:  azimuthal-axis */ 
	linfo->CellLength.b = 2*M_PI/n;
	linfo->N.b          = n;

	/* a-axis: radius-axis */

	__crystalHelixInfoIndirectVariablesSet(linfo, mode);
}


void
__crystalHelixInfoIndirectVariablesSet(CrystalInfo* linfo, int mode)
{
	/* Indirect */
	linfo->HelixInfo.dz     = linfo->CellLength.c/linfo->HelixInfo.u;
	linfo->HelixInfo.dphi   = 2*M_PI*linfo->HelixInfo.t/linfo->HelixInfo.u;
}


