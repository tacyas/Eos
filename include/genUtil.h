/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% genUtil.h ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : genUtil.h 
#%Z% Attention
#%Z%
*/
#ifndef GEN_UTIL_H 
#define GEN_UTIL_H
#include <string.h>
#include <math.h>

#ifndef I386MAC
#ifndef X86MAC64
#ifndef I386CYGWIN 
#ifndef ARM64MAC64
#include <values.h>
#else
#include <float.h>
#include <limits.h>
#endif
#else
#define MAXFLOAT 1e30
#endif
#else
#include <math.h>
#endif
#else
#define MAXFLOAT 1e30
#endif 

/* constant begin */
#define GEN_UTIL_MAX_STRING_LENGTH  (1024)
#ifdef GLOBAL_DECLARATION
int __verbose__;
#else
extern int __verbose__;
#endif
/* constant end */

/* prototype begin */
#define SQR(x)    ((x)*(x))
#define SQRT(x)   ((x)>0?sqrt(x):0)
#define CUBIC(x)  ((x)*(x)*(x))
#define QUAD(x)   ((x)*(x)*(x)*(x))
#ifndef MAX
#define MAX(x,y) ((x)>(y)?(x):(y))
#endif
#ifndef MIN
#define MIN(x,y) ((x)<(y)?(x):(y))
#define MIN3(x,y,z) MIN( MIN(x,y), z)
#endif
/* prototype end */

/* constant begin */
#define PI M_PI
#define DEGREE  (180.0/PI)
#define RADIAN  (PI/180.0)
#define PERCENT (100.0)

/* constant end */

/* prototype begin */
#define NORMAL_PHASE(x)     ((x)>=(0)?(fmod((x),2*M_PI)):(fmod((x),2*M_PI)+2*M_PI))   /* 0 ~ 2M_PI */
#define MIN_NORMAL_PHASE(x)  MIN(NORMAL_PHASE(x), 2*M_PI-NORMAL_PHASE(x))             /* 0 ~ M_PI */
#define POSITIVE_MODE(x,y)  ((x)>=(0)?(     (x)%(y)    ):((y)==1?0:     (x)%(y)  +(y)))
#define POSITIVE_FMODE(x,y) ((x)>=(0)?(fmod((x),(y))   ):((y)==1?0:fmod((x),(y)) +(y)))

#define SSWITCH(x)  { char* __sswitch_tmp_=x; \
					if(0==strcmp(__sswitch_tmp_, "")) { \
						fprintf(stderr, "SSWITCH Error\n"); \
						exit(EXIT_FAILURE); \
					}
#define SCASE(x)    else if(0==strcmp(x,__sswitch_tmp_))
#define SDEFAULT    else
#define SBREAK      ;
#define SSWITCHEND  }
#define IsOdd(x)    ((x)%2==1?1:0)
#define IsEven(x)   ((x)%2==0?1:0)

#ifdef M68
#define BYTE4SET(x3,x2,x1,x0) ((((x0)<< 0)&0x000f) \
							  |(((x1)<< 8)&0x00f0) \
							  |(((x2)<<16)&0x0f00) \
							  |(((x3)<<24)&0xf000))
#define BYTE4GETBYTE(x,byte)  (((x)>>(byte*8))&0x000f) 
#else
#define BYTE4SET(x3,x2,x1,x0) ((((x3)<< 0)&0x000f) \
							  |(((x2)<< 8)&0x00f0) \
							  |(((x1)<<16)&0x0f00) \
							  |(((x0)<<24)&0xf000))
#define BYTE4GETBYTE(x,byte)  (((x)>>((3-byte)*8))&0x000f) 

/* prototype end */
#endif
#ifdef NOINLINE
#define inline
#endif

/* prototype begin */
/* Usage */
#define USAGEPRINT(x) fprintf(stderr,x);
#define USAGEPRINT1(x,x1) fprintf(stderr,x,x1);
#define USAGEPRINT2(x,x1,x2) fprintf(stderr,x,x1,x2);

/* General Log Format*/
#define LOGPRINT(fpt,ID,ID2,x) \
					fprintf(fpt, "%-6s %-15s",ID,ID2); \
					fprintf(fpt, x); \
					fprintf(fpt, "\n"); fflush(fpt); \
					fprintf(stdout, "%-6s %-15s",ID,ID2); \
					fprintf(stdout, x); \
					fprintf(stdout, "\n"); fflush(stdout); 
#define LOGPRINT1(fpt,ID,ID2,x,d1) 	\
					fprintf(fpt, "%-6s %-15s ",ID,ID2); \
					fprintf(fpt, x, d1); \
					fprintf(fpt, "\n"); fflush(fpt); \
					fprintf(stdout, "%-6s %-15s ",ID,ID2); \
					fprintf(stdout, x, d1); \
					fprintf(stdout, "\n"); fflush(stdout); 
#define LOGPRINT2(fpt,ID,ID2,x,d1,d2) \
					fprintf(fpt, "%-6s %-15s ",ID,ID2); \
					fprintf(fpt, x, d1,d2);	\
					fprintf(fpt, "\n"); fflush(fpt); \
					fprintf(stdout, "%-6s %-15s ",ID,ID2); \
					fprintf(stdout, x, d1,d2);	\
					fprintf(stdout, "\n"); fflush(stdout); 
#define LOGPRINT3(fpt,ID,ID2,x,d1,d2,d3) 	\
					fprintf(fpt, "%-6s %-15s ",ID,ID2); \
					fprintf(fpt, x, d1,d2,d3); \
					fprintf(fpt, "\n"); fflush(fpt); \
					fprintf(stdout, "%-6s %-15s ",ID,ID2); \
					fprintf(stdout, x, d1,d2,d3); \
					fprintf(stdout, "\n"); fflush(stdout); 
#define LOGPRINT4(fpt,ID,ID2,x,d1,d2,d3,d4) \
					fprintf(fpt, "%-6s %-15s ",ID,ID2); \
					fprintf(fpt, x, d1,d2,d3,d4); \
					fprintf(fpt, "\n"); fflush(fpt); \
					fprintf(stdout, "%-6s %-15s ",ID,ID2); \
					fprintf(stdout, x, d1,d2,d3,d4); \
					fprintf(stdout, "\n"); fflush(stdout); 
#define LOGPRINT5(fpt,ID,ID2,x,d1,d2,d3,d4,d5) \
					fprintf(fpt, "%-6s %-15s ",ID,ID2); \
					fprintf(fpt, x, d1,d2,d3,d4,d5);	\
					fprintf(fpt, "\n"); fflush(fpt); \
					fprintf(stdout, "%-6s %-15s ",ID,ID2); \
					fprintf(stdout, x, d1,d2,d3,d4,d5);	\
					fprintf(stdout, "\n"); fflush(stdout);
#define LOGPRINT6(fpt,ID,ID2,x,d1,d2,d3,d4,d5,d6) \
					fprintf(fpt, "%-6s %-15s ",ID,ID2); \
					fprintf(fpt, x, d1,d2,d3,d4,d5,d6);	\
					fprintf(fpt, "\n"); fflush(fpt);  \
					fprintf(stdout, "%-6s %-15s ",ID,ID2); \
					fprintf(stdout, x, d1,d2,d3,d4,d5,d6);	\
					fprintf(stdout, "\n"); fflush(stdout); 
#define LOGPRINT7(fpt,ID,ID2,x,d1,d2,d3,d4,d5,d6,d7) \
					fprintf(fpt, "%-6s %-15s ",ID,ID2); \
					fprintf(fpt, x, d1,d2,d3,d4,d5,d6,d7);	\
					fprintf(fpt, "\n"); fflush(fpt); \
					fprintf(stdout, "%-6s %-15s ",ID,ID2); \
					fprintf(stdout, x, d1,d2,d3,d4,d5,d6,d7);	\
					fprintf(stdout, "\n"); fflush(stdout); 
#define LOGPRINT8(fpt,ID,ID2,x,d1,d2,d3,d4,d5,d6,d7,d8) \
					fprintf(fpt, "%-6s %-15s ",ID,ID2); \
					fprintf(fpt, x, d1,d2,d3,d4,d5,d6,d7,d8);	\
					fprintf(fpt, "\n"); fflush(fpt); \
					fprintf(stdout, "%-6s %-15s ",ID,ID2); \
					fprintf(stdout, x, d1,d2,d3,d4,d5,d6,d7,d8);	\
					fprintf(stdout, "\n"); fflush(stdout); 
#define LOGPRINT9(fpt,ID,ID2,x,d1,d2,d3,d4,d5,d6,d7,d8,d9) \
					fprintf(fpt, "%-6s %-15s ",ID,ID2); \
					fprintf(fpt, x, d1,d2,d3,d4,d5,d6,d7,d8,d9);	\
					fprintf(fpt, "\n"); fflush(fpt); \
					fprintf(stdout, "%-6s %-15s ",ID,ID2); \
					fprintf(stdout, x, d1,d2,d3,d4,d5,d6,d7,d8,d9);	\
					fprintf(stdout, "\n"); fflush(stdout); 
#define LOGPRINT10(fpt,ID,ID2,x,d1,d2,d3,d4,d5,d6,d7,d8,d9,d10) \
					fprintf(fpt, "%-6s %-15s ",ID,ID2); \
					fprintf(fpt, x, d1,d2,d3,d4,d5,d6,d7,d8,d9,d10);	\
					fprintf(fpt, "\n"); fflush(fpt); \
					fprintf(stdout, "%-6s %-15s ",ID,ID2); \
					fprintf(stdout, x, d1,d2,d3,d4,d5,d6,d7,d8,d9,d10);	\
					fprintf(stdout, "\n"); fflush(stdout); 
#define LOGPRINT11(fpt,ID,ID2,x,d1,d2,d3,d4,d5,d6,d7,d8,d9,d10,d11) \
					fprintf(fpt, "%-6s %-15s ",ID,ID2); \
					fprintf(fpt, x, d1,d2,d3,d4,d5,d6,d7,d8,d9,d10,d11);	\
					fprintf(fpt, "\n"); fflush(fpt); \
					fprintf(stdout, "%-6s %-15s ",ID,ID2); \
					fprintf(stdout, x, d1,d2,d3,d4,d5,d6,d7,d8,d9,d10,d11);	\
					fprintf(stdout, "\n"); fflush(stdout); 
#define LOGPRINT12(fpt,ID,ID2,x,d1,d2,d3,d4,d5,d6,d7,d8,d9,d10,d11,d12) \
					fprintf(fpt, "%-6s %-15s ",ID,ID2); \
					fprintf(fpt, x, d1,d2,d3,d4,d5,d6,d7,d8,d9,d10,d11,d12);	\
					fprintf(fpt, "\n"); fflush(fpt); \
					fprintf(stdout, "%-6s %-15s ",ID,ID2); \
					fprintf(stdout, x, d1,d2,d3,d4,d5,d6,d7,d8,d9,d10,d11,d12);	\
					fprintf(stdout, "\n"); fflush(stdout); 

#ifdef DEBUG
#define DEBUGPRINT(x) fprintf(stderr,x);fflush(stderr);
#define DEBUGPRINT1(x,x1) fprintf(stderr,x,x1);fflush(stderr);
#define DEBUGPRINT2(x,x1,x2) fprintf(stderr,x,x1,x2);fflush(stderr);
#define DEBUGPRINT3(x,x1,x2,x3) fprintf(stderr,x,x1,x2,x3);fflush(stderr);
#define DEBUGPRINT4(x,x1,x2,x3,x4) fprintf(stderr,x,x1,x2,x3,x4);fflush(stderr);
#define DEBUGPRINT5(x,x1,x2,x3,x4,x5) fprintf(stderr,x,x1,x2,x3,x4,x5);fflush(stderr);
#define DEBUGPRINT6(x,x1,x2,x3,x4,x5,x6) fprintf(stderr,x,x1,x2,x3,x4,x5,x6);fflush(stderr);
#define DEBUGPRINT7(x,x1,x2,x3,x4,x5,x6,x7) fprintf(stderr,x,x1,x2,x3,x4,x5,x6,x7);fflush(stderr)
#define DEBUGCOMMAND(x) (x);
#else
#define DEBUGPRINT(x)
#define DEBUGPRINT1(x,x1)
#define DEBUGPRINT2(x,x1,x2)
#define DEBUGPRINT3(x,x1,x2,x3)
#define DEBUGPRINT4(x,x1,x2,x3,x4)
#define DEBUGPRINT5(x,x1,x2,x3,x4,x5)
#define DEBUGPRINT6(x,x1,x2,x3,x4,x5,x6)
#define DEBUGPRINT7(x,x1,x2,x3,x4,x5,x6,x7)
#define DEBUGCOMMAND(x)
#endif

#ifdef DEBUG2
#define DEBUG2PRINT(x) fprintf(stderr,x);fflush(stderr);
#define DEBUG2PRINT1(x,x1) fprintf(stderr,x,x1);fflush(stderr);
#define DEBUG2PRINT2(x,x1,x2) fprintf(stderr,x,x1,x2);fflush(stderr);
#define DEBUG2PRINT3(x,x1,x2,x3) fprintf(stderr,x,x1,x2,x3);fflush(stderr);
#define DEBUG2PRINT4(x,x1,x2,x3,x4) fprintf(stderr,x,x1,x2,x3,x4);fflush(stderr);
#define DEBUG2PRINT5(x,x1,x2,x3,x4,x5) fprintf(stderr,x,x1,x2,x3,x4,x5);fflush(stderr);
#define DEBUG2PRINT6(x,x1,x2,x3,x4,x5,x6) fprintf(stderr,x,x1,x2,x3,x4,x5,x6);fflush(stderr);
#define DEBUG2PRINT7(x,x1,x2,x3,x4,x5,x6,x7) fprintf(stderr,x,x1,x2,x3,x4,x5,x6,x7);fflush(stderr)
#else
#define DEBUG2PRINT(x)
#define DEBUG2PRINT1(x,x1)
#define DEBUG2PRINT2(x,x1,x2)
#define DEBUG2PRINT3(x,x1,x2,x3)
#define DEBUG2PRINT4(x,x1,x2,x3,x4)
#define DEBUG2PRINT5(x,x1,x2,x3,x4,x5)
#define DEBUG2PRINT6(x,x1,x2,x3,x4,x5,x6)
#define DEBUG2PRINT7(x,x1,x2,x3,x4,x5,x6,x7)
#endif

#define ERRORPRINT(x) fprintf(stderr,x);
#define ERRORPRINT1(x,x1) fprintf(stderr,x,x1);
#define ERRORPRINT2(x,x1,x2) fprintf(stderr,x,x1,x2);
#define ERRORPRINT3(x,x1,x2,x3) fprintf(stderr,x,x1,x2,x3);
#define ERRORPRINT4(x,x1,x2,x3,x4) fprintf(stderr,x,x1,x2,x3,x4);
#define ERRORPRINT5(x,x1,x2,x3,x4,x5) fprintf(stderr,x,x1,x2,x3,x4,x5);
#define ERRORPRINT6(x,x1,x2,x3,x4,x5,x6) fprintf(stderr,x,x1,x2,x3,x4,x5,x6);
#define ERRORPRINT7(x,x1,x2,x3,x4,x5,x6,x7) fprintf(stderr,x,x1,x2,x3,x4,x5,x6,x7);

/* prototype end */

#endif /* GEN_UTIL_H */
