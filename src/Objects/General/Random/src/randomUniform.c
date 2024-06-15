/*
# randomUniform : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : randomUniform 
# Attention
#   $Loccker$
#  	$State$ 
#
*/
/* $Log$ */

#include "../inc/Random.h"

randomParaTypeReal
randomUniformGet(randomParaTypeReal min, randomParaTypeReal max, long mode)
{
	return random()*(max - min) + min;
}
