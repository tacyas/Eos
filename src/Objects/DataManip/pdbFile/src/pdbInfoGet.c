/*
# pdbInfoGet.c  1.2
# The latest update : 03/20/98 at 14:26:30
#
#@(#) pdbInfoGet ver 1.2
#@(#) Created by 
#@(#)
#@(#) Usage : pdbInfoGet 
#@(#) Attention
#@(#)
*/

static char __sccs_id[] = "@(#)pdbInfoGet ver1.1; Date:97/01/23 @(#)";

#include "genUtil.h"
#include "./pdbInfoGet.h"

void
pdbInfoGet(pdbFile* pdb, pdbInfoData* info, long mode)
{
    double sx, sy, sz;
    double cx, cy, cz;
    float x, y, z;
    double distance, d, dx, dy, dz;
    double distancex, distancey, distancez;
    long n;
    pdbInfoCenterMode centermode;

    pdbFileTop(pdb);
    n = 0; 
    sx = sy = sz = 0;
    centermode = pdbInfoCenterModeCa; 
    while(1) {
    if(pdbFileIsCA(pdb)) {
	pdbFileCoordGet(pdb, &x, &y, &z);   
	n++;
	sx += x;
	sy += y;
	sz += z;
	DEBUGPRINT1("%d\n", n);
      }
      if(pdbFileEnd(pdb)) {
	break;
      } else {
	pdbFileNext(pdb);
      }
    }
    if (!n){
      fprintf(stderr,"There are no Ca Atoms!  Center mode is set to CenterModeAll.\n");
      centermode = pdbInfoCenterModeAll;
      pdbFileTop(pdb);
      n = 0; 
      sx = sy = sz = 0;
      while(1) {
	if(pdbFileIsAtom(pdb)) {
	  pdbFileCoordGet(pdb, &x, &y, &z);   
	  n++;
	  sx += x;
	  sy += y;
	  sz += z;
	  DEBUGPRINT1("%d\n", n);
	}
	if(pdbFileEnd(pdb)) {
	  break;
	} else {
	  pdbFileNext(pdb);
	}
      }
    }
    cx = sx/n;
    cy = sy/n;
    cz = sz/n;
     

    distance = 0.0; n = 0;
    distancex = 0.0;
    distancey = 0.0;
    distancez = 0.0;
    pdbFileTop(pdb);
    while(1) {
        if(pdbFileIsAtom(pdb)) {
            n++;
            DEBUGPRINT1("%d\n", n);
            pdbFileCoordGet(pdb, &x, &y, &z);   
            d = sqrt(SQR(x-cx)+SQR(y-cy)+SQR(z-cz));
			dx = fabs(x-cx);
			dy = fabs(y-cy);
			dz = fabs(z-cz);
            if(d > distance) {
                distance = d;
            }
			if(dx> distancex) {
				distancex = dx;
			}
			if(dy> distancey) {
				distancey = dy;
			}
			if(dz> distancez) {
				distancez = dz;
			}
        }
    	if(pdbFileEnd(pdb)) {
			break;
		} else {
        	pdbFileNext(pdb);
		}
    } 

	info->cx = cx;
	info->cy = cy;
	info->cz = cz;
	info->distance = distance;
	info->distancex = distancex;
	info->distancey = distancey;
	info->distancez = distancez;
	info->centermode = centermode;
}
