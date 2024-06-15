/*
# anglediffchk : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : anglediffchk
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

/*
Example:
typedef struct langlediffchkInfo {
	float a;
	int   b;
} langlediffchkInfo;

typedef enum langlediffchkMode {
	a=0,
	b=1
} langlediffchkMode;
*/

int
main(int argc, char* argv[]) 
{
	anglediffchkInfo info;
	double ans;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

/*
	ans= info.Test - info.Reference;
	if(ans<0.0) ans*=(-1);
	while(ans>360){
		ans-=360;
	}
	if(ans>180) ans = 360-ans;
	//ans=100.0;
*/
	ans = MIN_NORMAL_PHASE(info.Test*RADIAN-info.Reference*RADIAN);
	fprintf(info.fptOut, "%f\n",ans*DEGREE);
 
	return EXIT_SUCCESS;
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
}
