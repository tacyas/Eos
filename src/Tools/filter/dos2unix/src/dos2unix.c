/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% dos2unix ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : dos2unix
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%dos2unix ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"

#define DEBUG
#include "genUtil.h"

/*
Example:
typedef struct ldos2unixInfo {
	float a;
	int   b;
} ldos2unixInfo;

typedef enum ldos2unixMode {
	a=0,
	b=1
} ldos2unixMode;
*/

void
main(int argc, char* argv[]) 
{
	int c;
	int flag=0;
	dos2unixInfo info;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");

	while(EOF!=(c = getc(info.fptIn))) {
		if(c!='\r') {
			if(1==flag && c!='\n') { /* CR without NL*/
				putc('\n', info.fptOut);
				putc(c, info.fptOut);
			} else {
				putc(c, info.fptOut); 
			}
			flag = 0;
		} else {
			flag = 1;
		}
	}
	
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
}

