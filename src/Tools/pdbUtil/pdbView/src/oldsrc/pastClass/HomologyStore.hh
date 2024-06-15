#ifndef HOMOLOGY_STORE_HH
#define HOMOLOGY_STORE_HH

#include "DataBase.hh"
#include "FunctionMode.hh"

class HomologyStore : public DataBase{
private:

public:
  HomologyStore();
  void SetKey(int ResNum, char* ResName, char* PdbCode, HomologyMode Mode);
};

#endif /* HOMOLOGY_STORE */
