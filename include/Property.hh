#ifndef PROPERTY_HH
#define PROPERTY_HH

#include <stdio.h>
#include "FunctionMode.hh"

class Property{
private:
  DisplayMode displayMode;
  HomologyMode homologyMode;
  ColorMode colorMode;
  PickMode pickMode;
  AtomMode atomMode;
  int ResMin;
  int ResMax;

  char* PdbCode;
  char* host;
  char* port;
  char* dbName;
  char* HomoTableName;
  char* NoteTableName;

public:
  Property();

  void        SetDisplayMode(DisplayMode m);
  DisplayMode GetDisplayMode();
  static void PrintDisplayMode(FILE* fpt);

  void SetAtomMode(AtomMode m);
  AtomMode GetAtomMode();
  static void PrintAtomMode(FILE* fpt);

  void SetColorMode(ColorMode m);
  ColorMode GetColorMode();
  static void PrintColorMode(FILE* fpt);

  void SetPickMode(PickMode m);
  PickMode GetPickMode();

  void SetHomologyMode(HomologyMode m);
  HomologyMode GetHomologyMode();

  void SetResNumMinAndMax(int min, int max);
  int GetResNumMin();
  int GetResNumMax();

  void SetDataBaseInfo(char* h, char* p, char* db);
  char* GetHostName();
  char* GetPortName();
  char* GetdbName();

  void SetHomoTableName(char* tName);
  char* GetHomoTableName();

  void SetNoteTableName(char* tName);
  char* GetNoteTableName();

  void SetPdbCode(char* pCode);
  char* GetPdbCode();

  };

#endif /* PROPERTY */
