/*
	Socket.h
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

/* prototype begin */
extern int  socketServerCreate(char* hostname, u_short port);
extern int  socketMultiServerCreate(char* hostname, u_short port, int max);
extern int  socketClientCreate(char* hostname, u_short port);
/* prototype end */
