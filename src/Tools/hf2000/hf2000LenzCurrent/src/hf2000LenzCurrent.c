/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% hf2000LenzCurrent ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : hf2000LenzCurrent
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%hf2000LenzCurrent ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#include <tcl.h>
#include <tk.h>
#define GLOBAL_DECLARATION
#include "../inc/config.h"

#define DEBUG
#include "genUtil.h"
#include "hf2000.h"
#include "lhf2000LenzCurrent.h"

extern int Tcl_AppInit(Tcl_Interp *interp);

hf2000Info hf2000;
hf2000LenzCurrentInfo  info;
lhf2000LenzCurrentInfo linfo;

void
main(int argc, char* argv[]) 
{
	hf2000LenzCurrent C;
	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");
	hf2000.deviceName = info.tty;
	hf2000.portSpeed  = info.speed;
	hf2000Init(&hf2000);

	if(info.flagInteractive) {
		DEBUGPRINT("Tk_Main");
		Tk_Main(argc, argv, hf2000_TclAppInit);
	} else {
		C = lhf2000LenzCurrentGet0(&hf2000, info.which, 0);
		fprintf(info.fptOut, "%s %6x %15.6e\n", info.which, C.D, C.A);
	}
	exit(EXIT_SUCCESS);
}

 void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
}
