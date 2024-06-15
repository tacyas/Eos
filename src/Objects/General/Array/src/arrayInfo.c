/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% arrayInfo ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : arrayInfo 
#%Z% Attention
#%Z%
*/

static char __sccs_id[] = "%Z%arrayInfo ver%I%; Date:%D% %Z%";

#include "../inc/Array.h"

void
arrayFormatInfoPrint(FILE* fpt, int mode)
{
	fprintf(fpt, ">>> Array Format under Eos. 'nvalue' indicates the number of values in one line, in usual case, nvalue=N0. If so, you need not define nvalue.<<<<\n"); 
	fprintf(fpt, "ndim N0 N1 N2 ... [nvalue]\n");
	fprintf(fpt, "data(0,   0,   0,...,        0) data(1,   0,   0,...,        0) data(2,   0,   0,...,        0) ... data(N0-1,   0,   0,...,        0)\n");
	fprintf(fpt, "data(0,   1,   0,...,        0) data(1,   1,   0,...,        0) data(2,   1,   0,...,        0) ... data(N0-1,   1,   0,...,        0)\n");
	fprintf(fpt, "..............................................................\n");
	fprintf(fpt, "data(0,N1-1,   0,...,        0) data(1,N1-1,   0,...,        0) data(2,N1-1,   0,...,        0) ... data(N0-1,N1-1,   0,...,        0)\n");
	fprintf(fpt, "data(0,   0,   1,...,        0) data(1,   0,   1,...,        0) data(2,   0,   1,...,        0) ... data(N0-1,   0,   1,...,        0)\n");
	fprintf(fpt, "..............................................................\n");
	fprintf(fpt, "data(0,N1-1,N2-1,...,Nndim-1-1) data(1,N1-1,N2-1,...,Nndim-1-1) data(2,N1-1,N2-1,...,Nndim-1-1) ... data(N0-1,N1-1,N2-1,...,Nndim-1-1)\n");
}
