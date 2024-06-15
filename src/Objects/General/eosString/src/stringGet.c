/*
# stringGet.c  1.1
# The latest update : 6/20/96 at 00:07:18
#
#@(#) stringGet ver 1.1
#@(#) Created by 
#@(#)
#@(#) Usage : stringGet 
#@(#) Attention
#@(#)
*/
static char __sccs_id[] = "@(#)stringGet ver1.1; Date:96/06/20 @(#)";
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "../inc/eosString.h"
#include "Memory.h"

#define OUT_WORD (0)
#define IN_WORD  (1)

char* 
stringGetWordFromField(char* s, long init, long end)
{
	char* w;
	int n;
	int i;

	n = end - init + 1;
	w = (char*)memoryAllocate(sizeof(char)*(n+1), "in getWord");

	for(i=init; i<=end; i++) {
		w[i-init] = s[i-1];
	}
	w[n] = '\0';
	return w;
}

long
stringGetIntegerDataFromField(char* s, long init, long end)
{
	char* w;
	int i;
	w = stringGetWordFromField(s, init, end);
	i = atoi(w); 
	free(w);
	return i;
}

double
stringGetRealDataFromField(char* s, long init, long end)
{
	char* w;
	double f;
	w = stringGetWordFromField(s, init, end);
	f = atof(w); 
	free(w);
	return f;
}

char* 
stringGetNthWord0(char* s, long nth, char* e)
{
    char* word;
    char* stmp;
    char* first;
    char* last;
    long  present, previous, next, n, i, slen;
	extern long __inWordOrNot(char c, char* e);
        
    first = last = NULL;
    previous = present = OUT_WORD;
	n = 0;
    stmp = s;
    while(*stmp!='\0') {
        present = __inWordOrNot(*stmp, e);
        if(previous==OUT_WORD && present==IN_WORD) {
            first = stmp;
            n++;
        }
        if(n==nth) {
            break;
        }
        previous = present;
        stmp++;
    }
    while(*stmp!='\0') {
        next = __inWordOrNot(*(stmp+1), e);
        if(present==IN_WORD && next==OUT_WORD) {
            last = stmp+1;
            slen = last - first;
			word = (char*)memoryAllocate(sizeof(char)*(slen+1), "in getNthWord");
			for(i=0; i<slen; i++) {
                *(word+i) = *(first+i);
            }
            *(word+slen) = '\0';
            return word;
        }
        stmp++;
	}
    return NULL;
}

char* 
stringGetNthWord(char* s, long nth, char* e)
{
    char* stmp;
    stmp = stringGetNthWord0(s, nth, e); 
    if(stmp==NULL) {
        fprintf(stderr, "%dth word not found in %s: exception %s\n", (int)nth, s, e);
    }
    return stmp;
}

            
long
__inWordOrNot(char c, char* e)
{
    char* etmp;
    
    if('\0'==c) {
        return OUT_WORD;
    } else {
        etmp = e;
        while(*etmp!='\0') {
            if(*etmp==c) {
                return OUT_WORD;
            }
            etmp++;
        }
        return IN_WORD;
    }
}
            
double
stringGetNthRealData0(char* s, long nth, char *e)
{
    double data = 0.0;
    char* stmp;
    
    stmp = stringGetNthWord0(s, nth, e);
    if(stmp==NULL) {
        fprintf(stderr, "No data: return 0\n");
        return 0;
    } else {
        data = atof(stmp);
        free(stmp);
        return data;
    }
}

double
stringGetNthRealData(char* s, long nth, char *e)
{
    double data = 0.0;
    char* stmp;
    
    stmp = stringGetNthWord(s, nth, e);
    if(stmp==NULL) {
        fprintf(stderr, "No data: return 0\n");
        return 0;
    } else {
        data = atof(stmp);
        free(stmp);
        return data;
    }
}

long
stringGetNthIntegerData0(char* s, long nth, char* e)
{
    char* stmp;
    long  data;
    
    stmp = stringGetNthWord0(s, nth, e);
    if(stmp==NULL) {
        fprintf(stderr, "No data: return 0\n");
        return 0;
    } else {
        data = atoi(stmp);
        free(stmp);
        return data;
    }
}

long
stringGetNthIntegerData(char* s, long nth, char* e)
{
    char* stmp;
    long  data;
    
    stmp = stringGetNthWord(s, nth, e);
    if(stmp==NULL) {
        fprintf(stderr, "No data: return 0\n");
        return 0;
    } else {
        data = atoi(stmp);
        free(stmp);
        return data;
    }
}
