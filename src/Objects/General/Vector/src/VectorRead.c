/*
# VectorRead : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : VectorRead 
# Attention
#   $Loccker$
#  	$State$ 
#
*/
/* $Log$ */

#include "eosString.h"
#include "File.h"
#include "../inc/Vector.h"

int
floatVectorFileReadOneLine(FILE* fpt, floatVector* v)
{
	int i;
	char s[STRING_MAX_LENGTH];

	if(NULL!=stringGetFromFile(s, "", fpt, stdout, 0)) {
		floatVectorInit(v, v->size);
		for(i=0; i<v->size; i++) {
			v->data[i] = stringGetNthRealData(s, i, " ,");
		}

		return v->size;
	} else {
		return 0;
	}	
}

void
floatVectorFileRead(FILE* fpt, floatVector* v)
{
			


}

