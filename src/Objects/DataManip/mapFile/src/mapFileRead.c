/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% mapFileRead ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : mapFileRead 
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%mapFileRead ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include "Memory.h"
#include "../inc/mapFile.h"

void
mapFileRead(FILE* fpt, mapFile* map, int mode)
{
	unsigned char record[8*8*8]; 
	unsigned char uctmp;
	int qx,  qy,  qz;
	int qnx, qny, qnz;

	fseek(fpt, 0L, SEEK_SET);
	fread(&(map->Header), sizeof(mapFileHeader), 1, fpt); 
#ifdef II
#endif
	map->Image = (unsigned char*)memoryAllocate(sizeof(unsigned char)*map->Header.N.x*map->Header.N.y*map->Header.N.z, "mapFileRead");
	for(qz=0; qz<qnz; qz++) {
	}
}
