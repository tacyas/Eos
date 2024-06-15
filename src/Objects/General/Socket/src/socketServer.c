/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% socketServer ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : socketServer 
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%socketServer ver%I%; Date:%D% %Z%";

#include "../inc/Socket.h"
#define DEBUG
#include "genUtil.h"

int
socketServerCreate(char* hostname, u_short port)
{
	struct hostent* myhost;
	struct sockaddr_in me;
	int s;
	int s_waiting;

	/* get hostent from hostname */ 
	if((myhost = gethostbyname(hostname)) == NULL) {
		fprintf(stderr, "bad hostname ! \n");
		return -1;
	}
	DEBUGPRINT1("h_name: %s\n", myhost->h_name);

	bzero((char*)&me, sizeof(me));
	me.sin_family = AF_INET;
	me.sin_port   = port;
	bcopy(myhost->h_addr, (char*)&me.sin_addr, myhost->h_length);

	/* Create socket */
	if((s_waiting = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		perror("socketServerCreate");
		fprintf(stderr, "socket allocation failed. \n");
		return -1;
	}

	/* assign the port to the socket */
	if(bind(s_waiting, &me, sizeof(me)) == -1) {
		perror("socketServerCreate");
		fprintf(stderr, "cannot bind.\n");
		return -1;
	}
	DEBUGPRINT("successfully bound, now listens.\n");

	/* Wait for a client */
	if(listen(s_waiting, 1) == -1) {
		perror("socketServerCreate");
		return -1;
	}; 
	DEBUGPRINT("ServerSetup listen\n");

	/* accept a request from a client */
	if((s = accept(s_waiting, NULL, NULL)) == -1) {
		perror("socketServerCreate");
		return -1;
	}
	close(s_waiting);

	DEBUGPRINT("Server Setup Finished\n");
	return s;
}


int
socketMultiServerCreate(char* hostname, u_short port, int max)
{
	struct hostent* myhost;
	struct sockaddr_in me;
	int s;

	myhost = gethostbyname(hostname);
	if(myhost == NULL) {
		perror("in socketMultiServerCreate");
		fprintf(stderr, "bad hostname ! \n");
		return -1;
	}

	DEBUGPRINT1("h_name: %s\n", myhost->h_name);

	bzero((char*)&me, sizeof(me));
	me.sin_family = AF_INET;
	me.sin_port   = port;
	bcopy(myhost->h_addr, (char*)&me.sin_addr, myhost->h_length);

	/* Create a socket */
	if((s = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		perror("socketServerCreate");
		fprintf(stderr, "socket allocation failed. \n");
		return -1;
	}

	/* Bind the socket to port */
	if(bind(s, &me, sizeof(me)) == -1) {
		perror("socketServerCreate");
		fprintf(stderr, "cannot bind.\n");
		return -1;
	}
	fprintf(stderr, "successfully bound, now listens.\n");

	/* Now, listening */
	if(listen(s, max) == -1) {
		perror("socketServerCreate");
		return -1;
	}; 
	DEBUGPRINT("ServerSetup listen\n");
	DEBUGPRINT("Server Setup Finished\n");
	return s;
}

int
socketMultiServerAccept(int w_soc, int limit, void (*func)())
{
	int i;
	int fd=-1;

	for(i=0; i<limit; i++) {
		fd = accept(w_soc, NULL, NULL);
		if(fd == -1) {
			fprintf(stderr, "accept error\n");
			return -1;
		}
		(*func)(i, fd);
	}
	close(w_soc);
	return fd;
}

