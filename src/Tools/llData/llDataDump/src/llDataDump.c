/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% llDataDump ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : llDataDump
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%llDataDump ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"

#define DEBUG
#include "genUtil.h"
#include "llData.h"

void lllDataDump(llData* ll, double RMax, int mode);

/*
Example:
typedef struct lllDataDumpInfo {
	float a;
	int   b;
} lllDataDumpInfo;

typedef enum lllDataDumpMode {
	a=0,
	b=1
} lllDataDumpMode;
*/

int
main(int argc, char* argv[]) 
{
	llDataDumpInfo info;
	llData ll;
	llDataParaTypeInteger status;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");
	llDataFileRead(info.fptIn, &ll, &status);
	lllDataDump(&ll, info.RMax, info.mode);

	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
}

void lllDataDump(llData* ll, double RMax, int mode)
{
  int l, R;

  DEBUGPRINT("a ");
  /*
  if(!ll->RValueSet) {
    llDataRValueSet(ll, 0);
  }
  */
  
  for(l=0; l<ll->llMax; l++) {
    for(R=0 ;R<ll->LL[l].nR ; R++) {
      if (ll->LL[l].data[R].RR < RMax){
	fprintf(stdout,"%d %g %g %g\n",l,ll->LL[l].data[R].RR, ll->LL[l].data[R].F, ll->LL[l].data[R].PHI);
      } else {
	break;
      }
    }
  }
}
