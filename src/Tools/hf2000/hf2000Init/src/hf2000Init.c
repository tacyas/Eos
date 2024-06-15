/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% hf2000Init ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : hf2000Init
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%hf2000Init ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"

#define DEBUG
#include "genUtil.h"
#include "Socket.h"
#include "Memory.h"
#include "hf2000.h"

/*
Example:
typedef struct lhf2000InitInfo {
	float a;
	int   b;
} lhf2000InitInfo;

typedef enum lhf2000InitMode {
	a=0,
	b=1
} lhf2000InitMode;
*/

hf2000Info   hf2000;

void
main(int argc, char* argv[]) 
{
	hf2000InitInfo info;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");
	hf2000.deviceName = info.tty;
	hf2000.portSpeed  = info.speed;
	if(info.flagServer) {
		hf2000.flagServer = 1;
		hf2000.hostname   = info.Host; 
		hf2000.port       = info.Server;
		hf2000.maxPort    = 10;
	}
	
	DEBUGPRINT2("tty: %s on %s\n", hf2000.deviceName, hf2000.hostname);
	hf2000Init(&hf2000);
	if(info.flagServer) {
		while(1) {
			hf2000.serverFD = accept(hf2000.serverSocket, NULL, NULL);
			if(hf2000.serverFD == -1) {
				fprintf(stderr, "accept error\n");
			} else {
				DEBUGPRINT("Accepted\n");
			}
			if(0==fork()) { /* Child process */
				char s[1024];
				close(hf2000.serverSocket);
				read(hf2000.serverFD, s, 1024);
				DEBUGPRINT1("read from a client: %s\n", s);
				hf2000Write(&hf2000, s);
				hf2000Read (&hf2000, s);
				DEBUGPRINT1("write to a client :%s\n", s);
				write(hf2000.serverFD, s, 1024);
			}
			close(hf2000.serverFD);
		}
	} else {
		Tk_Main(argc, argv, hf2000_TclAppInit);
	}
	hf2000Close(&hf2000);
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
}

