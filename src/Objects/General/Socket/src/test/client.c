#include "../../inc/Socket.h"

int
main(int argc, char* argv[])
{
	int s;
	char data[1024];	

	fprintf(stderr, "%d\n", argc);
	if(argc==3) {
		s = socketClientCreate(argv[1], atoi(argv[2]));	
	} else {
		fprintf(stderr, "%s hostname port\n", argv[0]);
		return -1;
	}

	if(s==-1) {
		fprintf(stderr, "Not connected\n");
		return -1;
	}
	while(1) {
		fgets(data, 1024, stdin); 
		if(data[0]=='\n') {
			break;
		} else {
			data[strlen(data)-1] = '\0';
			write(s, data, sizeof(data));
		}
	}
	close(s);
}

