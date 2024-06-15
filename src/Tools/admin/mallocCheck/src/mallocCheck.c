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
typedef struct lmallocCheckInfo {
	float a;
	int   b;
} lmallocCheckInfo;

typedef enum lmallocCheckMode {
	a=0,
	b=1
} lmallocCheckMode;
*/

int
main(int argc, char* argv[]) 
{
	mallocCheckInfo info;
	void* m;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");

	m = malloc(info.byte*info.item);	
	if(NULL!=m) {
		fprintf(stdout, "Success!: %ldx%ld\n", info.byte, info.item);
	} else {
		fprintf(stdout, "Failure!: %ldx%ld\n", info.byte, info.item);
		perror("mallocCheck:");
	}

	return EXIT_SUCCESS;
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
}
