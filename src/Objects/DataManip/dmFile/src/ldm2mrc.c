/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% ldm2mrc ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : ldm2mrc 
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%ldm2mrc ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#undef DEBUG
#include "genUtil.h"
#include "../inc/dmFile.h"

void
ldm2mrc(mrcImage* mrc, dmFile* dm, int mode)
{
	switch(dm->version) {
		case 3: {
			dmFile3TagDirectory2mrc(dm, dm->RootTag3, 0, mode);
			break;
		}
		case 4: {
			dmFile4TagDirectory2mrc(dm, dm->RootTag4, 0, mode);
			break;
		}
		default: {
			fprintf(stderr, "%d: Not supported version\n", dm->version);
			break;
		}
	}
	switch(mode) {
		case 0: {
			DEBUGPRINT("Out in ldm2mrc\n");
			*mrc = dm->image;
			break;
		}
		case 1: {
			DEBUGPRINT("Thumnail in ldm2mrc\n");
			*mrc = dm->thumnail;
			break;
		}
		default: {
			fprintf(stderr, "Not supported mode in ldm2mrc: %d\n", mode);
			exit(EXIT_FAILURE);
		}
	}
}

void
dmFile3TagDirectory2mrc(dmFile* dm, dmFile3TagDirectory tagDir, int layer, int mode)
{
	int i, j, k;
	char nest[1024];
	dmFile3TagDirectory* curDir; 
	mrcImage* curImage;

	switch(mode) {
		case 0: {
			DEBUGPRINT("RealImage\n");
			curImage = &dm->image;
			break;
		}
		case 1: {
			DEBUGPRINT("Thumnail\n");
			curImage = &dm->thumnail;
			break;
		}
		default: {
			break;
		}
	}

	DEBUGPRINT2("%snumberOfTags: %lld\n", nest, tagDir.numberOfTags);
	for(i=0; i<tagDir.numberOfTags; i++) {
		if(0<tagDir.Tags[i].tagNameLength) {
			// ImageList
			if(0==strncmp("ImageList", tagDir.Tags[i].tagName, tagDir.Tags[i].tagNameLength)) {
				for(j=0; j<tagDir.Tags[i].tagDir->numberOfTags; j++) { 
					DEBUGPRINT2("-%d: %s\n", j, tagDir.Tags[i].tagDir->Tags[j].tagName); 
					for(k=0; k<tagDir.Tags[i].tagDir->Tags[j].tagDir->numberOfTags; k++) { 
						DEBUGPRINT2("--%d: %s\n", j, tagDir.Tags[i].tagDir->Tags[j].tagDir->Tags[k].tagName); 
					}
				}
				// ImageData	
				switch(mode) {
					case 0: { // Raw Images
						if(0==strncmp("ImageData", tagDir.Tags[i].tagDir->Tags[1].tagDir->Tags[0].tagName, tagDir.Tags[i].tagDir->Tags[1].tagDir->Tags[0].tagNameLength)) {
							curDir = tagDir.Tags[i].tagDir->Tags[1].tagDir->Tags[0].tagDir;
							curImage = &dm->image;
						} else {
							fprintf(stderr, "Something wrong\n");
							exit(EXIT_FAILURE);
						}
						break;
					}
					case 1: { // Thumnail
						if(0==strncmp("ImageData", tagDir.Tags[i].tagDir->Tags[0].tagDir->Tags[0].tagName, tagDir.Tags[i].tagDir->Tags[0].tagDir->Tags[0].tagNameLength)) {
							curDir = tagDir.Tags[i].tagDir->Tags[0].tagDir->Tags[0].tagDir;
							curImage = &dm->thumnail;
						} else {
							fprintf(stderr, "Something wrong\n");
							exit(EXIT_FAILURE);
						}
						break;
					}
				}
				mrcDefaultHeaderValueSet(curImage);	
				curImage->numTailer = 0;
				for(j=0; j<curDir->numberOfTags; j++) { 			
					DEBUGPRINT2("curDir: %d: %s\n", j, curDir->Tags[j].tagName);
					SSWITCH(curDir->Tags[j].tagName)
						SCASE("Dimensions") {
							curImage->HeaderN.x = ((dmFileInteger4*)curDir->Tags[j].tagDir->Tags[0].value)[0];
							curImage->HeaderN.y = ((dmFileInteger4*)curDir->Tags[j].tagDir->Tags[1].value)[0];				
							if(3==curDir->Tags[j].tagDir->numberOfTags) {
								curImage->HeaderN.z = ((dmFileInteger4*)curDir->Tags[j].tagDir->Tags[2].value)[0];				
							} else {
								curImage->HeaderN.z = 1; 				
							}
							DEBUGPRINT5("%d: %s: %u %u %u\n", mode, curDir->Tags[j].tagName, curImage->HeaderN.x, curImage->HeaderN.y, curImage->HeaderN.z);
							SBREAK;
						}
						SCASE("Calibrations") {
							for(k=0; k<curDir->Tags[j].tagDir->numberOfTags; k++) { 			
								SSWITCH(curDir->Tags[j].tagDir->Tags[k].tagName) 
									SCASE("Dimension") {
										if(0==strncmp(curDir->Tags[j].tagDir->Tags[k].tagDir->Tags[0].tagDir->Tags[2].value, "nm", 2)) {
											curImage->HeaderLength.x = ((float*)curDir->Tags[j].tagDir->Tags[k].tagDir->Tags[0].tagDir->Tags[1].value)[0]*10;
										} else {
											fprintf(stderr, "Not supported units[0]: "); 
											dmFileValuePrint(stderr, curDir->Tags[j].tagDir->Tags[k].tagDir->Tags[0].tagDir->Tags[2].value, dmFileTagDataTypeUInt2, 2);
											curImage->HeaderLength.x = ((float*)curDir->Tags[j].tagDir->Tags[k].tagDir->Tags[0].tagDir->Tags[1].value)[0]*10;
										}
										if(0==strncmp(curDir->Tags[j].tagDir->Tags[k].tagDir->Tags[1].tagDir->Tags[2].value, "nm", 2)) {
											curImage->HeaderLength.y = ((float*)curDir->Tags[j].tagDir->Tags[k].tagDir->Tags[1].tagDir->Tags[1].value)[0]*10;
										} else {
											fprintf(stderr, "Not supported units[1]: "); 
											dmFileValuePrint(stderr, curDir->Tags[j].tagDir->Tags[k].tagDir->Tags[1].tagDir->Tags[2].value, dmFileTagDataTypeUInt2, 2);
											curImage->HeaderLength.y = ((float*)curDir->Tags[j].tagDir->Tags[k].tagDir->Tags[1].tagDir->Tags[1].value)[0]*10;
										}
										curImage->HeaderLength.z = curImage->HeaderLength.x;
										SBREAK;
									}
									SDEFAULT {
										;
									}
								SSWITCHEND
							}
							SBREAK;
						}
						SDEFAULT {
							;
						}
					SSWITCHEND;
				}	

				for(j=0; j<curDir->numberOfTags; j++) { 			
					DEBUGPRINT2("curDir: %d: %s\n", j, curDir->Tags[j].tagName);
					SSWITCH(curDir->Tags[j].tagName)
						SCASE("Data") {
							switch(curDir->Tags[j].info[1]) {
								case dmFileTagDataTypeReal4: {	
									DEBUGPRINT("RealImage\n");
									curImage->HeaderMode = mrcFloatImage; 
									curImage->Image = curDir->Tags[j].value;
									curImage->ImageFloatImage = (float*)curImage->Image;
									break;
								}
								case  dmFileTagDataTypeInt4: {	
									DEBUGPRINT1("Thumnail Transform: %d\n", curImage->HeaderN.x*curImage->HeaderN.y*curImage->HeaderN.z);
									curImage->HeaderMode = mrcCharImage; 
									mrcInit(curImage, NULL);
									for(k=0; k<curImage->HeaderN.x*curImage->HeaderN.y*curImage->HeaderN.z  		; k++) {
										curImage->ImageCharImage[k] = (unsigned char)((((unsigned int*)curDir->Tags[j].value)[k])&0xff);
										//DEBUGPRINT2("%d %f\n", k, curImage->ImageFloatImage[k]);
									}
									break;
								}
								case  dmFileTagDataTypeInt2: {	
									DEBUGPRINT1("Thumnail Transform: %d\n", curImage->HeaderN.x*curImage->HeaderN.y*curImage->HeaderN.z);
									curImage->HeaderMode = mrcShortImage; 
									curImage->Image = curDir->Tags[j].value;
									curImage->ImageShortImage = (unsigned short*)curImage->Image;
									break;
								}
								default: {
									fprintf(stderr, "Not supported mode[Not Real4|Int4|Int2]: %d\n", curDir->Tags[j].info[1]);
									exit(EXIT_FAILURE);
								}
							}
							SBREAK;
						}
						SDEFAULT {
						}
					SSWITCHEND	

				}	
				mrcHiddenDataSet(curImage, 0);
				return;
			}
		}
	}
}

void
dmFile4TagDirectory2mrc(dmFile* dm, dmFile4TagDirectory tagDir, int layer, int mode)
{

	int i, j, k, l, m, n;
	char nest[1024];

	dmFile4TagDirectory* curDir; 
	mrcImage* curImage;

	switch(mode) {
		case 0: {
			DEBUGPRINT("RealImage\n");
			curImage = &dm->image;
			break;
		}
		case 1: {
			DEBUGPRINT("Thumnail\n");
			curImage = &dm->thumnail;
			break;
		}
		default: {
			break;
		}
	}

	DEBUGPRINT2("%snumberOfTags: %lld\n", nest, tagDir.numberOfTags);
	for(i=0; i<tagDir.numberOfTags; i++) {
		if(0<tagDir.Tags[i].tagNameLength) {
			// ImageList
			if(0==strncmp("ImageList", tagDir.Tags[i].tagName, tagDir.Tags[i].tagNameLength)) {
				for(j=0; j<tagDir.Tags[i].tagDir->numberOfTags; j++) { 
					DEBUGPRINT2("-%d: %s\n", j, tagDir.Tags[i].tagDir->Tags[j].tagName); 
					for(k=0; k<tagDir.Tags[i].tagDir->Tags[j].tagDir->numberOfTags; k++) { 
						DEBUGPRINT2("--%d: %s\n", j, tagDir.Tags[i].tagDir->Tags[j].tagDir->Tags[k].tagName); 
					}
				}
				// ImageData	
				switch(mode) {
					case 0: { // Raw Images
						if(0==strncmp("ImageData", tagDir.Tags[i].tagDir->Tags[1].tagDir->Tags[0].tagName, tagDir.Tags[i].tagDir->Tags[1].tagDir->Tags[0].tagNameLength)) {
							curDir = tagDir.Tags[i].tagDir->Tags[1].tagDir->Tags[0].tagDir;
							curImage = &dm->image;
						} else {
							fprintf(stderr, "Something wrong\n");
							exit(EXIT_FAILURE);
						}
						break;
					}
					case 1: { // Thumnail
						if(0==strncmp("ImageData", tagDir.Tags[i].tagDir->Tags[0].tagDir->Tags[0].tagName, tagDir.Tags[i].tagDir->Tags[0].tagDir->Tags[0].tagNameLength)) {
							DEBUGPRINT("Thumnail->ImageData\n");
							curDir = tagDir.Tags[i].tagDir->Tags[0].tagDir->Tags[0].tagDir;
							curImage = &dm->thumnail;
						} else {
							fprintf(stderr, "Something wrong\n");
							exit(EXIT_FAILURE);
						}
						break;
					}
				}
				mrcDefaultHeaderValueSet(curImage);	
				curImage->numTailer = 0;
				for(j=0; j<curDir->numberOfTags; j++) { 			
					DEBUGPRINT2("curDir: %d: %s\n", j, curDir->Tags[j].tagName);
					SSWITCH(curDir->Tags[j].tagName)
						SCASE("Dimensions") {
							DEBUGPRINT("Dimensions\n");
							curImage->HeaderN.x = ((dmFileInteger4*)curDir->Tags[j].tagDir->Tags[0].value)[0];
							curImage->HeaderN.y = ((dmFileInteger4*)curDir->Tags[j].tagDir->Tags[1].value)[0];				
							if(3==curDir->Tags[j].tagDir->numberOfTags) {
								curImage->HeaderN.z = ((dmFileInteger4*)curDir->Tags[j].tagDir->Tags[2].value)[0]; 				
							} else {
								curImage->HeaderN.z = 1;
							}
							DEBUGPRINT5("%d: %s: %u %u %u\n", mode, curDir->Tags[j].tagName, curImage->HeaderN.x, curImage->HeaderN.y, curImage->HeaderN.z);
							SBREAK;
						}
						SCASE("Calibrations") {
							for(k=0; k<curDir->Tags[j].tagDir->numberOfTags; k++) { 			
								SSWITCH(curDir->Tags[j].tagDir->Tags[k].tagName) 
									SCASE("Dimension") {
										if(0==strncmp(curDir->Tags[j].tagDir->Tags[k].tagDir->Tags[0].tagDir->Tags[2].value, "nm", 2)) {
											curImage->HeaderLength.x = ((float*)curDir->Tags[j].tagDir->Tags[k].tagDir->Tags[0].tagDir->Tags[1].value)[0]*10;
										} else {
											fprintf(stderr, "Not supported units[0]: "); 
											dmFileValuePrint(stderr, curDir->Tags[j].tagDir->Tags[k].tagDir->Tags[0].tagDir->Tags[2].value, dmFileTagDataTypeUInt2, 2);
											curImage->HeaderLength.x = ((float*)curDir->Tags[j].tagDir->Tags[k].tagDir->Tags[0].tagDir->Tags[1].value)[0]*10;
										}
										if(0==strncmp(curDir->Tags[j].tagDir->Tags[k].tagDir->Tags[1].tagDir->Tags[2].value, "nm", 2)) {
											curImage->HeaderLength.y = ((float*)curDir->Tags[j].tagDir->Tags[k].tagDir->Tags[1].tagDir->Tags[1].value)[0]*10;
										} else {
											fprintf(stderr, "Not supported units[1]: "); 
											dmFileValuePrint(stderr, curDir->Tags[j].tagDir->Tags[k].tagDir->Tags[1].tagDir->Tags[2].value, dmFileTagDataTypeUInt2, 2);
											curImage->HeaderLength.y = ((float*)curDir->Tags[j].tagDir->Tags[k].tagDir->Tags[1].tagDir->Tags[1].value)[0]*10;
										}
										curImage->HeaderLength.z = curImage->HeaderLength.x;
										SBREAK;
									}
									SDEFAULT {
										;
									}
								SSWITCHEND
							}
							SBREAK;
						}
						SDEFAULT {
							;
						}
					SSWITCHEND	

				}	
				for(j=0; j<curDir->numberOfTags; j++) { 			
					DEBUGPRINT2("curDir: %d: %s\n", j, curDir->Tags[j].tagName);
					SSWITCH(curDir->Tags[j].tagName)
						SCASE("Data") {
							switch(curDir->Tags[j].info[1]) {
								case dmFileTagDataTypeReal4: {	
									DEBUGPRINT("RealImage\n");
									curImage->HeaderMode = mrcFloatImage; 
									curImage->Image = curDir->Tags[j].value;
									curImage->ImageFloatImage = (float*)curImage->Image;
									break;
								}
								case  dmFileTagDataTypeInt4: {	
									DEBUGPRINT1("Thumnail Transform: %d\n", curImage->HeaderN.x*curImage->HeaderN.y*curImage->HeaderN.z);
									curImage->HeaderMode = mrcCharImage; 
									mrcInit(curImage, NULL);
									for(k=0; k<curImage->HeaderN.x*curImage->HeaderN.y*curImage->HeaderN.z  		; k++) {
										curImage->ImageCharImage[k] = (unsigned char)((((unsigned int*)curDir->Tags[j].value)[k])&0xff);
										//DEBUGPRINT2("%d %f\n", k, curImage->ImageFloatImage[k]);
									}
									break;
								}
								default: {
									fprintf(stderr, "Not supported mode: %lld\n", curDir->Tags[j].info[1]);
									exit(EXIT_FAILURE);
								}
							}
						SBREAK;
						}
						SDEFAULT {
						}
					SSWITCHEND	

				}	
				mrcHiddenDataSet(curImage, 0);
				return;
			}
		}
	}
}
