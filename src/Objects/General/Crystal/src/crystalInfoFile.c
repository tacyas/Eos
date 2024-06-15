/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% crystalInfoFile ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : crystalInfoFile
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%crystalInfoRead ver%I%; Date:%D% %Z%";
#include <stdlib.h>
#include "genUtil.h"
#include "eosString.h"
#include "../inc/Crystal.h"

void
crystalInfoRead(FILE* fpt, CrystalInfo* c, int mode) 
{
	char s[STRING_MAX_LENGTH];
	char* key;

	while(NULL!=(key=stringGetFromFile(s, "", fpt, stdout, 3))) {
		if('#' !=key[0]
		 &&'\0'!=key[0]) {
			key = stringGetNthWord(s, 1, STRING_WORD_SEPARATOR);
			SSWITCH(key) 
				SCASE("aAxis") {
					crystalAxisSet(c, 'a', 
						stringGetNthRealData(s, 2,  STRING_WORD_SEPARATOR),
						stringGetNthRealData(s, 3,  STRING_WORD_SEPARATOR),
						stringGetNthRealData(s, 4,  STRING_WORD_SEPARATOR), 0);
					SBREAK;
				}
				SCASE("bAxis") {
					crystalAxisSet(c, 'b', 
						stringGetNthRealData(s, 2,  STRING_WORD_SEPARATOR),
						stringGetNthRealData(s, 3,  STRING_WORD_SEPARATOR),
						stringGetNthRealData(s, 4,  STRING_WORD_SEPARATOR), 0);
					SBREAK;
				}
				SCASE("cAxis") {
					crystalAxisSet(c, 'c', 
						stringGetNthRealData(s, 2,  STRING_WORD_SEPARATOR),
						stringGetNthRealData(s, 3,  STRING_WORD_SEPARATOR),
						stringGetNthRealData(s, 4,  STRING_WORD_SEPARATOR), 0);
					SBREAK;
				}
				SCASE("CellLength") {
					crystalCellLengthSet(c, 'a', stringGetNthRealData(s, 2,  STRING_WORD_SEPARATOR), 0);
					crystalCellLengthSet(c, 'b', stringGetNthRealData(s, 3,  STRING_WORD_SEPARATOR), 0);
					crystalCellLengthSet(c, 'c', stringGetNthRealData(s, 4,  STRING_WORD_SEPARATOR), 0);
					SBREAK;
				}
				SCASE("Origin") {
					c->Origin.x = stringGetNthRealData(s, 2,  STRING_WORD_SEPARATOR);
					c->Origin.y = stringGetNthRealData(s, 3,  STRING_WORD_SEPARATOR);
					c->Origin.z = stringGetNthRealData(s, 4,  STRING_WORD_SEPARATOR);
					SBREAK;
				}
				SCASE("N") {
					c->N.a = stringGetNthIntegerData(s, 2,  STRING_WORD_SEPARATOR);
					c->N.b = stringGetNthIntegerData(s, 3,  STRING_WORD_SEPARATOR);
					c->N.c = stringGetNthIntegerData(s, 4,  STRING_WORD_SEPARATOR);
					SBREAK;
				}
				SCASE("StartN") {
					c->StartN.a = stringGetNthIntegerData(s, 2,  STRING_WORD_SEPARATOR);
					c->StartN.b = stringGetNthIntegerData(s, 3,  STRING_WORD_SEPARATOR);
					c->StartN.c = stringGetNthIntegerData(s, 4,  STRING_WORD_SEPARATOR);
					SBREAK;
				}
				SCASE("HelixInfo") {
					c->HelixInfo.t = stringGetNthIntegerData(s, 2,  STRING_WORD_SEPARATOR);
					c->HelixInfo.u = stringGetNthIntegerData(s, 3,  STRING_WORD_SEPARATOR);
					c->HelixInfo.n = stringGetNthIntegerData(s, 4,  STRING_WORD_SEPARATOR);
					SBREAK;
				}
				SCASE("SpaceGroup") {
					c->SpaceGroup = stringGetNthIntegerData(s, 2,  STRING_WORD_SEPARATOR);
					SBREAK;
				}
				SDEFAULT {
					fprintf(stderr, "Not supported key %s\n", key);
				}
			SSWITCHEND
		}
	}
}

void
crystalInfoWrite(FILE* fpt, CrystalInfo* c, int mode)
{
	fprintf(fpt, "aAxis       %15.6g %15.6g %15.6g\n", c->aAxis.x, c->aAxis.y, c->aAxis.z);
	fprintf(fpt, "bAxis       %15.6g %15.6g %15.6g\n", c->bAxis.x, c->bAxis.y, c->bAxis.z);
	fprintf(fpt, "cAxis       %15.6g %15.6g %15.6g\n", c->cAxis.x, c->cAxis.y, c->cAxis.z);
	fprintf(fpt, "CellLength  %15.6g %15.6g %15.6g\n", c->CellLength.a, c->CellLength.b, c->CellLength.c);
	fprintf(fpt, "Origin      %15.6g %15.6g %15.6g\n", c->Origin.x, c->Origin.y, c->Origin.z);
	fprintf(fpt, "N           %15d %15d %15d\n",       c->N.a, c->N.b, c->N.c);
	fprintf(fpt, "StartN      %15d %15d %15d\n",       c->StartN.a, c->StartN.b, c->StartN.c);
	fprintf(fpt, "SpaceGroup  %15d\n", c->SpaceGroup);
	switch(c->SpaceGroup) {
		case CrystalSpaceGroupHelical: {
			fprintf(fpt, "HelixInfo %10d %10d %10d\n", c->HelixInfo.t, c->HelixInfo.u, c->HelixInfo.n);
			break;
		}
		default: {
			break;
		}	
	}
}


void
crystalInfoFileFormat(FILE* fpt, int mode)
{
	fprintf(fpt, "aAxis       %%15.6g %%15.6g %%15.6g\n");
	fprintf(fpt, "bAxis       %%15.6g %%15.6g %%15.6g\n");
	fprintf(fpt, "cAxis       %%15.6g %%15.6g %%15.6g\n");
	fprintf(fpt, "CellLength  %%15.6g %%15.6g %%15.6g\n");
	fprintf(fpt, "Origin      %%15.6g %%15.6g %%15.6g\n");
	fprintf(fpt, "N           %%15d %%15d %%15d\n");
	fprintf(fpt, "StartN      %%15d %%15d %%15d\n");
	fprintf(fpt, "SpaceGroup  %%15d\n");
	fprintf(fpt, "HelixInfo   %%10d %%10d %%10d\n");
	fprintf(fpt, "### Attention ###\n");
	fprintf(fpt, "Parameter Order is important: Dependent between CellLength and a|b|cAxis.\n");
	fprintf(fpt, "                              Because each of aAxis, bAxis, cAxis must be a unit vector.\n");
	fprintf(fpt, "HelixInfo   t  u  n\n");
}

