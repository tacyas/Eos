#include <stdio.h>
#include "llData.h"

void
llDataError(char* s)
{
	fprintf(stderr, "Something wrong\n");
	fprintf(stderr, "%s\n", s);
}

void
llDataErrorMsg(void)
{

}
