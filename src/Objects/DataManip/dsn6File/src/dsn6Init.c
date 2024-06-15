#include <stdio.h>
#include <stdlib.h>
#include "../inc/dsn6File.h"

void
dsn6Init(Dsn6* map, int mode) 
{
	int i;
	for(i=0; i<256; i++) {
		map->Header.data[i] = 0;
	}
	map->Dsn6Header.CellConstantScalingFactor = 100;
	map->Dsn6Header.Weight   = 100;

	map->Dsn6Header.CosAlpha = 90*map->Dsn6Header.CellConstantScalingFactor;
	map->Dsn6Header.CosBeta  = 90*map->Dsn6Header.CellConstantScalingFactor;
	map->Dsn6Header.CosGamma = 90*map->Dsn6Header.CellConstantScalingFactor;
}

void
dsn6ImageAllocate(Dsn6* map, int mode)
{
	map->FloatImage = (float*)calloc(  map->Dsn6Header.Extent.x
					  *map->Dsn6Header.Extent.y 
					  *map->Dsn6Header.Extent.z
					 , sizeof(float));
	if(NULL==map->FloatImage) {
		fprintf(stderr, "dsn6ImageAllocate Not Allocate\n");
		exit(EXIT_FAILURE);
	}
}
