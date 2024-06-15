/*
# eosMathAverage : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : eosMathAverage
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
typedef struct leosMathAverageInfo {
	float a;
	int   b;
} leosMathAverageInfo;

typedef enum leosMathAverageMode {
	a=0,
	b=1
} leosMathAverageMode;
*/

int
main(int argc, char* argv[]) 
{
	eosMathAverageInfo info;
  Array in;
  int n, i;
  int nn;
  double* v;
  double avg;
  double* vv;

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

  if(info.flagTrim) {
    vv = eosMathTrimming(&vv, &nn, v, n, info.Trim);
  } else {
    vv = v;
    nn = n;
  }
#ifdef DEBUG
  for(i=0; i<n; i++) DEBUGPRINT1(" %f", v[i]); DEBUGPRINT("\n");
  for(i=0; i<nn; i++) DEBUGPRINT1(" %f", vv[i]); DEBUGPRINT("\n");
#endif
  switch(info.mode) {
    case 0: {
      avg = eosMathAverage(vv, nn);
      break;
    } 
    case 1: {
      avg = eosMathWeightedAverage(vv, nn);
      break;
    }
    default: {
      fprintf(stderr, "Not supported mode: %ld\n", info.mode);
      exit(EXIT_FAILURE);
    }
  }

  fprintf(info.fptOut, "%f\n", avg);
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
	fprintf(stderr, "-m 0 : Average\n");
	fprintf(stderr, "-m 1 : WeightedAverage\n");
	fprintf(stderr, "-m 0 -trim xx: Trimming\n");
	fprintf(stderr, "-m 1 -trim xx: Trimming\n");
}
