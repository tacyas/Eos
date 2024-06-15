#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#include "largeIP.h"
#define GLOBAL_DECLARATION
#include "../inc/config.h"

void
main(int argc, char* argv[]) 
{
	long status;
	largeIPInfoInfo info;
	largeIP ip;
	largeIPSubImageInfo sub;
	int x, y, xx, yy;
	double max, min;

	init0(&info);
    argCheck(&info, argc, argv);
	init1(&info);

	sub.start.x = info.startx; sub.start.y = info.starty;
	sub.step.x = info.stepx;   sub.step.y = info.stepy;
	sub.length.x = info.width; sub.length.y = info.height;
	largeIPRead(&ip, info.fptIn, &sub, 0);

	max = min = ip.Image[0][0];
	for(xx=0, x=info.startx; xx<info.width; xx++, x+=info.stepx) {
		for(yy=0, y=info.starty; yy<info.height; yy++, y+=info.stepy) {
			if(max<ip.Image[xx][yy]) {
				max = ip.Image[xx][yy];
			}
			if(min>ip.Image[xx][yy]) {
				min = ip.Image[xx][yy];
			}

		}
	}
	fprintf(info.fptOut, "Max: %g, Min: %g\n", max, min);
}


void
additionalUsage()
{
}
