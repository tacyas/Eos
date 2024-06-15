#include <stdio.h>
#include <stdlib.h>
#include "../inc/SpecialNumber.h"
long 
pow2nn(long n)
{
	long n2;
	long bit;

	if(n<2) {
		fprintf(stderr, "mrcImage is too small\n");
		exit(EXIT_FAILURE);
	}
	n2 = n - 1;
	bit = 0;
	while(n2!=1) {
		n2 = n2>>1;
		bit++;
	}
	n2 = n2<<(bit+1);
	return n2;
}
