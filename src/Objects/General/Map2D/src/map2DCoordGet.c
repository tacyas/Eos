/*
# map2DCoordGet.c  1.1
# The latest update : 01/23/97 at 11:04:07
#
#@(#) map2DCoordGet ver 1.1
#@(#) Created by 
#@(#)
#@(#) Usage : map2DCoordGet 
#@(#) Attention
#@(#)
*/
static char __sccs_id[] = "@(#)map2DCoordGet ver1.1; Date:97/01/23 @(#)";
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../inc/Map2D.h"

/*
*/
void
map2DParallelInfo(Map2DParaTypeInteger* n, 
				  Map2DParaTypeReal*    d,
				  Map2DParaTypeReal     latitude,
				  Map2DParaTypeInteger  nparallel,
				  long mode)
{
	switch(mode) {
		case 0: {
			*d = 1.0; 
			*n = nparallel;
			break;
		}
		case 1: {
		    if(0.0!=cos(latitude)) {
				*d = 1.0/fabs(cos((double)latitude));
			} else {
				*d = nparallel; 
			}
			/* Number of images to draw */
			*n = (int)(((double)nparallel)/(*d)+0.5);
			if(*n==0) {
				*n = 1;
			}
			/* Delta of equator angle of images to draw */
			*d = ((double)nparallel)/((double)(*n));
			break;
		}
		default: {
			fprintf(stderr, "Not supported Mode in map2DCoordGet: %ld\n", mode);
			break;
		}
	}
}
/*
*/
void
map2DCoordGet(Map2DParaTypeReal* x,   Map2DParaTypeReal* y,
			  Map2DParaTypeReal rotx, Map2DParaTypeReal roty,
		      long nx, long ny, long mode)
{
	Map2DParaTypeReal tmpx, tmpy, tmpdx;
	long tmpnx;

	map2DParallelInfo(&tmpnx, &tmpdx, roty, ny, mode);
	tmpx = rotx/(2*M_PI)*nx;
	tmpy = roty/(2*M_PI)*ny;
	switch(mode) {
		case 0: {
			if(nx==1 && ny==1) {
				*x = 0.0;
				*y = 0.0;
			} else {
				*x = nx/2.0 + tmpx/tmpdx;
				*y = ny/2.0 + tmpy/tmpdx;
			}
			break;
		}
		case 1: {
			if(-nx/2.0 <= tmpx && tmpx <= nx/2.0)  {
				*x = ((double)nx)/2.0 - 0.5 + tmpx/tmpdx;
			} else if(0<tmpx) {
				*x = ((double)nx)/2.0 - 0.5 + (tmpx - nx)/tmpdx;
			} else {
				*x = ((double)nx)/2.0 - 0.5 + (tmpx + nx)/tmpdx;
			}
			*y = ny/2.0 - 0.5 + tmpy;
			break;
		}
		default: {
			fprintf(stderr, "Not supported Mode in map2DCoordGet: %ld\n", mode);
			break;
		}
	}
}
