#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#include <float.h>                  
#define GLOBAL_DECLARATION

#include "../inc/config.h"
#define DEBUG
#include "genUtil.h"
#include "File.h"
#include "eosString.h"
#include "Memory.h"
#include "mrcImage.h"
#include "tiff.h"
#include "tiffio.h"

typedef struct ltiff2mrcInfo {
	long    flagSigned;
	long    flagOffset;
	double  Offset;
	long 	flagMax;
	double  Max;
	long 	flagMin;
	double  Min;
	long 	flagrealMaxBit;
	double  realMaxBit;
	long 	flagrealMax;
	double  realMax;
	long 	flagrealMin;
	double  realMin;
	long 	Inverse;
	long    flagTime;
	long    Time;
	long    flagfinalmrcMode;
	long    finalmrcMode;

	long    flagShrink;
	long    Shrink;

    int     nz;
    int     currentz;
} ltiff2mrcInfo;

extern void ltiff2mrc(mrcImage* mrc, TIFF* tiff, ltiff2mrcInfo* linfo, long mode);
extern void lsin2ltiff2mrc(ltiff2mrcInfo* linfo, char* filename, long mode);

int
main(int argc, char* argv[]) 
{
    mrcImage mrc;
	TIFF *tiff;
    tiff2mrcInfo info;
	ltiff2mrcInfo linfo;
    int dirnum;
    float lx, ly, lz;
    short unit;
    char s[1024];
    char strUnit[256];
    float unitAng;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	memoryClear(&(mrc), sizeof(mrc), 0);		
	memoryClear(&(linfo), sizeof(linfo), 0);		

	linfo.flagSigned = info.Signed;
	linfo.flagOffset = info.flagOffset;
	linfo.Offset     = info.Offset;

	linfo.flagShrink = info.flagShrink;
	linfo.Shrink     = info.Shrink;
	DEBUGPRINT2("Offset: %f flag %ld\n", linfo.Offset, linfo.flagOffset);

	if(info.flagsinFile) {
		lsin2ltiff2mrc(&linfo, info.sinFile, 0);
	}
	if(info.flagMode) {
		linfo.flagfinalmrcMode = info.flagMode;	
		linfo.finalmrcMode     = info.Mode;	
	}

	tiff = TIFFOpen(info.inFile, "r");

    if(info.dirnum < 0) {
        TIFFSetDirectory(tiff, 0);

        dirnum = 0;
        do {
            dirnum++;
        } while(TIFFReadDirectory(tiff));
        linfo.nz = dirnum;
        linfo.currentz = 0;
        DEBUGPRINT1("Directory Number: %d\n", dirnum);
        TIFFSetDirectory(tiff, 0);
    } else {
        dirnum = info.dirnum;
        linfo.nz = 1;
        linfo.currentz = 0;
    }

	if(tiff != NULL) {
        if(info.flagResolution) {
		    mrc.HeaderLength.x = mrc.HeaderLength.y = mrc.HeaderLength.z = info.Resolution;
        } else if(info.flagResolutionX) {
		    mrc.HeaderLength.x = info.ResolutionX;
            mrc.HeaderLength.y = info.ResolutionY;
            mrc.HeaderLength.z = info.ResolutionZ;
        } else {
            TIFFGetField(tiff, TIFFTAG_RESOLUTIONUNIT, &unit);
            TIFFGetField(tiff, TIFFTAG_XRESOLUTION, &lx); 
            TIFFGetField(tiff, TIFFTAG_YRESOLUTION, &ly);
            TIFFGetField(tiff, TIFFTAG_IMAGEDESCRIPTION, s);
            //lz = atof(stringGetDefinedValue(s, "spacing", "="));  

            switch(unit) {
                case RESUNIT_NONE: {
                    //strUnit = stringGetDefinedValue(s, "unit", "="));  
                    if(strUnit[0]!='\0') {
                        if(strncmp(strUnit,"micron",6)==0) {
                          unitAng= 1e4;  
                        } else {
                          unitAng= 1;  
                        }
                    } else {
                        unitAng= 1;
                    }
                    break;
                }
                case RESUNIT_INCH: {
                    unitAng = 25.4e7;
                    break;
                }
                case RESUNIT_CENTIMETER: {
                    unitAng = 1e8;
                    break;
                }
                default: {
                    unitAng = 1;
                    break;
                }
            }
            mrc.HeaderLength.x = unitAng/lx;
            mrc.HeaderLength.y = unitAng/ly;
            if(lz<=0) {
                mrc.HeaderLength.z = mrc.HeaderLength.x;
            } else {
                mrc.HeaderLength.z = lz*unitAng;
            }
        }
		linfo.Inverse = info.Inverse;
		if(info.flagtime) {
			linfo.Time    	= info.time;
			linfo.flagTime  = info.flagtime;
		}
		if(info.flagMax) {
			linfo.Max     = pow(2, info.Max) - 1;
			linfo.flagMax = info.flagMax;
		}
		if(info.flagMin) {
			linfo.Min     = pow(2, info.Min);
			linfo.flagMin = info.flagMin;
		}
		if(info.flagrealMaxBit) {
			linfo.realMaxBit     = pow(2, info.realMaxBit) - 1;
			linfo.flagrealMaxBit = info.flagrealMaxBit;
		}
		if(info.flagrealMax) {
			linfo.realMax     = info.realMax;
			linfo.flagrealMax = info.flagrealMax;
		}
		if(info.flagrealMin) {
			linfo.realMin     = info.realMin;
			linfo.flagrealMin = info.flagrealMin;
		}

        if(info.dirnum<0) {
            dirnum = 0;
            do {
		        if(!TIFFSetDirectory(tiff, dirnum))	 {
			        fprintf(stderr, "Cannot read the directory (%d) in tiff file(%s).\n", dirnum, info.inFile);
			        exit(EXIT_FAILURE);
		        }
		        ltiff2mrc(&mrc, tiff, &linfo, info.mode);
                dirnum++;
            } while(TIFFReadDirectory(tiff));
        } else {
		    if(!TIFFSetDirectory(tiff, dirnum))	 {
			    fprintf(stderr, "Cannot read the directory (%d) in tiff file(%s).\n", dirnum, info.inFile);
			    exit(EXIT_FAILURE);
		    }
		    ltiff2mrc(&mrc, tiff, &linfo, info.mode);
        }
	} else {
		fprintf(stderr, "Cannot open tiff file (%s).\n", info.inFile);
		exit(EXIT_FAILURE);
	}

	if(linfo.flagShrink) {
		mrcImage shrink;
		mrcImageParaTypeIntegerCoord S;

		S.z = S.x = S.y = linfo.Shrink;
		//S.z = 1;	
		lmrcImageShrink(&shrink, &mrc, S, 0); 

		mrc = shrink; 
	}
	mrcFileWrite(&mrc, info.outFile, "in main routine", 0);
	return 0;
}

void
additionalUsage(void)
{
	fprintf(stderr, "---- mode ----\n");
	fprintf(stderr, "0x0000000f bits: Direct or Log\n");
	fprintf(stderr, "0x000000f0 bits: Which Color\n");
	fprintf(stderr, "                 R: 00\n");
	fprintf(stderr, "                 G: 10\n");
	fprintf(stderr, "                 B: 20\n");
}

void
lsin2ltiff2mrc(ltiff2mrcInfo* linfo, char* filename, long mode)
{
	FILE* fpt;	
	char s[1024];
	char* keyword;

	fpt = fileOpen(filename, "r");
	while(NULL==stringGetFromFile(s, "Information", fpt, stdout, 3)) {
		keyword = stringGetNthWord(s, 1, " \t,.");
		SSWITCH(keyword) 
			SCASE("SDMI") {
				linfo->flagrealMin = 1;
				linfo->realMin = stringGetNthRealData(s, 2, " \t,."); 
				SBREAK;
			}
			SCASE("SDMA") {
				linfo->flagrealMax = 1;
				linfo->realMax = stringGetNthRealData(s, 2, " \t,."); 
				SBREAK;
			}
		}
	}
}

void
ltiff2mrc(mrcImage* mrc, TIFF* tiff, ltiff2mrcInfo* linfo, long mode)
{
	unsigned short samplesPerPixel;
	unsigned short bitsPerSample;
    unsigned short sampleFormat;
	unsigned short bytesPerSample;
	unsigned short planarConfiguration;
	unsigned short photometric;
	unsigned short matte;
	unsigned short bytesPerRow;
	unsigned short resUnit, resTag;
	unsigned int w, h, row, col;
	float ox, oy, xres, yres;
	unsigned char*  tiffBuffer;
	uint32*  tiffBufferLong;
	double data;

	matte=0;

	bytesPerRow = TIFFScanlineSize(tiff);
	TIFFGetField(tiff, TIFFTAG_PHOTOMETRIC, &photometric);
	switch(photometric) {
		case PHOTOMETRIC_MINISBLACK:
		case PHOTOMETRIC_MINISWHITE:
		case PHOTOMETRIC_RGB:
			break;
		default: {
			TIFFError("ltiff2mrc", "Cannot handle %d photometric", photometric);
			exit(EXIT_FAILURE);
			break;
		}
	}
	TIFFGetFieldDefaulted(tiff, TIFFTAG_BITSPERSAMPLE, &bitsPerSample);
	switch(bitsPerSample) {
		case  8:
		case 16:
		case 32:
			bytesPerSample = bitsPerSample/8;
			break;
		default: {
			TIFFError("ltiff2mrc", "Can not handle %d-bit/sample image", bitsPerSample);
			exit(EXIT_FAILURE);
			break;
		}
	}
	TIFFGetFieldDefaulted(tiff, TIFFTAG_SAMPLESPERPIXEL, &samplesPerPixel);
	switch(samplesPerPixel) {
		case 1:
		case 3:
			break;
		default:
			TIFFError("ltiff2mrc", "Can not handle %d-sample/pixel image", samplesPerPixel);
			exit(EXIT_FAILURE);
			break;
	}
	TIFFGetField(tiff, TIFFTAG_PLANARCONFIG, &planarConfiguration);

	TIFFGetField(tiff, TIFFTAG_MATTEING, &matte);

	TIFFGetField(tiff, TIFFTAG_IMAGEWIDTH, &w);
	TIFFGetField(tiff, TIFFTAG_IMAGELENGTH, &h);
	if(!TIFFGetField(tiff, TIFFTAG_XPOSITION, &ox)) {
		ox = 0;
	}
	if(!TIFFGetField(tiff, TIFFTAG_YPOSITION, &oy)) {
		oy = 0;
	}
	if(!TIFFGetField(tiff, TIFFTAG_RESOLUTIONUNIT, &resUnit)) {
		resTag = RESUNIT_NONE;
	}
    if(!TIFFGetField(tiff, TIFFTAG_SAMPLEFORMAT, &sampleFormat)) {
        switch(sampleFormat) {
            case SAMPLEFORMAT_UINT: 
            case SAMPLEFORMAT_INT: 
            case SAMPLEFORMAT_IEEEFP: { 
                DEBUGPRINT1("sampleFormat: %d\n", sampleFormat);
                break;
            }
            case SAMPLEFORMAT_VOID: 
            case SAMPLEFORMAT_COMPLEXINT: 
            case SAMPLEFORMAT_COMPLEXIEEEFP: {
                fprintf(stderr, "Not supported sampleFormat: %d\n", sampleFormat);
                exit(EXIT_FAILURE);
            }
        }
    }

	mrc->HeaderN.x = w;
	mrc->HeaderN.y = h;
	mrc->HeaderN.z = linfo->nz;

    switch(mode&0xf) {
        case 0: {
			switch(bitsPerSample) {
				case  8: {
					mrc->HeaderMode = mrcCharImage;
					break;
				}
				case 16: {
                    switch(sampleFormat) {
                        case SAMPLEFORMAT_UINT: {
					        mrc->HeaderMode = mrcUShortImage;
                            break;
                        }
                        case SAMPLEFORMAT_INT: {
					        mrc->HeaderMode = mrcShortImage;
                            break;
                        }
                    }
					break;
				}
				case 32: {
                    if(sampleFormat==SAMPLEFORMAT_IEEEFP) {
					    mrc->HeaderMode = mrcFloatImage;
                    } else {
					    TIFFError("ltiff2mrc", "Can not handle %d-bit/sample not float image", bitsPerSample);
					    exit(EXIT_FAILURE);
                    }
					break;
				}
				default: {
					TIFFError("ltiff2mrc", "Can not handle %d-bit/sample image", bitsPerSample);
					exit(EXIT_FAILURE);
				}
			}
            break;
        }
        case 1: {
			mrc->HeaderMode = mrcFloatImage;
            break;
        }
        default: {
            fprintf(stderr, "Not supported mode : %ld\n", mode);
            exit(EXIT_FAILURE);
            break;
        }
    }
	if(linfo->flagfinalmrcMode) {
		mrc->HeaderMode = linfo->finalmrcMode;	
	}

    if(linfo->currentz==0) {
	    mrcInit(mrc, NULL);
    }
	DEBUGPRINT2("(%ud,%ud)\n", w, h);

	switch(samplesPerPixel) {
		case 1: {
			tiffBuffer = (unsigned char*)memoryAllocate(sizeof(unsigned char)*bytesPerRow, "in ltiff2mrc");
			switch(bitsPerSample) {
				case 8: {
					for(row=0; row < h; row++) {
						if(TIFFReadScanline(tiff, tiffBuffer, row, 0)<0) {
							break;
						}
						for(col=0; col < w; col++) {
							if(!linfo->flagSigned) {
								data = (double)*((unsigned char*)(tiffBuffer+col));
							} else {
								data = (double)*((char*)(tiffBuffer+col));
							}
							if(linfo->flagOffset) {
								data += linfo->Offset;
							}
							mrcPixelDataSet(mrc, col, (float)(h - 1 - row), linfo->currentz, data, mrcPixelRePart);
						}
					}
					break;
				}
				case 16: {
					DEBUGPRINT3("16bits image: gray: signed %ld: offset %f flag %ld\n", linfo->flagSigned, linfo->Offset, linfo->flagOffset);
					for(row=0; row < h; row++) {
						if(TIFFReadScanline(tiff, tiffBuffer, row, 0)<0) {
							break;
						}
						for(col=0; col < w; col++) {
							if(!linfo->flagSigned) {
								data = (double)*((unsigned short*)(tiffBuffer+col*bytesPerSample));
							} else {
								data = (double)*((short*)(tiffBuffer+col*bytesPerSample));
							}
							if(linfo->flagOffset) {
								data += linfo->Offset;
							}
							mrcPixelDataSet(mrc, (float)col, (float)(h - 1 - row), linfo->currentz, data, mrcPixelRePart);
						}
					}
					break;
				}
				case 32: {
					DEBUGPRINT3("16bits image: gray: signed %ld: offset %f flag %ld\n", linfo->flagSigned, linfo->Offset, linfo->flagOffset);
					for(row=0; row < h; row++) {
						if(TIFFReadScanline(tiff, tiffBuffer, row, 0)<0) {
							break;
						}
						for(col=0; col < w; col++) {
							if(!linfo->flagSigned) {
								data = (double)*((float*)(tiffBuffer+col*bytesPerSample));
							} else {
								data = (double)*((float*)(tiffBuffer+col*bytesPerSample));
							}
							if(linfo->flagOffset) {
								data += linfo->Offset;
							}
							mrcPixelDataSet(mrc, (float)col, (float)(h - 1 - row), linfo->currentz, data, mrcPixelRePart);
						}
					}
					break;
				}
			}
			break;
		}
		case 3: {
			DEBUGPRINT("in Read");
			switch(bitsPerSample) {
				case 8: {
					tiffBufferLong = (uint32*)memoryAllocate(sizeof(uint32)*w*h, "in ltiff2mrc");
					if(TIFFReadRGBAImage(tiff, w, h, tiffBufferLong, 0)<0) {	
						fprintf(stderr, "TIFFReadRGBAImage: Error\n");
						exit(EXIT_FAILURE);
					}
					for(row=0; row < h; row++) {
						for(col=0; col < w; col++) {
							switch(mode&0xf0) {
								case 0x00: {
#ifdef M68
									data = (double)*((unsigned char*)(tiffBufferLong+col+w*row) + 3);
#else
									data = (double)*((unsigned char*)(tiffBufferLong+col+w*row) + 0);
#endif
									mrcPixelDataSet(mrc, col, row, linfo->currentz, data, mrcPixelRePart);
									break;
								}
								case 0x10: {
#ifdef M68
									data = (double)*((unsigned char*)(tiffBufferLong+col+w*row) + 2);
#else
									data = (double)*((unsigned char*)(tiffBufferLong+col+w*row) + 1);
#endif
									mrcPixelDataSet(mrc, col, row, linfo->currentz, data, mrcPixelRePart);
									break;
								}
								case 0x20: {
#ifdef M68
									data = (double)*((unsigned char*)(tiffBufferLong+col+w*row) + 1);
#else
									data = (double)*((unsigned char*)(tiffBufferLong+col+w*row) + 2);
#endif
									mrcPixelDataSet(mrc, col, row, linfo->currentz, data, mrcPixelRePart);
									break;
								}
								case 0x40: {
#ifdef M68
									data = (double)*((unsigned char*)(tiffBufferLong+col+w*row) + 0);
#else
									data = (double)*((unsigned char*)(tiffBufferLong+col+w*row) + 3);
#endif
									mrcPixelDataSet(mrc, col, row, linfo->currentz, data, mrcPixelRePart);
									break;
								}
								default: {
									fprintf(stderr, "\n");
									exit(EXIT_FAILURE);
								}
							}
						}
					}
					break;
				}
				case 16: {
					tiffBufferLong = (uint32*)memoryAllocate(sizeof(uint32)*w*h*2, "in ltiff2mrc");
					if(TIFFReadRGBAImage(tiff, w, h, tiffBufferLong, 0)<0) {	
						fprintf(stderr, "TIFFReadRGBAImage: Error\n");
						exit(EXIT_FAILURE);
					}
					for(row=0; row < h; row++) {
						for(col=0; col < w; col++) {
							switch(mode&0xf0) {
								case 0x00: {
#ifdef M68
									data = (double)*((unsigned short*)(tiffBufferLong+(col+w*row)) + 3);
#else
									data = (double)*((unsigned short*)(tiffBufferLong+(col+w*row)) + 0);
#endif
									mrcPixelDataSet(mrc, col, row, linfo->currentz, data, mrcPixelRePart);
									break;
								}
								case 0x10: {
#ifdef M68
									data = (double)*((unsigned short*)(tiffBufferLong+(col+w*row)) + 2);
#else
									data = (double)*((unsigned short*)(tiffBufferLong+(col+w*row)) + 1);
#endif
									mrcPixelDataSet(mrc, col, row, linfo->currentz, data, mrcPixelRePart);
									break;
								}
								case 0x20: {
#ifdef M68
									data = (double)*((unsigned short*)(tiffBufferLong+(col+w*row)) + 1);
#else
									data = (double)*((unsigned short*)(tiffBufferLong+(col+w*row)) + 2);
#endif
									mrcPixelDataSet(mrc, col, row, linfo->currentz, data, mrcPixelRePart);
									break;
								}
								case 0x40: {
#ifdef M68
									data = (double)*((unsigned short*)(tiffBufferLong+(col+w*row)) + 0);
#else
									data = (double)*((unsigned short*)(tiffBufferLong+(col+w*row)) + 3);
#endif
									mrcPixelDataSet(mrc, col, row, linfo->currentz, data, mrcPixelRePart);
									break;
								}
								default: {
									fprintf(stderr, "\n");
									exit(EXIT_FAILURE);
								}
							}
						}
					}
					break;
				}
			}
			break;
		}
	}	


	if(!linfo->flagMax) {
		switch(bitsPerSample) {
			case 8: {
				linfo->Max = 255;
				break;
			}
			case 16: {
				linfo->Max = 65535;
				break;
			}
			case 32: {
				linfo->Max = FLT_MIN;
				break;
			}
			default: {
				fprintf(stderr, "Not supported\n");
				exit(EXIT_FAILURE);
				break;
			}
		}
	} 

	if(!linfo->flagMin) {
		linfo->Min = 1;
	} 

	if(!linfo->flagrealMaxBit) {
		switch(bitsPerSample) {
			case 8: {
				linfo->realMaxBit = 255;
				break;
			}
			case 16: {
				linfo->realMaxBit = 65535;
				break;
			}
			case 32: {
				linfo->realMaxBit = FLT_MIN;
				break;
			}
			default: {
				fprintf(stderr, "Not supported\n");
				exit(EXIT_FAILURE);
				break;
			}
		}
	} 

	if(!linfo->flagrealMax) {
		linfo->realMin = 0;
	}

	if(!linfo->flagrealMin) {
		linfo->realMax = linfo->Max;
	}

	if(linfo->flagrealMax || linfo->flagrealMin) {
		for(row=0; row < h; row++) {
			for(col=0; col < w; col++) {
				mrcPixelDataGet(mrc, col, row, 0, &data, mrcPixelRePart, mrcPixelHowNearest);
				data = data*(linfo->realMax - linfo->realMin)/linfo->realMaxBit + linfo->realMin;
				mrcPixelDataSet(mrc, col, row, linfo->currentz, data, mrcPixelRePart);
			}
		}
	}

	if(linfo->Inverse) {
		for(row=0; row < h; row++) {
			for(col=0; col < w; col++) {
				mrcPixelDataGet(mrc, col, row, linfo->currentz, &data, mrcPixelRePart, mrcPixelHowNearest);
				data = (linfo->Max - data)/linfo->Min;
				mrcPixelDataSet(mrc, col, row, linfo->currentz, data, mrcPixelRePart);
			}
		}
	}

	if(linfo->flagTime) {
		for(row=0; row < h; row++) {
			for(col=0; col < w; col++) {
				mrcPixelDataGet(mrc, col, row, linfo->currentz, &data, mrcPixelRePart, mrcPixelHowNearest);
				data = data/linfo->Time;
				mrcPixelDataSet(mrc, col, row, linfo->currentz, data, mrcPixelRePart);
			}
		}
	}

    switch(mode&0xf) {
        case 0: {
            break;
        }
        case 1: {
			for(row=0; row < h; row++) {
				for(col=0; col < w; col++) {
					mrcPixelDataGet(mrc, col, row, linfo->currentz, &data, mrcPixelRePart, mrcPixelHowNearest);
					if(0<data) {
                    	data = log10(linfo->Max/data);
					} else {
                    	data = log10(linfo->Max);
					}
					mrcPixelDataSet(mrc, col, row, linfo->currentz, data, mrcPixelRePart);
				}
            }
            break;
        }
        default: {
            fprintf(stderr, "Not supported mode : %ld\n", mode);
            exit(EXIT_FAILURE);
            break;
        }
    }
    if(1<linfo->nz && linfo->currentz<linfo->nz-1) {
        linfo->currentz++;
    }
    DEBUGPRINT2("%d/%d", linfo->currentz, linfo->nz);
}
