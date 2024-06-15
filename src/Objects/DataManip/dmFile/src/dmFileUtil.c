/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% dmFileUtil ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : dmFileUtil 
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%dmFileUtil ver%I%; Date:%D% %Z%";
#include <locale.h>
#include <wchar.h>
#include <stdlib.h>

#undef DEBUG

#include "genUtil.h"
#include "../inc/dmFile.h"

void 
dmFileValuePrint(FILE* fpt, void* value, dmFileTagDataType valueType, int n)
{
	int i;
	char format[100];
	int max;
	
	max = MIN(5, n);

	strncpy(format,  __dmFileTagDataTypeFormat[valueType], 99);  
	strcat(format, " ");

	DEBUGPRINT1("valueType: %x in dmFileValuePrint\n", valueType);
	switch(valueType) {
		case dmFileTagDataTypeInt2: {
			for(i=0; i<max; i++) {
				fprintf(fpt, format, ((dmFileInteger2*)value)[i]);
			}
			break;
		}
  		case dmFileTagDataTypeInt4: {
			for(i=0; i<max; i++) {
				fprintf(fpt, format, ((dmFileInteger4*)value)[i]);
			}
			break;
		}
		case dmFileTagDataTypeUInt2: {
			setlocale(LC_ALL, ".1200");
			for(i=0; i<n; i++) {
				fputwc(((dmFileInteger2*)value)[i], fpt);
				//fprintf(fpt, format, ((dmFileInteger2*)value)[i]);
			}
			break;
		}
		case dmFileTagDataTypeUInt4: {
			for(i=0; i<max; i++) {
				fprintf(fpt, format, ((dmFileInteger4*)value)[i]);
			}
			break;
		}
	 	case dmFileTagDataTypeReal4: {
			for(i=0; i<max; i++) {
				fprintf(fpt, format, ((float*)value)[i]);
			}
			break;
		}
		case dmFileTagDataTypeReal8: {
			for(i=0; i<max; i++) {
				fprintf(fpt, format, ((double*)value)[i]);
			}
			break;
		}
	   	case dmFileTagDataTypeBool1: {
			for(i=0; i<max; i++) {
				fprintf(fpt, format, ((char*)value)[i]);
			}
			break;
		}
		case dmFileTagDataTypeChar1: {
			for(i=0; i<max; i++) {
				fprintf(fpt, format, ((char*)value)[i]);
			}
			break;
		}
		case dmFileTagDataTypeInt1: {
			for(i=0; i<max; i++) {
				fprintf(fpt, format, ((char*)value)[i]);
			}
			break;
		}
		case dmFileTagDataTypeInt8: {
			for(i=0; i<max; i++) {
				fprintf(fpt, format, ((dmFileInteger8*)value)[i]);
			}
			break;
		}
		case dmFileTagDataTypeUInt8: {
			for(i=0; i<max; i++) {
				fprintf(fpt, format, ((dmFileInteger8*)value)[i]);
			}
			break;
		}
		case dmFileTagDataTypeString: {
			DEBUGPRINT("STRING^^^^");
			fprintf(fpt, "%s", (char*)value);
			break;
		}
		default: {
			fprintf(stderr, "Not supported valueType(hex): %x\n", valueType);
			exit(EXIT_FAILURE);
			break;
		}
	}
	fprintf(fpt, "\n");
}
