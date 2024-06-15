#include "Property.hh"
#include "FunctionMode.hh"
#include <stdio.h>
#include <string.h>

Property::Property()
{

  //DEFAULT
  displayMode = SpaceFill;
  colorMode = Monochrome;
  atomMode = AtomModeCA;
  pickMode = Default;
  homologyMode = AllData;

  ResMin = 1;
  ResMax = 10;

}

void Property::SetDisplayMode(DisplayMode m)
{
  displayMode = m;
  if(m==BackBone) {
    atomMode = AtomModeCA;
  }
}

DisplayMode Property::GetDisplayMode()
{
  return displayMode;
}

void 
Property::PrintDisplayMode(FILE* fpt)
{
	fprintf(fpt, ">>>> DisplayMode \n"); 
	fprintf(fpt, "SpaceFill: %d\n", SpaceFill); 
	fprintf(fpt, "Point:     %d\n", Point); 
	fprintf(fpt, "BackBone:  %d\n", BackBone); 
}

void Property::SetAtomMode(AtomMode m)
{
  atomMode = m;
  if(displayMode == BackBone)
    {atomMode = AtomModeCA;}
}

AtomMode Property::GetAtomMode()
{
  return atomMode;
}

void
Property::PrintAtomMode(FILE* fpt)
{
	fprintf(fpt, ">>>> AtomMode \n"); 
	fprintf(fpt, "AtomModeAll: %d\n", AtomModeAll); 
	fprintf(fpt, "AtomModeCA:  %d\n", AtomModeCA); 
}

void Property::SetColorMode(ColorMode m)
{
  colorMode =  m;
}

ColorMode Property::GetColorMode()
{
  return colorMode;
}

void
Property::PrintColorMode(FILE* fpt)
{
	fprintf(fpt, ">>>> ColorMode \n"); 
	fprintf(fpt, "Monochrome:  %d\n", Monochrome); 
	fprintf(fpt, "CPK:         %d\n", CPK); 
	fprintf(fpt, "Group:       %d\n", Group); 
	fprintf(fpt, "Amino:       %d\n", Amino); 
	fprintf(fpt, "Temperature: %d\n", Temperature); 
	fprintf(fpt, "HomoColor:   %d\n", HomoColor); 
}

void Property::SetPickMode(PickMode m)
{
  pickMode = m;
  if(m == Homology){
    homologyMode = AllData;
  }
}

PickMode Property::GetPickMode()
{
  return pickMode;
}

void Property::SetHomologyMode(HomologyMode m)
{
  homologyMode = m;
}

HomologyMode Property::GetHomologyMode()
{
  return homologyMode;
}

void Property::SetResNumMinAndMax(int min, int max)
{
  ResMin = min;
  ResMax = max;
  printf("min%d  max%d\n",ResMin,ResMax);
}

void Property::SetDataBaseInfo(char* h, char* p, char* db)
{
  host =strdup(h);
  port = strdup(p);
  dbName = strdup(db);
}

char* Property::GetHostName()
{
  return host;
}

char* Property::GetPortName()
{
  return port;
}

char* Property::GetdbName()
{
  return dbName;
}

void Property::SetHomoTableName(char* tName)
{
  HomoTableName = strdup(tName);
}

char* Property::GetHomoTableName()
{
  return HomoTableName;
}

void Property::SetNoteTableName(char* tName)
{
  NoteTableName = strdup(tName);
}

char* Property::GetNoteTableName()
{
  return NoteTableName;
}

int Property::GetResNumMin()
{
  return ResMin;
}

int Property::GetResNumMax()
{
  return ResMax;
}

void Property::SetPdbCode(char* pCode)
{
  PdbCode = strdup(pCode);
}

char* Property::GetPdbCode()
{
  return PdbCode;
}

