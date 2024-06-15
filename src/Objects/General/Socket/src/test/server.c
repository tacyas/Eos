#include "../../inc/Socket.h"

int
main(int argc, char* argv[])
{
	int s;
	char word[1024];
	size_t byte;

	fprintf(stderr, "%d\n", argc);
	if(argc==3) {
		s = socketServerCreate(argv[1], atoi(argv[2]));	
	} else {
		fprintf(stderr, "%s hostname port\n", argv[0]);
		return -1;
	}
	
	if(s==-1) {
		fprintf(stderr, "Not accepting\n");
		return -1;
	}
	while(1) {
		byte = read(s, word, 1024);
		if(0<byte)  {
			fprintf(stdout, "from client: %s\n", word);
		}
	}
	close(s);
}

