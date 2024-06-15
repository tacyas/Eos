/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% socketClient ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : socketClient 
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%socketClient ver%I%; Date:%D% %Z%";

#include "../inc/Socket.h"

int
socketClientCreate(char* hostname, u_short port)
{
    struct hostent*    serverHost;
    struct sockaddr_in server;
    int s;

    if((serverHost = gethostbyname(hostname)) == NULL) {
        fprintf(stderr, "bad hostname ! \n");
        return -1;
    }
    bzero((char*)&server, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_port   = port;
    bcopy(serverHost->h_addr, (char*)&server.sin_addr, serverHost->h_length);

	if((s=socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		fprintf(stderr, "socket allocation failed.\n");
		return -1;
	}

	if(connect(s, &server, sizeof(server)) == -1) {
		perror("socketClientCreate");
		fprintf(stderr, "cannot connect. %d\n", s);
		return -1;
	}

	fprintf(stderr, "connected.\n");

    return s;
}

