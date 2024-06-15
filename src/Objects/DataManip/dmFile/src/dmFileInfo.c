/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% dmFileInfo ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : dmFileInfo 
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%dmFileInfo ver%I%; Date:%D% %Z%";
#include <string.h>
#include <wchar.h>

#undef DEBUG
#include "genUtil.h"
#include "Memory.h"
#include "../inc/dmFile.h"

void
dmFileInfo(FILE* fpt, dmFile dm, int mode)
{

	dmFileHeaderInfo(fpt, dm, mode);

	switch(dm.version) {
		case 3: {
			dmFile3TagDirectoryInfo(fpt, dm.RootTag3, 0, mode);
			break;
		}
		case 4: {
			dmFile4TagDirectoryInfo(fpt, dm.RootTag4, 0, mode);
			break;
		}
		default: {
			fprintf(stderr, "%d: Not supported version\n", dm.version);
			break;
		}

	}
}

void
dmFileHeaderInfo(FILE* fpt, dmFile dm, int mode)
{
	fprintf(fpt, "header: \n");
	switch(dm.version) {
		case 3: {
			fprintf(fpt, " version: %d\n", dm.Header3.version);
			fprintf(fpt, " RootLength: %d\n", dm.Header3.rootLength);
			fprintf(fpt, " ByteOrder: %d\n", dm.Header3.byteOrder);
			break;
		}
		case 4: {
			fprintf(fpt, " version: %d\n", dm.Header4.version);
			fprintf(fpt, " RootLength: %lld\n", dm.Header4.rootLength);
			fprintf(fpt, " ByteOrder: %d\n", dm.Header4.byteOrder);
			break;
		}
		default: {
			fprintf(stderr, "%d: Not supported version\n", dm.version);
			break;
		}

	}
}

void
dmFile3TagDirectoryInfo(FILE* fpt, dmFile3TagDirectory tagDir, int layer, int mode)
{
	int i;
	char nest[1024];

	nest[0]='\0';
	for(i=0; i<layer; i++) {
		strcat(nest, " ");		
	}

	switch(mode) {
		case 0: {
			fprintf(fpt, "%ssortf: %d\n", nest, tagDir.sortf);
			fprintf(fpt, "%sclosef: %d\n", nest, tagDir.closef);
			fprintf(fpt, "%snumberOfTags: %d\n", nest, tagDir.numberOfTags);
			for(i=0; i<tagDir.numberOfTags; i++) {
				fprintf(fpt, "%s%d: \n", nest, i); 
				fprintf(fpt, "%s tagID: %s \n",  nest, __dmFileTagDirTypeChar[tagDir.Tags[i].tagID]);
				if(0<tagDir.Tags[i].tagNameLength) {
					fprintf(fpt, "%s tagName: %s\n", nest, tagDir.Tags[i].tagName);
				}
				switch(tagDir.Tags[i].tagID) {
					case dmFileTagDirTypeTagDir: {
						fprintf(fpt, "%s TagDir: \n", nest); 
						dmFile3TagDirectoryInfo(fpt, *(tagDir.Tags[i].tagDir), layer+2, mode);
						break;
					}
					case dmFileTagDirTypeTag: {
						dmFile3TagInfo(fpt, tagDir.Tags[i], layer+1, mode);
						break;
					}
					case dmFileTagDirTypeFileEnd: {
						return;
						break;
					}
					default: {
						fprintf(stderr, "Something wrong!: tagID: %x\n", tagDir.Tags[i].tagID);
						break;
					}
				}
			}
			break;
		}
		case 1: {
			fprintf(fpt, "%snumberOfTags: %d\n", nest, tagDir.numberOfTags);
			for(i=0; i<tagDir.numberOfTags; i++) {
				fprintf(fpt, "%s%d: \n", nest, i); 
				if(0<tagDir.Tags[i].tagNameLength) {
					fprintf(fpt, "%s %s: %s\n", nest, __dmFileTagDirTypeChar[tagDir.Tags[i].tagID], tagDir.Tags[i].tagName);
				}
				switch(tagDir.Tags[i].tagID) {
					case dmFileTagDirTypeTagDir: {
						fprintf(fpt, "%s TagDir: \n", nest); 
						dmFile3TagDirectoryInfo(fpt, *(tagDir.Tags[i].tagDir), layer+2, mode);
						break;
					}
					case dmFileTagDirTypeTag: {
						dmFile3TagInfo(fpt, tagDir.Tags[i], layer+1, mode);
						break;
					}
					case dmFileTagDirTypeFileEnd: {
						return;
						break;
					}
					default: {
						fprintf(stderr, "Something wrong!: tagID: %x\n", tagDir.Tags[i].tagID);
						break;
					}
				}
			}
			break;
		}
		default: {
			fprintf(stderr, "Not supported mode in dmFile3TagDirectoryInfo: %d\n", mode);
			break;
		}
	}

}

void
dmFile3TagInfo(FILE* fpt, dmFile3Tag tag, int layer, int mode)
{
	int i;
	char nest[1024];

	nest[0]='\0';
	for(i=0; i<layer; i++) {
		strcat(nest, " ");		
	}

	switch(mode) {
		case 0: {
			fprintf(fpt, "%sDataType: %s\n", nest, __dmFileTagDataTypeChar[tag.info[0]]);
			switch(tag.info[0]) {
				case dmFileTagDataTypeArray: {
					switch(tag.info[1])			{ // Array of Sruct
						case dmFileTagDataTypeStruct: {
							int offset;
							for(i=0; i<tag.info[3]; i++) { // Member Type
								fprintf(fpt, "%sDataType-%d: %s\n", nest, i, __dmFileTagDataTypeChar[tag.info[5+i*2]]);
							}
							// ArraySize
							fprintf(fpt, "%sDataNum: %d\n", nest, tag.info[5+2*tag.info[3]]);

							offset = 0;
							for(i=0; i<tag.info[3]; i++) {
								fprintf(fpt, "%sStructDataPValue-%d: %ld\n", nest, i, tag.pValue3[i]);
								fprintf(fpt, "%sStructDataValue-%d: ", nest, i);
								dmFileValuePrint(fpt, (char*)(tag.value3)+offset, tag.info[5+i*2], tag.info[5+2*tag.info[3]]);
								offset += tag.info[3]*__dmFileTagDataTypeSize[tag.info[5+i*2]];
							}
							break;
						}
						default: { // Simple Array
							fprintf(fpt, "%sArrayDataType: %s\n", nest, __dmFileTagDataTypeChar[tag.info[1]]);
							fprintf(fpt, "%sArrayDataNum: %d\n", nest, tag.info[2]);
							fprintf(fpt, "%sDataPValue: %ld\n", nest, tag.pValue);
							fprintf(fpt, "%sDataValue: ", nest);
							if(0<tag.info[2]) {
								dmFileValuePrint(fpt, tag.value, tag.info[1], tag.info[2]);
							} else {
								fprintf(fpt, "\n");
							}

							break;
						}
					}
					break;
				}
				case dmFileTagDataTypeStruct: { // Simple Struct
					for(i=0; i<tag.info[2]; i++) {
						fprintf(fpt, "%sStructDataType-%d: %s\n", nest, i, __dmFileTagDataTypeChar[tag.info[4+i*2]]);
					}
					for(i=0; i<tag.info[2]; i++) {
						fprintf(fpt, "%sStructDataPValue-%d: %ld\n", nest, i, tag.pValue2[i]);
						fprintf(fpt, "%sStructDataValue-%d: ", nest, i);
						dmFileValuePrint(fpt, tag.value2, tag.info[4+i*2], 1);
					}
					break;
				}
				default: {
					fprintf(fpt, "%sDataPValue: %ld\n", nest, tag.pValue);
					fprintf(fpt, "%sDataValue: ", nest);
					dmFileValuePrint(fpt, tag.value, tag.info[0], 1);
					break;
				}
			}
			break;
		}
		case 1: {
			switch(tag.info[0]) {
				case dmFileTagDataTypeArray: {
					switch(tag.info[1])			{ // Array of Sruct
						case dmFileTagDataTypeStruct: {
							int offset;
							offset = 0;
							for(i=0; i<tag.info[3]; i++) {
								fprintf(fpt, "%s%s-%d[%d](%s)-PValue: %ld\n", nest, tag.tagName, i, tag.info[5+2*tag.info[3]], __dmFileTagDataTypeChar[tag.info[5+i*2]], tag.pValue3[i]);
								fprintf(fpt, "%s%s-%d[%d](%s): ", nest, tag.tagName, i, tag.info[5+2*tag.info[3]], __dmFileTagDataTypeChar[tag.info[5+i*2]]);
								dmFileValuePrint(fpt, (char*)(tag.value3)+offset, tag.info[5+i*2], tag.info[5+2*tag.info[3]]);
								offset += tag.info[3]*__dmFileTagDataTypeSize[tag.info[5+i*2]];
							}
							break;
						}
						default: { // Simple Array
							fprintf(fpt, "%s%s[%d](%s)-PValue: %ld\n", nest, tag.tagName, tag.info[2],  __dmFileTagDataTypeChar[tag.info[1]], tag.pValue);
							fprintf(fpt, "%s%s[%d](%s): ", nest, tag.tagName, tag.info[2],  __dmFileTagDataTypeChar[tag.info[1]]);
							if(0<tag.info[2]) {
								dmFileValuePrint(fpt, tag.value, tag.info[1], tag.info[2]);
							} else {
								fprintf(fpt, "null\n");
							}
							break;
						}
					}
					break;
				}
				case dmFileTagDataTypeStruct: { // Simple Struct
					for(i=0; i<tag.info[2]; i++) {
						fprintf(fpt, "%s%s(%d:%s)-PValue: %ld\n", nest, tag.tagName, i,  __dmFileTagDataTypeChar[tag.info[4+i*2]], tag.pValue2[i]);
						fprintf(fpt, "%s%s(%d:%s): ", nest, tag.tagName, i,  __dmFileTagDataTypeChar[tag.info[4+i*2]]);
						dmFileValuePrint(fpt, tag.value2, tag.info[4+i*2], 1);
					}
					break;
				}
				default: {
					fprintf(fpt, "%s%s(%s)-PValue: %ld\n", nest, tag.tagName,  __dmFileTagDataTypeChar[tag.info[0]], tag.pValue);
					fprintf(fpt, "%s%s(%s): ", nest, tag.tagName,  __dmFileTagDataTypeChar[tag.info[0]]);
					dmFileValuePrint(fpt, tag.value, tag.info[0], 1);
					break;
				}
			}
			break;
		}
		default: {
			fprintf(stderr, "Not supported mode in dmFile3TagInfo: %d\n", mode);
			break;
		}
	}
}

void
dmFile4TagDirectoryInfo(FILE* fpt, dmFile4TagDirectory tagDir, int layer, int mode)
{

	int i;
	char nest[1024];

	nest[0]='\0';
	for(i=0; i<layer; i++) {
		strcat(nest, " ");		
	}

	switch(mode) {
		case 0: {
			fprintf(fpt, "%ssortf: %d\n", nest, tagDir.sortf);
			fprintf(fpt, "%sclosef: %d\n", nest, tagDir.closef);
			fprintf(fpt, "%snumberOfTags: %lld\n", nest, tagDir.numberOfTags);

			for(i=0; i<tagDir.numberOfTags; i++) {
				fprintf(fpt, "%s%d: \n", nest, i); 
				fprintf(fpt, "%s tagID: %s \n",  nest, __dmFileTagDirTypeChar[tagDir.Tags[i].tagID]);
				if(0<tagDir.Tags[i].tagNameLength) {
					fprintf(fpt, "%s tagName: %s\n", nest, tagDir.Tags[i].tagName);
				}
				fprintf(fpt, "%s tagLength: %lld\n", nest, tagDir.Tags[i].tagLength);
				switch(tagDir.Tags[i].tagID) {
					case dmFileTagDirTypeTagDir: {
						fprintf(fpt, "%s TagDir: \n", nest); 
						dmFile4TagDirectoryInfo(fpt, *(tagDir.Tags[i].tagDir), layer+2, mode);
						break;
					}
					case dmFileTagDirTypeTag: {
						dmFile4TagInfo(fpt, tagDir.Tags[i], layer+1, mode);
						break;
					}
					case dmFileTagDirTypeFileEnd: {
						return;
						break;
					}
					default: {
						fprintf(stderr, "Something wrong!: tagID: %x\n", tagDir.Tags[i].tagID);
						break;
					}
				}
			}
			break;
		}
		case 1: {
			fprintf(fpt, "%snumberOfTags: %lld\n", nest, tagDir.numberOfTags);
			for(i=0; i<tagDir.numberOfTags; i++) {
				fprintf(fpt, "%s%d: \n", nest, i); 
				if(0<tagDir.Tags[i].tagNameLength) {
					fprintf(fpt, "%s %s: %s\n", nest, __dmFileTagDirTypeChar[tagDir.Tags[i].tagID], tagDir.Tags[i].tagName);
				}
				switch(tagDir.Tags[i].tagID) {
					case dmFileTagDirTypeTagDir: {
						fprintf(fpt, "%s TagDir: \n", nest); 
						dmFile4TagDirectoryInfo(fpt, *(tagDir.Tags[i].tagDir), layer+2, mode);
						break;
					}
					case dmFileTagDirTypeTag: {
						dmFile4TagInfo(fpt, tagDir.Tags[i], layer+1, mode);
						break;
					}
					case dmFileTagDirTypeFileEnd: {
						return;
						break;
					}
					default: {
						fprintf(stderr, "Something wrong!: tagID: %x\n", tagDir.Tags[i].tagID);
						break;
					}
				}
			}
			break;
		}
		default: {
			fprintf(stderr, "Not supported mode in dmFile4TagDirectoryInfo: %d\n", mode);
			break;
		}
	}
}

void
dmFile4TagInfo(FILE* fpt, dmFile4Tag tag, int layer, int mode)
{
	int i;
	char nest[1024];

	nest[0]='\0';
	for(i=0; i<layer; i++) {
		strcat(nest, " ");		
	}

	switch(mode) {
		case 0: {
			fprintf(fpt, "%sDataType: %s\n", nest, __dmFileTagDataTypeChar[tag.info[0]]);
			switch(tag.info[0]) {
				case dmFileTagDataTypeArray: {
					switch(tag.info[1])	{ // Array of Sruct
						case dmFileTagDataTypeStruct: {
							int offset;
							for(i=0; i<tag.info[3]; i++) {
								fprintf(fpt, "%sDataType-%d: %s\n", nest, i, __dmFileTagDataTypeChar[tag.info[5+i*2]]);
							}
							fprintf(fpt, "%sDataNum: %lld\n", nest, tag.info[5+2*tag.info[3]]);

							offset = 0;
							for(i=0; i<tag.info[3]; i++) {
								fprintf(fpt, "%sStructDataPValue-%d: %ld\n", nest, i, tag.pValue3[i]);
								fprintf(fpt, "%sStructDataValue-%d: ", nest, i);
								dmFileValuePrint(fpt, (char*)(tag.value3)+offset, tag.info[5+i*2], tag.info[5+2*tag.info[3]]);
								offset += tag.info[3]*__dmFileTagDataTypeSize[tag.info[5+i*2]];
							}
							break;
						}
						default: { // Simple Array
							fprintf(fpt, "%sArrayDataType: %s\n", nest, __dmFileTagDataTypeChar[tag.info[1]]);
							fprintf(fpt, "%sArrayDataNum: %lld\n", nest, tag.info[2]);
							fprintf(fpt, "%sDataPValue: %ld\n", nest, tag.pValue);
							fprintf(fpt, "%sDataValue: ", nest);
							if(0<tag.info[2]) {
								dmFileValuePrint(fpt, tag.value, tag.info[1], tag.info[2]);
							} else {
								fprintf(fpt, "\n");
							}
							break;
						}
					}
					break;
				}
				case dmFileTagDataTypeStruct: { // Simple Struct
					for(i=0; i<tag.info[2]; i++) {
						fprintf(fpt, "%sStructDataType-%d: %s\n", nest, i, __dmFileTagDataTypeChar[tag.info[4+i*2]]);
					}
					for(i=0; i<tag.info[2]; i++) {
						fprintf(fpt, "%sStructDataPValue-%d: %ld\n", nest, i, tag.pValue2[i]);
						fprintf(fpt, "%sStructDataValue-%d: ", nest, i);
						dmFileValuePrint(fpt, tag.value2, tag.info[4+i*2], 1);
					}
					break;
				}
				default: {
					fprintf(fpt, "%sDataPValue: %ld\n", nest, tag.pValue);
					fprintf(fpt, "%sDataValue: ", nest);
					dmFileValuePrint(fpt, tag.value, tag.info[0], 1);
					break;
				}
			}
			break;
		}
		case 1: {
			fprintf(fpt, "%sDataType: %s\n", nest, __dmFileTagDataTypeChar[tag.info[0]]);
			switch(tag.info[0]) {
				case dmFileTagDataTypeArray: {
					switch(tag.info[1])	{ // Array of Sruct
						case dmFileTagDataTypeStruct: {
							int offset;
							offset = 0;
							for(i=0; i<tag.info[3]; i++) {
								fprintf(fpt, "%s%s-%d[%lld](%s)-PValue: %ld\n", nest, tag.tagName, i, tag.info[5+2*tag.info[3]], __dmFileTagDataTypeChar[tag.info[5+i*2]], tag.pValue3[i]);
								fprintf(fpt, "%s%s-%d[%lld](%s): ", nest, tag.tagName, i, tag.info[5+2*tag.info[3]], __dmFileTagDataTypeChar[tag.info[5+i*2]]);
								dmFileValuePrint(fpt, (char*)(tag.value3)+offset, tag.info[5+i*2], tag.info[5+2*tag.info[3]]);
								offset += tag.info[3]*__dmFileTagDataTypeSize[tag.info[5+i*2]];
							}
							break;
						}
						default: { // Simple Array
							fprintf(fpt, "%s%s[%lld](%s)-PValue: %ld\n", nest, tag.tagName, tag.info[2],  __dmFileTagDataTypeChar[tag.info[1]], tag.pValue);
							fprintf(fpt, "%s%s[%lld](%s): ", nest, tag.tagName, tag.info[2],  __dmFileTagDataTypeChar[tag.info[1]]);
							if(0<tag.info[2]) {
								dmFileValuePrint(fpt, tag.value, tag.info[1], tag.info[2]);
							} else {
								fprintf(fpt, "\n");
							}
							break;
						}
					}
					break;
				}
				case dmFileTagDataTypeStruct: { // Simple Struct
					for(i=0; i<tag.info[2]; i++) {
						fprintf(fpt, "%s%s(%d:%s)-PValue: %ld\n", nest, tag.tagName, i,  __dmFileTagDataTypeChar[tag.info[4+i*2]], tag.pValue2[i]);
						fprintf(fpt, "%s%s(%d:%s): ", nest, tag.tagName, i,  __dmFileTagDataTypeChar[tag.info[4+i*2]]);
						dmFileValuePrint(fpt, tag.value2, tag.info[4+i*2], 1);
					}
					break;
				}
				default: {
					fprintf(fpt, "%s%s-PValue: %ld\n", nest, tag.tagName, tag.pValue);
					fprintf(fpt, "%s%s: ", nest, tag.tagName);
					dmFileValuePrint(fpt, tag.value, tag.info[0], 1);
					break;
				}
			}
			break;
		}
		default: {
			fprintf(stderr, "Not supported mode in dmFile4TagInfo: %d\n", mode);
			break;
		}
	}
}


