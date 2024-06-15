/*
# srandom : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : srandom 
# Attention
#   $Loccker$
#  	$State$ 
#
*/
/* $Log$ */

#include <time.h>
#include <sys/timeb.h>

#include "../inc/Random.h"

void
srandomByTime()
{
	struct timeb time; 
	//time_t t;

	ftime(&time);
	srand(time.time+time.millitm);
}
