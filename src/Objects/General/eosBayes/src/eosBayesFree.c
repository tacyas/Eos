/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% eosBayesFree ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : eosBayesFree 
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%eosBayesFree ver%I%; Date:%D% %Z%";

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../inc/eosBayes.h"
#define DEBUG
#include "genUtil.h"


void eosBayesFree(eosBayes* d){

  DEBUGPRINT("In eosBayesFree\n");

  free(d->prior->value);
  free(d->prior->prob);

  free(d->posterior->value);
  free(d->posterior->prob);

  free(d->likelihood->value);
  free(d->likelihood->prob);

  free(d->prior);
  free(d->posterior);
  free(d->likelihood);

  DEBUGPRINT("Compreated eosBayesFree\n");

}
