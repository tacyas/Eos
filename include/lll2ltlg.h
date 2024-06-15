#ifndef LLL2LTLG_H
#define LLL2LTLG_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#undef DEBUG
#include "genUtil.h"
#include "Memory.h"
#include "eosString.h"
#include "File.h"
#include "llData.h"
#include "ltlgData.h"

/* struct begin */
typedef struct lll2ltlgInfo {
	/* Input File */
		long flagIn;
   		char* In;
   		FILE* fptIn; 

	/* Output File */
    	char* Out;
    	FILE* fptOut;

	/* Config File */
   		long flagconfigFile;
   		char* configFile;
    	FILE* fptconfigFile;

	/* Title for ltlg */
   		long flagTitle;
   		char* Title;

	/* The Number of Layer Line */
    	long flagllMax;
    	long llMax;

	/* The inverse of deltaR: unit Angstrom */
    	long flagdelRInv;
    	float delRInv;

	/* The inverse of Rmax:  unix Angstrom */
    	long flagRMaxInv;
    	float RMaxInv;

	/* Delta r : unit Angstrom */
    	long flagdelr;
    	float delr;

	/* rmax : unit Angstrom */
    	long flagrMax;
    	float rMax;

 	    long mode;
} lll2ltlgInfo;
/* struct end */

/* prototype begin */
extern void ll2ltlgConfigFileRead(lll2ltlgInfo* linfo, FILE* fpt);


/* Fourier Bessel Transform */
extern void lll2ltlg(ltlgData* out, llData* in, lll2ltlgInfo* linfo);
extern void emBessel(ltlgData* ltlg, llData* ll);
extern ltlgDataParaTypeReal Bessel0(ltlgDataParaTypeReal x0);
extern ltlgDataParaTypeReal Bessel1(ltlgDataParaTypeReal x0);
/* prototype end */

#endif /* LLL2LTLG_H */
