#ifndef EMDATA_H
#define EMDATA_H

#include <stdio.h>

/* constant begin */
#define EMDATA_VER0_HEADER_SIZE (256)
#define EMDATA_HEADER_SIZE (512)
/* constant end */

/* struct begin */
typedef char  emDataTypeChar;
typedef short emDataTypeIntegerShort;
typedef int   emDataTypeInteger;
typedef float emDataTypeFloat;

typedef struct emDataHeaderCont {
	/* 1st 256 byte                                        :256 */
	emDataTypeIntegerShort type1;				/* 000-001 :  2 */	
	emDataTypeIntegerShort type2;			    /* 002-003 :  2 */	
	emDataTypeInteger      Nx;				    /* 004-007 :  4 */
	emDataTypeInteger      Ny;					/* 010-013 :  4 */
	emDataTypeInteger      Nz;					/* 014-017 :  4 */
	emDataTypeChar         Comment[96];		    /* 020-137 : 96 */
	emDataTypeFloat        unknown[36];		    /* 140-377 :144 */
	/* 2nd 256 byte                                         256*/
	emDataTypeChar         ExtendedCode[4]; 	/* 400-403 :  4 : wwww */
	emDataTypeFloat        kV; 		            /* 404-407 :  4 */
	emDataTypeFloat        Cs; 		            /* 410-413 :  4 */
	emDataTypeFloat        UnknownFloat413; 	/* 413-417 :  4 : 0    */
	emDataTypeFloat        Magnification;       /* 420-423 :  4 */ 
	emDataTypeFloat        PostMagnification;   /* 424-427 :  4 */
	emDataTypeFloat        Cc;                  /* 430-433 :  4 */
	emDataTypeFloat        Defocus;             /* 433-437 :  4 */
	emDataTypeFloat        UnknownFloat440[8];  /* 440-477 : 32 */
	emDataTypeFloat        UnknownFloat500[5];  /* 500-523 : 20 */  
	emDataTypeFloat        ccdSize;             /* 524-527 :  4 */  
	emDataTypeFloat        offsetX;             /* 530-533 :  4 */  
	emDataTypeFloat        offsetY;             /* 534-537 :  4 */  
	emDataTypeFloat        pixelSize;           /* 540-543 :  4 */ 
	emDataTypeFloat        binning;             /* 543-547 :  4 */ 
	emDataTypeFloat        readOutSpeed;        /* 550-553 :  4 */ 
	emDataTypeFloat        gain;                /* 554-557 :  4 */ 
	emDataTypeFloat        sensitivity;         /* 560-563 :  4 */ 
	emDataTypeFloat        time;                /* 564-567 :  4 */ 
	emDataTypeFloat        flatField;           /* 570-573 :  4 */ 
	emDataTypeFloat        UnknownFloat574;     /* 574-577 :  4 */ 
	emDataTypeFloat        average;             /* 600-603 :  4 */ 
	emDataTypeFloat        unknown604;          /* 604-607 :  4 */ 
	emDataTypeFloat        unknown610;          /* 610-613 :  4 : 0 */ 
	emDataTypeFloat        unknown613;          /* 614-617 :  4 : 0 */ 
	emDataTypeFloat        unknown620;          /* 620-623 :  4 : 1e4*/ 
	emDataTypeFloat        unknown623;          /* 624-627 :  4 : 7e6*/ 
	emDataTypeFloat        min;                 /* 630-633 :  4 */ 
	emDataTypeFloat        max;                 /* 634-637 :  4 */ 
	emDataTypeFloat        StatisticQuality;    /* 640-643 :  4 */
	emDataTypeFloat        UnknownFloat644[23]; /* 644-777 :   */ 
} emDataHeaderCont;

typedef union emDataHeader {
	char  All[512]; 
	float Float[128];
	int   Int[128];
	emDataHeaderCont Cont;
} emDataHeader;

typedef struct emData {
	emDataHeader Header;
	int          version;
	unsigned char*          Image;
	emDataTypeIntegerShort* ShortImage;  
} emData; 

/* struct end */

/* prototpye begin */
extern void emDataHeaderRead(emData* em, FILE* fpt, char* message, int mode); 
extern void emDataFileRead(emData* em, FILE* fpt, char* message, int mode); 
extern void emDataHeaderPrint(emData* em, FILE* fpt, char* message, int mode); 
/* prototype end */

#endif /* EMDATA_H */

