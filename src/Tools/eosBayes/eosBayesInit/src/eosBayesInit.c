/*
# eosBayesInit : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : eosBayesInit
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
#include "eosString.h"
#include "eosBayes.h"

/*
Example:
typedef struct leosBayesInitInfo {
	float a;
	int   b;
} leosBayesInitInfo;

typedef enum leosBayesInitMode {
	a=0,
	b=1
} leosBayesInitMode;
*/

int
main(int argc, char* argv[]) 
{
	eosBayes out;
	eosBayesInitInfo info;
	eosBayesDistributionInfo llinfo;

	
	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");

	leosBayesInit(&out, info.numDistribution, info.numLikelihood, info.mode);

	// input: info.fptIn  
	// 0 min0 max0 delta0 mode0 mean0 sigma0
	// ...


	eosBayesCondition(info.fptIn, &out, &llinfo, 0);

	
	eosBayesPriorWrite(info.fptOut, &out, info.mode); 
	DEBUGPRINT("PriorWrite finish\n");
	
	exit(EXIT_SUCCESS);

}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
}
