#ifndef DSN6_H
#define DSN6_H
#include <stdio.h>

typedef short Dsn6IntegerType;
typedef unsigned char Dsn6ImageType;

#define Dsn6Header Header.DSN6HeaderCont

typedef struct Dsn6Coord {
	Dsn6IntegerType x;
	Dsn6IntegerType y;
	Dsn6IntegerType z;
} Dsn6Coord;

typedef struct Dsn6HeaderContent {
	Dsn6Coord Start;
	Dsn6Coord Extent;
	Dsn6Coord SamplingRate;
	Dsn6IntegerType	ACellEdge;
	Dsn6IntegerType	BCellEdge;
	Dsn6IntegerType	CCellEdge;
	Dsn6IntegerType	CosAlpha;
	Dsn6IntegerType	CosBeta;
	Dsn6IntegerType	CosGamma;
	Dsn6IntegerType	DensScaling;
	Dsn6IntegerType	DensOffset;
	Dsn6IntegerType	CellConstantScalingFactor;
	Dsn6IntegerType	Weight;
	Dsn6IntegerType dummy[256-19];
} Dsn6HeaderContent;

typedef union DSN6Header {
	char               byte[512];
	Dsn6IntegerType    data[256];
	Dsn6HeaderContent  DSN6HeaderCont;
} DSN6Header;

typedef struct Dsn6 {
	DSN6Header     Header;
	Dsn6ImageType* Image;	
	float*	       FloatImage;	
} Dsn6;

extern void dsn6Init(Dsn6* map, int mode);
extern void dsn6ImageAllocate(Dsn6* map, int mode);

extern void dsn6FileWrite(Dsn6* map, FILE* fpt, int mode);
#endif /* DSN6_H */
