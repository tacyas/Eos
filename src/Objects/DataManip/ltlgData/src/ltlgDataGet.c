#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "genUtil.h"
#include "../inc/ltlgData.h"

long
ltlgDataLNumberGet(ltlgData* ltlg, ltlgDataParaTypeInteger n, ltlgDataParaTypeInteger l)
{
    long i;
    for(i=0; i<ltlg->ll.Max; i++) {
		if(l == ltlg->llInfo[i].NL
		 &&n == ltlg->llInfo[i].NN) {
			return i;
		}
    }

	exit(EXIT_FAILURE);
}

ltlgDataParaTypeReal
ltlgDataGet(ltlgData* ltlg, 
			ltlgDataParaTypeInteger n, 
			ltlgDataParaTypeInteger l, 
			ltlgDataParaTypeReal r, 
			ltlgDataParaTypeReal* data,
			ltlgDataType type, ltlgDataHow how)
{
	ltlgDataGet2(ltlg, ltlgDataLNumberGet(ltlg, n, l), r, data, type, how);
	return *data;
}

ltlgDataParaTypeReal
ltlgDataGet2(ltlgData* ltlg, 
			 long ll, 
			 ltlgDataParaTypeReal r, 
			 ltlgDataParaTypeReal* data,
			 ltlgDataType type, ltlgDataHow how)
{
    long ir, irr;
    ltlgDataParaTypeReal    rr, rbit, rbar;
	double                  re, im;

	rr = r/ltlg->r.d;
	ir = floor(rr);
	switch(how) {
		case ltlgDataHowNearest: {
			irr = (ltlgDataParaTypeInteger)(rr+0.5);
			switch(type) {
				case ltlgDataTypeRePart: {
					*data = ltlg->ltlg[ll][irr].Re;
					break;
				}
				case ltlgDataTypeImPart: {
					*data = ltlg->ltlg[ll][irr].Im;
					break;
				}
				case ltlgDataTypeMag: {
					*data = sqrt(SQR(ltlg->ltlg[ll][irr].Re)
								+SQR(ltlg->ltlg[ll][irr].Im));
					break;
				}
				case ltlgDataTypePhase: {
					*data = atan2(ltlg->ltlg[ll][irr].Im
								 ,ltlg->ltlg[ll][irr].Re);
					break;
				}
				default: {
					fprintf(stderr, "Not supported Type : %d\n", type);
				}
			}
			break;
		}
		case ltlgDataHowLinear: {
			rbit = rr - ir;
			rbar = 1.0 - rbit;
			re = rbar*ltlg->ltlg[ll][ir].Re
				+rbit*ltlg->ltlg[ll][ir+1].Re;
			im = rbar*ltlg->ltlg[ll][ir].Im
				+rbit*ltlg->ltlg[ll][ir+1].Im;
			switch(type) {
				case ltlgDataTypeRePart: {
					*data = re;
					break;
				}
				case ltlgDataTypeImPart: {
					*data = im;
					break;
				}
				case ltlgDataTypeMag: {
					*data = sqrt(SQR(re)+SQR(im));
					break;
				}
				case ltlgDataTypePhase: {
					*data = atan2(im, re);
					break;
				}
				default: {
					fprintf(stderr, "Not supported Type : %d\n", type);
				}
			}
		}
		default: {
			fprintf(stderr, "Not supported How: %d\n", how);
		}
	}
	return *data;
}
