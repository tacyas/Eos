/* struct begin */

typedef struct ctfInfoZeroPoint {
	float RMax;      /* RMax */
	float dR;        /* delta R */
	int   N;         /* Zero Point Number */
	long mode;
} ctfInfoZeroPoint;

/* struct end */

/* prototype begin */

extern float ctfZeroPoint(ctfInfo* info, ctfInfoZeroPoint* infoZeroPoint, long mode);

/* prototype end */
