/*
# powerspectraTangentLine.h : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : powerspectraTangentLine.h 
# Attention
#   $Loccker$
#  	$State$ 
#
*/
/* $Log$ */
#ifndef POWER_SPECTRA_TANGENT_LINE_H
#define POWER_SPECTRA_TANGENT_LINE_H

#include "mrcImage.h"
#include "ctfInfo.h"
#include "lctfDetermination.h"

/*prototype begin*/
extern void TangentLine(floatVector* spacing, 
		floatVector* scatter,
		float** belowCoefficient, 
		float** aboveCoefficient, 
		ctfInfo* ini,
		lctfDetermineInfo* linfo,
		int mode); 
extern void TangentLinePrint(FILE* fpt, floatVector* spacing, 
		floatVector* scatter,
		float** belowCoefficient, 
		float** aboveCoefficient, 
		lctfDetermineInfo* linfo,
		int mode); 


/*prototype end*/

#endif /*POWER_SPECTRA_TANGENT_LINE*/
