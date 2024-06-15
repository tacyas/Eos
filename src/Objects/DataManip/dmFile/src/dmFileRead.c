/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% dmFileRead ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : dmFileRead 
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%dmFileRead ver%I%; Date:%D% %Z%";
#undef DEBUG
#undef DEBUG2
#include "genUtil.h"
#include "Memory.h"
#include "../inc/dmFile.h"

void
dmFileRead(FILE* fpt, dmFile* dm, char* message, int mode)
{
	int i, j;
	dmFile3Tag* dmTag3;
	dmFile4Tag* dmTag4;

	dmFileInit(dm, 0);
	dmFileHeaderTailRead(fpt, dm, message, mode);

	switch(dm->version) {
		case 3: {
			// Header
			dmFile3HeaderRead(fpt, dm, message, mode);
			// Root Tag
			dmFile3TagDirectoryHeaderRead(fpt, &(dm->RootTag3), message, mode);
			for(i=0; i<dm->RootTag3.numberOfTags; i++) {
				dmTag3 = &(dm->RootTag3.Tags[i]);
				DEBUGPRINT2("Tags-i: %d/%d\n", i, dm->RootTag3.numberOfTags);
				dmFile3TagHeaderRead(fpt, &(dm->RootTag3.Tags[i]), message, mode);
				switch(dm->RootTag3.Tags[i].tagID) {
					case dmFileTagDirTypeTag: { // tag
						DEBUGPRINT("TAG\n");
						dmFile3TagRead(fpt, &(dm->RootTag3.Tags[i]), message, mode);
						break;
					}
					case dmFileTagDirTypeTagDir: { // tag directories
						DEBUGPRINT("TAG DIRECTORIES\n");	
						dm->RootTag3.Tags[i].tagDir = memoryAllocate(sizeof(dmFile3TagDirectory), message);
						dmFile3TagDirectoryRead(fpt, dm->RootTag3.Tags[i].tagDir, message, mode);	
						break;
					}
					case dmFileTagDirTypeFileEnd: {  
						DEBUGPRINT("FILE END\n")
						return; 
						break;
					}
					default: {
						//dmFile3TagRead(fpt, &(dm->RootTag3.Tags[i]), message, mode);
						fprintf(stderr, "Not supported tagID(hex): %X\n", dm->RootTag3.Tags[i].tagID);
						//exit(EXIT_FAILURE);
						break;
					}
				}
			}
			break;
		}
		case 4: {
			// Header
			dmFile4HeaderRead(fpt, dm, message, mode);
			// Root Tag
			dmFile4TagDirectoryHeaderRead(fpt, &(dm->RootTag4), message, mode);
			DEBUGPRINT1("dm->RootTag4.numberOfTags: %lld\n", dm->RootTag4.numberOfTags);
			for(i=0; i<dm->RootTag4.numberOfTags; i++) {
				dmTag4 = &(dm->RootTag4.Tags[i]);
				DEBUGPRINT2("Tags-i: %d/%lld\n", i, dm->RootTag4.numberOfTags);
				dmFile4TagHeaderRead(fpt, &(dm->RootTag4.Tags[i]), message, mode);
				switch(dm->RootTag4.Tags[i].tagID) {
					case dmFileTagDirTypeTag: { // tag
						DEBUGPRINT("TAG\n");
						dmFile4TagRead(fpt, &(dm->RootTag4.Tags[i]), message, mode);
						break;
					}
					case dmFileTagDirTypeTagDir: { // tag directories
						DEBUGPRINT("TAG DIRECTORIES\n");	
						dm->RootTag4.Tags[i].tagDir = memoryAllocate(sizeof(dmFile4TagDirectory), message);
						dmFile4TagDirectoryRead(fpt, dm->RootTag4.Tags[i].tagDir, message, mode);	
						break;
					}
					case dmFileTagDirTypeFileEnd: {  
						DEBUGPRINT("FILE END\n")
						return; 
						break;
					}
					default: {
						//dmFile3TagRead(fpt, &(dm->RootTag4.Tags[i]), message, mode);
						fprintf(stderr, "Not supported tagID(hex): %X\n", dm->RootTag4.Tags[i].tagID);
						//exit(EXIT_FAILURE);
						break;
					}
				}
			}
			break;
		}
		default: {
			fprintf(stderr, "Not supported version: %d\n", dm->version);
			break;
		}
	}
}


void
dmFileHeaderTailRead(FILE* fpt, dmFile* dm, char* message, int mode)
{
	DEBUGPRINT("dmFileHeaderTailRead\n");
	fseek(fpt, 0L, SEEK_SET);
	fread(&(dm->version), sizeof(dmFileInteger4), 1, fpt);
#ifdef II
	memoryByteSwap(&(dm->version), sizeof(dmFileInteger4), 1);
#endif
	DEBUGPRINT1("version: %d\n", dm->version);

	fseek(fpt, -8L, SEEK_END);
	fread(&(dm->Tail), sizeof(dmFileInteger8), 1, fpt);
	if(dm->Tail!=0 && 3<=dm->version) {
		fprintf(stderr, "This file is not dm3/dm4: version %d \n", dm->version);
		exit(EXIT_FAILURE);
	}
}

void
dmFile3HeaderRead(FILE* fpt, dmFile* dm, char* message, int mode)
{
	DEBUGPRINT("dmFile3HeaderRead start\n");
	// Header
	fseek(fpt, 0L, SEEK_SET);
	if(12!=sizeof(dm->Header3)) {
		fprintf(stderr, "Size is strange: %lu expected 12\n", sizeof(dm->Header4));
		fread(&(dm->Header3.version), sizeof(dm->Header3.version), 1, fpt);
		fread(&(dm->Header3.rootLength), sizeof(dm->Header3.rootLength), 1, fpt);
		fread(&(dm->Header3.byteOrder), sizeof(dm->Header3.byteOrder), 1, fpt);
	} else {
		DEBUGPRINT1("Header3 Size: %lu expect 12\n", sizeof(dm->Header4));
		fread(&(dm->Header3), sizeof(dm->Header3), 1, fpt);
	}
#ifdef II
	memoryByteSwap(&(dm->Header3.version), sizeof(dmFileInteger4), 1);
	memoryByteSwap(&(dm->Header3.rootLength), sizeof(dmFileInteger4), 1);
	memoryByteSwap(&(dm->Header3.byteOrder), sizeof(dmFileInteger4), 1);
#endif
	DEBUGPRINT1("version:    %d\n", dm->Header3.version);
	DEBUGPRINT1("RootLength: %d\n", dm->Header3.rootLength);
	DEBUGPRINT1("ByteOrder:  %d\n", dm->Header3.byteOrder);
	DEBUGPRINT("dmFile3HeaderRead end\n");
}


void
dmFile4HeaderRead(FILE* fpt, dmFile* dm, char* message, int mode)
{
	// Header
	fseek(fpt, 0L, SEEK_SET);
	if(16!=sizeof(dm->Header4)) {
		fprintf(stderr, "Size is strange: %lu expected 16\n", sizeof(dm->Header4));
		fread(&(dm->Header4.version), sizeof(dm->Header4.version), 1, fpt);
		fread(&(dm->Header4.rootLength), sizeof(dm->Header4.rootLength), 1, fpt);
		fread(&(dm->Header4.byteOrder), sizeof(dm->Header4.byteOrder), 1, fpt);
	} else {
		DEBUGPRINT1("Header4 Size: %lu expect 16\n", sizeof(dm->Header4));
		fread(&(dm->Header4), sizeof(dm->Header4), 1, fpt);
	}
#ifdef II
	memoryByteSwap(&(dm->Header4.version), sizeof(dmFileInteger4), 1);
	memoryByteSwap(&(dm->Header4.rootLength), sizeof(dmFileInteger8), 1);
	memoryByteSwap(&(dm->Header4.byteOrder), sizeof(dmFileInteger4), 1);
#endif
	DEBUGPRINT1("version:    %d\n", dm->Header4.version);
	DEBUGPRINT1("RootLength: %lld\n", dm->Header4.rootLength);
	DEBUGPRINT1("ByteOrder:  %d\n", dm->Header4.byteOrder);
}


void
dmFile3TagDirectoryRead(FILE* fpt, dmFile3TagDirectory* tagDir, char* message, int mode)
{
	int j;
	DEBUGPRINT("dmFile3TagDirectoryRead Start\n");	
	dmFile3TagDirectoryHeaderRead(fpt, tagDir, message, mode);	
	DEBUGPRINT1("Number of Tages: %d\n", tagDir->numberOfTags);
	for(j=0; j<tagDir->numberOfTags; j++) {
		DEBUGPRINT1("Tags-j(in tag directories): %d in dmFile3TagDirectoryRead\n", j);
		dmFile3TagHeaderRead(fpt, &(tagDir->Tags[j]), message, mode);	
		DEBUGPRINT2("%d tagID(hex): %x dmFile3TagHeaderRead in dmFile3TagDirectoryRead\n", j, tagDir->Tags[j].tagID);

		DEBUGPRINT("TAG or TAGDIR switch Start\n");
		switch(tagDir->Tags[j].tagID) {
			case dmFileTagDirTypeTagDir: { 
				DEBUGPRINT("TAGDIR READ START in dmFile3TagDirectoryRead\n");
				tagDir->Tags[j].tagDir = memoryAllocate(sizeof(dmFile3TagDirectory), message);
				dmFile3TagDirectoryRead(fpt, tagDir->Tags[j].tagDir, message, mode);
				DEBUGPRINT("TAGDIR READ END in dmFile3TagDirectoryRead\n");
				break;
			}
			default: {
				DEBUGPRINT("TAG READ START in dmFile3TagDirectoryRead\n");
				dmFile3TagRead(fpt, &(tagDir->Tags[j]), message, mode);	
				DEBUGPRINT("TAG READ END in dmFile3TagDirectoryRead\n");
				break;
			}
		}
		DEBUGPRINT("TAG or TAGDIR switch End\n");
	}
	DEBUGPRINT("dmFile3TagDirectoryRead end\n");	
}

void
dmFile4TagDirectoryRead(FILE* fpt, dmFile4TagDirectory* tagDir, char* message, int mode)
{
	int j;
	DEBUGPRINT("dmFile4TagDirectoryRead Start\n");	
	dmFile4TagDirectoryHeaderRead(fpt, tagDir, message, mode);	
	DEBUGPRINT1("Number of Tages: %lld\n", tagDir->numberOfTags);
	for(j=0; j<tagDir->numberOfTags; j++) {
		DEBUGPRINT1("Tags-j(in tag directories): %d in dmFile4TagDirectoryRead\n", j);
		dmFile4TagHeaderRead(fpt, &(tagDir->Tags[j]), message, mode);	
		DEBUGPRINT2("%d tagID(hex): %x dmFile4TagHeaderRead in dmFile4TagDirectoryRead\n", j, tagDir->Tags[j].tagID);

		DEBUGPRINT("TAG or TAGDIR switch Start\n");
		switch(tagDir->Tags[j].tagID) {
			case dmFileTagDirTypeTagDir: { 
				DEBUGPRINT("TAGDIR READ START in dmFile4TagDirectoryRead\n");
				tagDir->Tags[j].tagDir = memoryAllocate(sizeof(dmFile4TagDirectory), message);
				dmFile4TagDirectoryRead(fpt, tagDir->Tags[j].tagDir, message, mode);
				DEBUGPRINT("TAGDIR READ END in dmFile3TagDirectoryRead\n");
				break;
			}
			default: {
				DEBUGPRINT("TAG READ START in dmFile4TagDirectoryRead\n");
				dmFile4TagRead(fpt, &(tagDir->Tags[j]), message, mode);	
				DEBUGPRINT("TAG READ END in dmFile4TagDirectoryRead\n");
				break;
			}
		}
		DEBUGPRINT("TAG or TAGDIR switch End\n");
	}
	DEBUGPRINT("dmFile4TagDirectoryRead end\n");	
}

void
dmFile3TagDirectoryHeaderRead(FILE* fpt, dmFile3TagDirectory* RootTag3, char* message, int mode)
{
	DEBUGPRINT("dmFile3TagDirectroyHeaderRead Start\n");
	// Root Tag
	fread(&(RootTag3->sortf), sizeof(dmFileInteger1), 1, fpt);
	fread(&(RootTag3->closef), sizeof(dmFileInteger1), 1, fpt);
	fread(&(RootTag3->numberOfTags), sizeof(dmFileInteger4), 1, fpt);
#ifdef II
	memoryByteSwap(&(RootTag3->numberOfTags), sizeof(dmFileInteger4), 1);
#endif
	DEBUGPRINT1("sortf:    %d\n", RootTag3->sortf);
	DEBUGPRINT1("closef:   %d\n", RootTag3->closef);
	DEBUGPRINT1("numberOfTags:   %d\n", RootTag3->numberOfTags);
	RootTag3->Tags = (dmFile3Tag*)memoryAllocate(sizeof(dmFile3Tag)*RootTag3->numberOfTags, "in dmFileRead");
	DEBUGPRINT("dmFile3TagDirectroyHeaderRead End\n");
}

void
dmFile4TagDirectoryHeaderRead(FILE* fpt, dmFile4TagDirectory* RootTag4, char* message, int mode)
{
	DEBUGPRINT("dmFile4TagDirectoryHeaderRead");
	// Root Tag
	fread(&(RootTag4->sortf), sizeof(dmFileInteger1), 1, fpt);
	fread(&(RootTag4->closef), sizeof(dmFileInteger1), 1, fpt);
	fread(&(RootTag4->numberOfTags), sizeof(dmFileInteger8), 1, fpt);
#ifdef II
	memoryByteSwap(&(RootTag4->numberOfTags), sizeof(dmFileInteger8), 1);
#endif
	DEBUGPRINT1("sortf:    %d\n", RootTag4->sortf);
	DEBUGPRINT1("closef:   %d\n", RootTag4->closef);
	DEBUGPRINT1("numberOfTags:   %lld\n", RootTag4->numberOfTags);
	RootTag4->Tags = (dmFile4Tag*)memoryAllocate(sizeof(dmFile4Tag)*RootTag4->numberOfTags, "in dmFileRead");
}

void
dmFile3TagHeaderRead(FILE* fpt, dmFile3Tag* dmTag, char* message, int mode)
{
	DEBUGPRINT("dmFile3TagHeaderRead Start\n");	
	fread(&(dmTag->tagID), sizeof(dmFileInteger1), 1, fpt);
	fread(&(dmTag->tagNameLength), sizeof(dmFileInteger2), 1, fpt);
#ifdef II
	memoryByteSwap(&(dmTag->tagNameLength), sizeof(dmFileInteger2), 1);		
#endif
	if(0<dmTag->tagNameLength) {
		dmTag->tagName = (char*)memoryAllocate(sizeof(char)*(dmTag->tagNameLength+1), "in dmFileRead");
		fread(dmTag->tagName, sizeof(char), dmTag->tagNameLength, fpt); 
		DEBUGPRINT3("tagID(hex) %X tagNameLength %d tagName %s\n", dmTag->tagID, dmTag->tagNameLength, dmTag->tagName);
	} else {
		DEBUGPRINT2("tagID(hex) %X tagNameLength %d \n", dmTag->tagID, dmTag->tagNameLength);
	}

	if(0<dmTag->tagNameLength) {
	if(0==strncmp("Data", dmTag->tagName, dmTag->tagNameLength)) {
		DEBUGPRINT2("ImageData: %s %d\n", dmTag->tagName, dmTag->tagNameLength);
	}
	}

	DEBUGPRINT("dmFile3TagHeaderRead End\n");	
}

void
dmFile4TagHeaderRead(FILE* fpt, dmFile4Tag* dmTag, char* message, int mode)
{
	DEBUGPRINT("dmFile4TagHeaderRead Start\n");	
	fread(&(dmTag->tagID), sizeof(dmFileInteger1), 1, fpt);
	fread(&(dmTag->tagNameLength), sizeof(dmFileInteger2), 1, fpt);
#ifdef II
	memoryByteSwap(&(dmTag->tagNameLength), sizeof(dmFileInteger2), 1);		
#endif
	if(0<dmTag->tagNameLength) {
		dmTag->tagName = (char*)memoryAllocate(sizeof(char)*(dmTag->tagNameLength+1), "in dmFileRead");
		fread(dmTag->tagName, sizeof(char), dmTag->tagNameLength, fpt); 
		DEBUGPRINT3("tagID(hex) %X tagNameLength %d tagName %s\n", dmTag->tagID, dmTag->tagNameLength, dmTag->tagName);
	} else {
		DEBUGPRINT2("tagID(hex) %X tagNameLength %d \n", dmTag->tagID, dmTag->tagNameLength);
	}

	if(0<dmTag->tagNameLength) {
	if(0==strncmp("Data", dmTag->tagName, dmTag->tagNameLength)) {
		DEBUGPRINT2("ImageData: %s %d\n", dmTag->tagName, dmTag->tagNameLength);
	}
	}
	fread(&(dmTag->tagLength), sizeof(dmFileInteger8), 1, fpt);
#ifdef II
	memoryByteSwap(&(dmTag->tagLength), sizeof(dmFileInteger8), 1);		
#endif

	DEBUGPRINT1("Length: %lld\n", dmTag->tagLength);
	DEBUGPRINT("dmFile4TagHeaderRead End\n");	
}

void
dmFile3TagRead(FILE* fpt, dmFile3Tag* dmTag, char* message, int mode)
{
	int j;

	DEBUGPRINT("dmFile3TagRead Start\n");	
	fread(dmTag->seperator, sizeof(char), 4, fpt); 
	DEBUGPRINT1("%s\n",dmTag->seperator);
	if(0!=strncmp(dmTag->seperator, "%%%%", 4)) {
		fprintf(stderr, "Not supported : Strange!!!\n");
		exit(EXIT_FAILURE);
	} else {
		DEBUGPRINT("\n");
	}
	fread(&(dmTag->ninfo), sizeof(dmFileInteger4), 1, fpt); 
#ifdef II
	memoryByteSwap(&(dmTag->ninfo), sizeof(dmFileInteger4), 1);		
#endif
	DEBUGPRINT1("tag ninfo %d\n", dmTag->ninfo);
	if(0==dmTag->ninfo) {
		DEBUGPRINT1("tag ninfo is zero: %d\n", dmTag->ninfo);
		return;
	}
	dmTag->info = (dmFileInteger4*)memoryAllocate(sizeof(dmFileInteger4)*dmTag->ninfo, "in dmFileRead");					
	fread(dmTag->info, sizeof(dmFileInteger4), dmTag->ninfo, fpt);
#ifdef II
	memoryByteSwap(dmTag->info, sizeof(dmFileInteger4), dmTag->ninfo);		
#endif
	DEBUGPRINT2("tag: info[0] %X ninfo %d\n", dmTag->info[0], dmTag->ninfo);
	switch(dmTag->info[0]) { // dmTag->info[0]: tag data type
		case dmFileTagDataTypeStruct: {
			DEBUGPRINT1("Struct: numEntry %d\n", dmTag->info[2]);
			// dmTag->info[0]       ; 0x0f
			// dmTag->info[1]       ; 0x0  Group Name
			// dmTag->info[2]       ; num of Entries 
			// dmTag->info[2*n + 4] ; data type of value-n
			dmTag->pValue2 =  (long*)memoryAllocate(sizeof(long)*dmTag->info[2], "in dmFileRead");
			dmTag->value2 = (void**)memoryAllocate(sizeof(void*)*dmTag->info[2], "in dmFileRead");
			for(j=0; j<dmTag->info[2]; j++) {
				DEBUGPRINT2("value %d type %d\n", j, dmTag->info[2*j+4]); 
				dmTag->value2[j] = memoryAllocate(__dmFileTagDataTypeSize[dmTag->info[2*j+4]], "in dmFileRead");
				dmTag->pValue2[j] = ftell(fpt);
				fread(dmTag->value2[j], __dmFileTagDataTypeSize[dmTag->info[2*j+4]], 1, fpt);	
#ifdef II
				//memoryByteSwap(dmTag->value2[j], __dmFileTagDataTypeSize[dmTag->info[2*j+4]], 1);		
#endif 
#ifdef DEBUG2
				//dmFileValuePrint(stderr, dmTag->value2[j], __dmFileTagDataTypeSize[dmTag->info[2*j+4]], 1); 
#endif
			}
			break;
		}
		case dmFileTagDataTypeArray: {
			DEBUGPRINT2("ARRAY datatype(hex) %x dataType or 0x0f: %x\n", dmTag->info[0], dmTag->info[1]);
			// dmTag->info[0] ; 0x14: array  
			// dmTag->info[1] ; data type or 0x0f: Struct 
			switch(dmTag->info[1]) {
				case dmFileTagDataTypeStruct: { // array of struct : 0x0f
					// dmTag->info[2] : 0x0 GroupNam
					// dmTag->info[3] : num of Entries
					// dmTag->info[4] : 0x0 FieldNum
					// dmTag->info[2*n + 5] : data type of value-n 
					// dmTag->info[2*dmTag->info[3] + 5 + 2] : size of array
					DEBUGPRINT1("EntryNum: %d\n",  dmTag->info[3]);
					dmTag->pValue3 = (long*)memoryAllocate(sizeof(long)*dmTag->info[3], "in dmFileRead");
					dmTag->value3 = (void**)memoryAllocate(sizeof(void*)*dmTag->info[3], "in dmFileRead");
					for(j=0; j<dmTag->info[3]; j++) {
						DEBUGPRINT3("%d : valueType %x arraySize %d\n", j, dmTag->info[2*j+5], dmTag->info[2*dmTag->info[3] + 4 ]);
						dmTag->value3[j] = memoryAllocate(__dmFileTagDataTypeSize[dmTag->info[2*j+5]]*dmTag->info[2*dmTag->info[3] + 4 ], "in dmFileRead");	
						dmTag->pValue3[j] = ftell(fpt);
						fread(dmTag->value3[j], __dmFileTagDataTypeSize[dmTag->info[2*j+5]], dmTag->info[2*dmTag->info[3] + 4], fpt);	

#ifdef II
						//memoryByteSwap(dmTag->value3[j], __dmFileTagDataTypeSize[dmTag->info[2*j+5]], dmTag->info[2*dmTag->info[3] + 4]);		
#endif 
#ifdef DEBUG2
						//dmFileValuePrint(stderr, &(dmTag->value3[j]), dmTag->info[2*j+5], MIN(16,dmTag->info[2*dmTag->info[3] + 4])); 
#endif
					}
					break;
				}
				default: {
					// dmTag->info[1] ; data type  
					// dmTag->info[2] ; data array size 
					if(0<dmTag->info[2]) {
						DEBUGPRINT3("%d : valueType %x arraySize %d\n", j, dmTag->info[1], dmTag->info[2]);
						dmTag->value = memoryAllocate(__dmFileTagDataTypeSize[dmTag->info[1]]*dmTag->info[2], "in dmFileRead");
						dmTag->pValue = ftell(fpt);
						fread(dmTag->value, __dmFileTagDataTypeSize[dmTag->info[1]], dmTag->info[2], fpt);

#ifdef II
						//memoryByteSwap(dmTag->value, __dmFileTagDataTypeSize[dmTag->info[1]], dmTag->info[2]);		
#endif 
#ifdef DEBUG2
						//dmFileValuePrint(stderr, dmTag->value, dmTag->info[1], MIN(16,dmTag->info[2])); 
#endif
					} else {
						DEBUGPRINT1("Array size is less than 1: %d\n", dmTag->info[2]);
					}
					break;
				}
			}
			break;
		}
		default: {
			dmTag->value = memoryAllocate(__dmFileTagDataTypeSize[dmTag->info[0]], "in dmFileRead");
			dmTag->pValue = ftell(fpt);
			fread(dmTag->value, __dmFileTagDataTypeSize[dmTag->info[0]], 1, fpt);
#ifdef II
			//memoryByteSwap(dmTag->value, __dmFileTagDataTypeSize[dmTag->info[0]], 1);		
#endif 
			//dmFileValuePrint(stderr, dmTag->value, dmTag->info[0], 1); 
			//fprintf(stderr, "Not supported tagType: %d\n", dmTag->info[j]);
			break;
		}
	}
	DEBUGPRINT("dmFile3TagRead End\n");	
}

void
dmFile4TagRead(FILE* fpt, dmFile4Tag* dmTag, char* message, int mode)
{
	int j;

	DEBUGPRINT("dmFile4TagRead Start\n");	
	fread(dmTag->seperator, sizeof(char), 4, fpt); 
	DEBUGPRINT1("%s\n",dmTag->seperator);
	if(0!=strncmp(dmTag->seperator, "%%%%", 4)) {
		fprintf(stderr, "Not supported : Strange!!!\n");
		exit(EXIT_FAILURE);
	} else {
		DEBUGPRINT("\n");
	}
	fread(&(dmTag->ninfo), sizeof(dmFileInteger8), 1, fpt); 
#ifdef II
	memoryByteSwap(&(dmTag->ninfo), sizeof(dmFileInteger8), 1);		
#endif
	DEBUGPRINT1("tag ninfo %lld\n", dmTag->ninfo);
	if(0==dmTag->ninfo) {
		DEBUGPRINT1("tag ninfo is zero: %lld\n", dmTag->ninfo);
		return;
	}
	dmTag->info = (dmFileInteger8*)memoryAllocate(sizeof(dmFileInteger8)*dmTag->ninfo, "in dmFileRead");					
	fread(dmTag->info, sizeof(dmFileInteger8), dmTag->ninfo, fpt);
#ifdef II
	memoryByteSwap(dmTag->info, sizeof(dmFileInteger8), dmTag->ninfo);		
#endif
	DEBUGPRINT2("tag: info[0] %llX ninfo %lld ; # After fread(dmTag->info) \n", dmTag->info[0], dmTag->ninfo);
	switch(dmTag->info[0]) { // dmTag->info[0]: tag data type
		case dmFileTagDataTypeStruct: {
			DEBUGPRINT1("Struct: numEntry %lld\n", dmTag->info[2]);
			// dmTag->info[0]       ; 0x0f
			// dmTag->info[1]       ; 0x0  Group Name
			// dmTag->info[2]       ; num of Entries 
			// dmTag->info[2*n + 4] ; data type of value-n
			dmTag->pValue2 = (long*)memoryAllocate(sizeof(long)*dmTag->info[2], "in dmFileRead");
			dmTag->value2 = (void**)memoryAllocate(sizeof(void*)*dmTag->info[2], "in dmFileRead");
			for(j=0; j<dmTag->info[2]; j++) {
				DEBUGPRINT2("value %d type %lld\n", j, dmTag->info[2*j+4]); 
				dmTag->value2[j] = memoryAllocate(__dmFileTagDataTypeSize[dmTag->info[2*j+4]], "in dmFileRead");
				dmTag->pValue2[j] = ftell(fpt);
				fread(dmTag->value2[j], __dmFileTagDataTypeSize[dmTag->info[2*j+4]], 1, fpt);	
#ifdef II
				//memoryByteSwap(dmTag->value2[j], __dmFileTagDataTypeSize[dmTag->info[2*j+4]], 1);		
#endif 
#ifdef DEBUG2
				dmFileValuePrint(stderr, dmTag->value2[j], __dmFileTagDataTypeSize[dmTag->info[2*j+4]], 1); 
#endif
			}
			break;
		}
		case dmFileTagDataTypeArray: {
			DEBUGPRINT2("ARRAY datatype(hex) %llx dataType or 0x0f: %llx\n", dmTag->info[0], dmTag->info[1]);
			// dmTag->info[0] ; 0x14: array  
			// dmTag->info[1] ; data type or 0x0f: Struct 
			switch(dmTag->info[1]) {
				case dmFileTagDataTypeStruct: { // array of struct : 0x0f
					// dmTag->info[2] : 0x0 GroupNam
					// dmTag->info[3] : num of Entries
					// dmTag->info[4] : 0x0 FieldNum
					// dmTag->info[2*n + 5] : data type of value-n 
					// dmTag->info[2*dmTag->info[3] + 5 + 2] : size of array
					DEBUGPRINT1("EntryNum: %lld\n",  dmTag->info[3]);
					dmTag->pValue3 = (long*)memoryAllocate(sizeof(long)*dmTag->info[3], "in dmFileRead");
					dmTag->value3 = (void**)memoryAllocate(sizeof(void*)*dmTag->info[3], "in dmFileRead");
					for(j=0; j<dmTag->info[3]; j++) {
						DEBUGPRINT3("%d : valueType %llx arraySize %lld\n", j, dmTag->info[2*j+5], dmTag->info[2*dmTag->info[3] + 4 ]);
						dmTag->value3[j] = memoryAllocate(__dmFileTagDataTypeSize[dmTag->info[2*j+5]]*dmTag->info[2*dmTag->info[3] + 4 ], "in dmFileRead");	
						dmTag->pValue3[j] = ftell(fpt);
						fread(dmTag->value3[j], __dmFileTagDataTypeSize[dmTag->info[2*j+5]], dmTag->info[2*dmTag->info[3] + 4], fpt);	

#ifdef II
						//memoryByteSwap(dmTag->value3[j], __dmFileTagDataTypeSize[dmTag->info[2*j+5]], dmTag->info[2*dmTag->info[3] + 4]);		
#endif 
#ifdef DEBUG2
						dmFileValuePrint(stderr, &(dmTag->value3[j]), dmTag->info[2*j+5], MIN(16,dmTag->info[2*dmTag->info[3] + 4])); 
#endif
					}
					break;
				}
				default: {
					// dmTag->info[1] ; data type  
					// dmTag->info[2] ; data array size 
					if(0<dmTag->info[2]) {
						DEBUGPRINT4("%d ; valueType: %llx arraySize: %lld Each: %zu\n", j, dmTag->info[1], dmTag->info[2], __dmFileTagDataTypeSize[dmTag->info[1]]);
						dmTag->value = memoryAllocate(__dmFileTagDataTypeSize[dmTag->info[1]]*dmTag->info[2], "in dmFileRead");
						dmTag->pValue = ftell(fpt);
						fread(dmTag->value, __dmFileTagDataTypeSize[dmTag->info[1]], dmTag->info[2], fpt);

#ifdef II
						//memoryByteSwap(dmTag->value, __dmFileTagDataTypeSize[dmTag->info[1]], dmTag->info[2]);		
#endif 
#ifdef DEBUG2
						dmFileValuePrint(stderr, dmTag->value, dmTag->info[1], MIN(16,dmTag->info[2])); 
#endif
					} else {
						DEBUGPRINT1("Not supported array size: %lld\n", dmTag->info[2]);
					}
					break;
				}
			}
			break;
		}
		default: {
			DEBUGPRINT3("Single Ently %d ; valueType: %llx valueSize: %zu\n", j, dmTag->info[0], __dmFileTagDataTypeSize[dmTag->info[0]]);
			dmTag->value = memoryAllocate(__dmFileTagDataTypeSize[dmTag->info[0]], "in dmFileRead");
			dmTag->pValue = ftell(fpt);
			fread(dmTag->value, __dmFileTagDataTypeSize[dmTag->info[0]], 1, fpt);
#ifdef II
			//memoryByteSwap(dmTag->value, __dmFileTagDataTypeSize[dmTag->info[0]], 1);		
#endif 
#ifdef DEBUG2
			dmFileValuePrint(stderr, dmTag->value, dmTag->info[0], 1); 
			//fprintf(stderr, "Not supported tagType: %d\n", dmTag->info[j]);
#endif
			break;
		}
	}
	DEBUGPRINT("dmFile3TagRead End\n");	
}

