#ifndef RANDOM_H
#define RANDOM_H
#include <stdio.h>	
#include <stdlib.h>	
#include <math.h>	
#include <time.h>	

/* struct begin */
typedef double randomParaTypeReal;
/* struct end */

/* prototype begin */
#define random()  ((1.0/(RAND_MAX + 1.0))*rand())

extern randomParaTypeReal randomUniformGet(randomParaTypeReal min, randomParaTypeReal max, long mode);
extern randomParaTypeReal randomNormalGet(long mode);
extern void srandomByTime();

/* prototype end */

#endif /* RANDOM_H */
