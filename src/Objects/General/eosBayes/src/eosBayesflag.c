/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% eosBayesflag ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : eosBayesflag 
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%eosBayesflag ver%I%; Date:%D% %Z%";

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../inc/eosBayes.h"

#define  DEBUG
#include "genUtil.h"
#include "eosString.h"

void eosBayesMaxposteriorflagSet(eosBayes* d, int Distnum){
  d->posterior[Distnum].maxposteriorflag = 1;
  d->posterior[Distnum].rangechangeflag = 0;
  d->posterior[Distnum].n = 1;
  d->prior[Distnum].n = 1;
  d->likelihood[Distnum].n = 1;
}


void eosBayesRangeChangeflagSet(eosBayes*d, int Distnum, float percentageofrange, int nofpartitions){
  d->posterior[Distnum].rangechangeflag   = 1;
  d->posterior[Distnum].percentageofrange = percentageofrange;
  d->posterior[Distnum].nofpartitions     = nofpartitions;
}
