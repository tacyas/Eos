/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% lllDatarMaxLimitForSeparation ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : lllDatarMaxLimitForSeparation 
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%lllDatarMaxLimitForSeparation ver%I%; Date:%D% %Z%";

#define DEBUG
#include "genUtil.h"

#include <stdlib.h>
#include "lllExtract.h"

void
lllDatarMaxLimitForSeparation(llData* llIn, llDataParaTypeReal rMax, lllExtractInfo* info, long mode)
{
	int l, l1, l2, l3, R;

	switch(mode) {
		case 0: {
			for(l=0; l<info->llMax; l++) {  /* info llMax*/	
				for(l1=0; l1<info->nn[l]; l1++) { /* info nn */ 	
					for(l2=0; l2<llIn->llMax; l2++) { /* All */
						if(info->ns[l][l1] == llIn->LL[l2].nn
						 &&info->l[l]      == llIn->LL[l2].nl) {
							for(R=0; R<llIn->LL[l2].nR; R++) {
								if(0==lllDatarMaxLimitCheck(llIn->LL[l2].data[R].RR,
															info->ns[l][l1],
															rMax)) {
									llIn->LL[l2].data[R].Re  = 0.0; 		
									llIn->LL[l2].data[R].Im  = 0.0; 		
									llIn->LL[l2].data[R].F   = 0.0; 		
									llIn->LL[l2].data[R].PHI = 0.0; 		
								} else {
								}
								for(l3=l1+1; l3<info->nn[l]; l3++) {
									if(fabs(info->ns[l][l1]) < fabs(info->ns[l][l3])) {
										if(1==lllDatarMaxLimitCheck(llIn->LL[l2].data[R].RR,
																info->ns[l][l3],
																rMax)) {
											llIn->LL[l2].data[R].Re  = 0.0; 
											llIn->LL[l2].data[R].Im  = 0.0;
											llIn->LL[l2].data[R].F   = 0.0;
											llIn->LL[l2].data[R].PHI = 0.0;
										}
										break;
									}
								}
							}
							break;
						}
					}
				}
			}
			break;
		}
		case 1: {
			for(l=0; l<info->llMax; l++) {  /* info llMax*/	
				for(l1=0; l1<info->nn[l]; l1++) { /* info nn */ 	
					for(l2=0; l2<llIn->llMax; l2++) { /* All */
						if(info->ns[l][l1] == llIn->LL[l2].nn
						 &&info->l[l]      == llIn->LL[l2].nl) {
							for(R=0; R<llIn->LL[l2].nR; R++) {
								if(0==lllDatarMaxLimitCheck(llIn->LL[l2].data[R].RR,
															info->ns[l][l1],
															rMax)) {
									llIn->LL[l2].data[R].Re  = 0.0; 		
									llIn->LL[l2].data[R].Im  = 0.0; 		
									llIn->LL[l2].data[R].F   = 0.0; 		
									llIn->LL[l2].data[R].PHI = 0.0; 		
								} else {
								}
								for(l3=l1+1; l3<info->nn[l]; l3++) {
									if(fabs(info->ns[l][l1]) < fabs(info->ns[l][l3])
									 &&IsEven(info->ns[l][l1] - info->ns[l][l3])) { 
										if(1==lllDatarMaxLimitCheck(llIn->LL[l2].data[R].RR,
																info->ns[l][l3],
																rMax)) {
											llIn->LL[l2].data[R].Re  = 0.0; 
											llIn->LL[l2].data[R].Im  = 0.0;
											llIn->LL[l2].data[R].F   = 0.0;
											llIn->LL[l2].data[R].PHI = 0.0;
										}
										break;
									}
								}
							}
							break;
						}
					}
				}
			}
			break;
		}
		default: {
			fprintf(stderr, "Not supported mode in lllDatarMaxLimitForSeparation: %ld\n", mode);
			exit(EXIT_FAILURE);
		}
	}
}
