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
#define __HF2000INIT__
#include "../inc/hf2000.h"
#undef  __HF2000INIT__

#define DEBUG 
#include <stdio.h>
#include <stdlib.h>
#include "genUtil.h"
#include <string.h>
#include "eosString.h"
#include "Socket.h"

static void __hf2000Init(hf2000Info* info);

void
hf2000Init(hf2000Info* info)
{
	if(1==info->flagServer) {
		__hf2000Init(info);
		info->serverSocket = socketMultiServerCreate(info->hostname, info->port, info->maxPort);
		if(-1==info->serverSocket) {
			fprintf(stderr, "Not sccepted\n");
			exit(EXIT_FAILURE);
		}
	} else if(1==info->flagClient) {
		info->fd = socketClientCreate(info->hostname, info->port);	
		if(-1==info->fd) {
			fprintf(stderr, "Not connected\n");
			exit(EXIT_FAILURE);
		}
	} else {
		__hf2000Init(info);
	}
}

void
__hf2000Init(hf2000Info* info)
{
	char s[1024];
	int oldFlags;
	int iter;
	int oflag;

	/* Open device for reading and writing and not as controlling tty
	  because we do not want to get killed if linenoise sends CTRL-C */
	DEBUGPRINT("hf2000Init Start\n");

	oflag = O_RDWR|O_APPEND|O_NOCTTY|O_NDELAY;
	info->fd = open(info->deviceName, oflag); 
	DEBUGPRINT("Open\n");
	if(info->fd<0) {
		sprintf(s, "%s in hf2000Init", info->deviceName);
		perror(s);
		exit(EXIT_FAILURE);
	}
	
	oldFlags = fcntl(info->fd, F_GETFL, 0);
	fcntl(info->fd, F_SETFL, oldFlags & ~O_NDELAY);

	DEBUGPRINT("ATTRIBUTE GET");
	tcgetattr(info->fd, &(info->prevIO));
	bzero(&(info->IO), sizeof(info->IO));
	if(4800==info->portSpeed) {
		/* Ctrl:           4800baud | 7bits | Parity Odd  | Recieve    | StopBits 2 */
		info->IO.c_cflag = B4800    | CS7   |PARODD|PARENB| CREAD      | CSTOPB;
	} else {
		/* Ctrl:           1200baud | 7bits | Parity Odd  | Recieve    | StopBits 2 */
		info->IO.c_cflag = B1200    | CS7   |PARODD|PARENB| CREAD      | CSTOPB;
	}
	/* Input:          CR to NL */
	info->IO.c_iflag = ICRNL; 
	/* Output:         */
	info->IO.c_oflag = 0;
	/* Local : */
	info->IO.c_lflag = ICANON;
	/* */

	tcflush(info->fd, TCIFLUSH);
	DEBUGPRINT("ATTRIBUTE SET\n");
	tcsetattr(info->fd, TCSANOW, &(info->IO));

	iter = 0;
	while(iter<10) {
		DEBUGPRINT1("*R : %s\n", __hf2000CommandList[HF2000CMD_Initialize]);
		hf2000Write(info, __hf2000CommandList[HF2000CMD_Initialize]);
		DEBUGPRINT ("OK? \n");
		hf2000Read (info, s);
		DEBUGPRINT1("OK : %s\n", s);
		if(0==strcmp(s, "OK")) {
			break;
		}
		iter++;
	}
	if(10<=iter) {
		fprintf(stderr, "Cannot initialize the EM\n");
		fprintf(stderr, "Please check lines \n");
		exit(EXIT_FAILURE);	
	}
}

