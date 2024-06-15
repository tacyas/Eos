/*
# eosMathMedian : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : eosMathMedian
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
#include "Memory.h"
#include "Array.h"
#include "eosMath.h"

/*
Example:
typedef struct leosMathMedianInfo {
	float a;
	int   b;
} leosMathMedianInfo;

typedef enum leosMathMedianMode {
	a=0,
	b=1
} leosMathMedianMode;
*/

int
main(int argc, char* argv[]) 
{
	eosMathMedianInfo info;
  Array in;
  int n, i;
  double* v;
  double med;

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

  switch(info.mode) {
    case 0: {
      med = eosMathMedian(v, n);
      break;
    }
    case 1: {
      med = eosMathHodgesLehmannEstimator(v, n);
      break;
    }
    default: {
      fprintf(stderr, "Not supported mode: %ld\n", info.mode);
      exit(EXIT_FAILURE);
    }
  }

  fprintf(info.fptOut, "%f\n", med);
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
	fprintf(stderr, "-m 0 : median\n");
	fprintf(stderr, "-m 1 : HodgesLehmannEstimator\n");

}
