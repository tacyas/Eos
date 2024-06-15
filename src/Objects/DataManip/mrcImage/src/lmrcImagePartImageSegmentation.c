/*
# lmrcImagePartImageSegmentation : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : lmrcImagePartImageSegmentation 
# Attention
#   $Loccker$
#  	$State$ 
#
*/
/* $Log$ */
#include "Memory.h"
#include "../inc/mrcImage.h"


void
lmrcImagePartImageSegmentation(mrcImage* mrc, int L, int mode)
{


}

/*
double
lmrcImageDeterminationOfThresholdForBinarizationByOhtsuMethod(mrcImage* mrc, int L, int mode)
{
        double  Emax; 
	    double  E;
        int     kmax;
        double* hist ;
        int index;
        mrcImageInformation linfo;
        float x, y, z;
        double data;
        int k;
        double omega0, omega1;
        double sigma0, sigma1;
        double mean0, mean1, mean;
        int    count0, count1;
        int N;

        linfo.mode = meanOfAll;
        lmrcImageInformation(&linfo, mrc);
        mean = linfo.mean;
        hist = (double*)memoryAllocate(sizeof(double)*L, "in lmrcImageDetermination");

        N=mrc->HeaderN.x*mrc->HeaderN.y*mrc->HeaderN.z;

        for(index=0; index<L; index++) { 
                hist[index] = (linfo.max-linfo.min)*((double)index)/(double)L+linfo.min; 
                DEBUGPRINT2("hist %4d %15.6g\n", index, hist[index]);
        }

        Emax = 0; 
        DEBUGPRINT1("start E: %15.6g\n", Emax)
        kmax = 0;
        for(k=1; k<L; k++) {
                omega0 = omega1 = 0;
                mean0  = mean1  = 0;
                count0 = count1 = 0;
                for(x=0; x<mrc->HeaderN.x; x++) {
                for(y=0; y<mrc->HeaderN.y; y++) {
                for(z=0; z<mrc->HeaderN.z; z++) {
                        mrcPixelDataGet(mrc, x, y, z, &data, mrcPixelRePart, mrcPixelHowNearest);
                        if(data<hist[k]) {
                                omega0++;
                                mean0 += data;
                                count0++;       
                        } else {
                                omega1++;
                                mean1 += data;
                                count1++;
                        }
                }
                }
                }
                omega0 /= N;
                omega1 /= N;
                mean0  /= count0;
                mean1  /= count1;
																																				        
                E = omega0*SQR(mean0-mean) + omega1*SQR(mean1-mean); 
                DEBUGPRINT5("count below %6d above %6d hist %15.6g mean %15.6g %15.6g\n", count0, count1, hist[k], mean0, mean1);
                DEBUGPRINT2("E: k %4d E %15.6g \n", k, E);
                if(Emax<E)  {
                        DEBUGPRINT("MAXIMUM\n");
                        Emax = E;
                        kmax = k; 
                }
        }
        DEBUGPRINT3("minimum kmin %6d Emax %15.6g hist %15.6g\n", kmax, Emax, hist[kmax]);
        PartHist[i]=hist[kmax];
		if(Emax>a)
		 	 	PartEmax[i]=Emax;
		else
				PartEmax[i]=0;
        free(hist);
}
*/
