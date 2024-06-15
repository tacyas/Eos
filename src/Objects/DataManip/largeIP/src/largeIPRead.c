/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% largeIPRead ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : largeIPRead 
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%largeIPRead ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include "../inc/largeIP.h"
#undef DEBUG
void
largeIPRead(largeIP* ip, FILE* fpt, largeIPSubImageInfo* info, long mode)
{
	largeIPHeaderRead(ip, fpt, mode);
	largeIPInit(ip, info, mode);
	largeIPImageRead(ip, fpt, info, mode);
}

void
largeIPImageRead(largeIP* ip, FILE* fpt, largeIPSubImageInfo* info, long mode)
{
	largeIPImageType* tmp;
	largeIPImageType* buffer;
	largeIPParaTypeInteger i, w, h, x, y, xx, yy, sx, sy, stepx, stepy;
	unsigned char u, l;

	if(NULL==info) {
		w = LARGE_IP_IMAGE_WIDTH;
		h = LARGE_IP_IMAGE_HEIGHT;		
		sx = 0;
		sy = 0;
		stepx = 1;
		stepy = 1;
	} else {
		w = info->length.x;
		h = info->length.y;
		sx = info->start.x;
		sy = info->start.y;
		stepx = info->step.x;
		stepy = info->step.y;
	}
	#ifdef DEBUG
	fprintf(stderr, "start(%d, %d) step(%d, %d) size(%d, %d)\n", sx, sy, stepx, stepy, w, h);
	#endif
	if(NULL==(buffer=(largeIPImageType*)malloc(sizeof(largeIPImageType)*LARGE_IP_IMAGE_WIDTH))) {
		fprintf(stderr, "Memory Not Allocated in largeIPImageRead\n");
		exit(EXIT_FAILURE);
	}

	for(y=sy, yy=0; yy<h; y+=stepy, yy++) {
		fseek(fpt, sizeof(largeIPHeader)+y*sizeof(largeIPImageType)*LARGE_IP_IMAGE_WIDTH, SEEK_SET);
		fread(buffer, sizeof(largeIPImageType), LARGE_IP_IMAGE_WIDTH, fpt);
		for(x=sx, xx=0; xx<w; x+=stepx, xx++) {
			ip->Image[xx][yy] = buffer[x];
		}
	}
#ifdef  M68
#else
	tmp = ip->Image[0];
	for(i=0; i<w*h; i++) {
		u = *((unsigned char*)(tmp+i));
		l = *((unsigned char*)(tmp+i) + 1);
		*(tmp+i) = u + 256*l;
	}
#endif
	free(buffer);
}

void
largeIPInit(largeIP* ip, largeIPSubImageInfo* info, long mode)
{
	unsigned short* tmp;
	unsigned char   u;
	unsigned char   l;
	largeIPParaTypeInteger i, w, h;
	
	if(NULL==info) {
		w = LARGE_IP_IMAGE_WIDTH;		
		h = LARGE_IP_IMAGE_HEIGHT;		
	} else {
		w = info->length.x;
		h = info->length.y;
	}
	#ifdef DEBUG
	fprintf(stderr, "size(%d, %d)\n", w, h);
	#endif 
	if(NULL==(tmp=(unsigned short*)malloc(sizeof(unsigned short)*w*h))) {
		fprintf(stderr, "Memory Not Allocated in largeIPRead (All)\n");
		exit(EXIT_FAILURE);
	}
	if(NULL==(ip->Image=(unsigned short**)malloc(sizeof(unsigned short*)*w))) {
		fprintf(stderr, "Memory Not Allocated in largeIPRead (All)\n");
		exit(EXIT_FAILURE);
	}
		
	for(i=0; i<w; i++) {
		ip->Image[i] = tmp + i*h;
	}
}

void
largeIPFree(largeIP* ip)
{
	free(ip->Image[0]);
}

void
largeIPHeaderRead(largeIP* ip, FILE* fpt, long mode)
{
	fseek(fpt, 0L, SEEK_SET);
	fread(&(ip->Header), sizeof(largeIPHeader), 1, fpt);
}
