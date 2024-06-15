/*
# eosMathSorting : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : eosMathSorting
# Attention
#   $Loccker$
#  	$State$ 
#
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"

#define DEBUG
#include "genUtil.h"
#include "Array.h"
#include "Memory.h"
#include "eosMath.h"

/*
Example:
typedef struct leosMathSortingInfo {
	float a;
	int   b;
} leosMathSortingInfo;

typedef enum leosMathSortingMode {
	a=0,
	b=1
} leosMathSortingMode;
*/

int
main(int argc, char* argv[]) 
{
	eosMathSortingInfo info;
  Array in;
  Array out;
  double* v;
  int n, i;

	init0(&info);
  argCheck(&info, argc, argv);
  init1(&info);

	DEBUGPRINT("Program Start\n");
  arrayReadFromFile(info.fptIn, &in, "in main");
  
  if(1<in.dim) {
    fprintf(stderr, "Not supported dim: %ld\n", in.dim);
    exit(EXIT_FAILURE);
  }
  n = in.n[0];
  v = memoryAllocate(sizeof(double)*n, "in main");
  for(i=0; i<n; i++) {
    v[i] = in.A[i];
  }

  eosMathSorting(v, n);

  out.dim = 1;
  out.n[0] = n;
  arrayInit(&out, "in message"); 

  for(i=0; i<n; i++) {
    out.A[i] = v[i];
  }

  arrayWriteToFile(info.fptOut, &out, "in main");

	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
}
