#ifndef DATA_BASE_MAKER_HH
#define DATA_BASE_MAKER_HH

#include "DataBase.hh"
#include <stdio.h>
#include "pdbFile.h"

class DataBaseMaker : public DataBase{
private:
  char TabFileName[20];

public:
  DataBaseMaker(FILE* TabFile, pdbFile* pdb);
  DataBaseMaker(FILE* TabFile);
  void InputToDataBase(FILE* TabFile);
};

#endif /* DATA_BASE_MAKER */
