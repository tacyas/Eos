/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% lllDataCTFCompensate ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : lllDataCTFCompensate 
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%lllDataCTFCompensate ver%I%; Date:%D% %Z%";
#include "lllDataCTFCompensate.h"

void 
llDataCTFSet2(llData* llInfo, FILE* fpt)
{
	ctfInfo ctf;
    llDataParaTypeInteger ll, iR;
    char s[GEN_UTIL_MAX_STRING_LENGTH];
	double CTF, F, R;

	fseek(fpt,0L, SEEK_SET);
    stringGetFromFile(s, "", fpt, NULL, 1);
	ctf.defocus = stringGetNthRealData(s, 1, SECTION_MARK);
	ctf.Cs = stringGetNthRealData(s, 2, SECTION_MARK);
	ctf.kV = stringGetNthRealData(s, 3, SECTION_MARK);
	ctf.ratioOfAmpToPhase = stringGetNthRealData(s, 4, SECTION_MARK);
	ctf.mode = ctfInfoModePhaseAndAmpCTF;
	ctf.Ain  = 0.02;

    for(ll=0; ll<llInfo->llMax; ll++) {
        for(iR=0; iR<llInfo->LL[ll].nR; iR++) {
            R = sqrt(SQR(llInfo->LL[ll].data[iR].RR)+SQR(llInfo->LL[ll].nl/llInfo->truePitch));
			CTF = ctfFunction(&ctf, R, 0);
			if(CTF!=0) {
				F = CTF/fabs(CTF);
			} else {
				F = 1.0;
			}
            llInfo->LL[ll].data[iR].F   = fabs(F);
			if(0<F) {
            	llInfo->LL[ll].data[iR].PHI = 0;
			} else {
            	llInfo->LL[ll].data[iR].PHI = M_PI;
			}
            llInfo->LL[ll].data[iR].Re  = F;
            llInfo->LL[ll].data[iR].Im  = 0;
		}
	}
}

void
llDataCTFSet(llData* llInfo, FILE* fpt)
{
    llDataParaTypeInteger ll, iR;
    llDataParaTypeReal    R, RR0, RR1, F0, F1, PHI0, PHI1;
    char s[GEN_UTIL_MAX_STRING_LENGTH];

    fseek(fpt, 0L, SEEK_SET);
    stringGetFromFile(s, "", fpt, NULL, 1);
    RR0  = stringGetNthRealData(s, 1, SECTION_MARK);
    F0   = stringGetNthRealData(s, 2, SECTION_MARK);
    PHI0 = stringGetNthRealData(s, 3, SECTION_MARK)*RADIAN;
    for(ll=0; ll<llInfo->llMax; ll++) {
        for(iR=0; iR<llInfo->LL[ll].nR; iR++) {
            R = sqrt(SQR(llInfo->LL[ll].data[iR].RR)+SQR(llInfo->LL[ll].nl/llInfo->truePitch));
            if(R<RR0) {
                llInfo->LL[ll].data[iR].F   = 0;
                llInfo->LL[ll].data[iR].PHI = 0;
                llInfo->LL[ll].data[iR].Re  = 0;
                llInfo->LL[ll].data[iR].Im  = 0;
            } else {
                break;
            }
        }
    }
    while(NULL!=stringGetFromFile(s, "", fpt, NULL, 1)) {
        RR1  = stringGetNthRealData(s, 1, SECTION_MARK);
        F1   = stringGetNthRealData(s, 2, SECTION_MARK);
        PHI1 = stringGetNthRealData(s, 3, SECTION_MARK)*RADIAN;
        for(ll=0; ll<llInfo->llMax; ll++) {
            for(iR=0; iR<llInfo->LL[ll].nR; iR++) {
                R = sqrt(SQR(llInfo->LL[ll].data[iR].RR)+SQR(llInfo->LL[ll].nl/llInfo->truePitch));
                if(R<RR0) {
                } else if(RR0<=R && R<RR1) {
                    llInfo->LL[ll].data[iR].Re  = (F0*cos(PHI0)*(RR1-R)+F1*cos(PHI1)*(R-RR0))/(RR1-RR0);
                    llInfo->LL[ll].data[iR].Im  = (F0*sin(PHI0)*(RR1-R)+F1*sin(PHI1)*(R-RR0))/(RR1-RR0);
                    llInfo->LL[ll].data[iR].F   = sqrt(SQR(llInfo->LL[ll].data[iR].Re)+SQR(llInfo->LL[ll].data[iR].Im));
                    llInfo->LL[ll].data[iR].PHI = atan2(llInfo->LL[ll].data[iR].Im, llInfo->LL[ll].data[iR].Re);
                } else {
                    break;
                }

            }
        }
        RR0  = RR1;
        F0   = F1;
        PHI0 = PHI1;
    }
    for(ll=0; ll<llInfo->llMax; ll++) {
        for(iR=0; iR<llInfo->LL[ll].nR; iR++) {
            R = sqrt(SQR(llInfo->LL[ll].data[iR].RR)+SQR(llInfo->LL[ll].nl/llInfo->truePitch));
            if(RR0<R) {
                llInfo->LL[ll].data[iR].F   = 0;
                llInfo->LL[ll].data[iR].PHI = 0;
                llInfo->LL[ll].data[iR].Re  = 0;
                llInfo->LL[ll].data[iR].Im  = 0;
            }
        }
    }
}

void
configFileRead(FILE* fpt, lllDataCTFCompensateInfo* linfo)
{
    char s[1024];

    fseek(fpt, 0L, SEEK_SET);
    stringGetFromFile(s, "", fpt, stdout, 3);
    if(!linfo->flagIn) {
        linfo->In = stringGetNthWord(s, 1, " \t,");
        linfo->fptIn = fileOpen(linfo->In, "r");
        linfo->flagIn++;
    }
    
    stringGetFromFile(s, "", fpt, stdout, 3);
    if(!linfo->flagIn1) {
        linfo->In1 = stringGetNthWord(s, 1, " \t,");
        linfo->fptIn1 = fileOpen(linfo->In1, "r");
        linfo->flagIn1++;
    }
    
    stringGetFromFile(s, "", fpt, stdout, 3);
    if(!linfo->flagOut) {
        linfo->Out = stringGetNthWord(s, 1, " \t,");
        linfo->fptOut = fileOpen(linfo->Out, "w");
        linfo->flagOut++;
    }
    
    stringGetFromFile(s, "", fpt, stdout, 3);
    if(!linfo->flagtruePitch) {
        linfo->truePitch = stringGetNthRealData(s, 1, " \t,");
        linfo->flagtruePitch++;
    }
    
    stringGetFromFile(s, "", fpt, stdout, 3);
    if(!linfo->flagmode) {
        linfo->mode = stringGetNthIntegerData(s, 1, " \t,");
        linfo->flagmode++;
    }
    
}

void
configFileUsage(FILE* fpt)
{
    fprintf(fpt, "----- Control File -----\n");
    fprintf(fpt, "In[inFile:NULL]\t\t\t\t#InputDataFile\n");
    fprintf(fpt, "In1[inFile:NULL]\t\t\t\t#InputCTFInformation\n");
    fprintf(fpt, "Out[outFile:NULL]\t\t\t\t#OutputDataFile\n");
    fprintf(fpt, "truePitch[Real:100.0]\t\t\t\t#truePitch[A]\n");
    fprintf(fpt, "mode[Integer:0]\t\t\t\t#Mode\n");
}
