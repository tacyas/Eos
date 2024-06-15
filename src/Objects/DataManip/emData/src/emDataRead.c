#define DEBUG
#include "genUtil.h"
#include "Memory.h"
#include "../inc/emData.h"

void
emDataHeaderRead(emData* em, FILE* fpt, char* message, int mode)
{
	DEBUGPRINT("emDataHeaderRead Start\n");
	if(sizeof(em->Header.Cont)!=EMDATA_HEADER_SIZE) {
		fprintf(stderr, "HeaderSize wrong: %d != %d\n", (int)sizeof(em->Header.Cont), EMDATA_HEADER_SIZE);
		exit(EXIT_FAILURE);
	}
	fseek(fpt, 0L, SEEK_SET);
	fread(em->Header.All, EMDATA_HEADER_SIZE, 1, fpt); 
	if(em->Header.Cont.ExtendedCode[0]=='w'
	 &&em->Header.Cont.ExtendedCode[1]=='w'
	 &&em->Header.Cont.ExtendedCode[2]=='w'
	 &&em->Header.Cont.ExtendedCode[3]=='w') {
		em->version = 1; 
	} else {
		em->version = 0; 	
	}

	if(0xff < em->Header.Cont.type1
	 &&0xff < em->Header.Cont.type2
	 &&0xffff < em->Header.Cont.Nx
	 &&0xffff < em->Header.Cont.Ny
	 &&0xffff < em->Header.Cont.Nz) {
		memoryByteSwap(&(em->Header.Cont.type1), sizeof(emDataTypeIntegerShort), 1);
		memoryByteSwap(&(em->Header.Cont.type2), sizeof(emDataTypeIntegerShort), 1);
		memoryByteSwap(&(em->Header.Cont.Nx), sizeof(emDataTypeInteger), 1);
		memoryByteSwap(&(em->Header.Cont.Ny), sizeof(emDataTypeInteger), 1);
		memoryByteSwap(&(em->Header.Cont.Nz), sizeof(emDataTypeInteger), 1);
		memoryByteSwap(em->Header.Cont.unknown, sizeof(emDataTypeFloat), 36);
		memoryByteSwap(em->Header.All+EMDATA_VER0_HEADER_SIZE, sizeof(emDataTypeFloat), (EMDATA_HEADER_SIZE-EMDATA_VER0_HEADER_SIZE)/sizeof(emDataTypeFloat));
	}	

	DEBUGPRINT("emDataHeaderRead End\n");
#ifdef DEBUG
	emDataHeaderPrint(em, stderr, "DEBUGMODE", 0);
#endif
}

void
emDataFileRead(emData* em, FILE* fpt, char* message, int mode)
{
	DEBUGPRINT("emDataFileRead Start\n");
	emDataHeaderRead(em, fpt, "in emDataFileRead", mode);
	if(em->version < 1) {
		fseek(fpt, EMDATA_VER0_HEADER_SIZE, SEEK_SET);
	} else {
		fseek(fpt, EMDATA_HEADER_SIZE, SEEK_SET);
	}
	em->ShortImage = (short*)memoryAllocate(sizeof(short)*em->Header.Cont.Nx*em->Header.Cont.Ny*em->Header.Cont.Nz, "in emDataFileRead");
	fread(em->ShortImage, sizeof(short), em->Header.Cont.Nx*em->Header.Cont.Ny, fpt);
#ifdef M68
#else
	memoryByteSwap(em->ShortImage, sizeof(short), em->Header.Cont.Nx*em->Header.Cont.Ny);
#endif
}


void
emDataHeaderPrint(emData* em, FILE* fpt, char* message, int mode)
{
	fprintf(fpt, "message: %s\n", message);
	fprintf(fpt, "type1: %d\n", em->Header.Cont.type1);
	fprintf(fpt, "type2: %d\n", em->Header.Cont.type1);
	fprintf(fpt, "Nx: %d \n", em->Header.Cont.Nx);
	fprintf(fpt, "Ny: %d \n", em->Header.Cont.Ny);
	fprintf(fpt, "Nz: %d \n", em->Header.Cont.Nz);
	fprintf(fpt, "Comment: %s\n", em->Header.Cont.Comment);
	if(em->version < 1) {
		return;
	}
	fprintf(fpt, "kV:  %f\n", em->Header.Cont.kV);
	fprintf(fpt, "Mag:  %f\n", em->Header.Cont.Magnification);
	fprintf(fpt, "Post: %f\n", em->Header.Cont.PostMagnification);
	fprintf(fpt, "Cs: %f\n", em->Header.Cont.Cs);
	fprintf(fpt, "Cc: %f\n", em->Header.Cont.Cc);
	fprintf(fpt, "Defocus: %f\n", em->Header.Cont.Defocus);
	fprintf(fpt, "ccdSize: %f\n", em->Header.Cont.ccdSize);
	fprintf(fpt, "offsetX: %f\n", em->Header.Cont.offsetX);
	fprintf(fpt, "offsetY: %f\n", em->Header.Cont.offsetY);
	fprintf(fpt, "pixelSize: %f\n", em->Header.Cont.pixelSize);
	fprintf(fpt, "binning: %f\n", em->Header.Cont.binning);
	fprintf(fpt, "readoutSpeed: %f\n", em->Header.Cont.readOutSpeed);
	fprintf(fpt, "gain: %f\n", em->Header.Cont.gain);
	fprintf(fpt, "sensitivity: %f\n", em->Header.Cont.sensitivity);
	fprintf(fpt, "time: %f\n", em->Header.Cont.time);
	fprintf(fpt, "flatField: %f\n", em->Header.Cont.flatField);
	fprintf(fpt, "average: %f\n", em->Header.Cont.average);
	fprintf(fpt, "min: %f\n", em->Header.Cont.min);
	fprintf(fpt, "max: %f\n", em->Header.Cont.max);
	fprintf(fpt, "StatQ: %f\n", em->Header.Cont.StatisticQuality);
}

