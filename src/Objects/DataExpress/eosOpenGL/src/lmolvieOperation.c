/*
# lmolvieOperation : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : lmolvieOperation 
# Attention
#   $Loccker$
#  	$State$ 
#
*/
/* $Log$ */
#include "./lmolvie.h"

static operationMode __operation = normal;
static displayMode __display[5]={atom, atom, atom, atom, atom};

void 
operationModeSet(operationMode mode)
{
	__operation = mode; 
}

operationMode
operationModeGet(void)
{
	return __operation;
}

void displayModeSet(int number, displayMode mode)
{
	__display[number]=mode;
}

displayMode displayModeGet(int number)
{
	return __display[number];
}
