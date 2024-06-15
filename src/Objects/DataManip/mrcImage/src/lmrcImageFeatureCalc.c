/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% lmrcImageFeatureCalc ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : lmrcImageFeatureCalc 
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%lmrcImageFeatureCalc ver%I%; Date:%D% %Z%";

#define DEBUG
#include "genUtil.h"
#include "Memory.h"
#include "./lmrcImageFeatureCalc.h"

static const int _SEARCH_DIRECTION=2;

void
lmrcImageFeaturePrint(FILE* fpt, lmrcImageFeatureList* linfo, int mode)
{
	int i;
	fprintf(fpt, "%6s %10s %10s %10s %12s %6s %6s %6s", "id", "gcx", "gcy", "gcz", "area", "startx", "starty", "startz");
	if(linfo->each[0].flagPerimeter) {
		fprintf(fpt, " %10s", "perimeter");
	}
	if(linfo->each[0].flagSurfaceArea) {
		fprintf(fpt, " %10s", "surfArea");
	}
	if(!linfo->each[0].flagCircularity) {
		lmrcImageCircularityCalc(linfo, 0);
	}
	if(linfo->each[0].flagCircularity) {
		fprintf(fpt, " %12s", "circularity");
	}
	if(!linfo->each[0].flagComplexity) {
		lmrcImageComplexityCalc(linfo, 0);
	}
	if(linfo->each[0].flagComplexity) {
		fprintf(fpt, " %12s", "complexity");
	}
	if(!linfo->each[0].flagRadius) {
		lmrcImageRadiusCalc(linfo, 0);
	}
	if(linfo->each[0].flagRadius) {
		fprintf(fpt, " %12s", "radius");
	}
	if(linfo->each[0].flagSumDensity) {
		fprintf(fpt, " %12s", "sumDensity");
	}
	fprintf(fpt, "\n");
	for(i=0; i<=linfo->Number; i++) {
		fprintf(fpt, "%06d %10.4f %10.4f %10.4f %12.4f %6d %6d %6d", 
			linfo->each[i].label,
			linfo->each[i].gravityCenter.x,
			linfo->each[i].gravityCenter.y,
			linfo->each[i].gravityCenter.z,
			linfo->each[i].area,
			linfo->each[i].bottomLeft.x,
			linfo->each[i].bottomLeft.y,
			linfo->each[i].bottomLeft.z);
		if(linfo->each[i].flagPerimeter) {
			fprintf(fpt, " %10.4f", linfo->each[i].perimeter);
		}
		if(linfo->each[i].flagSurfaceArea) {
			fprintf(fpt, " %10.4f", linfo->each[i].surfaceArea);
		}
		if(linfo->each[i].flagCircularity) {
			fprintf(fpt, " %12.4f", linfo->each[i].circularity);
		}
		if(linfo->each[i].flagComplexity) {
			fprintf(fpt, " %12.4f", linfo->each[i].complexity);
		}
		if(linfo->each[i].flagRadius) {
			fprintf(fpt, " %12.4f", linfo->each[i].radius);
		}
		if(linfo->each[i].flagSumDensity) {
			fprintf(fpt, " %12.4f", linfo->each[i].sumDensity);
		}
		fprintf(fpt, "\n");
	}
}

void
lmrcImageCircularityCalc(lmrcImageFeatureList* linfo, int mode)
{
	int i;

	if(linfo->each[0].flagPerimeter) {
		for(i=0; i<=linfo->Number; i++) {
			if(0<linfo->each[i].perimeter) {
				linfo->each[i].circularity=4*M_PI*linfo->each[i].area/SQR(linfo->each[i].perimeter);
			} else {
				linfo->each[i].circularity=1e4;
			}
			linfo->each[i].flagCircularity=1;
		}
	} else if(linfo->each[0].flagSurfaceArea) {
		for(i=0; i<=linfo->Number; i++) {
			if(0<linfo->each[i].surfaceArea) {
				linfo->each[i].circularity=36*M_PI*SQR(linfo->each[i].area)/CUBIC(linfo->each[i].surfaceArea);
			} else {
				linfo->each[i].circularity=1e4;
			}
			linfo->each[i].flagCircularity=1;
		}
	} else {
		fprintf(stderr, "Cannot calculate circularity because of no perimeter/surfaceArea\n");
		for(i=0; i<=linfo->Number; i++) {
			linfo->each[i].flagCircularity=0;
		}
	}
}

void
lmrcImageComplexityCalc(lmrcImageFeatureList* linfo, int mode)
{
	int i;

	if(linfo->each[0].flagPerimeter) {
		for(i=0; i<=linfo->Number; i++) {
			if(0<linfo->each[i].perimeter) {
				linfo->each[i].complexity=SQR(linfo->each[i].perimeter)/linfo->each[i].area;
			} else {
				linfo->each[i].complexity=1e4;
			}
			linfo->each[i].flagComplexity=1;
		}
	} else if(linfo->each[0].flagSurfaceArea) {
		for(i=0; i<=linfo->Number; i++) {
			if(0<linfo->each[i].surfaceArea) {
				linfo->each[i].complexity=CUBIC(linfo->each[i].surfaceArea)/SQR(linfo->each[i].area);
			} else {
				linfo->each[i].complexity=1e4;
			}
			linfo->each[i].flagComplexity=1;
		}
	} else {
		fprintf(stderr, "Cannot calculate complexity because of no perimeter/surfaceArea\n");
		for(i=0; i<=linfo->Number; i++) {
			linfo->each[i].flagComplexity=0;
		}
	}
}

void
lmrcImageRadiusCalc(lmrcImageFeatureList* linfo, int mode)
{
	int i;

	if(linfo->each[0].flagPerimeter) {
		for(i=0; i<=linfo->Number; i++) {
			if(0<linfo->each[i].perimeter) {
				linfo->each[i].radius=sqrt(linfo->each[i].area/M_PI);
			} else {
				linfo->each[i].radius=1e4;
			}
			linfo->each[i].flagRadius=1;
		}
	} else if(linfo->each[0].flagSurfaceArea) {
		for(i=0; i<=linfo->Number; i++) {
			if(0<linfo->each[i].surfaceArea) {
				linfo->each[i].radius=pow(linfo->each[i].area/(4./3.*M_PI), 1.0/3.0);
			} else {
				linfo->each[i].radius=1e4;
			}
			linfo->each[i].flagRadius=1;
		}
	} else {
		fprintf(stderr, "Cannot calculate radius because of no perimeter/surfaceArea\n");
		for(i=0; i<=linfo->Number; i++) {
			linfo->each[i].flagRadius=0;
		}
	}
}

void
lmrcImageSumOfDensityCalc(lmrcImageFeatureList* linfo, mrcImage* in, mrcImage* label, mrcImage* dinsity, int mode)
{ 
  int x, y, z;

}


void
lmrcImageBasicFeatureCalc(mrcImage* gc, lmrcImageFeatureList* linfo, mrcImage* label, int mode)
{
	int x, y, z;
	int max, i;
	double data;
	double* sumx;
	double* sumy;
	double* sumz;
	int* count;
	int* blx;
	int* bly;
	int* blz;

	DEBUGPRINT("lmrcImageBasicFeatureCalc Start \n");
	if(linfo->flagNumber) {
		max = linfo->Number;
	} else {
		DEBUGPRINT("MAX Search\n");
		max = 0;
		for(z=0; z<label->HeaderN.z; z++) {
		for(y=0; y<label->HeaderN.y; y++) {
		for(x=0; x<label->HeaderN.x; x++) {
			mrcPixelDataGet(label, x, y, z, &data, mrcPixelRePart, mrcPixelHowNearest);
			if(max<data) {
				max=data;
			}
		}
		}
		}
		linfo->flagNumber++;
		linfo->Number = max;
		linfo->flagEachAllocation=0;
		DEBUGPRINT1("Max: %d\n", max);
	}
	if(!linfo->flagEachAllocation) {
		linfo->each = memoryAllocate(sizeof(lmrcImageFeatureEach)*(max+1), "lmrcImageFeatureCalc");	
		linfo->flagEachAllocation++;
	}
	gc->Header = label->Header;
	mrcInit(gc, NULL);
	
	sumx = memoryAllocate(sizeof(double)*(max+1), "in lmrcImageGravityCenter");
	sumy = memoryAllocate(sizeof(double)*(max+1), "in lmrcImageGravityCenter");
	sumz = memoryAllocate(sizeof(double)*(max+1), "in lmrcImageGravityCenter");
	count = memoryAllocate(sizeof(int)*(max+1), "in lmrcImageGravityCenter");
	blx = memoryAllocate(sizeof(int)*(max+1), "in lmrcImageGravityCenter");
	bly = memoryAllocate(sizeof(int)*(max+1), "in lmrcImageGravityCenter");
	blz = memoryAllocate(sizeof(int)*(max+1), "in lmrcImageGravityCenter");


	for(i=0; i<=max; i++) {
		blx[i] = -1;
		bly[i] = -1;
		blz[i] = -1;
	}

	DEBUGPRINT("BL Calc.");
	for(z=0; z<label->HeaderN.z; z++) {
	for(y=0; y<label->HeaderN.y; y++) {
	for(x=0; x<label->HeaderN.x; x++) {
		mrcPixelDataGet(label, x, y, z, &data, mrcPixelRePart, mrcPixelHowNearest);
		sumx[(int)(data+0.5)]+=x;
		sumy[(int)(data+0.5)]+=y;
		sumz[(int)(data+0.5)]+=z;
		count[(int)(data+0.5)]++;

		// Bottom Left Position: Perimeter Start Point 
		if(blx[(int)(data+0.5)]<0) {
			blx[(int)(data+0.5)] = x;
			bly[(int)(data+0.5)] = y;
			blz[(int)(data+0.5)] = z;
		}
	}
	}
	}

	DEBUGPRINT("GC Calc\n");
	for(i=0; i<=max; i++) {
		if(0<count[i]) {
			linfo->each[i].gravityCenter.x = sumx[i]/count[i]; 	
			linfo->each[i].gravityCenter.y = sumy[i]/count[i]; 	
			linfo->each[i].gravityCenter.z = sumz[i]/count[i]; 	
			linfo->each[i].label = i;
			linfo->each[i].area  = count[i];
			linfo->each[i].bottomLeft.x = blx[i];
			linfo->each[i].bottomLeft.y = bly[i];
			linfo->each[i].bottomLeft.z = blz[i];
			mrcPixelDataSet(gc, linfo->each[i].gravityCenter.x, 
								linfo->each[i].gravityCenter.y,
								linfo->each[i].gravityCenter.z, i, mrcPixelRePart);
		} else {
			fprintf(stderr, "Something Wrong zero area: %d\n", i);
		}
	}
}

void
lmrcImagePerimeterCalcUsage(FILE* fpt)
{
	fprintf(fpt, ">> mode\n ");
	fprintf(fpt, "  0: 8-neighbor, chainCode absolute\n ");
	fprintf(fpt, "  1: 4-neighbor, chainCode absolute\n ");
	fprintf(fpt, "  2: 8-neighbor, chainCode relative\n ");
	fprintf(fpt, "  3: 4-neighbor, chainCode relative\n ");
}



void
lmrcImagePerimeterCalc(mrcImage* out, mrcImage* in, lmrcImagePerimeterCalcInfo* linfo, int mode)
{
	int x, y, z;
	int x1, y1, z1;
	int flag, flagIn, chainCode, chainCodeStart, startChainCode, previousChainCode, flagStart, absChainCode;
	double data0;
	double data1;
	double data2;
	double data3;
	mrcImage* area;
	mrcImage* label;
	mrcImage* chain;
	double L, dL, labelID, chainID;
	mrcImageParaTypeRealCoord ori, next;
  int errorFlag = 0;

	DEBUGPRINT1("lmrcImagePerimeterCalc Start mode : %d\n", mode);
	out->Header = in->Header; 
	chain = linfo->ChainCode = memoryAllocate(sizeof(mrcImage), "in lmrcImagePerimeterCalc");
	chain->Header = in->Header;
	mrcInit(out, NULL);
	mrcInit(chain, NULL);

	if(linfo->flagArea) {
		area  = linfo->Area;	
		label = linfo->Label;	
	} else {
		linfo->flagArea = 1;
		label = linfo->Label = memoryAllocate(sizeof(mrcImage), "in lmrcImagePerimeterCalc");
		area  = linfo->Area  = memoryAllocate(sizeof(mrcImage), "in lmrcImagePerimeterCalc");
		lmrcImageCalcArea(area, label, in, linfo->Neighbor, 0);
	}
	lmrcImageLabelingOrder(label, 1);

	for(y=0; y<in->HeaderN.y; y++) {	
	for(x=0; x<in->HeaderN.x; x++) {	
		mrcPixelDataSet(out,    x, y, 0, -1, mrcPixelRePart);
		mrcPixelDataSet(chain,  x, y, 0, -2, mrcPixelRePart);
	}
	}
	for(y=0; y<in->HeaderN.y; y++) {	
	for(x=0; x<in->HeaderN.x; x++) {	
		DEBUGPRINT2("Loop: %d %d\n", x, y);
		mrcPixelDataGet(area, x, y, 0, &data0, mrcPixelRePart, mrcPixelHowNearest);
		mrcPixelDataGet(chain, x, y, 0, &chainID, mrcPixelRePart, mrcPixelHowNearest);
    mrcPixelDataGet(label, x, y, 0, &labelID, mrcPixelRePart, mrcPixelHowNearest);
    if(0<labelID && -2==chainID) {
		if(1<data0) {  // in Area
      if(((int)labelID/10)*10 == labelID) {
        fprintf(stderr, "%f/%f\n", labelID, label->HeaderAMax);
      }
			switch(mode) { // Edge or Not
				case 0: 
				case 2: // 8-neighbor 
					flag = lmrcImageIsEdge(in, x, y, 0, 8, 0);
					break;
				case 1: //
				case 3: // 4-neighbor
					flag = lmrcImageIsEdge(in, x, y, 0, 4, 0);
					break;
				default:
					fprintf(stderr, "Not supported mode\n");
					flag = 0;
					break;
			}
			if(flag) { // Edge
				mrcPixelDataGet(chain,  x, y, 0, &chainID, mrcPixelRePart, mrcPixelHowNearest);
				if(0<=chainID) { // Already Calc 
					// Skip;
				} else {      // First Calc
					flag = 1;
					chainCodeStart = 0; // First Search from right because bottom left is the origin and first scan direction is x-axis whereas the next is y
					ori.x = x;
					ori.y = y;
					ori.z = 0;
					lmrcImageChainCodeSearch(&startChainCode, &next, &dL, in, ori, chainCodeStart, mode);
					switch(mode) {
						case 0:
						case 1: {
							break;
						}
						case 2:
						case 3: { // If relative, startChainCode must be absolute.
							startChainCode = (startChainCode + chainCodeStart)%8;
							break;
						}
						default: {
							fprintf(stderr, "Not supported mode : %d\n", mode);
							break;
						}
					}
					flagStart = 1;	
					L = 0;				
					while(flag) { // Loop
						flagIn = lmrcImageChainCodeSearch(&chainCode, &next, &dL, in, ori, chainCodeStart, mode);
						if(flagIn<0) {  // No Edge, i.e., Single Point
							//DEBUGPRINT2("Single Points: %f %f\n", ori.x, ori.y);
							L = 0;
							mrcPixelDataSet(chain, x, y, 0, -1, mrcPixelRePart); // No chainCode 
							mrcPixelDataSet(out,   x, y, 0,  0, mrcPixelRePart); // Length 
							flag = 0; // End
              errorFlag = -1;
						} else {        // If Edge
							switch(mode) {
								case 0:
								case 1: { // Absolute
									absChainCode = chainCode;
									break;
								}
								case 2:
								case 3: { // Relative
									absChainCode = (chainCode + chainCodeStart)%8;
									chainCode    = (chainCode-_SEARCH_DIRECTION + 8)%8;
									break;
								}
								default: {
									fprintf(stderr, "Not supported mode : %d\n", mode);
									break;
								}
							}

							if(ori.x==x && ori.y == y && absChainCode == startChainCode) {  // Start or End
                // start position (x,y), ori is a current position, the same direction   
								if(flagStart) { // If Start point, 
									//DEBUGPRINT4("Start Points: %f %f %d %d\n", ori.x, ori.y, chainCode, absChainCode);
									flagStart = 0;
								} else {        // If End point,
									//DEBUGPRINT4("End Points:   %f %f %d %d\n", ori.x, ori.y, chainCode, absChainCode);
                  errorFlag = 1;
									flag = 0; 
								}
								mrcPixelDataSet(chain, x, y, 0, chainCode, mrcPixelRePart); // Chain Code Set 
							} else { // Connection
								// On the way, 
								//DEBUGPRINT6("On the way Points: %f %f chain %d start %d %d chain %d\n", ori.x, ori.y, chainCode, x, y, startChainCode);
								//DEBUGPRINT5("Next Points:       %f %f L: %f abs: %d <- %d\n", next.x, next.y, L, absChainCode, chainCode);
								mrcPixelDataGet(chain, ori.x, ori.y, 0, &chainID, mrcPixelRePart, mrcPixelHowNearest);
                if(0<=chainID) { // Allready traced, looped perimeters  
                  flag = 0;
                  errorFlag = -1;
                } else {
								  mrcPixelDataSet(chain, ori.x, ori.y, 0, chainCode, mrcPixelRePart);
								  mrcPixelDataSet(out,   ori.x, ori.y, 0, -1,        mrcPixelRePart);
                }
							}
							L+=dL;
							mrcPixelDataSet(out, x, y, 0, errorFlag*L, mrcPixelRePart); 
						}
						ori = next;
						chainCodeStart = (absChainCode-_SEARCH_DIRECTION+8)%8; // Next search
					}
				}
			} else { // Inside
				mrcPixelDataSet(out,   x, y, 0, -1, mrcPixelRePart);
				mrcPixelDataSet(chain, x, y, 0, -1, mrcPixelRePart);
			}
		} else if(1==data0) {  // Single Point
			mrcPixelDataSet(out,   x, y, 0,  0, mrcPixelRePart);
			mrcPixelDataSet(chain, x, y, 0, -1, mrcPixelRePart);
		} else {               // No
			mrcPixelDataSet(out,   x, y, 0, -1, mrcPixelRePart);
			mrcPixelDataSet(chain, x, y, 0, -1, mrcPixelRePart);
		}
    }
	}
	}
}

int
lmrcImageChainCodeSearch(int* chain, mrcImageParaTypeRealCoord* next, double* pdL, mrcImage* in, mrcImageParaTypeRealCoord ori, int chainCodeStart, int mode)
{
	int flagIn;
	int chainCode;
	double data;
	mrcImageParaTypeReal x, y, z;	
	mrcImageParaTypeReal x1, y1, z1;	
	double dL;
	static double r2 = 1.414213562373095048801688724209698078569671875376948073176679;
	x = ori.x;
	y = ori.y;
	
	flagIn = -1;
	for(chainCode=(chainCodeStart-0+8)%8; chainCode<chainCodeStart+8 && flagIn<0; chainCode++) {
		switch(mode) {
			case 0:   // 8-neighbor 
			case 2: { // 8-neighbor 
				switch(chainCode%8) {
					case 0: { // right 
						x1 = x+1; y1 = y; dL = 1;
						break;
					} 
					case 1: { // right up
						x1 = x+1; y1 = y+1; dL = r2;
						break;
					} 
					case 2: { // up 
						x1 = x;   y1 = y+1; dL = 1;
						break;
					} 
					case 3: { // left up
						x1 = x-1; y1 = y+1; dL = r2;
						break;
					} 
					case 4: { // left
						x1 = x-1; y1 = y; dL = 1;
						break;
					} 
					case 5: { // left down 
						x1 = x-1; y1 = y-1; dL = r2; 
						break;
					} 
					case 6: { // down 
						x1 = x;   y1 = y-1; dL = 1;
						break;
					} 
					case 7: { // right down 
						x1 = x+1; y1 = y-1; dL = r2;
						break;
					} 
					default: {
						break;
					}
				}
				if(lmrcImageIsEdge(in, x1, y1, 0.0, 8, 0)) {	
					flagIn = 0;	
				}
				break;
			} 
		case 1:   // 4-neighbor
		case 3: { // 4-neighbor
				switch(chainCode%8) {
					case 0: { // right 
						x1 = x+1; y1 = y; dL = 1;
						break;
					} 
					case 2: { // up 
						x1 = x;   y1 = y+1; dL = 1;
						break;
					} 
					case 4: { // left
						x1 = x-1; y1 = y; dL = 1;
						break;
					} 
					case 6: { // down 
						x1 = x;   y1 = y-1; dL = 1;
						break;
					} 
					default: {
						break;
					}
				}
				switch(chainCode%8) {
					case 0:
					case 2:
					case 4:
					case 6: {
						if(lmrcImageIsEdge(in, x1, y1, 0.0, 4, 0)) {	
							flagIn = 0;	
						}
						break;
					}
					default: {
						break;
					}	
				}
				break;
			}
		} 
	}
	next->x = x1;
	next->y = y1;
	next->z = 0;
	*pdL = dL;

	if(flagIn<0) {
		*chain = -1;
	} else {
		switch(mode) {
			case 0: // Absolute chain ID
			case 1: {
				*chain = (chainCode-1 + 8)%8;
				break;
			}
			case 2: // Relative chain ID
			case 3: {
				*chain = (chainCode-1 - chainCodeStart + 16)%8;
				break;
			}
			default: {
				*chain = -1;
				fprintf(stderr, "Not supported mode in lmrcImageChainCodeSearch: %d\n", mode);
				break;
			}
		}
	}
	//DEBUGPRINT3("ChainCode: %d abs %d start %d\n", *chain, chainCode-1, chainCodeStart)
	return *chain;
}
