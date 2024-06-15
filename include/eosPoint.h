#ifndef EOS_POINT_H
#define EOS_POINT_H

#include <stdio.h>
#include "Matrix3D.h"
#include "Vector.h"

/* constant begin */


/* constant end */

/* struct begin */

typedef double eosPointParaTypeReal;
typedef struct eosPointCoord {
	floatVector coord;
	eosPointParaTypeReal sigma;  
	floatVector sig;
} eosPointCoord;

typedef struct eosPointList {
	eosPointCoord p;
	struct eosPointList* next;
	struct eosPointList* prev;
} eosPointList ;

typedef struct eosPoint {
	eosPointList* top;  
	eosPointList* current;  
	eosPointList* bottom;  
} eosPoint;

/* struct end */

#ifdef __cplusplus
extern "C" {
#endif

/* prototype begin */

extern void eosPointFileFormatUsage(FILE* fpt);
extern void eosPointRead(FILE* fpt, eosPoint* p, int mode); 

extern void eosPointWrite(FILE* fpt, eosPoint* p, int mode); 

extern void eosPointInit(eosPoint* p, eosPointCoord* pc);
extern eosPointList* eosPointTop(eosPoint* p);
extern eosPointList* eosPointBottom(eosPoint* p);
extern eosPointList* eosPointNext(eosPoint* p);
extern eosPointList* eosPointPrev(eosPoint* p);
extern eosPointList* eosPointAppend(eosPoint* p, eosPointCoord* pc, int mode);
extern void eosPointCoordInit(eosPointCoord* pc, int mode);
extern void eosPointCoordSet(eosPointCoord* p, eosPointParaTypeReal x, eosPointParaTypeReal y, eosPointParaTypeReal z);
extern void eosPointCoordSigSet(eosPointCoord* p, eosPointParaTypeReal sigx, eosPointParaTypeReal sigy, eosPointParaTypeReal sigz);

extern void eosPointRotate(eosPoint* p, Matrix3D mat);
extern void eosPointRotate2(eosPoint* out, eosPoint* in, Matrix3D mat);

extern void eosPointProject(eosPoint* p, int index); // index　0: x-projection, 1: y-projection, 2: z-projection
extern void eosPointProject2(eosPoint* out, eosPoint* in, int index); 

extern void eosPointCopy(eosPoint* out, eosPoint* in);

/* prototype end */

#ifdef __cplusplus
};
#endif


#endif  /* EOS_POINT_H */ 