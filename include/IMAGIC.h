#ifndef IMAGIC_H
#define IMAGIC_H

typedef char  ImagicParaTypeChar;
typedef int   ImagicParaTypeInteger;
typedef float ImagicParaTypeReal;
#define IMAGIC_HEADER  (1024)
#define IMAGIC_HEADER4 (256)

typedef struct _ImagicHeader {
	ImagicParaTypeInteger IMN; 		//   1, Image Location Number (1, 2, 3 ...)
	ImagicParaTypeInteger IFOL; 	//   2, Number of Images Following (0, 1, ...) only of importance in the first location
	ImagicParaTypeInteger IERROR; 	//   3, Error code for this image during IMAGIC-5 run
	ImagicParaTypeInteger NHFR; 	//   4, Number of Header Records per image (=1 current) 
	ImagicParaTypeInteger NMONTH; 	//   5, creation month
	ImagicParaTypeInteger NDAY; 	//   6, creation day 
	ImagicParaTypeInteger NYEAR; 	//   7, creation year 
	ImagicParaTypeInteger NHOUR; 	//   8, creation hour 
	ImagicParaTypeInteger NMINUT; 	//   9, creation minute 
	ImagicParaTypeInteger NSEC; 	//  10, creation second 
	ImagicParaTypeInteger NPIX2; 	//  11, image size in BYTES as seen from the program IDAT1(13)*IDAT1(89)
	ImagicParaTypeInteger NPIXEL; 	//  12, total number of image elements
	ImagicParaTypeInteger IXLP; 	//  13, number of lines per image (for 1D data IYLP1=1) : x-size 
	ImagicParaTypeInteger IYLP; 	//  14, number of pixels per line                       : y-size
	ImagicParaTypeChar    TYPE[4]; 	//  15, 4 characters determining the image type: 
									//  		REAL(float),INTG(short),PACK(byte),COMP(2float),RECO(complex with 0 in imaginary)
	ImagicParaTypeInteger IXOLD; 	//	16, top left X co-ordinate before CUT-IMAGE boxing
	ImagicParaTypeInteger IYOLD; 	//	17, top left Y co-ordinate before CUT-IMAGE boxing
	ImagicParaTypeReal    AVDENS; 	//	18, average density in image 
	ImagicParaTypeReal    SIGMA; 	//	19, standard deviation of densities
	ImagicParaTypeReal    VARIAN; 	//	20, variance of densities
	ImagicParaTypeReal    OLDAVD; 	//	21, old average density of this image
	ImagicParaTypeReal    DENSMAX; 	//	22, highest density in image
	ImagicParaTypeReal    DENSMIN; 	//	23, minimal density in image
	ImagicParaTypeInteger COMPLEX; 	//	24, label indicating that data are always complex 
	ImagicParaTypeReal    CXLENGTH; //	25, cell dimension in Angstr. MRC(12) 
	ImagicParaTypeReal    CYLENGTH; //	26, cell dimension in Angstr. MRC(11)
	ImagicParaTypeReal    CZLENGTH; //	27, cell dimension in Angstr. MRC(13)
	ImagicParaTypeReal    CALPHA;   //	28, cell angle alpha. MRC(14)
	ImagicParaTypeReal    CBETA;    //	29, cell angle beta.  MRC(15)
	ImagicParaTypeChar    NAME[80]; //	30-49, coded NAME/TITLE of the image  
	ImagicParaTypeReal    CGAMMA;   //	50, cell angle gamma.  MRC(16)
	ImagicParaTypeInteger MAPC; 	//	51, axis corresponding to columns. MRC(17) (1,2,3 for X, Y, Z)
	ImagicParaTypeInteger MAPR; 	//	52, axis corresponding to rows.    MRC(18) (1,2,3 for X, Y, Z)  
	ImagicParaTypeInteger MAPS; 	//	53, axis corresponding to section. MRC(19) (1,2,3 for X, Y, Z)  
	ImagicParaTypeInteger ISPG; 	//	54, space group MRC(23)

	ImagicParaTypeInteger NXSTART; 	//	55, number of 1st column in map  MRC(6)
	ImagicParaTypeInteger NYSTART; 	//	56, number of 1st row in map     MRC(5)
	ImagicParaTypeInteger NZSTART; 	//	57, number of 1st section in map MRC(7)

	ImagicParaTypeInteger NXINTV; 	//	58, number of intervals along X MRC(9)
	ImagicParaTypeInteger NYINTV; 	//	59, number of intervals along Y MRC(8)
	ImagicParaTypeInteger NZINTV; 	//	60, number of intervals along Z MRC(10)




} ImagicHeader;

typedef union ImagicHeader {
	unsigned char All[IMAGIC_HEADER];
	IDAT1	IDAT1[IMAGIC_HEADER4];	
	DAT1	DAT1[IMAGIC_HEADER4];	
	ImagicHeader Header;
} ImagicHeader;

typedef struct Imagic {
	
} IMAGIC;

#endif
