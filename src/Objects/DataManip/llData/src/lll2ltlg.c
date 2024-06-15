/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% lll2ltlg ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : lll2ltlg 
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%lll2ltlg ver%I%; Date:%D% %Z%";

#include "lll2ltlg.h"

void
ll2ltlgConfigFileRead(lll2ltlgInfo* linfo, FILE* fpt) 
{
	char s[1024];
	
	fseek(fpt, 0L, SEEK_SET);
	stringGetFromFile(s, "", fpt, stderr, 3);
	if(!linfo->flagTitle) {
		linfo->Title = stringGetNthWord(s, 1, "\n");	
	}
	stringGetFromFile(s, "", fpt, stderr, 3);
	if(!linfo->flagIn) {
		linfo->In = stringGetNthWord(s, 1, "\n");	
		linfo->fptIn = fileOpen(linfo->In, "r"); 
	}
	stringGetFromFile(s, "", fpt, stderr, 3);
	if(!linfo->flagTitle) {
		linfo->Out = stringGetNthWord(s, 1, "\n");	
		linfo->fptOut = fileOpen(linfo->Out, "w"); 
	}
	stringGetFromFile(s, "", fpt, stderr, 3);
	if(!linfo->flagdelRInv) {
		linfo->delRInv = stringGetNthRealData(s, 1, " \t,");
	}
	if(!linfo->flagllMax) {
		linfo->llMax = stringGetNthIntegerData(s, 2, " \t,");
	}
	if(!linfo->flagRMaxInv) {
		linfo->RMaxInv = stringGetNthRealData(s, 3, " \t,");
	}
	stringGetFromFile(s, "", fpt, stderr, 3);
	if(!linfo->flagdelr) {
		linfo->delr = stringGetNthRealData(s, 1, " \t,");
	}
	if(!linfo->flagrMax) {
		linfo->rMax = stringGetNthRealData(s, 2, " \t,");
	}
	stringGetFromFile(s, "", fpt, stderr, 3);
	if(!linfo->mode) {
		linfo->mode = stringGetNthIntegerData(s, 1, " \t,");
	}
}

void
lll2ltlg(ltlgData* out, llData* in, lll2ltlgInfo* linfo)
{
	ltlgDataParaTypeInteger status;

	/* Set ltlgData */
	strncpy(out->title1, linfo->Title, CommentLength); 
	strncpy(out->title2, in->LL[0].Head+SidePosition+4, CommentLength);
	if(linfo->flagdelRInv) {
		out->R.d = 1.0/linfo->delRInv;
	} else {
		out->R.d = in->LL[0].delBR;
	}
	if(linfo->flagRMaxInv) {
		out->R.Max = 1.0/linfo->RMaxInv;
		out->R.n = out->R.Max/out->R.d;
	} else {
		out->R.n = in->nRMax;
		out->R.Max = in->nRMax*out->R.d;
	}
	out->R.Min = 0.0;
	if(linfo->flagllMax) {
		out->ll.Max = linfo->llMax;
	} else {
		out->ll.Max = in->llMax;
	}
	out->r.d = linfo->delr;
	out->r.Max = linfo->rMax;
	out->r.n   = out->r.Max/out->r.d + 1;
	out->r.Min = 0.0;

	DEBUGPRINT1("llMax : %f in ll2ltlg\n", out->ll.Max);
	ltlgDataAllocate(out, &status);
	if(status==EXIT_FAILURE) {
		return;
	}

	/* Transform with Fourier-Bessel Transformation */
	emBessel(out, in);

}

void
emBessel(ltlgData* ltlg, llData* ll)
{
	float dRdR, drdR, ff, ftmp;
	float arg, re, im, recip, bfre, bfim, sumA, sumB;
	float* bsa;
	long nabs;
	long r, R, rR, rRMax, l, n;

/* Check Side */
	switch(ll->LL[0].Side) {
		case NearSide: {
			strncpy(ltlg->side, "NEAR", 4);
			break;
		}
		case FarSide: {
			strncpy(ltlg->side, "FAR ", 4);
			break;
		}
		case AverageSide: {
			strncpy(ltlg->side, "AVG ", 4);
			break;
		}
		default: {
			fprintf(stderr, "Not Supported Side\n");
			exit(EXIT_FAILURE);
		}
	}

	dRdR = 2.0*PI*ltlg->R.d*ltlg->R.d;
	drdR = 2.0*PI*ltlg->r.d*ltlg->R.d;

	for(l=0; l<ltlg->ll.Max; l++) {
		ltlg->llInfo[l].NN = ll->LL[l].nn;
		ltlg->llInfo[l].NL = ll->LL[l].nl;
		ltlg->llInfo[l].WT = ll->LL[l].Weight;
		rRMax = (ltlg->r.n - 1)*ll->nRMax + 1;
		bsa = (float*)memoryAllocate(sizeof(float)*(rRMax+1), "in emBessage");
		nabs = abs(ltlg->llInfo[l].NN);

		/* CALL EMBESL */
		if(nabs==0) {
			for(rR=0; rR<rRMax; rR++) {
                arg = drdR*rR;
				bsa[rR] = Bessel0(arg);
			}
		} else {
			for(rR=0; rR<rRMax; rR++) {
				arg = drdR*rR;
				if((arg<=(0.825*(nabs - 4.9)))||(arg==0.0)) {
					bsa[rR] = 0.0;
				} else {
					re = Bessel0(arg);
					im = Bessel1(arg);
					recip = 2.0/arg;
					for(n=1; n<=nabs; n++) {
						ftmp = n*im*recip - re;
						re = im; 
						im = ftmp; 
					}	
					bsa[rR] = re ;
				}
			}
		}

		/* After EMBESL */	
		for(r=0; r<ltlg->r.n; r++) {
			sumA = sumB = 0.0;
			ltlg->ltlg[l][r].r = r*ltlg->r.d;
			for(R=ll->LL[l].iRMin; R<=ll->LL[l].iRMax; R++) {
				ff    = (R + 1)*dRdR;
				rR    = (R + 1)*r;
				ftmp  = bsa[rR]*ff*ltlg->llInfo[l].WT;
    			sumA += ftmp*ll->LL[l].data[R - ll->LL[l].iRMin].Re;
				sumB += ftmp*ll->LL[l].data[R - ll->LL[l].iRMin].Im;
			}
			ltlg->ltlg[l][r].Re += sumA;
			ltlg->ltlg[l][r].Im += sumB;
		}

		/* Phase Correction */
		if(IsOdd(nabs)) {
			if(ll->LL[l].Side==FarSide) {
				for(r=0; r<ltlg->r.n; r++) {
					ltlg->ltlg[l][r].Re = -ltlg->ltlg[l][r].Re;
					ltlg->ltlg[l][r].Im = -ltlg->ltlg[l][r].Im;
				}
			}
		}
		free(bsa);
	}
}

ltlgDataParaTypeReal
Bessel0(ltlgDataParaTypeReal x0)
{
	ltlgDataParaTypeReal x1, x2, p, q, bsl0;

    if(x0<4.0) {
        x2=SQR(x0/4.0);
        bsl0 =  ((((((-0.00050144*x2+0.00767719)*x2-0.07092536)*x2+
                     0.44435843)*x2-1.7777561)*x2+3.9999973)*x2-3.9999999)*x2+1.0;
    } else {
        x1=4.0/x0;
        x2 = SQR(x1);
        p = ((((-0.00000370*x2+0.0001736)*x2-.48761e-04)*x2+0.00017343)*
                x2-0.00175306)*x2+0.39894228;
        q = (x1)*(((((0.00000323*x2-0.00001421)*x2+0.00003425)*x2-
            0.00008698)*x2+0.00045643)*x2-0.01246694);
        bsl0 =  sqrt(x1)*(p*cos(x0-.7853981e+00)-q*sin(x0-.7853981e+00));
    }
    return bsl0;
}

ltlgDataParaTypeReal
Bessel1(ltlgDataParaTypeReal x0)
{
	ltlgDataParaTypeReal x1, x2, p, q, bsl1;

    if(x0<4.0) {
        x1 = x0/4.0;
        x2 = SQR(x1);
        bsl1 = x1*(((((((-0.0001290 *x2+0.0022069 )*x2-0.02366168)*x2+
                   0.1777583 )*x2-0.8888840 )*x2+2.6666661)*x2-4.0)*x2+2.0);
    } else {
        x1 = 4.0/x0;
        x2 = SQR(x1);
        p = ((((0.0000042 *x2-0.0000201 )*x2+0.0000581 )*x2-0.0002232 )*x2
             +0.0029218 )*x2+0.3989423;
        q = (x1)*(((((-0.0000037 *x2+0.0000162 )*x2-.398708e-04)*x2
             +0.0001065 )*x2-0.0006390 )*x2+0.0374008 );
        bsl1 = sqrt(x1)*(p*sin(x0-.7853981e+00)+q*cos(x0-.7853981e+00));
    }
    return bsl1;
}