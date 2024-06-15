/*
# lastigmatismDetection : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : lastigmatismDetection 
# Attention
#   $Loccker$
#  	$State$ 
#
*/
/* $Log$ */
#include "genUtil.h"
#include<stdio.h>
#include<math.h>

#include "./lastigmatismDetection.h"

/*mode is start angle	0:-90~90
						1:  0~180*/
void
lastigmatismDetection(ctfInfo* ctf, lastigmatismDetectionInfo linfo, int mode) 
{
	int i;
	double averageDefocus = 0.0;
	double a = 0.0;
	double b = 0.0;
	double astigmatismAamplitude, astigmatismAngle;
	
	for(i=0; i < linfo.sectionSize ; i++){
		fprintf(stderr, "sectionDefocus %d% lf\n", i+1, linfo.defocus[i]);
		averageDefocus += linfo.defocus[i];
		a += linfo.defocus[i] * sin( 2.0 * (i+1.0-0.5) * M_PI/linfo.sectionSize);
		b += linfo.defocus[i] * cos( 2.0 * (i+1.0-0.5) * M_PI/linfo.sectionSize);
	}
	averageDefocus /= linfo.sectionSize;
	astigmatismAamplitude = 4 * sqrt(a*a+b*b); // 
	astigmatismAngle      = (atan2(b,a) - M_PI/2)/2 ;
	ctf->defocus = averageDefocus;
	ctf->defocus0axis =  astigmatismAngle; 
	ctf->defocus2D[0] = astigmatismAamplitude;
	ctf->defocus2D[1] = astigmatismAamplitude;

	/*if(0 == mode){
		AstigmatismAngle += 270;
	}*/
	fprintf(stderr,"AverageDefocus%lf AstigmatismAamplitude: %lf AstigmatismAngle: %lf\n",
				averageDefocus,
				astigmatismAamplitude,
				astigmatismAngle*DEGREE);
}
