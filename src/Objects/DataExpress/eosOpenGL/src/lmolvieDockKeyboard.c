/*
# lmolvieKeyboardParallel : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : lmolvieKeyboardParallel 
# Attention
#   $Loccker$
#  	$State$ 
#
*/
/* $Log$ */
#include <stdio.h>
#include <stdlib.h>
#include "./lmolvie.h"

void
lmolvieDockKeyboard(unsigned char pushkey,
		int x,
		int y)	/*multi mode*/
{
	int multiProteinChange;
	int ProteinNumber;

	multiProteinChange=get_multiProteinChange();
	ProteinNumber=getProteinNumber();

	if(pushkey!='w' && pushkey!='e'){
		fprintf(stdout, "%c:", pushkey);
	}

	switch(pushkey) {
		case 'q': {
			fprintf(stdout, "quit.\n");
			exit(EXIT_FAILURE);
			break;
		}

		case 'i': {
			if(ProteinNumber==1){
				loadPDB1();
			}
/*			else if(ProteinNumber==2){
				loadPDB2();
			}
			else if(ProteinNumber==3){
				loadPDB3();
			}
			else{
				loadPDB4();
			}*/
			break;
		}

		case '0': {
			displayModeSet(multiProteinChange, 0);
			fprintf(stdout, "(DisplayModeChange) NoneAtom mode\n");
			break;
		}
		case '1': {
			displayModeSet(multiProteinChange, 1);
			fprintf(stdout, "(DisplayModeChange) Atom mode\n");
			break;
		}
		case '5': {
			displayModeSet(multiProteinChange, 2);
			fprintf(stdout, "(DisplayModeChange) CStickNumber mode\n");
			break;
		}
		case '2': {
			displayModeSet(multiProteinChange, 3);
			fprintf(stdout, "(DisplayModeChange) Number mode\n");
			break;
		}
		case '3': {
			displayModeSet(multiProteinChange, 4);
			fprintf(stdout, "(DisplayModeChange) AminoAcid mode\n");
			break;
		}
		case '4': {
			displayModeSet(multiProteinChange, 5);
			fprintf(stdout, "(DisplayModeChange) Temperature mode\n");
			break;
		}
		case '7': {
			displayModeSet(multiProteinChange, 6);
			fprintf(stdout, "(DisplayModeChange) CStickTemperature mode\n");
			break;
		}
		case '6': {
			displayModeSet(multiProteinChange, 7);
			fprintf(stdout, "(DisplayModeChange) CStickAminoAcid mode\n");
			break;
		}
		case 'c': {
			set_multiProteinChange();
			fprintf(stdout, "Protein Change.\n");
			break;
		}

/*		case 'v': {
			voice();
			fprintf(stdout, "voice!\n");
			break;
		}*/

		case 'r': {
			resetMyCamera();
			fprintf(stdout, "camera reset.\n");
			break;
		}

		case 'w': {
			moveMyCamera(1.0);
			break;
		}
		case 'e': {
			moveMyCamera(-1.0);
			break;
		}
		case 'F': {
			setCameraCentreTagD(-1);
			break;
		}

		default: {
			fprintf(stdout, "\n");
			break;
		}
	}	

}
