#include <stdio.h>
#include <stdlib.h>

#define GLOBAL_DECLARATION
#include "../../inc/Crystal.h"

int 
main(int argc, char* argv[])
{
	CrystalInfo c;

	crystalSpaceGroupPrint(stderr, 0);
	crystalInfoFileFormat(stderr, 0);
	crystalInit(&c);
	crystalInfoRead(stdin, &c, 0);
	crystalInfoWrite(stdout, &c, 0);
	return 0;
}
