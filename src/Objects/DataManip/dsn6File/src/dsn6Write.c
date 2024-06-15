#include <stdio.h>
#include <stdlib.h>
#include "../inc/dsn6File.h"

void
dsn6FileWrite(Dsn6* map, FILE* fpt, int mode)
{
	size_t n;
	int i;
	char ctmp;
	int qnx, qny, qnz;
	int qx, qy, qz;
	int qx2, qy2, qz2;
	int ix, iy, iz;
	int itmp;
	unsigned char record[8*8*8];

	for(i=0; i<256; i++) {
		ctmp = map->Header.byte[2*i];	
		map->Header.byte[2*i] = map->Header.byte[2*i+1];	
		map->Header.byte[2*i+1] = ctmp;
	}
	fwrite(&map->Header, sizeof(DSN6Header), 1, fpt);
	for(i=0; i<256; i++) {
		ctmp = map->Header.byte[2*i];	
		map->Header.byte[2*i] = map->Header.byte[2*i+1];	
		map->Header.byte[2*i+1] = ctmp;
	}


	qnx = map->Dsn6Header.Extent.x/8; if(qnx*8!=map->Dsn6Header.Extent.x) { qnx += 1; }
	qny = map->Dsn6Header.Extent.y/8; if(qny*8!=map->Dsn6Header.Extent.y) { qny += 1; }
	qnz = map->Dsn6Header.Extent.z/8; if(qnz*8!=map->Dsn6Header.Extent.z) { qnz += 1; }

	n = qnx*8*qny*8*qnz*8;
	map->Image = (unsigned char*)malloc(sizeof(unsigned char)*n);
	if(NULL==map->Image) {
		fprintf(stderr, "in dsn6FileWrite");
		exit(EXIT_FAILURE);
	}

	for(ix=0; ix<map->Dsn6Header.Extent.x; ix++){
	for(iy=0; iy<map->Dsn6Header.Extent.y; iy++){
	for(iz=0; iz<map->Dsn6Header.Extent.z; iz++){
		itmp = map->FloatImage[ix
					+iy*map->Dsn6Header.Extent.x
					+iz*map->Dsn6Header.Extent.x*map->Dsn6Header.Extent.y]
			*map->Dsn6Header.DensScaling/map->Dsn6Header.Weight 
			+ map->Dsn6Header.DensOffset + 0.5;
		if(255<itmp) {
			itmp = 255;
		} else if(itmp<0) {
			itmp = 0;
		}
		map->Image[ix + iy*qnx*8 + iz*qnx*8*qny*8] = (unsigned char)itmp;
	}
	}
	}

	for(qz=0;qz<qnz;qz++) {
	for(qy=0;qy<qny;qy++) {
	for(qx=0;qx<qnx;qx++) {
		for(qz2=0; qz2<8; qz2++) {
		for(qy2=0; qy2<8; qy2++) {
		for(qx2=0; qx2<8; qx2+=2) {
			ix = qx*8 + qx2;
			iy = qy*8 + qy2;
			iz = qz*8 + qz2;
			record[qx2+1+qy2*8+qz2*8*8] = map->Image[ix   + iy*qnx*8 + iz*qnx*8*qny*8];
			record[qx2+  qy2*8+qz2*8*8] = map->Image[ix+1 + iy*qnx*8 + iz*qnx*8*qny*8];
		}
		}
		}
		fwrite(record, sizeof(unsigned char), 8*8*8, fpt);
	}
	}
	}
} 


