/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% mapFile.h ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : mapFile.h 
#%Z% Attention
#%Z%
*/

/* struct begin */

typedef struct mapFileShortCoord {
	short x;
	short y;
	short z;
} mapShortCoord;

typedef struct mapFileHeader {
	mapShortCoord Start;
	mapShortCoord N;
	mapShortCoord M;
	mapShortCoord Length;
	mapShortCoord Angle;
	short prod;
	short plus;
	short i1;
	short i2;
	short dummy[256-19];
} mapFileHeader;

typedef struct mapFile {
	mapFileHeader Header;
	unsigned char* Image;
} mapFile;

/* struct end */
