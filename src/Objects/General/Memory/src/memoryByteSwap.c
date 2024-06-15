/*
# memoryByteSwap.c  1.1
# The latest update : 01/23/97 at 11:02:43
#
#@(#) memoryByteSwap ver 1.1
#@(#) Created by 
#@(#)
#@(#) Usage : memoryByteSwap 
#@(#) Attention
#@(#)
*/
static char __sccs_id[] = "@(#)memoryByteSwap ver1.1; Date:97/01/23 @(#)";

#undef DEBUG
#include "genUtil.h"
#include <stdio.h>
#include "../inc/Memory.h"

Memory
memoryByteSwap(Memory ptr, size_t each, int howmany)
{
	char* tmp;
	char ctmp;
	int i;

	DEBUGPRINT2("%d %d in memoryByteSwap\n", each, howmany); 
	for(i=0; i<howmany; i++) {
		tmp = ptr + i*each;
		switch(each) {
			case 1: {
			 	break;
			}
			case 2: {
				ctmp = tmp[0];
				tmp[0] = tmp[1];
				tmp[1] = ctmp;
				break;	
			}
			case 4: {
				ctmp = tmp[0];
				tmp[0] = tmp[3];
				tmp[3] = ctmp;
				ctmp = tmp[1];
				tmp[1] = tmp[2];
				tmp[2] = ctmp;
				break;	
			}
			case 8: {
				ctmp = tmp[0];
				tmp[0] = tmp[each-1];
				tmp[each-1] = ctmp;
				ctmp = tmp[1];
				tmp[1] = tmp[each-2];
				tmp[each-2] = ctmp;
				ctmp = tmp[2];
				tmp[2] = tmp[each-3];
				tmp[each-3] = ctmp;
				ctmp = tmp[3];
				tmp[3] = tmp[each-4];
				tmp[each-4] = ctmp;
				break;
			}
			default: {
				fprintf(stderr, "not supported byte: %zu", each);
				exit(EXIT_FAILURE);
			}
		}
	}
	return ptr;
}
