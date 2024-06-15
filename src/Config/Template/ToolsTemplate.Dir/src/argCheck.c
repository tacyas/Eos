#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "../inc/config.h"

void
argCheck(THIS_PROGRAM\
Info* info, int argc, char* argv[])
{
    long i;
	char s[DefaultStringLength];
            
    for(i=1; i<argc; i++) {
        if(argv[i][OPTION_FLAG_POS]==OPTION_FLAG) {
            switch(argv[i][OPTION_POS]) {
                case 'i': {
					if(i+1<argc) {
						strncpy(info->inFileName, argv[i+1], FILENAME_LENGTH-1);
					} else {
						usage(argv[0]);
					}
					info->flagInFile++;
                    i++;
                    break;
                }
                case 'o': {
                    if(i+1<argc) {
						strncpy(info->outFileName, argv[i+1], FILENAME_LENGTH-1);
					} else {
						usage(argv[0]);
					}
					info->flagOutFile++;
                    i++;
                    break;
                }
                case 'l': {
					if(i+1<argc) {
                    	info->layer = atoi(argv[i+1]);
					} else {
						usage(argv[0]);
					}
                    i++;
                    break;
                }
                case 'm': {
					if(i+1<argc) {
                    	info->mode = atoi(argv[i+1]);
					} else {
						usage(argv[0]);
					}
                    i++;
                    break;
                }
                case 'h': {
                    usage(argv[0]);
                    break;
                }
                default: {
                    fprintf(stderr, "Not Supported Options: %s\n", argv[i]);
                    usage(argv[0]);
                }
            }
        }
    }
}

