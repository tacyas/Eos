#ifndef MAP_2D_H
#define MAP_2D_H
/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% Map2D ver %I%
#%Z% Created by tacyas
#%Z%
*/

/* struct begin */
typedef float Map2DParaTypeReal;
typedef long  Map2DParaTypeInteger;
/* struct end */


#ifdef __cplusplus 
extern "C" {
#endif

/* prototype begin */

extern void map2DParallelInfo(Map2DParaTypeInteger* n, 
				  Map2DParaTypeReal*    d,
				  Map2DParaTypeReal     latitude,
				  Map2DParaTypeInteger  nparallel,
				  long mode);

extern void map2DCoordGet(Map2DParaTypeReal* x,   Map2DParaTypeReal* y,
			  Map2DParaTypeReal rotx, Map2DParaTypeReal roty,
		      long nx, long ny, long mode);

/* prototype end */
#ifdef __cplusplus 
}
#endif
#endif /* MAP_2D_H */
