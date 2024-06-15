/*
# ctfInfoWrite2 : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : ctfInfoWrite2 
# Attention
#   $Loccker$
#  	$State$ 
#
*/
/* $Log$ */

static char __sccs_id[] = "%Z%ctfInfoWrite ver%I%; Date:%D% %Z%";
#include "genUtil.h"
#include "eosString.h"
#include <math.h>
#include "../inc/ctfInfo.h"
#include "./ctfInfoWrite2.h"
#include <stdio.h>
#include <stdlib.h>

void
ctfInfoWrite2(FILE* fpt, lctfDetermineInfo linfo, char* head)
{
	long i;
	
	fprintf(fpt, "%sInoise:        %15.6g\n", head, exp(M_LN10/2*linfo.noise[0]));
	fprintf(fpt, "%sMTF:           %15.6g\n", head, M_LN10/-2*linfo.noise[1]);
	for(i=2 ; i<=linfo.degree ; i++){
		 fprintf(fpt, "%sMTFd%d:         %15.6g\n", head, i , M_LN10/2*linfo.noise[i]);
	}
	for(i=linfo.degree +1 ; i<=6 ;i++){
		fprintf(fpt, "%sMTFd%d:         %15.0f\n", head, i , 0);
	}
	fprintf(fpt, "%sImin:          %15.6g\n", head, linfo.IntensityMin);
	fprintf(fpt, "%sImax:          %15.6g\n", head, linfo.IntensityMax);
	fprintf(fpt, "%swhichMTF:           Polynomial\n", head);
	fprintf(fpt, "%sIsignal:                    12\n", head);
	fprintf(fpt, "%sflagLogScale:                1\n", head);
	fprintf(fpt, "%sddefocus:                  -100\n", head);
	fprintf(fpt, "%sdInoise:                   0.1\n", head);
}
