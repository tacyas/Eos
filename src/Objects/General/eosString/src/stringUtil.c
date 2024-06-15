/*
# stringUtil.c  1.2
# The latest update : 09/07/99 at 12:21:14
#
#@(#) stringUtil ver 1.2
#@(#) Created by 
#@(#)
#@(#) Usage : stringUtil 
#@(#) Attention
#@(#)
*/
static char __sccs_id[] = "@(#)stringUtil ver1.2; Date:99/09/07 @(#)";

#include "Memory.h"
#include "../inc/eosString.h"

String  
stringDefinedValueGet(String s, String key, String seperator) 
{
    int i;
    String sub;
    String keytmp;
    String value;

    i=1;
    while(NULL!=(sub = stringGetNthWord(s, i, "\n"))) {
        keytmp = stringGetNthWord(sub, 1, seperator);     
        if(key!=NULL) {
            if(stringIsSame(key, keytmp, stringLength(key))) {
                value = stringGetNthWord(sub, 2, seperator); 
                return value;
            }
        }
    }
    return NULL;
}

long
stringLength(String s) 
{
	String stmp;

	stmp=s;
	while('\0' !=*stmp) {
		stmp++;
	}
	return (stmp-s);
}

long
stringCopy(String dst, String src, long n)
{
	String stmp;
	String dtmp;

	stmp = src;
	dtmp = dst;
	while('\0' !=*stmp && stmp-src<n) {
		*dtmp = *stmp;
		stmp++;
		dtmp++;
	}
	*dtmp = '\0';
	return (stmp-src);
}

String
stringDuplicate(String src)
{
	String dst;
	long n;
	long n2;

	n   = stringLength(src);
	dst = memoryAllocate(sizeof(char)*(n+1), "in stringDuplicate");
	n2  = stringCopy(dst, src, n);
	if(n2!=n) {
		fprintf(stderr, "not same in stringDuplicate\n");
	}
	return dst;
}

