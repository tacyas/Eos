/*
# stringGetFromFile.c  1.1
# The latest update : 6/20/96 at 00:07:19
#
#@(#) stringGetFromFile ver 1.1
#@(#) Created by 
#@(#)
#@(#) Usage : stringGetFromFile 
#@(#) Attention
#@(#)
*/
static char __sccs_id[] = "@(#)stringGetFromFile ver1.1; Date:96/06/20 @(#)";
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "../inc/eosString.h"

#define OUT_WORD (0)
#define IN_WORD  (1)

/*
	mode:
		mode&0x01 : 0 = quary,   1 = No quary
		mode&0x02 : 0 = message, 1 = no message
*/

char*
stringGetFromFile(char* s, char* message, FILE* fptIn, FILE* fptOut, long mode)
{
	return __getStringData(s, message, fptIn, fptOut, mode);	
}

char*
stringGetFromFileWithSkippingComment(char* s, char* message, FILE* fptIn, FILE* fptOut, long mode)
{
	String w;
	while(NULL!=__getStringData(s, message, fptIn, fptOut, mode)) {
		w = stringGetNthWord(s, 1, STRING_WORD_SEPARATOR);
		if(STRING_COMMENT_LINE_ID!=w[0]) {
			free(w);
			return s;
		} else {
			free(w);
		}
	}
	return NULL;
}

char*
__getStringData(char* s, char* message, FILE* fptIn, FILE* fptOut, long mode)
{
    char ans[256];
    char* tmp;
    int   slen;

    *s = '\0';
    while(strlen(s)==0) {
        if(NULL!=message) {
            if(*message!='\0' && (mode&0x02)!=0x02) {
    	       	fprintf(fptOut, "%s :", message);
            }
        }
        if(NULL==fgets(s, STRING_MAX_LENGTH, fptIn)) {
			return NULL;
        }
        slen = strlen(s);
        s[slen-1] = '\0';
        switch(mode&0x01) {
            case 0: { 
                fprintf(fptOut, "%s is %s. OK? (y/n)", message, s);
                fgets(ans, 256, fptIn);
                tmp = ans;
                while(*tmp==' ') {
                    tmp++;
                } 
                if(*tmp=='n' || *tmp=='N') {
                    s[0] = '\0';
                } else {
                    return s;
                }
                break;
            }
            case 1: {
                return s;
            }
            default: {
                fprintf(stderr, "Not Supported Mode %d in getStringData\n",  (int)mode);
                exit(EXIT_FAILURE);
                break;
            }
        }
    }
    return s;
}
