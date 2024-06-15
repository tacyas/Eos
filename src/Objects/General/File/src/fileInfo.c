#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "File.h"
#include "eosString.h"

static long __getLineNumber(FILE* file, char* e);

long
fileLineNumberGet(File* file, char* e)
{
	return __getLineNumber(file->fpt, e);
}

long
fileLineNumberGet2(FILE * fpt, char* e)
{
	return __getLineNumber(fpt, e);
}

long
__getLineNumber(FILE* fpt, char* e)
{
	char s[FILE_MAX_STRING_LENGTH];
    char* etmp;
    long  count, flag, position;

    count = 0;
    position = ftell(fpt);
    fseek(fpt, 0L, SEEK_SET);
    while(NULL!=__getStringData(s, "", fpt, stderr, 3)) {
		if('\0'==*e) {
			count++;
		} else {
        	flag = 0;
            etmp = e;
            while(*etmp!='\0') { /* Search */
                if(*etmp==s[0]) {
                    flag = 1;
                    break;
                }
                etmp++;
            }
            if(0==flag) {
				count++;
			}
        }
    }
    fseek(fpt, position, SEEK_SET);
    return count;    	    
}
